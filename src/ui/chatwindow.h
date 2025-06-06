#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QString>
#include <QComboBox>
#include "../core/chat/chatcore.h"
#include "../core/voice/voicehandler.h"
#include "../core/role/customrole.h"
#include "../core/role/rolemanager.h"
#include "customroledialog.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

    void appendMessage(const QString &sender, const QString &text, const QString &avatarPath = "");
    void clearChatHistory();
    QString getCurrentRole() const;
    void setRoleManager(RoleManager *manager);
    void loadChatHistory(const QString &roleName);
    
    // 获取当前角色的提示词
    QString getCurrentRolePrompt() const;

public slots:
    void setCurrentRole(const QString &role);
    void updateRoleList(const QStringList &roles);
    void onRoleSelected(const QString &roleName); // Slot to handle role selection from MainWindow
    
    // Added back from .cpp connections
    void handleMessageReceived(const Message &message);
    void handleError(const QString &error);
    void handleTextRecognized(const QString &text);

private slots:
    void on_sendButton_clicked();
    void on_newRoleButton_clicked(); // Slot for the new role button
    void on_roleComboBox_currentIndexChanged(int index); // Slot for role selection change, was onRoleComboBoxChanged
    void handleRoleConfirmed(const RoleData &data); // Connected from CustomRoleDialog

    // Added back from .cpp connections
    void handleVoiceButtonClicked(); // Explicitly connected in .cpp for voiceHandler logic
    // void onRoleComboBoxChanged(int index); // Replaced by on_roleComboBox_currentIndexChanged from .ui
    void onStopRecording();

private:
    Ui::ChatWindow *ui;
    ChatCore *chatCore;             // Moved up for initialization order consistency
    VoiceHandler *voiceHandler;     // Moved up for initialization order consistency
    QString currentRole;
    QString currentAvatarPath;
    RoleManager *roleManager;
    void saveChatHistory(const QString &roleName);
    void displayWelcomeMessage(const QString &roleName);
    
    // Helper methods
    void initializeUI();
    void setupConnections();

signals:
    void messageSent(const QString &role, const QString &message);
    void roleSelected(const QString &roleName); // Signal to notify role selection
    void newRoleCreated(const RoleData &data); // Signal to notify new role creation to MainWindow
};

#endif // CHATWINDOW_H 