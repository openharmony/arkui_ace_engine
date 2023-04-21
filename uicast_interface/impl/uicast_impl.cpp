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

#include "uicast_interface/uicast_impl.h"

namespace OHOS::Ace::Framework {
int UICastImpl::GetViewUniqueID(int parentUniqueId)
{
    return 0;
}

void UICastImpl::CacheCmd(const std::string& cmd) {}

void UICastImpl::CacheCmd(const std::string& cmd, const std::string& para) {}

void UICastImpl::SendCmd() {}

void UICastImpl::ViewCreate(const std::string& viewId, int uniqueId, JSView* view) {}

void UICastImpl::ViewConstructor(
    const std::string& viewId, int uniqueId, const std::string& parentViewId, int parentUniqueId, JSView* view)
{}

void UICastImpl::Render(const std::string& viewId) {}

void UICastImpl::CreateLazyForEach(const std::string& pviewID, int totalCount, const std::string& remoteInfo) {}
} // namespace OHOS::Ace::Framework