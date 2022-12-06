#include "db.h"

stringstream ss;
stringstream qq;

int callback(void *data, int argc, char **argv, char **ColName) {
  for (int i = 0; i < argc; ++i) {
    ss << ColName[i];
    ss << ": ";
    ss << argv[i];
    qq << argv[i];
    ss << "\n";
  }
  ss << "\n";
  return 0;
}

DB::DB()
    : filename{
          "C:/Users/Dmitry/Desktop/CPP_home_work/otus-cpp-developer/project1/"
          "RentCarDB.db"} {
  rc = sqlite3_open_v2(
      filename, &db,
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);

  checkDBErr();
}

DB::~DB() { sqlite3_close(db); }

void DB::checkDBErr() {
  if (rc != SQLITE_OK) {
    cout << "DB Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
  }
}

// Car Methods
void DB::CreateCarTable() {
  sql =
      "CREATE TABLE CAR (ID INTEGER PRIMARY KEY AUTOINCREMENT, CAR TEXT NOT "
      "NULL, ENGINE TEXT NOT NULL, GEAR_BOX TEXT NOT NULL, BODY  TEXT NOT "
      "NULL, HORSE_POWER INTEGER NOT NULL, COST_RUB_PER_DAY REAL, STATUS "
      "TEXT NOT NULL);";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::InsertCarData() {
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

void DB::PrintCarData() {
  sql = "SELECT *FROM CAR WHERE STATUS = 'Available'";
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;

  checkDBErr();
}

void DB::CheckCarReserve(string &id) {
  query = "SELECT STATUS FROM CAR WHERE ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << qq.str() << endl;
  checkDBErr();
}

void DB::CarName(string &id) {
  query = "SELECT CAR FROM CAR WHERE ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << qq.str() << endl;

  checkDBErr();
}

void DB::CarPrice(string &id) {
  query = "SELECT COST_RUB_PER_DAY FROM CAR WHERE ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << qq.str() << endl;

  checkDBErr();
}

void DB::SetCarReserve(string &id) {
  query = "UPDATE CAR set STATUS ='Reserved' where ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::RemoveCarReserve(string &id) {
  query = "UPDATE CAR set STATUS ='Available' where ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::DeleteCarRow(string &id) {
  query = "DELETE FROM CAR WHERE ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::DelAllCarRows() {
  sql = "DELETE FROM CAR";
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

// Client Methods
void DB::CreateClientTable() {
  sql =
      "CREATE TABLE CLIENT (ID INTEGER PRIMARY KEY AUTOINCREMENT, LAST_NAME "
      "TEXT NOT NULL, FIRST_NAME TEXT NOT NULL, LICENSE TEXT NOT NULL, "
      "RENTED_CAR_ID TEXT NOT NULL, RENTED_CAR_NAME TEXT NOT NULL, "
      "RENT_PERIOD_DAYS INTEGER, SINCE TEXT NOT NULL, TILL TEXT NOT NULL, SUM  "
      "REAL, STATUS TEXT NOT NULL)";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::InsertClientData(std::string &last_name, std::string &first_name,
                          std::string &license, std::string &car_id,
                          std::string &rented_car, int &rent_period,
                          std::string &since, std::string &till, int &sum) {
  query =
      "INSERT INTO CLIENT (LAST_NAME, FIRST_NAME, LICENSE, RENTED_CAR_ID, "
      "RENTED_CAR_NAME, RENT_PERIOD_DAYS, SINCE, TILL, SUM, STATUS) VALUES( '" +
      last_name + "', '" + first_name + "', '" + license + "', '" + car_id +
      "', '" + rented_car + "', '" + to_string(rent_period) + "', '" + since +
      "', '" + till + "', '" + to_string(sum) + "', " + "'In Rent');";

  sql = query.c_str();
  cout << sql << endl;
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::PrintClientData(string &id) {
  query = "SELECT *FROM CLIENT WHERE LICENSE = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;

  checkDBErr();
}

void DB::PrintAllClient() {
  sql = "SELECT *FROM CLIENT";
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;

  checkDBErr();
}

void DB::ClientStatus(string &id) {
  query = "UPDATE CLIENT set STATUS ='Rent is completed' where LICENSE = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ClientGetCarId(string &id) {
  query = "SELECT RENTED_CAR_ID FROM CLIENT WHERE LICENSE = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ClientGetLicenese(string &id) {
  query = "SELECT LICENSE FROM CLIENT WHERE LICENSE = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::DeleteClientRow(string &id) {
  query = "DELETE FROM CLIENT WHERE ID = " + id;
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::DelAllClientRows() {
  sql = "DELETE FROM CLIENT";
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}
