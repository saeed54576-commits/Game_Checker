#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onCheckClicked();
    void onGameSelected();
    void validateInputs();

private:
    void populateHardwareLists();
    void populateGameButtons();
    void updateSelectedGameButton(QPushButton* selectedButton);

    Ui::MainWindow* ui;
    QString selectedGameName;
    QList<QPushButton*> gameButtons;
};

#endif // MAINWINDOW_H
