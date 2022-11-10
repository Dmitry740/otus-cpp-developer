#include <sqlite3.h>

#include <iostream>

class DB {
 private:
  sqlite3 *db;
  char *ErrMsg;
  int rc;
  char *sql;
  const char *sql3;
  std::string query;

  static int callback(void *Notused, int argc, char **argv, char **ColName) {
    for (int i = 0; i < argc; ++i) {
      std::cout << ColName[i] << ": " << argv[i] << std::endl;
    }

    std::cout << std::endl;

    return 0;
  }

  void checkDBErr() {
    if (rc != SQLITE_OK) {
      std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;

      sqlite3_close(db);
    }
  }

 public:
  DB() {
    rc = sqlite3_open("RentCarDB.db", &db);

    checkDBErr();
  }

  ~DB() { sqlite3_close(db); }

  void CreateCarTable() {
    sql =
        "CREATE TABLE CAR (ID INTEGER PRIMARY KEY AUTOINCREMENT, CAR TEXT NOT "
        "NULL, ENGINE TEXT NOT NULL, GEAR_BOX TEXT NOT NULL, BODY TEXT NOT "
        "NULL, HORSE_POWER INTEGER NOT NULL, COST_RUB_PER_DAY REAL, STATUS "
        "TEXT "
        "NOT NULL);";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void InsertCarData() {
    sql =
        "INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, "
        "COST_RUB_PER_DAY, STATUS) VALUES('Toyota Camry', 'Gasoline',  "
        "'Automatic', 'Saloon', 181, 3200.00, 'Available'); INSERT INTO CAR "
        "(CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, COST_RUB_PER_DAY, STATUS) "
        "VALUES('Kia Rio', 'Gasoline', 'Automatic', 'Saloon', 125, 2300.00, "
        "'Available'); "
        "INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, "
        "COST_RUB_PER_DAY, STATUS) VALUES('BMW M3', 'Disel', 'Automatic', "
        "'Saloon', "
        "215, "
        "4100.00, 'Available'); INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, BODY, "
        "HORSE_POWER, COST_RUB_PER_DAY, STATUS) VALUES('Mercedes S-class', "
        "'Disel',  "
        "'Automatic', 'Saloon', 315, 6800.00, 'Available'); INSERT INTO CAR "
        "(CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, COST_RUB_PER_DAY, STATUS) "
        "VALUES('Nissan Note', 'Gasoline', 'Manual', 'Hatchback', 110, "
        "1800.00, "
        "'Available')";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void CreateClientTable() {
    sql =
        "CREATE TABLE CLIENT (ID INTEGER PRIMARY KEY AUTOINCREMENT, LAST_NAME "
        "TEXT NOT NULL, FIRST_NAME TEXT NOT NULL, LICENSE_# INTEGER NOT NULL, "
        "RENTED_CAR INEGER, RENT_PERIOD_DAYS INTEGER);";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void InsertClientData() {
    sql =
        "INSERT INTO CLIENT (LAST_NAME, FIRST_NAME, LICENSE_#, RENTED_CAR, "
        "RENT_PERIOD_DAYS) VALUES( , , , , )";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  }

  void ShowTable() {
    sql = "SELECT *FROM CAR WHERE STATUS = 'Available'";
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  }

  void UpdateData() {
    sql = "UPDATE CAR set STATUS ='Reserved' where ID = 3";
    // query.replace(25, 8, text);
    // std::string sum = query + id;

    // sql3 = sum.c_str();
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void DeleteRow(std::string id) {
    query = "DELETE FROM CAR WHERE ID = ";
    std::string sum = query + id;
    sql3 = sum.c_str();

    rc = sqlite3_exec(db, sql3, callback, 0, &ErrMsg);

    checkDBErr();
  }
};