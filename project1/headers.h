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
#include <ctime>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace TgBot;

int callback(void *data, int argc, char **argv, char **ColName);

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
  void CheckCarReserve(string &id);
  void CarName(string &id);
  void CarPrice(string &id);
  void SetCarReserve(string &id);
  void RemoveCarReserve(string &id);
  void DeleteCarRow(string &id);
  void DelAllCarRows();
  // Client Methods
  void CreateClientTable();
  void InsertClientData(std::string &last_name, std::string &first_name,
                        std::string &license, std::string &car_id,
                        std::string &rented_car, int &rent_period,
                        std::string &since, std::string &till, int &sum);
  void PrintClientData(string &id);
  void PrintAllClient();
  void ClientStatus(string &id);
  void ClientGetCarId(string &id);
  void ClientGetLicenese(string &id);
  void DeleteClientRow(string &id);
  void DelAllClientRows();
};

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