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

#include "uicast_interface/uicast_context_impl.h"

namespace OHOS::Ace {
bool UICastContextImpl::IsEnable()
{
    return false;
}

void UICastContextImpl::Init(const WeakPtr<PipelineContext>& context) {}

bool UICastContextImpl::NeedsRebuild()
{
    return false;
}

void UICastContextImpl::OnFlushBuildStart() {}

void UICastContextImpl::OnFlushBuildFinish() {}

bool UICastContextImpl::CallRouterBackToPopPage()
{
    return false;
}

void UICastContextImpl::CheckEvent() {}

void UICastContextImpl::HandleRouterPageCall(const std::string& cmd, const std::string& url) {}

void UICastContextImpl::ShowToast(const std::string& message, int32_t duration, const std::string& bottom) {}

void UICastContextImpl::ShowDialog(const DialogProperties& dialogProperties) {}
} // namespace OHOS::Ace