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

#include "adapter/preview/entrance/clipboard/clipboard_impl.h"

namespace OHOS::Ace::Platform {

void ClipboardImpl::SetData(const std::string& data)
{
    if (!taskExecutor_ || !callbackSetClipboardData_) {
        LOGE("Failed to set the data to clipboard.");
        return;
    }
    taskExecutor_->PostTask(
        [callbackSetClipboardData = callbackSetClipboardData_, data] {
            callbackSetClipboardData(data);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void ClipboardImpl::GetData(const std::function<void(const std::string&)>& callback, bool syncMode)
{
    if (!taskExecutor_ || !callbackGetClipboardData_ || !callback) {
        LOGE("Failed to get the data from clipboard.");
        return;
    }
    taskExecutor_->PostTask(
        [callbackGetClipboardData = callbackGetClipboardData_, callback] {
            callback(callbackGetClipboardData());
        },
        TaskExecutor::TaskType::PLATFORM);
}

void ClipboardImpl::Clear() {}

void ClipboardImpl::RegisterCallbackSetClipboardData(CallbackSetClipboardData callback)
{
    callbackSetClipboardData_ = callback;
}

void ClipboardImpl::RegisterCallbackGetClipboardData(CallbackGetClipboardData callback)
{
    callbackGetClipboardData_ = callback;
}

} // namespace OHOS::Ace::Platform
