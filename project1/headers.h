#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")
#include <tgbot/tgbot.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace TgBot;

void createOneColumnKeyboard(const vector<string> &buttonStrings,
                             ReplyKeyboardMarkup::Ptr &kb);

void createKeyboard(const vector<vector<string>> &buttonLayout,
                    ReplyKeyboardMarkup::Ptr &kb);

struct MenuText;

enum class State;

void startprog(Bot &bot);

void ErrorData(Bot &bot, Message::Ptr message);

void ChangeSC(Bot &bot, Message::Ptr message, State &state);

void InitCase(Bot &bot, Message::Ptr message, State &state);

void ChooseCarCase(Bot &bot, Message::Ptr message, State &state);

void W4CarIdCase(Bot &bot, Message::Ptr message, State &state);

void W4LastNameCase(Bot &bot, Message::Ptr message, State &state);

void W4FirstNameCase(Bot &bot, Message::Ptr message, State &state);

void W4LicenseCase(Bot &bot, Message::Ptr message, State &state,
                   std::string &size);
void W4PeriodCase(Bot &bot, Message::Ptr message, State &state);

void W4ComplIdCase(Bot &bot, Message::Ptr message, State &state,
                   std::string &size);
void W4ComplRentCase(Bot &bot, Message::Ptr message, State &state);
