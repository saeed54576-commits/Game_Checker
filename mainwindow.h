#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTextEdit>
#include <QLineEdit>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class QPushButton;
class ChatAIWorker;

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
    void onAIChatButtonClicked();
    void onSendMessageClicked();
    void onAIResponseReceived(const QString &response);
    void onAIError(const QString &error);

private:
    void populateHardwareLists();
    void populateGameButtons();
    void updateSelectedGameButton(QPushButton* selectedButton);
    void setupAIChat();
    void addMessageToChat(const QString &message, bool isUser);

    Ui::MainWindow* ui;
    QString selectedGameName;
    QList<QPushButton*> gameButtons;
    
    // AI Chat widgets
    QTextEdit* chatDisplay;
    QLineEdit* chatInput;
    QPushButton* sendButton;
    QPushButton* aiChatButton;
    
    // AI Worker thread
    ChatAIWorker* aiWorker;
    QThread* aiThread;
};

#endif // MAINWINDOW_H
