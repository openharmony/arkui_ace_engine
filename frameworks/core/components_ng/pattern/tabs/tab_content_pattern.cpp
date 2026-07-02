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

#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

namespace OHOS::Ace::NG {

void TabContentPattern::OnAttachToMainTree()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto tabs = TabContentModelNG::FindTabsNode(hostNode);
    CHECK_NULL_VOID(tabs);
    auto swiper = tabs->GetTabs();
    CHECK_NULL_VOID(swiper);
    auto indexPair = swiper->GetChildFlatIndex(hostNode->GetId());
    if (!indexPair.first) {
        return;
    }
    GenerateGlobalComponentId(std::to_string(indexPair.second));
}

} // namespace OHOS::Ace::NG
