/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
