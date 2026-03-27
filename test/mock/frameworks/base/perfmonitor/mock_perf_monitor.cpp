/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/perfmonitor/perf_monitor.h"

namespace OHOS::Ace {
PerfMonitor* PerfMonitor::pMonitor = nullptr;
std::once_flag PerfMonitor::initFlag;

PerfMonitor* PerfMonitor::GetPerfMonitor()
{
    static PerfMonitor monitor;
    return &monitor;
}

void PerfMonitor::SetSubHealthInfo(const std::string& info, const std::string& reason, const int32_t duration)
{
    (void)info;
    (void)reason;
    (void)duration;
}

void PerfMonitor::SetAppForeground(bool isShow)
{
    (void)isShow;
}
} // namespace OHOS::Ace
