#include "db.h"
#include "headers.h"

extern stringstream ss;
extern stringstream qq;

void createOneColumnKeyboard(const vector<string> &buttonStrings,
                             ReplyKeyboardMarkup::Ptr &kb) {
  for (size_t i = 0; i < buttonStrings.size(); ++i) {
    vector<KeyboardButton::Ptr> row;
    KeyboardButton::Ptr button(new KeyboardButton);
    button->text = buttonStrings[i];
    row.push_back(button);
    kb->keyboard.push_back(row);
  }
}

void createKeyboard(const vector<vector<string>> &buttonLayout,
                    ReplyKeyboardMarkup::Ptr &kb) {
  for (size_t i = 0; i < buttonLayout.size(); ++i) {
    vector<KeyboardButton::Ptr> row;
    for (size_t j = 0; j < buttonLayout[i].size(); ++j) {
      KeyboardButton::Ptr button(new KeyboardButton);
      button->text = buttonLayout[i][j];
      row.push_back(button);
    }
    kb->keyboard.push_back(row);
  }
}

DB Car;
MenuText menutext;
char *p;
map<int64_t, Client> client_data;
map<int64_t, State> chat_states;

void ErrorData(Bot &bot, Message::Ptr message) {
  bot.getApi().sendMessage(message->chat->id, "Wrong data. Please try again");
}

void ChangeSC(Bot &bot, Message::Ptr message,
              map<int64_t, State> &chat_states) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    chat_states.insert_or_assign(message->chat->id, State::Init);
  } else if (message->text == "About company") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.AboutCompany);
  } else if (message->text == "Conditions") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.conditions);
  } else if (message->text == "Contacts") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.contacts);
  } else if (message->text == "Exit") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.exit);
  } else if (message->text == "Price of available cars") {
    chat_states.insert_or_assign(message->chat->id, State::ChooseCar);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "My rent") {
    chat_states.insert_or_assign(message->chat->id, State::MyRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Complete the rent") {
    chat_states.insert_or_assign(message->chat->id, State::CompleteRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else {
    ErrorData(bot, message);
  }
}
void ChangeSCSpec(Bot &bot, Message::Ptr message,
                  map<int64_t, State> &chat_states) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    chat_states.insert_or_assign(message->chat->id, State::Init);
  }
  if (message->text == "About company") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.AboutCompany);
  }
  if (message->text == "Conditions") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.conditions);
  } else if (message->text == "Contacts") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.contacts);
  }
  if (message->text == "Exit") {
    chat_states.insert_or_assign(message->chat->id, State::Init);
    bot.getApi().sendMessage(message->chat->id, menutext.exit);
  }
  if (message->text == "Price of available cars") {
    chat_states.insert_or_assign(message->chat->id, State::ChooseCar);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
  if (message->text == "My rent") {
    chat_states.insert_or_assign(message->chat->id, State::MyRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
  if (message->text == "Complete the rent") {
    chat_states.insert_or_assign(message->chat->id, State::CompleteRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
}

void InitCase(Bot &bot, Message::Ptr message,
              map<int64_t, State> &chat_states) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
  } else if (message->text == "About company") {
    bot.getApi().sendMessage(message->chat->id, menutext.AboutCompany);
  } else if (message->text == "Conditions") {
    bot.getApi().sendMessage(message->chat->id, menutext.conditions);
  } else if (message->text == "Contacts") {
    bot.getApi().sendMessage(message->chat->id, menutext.contacts);
  } else if (message->text == "Exit") {
    bot.getApi().sendMessage(message->chat->id, menutext.exit);
  } else if (message->text == "My rent") {
    chat_states.insert_or_assign(message->chat->id, State::MyRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Price of available cars") {
    chat_states.insert_or_assign(message->chat->id, State::ChooseCar);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Complete the rent") {
    chat_states.insert_or_assign(message->chat->id, State::CompleteRent);
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
}

void MyRentCase(Bot &bot, Message::Ptr message,
                map<int64_t, State> &chat_states) {
  if (message->text == "Y") {
    bot.getApi().sendMessage(message->chat->id, "Enter License number");
    chat_states.insert_or_assign(message->chat->id, State::RentData);
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

void RentDataCase(Bot &bot, Message::Ptr message, string &size,
                  map<int64_t, State> &chat_states) {
  size = message->text;
  if (size.size() == 10 && strtol(size.c_str(), &p, 10)) {
    qq.str("");
    Car.ClientGetLicenese(message->text);
    if (qq.str() == message->text) {
      ss.str("");
      Car.PrintClientData(message->text);
      bot.getApi().sendMessage(message->chat->id, "Your rent \n" + ss.str());
      chat_states.insert_or_assign(message->chat->id, State::Init);
    } else if (message->text == "Exit") {
      chat_states.insert_or_assign(message->chat->id, State::Init);
      bot.getApi().sendMessage(message->chat->id, menutext.exit);
    } else {
      ChangeSC(bot, message, chat_states);
    }
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

void ChooseCarCase(Bot &bot, Message::Ptr message,
                   map<int64_t, State> &chat_states) {
  if (message->text == "Y") {
    ss.str("");
    Car.PrintCarData();
    ss << "\nEnter Car ID to rent";
    bot.getApi().sendMessage(message->chat->id, ss.str());
    chat_states.insert_or_assign(message->chat->id, State::Wait4Carid);
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

void W4CarIdCase(Bot &bot, Message::Ptr message,
                 map<int64_t, State> &chat_states,
                 map<int64_t, Client> &client_data) {
  if (message->text == "1" || message->text == "2" || message->text == "3" ||
      message->text == "4" || message->text == "5") {
    qq.str("");
    Car.CheckCarReserve(message->text);
    if (qq.str() == "Reserved") {
      bot.getApi().sendMessage(message->chat->id,
                               "Car under ID " + message->text +
                                   " is reserved, please choose another one");
    } else {
      Car.SetCarReserve(message->text);
      client_data[message->chat->id];
      auto temp = client_data.find(message->chat->id);
      if (temp != client_data.end()) {
        temp->second.car_id = message->text;

        qq.str("");
        Car.CarName(message->text);
        temp->second.rented_car = qq.str();

        qq.str("");
        Car.CarPrice(message->text);
        temp->second.sum = stoi(qq.str());
      } else {
        chat_states.insert_or_assign(message->chat->id, State::Init);
      }
      bot.getApi().sendMessage(
          message->chat->id,
          "To rent Car under ID " + message->text + " enter Last Name");
      chat_states.insert_or_assign(message->chat->id, State::Wait4Lastname);
    }
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

void W4LastNameCase(Bot &bot, Message::Ptr message,
                    map<int64_t, State> &chat_states,
                    map<int64_t, Client> &client_data) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    auto id = client_data.find(message->chat->id);
    if (id != client_data.end()) {
      Car.RemoveCarReserve(id->second.car_id);
      client_data.erase(id->first);
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    ChangeSCSpec(bot, message, chat_states);
  } else {
    auto temp = client_data.find(message->chat->id);
    if (temp != client_data.end()) {
      temp->second.last_name = message->text;
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    chat_states.insert_or_assign(message->chat->id, State::Wait4Firstname);
    bot.getApi().sendMessage(message->chat->id, "Enter First Name");
  }
}

void W4FirstNameCase(Bot &bot, Message::Ptr message,
                     map<int64_t, State> &chat_states,
                     map<int64_t, Client> &client_data) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    auto id = client_data.find(message->chat->id);
    if (id != client_data.end()) {
      Car.RemoveCarReserve(id->second.car_id);
      client_data.erase(id->first);
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    ChangeSCSpec(bot, message, chat_states);
  } else {
    auto temp = client_data.find(message->chat->id);
    if (temp != client_data.end()) {
      temp->second.first_name = message->text;
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    chat_states.insert_or_assign(message->chat->id, State::Wait4Lisence);
    bot.getApi().sendMessage(message->chat->id, "Enter License number");
  }
}

void W4LicenseCase(Bot &bot, Message::Ptr message, string &size,
                   map<int64_t, State> &chat_states,
                   map<int64_t, Client> &client_data) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    auto id = client_data.find(message->chat->id);
    if (id != client_data.end()) {
      Car.RemoveCarReserve(id->second.car_id);
      client_data.erase(id->first);
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    ChangeSCSpec(bot, message, chat_states);
  } else {
    size = message->text;
    if (size.size() == 10 && strtol(size.c_str(), &p, 10)) {
      auto temp = client_data.find(message->chat->id);
      if (temp != client_data.end()) {
        temp->second.license = message->text;
      } else {
        chat_states.insert_or_assign(message->chat->id, State::Init);
      }
      bot.getApi().sendMessage(message->chat->id, "Enter rent period in days");
      chat_states.insert_or_assign(message->chat->id, State::Wait4Period);
    } else {
      ErrorData(bot, message);
    }
  }
}

void Time(Message::Ptr message, int &rent_period,
          map<int64_t, Client> &client_data) {
  struct tm ltm;
  time_t now = time(0);
  localtime_s(&ltm, &now);
  qq.str("");
  qq << ltm.tm_mday << "." << ltm.tm_mon + 1 << "." << ltm.tm_year + 1900;
  auto temp = client_data.find(message->chat->id);
  temp->second.since = qq.str();

  now += rent_period * 24 * 3600;
  localtime_s(&ltm, &now);
  qq.str("");
  qq << ltm.tm_mday << "." << ltm.tm_mon + 1 << "." << ltm.tm_year + 1900;
  temp->second.till = qq.str();
}

void W4PeriodCase(Bot &bot, Message::Ptr message,
                  map<int64_t, State> &chat_states,
                  map<int64_t, Client> &client_data) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    auto id = client_data.find(message->chat->id);
    if (id != client_data.end()) {
      Car.RemoveCarReserve(id->second.car_id);
      client_data.erase(id->first);
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    ChangeSCSpec(bot, message, chat_states);
  }
  if (strtol(message->text.c_str(), &p, 10)) {
    auto temp = client_data.find(message->chat->id);
    if (temp != client_data.end()) {
      temp->second.rent_period = stoi(message->text);
      auto sum = temp->second.sum;
      auto period = temp->second.rent_period;
      auto res = sum * period;
      temp->second.sum = res;
      Time(message, period, client_data);

      Car.InsertClientData(temp->second.last_name, temp->second.first_name,
                           temp->second.license, temp->second.car_id,
                           temp->second.rented_car, temp->second.rent_period,
                           temp->second.since, temp->second.till,
                           temp->second.sum);
      ss.str("");
      Car.PrintClientData(temp->second.license);
      bot.getApi().sendMessage(
          message->chat->id,
          "Congratilations! You reserve car.\n Your order: \n" + ss.str() +
              "\n Bon Voyage!");
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
    }
    chat_states.insert_or_assign(message->chat->id, State::Init);
    client_data.erase(temp->first);
  } else {
    ErrorData(bot, message);
  }
}

void W4ComplRentCase(Bot &bot, Message::Ptr message,
                     map<int64_t, State> &chat_states) {
  if (message->text == "Y") {
    bot.getApi().sendMessage(message->chat->id, menutext.complete);
    chat_states.insert_or_assign(message->chat->id, State::Wait4completeId);
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

void W4ComplIdCase(Bot &bot, Message::Ptr message, string &size,
                   map<int64_t, State> &chat_states) {
  size = message->text;
  if (size.size() == 10 && strtol(size.c_str(), &p, 10)) {
    qq.str("");
    Car.ClientGetLicenese(message->text);
    if (qq.str() == message->text) {
      Car.ClientStatus(message->text);
      qq.str("");
      Car.ClientGetCarId(message->text);
      Car.RemoveCarReserve(qq.str());
      ss.str("");
      Car.PrintClientData(message->text);

      bot.getApi().sendMessage(message->chat->id,
                               "Your rent is completed!\n" + ss.str() +
                                   "\n Thank you. Wait you again");
      chat_states.insert_or_assign(message->chat->id, State::Init);
      chat_states.erase(message->chat->id);
    } else {
      ChangeSC(bot, message, chat_states);
    }
  } else {
    ChangeSC(bot, message, chat_states);
  }
}

volatile sig_atomic_t gSignalStatus;

void signal_handler(int signal) { gSignalStatus = signal; }

void startprog(Bot &bot) {
  ReplyKeyboardMarkup::Ptr keyboardOneCol(new ReplyKeyboardMarkup);
  createOneColumnKeyboard({"Price of available cars", "About company", "Exit"},
                          keyboardOneCol);

  ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
  createKeyboard({{"Price of available cars", "About company"},
                  {"Conditions", "Contacts"},
                  {"Complete the rent", "My rent", "Exit"}},
                 keyboardWithLayout);

  bot.getEvents().onCommand(
      "start", [&bot, &keyboardOneCol](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, menutext.start, false, 0,
                                 keyboardOneCol);
        chat_states.insert_or_assign(message->chat->id, State::Init);
      });
  bot.getEvents().onCommand(
      "layout", [&bot, &keyboardWithLayout](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, menutext.layout, false, 0,
                                 keyboardWithLayout);
        chat_states.insert_or_assign(message->chat->id, State::Init);
      });

  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());

    State state;
    auto id = chat_states.find(message->chat->id);
    if (id != chat_states.end()) {
      state = id->second;
    } else {
      chat_states.insert_or_assign(message->chat->id, State::Init);
      state = State::Init;
    }

    string size{""};
    switch (state) {
      case State::Init:
        InitCase(bot, message, chat_states);
        break;
      case State::MyRent:
        MyRentCase(bot, message, chat_states);
        break;
      case State::RentData:
        RentDataCase(bot, message, size, chat_states);
        break;
      case State::ChooseCar:
        ChooseCarCase(bot, message, chat_states);
        break;
      case State::Wait4Carid:
        W4CarIdCase(bot, message, chat_states, client_data);
        break;
      case State::Wait4Lastname:
        W4LastNameCase(bot, message, chat_states, client_data);
        break;
      case State::Wait4Firstname:
        W4FirstNameCase(bot, message, chat_states, client_data);
        break;
      case State::Wait4Lisence:
        W4LicenseCase(bot, message, size, chat_states, client_data);
        break;
      case State::Wait4Period:
        W4PeriodCase(bot, message, chat_states, client_data);
        break;
      case State::CompleteRent:
        W4ComplRentCase(bot, message, chat_states);
        break;
      case State::Wait4completeId:
        W4ComplIdCase(bot, message, size, chat_states);
        break;
      default:
        ErrorData(bot, message);
        chat_states.insert_or_assign(message->chat->id, State::Init);
        break;
    }
  });

  signal(SIGINT, signal_handler);

  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    bot.getApi().deleteWebhook();

    TgLongPoll longPoll(bot);
    while (true) {
      printf("Long poll started\n");
      longPoll.start();
    }
  } catch (exception &e) {
    printf("error: %s\n", e.what());
  }
}