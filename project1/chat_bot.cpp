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
  const std::string complete =
      "For compleating your rent please enter Lisence number";
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
static MenuText menutext;
State state;

void ErrorData(Bot &bot, Message::Ptr message) {
  bot.getApi().sendMessage(message->chat->id, "Wrong data. Please try again");
}

void ChangeSC(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    state = State::Init;
  }
  if (message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit") {
    state = State::Init;
  }
  if (message->text == "Price of available cars") {
    state = State::ChooseCar;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
  if (message->text == "Complete the rent") {
    state = State::CompleteRent;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
}

void InitCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    bot.getApi().sendMessage(
        message->chat->id,
        "/start for one column keyboard\n/layout for a more complex keyboard");
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
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
}

void W4CarIdCase(Bot &bot, Message::Ptr message, State &state) {
  ChangeSC(bot, message, state);

  if (message->text == "1" || message->text == "2" || message->text == "3" ||
      message->text == "4" || message->text == "5") {
    qq.str("");
    Car.CheckCarReserve(message->text);
    if (qq.str() == "Reserved") {
      bot.getApi().sendMessage(message->chat->id,
                               "Car under ID " + message->text +
                                   " is reserved, please choose another one");
      return;
    }
    Car.SetCarReserve(message->text);
    client.car_id = message->text;
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
}

void W4LastNameCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    client.last_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter First Name");
    state = State::Wait4Firstname;
  }
}

void W4FirstNameCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    client.first_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter License number");
    state = State::Wait4Lisence;
  }
}

void W4LicenseCase(Bot &bot, Message::Ptr message, State &state,
                   std::string &size) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    size = message->text;
    if (size.size() == 10 & StringTools::startsWith(message->text, "0") ||
        StringTools::startsWith(message->text, "1") ||
        StringTools::startsWith(message->text, "2") ||
        StringTools::startsWith(message->text, "3") ||
        StringTools::startsWith(message->text, "4") ||
        StringTools::startsWith(message->text, "5") ||
        StringTools::startsWith(message->text, "6") ||
        StringTools::startsWith(message->text, "7") ||
        StringTools::startsWith(message->text, "8") ||
        StringTools::startsWith(message->text, "9")) {
      client.license = message->text;
      bot.getApi().sendMessage(message->chat->id, "Enter rent period in days");
      state = State::Wait4Period;
    }
  }
}

void W4PeriodCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  }
  if (StringTools::startsWith(message->text, "0") ||
      StringTools::startsWith(message->text, "1") ||
      StringTools::startsWith(message->text, "2") ||
      StringTools::startsWith(message->text, "3") ||
      StringTools::startsWith(message->text, "4") ||
      StringTools::startsWith(message->text, "5") ||
      StringTools::startsWith(message->text, "6") ||
      StringTools::startsWith(message->text, "7") ||
      StringTools::startsWith(message->text, "8") ||
      StringTools::startsWith(message->text, "9")) {
    client.rent_period = stoi(message->text);
    client.sum *= client.rent_period;
    Car.InsertClientData(client.last_name, client.first_name, client.license,
                         client.car_id, client.rented_car, client.rent_period,
                         client.sum);
    ss.str("");
    Car.PrintClientData(client.license);
    bot.getApi().sendMessage(
        message->chat->id,
        "Congratilations! You reserve car.\n Your order: \n" + ss.str() +
            "\n Bon Voyage!");
    state = State::Init;
  }
}

void W4ComplIdCase(Bot &bot, Message::Ptr message, State &state,
                   std::string &size) {
  ChangeSC(bot, message, state);
  size = message->text;
  if (size.size() == 10 & StringTools::startsWith(message->text, "0") ||
      StringTools::startsWith(message->text, "1") ||
      StringTools::startsWith(message->text, "2") ||
      StringTools::startsWith(message->text, "3") ||
      StringTools::startsWith(message->text, "4") ||
      StringTools::startsWith(message->text, "5") ||
      StringTools::startsWith(message->text, "6") ||
      StringTools::startsWith(message->text, "7") ||
      StringTools::startsWith(message->text, "8") ||
      StringTools::startsWith(message->text, "9")) {
    Car.ClientStatus(message->text);
    qq.str("");
    Car.ClientGetCarId(message->text);
    Car.RemoveCarReserve(qq.str());
    bot.getApi().sendMessage(message->chat->id,
                             "Your rent " + message->text +
                                 " is completed! Thank you. Wait you again");
    state = State::Init;
  }
}

void W4ComplRentCase(Bot &bot, Message::Ptr message, State &state) {
  ChangeSC(bot, message, state);
  if (message->text == "Y") {
    bot.getApi().sendMessage(message->chat->id, menutext.complete);
    state = State::Wait4completeId;
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

  State state = State::Init;

  bot.getEvents().onAnyMessage([&bot, &state](Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());

    std::string size{""};
    switch (state) {
      case State::Init:
        InitCase(bot, message, state);
        break;
      case State::ChooseCar:
        ChangeSC(bot, message, state);
        if (message->text == "Y") {
          ss.str("");
          Car.PrintCarData();
          ss << "\nEnter Car ID to rent";
          bot.getApi().sendMessage(message->chat->id, ss.str());
          state = State::Wait4Carid;
        }
        break;
      case State::Wait4Carid:
        W4CarIdCase(bot, message, state);
        break;
      case State::Wait4Lastname:
        W4LastNameCase(bot, message, state);
        break;
      case State::Wait4Firstname:
        W4FirstNameCase(bot, message, state);
        break;
      case State::Wait4Lisence:
        W4LicenseCase(bot, message, state, size);
        break;
      case State::Wait4Period:
        W4PeriodCase(bot, message, state);
        break;
      case State::CompleteRent:
        W4ComplRentCase(bot, message, state);
        break;
      case State::Wait4completeId:
        W4ComplIdCase(bot, message, state, size);
        break;
      default:
        ErrorData(bot, message);
        state = State::Init;
        break;
    }
  });

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