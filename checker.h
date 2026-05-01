#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <vector>
#include "hardware.h"

struct HardwareSpec {
    int cpuScore;
    int gpuScore;
    int ramGB;
    int storageGB;
};

class GameRequirement {
public:
    GameRequirement() = default;
    GameRequirement(std::string name, HardwareSpec minimum, HardwareSpec recommended, int storageSizeGB)
        : name_(std::move(name)), minimum_(minimum), recommended_(recommended), storageSizeGB_(storageSizeGB) {}

    const std::string &getName() const { return name_; }
    const HardwareSpec &getMinimum() const { return minimum_; }
    const HardwareSpec &getRecommended() const { return recommended_; }
    int getStorageSizeGB() const { return storageSizeGB_; }

private:
    std::string name_;
    HardwareSpec minimum_;
    HardwareSpec recommended_;
    int storageSizeGB_ = 0;
};

enum class CompatibilityLevel {
    CANNOT_RUN,
    LOW_SETTINGS,
    FULL_RUN
};

struct ComponentResult {
    std::string component;
    bool meetsMin;
    bool meetsRec;
    std::string status;
    int userScore;
    int minScore;
    int recScore;
};

struct CompatibilityResult {
    CompatibilityLevel level;
    std::string summary;
    std::vector<ComponentResult> details;
    int totalScore;
};

class CompatibilityChecker {
public:
    static CompatibilityResult check(const Computer &pc, const GameRequirement &game);
};

inline CompatibilityResult CompatibilityChecker::check(const Computer &pc, const GameRequirement &game)
{
    CompatibilityResult result;
    result.totalScore = pc.getTotalScore();
    result.level = CompatibilityLevel::FULL_RUN;

    struct CheckPair {
        std::string component;
        int user;
        int minScore;
        int recScore;
    };

    int cpuScore = pc.getCPU().getPerformanceScore();
    int gpuScore = pc.getGPU().getPerformanceScore();
    int ramGB = pc.getRAM().getCapacityGB();
    int storageGB = pc.getStorage().getCapacityGB();

    std::vector<CheckPair> checks = {
        {"CPU", cpuScore, game.getMinimum().cpuScore, game.getRecommended().cpuScore},
        {"GPU", gpuScore, game.getMinimum().gpuScore, game.getRecommended().gpuScore},
        {"RAM", ramGB, game.getMinimum().ramGB, game.getRecommended().ramGB},
        {"Storage", storageGB, game.getMinimum().storageGB, game.getRecommended().storageGB}
    };

    bool anyBelowMin = false;
    bool anyBelowRec = false;

    for (const auto &check : checks) {
        ComponentResult detail;
        detail.component = check.component;
        detail.userScore = check.user;
        detail.minScore = check.minScore;
        detail.recScore = check.recScore;
        detail.meetsMin = check.user >= check.minScore;
        detail.meetsRec = check.user >= check.recScore;

        if (!detail.meetsMin) {
            detail.status = "Below Minimum";
            anyBelowMin = true;
        } else if (!detail.meetsRec) {
            detail.status = "Below Recommended";
            anyBelowRec = true;
        } else {
            detail.status = "OK";
        }

        result.details.push_back(detail);
    }

    if (anyBelowMin) {
        result.level = CompatibilityLevel::CANNOT_RUN;
        result.summary = "Cannot run this game on your current PC.";
    } else if (anyBelowRec) {
        result.level = CompatibilityLevel::LOW_SETTINGS;
        result.summary = "Your PC can run the game, but lower settings are recommended.";
    } else {
        result.level = CompatibilityLevel::FULL_RUN;
        result.summary = "Your PC meets or exceeds the recommended requirements.";
    }

    return result;
}

#endif // CHECKER_H
