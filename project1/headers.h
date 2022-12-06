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

struct MenuText;

struct Client;

enum class State;

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