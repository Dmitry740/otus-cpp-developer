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

struct MenuText {
  const string AboutCompany = "Simply - WE ARE THE BEST!!!";
  const string conditions =
      "Give us your pasport, credit card and keys from flat, after that we "
      "give you car:)";
  const string contacts =
      "Adress: Russia, Moscow, red square, 7\n ph.: 777-77-77\n web: "
      "/www.rentcar.ru";
  const string complete =
      "For compleating your rent please enter Lisence number";
  const string exit = "Thank you for your visit! Wait you again";
};

enum class State {
  Init,
  ChooseCar,
  Wait4Firstname,
  Wait4Lastname,
  Wait4Lisence,
  Wait4Carid,
  Wait4Period,
  CompleteRent,
  Wait4completeId,
  MyRent,
  RentData
};

DB Car;
Client client;
MenuText menutext;
State state;

void ErrorData(Bot &bot, Message::Ptr message) {
  bot.getApi().sendMessage(message->chat->id, "Wrong data. Please try again");
}

void ChangeSC(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout")) {
    state = State::Init;
  } else if (message->text == "About company") {
    state = State::Init;
    bot.getApi().sendMessage(message->chat->id, menutext.AboutCompany);
  } else if (message->text == "Conditions") {
    state = State::Init;
    bot.getApi().sendMessage(message->chat->id, menutext.conditions);
  } else if (message->text == "Contacts") {
    state = State::Init;
    bot.getApi().sendMessage(message->chat->id, menutext.contacts);
  } else if (message->text == "Exit") {
    state = State::Init;
    bot.getApi().sendMessage(message->chat->id, menutext.exit);
  } else if (message->text == "Price of available cars") {
    state = State::ChooseCar;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "My rent") {
    state = State::MyRent;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Complete the rent") {
    state = State::CompleteRent;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else {
    ErrorData(bot, message);
  }
}

void InitCase(Bot &bot, Message::Ptr message, State &state) {
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
    return;
  } else if (message->text == "My rent") {
    state = State::MyRent;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Price of available cars") {
    state = State::ChooseCar;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  } else if (message->text == "Complete the rent") {
    state = State::CompleteRent;
    bot.getApi().sendMessage(message->chat->id,
                             "To confirm your choose enter \"Y\"");
  }
}

void MyRentCase(Bot &bot, Message::Ptr message, State &state) {
  if (message->text == "Y") {
    bot.getApi().sendMessage(message->chat->id, "Enter License number");
    state = State::RentData;
  } else {
    ChangeSC(bot, message, state);
  }
}

void RentDataCase(Bot &bot, Message::Ptr message, State &state, string &size) {
  size = message->text;
  char *p;
  if ((size.size() == 10) & strtol(size.c_str(), &p, 10)) {
    qq.str("");
    Car.ClientGetLicenese(message->text);
    if (qq.str() == message->text) {
      ss.str("");
      Car.PrintClientData(message->text);
      bot.getApi().sendMessage(message->chat->id, "Your rent \n" + ss.str());
      state = State::Init;
    } else if (message->text == "Exit") {
      state = State::Init;
      bot.getApi().sendMessage(message->chat->id, menutext.exit);
    } else {
      ChangeSC(bot, message, state);
    }
  } else {
    ChangeSC(bot, message, state);
  }
}

void ChooseCarCase(Bot &bot, Message::Ptr message, State &state) {
  if (message->text == "Y") {
    ss.str("");
    Car.PrintCarData();
    ss << "\nEnter Car ID to rent";
    bot.getApi().sendMessage(message->chat->id, ss.str());
    state = State::Wait4Carid;
  } else {
    ChangeSC(bot, message, state);
  }
}

void W4CarIdCase(Bot &bot, Message::Ptr message, State &state) {
  if (message->text == "1" || message->text == "2" || message->text == "3" ||
      message->text == "4" || message->text == "5") {
    qq.str("");
    Car.CheckCarReserve(message->text);
    if (qq.str() == "Reserved") {
      bot.getApi().sendMessage(message->chat->id,
                               "Car under ID " + message->text +
                                   " is reserved, please choose another one");
    }
    Car.SetCarReserve(message->text);
    client.car_id = message->text;
    qq.str("");
    Car.CarName(message->text);
    client.rented_car = qq.str();
    qq.str("");
    Car.CarPrice(message->text);
    client.sum = stoi(qq.str());

    bot.getApi().sendMessage(
        message->chat->id,
        "To rent Car under ID " + message->text + " enter Last Name");
    state = State::Wait4Lastname;
  } else {
    ChangeSC(bot, message, state);
  }
}

void W4LastNameCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    client.last_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter First Name");
    state = State::Wait4Firstname;
  }
}

void W4FirstNameCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    client.first_name = message->text;
    bot.getApi().sendMessage(message->chat->id, "Enter License number");
    state = State::Wait4Lisence;
  }
}

void W4LicenseCase(Bot &bot, Message::Ptr message, State &state, string &size) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  } else {
    size = message->text;
    char *p;
    if ((size.size() == 10) & strtol(size.c_str(), &p, 10)) {
      client.license = message->text;
      bot.getApi().sendMessage(message->chat->id, "Enter rent period in days");
      state = State::Wait4Period;
    } else {
      ErrorData(bot, message);
    }
  }
}

void W4PeriodCase(Bot &bot, Message::Ptr message, State &state) {
  if (StringTools::startsWith(message->text, "/start") ||
      StringTools::startsWith(message->text, "/layout") ||
      message->text == "About company" || message->text == "Conditions" ||
      message->text == "Contacts" || message->text == "Exit" ||
      message->text == "Price of available cars" ||
      message->text == "Complete the rent" || message->text == "My rent") {
    state = State::Init;
    Car.RemoveCarReserve(client.car_id);
    bot.getApi().sendMessage(message->chat->id, "Try again");
  }
  char *p;
  if (strtol(message->text.c_str(), &p, 10)) {
    client.rent_period = stoi(message->text);
    client.sum *= client.rent_period;
    Car.InsertClientData(client.last_name, client.first_name, client.license,
                         client.car_id, client.rented_car, client.rent_period,
                         client.sum);
    ss.str("");
    Car.PrintClientData(client.license);
    bot.getApi().sendMessage(
        message->chat->id,
        "Congratilations! You reserve car.\n Your order: \n" + ss.str() +
            "\n Bon Voyage!");
    state = State::Init;
  } else {
    ErrorData(bot, message);
  }
}

void W4ComplRentCase(Bot &bot, Message::Ptr message, State &state) {
  if (message->text == "Y") {
    bot.getApi().sendMessage(message->chat->id, menutext.complete);
    state = State::Wait4completeId;
  } else {
    ChangeSC(bot, message, state);
  }
}

void W4ComplIdCase(Bot &bot, Message::Ptr message, State &state, string &size) {
  size = message->text;
  char *p;
  if ((size.size() == 10) & strtol(size.c_str(), &p, 10)) {
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
      state = State::Init;
    } else {
      ChangeSC(bot, message, state);
    }
  } else {
    ChangeSC(bot, message, state);
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
        bot.getApi().sendMessage(
            message->chat->id,
            "Hi, i'm a rentCar Chatbot and i help you to choose car\n/start "
            "for one column keyboard\n/layout for a more complex keyboard",
            false, 0, keyboardOneCol);
      });
  bot.getEvents().onCommand("layout", [&bot, &keyboardWithLayout](
                                          Message::Ptr message) {
    bot.getApi().sendMessage(
        message->chat->id,
        "/start for one column keyboard\n/layout for a more complex keyboard",
        false, 0, keyboardWithLayout);
  });

  State state = State::Init;

  bot.getEvents().onAnyMessage([&bot, &state](Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());

    string size{""};
    switch (state) {
      case State::Init:
        InitCase(bot, message, state);
        break;
      case State::MyRent:
        MyRentCase(bot, message, state);
        break;
      case State::RentData:
        RentDataCase(bot, message, state, size);
        break;
      case State::ChooseCar:
        ChooseCarCase(bot, message, state);
        break;
      case State::Wait4Carid:
        W4CarIdCase(bot, message, state);
        break;
      case State::Wait4Lastname:
        W4LastNameCase(bot, message, state);
        break;
      case State::Wait4Firstname:
        W4FirstNameCase(bot, message, state);
        break;
      case State::Wait4Lisence:
        W4LicenseCase(bot, message, state, size);
        break;
      case State::Wait4Period:
        W4PeriodCase(bot, message, state);
        break;
      case State::CompleteRent:
        W4ComplRentCase(bot, message, state);
        break;
      case State::Wait4completeId:
        W4ComplIdCase(bot, message, state, size);
        break;
      default:
        ErrorData(bot, message);
        state = State::Init;
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