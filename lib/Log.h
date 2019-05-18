//
// Created by Andrey on 19.04.2019.
//

#ifndef HYDROLIB2_LOG_H
#define HYDROLIB2_LOG_H

#include <stdio.h>

#define  LOGE(...)  printf(__VA_ARGS__)
#define  LOGW(...)  printf(__VA_ARGS__)
#define  LOGD(...)  printf(__VA_ARGS__)
#define  LOGS(...)  printf(__VA_ARGS__)
#define  LOGI(...)  printf(__VA_ARGS__)

class Log {
public:
    static void dump(const void *aData, int aSize);
};
#endif //HYDROLIB2_LOG_H
