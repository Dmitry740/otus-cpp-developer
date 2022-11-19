#include <sqlite3.h>

#include <iomanip>
#include <iostream>
#include <sstream>

struct Client {
  std::string last_name;
  std::string first_name;
  size_t lisence = 0;
  std::string rented_car;
  size_t rent_period;
};

// using query_result_t = std::map<std::string, std::vector<std::string>>;
std::stringstream ss;

int callback(void *data, int argc, char **argv, char **ColName) {
  // query_result_t &result = *reinterpret_cast<query_result_t *>(data);
  for (int i = 0; i < argc; ++i) {
    ss << ColName[i];
    ss << ": ";
    ss << argv[i];
    ss << "\n";
    // result[ColName[i]].emplace_back(argv[i]);
  }
  ss << "\n";
  return 0;
}

class DB {
 private:
  sqlite3 *db;
  char *ErrMsg;
  int rc;
  const char *sql;
  std::string query;

 public:
  DB() {
    rc = sqlite3_open("RentCarDB.db", &db);

    checkDBErr();
  }

  ~DB() { sqlite3_close(db); }

  void CheckReserve(std::string id) {
    query = "SELECT STATUS FROM CAR WHERE ID = " + id;
    sql = query.c_str();
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  }

  void PrintData() {
    // query_result_t result;
    sql = "SELECT *FROM CAR WHERE STATUS = 'Available'";
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    std::cout << ss.str() << std::endl;

    // size_t nrows = 0;
    // for (const auto &col : result) {
    //   std::cout << col.first << "\t|";
    //   nrows = col.second.size();
    // }

    // for (size_t row = 0; row < nrows; ++row) {
    //   for (const auto &col : result) {
    //     std::cout << col.second[row] << "\t|";
    //   }
    // }
    // std::cout << std::endl;
  }

  void checkDBErr() {
    if (rc != SQLITE_OK) {
      std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;

      sqlite3_close(db);
    }
  }

  void CreateCarTable() {
    sql =
        "CREATE TABLE CAR (ID INTEGER PRIMARY KEY AUTOINCREMENT, CAR TEXT NOT "
        "NULL, ENGINE TEXT NOT NULL, GEAR_BOX TEXT NOT NULL, BODY  TEXT NOT "
        "NULL, HORSE_POWER INTEGER NOT NULL, COST_RUB_PER_DAY REAL, STATUS "
        "TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void InsertCarData() {
    sql =
        "INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, "
        "COST_RUB_PER_DAY, STATUS) VALUES('Toyota Camry', 'Gasoline',     "
        "'Automatic', 'Saloon', 181, 3200.00, 'Available'); INSERT INTO CAR "
        "(CAR, ENGINE, GEAR_BOX, BODY, HORSE_POWER, COST_RUB_PER_DAY,      "
        "STATUS) VALUES('Kia Rio', 'Gasoline', 'Automatic', 'Saloon', 125, "
        "2300.00,'Available'); INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, "
        "BODY, HORSE_POWER, COST_RUB_PER_DAY, STATUS) VALUES('BMW M3', "
        "'Disel', "
        "'Automatic','Saloon', 215, 4100.00, 'Available'); INSERT INTO "
        "CAR (CAR, ENGINE, GEAR_BOX, BODY,HORSE_POWER, COST_RUB_PER_DAY, "
        "STATUS) VALUES('Mercedes S-class', 'Disel', 'Automatic', 'Saloon', "
        "315, 6800.00, 'Available'); INSERT INTO CAR (CAR, ENGINE, GEAR_BOX, "
        "BODY, HORSE_POWER, COST_RUB_PER_DAY, STATUS) VALUES('Nissan Note', "
        "'Gasoline', 'Manual', 'Hatchback', 110, 1800.00, 'Available');";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void CreateClientTable() {
    sql =
        "CREATE TABLE CLIENT (ID INTEGER PRIMARY KEY AUTOINCREMENT, LAST_NAME "
        "TEXT NOT NULL, FIRST_NAME TEXT NOT NULL, LICENSE INTEGER NOT "
        "NULL, RENTED_CAR TEXT NOT NULL, RENT_PERIOD_DAYS INTEGER, SUM REAL)";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void InsertClientData() {
    sql =
        "INSERT INTO CLIENT (LAST_NAME, FIRST_NAME, LICENSE_#, RENTED_CAR, "
        "RENT_PERIOD_DAYS) VALUES( , , , , )";

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  }

  void UpdateData(std::string id) {
    query = "UPDATE CAR set STATUS ='Reserved' where ID = " + id;
    sql = query.c_str();
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }

  void DeleteRow(std::string id) {
    query = "DELETE FROM CAR WHERE ID = " + id;
    sql = query.c_str();

    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    checkDBErr();
  }
};