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

#include "interfaces/inner_api/ace_kit/include/ui/view/extend/badge/badge_extension.h"

#include <string>

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/utils/utils.h"
#include "ui/view/frame_node.h"
#include "ui/view/pattern.h"

#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "frameworks/core/components_ng/base/frame_node.h"

namespace OHOS::Ace::Kit {

BadgeExtension::BadgeExtension(const WeakPtr<Pattern>& pattern) : hostPattern_(pattern) {}

BadgeExtension::~BadgeExtension() = default;

void BadgeExtension::AdjustPosition(bool& hasFontSize) {}

std::string BadgeExtension::GetBadgeString()
{
    auto hostNode = AceType::DynamicCast<FrameNodeImpl>(GetHostNode());
    CHECK_NULL_RETURN(hostNode, "");
    auto nodePtr = hostNode->GetAceNodePtr();
    CHECK_NULL_RETURN(nodePtr, "");
    auto layoutProp = nodePtr->GetLayoutProperty<NG::BadgeLayoutProperty>();
    CHECK_NULL_RETURN(layoutProp, "");
    auto badgeCount = layoutProp->GetBadgeCount();
    auto badgeValue = layoutProp->GetBadgeValue();
    if (badgeCount.has_value()) {
        return std::to_string(badgeCount.value());
    }
    if (badgeValue.has_value()) {
        return badgeValue.value();
    }
    return "";
}

RefPtr<FrameNode> BadgeExtension::GetHostNode()
{
    auto hostPattern = GetHostPattern();
    CHECK_NULL_RETURN(hostPattern, nullptr);
    return hostPattern->GetHost().Upgrade();
}

RefPtr<Pattern> BadgeExtension::GetHostPattern()
{
    return hostPattern_.Upgrade();
}

} // namespace OHOS::Ace::Kit
