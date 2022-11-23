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

void rent(Bot &bot);

void CompleteCarRent(Bot &bot);

void startprog(Bot &bot);
