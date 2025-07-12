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
#ifndef FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_JUNK_FRAME_H
#define FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_JUNK_FRAME_H

#include <optional>
#include <set>
#include <string>
#include <vector>

#include "base/perfmonitor/perf_monitor.h"

namespace OHOS::Ace {
class PerfMonitorTestHolder {
public:
    PerfMonitorTestHolder() = default;
    ~PerfMonitorTestHolder() = default;
    static PerfMonitorTestHolder* GetInstance()
    {
        static PerfMonitorTestHolder instance;
        return &instance;
    }
    void SetUp()
    {
        isCalled = false;
        actionType = std::nullopt;
        sourceType = std::nullopt;
        scene = std::nullopt;
        note = std::nullopt;
        time = std::nullopt;
        isJsApi = std::nullopt;
    }
    void TearDown()
    {
        isCalled = false;
    }

    bool isCalled = false;
    std::optional<PerfActionType> actionType = std::nullopt;
    std::optional<PerfSourceType> sourceType = std::nullopt;
    std::optional<std::string> scene = std::nullopt;
    std::optional<std::string> note = std::nullopt;
    std::optional<int64_t> time = std::nullopt;
    std::optional<bool> isJsApi = std::nullopt;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_JUNK_FRAME_H
