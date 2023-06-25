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

#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
UIExtensionPattern::UIExtensionPattern(const std::string& bundleName, const std::string& abilityName) {}

UIExtensionPattern::~UIExtensionPattern() {}

void UIExtensionPattern::OnConnect() {}

void UIExtensionPattern::OnWindowShow() {}

void UIExtensionPattern::OnWindowHide() {}

void UIExtensionPattern::RequestExtensionSessionActivation() {}

void UIExtensionPattern::RequestExtensionSessionBackground() {}

void UIExtensionPattern::RequestExtensionSessionDestruction() {}

RefPtr<LayoutAlgorithm> UIExtensionPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<LayoutAlgorithm>();
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode) {}

void UIExtensionPattern::OnModifyDone() {}

FocusPattern UIExtensionPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::NONE };
}
} // namespace OHOS::Ace::NG
