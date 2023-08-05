/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_FRAME_TRACE_ADAPTER_H
#define FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_FRAME_TRACE_ADAPTER_H
#include "gmock/gmock.h"

#include "base/thread/frame_trace_adapter.h"

namespace OHOS::Ace {
class MockFrameTraceAdapter : public FrameTraceAdapter {
public:
    MockFrameTraceAdapter() = default;
    ~MockFrameTraceAdapter() override = default;

    MOCK_METHOD1(QuickExecute, void(std::function<void()>&& func));
    MOCK_METHOD1(SlowExecute, void(std::function<void()>&& func));
    MOCK_METHOD1(EnableFrameTrace, bool(const std::string& traceTag));
    MOCK_METHOD0(IsEnabled, bool());
    MOCK_METHOD0(SetFrameTraceLimit, void());
};
}
#endif
