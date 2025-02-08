#include <tgbot/tgbot.h>
#include <iostream>
#include <string>
#include <vector>

int main() {
    TgBot::Bot bot("7489856709:AAFIYmV6zdfrmeT74chW1VJRjl8Md0baZjI");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        std::string taskList = "Lista de tarefas:\n";
        taskList += "1. Beber água\n";
        taskList += "2. Fazer exercício\n";
        taskList += "3. Ler um livro\n";
        
        TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
        keyboard->oneTimeKeyboard = true;
        keyboard->resizeKeyboard = true;

        std::vector<TgBot::KeyboardButton::Ptr> row;
        TgBot::KeyboardButton::Ptr button(new TgBot::KeyboardButton);
        button->text = "Marcar como concluído";
        row.push_back(button);
        keyboard->keyboard.push_back(row);

        bot.getApi().sendMessage(message->chat->id, taskList, nullptr, 0, keyboard, "Markdown");
    });

    try {
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Bot rodando..." << std::endl;
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
