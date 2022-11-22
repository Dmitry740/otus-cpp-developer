#include <iostream>

#include "headers.h"

int main() {
  Bot bot("TOKEN");

  startprog(bot);

  signal(SIGINT, [](int s) {
    printf("SIGINT got\n");
    exit(0);
  });

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

  return 0;
}