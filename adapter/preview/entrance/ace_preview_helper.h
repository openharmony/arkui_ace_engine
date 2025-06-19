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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_PREVIEW_HELPER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_PREVIEW_HELPER_H

#include <functional>
#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace::Platform {
using CallbackTypeIsCurrentRunnerThread = std::function<bool(void)>;
using CallbackTypePostTask = std::function<void(const std::function<void()>&, int64_t)>;
using CallbackTypeHspBufferTracker = std::function<bool(const std::string&, bool, uint8_t**, size_t*, std::string&)>;
using CallbackTypeSetClipboardData = std::function<void(const std::string&)>;
using CallbackTypeGetClipboardData = std::function<const std::string(void)>;
using CallbackFlushEmpty = std::function<bool(const uint64_t)>;
class ACE_FORCE_EXPORT AcePreviewHelper {
public:
    static AcePreviewHelper* GetInstance();
    ~AcePreviewHelper() = default;

    void SetCallbackFlushEmpty(const CallbackFlushEmpty&& flushEmpty)
    {
        flushEmpty_ =  flushEmpty;
    }

    CallbackFlushEmpty GetCallbackFlushEmpty()
    {
        return flushEmpty_;
    }

    void SetCallbackOfPostTask(const CallbackTypePostTask&& postTask)
    {
        postTask_ = postTask;
    }

    CallbackTypePostTask GetCallbackOfPostTask()
    {
        return postTask_;
    }

    void SetCallbackOfIsCurrentRunnerThread(const CallbackTypeIsCurrentRunnerThread&& isCurrentRunnerThread)
    {
        isCurrentRunnerThread_ = isCurrentRunnerThread;
    }

    CallbackTypeIsCurrentRunnerThread GetCallbackOfIsCurrentRunnerThread()
    {
        return isCurrentRunnerThread_;
    }

    void SetCallbackOfHspBufferTracker(const CallbackTypeHspBufferTracker&& hspBufferTracker)
    {
        hspBufferTracker_ = hspBufferTracker;
    }

    CallbackTypeHspBufferTracker GetCallbackOfHspBufferTracker()
    {
        return hspBufferTracker_;
    }

    void SetCallbackOfSetClipboardData(const CallbackTypeSetClipboardData&& setClipboardData)
    {
        setClipboardData_ = std::move(setClipboardData);
    }

    CallbackTypeSetClipboardData GetCallbackOfSetClipboardData()
    {
        return setClipboardData_;
    }

    void SetCallbackOfGetClipboardData(const CallbackTypeGetClipboardData&& getClipboardData)
    {
        getClipboardData_ = std::move(getClipboardData);
    }

    CallbackTypeGetClipboardData GetCallbackOfGetClipboardData()
    {
        return getClipboardData_;
    }

private:
    AcePreviewHelper() = default;
    AcePreviewHelper(const AcePreviewHelper&) = delete;
    AcePreviewHelper& operator=(const AcePreviewHelper&) = delete;

    CallbackTypePostTask postTask_ = nullptr;
    CallbackTypeIsCurrentRunnerThread isCurrentRunnerThread_ = nullptr;
    CallbackTypeHspBufferTracker hspBufferTracker_ = nullptr;
    CallbackTypeSetClipboardData setClipboardData_ = nullptr;
    CallbackTypeGetClipboardData getClipboardData_ = nullptr;
    CallbackFlushEmpty flushEmpty_ = nullptr;
};
} // namespace OHOS::Ace::Platform
#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_PREVIEW_HELPER_H
