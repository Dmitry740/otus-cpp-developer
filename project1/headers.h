#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")
#include <sqlite3.h>
#include <tgbot/tgbot.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace TgBot;

int callback(void *data, int argc, char **argv, char **ColName);

struct Client {
  string last_name;
  string first_name;
  string license;
  string car_id;
  string rented_car;
  int rent_period = 0;
  int sum = 0;
};

class DB {
 private:
  sqlite3 *db;
  char *ErrMsg;
  int rc;
  const char *sql;
  string query;

 public:
  DB();
  DB(const DB &) = delete;
  DB &operator=(const DB &) = delete;

  DB(DB &&) = delete;

  DB &operator=(DB &&) = delete;

  ~DB();

  void checkDBErr();
  // Car Methods
  void CreateCarTable();
  void InsertCarData();
  void PrintCarData();
  void CheckCarReserve(std::string id);
  void CarName(std::string id);
  void CarPrice(std::string id);
  void SetCarReserve(std::string id);
  void RemoveCarReserve(std::string id);
  void DeleteCarRow(std::string id);
  void DelAllCarRows();
  // Client Methods
  void CreateClientTable();
  void InsertClientData(std::string last_name, std::string first_name,
                        std::string license, std::string car_id,
                        std::string rented_car, int rent_period, int sum);
  void PrintClientData(std::string id);
  void PrintAllClient();
  void ClientStatus(std::string id);
  void ClientGetCarId(std::string id);
  void ClientGetLicenese(std::string id);
  void DeleteClientRow(std::string id);
  void DelAllClientRows();
};

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