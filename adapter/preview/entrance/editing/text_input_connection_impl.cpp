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


#include "adapter/preview/entrance/editing/text_input_connection_impl.h"

#include "adapter/preview/entrance/editing/text_input_client_mgr.h"

namespace OHOS::Ace::Platform {

void TextInputConnectionImpl::Show(bool isFocusViewChanged, int32_t instanceId)
{}

void TextInputConnectionImpl::SetEditingState(
    const TextEditingValue& value, int32_t instanceId, bool needFireChangeEvent)
{
    if (taskExecutor_ && Attached()) {
        taskExecutor_->PostTask(
            [value, instanceId, needFireChangeEvent] {
                TextInputClientMgr::GetInstance().SetTextEditingValue(value);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUITextEditingSetValue");
    }
}

void TextInputConnectionImpl::Close(int32_t instanceId)
{
    // Set the current client id to invalid value.
    TextInputClientMgr::GetInstance().ResetClientId();
    TextInputClientMgr::GetInstance().SetCurrentConnection(nullptr);
    if (Attached()) {
        LOGE("Text input connection close failed.");
    }
}

bool TextInputConnectionImpl::Attached()
{
    return TextInputClientMgr::GetInstance().IsCurrentConnection(this);
}

} // namespace OHOS::Ace::Platform
