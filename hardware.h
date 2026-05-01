#ifndef HARDWARE_H
#define HARDWARE_H

#include <string>

class Hardware {
public:
    virtual int getPerformanceScore() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Hardware() = default;
};

class CPU : public Hardware {
public:
    CPU() = default;
    CPU(std::string model, int cores, double clockSpeedGHz, int benchmarkScore)
        : model_(std::move(model)), cores_(cores), clockSpeedGHz_(clockSpeedGHz), benchmarkScore_(benchmarkScore) {}

    int getPerformanceScore() const override { return benchmarkScore_; }
    std::string getName() const override { return model_; }

    const std::string &getModel() const { return model_; }
    void setModel(const std::string &model) { model_ = model; }

    int getCores() const { return cores_; }
    void setCores(int cores) { cores_ = cores; }

    double getClockSpeedGHz() const { return clockSpeedGHz_; }
    void setClockSpeedGHz(double clockSpeedGHz) { clockSpeedGHz_ = clockSpeedGHz; }

    int getBenchmarkScore() const { return benchmarkScore_; }
    void setBenchmarkScore(int benchmarkScore) { benchmarkScore_ = benchmarkScore; }

private:
    std::string model_;
    int cores_ = 0;
    double clockSpeedGHz_ = 0.0;
    int benchmarkScore_ = 0;
};

class GPU : public Hardware {
public:
    GPU() = default;
    GPU(std::string model, int vramGB, int benchmarkScore)
        : model_(std::move(model)), vramGB_(vramGB), benchmarkScore_(benchmarkScore) {}

    int getPerformanceScore() const override { return benchmarkScore_ + (vramGB_ * 200); }
    std::string getName() const override { return model_; }

    const std::string &getModel() const { return model_; }
    void setModel(const std::string &model) { model_ = model; }

    int getVramGB() const { return vramGB_; }
    void setVramGB(int vramGB) { vramGB_ = vramGB; }

    int getBenchmarkScore() const { return benchmarkScore_; }
    void setBenchmarkScore(int benchmarkScore) { benchmarkScore_ = benchmarkScore; }

private:
    std::string model_;
    int vramGB_ = 0;
    int benchmarkScore_ = 0;
};

class RAM : public Hardware {
public:
    RAM() = default;
    RAM(int capacityGB, int speedMHz)
        : capacityGB_(capacityGB), speedMHz_(speedMHz) {}

    int getPerformanceScore() const override { return capacityGB_ * 100 + speedMHz_ / 10; }
    std::string getName() const override { return "RAM"; }

    int getCapacityGB() const { return capacityGB_; }
    void setCapacityGB(int capacityGB) { capacityGB_ = capacityGB; }

    int getSpeedMHz() const { return speedMHz_; }
    void setSpeedMHz(int speedMHz) { speedMHz_ = speedMHz; }

private:
    int capacityGB_ = 0;
    int speedMHz_ = 0;
};

class Storage : public Hardware {
public:
    Storage() = default;
    Storage(std::string type, int capacityGB)
        : type_(std::move(type)), capacityGB_(capacityGB) {}

    int getPerformanceScore() const override {
        int base = capacityGB_ / 10;
        return (type_ == "SSD") ? base + 500 : base;
    }
    std::string getName() const override { return type_; }

    const std::string &getType() const { return type_; }
    void setType(const std::string &type) { type_ = type; }

    int getCapacityGB() const { return capacityGB_; }
    void setCapacityGB(int capacityGB) { capacityGB_ = capacityGB; }

private:
    std::string type_ = "HDD";
    int capacityGB_ = 0;
};

class Computer {
public:
    Computer() = default;
    Computer(const CPU &cpu, const GPU &gpu, const RAM &ram, const Storage &storage)
        : cpu_(cpu), gpu_(gpu), ram_(ram), storage_(storage) {}

    int getTotalScore() const {
        return cpu_.getPerformanceScore()
             + gpu_.getPerformanceScore()
             + ram_.getPerformanceScore()
             + storage_.getPerformanceScore();
    }

    const CPU &getCPU() const { return cpu_; }
    void setCPU(const CPU &cpu) { cpu_ = cpu; }

    const GPU &getGPU() const { return gpu_; }
    void setGPU(const GPU &gpu) { gpu_ = gpu; }

    const RAM &getRAM() const { return ram_; }
    void setRAM(const RAM &ram) { ram_ = ram; }

    const Storage &getStorage() const { return storage_; }
    void setStorage(const Storage &storage) { storage_ = storage; }

private:
    CPU cpu_;
    GPU gpu_;
    RAM ram_;
    Storage storage_;
};

#endif // HARDWARE_H
