/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/utils/time_util.h"

namespace OHOS::Ace {
int64_t GetSysTimestamp()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetCurrentTimestampMicroSecond()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetCurrentTimestamp()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetMicroTickCount()
{
    static int64_t tick = 0;
    return ++tick;
}
} // namespace OHOS::Ace
