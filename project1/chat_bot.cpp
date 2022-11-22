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

static DB Car;
Client client;

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
  const std::string Complete = "For compleating yor rent please enter Car ID ";
};

void rent(Bot &bot) {
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
  });

  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
    client.last_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter First Name");
  });
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
    client.first_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter Lisence number");
  });
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
    client.lisence = stoi(message->text);
    bot.getApi().sendMessage(message->chat->id, "Enter rent period in days");
  });
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
    client.rent_period = stoi(message->text);
    client.sum *= client.rent_period;
    Car.InsertClientData(client.last_name, client.first_name, client.lisence,
                         client.rented_car, client.rent_period, client.sum);
    ss.clear();
    Car.PrintClientData(std::to_string(client.lisence));
    bot.getApi().sendMessage(
        message->chat->id, "Congratilations! You reserve car.\n Your order: " +
                               ss.str() + "\n Bon Voyage!");
    return;
  });
}

void CompleteCarRent(Bot &bot) {
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text);
    Car.ClientStatus(message->text);
    bot.getApi().sendMessage(message->chat->id,
                             "Yor rent ID " + message->text +
                                 " is completed! Thank you. Wait you again");
    return;
  });
}

void startprog(Bot &bot) {
  static MenuText menutext;

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
            "Hi, i'm a rentCar Chatbot and i help you to choose car\n /start "
            "for one "
            "column keyboard\n/layout for a more complex keyboard",
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
    if (StringTools::startsWith(message->text, "/start") ||
        StringTools::startsWith(message->text, "/layout")) {
      return;
    }
    if (message->text == "Price of available cars") {
      ss.clear();
      Car.PrintCarData();
      ss << "\nEnter Car ID to rent";
      bot.getApi().sendMessage(message->chat->id, ss.str());
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
    if (message->text == "Complete the rent") {
      bot.getApi().sendMessage(message->chat->id, menutext.Complete);
      CompleteCarRent(bot);
    }
    if (message->text == "1" || message->text == "2" || message->text == "3" ||
        message->text == "4" || message->text == "5") {
      qq.clear();
      Car.CheckCarReserve(message->text);
      if (qq.str() == "Reserved") {
        bot.getApi().sendMessage(message->chat->id,
                                 "Car under ID " + message->text +
                                     " is reserved, please choose another one");
        return;
      }
      Car.SetCarReserve(message->text);
      qq.clear();
      Car.CarName(message->text);
      client.rented_car = qq.str();
      qq.clear();
      Car.CarPrice(message->text);
      client.sum = stoi(qq.str());

      bot.getApi().sendMessage(
          message->chat->id,
          "To rent Car under ID " + message->text + " enter Last Name");
    }

    if (message->text == "Exit") {
      bot.getApi().sendMessage(message->chat->id,
                               "Thank you for your visit! Wait you again");
      return;
    }
  });
}