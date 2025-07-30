/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/resource/web_javascript_execute_callback.h"

namespace OHOS::Ace {
void WebJavaScriptExecuteCallBack::OnReceiveValue(std::shared_ptr<NWebMessage> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    if (callback_ && result && result->GetType() == NWebValue::Type::STRING) {
        callback_(result->GetString());
    }
}

void WebJavaScriptExecuteCallBack::OnReceiveValueV2(std::shared_ptr<NWebHapValue> value)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    if (callback_ && value && value->GetType() == NWebHapValue::Type::STRING) {
        callback_(value->GetString());
    }
}

void WebMessageValueCallBackImpl::OnReceiveValue(std::shared_ptr<NWebMessage> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    if (callback_ && result && result->GetType() == NWebValue::Type::STRING) {
        callback_(result->GetString());
    }
}

void WebMessageValueCallBackImpl::OnReceiveValueV2(std::shared_ptr<NWebHapValue> value)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    if (callback_ && value && value->GetType() == NWebHapValue::Type::STRING) {
        callback_(value->GetString());
    }
}
} // OHOS::Ace
