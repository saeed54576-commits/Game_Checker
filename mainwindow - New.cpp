#include "mainwindow.h"
#include "hardware.h"
#include "checker.h"
#include "games_db.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QProgressBar>
#include <algorithm>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    populateHardwareLists();
    populateGameButtons();
    ui->resultPanel->setVisible(false);

    connect(ui->checkButton, &QPushButton::clicked, this, &MainWindow::onCheckClicked);
    connect(ui->cpuComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::validateInputs);
    connect(ui->gpuComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::validateInputs);
    connect(ui->ramSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::validateInputs);
    connect(ui->storageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::validateInputs);
    connect(ui->ssdRadioButton, &QRadioButton::toggled, this, &MainWindow::validateInputs);
    connect(ui->hddRadioButton, &QRadioButton::toggled, this, &MainWindow::validateInputs);

    validateInputs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateHardwareLists()
{
    ui->cpuComboBox->addItem("Intel Core i9-14900K");
    ui->cpuComboBox->addItem("Intel Core i9-13900K");
    ui->cpuComboBox->addItem("Intel Core i9-12900K");
    ui->cpuComboBox->addItem("Intel Core i9-11900K");
    ui->cpuComboBox->addItem("Intel Core i9-10900K");
    ui->cpuComboBox->insertSeparator(ui->cpuComboBox->count());
    ui->cpuComboBox->addItem("Intel Core i7-14700K");
    ui->cpuComboBox->addItem("Intel Core i7-13700K");
    ui->cpuComboBox->addItem("Intel Core i7-12700K");
    ui->cpuComboBox->addItem("Intel Core i7-11700K");
    ui->cpuComboBox->addItem("Intel Core i7-10700K");
    ui->cpuComboBox->addItem("Intel Core i7-9700K");
    ui->cpuComboBox->addItem("Intel Core i7-8700K");
    ui->cpuComboBox->insertSeparator(ui->cpuComboBox->count());
    ui->cpuComboBox->addItem("Intel Core i5-14600K");
    ui->cpuComboBox->addItem("Intel Core i5-13600K");
    ui->cpuComboBox->addItem("Intel Core i5-12600K");
    ui->cpuComboBox->addItem("Intel Core i5-12400");
    ui->cpuComboBox->addItem("Intel Core i5-11600K");
    ui->cpuComboBox->addItem("Intel Core i5-10600K");
    ui->cpuComboBox->addItem("Intel Core i5-10400");
    ui->cpuComboBox->addItem("Intel Core i5-9600K");

    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4090");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4080 Super");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4080");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4070 Ti Super");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4070 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4070 Super");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4070");
    ui->gpuComboBox->insertSeparator(ui->gpuComboBox->count());
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4060 Ti 16GB");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4060 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4060");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 4050");
    ui->gpuComboBox->insertSeparator(ui->gpuComboBox->count());
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3090 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3090");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3080 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3080 12GB");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3080");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3070 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3070");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3060 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3060");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 3050");
    ui->gpuComboBox->insertSeparator(ui->gpuComboBox->count());
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2080 Ti");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2080 Super");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2080");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2070 Super");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2070");
    ui->gpuComboBox->addItem("NVIDIA GeForce RTX 2060 Super");

    ui->ramSpinBox->setRange(2, 256);
    ui->ramSpinBox->setSuffix(" GB");
    ui->ramSpinBox->setValue(16);

    ui->storageSpinBox->setRange(10, 10000);
    ui->storageSpinBox->setSuffix(" GB");
    ui->storageSpinBox->setValue(512);
    ui->ssdRadioButton->setChecked(true);
}

void MainWindow::populateGameButtons()
{
    const auto games = GamesDB::allGames();
    const int columns = 5;
    int row = 0;
    int column = 0;

    for (const auto& game : games) {
        QPushButton* button = new QPushButton(QString::fromStdString(game.getName()), ui->gameGridWidget);
        button->setObjectName("gameButton");
        button->setCheckable(true);
        button->setMinimumHeight(60);
        button->setCursor(Qt::PointingHandCursor);
        gameButtons.append(button);
        ui->gameGridLayout->addWidget(button, row, column);

        connect(button, &QPushButton::clicked, this, &MainWindow::onGameSelected);

        column++;
        if (column >= columns) {
            column = 0;
            row++;
        }
    }
}

void MainWindow::onGameSelected()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    selectedGameName = button->text();
    updateSelectedGameButton(button);
    validateInputs();
}

void MainWindow::updateSelectedGameButton(QPushButton* selectedButton)
{
    for (auto button : gameButtons) {
        bool selected = (button == selectedButton);
        button->setProperty("selected", selected);
        button->setChecked(selected);
        button->style()->unpolish(button);
        button->style()->polish(button);
    }
}

void MainWindow::validateInputs()
{
    bool hasGame = !selectedGameName.isEmpty();
    ui->checkButton->setEnabled(hasGame);
}

void MainWindow::onCheckClicked()
{
    if (selectedGameName.isEmpty())
        return;

    QString cpuModel = ui->cpuComboBox->currentText();
    QString gpuModel = ui->gpuComboBox->currentText();
    int ramAmount = ui->ramSpinBox->value();
    int storageAmount = ui->storageSpinBox->value();
    bool isSSD = ui->ssdRadioButton->isChecked();

    int cpuScore = GamesDB::cpuBenchmarkForModel(cpuModel.toStdString());
    int gpuScore = GamesDB::gpuBenchmarkForModel(gpuModel.toStdString());
    int gpuVram = GamesDB::gpuVRAMForModel(gpuModel.toStdString());

    CPU cpu(cpuModel.toStdString(), 8, 0.0, cpuScore);
    GPU gpu(gpuModel.toStdString(), gpuVram, gpuScore);
    RAM ram(ramAmount, 3200);
    Storage storage(isSSD ? "SSD" : "HDD", storageAmount);
    Computer pc(cpu, gpu, ram, storage);

    const GameRequirement* game = GamesDB::findGame(selectedGameName.toStdString());
    if (!game)
        return;

    CompatibilityResult result = CompatibilityChecker::check(pc, *game);

    ui->verdictEmojiLabel->setText(result.level == CompatibilityLevel::FULL_RUN ? "✅" :
        result.level == CompatibilityLevel::LOW_SETTINGS ? "⚠️" : "❌");
    ui->verdictTextLabel->setText(selectedGameName);
    ui->verdictBadgeLabel->setText(QString::fromStdString(result.level == CompatibilityLevel::FULL_RUN ? "FULL RUN" :
        result.level == CompatibilityLevel::LOW_SETTINGS ? "LOW SETTINGS" : "CANNOT RUN"));
    ui->verdictBadgeLabel->setProperty("level", QVariant::fromValue(static_cast<int>(result.level)));
    ui->verdictBadgeLabel->style()->unpolish(ui->verdictBadgeLabel);
    ui->verdictBadgeLabel->style()->polish(ui->verdictBadgeLabel);

    auto updateRow = [&](QProgressBar* bar, QLabel* statusLabel, const ComponentResult& detail) {
        int maxValue = std::max(detail.recScore, detail.userScore);
        bar->setMaximum(maxValue > 0 ? maxValue : 1);
        bar->setValue(detail.userScore);
        bar->setFormat(QString("%1 / %2").arg(detail.userScore).arg(detail.recScore));
        statusLabel->setText(QString::fromStdString(detail.status));
        QString state = QString::fromStdString(detail.status == "OK" ? "ok" : detail.status == "Below Recommended" ? "warn" : "error");
        statusLabel->setProperty("state", state);
        bar->setProperty("state", state);
        statusLabel->style()->unpolish(statusLabel);
        statusLabel->style()->polish(statusLabel);
        bar->style()->unpolish(bar);
        bar->style()->polish(bar);
        };

    for (const auto& detail : result.details) {
        if (detail.component == "CPU")
            updateRow(ui->cpuProgressBar, ui->cpuStatusLabel, detail);
        else if (detail.component == "GPU")
            updateRow(ui->gpuProgressBar, ui->gpuStatusLabel, detail);
        else if (detail.component == "RAM")
            updateRow(ui->ramProgressBar, ui->ramStatusLabel, detail);
        else if (detail.component == "Storage")
            updateRow(ui->storageProgressBar, ui->storageStatusLabel, detail);
    }

    ui->cpuScoreValue->setText(QString::number(pc.getCPU().getPerformanceScore()));
    ui->gpuScoreValue->setText(QString::number(pc.getGPU().getPerformanceScore()));
    ui->ramScoreValue->setText(QString::number(pc.getRAM().getCapacityGB()) + " GB");

    ui->resultPanel->setVisible(true);
}
