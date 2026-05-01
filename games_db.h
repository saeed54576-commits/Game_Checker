#ifndef GAMES_DB_H
#define GAMES_DB_H

#include "checker.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace GamesDB {

inline const std::unordered_map<std::string, int> cpuBenchmarks = {
    {"Intel Core i9-14900K", 9800},
    {"Intel Core i9-13900K", 9600},
    {"Intel Core i9-12900K", 9200},
    {"Intel Core i9-11900K", 8600},
    {"Intel Core i9-10900K", 8000},
    {"Intel Core i7-14700K", 8900},
    {"Intel Core i7-13700K", 8700},
    {"Intel Core i7-12700K", 8200},
    {"Intel Core i7-11700K", 7600},
    {"Intel Core i7-10700K", 7200},
    {"Intel Core i7-9700K", 6500},
    {"Intel Core i7-8700K", 5900},
    {"Intel Core i5-14600K", 7800},
    {"Intel Core i5-13600K", 7600},
    {"Intel Core i5-12600K", 7000},
    {"Intel Core i5-12400", 6200},
    {"Intel Core i5-11600K", 6000},
    {"Intel Core i5-10600K", 5800},
    {"Intel Core i5-10400", 5200},
    {"Intel Core i5-9600K", 4900}
};

inline const std::unordered_map<std::string, int> gpuBenchmarks = {
    {"NVIDIA GeForce RTX 4090", 20000},
    {"NVIDIA GeForce RTX 4080 Super", 17000},
    {"NVIDIA GeForce RTX 4080", 16000},
    {"NVIDIA GeForce RTX 4070 Ti Super", 14500},
    {"NVIDIA GeForce RTX 4070 Ti", 13500},
    {"NVIDIA GeForce RTX 4070 Super", 12000},
    {"NVIDIA GeForce RTX 4070", 11000},
    {"NVIDIA GeForce RTX 4060 Ti 16GB", 10000},
    {"NVIDIA GeForce RTX 4060 Ti", 9500},
    {"NVIDIA GeForce RTX 4060", 7800},
    {"NVIDIA GeForce RTX 4050", 5500},
    {"NVIDIA GeForce RTX 3090 Ti", 15500},
    {"NVIDIA GeForce RTX 3090", 14500},
    {"NVIDIA GeForce RTX 3080 Ti", 14000},
    {"NVIDIA GeForce RTX 3080 12GB", 13500},
    {"NVIDIA GeForce RTX 3080", 13000},
    {"NVIDIA GeForce RTX 3070 Ti", 10500},
    {"NVIDIA GeForce RTX 3070", 9800},
    {"NVIDIA GeForce RTX 3060 Ti", 8500},
    {"NVIDIA GeForce RTX 3060", 6500},
    {"NVIDIA GeForce RTX 3050", 5000},
    {"NVIDIA GeForce RTX 2080 Ti", 10000},
    {"NVIDIA GeForce RTX 2080 Super", 9200},
    {"NVIDIA GeForce RTX 2080", 8800},
    {"NVIDIA GeForce RTX 2070 Super", 8200},
    {"NVIDIA GeForce RTX 2070", 7500},
    {"NVIDIA GeForce RTX 2060 Super", 6800}
};

inline const std::unordered_map<std::string, int> gpuVram = {
    {"NVIDIA GeForce RTX 4090", 24},
    {"NVIDIA GeForce RTX 4080 Super", 16},
    {"NVIDIA GeForce RTX 4080", 16},
    {"NVIDIA GeForce RTX 4070 Ti Super", 16},
    {"NVIDIA GeForce RTX 4070 Ti", 12},
    {"NVIDIA GeForce RTX 4070 Super", 12},
    {"NVIDIA GeForce RTX 4070", 12},
    {"NVIDIA GeForce RTX 4060 Ti 16GB", 16},
    {"NVIDIA GeForce RTX 4060 Ti", 8},
    {"NVIDIA GeForce RTX 4060", 8},
    {"NVIDIA GeForce RTX 4050", 8},
    {"NVIDIA GeForce RTX 3090 Ti", 24},
    {"NVIDIA GeForce RTX 3090", 24},
    {"NVIDIA GeForce RTX 3080 Ti", 12},
    {"NVIDIA GeForce RTX 3080 12GB", 12},
    {"NVIDIA GeForce RTX 3080", 10},
    {"NVIDIA GeForce RTX 3070 Ti", 8},
    {"NVIDIA GeForce RTX 3070", 8},
    {"NVIDIA GeForce RTX 3060 Ti", 8},
    {"NVIDIA GeForce RTX 3060", 12},
    {"NVIDIA GeForce RTX 3050", 8},
    {"NVIDIA GeForce RTX 2080 Ti", 11},
    {"NVIDIA GeForce RTX 2080 Super", 8},
    {"NVIDIA GeForce RTX 2080", 8},
    {"NVIDIA GeForce RTX 2070 Super", 8},
    {"NVIDIA GeForce RTX 2070", 8},
    {"NVIDIA GeForce RTX 2060 Super", 8}
};

inline const std::vector<GameRequirement> gameDatabase = {
    {"Cyberpunk 2077", {4200, 4600, 8, 70}, {7500, 10400, 16, 70}, 70},
    {"Elden Ring", {4500, 3400, 12, 60}, {6800, 9500, 16, 60}, 60},
    {"GTA V", {3200, 1900, 4, 72}, {5500, 5700, 8, 72}, 72},
    {"Fortnite", {3000, 1400, 8, 29}, {6000, 5800, 16, 29}, 29},
    {"Red Dead Redemption 2", {4500, 4800, 12, 150}, {7000, 9600, 16, 150}, 150},
    {"The Witcher 3", {3200, 2400, 6, 35}, {5500, 6300, 12, 35}, 35},
    {"Valorant", {2500, 1000, 4, 20}, {5000, 3800, 8, 20}, 20},
    {"Microsoft Flight Simulator", {5500, 6000, 16, 150}, {8500, 12000, 32, 150}, 150},
    {"God of War", {4200, 3800, 8, 70}, {7500, 9600, 16, 70}, 70},
    {"Minecraft", {2000, 800, 4, 4}, {4000, 2600, 8, 4}, 4},
    {"Counter-Strike 2", {3000, 1900, 8, 85}, {5500, 5800, 16, 85}, 85},
    {"Starfield", {5000, 6000, 16, 125}, {8000, 10800, 16, 125}, 125},
    {"Baldur's Gate 3", {4500, 4000, 8, 150}, {7000, 8000, 16, 150}, 150},
    {"Hogwarts Legacy", {4800, 5000, 12, 85}, {7500, 9500, 16, 85}, 85},
    {"Apex Legends", {2800, 1400, 8, 60}, {5200, 5600, 16, 60}, 60},
    {"Assassin's Creed Valhalla", {4200, 4800, 8, 85}, {7300, 9000, 16, 85}, 85},
    {"Forza Horizon 5", {3300, 2600, 8, 110}, {6200, 7200, 16, 110}, 110},
    {"Rainbow Six Siege", {2400, 1300, 8, 60}, {5200, 4500, 16, 60}, 60},
    {"Doom Eternal", {3200, 1400, 8, 50}, {6400, 5400, 16, 50}, 50},
    {"Horizon Zero Dawn", {3500, 3000, 8, 80}, {7000, 8600, 16, 80}, 80},
    {"Metro Exodus", {3200, 4000, 8, 90}, {6800, 7600, 16, 90}, 90},
    {"Battlefield 2042", {4000, 4800, 8, 120}, {7600, 9400, 16, 120}, 120},
    {"The Last of Us Part I", {3600, 3200, 8, 100}, {7100, 8300, 16, 100}, 100},
    {"Control", {3400, 4200, 8, 75}, {7000, 8800, 16, 75}, 75},
    {"Resident Evil Village", {3000, 2600, 8, 75}, {6200, 5800, 16, 75}, 75}
};

inline const std::vector<GameRequirement> &allGames() {
    return gameDatabase;
}

inline int cpuBenchmarkForModel(const std::string &model) {
    auto it = cpuBenchmarks.find(model);
    return it != cpuBenchmarks.end() ? it->second : 0;
}

inline int gpuBenchmarkForModel(const std::string &model) {
    auto it = gpuBenchmarks.find(model);
    return it != gpuBenchmarks.end() ? it->second : 0;
}

inline int gpuVRAMForModel(const std::string &model) {
    auto it = gpuVram.find(model);
    return it != gpuVram.end() ? it->second : 0;
}

inline const GameRequirement *findGame(const std::string &name) {
    for (const auto &game : gameDatabase) {
        if (game.getName() == name) {
            return &game;
        }
    }
    return nullptr;
}

} // namespace GamesDB

#endif // GAMES_DB_H
