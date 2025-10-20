#include <iostream>
#include <vector>
using namespace std;

//абстрактний компонент//
class IMessage {
public:
    virtual void show() const = 0;
    virtual ~IMessage() = default;
};

// просте повідомлення //
class TextMessage : public IMessage {
private:
    string text;
public:
    TextMessage(const string& t) : text(t) {}
    void show() const override {
        cout << "Text: " << text << endl;
    }
};

// компонувальник, який може містити інші повідомлення //
class MessageGroup : public IMessage {
private:
    vector<IMessage*> messages;
public:
    void add(IMessage* msg) {
        messages.push_back(msg);
    }
    void show() const override {
        cout << "Group:" << endl;
        for (const auto& msg : messages) {
            msg->show();
        }
    }
    ~MessageGroup() {
        for (auto msg : messages) {
            delete msg;
        }
    }
};
int main() {
    // створюємо окремі повідомлення //
    IMessage* msg1 = new TextMessage("Hello!");
    IMessage* msg2 = new TextMessage("How are you?");
    IMessage* msg3 = new TextMessage("Goodbye!");

    // створюємо групу повідомлень //
    MessageGroup* group = new MessageGroup();
    group->add(msg1);
    group->add(msg2);
    group->add(msg3);

    group->show();
    delete group;
    return 0;
}