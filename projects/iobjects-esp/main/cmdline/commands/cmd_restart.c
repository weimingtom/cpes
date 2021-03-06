/******************************************************************************
 * @copyright Copyright (c) A1 Company LLC. All rights reserved.
 *****************************************************************************/

#include "headers.h"

static int restart(int argc, char** argv)
{
  puts("Restarting");
  esp_restart();
}

void cmd_restart()
{
  const esp_console_cmd_t cmd =
  {
    .command = "restart",
    .help = "Restart ESP",
    .hint = NULL,
    .func = &restart,
  };
  ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

/*****************************************************************************/
