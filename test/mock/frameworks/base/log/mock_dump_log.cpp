/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/log/dump_log.h"

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(DumpLog);

DumpLog::DumpLog() = default;
DumpLog::~DumpLog() = default;

void DumpLog::Print(const std::string& content)
{
    (void)content;
}

void DumpLog::Print(int32_t depth, const std::string& content)
{
    (void)depth;
    (void)content;
}

bool DumpLog::OutPutBySize()
{
    return true;
}

void DumpLog::OutPutDefault() {}
void DumpLog::OutPutByCompress() {}

void DumpLog::PrintEndDumpInfoNG(bool isElement)
{
    (void)isElement;
}
} // namespace OHOS::Ace
