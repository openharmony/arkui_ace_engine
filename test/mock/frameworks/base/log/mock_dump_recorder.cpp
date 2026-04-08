/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/log/dump_recorder.h"

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(DumpRecorder);

DumpRecorder::DumpRecorder() = default;
DumpRecorder::~DumpRecorder() = default;

void DumpRecorder::Start(std::function<bool()>&& func)
{
    frameDumpFunc_ = std::move(func);
}

void DumpRecorder::Stop()
{
    frameDumpFunc_ = nullptr;
}

void DumpRecorder::StopInner()
{
    frameDumpFunc_ = nullptr;
}

void DumpRecorder::Init() {}
void DumpRecorder::Clear() { records_.clear(); }

void DumpRecorder::Record(int64_t timestamp, std::unique_ptr<JsonValue>&& json)
{
    (void)timestamp;
    (void)json;
}

void DumpRecorder::Diff(int64_t timestamp)
{
    (void)timestamp;
}

bool DumpRecorder::Compare(std::unique_ptr<JsonValue>& prevNode, std::unique_ptr<JsonValue>& curNode, std::string& diff)
{
    (void)prevNode;
    (void)curNode;
    (void)diff;
    return false;
}

bool DumpRecorder::CompareDumpParam(std::unique_ptr<JsonValue>& curParams, std::unique_ptr<JsonValue>& prevParams)
{
    (void)curParams;
    (void)prevParams;
    return false;
}

void DumpRecorder::Output(const std::string& content)
{
    (void)content;
}
} // namespace OHOS::Ace
