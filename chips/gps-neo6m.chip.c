// For information and examples see:
// https://link.wokwi.com/custom-chips-alpha
//
// SPDX-License-Identifier: MIT
// Copyright (C) 2022 Uri Shaked / wokwi.com

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    

#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))    
#define SECOND 1000000    
#define SENTENCES_COUNT 3

const char gps_tx_data[][80] = {
  "$GPGGA,172914.00,0756.5500,S,11236.9360,E,1,08,1.0,450.0,M,0.0,M,,*4E\r\n",
  "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
  "$GPRMC,172914.00,A,0756.5500,S,11236.9360,E,005.2,180.0,280526,000.0,E*47\r\n",

  "$GPGGA,172915.00,0756.5550,S,11236.9365,E,1,08,1.0,450.0,M,0.0,M,,*4F\r\n",
  "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
  "$GPRMC,172915.00,A,0756.5550,S,11236.9365,E,005.2,180.0,280526,000.0,E*46\r\n",

  "$GPGGA,172916.00,0756.5600,S,11236.9370,E,1,08,1.0,450.0,M,0.0,M,,*4E\r\n",
  "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
  "$GPRMC,172916.00,A,0756.5600,S,11236.9370,E,005.2,180.0,280526,000.0,E*47\r\n",

  "$GPGGA,172917.00,0756.5650,S,11236.9375,E,1,08,1.0,450.0,M,0.0,M,,*4F\r\n",
  "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
  "$GPRMC,172917.00,A,0756.5650,S,11236.9375,E,005.2,180.0,280526,000.0,E*46\r\n"
};

typedef struct {
  uart_dev_t uart0;
  uint32_t   gps_tx_index;
} chip_state_t;

static void chip_timer_event(void *user_data);

void chip_init(void) {
  setvbuf(stdout, NULL, _IOLBF, 1024);     

  chip_state_t *chip = malloc(sizeof(chip_state_t));

  const uart_config_t uart_config = {
    .tx         = pin_init("TX", INPUT_PULLUP),
    .rx         = pin_init("RX", INPUT),
    .baud_rate  = 9600,
    .user_data  = chip,
  };

  chip->uart0        = uart_init(&uart_config);
  chip->gps_tx_index = 0;

  const timer_config_t timer_config = {
    .callback  = chip_timer_event,
    .user_data = chip,
  };

  timer_t timer = timer_init(&timer_config);
  timer_start(timer, SECOND, true);

  printf("GPS Chip initialized!\n");     
}

void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*) user_data;

  for (int i = 0; i < SENTENCES_COUNT; i++) {
    const char * message = gps_tx_data[chip->gps_tx_index++];
    uart_write(chip->uart0, (uint8_t *) message, strlen(message));

    if (chip->gps_tx_index >= LEN(gps_tx_data)) {       
      chip->gps_tx_index = 0;
    }
  }
}