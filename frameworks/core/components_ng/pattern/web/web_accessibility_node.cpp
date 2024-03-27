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


#include "core/components_ng/pattern/web/web_accessibility_node.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {
WebAccessibilityNode::WebAccessibilityNode(const RefPtr<WebPattern>& webPattern)
    : FrameNode(V2::WEB_CORE_TAG, 0, MakeRefPtr<Pattern>())
{
    webPattern_ = webPattern;
    if (webPattern != nullptr) {
        auto webNode = webPattern->GetHost();
        if (webNode != nullptr) {
            pageId_ = webNode->GetPageId();
        }
    }
    AddFlag(NodeFlag::WEB_CORE_TAG);
}

RefPtr<FrameNode> WebAccessibilityNode::GetWebNode() const
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, nullptr);
    return webPattern->GetHost();
}
} // namespace OHOS::Ace::NG
