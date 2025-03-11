/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_DUMP_RECORDER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_DUMP_RECORDER_H

#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "base/utils/singleton.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
class DumpRecorder : public Singleton<DumpRecorder> {
    DECLARE_SINGLETON(DumpRecorder);

public:
    void Start(std::function<bool()>&& func);

    void Stop();

    void StopInner();

    void Init();

    void Clear();

    std::function<bool()> GetFrameDumpFunc() const
    {
        return frameDumpFunc_;
    }

    bool IsRecording() const
    {
        return frameDumpFunc_ != nullptr;
    }

    void Record(int64_t timestamp, std::unique_ptr<JsonValue>&& json);

    void Diff(int64_t timestamp);

    bool Compare(std::unique_ptr<JsonValue>& prevNode, std::unique_ptr<JsonValue>& curNode, std::string& diff);

    bool CompareDumpParam(std::unique_ptr<JsonValue>& curParams, std::unique_ptr<JsonValue>& prevParams);

    void Output(const std::string& content);

private:
    std::function<bool()> frameDumpFunc_;
    std::unique_ptr<JsonValue> recordTree_;
    std::map<int64_t, std::unique_ptr<JsonValue>> records_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_DUMP_RECORDER_H