#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#include <tgbot/tgbot.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <map>
#include <vector>

using namespace std;
using namespace TgBot;

struct MenuText {
  const string start =
      "Hi, i'm a rentCar Chatbot and i help you to choose car\n/start for one "
      "column keyboard\n/layout for a more complex keyboard";
  const string layout =
      "/start for one column keyboard\n/layout for a more complex keyboard";
  const string AboutCompany = "Simply - WE ARE THE BEST!!!";
  const string conditions =
      "Give us your pasport, credit card and keys from flat, after that we "
      "give you car:)";
  const string contacts =
      "Adress: Russia, Moscow, red square, 7\n ph.: 777-77-77\n web: "
      "/www.rentcar.ru";
  const string complete =
      "For compleating your rent please enter Lisence number";
  const string exit = "Thank you for your visit! Wait you again";
};

struct Client {
  string last_name;
  string first_name;
  string license;
  string car_id;
  string rented_car;
  int rent_period = 0;
  string since;
  string till;
  int sum = 0;
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
  Wait4completeId,
  MyRent,
  RentData
};

void Time(Message::Ptr message, int &rent_period,
          map<int64_t, Client> &client_data);

void createOneColumnKeyboard(const vector<string> &buttonStrings,
                             ReplyKeyboardMarkup::Ptr &kb);

void createKeyboard(const vector<vector<string>> &buttonLayout,
                    ReplyKeyboardMarkup::Ptr &kb);

void startprog(Bot &bot);

void ErrorData(Bot &bot, Message::Ptr message);

void ChangeSC(Bot &bot, Message::Ptr message, map<int64_t, State> &chat_states);

void ChangeSCSpec(Bot &bot, Message::Ptr message,
                  map<int64_t, State> &chat_states);

void InitCase(Bot &bot, Message::Ptr message, map<int64_t, State> &chat_states);

void MyRentCase(Bot &bot, Message::Ptr message,
                map<int64_t, State> &chat_states);

void RentDataCase(Bot &bot, Message::Ptr message, string &size,
                  map<int64_t, State> &chat_states);

void ChooseCarCase(Bot &bot, Message::Ptr message,
                   map<int64_t, State> &chat_states);

void W4CarIdCase(Bot &bot, Message::Ptr message,
                 map<int64_t, State> &chat_states,
                 map<int64_t, Client> &client_data);

void W4LastNameCase(Bot &bot, Message::Ptr message,
                    map<int64_t, State> &chat_states,
                    map<int64_t, Client> &client_data);

void W4FirstNameCase(Bot &bot, Message::Ptr message,
                     map<int64_t, State> &chat_states,
                     map<int64_t, Client> &client_data);

void W4LicenseCase(Bot &bot, Message::Ptr message, string &size,
                   map<int64_t, State> &chat_states,
                   map<int64_t, Client> &client_data);

void Time(Message::Ptr message, int &rent_period,
          map<int64_t, Client> &client_data);

void W4PeriodCase(Bot &bot, Message::Ptr message,
                  map<int64_t, State> &chat_states,
                  map<int64_t, Client> &client_data);

void W4ComplRentCase(Bot &bot, Message::Ptr message,
                     map<int64_t, State> &chat_states);

void W4ComplIdCase(Bot &bot, Message::Ptr message, string &size,
                   map<int64_t, State> &chat_states);