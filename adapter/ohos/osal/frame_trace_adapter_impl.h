/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_FRAME_TRACE_ADAPTER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_FRAME_TRACE_ADAPTER_IMPL_H

#include <functional>
#include "base/thread/frame_trace_adapter.h"

namespace OHOS::Ace {
class FrameTraceAdapterImpl : public FrameTraceAdapter {
public:
    FrameTraceAdapterImpl() = default;
    ~FrameTraceAdapterImpl() override = default;
    void QuickExecute(std::function<void()>&& func) override;
    void SlowExecute(std::function<void()>&& func) override;
    bool EnableFrameTrace(const std::string& traceTag) override;
    bool IsEnabled() override;
    void SetFrameTraceLimit() override;

private:
    bool AccessFrameTrace();
};

class FrameTraceAdapterFakeImpl : public FrameTraceAdapter {
public:
    FrameTraceAdapterFakeImpl() = default;
    ~FrameTraceAdapterFakeImpl() override = default;
    void QuickExecute(std::function<void()>&& func) override;
    void SlowExecute(std::function<void()>&& func) override;
    bool EnableFrameTrace(const std::string& traceTag) override;
    bool IsEnabled() override;
};
}
#endif

