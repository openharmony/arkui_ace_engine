/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/pattern.h"

#include "core/components_ng/event/focus_hub.h"

namespace OHOS::Ace::NG {
int32_t Pattern::OnRecvCommand(const std::string& command)
{
    return 0;
}

void Pattern::OnColorModeChange(uint32_t colorMode) {}

void Pattern::AddResObj(const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{}

void Pattern::AddResCache(const std::string& key, const std::string& value) {}

std::string Pattern::GetResCacheMapByKey(const std::string& key)
{
    return std::string();
}

void Pattern::RemoveResObj(const std::string& key) {}

void Pattern::UnRegisterResource(const std::string& key) {}

ScopeFocusAlgorithm Pattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm();
}

FocusPattern Pattern::GetFocusPattern() const
{
    return {};
}

RefPtr<AccessibilityProperty> Pattern::CreateAccessibilityProperty()
{
    return nullptr;
}

RefPtr<LayoutAlgorithm> Pattern::CreateLayoutAlgorithm()
{
    return nullptr;
}

RefPtr<EventHub> Pattern::CreateEventHub()
{
    return nullptr;
}

void Pattern::CheckLocalized()
{}
} // namespace OHOS::Ace::NG
