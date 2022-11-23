#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")
#include <tgbot/tgbot.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "db.h"

using namespace std;
using namespace TgBot;

void createOneColumnKeyboard(const vector<string> &buttonStrings,
                             ReplyKeyboardMarkup::Ptr &kb) {
  for (size_t i = 0; i < buttonStrings.size(); ++i) {
    vector<KeyboardButton::Ptr> row;
    KeyboardButton::Ptr button(new KeyboardButton);
    button->text = buttonStrings[i];
    row.push_back(button);
    kb->keyboard.push_back(row);
  }
}

void createKeyboard(const vector<vector<string>> &buttonLayout,
                    ReplyKeyboardMarkup::Ptr &kb) {
  for (size_t i = 0; i < buttonLayout.size(); ++i) {
    vector<KeyboardButton::Ptr> row;
    for (size_t j = 0; j < buttonLayout[i].size(); ++j) {
      KeyboardButton::Ptr button(new KeyboardButton);
      button->text = buttonLayout[i][j];
      row.push_back(button);
    }
    kb->keyboard.push_back(row);
  }
}

struct MenuText {
  const std::string AboutCompany = "Simply - WE ARE THE BEST!!!";
  const std::string conditions =
      "Give us your pasport, credit card and keys from flat, after that we "
      "give you car:)";
  const std::string contacts =
      "Adress: Russia, Moscow, red square, 7\n ph.: 777-77-77\n web: "
      "/www.rentcar.ru";
  const std::string complete = "For compleating your rent please enter Car ID";
  const std::string exit = "Thank you for your visit! Wait you again";
};

enum class State {
  Init,
  ChooseCar,
  Wait4Firstname,
  Wait4Lastname,
  Wait4Lisence,
  Wait4Carid,
  Wait4Period,
  CompleteRent,
  Wait4completeId
};

static DB Car;
Client client;
State state;
static MenuText menutext;

void ErrorData(Bot &bot, Message::Ptr message) {
  bot.getApi().sendMessage(message->chat->id, "Wrong data. Please try again");
}

void ChangeSC(Message::Ptr message) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent") {
    state = State::Init;
  } else {
    ErrorData(bot, message);
  }
}
void InitCase(Bot &bot, Message::Ptr message) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    return;
  }
  if (message->text == "About company") {
    bot.getApi().sendMessage(message->chat->id, menutext.AboutCompany);
  }
  if (message->text == "Conditions") {
    bot.getApi().sendMessage(message->chat->id, menutext.conditions);
  }
  if (message->text == "Contacts") {
    bot.getApi().sendMessage(message->chat->id, menutext.contacts);
  }
  if (message->text == "Exit") {
    bot.getApi().sendMessage(message->chat->id, menutext.exit);
    return;
  }
  if (message->text == "Price of available cars") {
    state = State::ChooseCar;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
  if (message->text == "Complete the rent") {
    state = State::CompleteRent;
  }
}

void startprog(Bot &bot) {
  ReplyKeyboardMarkup::Ptr keyboardOneCol(new ReplyKeyboardMarkup);
  createOneColumnKeyboard({"Price of available cars", "About company", "Exit"},
                          keyboardOneCol);

  ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
  createKeyboard({{"Price of available cars", "About company"},
                  {"Conditions", "Contacts"},
                  {"Complete the rent", "Exit"}},
                 keyboardWithLayout);

  bot.getEvents().onCommand(
      "start", [&bot, &keyboardOneCol](Message::Ptr message) {
        bot.getApi().sendMessage(
            message->chat->id,
            "Hi, i'm a rentCar Chatbot and i help you to choose car\n/start "
            "for one column keyboard\n/layout for a more complex keyboard",
            false, 0, keyboardOneCol);
      });
  bot.getEvents().onCommand("layout", [&bot, &keyboardWithLayout](
                                          Message::Ptr message) {
    bot.getApi().sendMessage(
        message->chat->id,
        "/start for one column keyboard\n/layout for a more complex keyboard",
        false, 0, keyboardWithLayout);
  });

  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());

    std::string size{""};
    state = State::Init;
    switch (state) {
      case State::Init:
        InitCase(bot, message);
        break;
      case State::ChooseCar:
        ChangeSC(message);
        if (message->text == "Y") {
          ss.str("");
          Car.PrintCarData();
          ss << "\nEnter Car ID to rent";
          bot.getApi().sendMessage(message->chat->id, ss.str());
          state = State::Wait4Carid;
        } else {
          ErrorData(bot, message);
        }
        break;
      case State::Wait4Carid:
        ChangeSC(message);
        if (message->text == "1" || message->text == "2" ||
            message->text == "3" || message->text == "4" ||
            message->text == "5") {
          qq.str("");
          Car.CheckCarReserve(message->text);
          if (qq.str() == "Reserved") {
            bot.getApi().sendMessage(
                message->chat->id,
                "Car under ID " + message->text +
                    " is reserved, please choose another one");
            return;
          }
          Car.SetCarReserve(message->text);
          qq.str("");
          Car.CarName(message->text);
          client.rented_car = qq.str();
          qq.str("");
          Car.CarPrice(message->text);
          client.sum = stoi(qq.str());

          bot.getApi().sendMessage(
              message->chat->id,
              "To rent Car under ID " + message->text + " enter Last Name");
          state = State::Wait4Lastname;
        } else {
          ErrorData(bot, message);
        }
        break;
      case State::Wait4Lastname:
        ChangeSC(message);
        client.last_name = message->text;
        bot.getApi().sendMessage(message->chat->id, "Enter First Name");
        state = State::Wait4Firstname;
        break;
      case State::Wait4Firstname:
        ChangeSC(message);
        client.first_name = message->text;
        bot.getApi().sendMessage(message->chat->id, "Enter Lisence number");
        state = State::Wait4Lisence;
        break;
      case State::Wait4Lisence:
        ChangeSC(message);
        size = message->text;
        if (size.size() == 10) {
          client.lisence = message->text;
          bot.getApi().sendMessage(message->chat->id,
                                   "Enter rent period in days");
          state = State::Wait4Period;
        } else {
          ErrorData(bot, message);
        }
        break;
      case State::Wait4Period:
        ChangeSC(message);
        client.rent_period = stoi(message->text);
        client.sum *= client.rent_period;
        Car.InsertClientData(client.last_name, client.first_name,
                             client.lisence, client.rented_car,
                             client.rent_period, client.sum);
        ss.str("");
        Car.PrintClientData(client.lisence);
        bot.getApi().sendMessage(
            message->chat->id,
            "Congratilations! You reserve car.\n Your order: " + ss.str() +
                "\n Bon Voyage!");
        break;
      case State::CompleteRent:
        ChangeSC(message);
        bot.getApi().sendMessage(message->chat->id, menutext.complete);
        state = State::Wait4completeId;
        break;
      case State::Wait4completeId:
        ChangeSC(message);
        Car.ClientStatus(message->text);
        Car.RemoveCarReserve(message->text);
        bot.getApi().sendMessage(
            message->chat->id, "Your rent ID " + message->text +
                                   " is completed! Thank you. Wait you again");
        break;
    }
  });

  // if (message->text == "Price of available cars") {
  //   ss.str("");
  //   Car.PrintCarData();
  //   ss << "\nEnter Car ID to rent";
  //   bot.getApi().sendMessage(message->chat->id,
  //   ss.str());
  // }
  // if (message->text == "About company") {
  //   bot.getApi().sendMessage(message->chat->id,
  //   menutext.AboutCompany);
  // }
  // if (message->text == "Conditions") {
  //   bot.getApi().sendMessage(message->chat->id,
  //   menutext.conditions);
  // }
  // if (message->text == "Contacts") {
  //   bot.getApi().sendMessage(message->chat->id,
  //   menutext.contacts);
  // }
  // if (message->text == "Complete the rent") {
  //   bot.getApi().sendMessage(message->chat->id,
  //   menutext.complete);
  // }
  // if (message->text == "Exit") {
  //   bot.getApi().sendMessage(message->chat->id,
  //   menutext.exit); return;
  // }
  // });

  // bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
  //   printf("User wrote %s\n", message->text.c_str());

  // if (message->text == "1" || message->text == "2" || message->text == "3"
  // ||
  //     message->text == "4" || message->text == "5") {
  //   qq.str("");
  //   Car.CheckCarReserve(message->text);
  //   if (qq.str() == "Reserved") {
  //     bot.getApi().sendMessage(message->chat->id,
  //                              "Car under ID " + message->text +
  //                                  " is reserved, please choose
  //                                  another one");
  //     return;
  //   }
  //   Car.SetCarReserve(message->text);
  //   qq.str("");
  //   Car.CarName(message->text);
  //   client.rented_car = qq.str();
  //   qq.str("");
  //   Car.CarPrice(message->text);
  //   client.sum = stoi(qq.str());

  //         bot.getApi().sendMessage(message->chat->id,
  //                                  "To rent Car under ID " +
  //                                  message->text
  //                                  +
  //                                      " enter Last Name. Example:
  //                                      LN Ivanov");
  // }
  //   if (StringTools::startsWith(message->text, "LN")) {
  //     message->text.erase(0, 3);
  //     client.last_name = message->text;
  //     bot.getApi().sendMessage(message->chat->id,
  //                              "Enter First Name. Example: FN
  //                              Ivan");
  //   }
  //   if (StringTools::startsWith(message->text, "FN")) {
  //     message->text.erase(0, 3);
  //     client.first_name = message->text;
  //     bot.getApi().sendMessage(message->chat->id,
  //                              "Enter Lisence number. Example: LS
  //                              1234567890");
  //   }
  //   if (StringTools::startsWith(message->text, "LS")) {
  //     message->text.erase(0, 3);
  //     std::string begin = message->text;
  //     std::string size = message->text;
  //     begin.begin();
  //     if (size.size() == 10) {
  //       if (size.size() != 10) {
  //         bot.getApi().sendMessage(message->chat->id,
  //                                  "Wrong number. Shold be 10
  //                                  simbols");
  //       }
  //       client.lisence = stoi(message->text);
  //       bot.getApi().sendMessage(message->chat->id,
  //                                "Enter rent period in days.
  //                                Example: DAY 3");
  //     }
  //   }
  //   if (StringTools::startsWith(message->text, "DAY")) {
  //     message->text.erase(0, 4);
  //     client.rent_period = stoi(message->text);
  //     client.sum *= client.rent_period;
  //     Car.InsertClientData(client.last_name, client.first_name,
  //     client.lisence,
  //                          client.rented_car, client.rent_period,
  //                          client.sum);
  //     ss.str("");
  //     Car.PrintClientData(std::to_string(client.lisence));
  //     bot.getApi().sendMessage(
  //         message->chat->id,
  //         "Congratilations! You reserve car.\n Your order: " +
  //         ss.str()
  //         +
  //             "\n Bon Voyage!");
  //     return;
  //   }
  //   if (StringTools::startsWith(message->text, "ID")) {
  //     message->text.erase(0, 3);
  //     Car.ClientStatus(message->text);
  //     bot.getApi().sendMessage(message->chat->id,
  //                              "Your rent ID " + message->text +
  //                                  " is completed! Thank you. Wait
  //                                  you again");
  //     return;
  //   }
  // });

  signal(SIGINT, [](int s) {
    printf("SIGINT got\n");
    exit(0);
  });

  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    bot.getApi().deleteWebhook();

    TgLongPoll longPoll(bot);
    while (true) {
      printf("Long poll started\n");
      longPoll.start();
    }
  } catch (exception &e) {
    printf("error: %s\n", e.what());
  }
}