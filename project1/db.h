#pragma once

#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include <sqlite3.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int callback(void *data, int argc, char **argv, char **ColName);

class DB {
 private:
  sqlite3 *db;
  char *ErrMsg;
  int rc;
  const char *sql;
  string query;
  const char *filename;

 public:
  DB();
  DB(const DB &) = delete;
  DB &operator=(const DB &) = delete;

  DB(DB &&other) noexcept {
    db = other.db;
    other.db = nullptr;
    ErrMsg = other.ErrMsg;
    other.ErrMsg = nullptr;
    rc = other.rc;
    other.rc = 0;
    sql = other.sql;
    other.sql = nullptr;
    query = other.query;
    other.query = nullptr;
    filename = other.filename;
    other.filename = nullptr;
  }

  DB &operator=(DB &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    db = rhs.db;
    rhs.db = nullptr;
    ErrMsg = rhs.ErrMsg;
    rhs.ErrMsg = nullptr;
    rc = rhs.rc;
    rhs.rc = 0;
    sql = rhs.sql;
    rhs.sql = nullptr;
    query = rhs.query;
    rhs.query = nullptr;
    filename = rhs.filename;
    rhs.filename = nullptr;

    return *this;
  }

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
