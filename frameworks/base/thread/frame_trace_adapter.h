/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_THREAD_FRAME_TRACE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_THREAD_FRAME_TRACE_IMPL_H

#include <functional>
#include <string>

namespace OHOS::Ace {
class FrameTraceAdapter {
public:
    FrameTraceAdapter() = default;
    virtual ~FrameTraceAdapter() = default;
    static FrameTraceAdapter* GetInstance();
    virtual void QuickExecute(std::function<void()> && func) {}
    virtual void SlowExecute(std::function<void()> && func) {}
    virtual bool EnableFrameTrace(const std::string &traceTag)
    {
        return false;
    }
    virtual bool IsEnabled()
    {
        return false;
    }
    virtual void SetFrameTraceLimit() {}
};
}
#endif
