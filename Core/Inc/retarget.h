//
// Created by Lyu on 2023/10/21.
//

#ifndef TEST_RETARGET_H
#define TEST_RETARGET_H
#include "stm32l4xx_hal.h"

#include <sys/stat.h>

#include <stdio.h>

void RetargetInit(UART_HandleTypeDef *huart);

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

int _fstat(int fd, struct stat *st);

#endif //TEST_RETARGET_H
