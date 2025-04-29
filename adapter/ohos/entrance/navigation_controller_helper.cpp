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

#include "navigation_controller_helper.h"

#include "ui_content_impl.h"

namespace OHOS {
namespace Ace {
extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_GetNavigationController(
    UIContent* uiContent, const char* navigationId)
{
    return NavigationControllerHelper::GetNavigationController(uiContent, navigationId);
}

NavigationController* NavigationControllerHelper::GetNavigationController(
    UIContent* uiContent, const std::string& navigationId)
{
    if (navigationId.empty()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "navigationId is empty");
        return nullptr;
    }

    OHOS::Ace::UIContentImpl* uiContentImpl = reinterpret_cast<OHOS::Ace::UIContentImpl*>(uiContent);
    if (uiContentImpl == nullptr) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "uiContentImpl is null");
        return nullptr;
    }

    int32_t instanceId = uiContentImpl->GetInstanceId();
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (!container) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "container is nullptr, instanceId is %{public}d", instanceId);
        return nullptr;
    }

    return container->GetNavigationController(navigationId).get();
}
} // namespace Ace
} // namespace OHOS
