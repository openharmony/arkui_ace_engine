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

#include "core/components_ng/pattern/navigation/navdestination_node_base.h"

#include "base/utils/utf_helper.h"
#include "base/json/json_util.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
std::string NavDestinationNodeBase::GetBarItemsString(bool isMenu) const
{
    auto jsonValue = JsonUtil::Create(true);
    auto parentNodeOfBarItems = isMenu ? DynamicCast<FrameNode>(GetMenu()) : DynamicCast<FrameNode>(GetToolBarNode());
    CHECK_NULL_RETURN(parentNodeOfBarItems, "");
    if (parentNodeOfBarItems->GetChildren().empty()) {
        return "";
    }
    auto jsonOptions = JsonUtil::CreateArray(true);
    int32_t i = 0;
    for (auto iter = parentNodeOfBarItems->GetChildren().begin(); iter != parentNodeOfBarItems->GetChildren().end();
            ++iter, i++) {
        auto jsonToolBarItem = JsonUtil::CreateArray(true);
        auto barItemNode = DynamicCast<BarItemNode>(*iter);
        if (!barItemNode) {
            jsonToolBarItem->Put("value", "");
            jsonToolBarItem->Put("icon", "");
            continue;
        }
        auto iconNode = DynamicCast<FrameNode>(barItemNode->GetIconNode());
        if (iconNode) {
            auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
            if (!imageLayoutProperty || !imageLayoutProperty->HasImageSourceInfo()) {
                jsonToolBarItem->Put("icon", "");
            } else {
                jsonToolBarItem->Put("icon", imageLayoutProperty->GetImageSourceInfoValue().GetSrc().c_str());
            }
        } else {
            jsonToolBarItem->Put("icon", "");
        }
        auto textNode = DynamicCast<FrameNode>(barItemNode->GetTextNode());
        if (textNode) {
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            if (!textLayoutProperty) {
                jsonToolBarItem->Put("value", "");
            } else {
                jsonToolBarItem->Put("value", UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u"")).c_str());
            }
        } else {
            jsonToolBarItem->Put("value", "");
        }
        auto index_ = std::to_string(i);
        jsonOptions->Put(index_.c_str(), jsonToolBarItem);
    }
    jsonValue->Put("items", jsonOptions);
    return jsonValue->ToString();
}

bool NavDestinationNodeBase::IsToolBarVisible() const
{
    auto toolBarNode = AceType::DynamicCast<FrameNode>(GetToolBarNode());
    CHECK_NULL_RETURN(toolBarNode, false);
    auto layoutProperty = toolBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE;
}
} // namespace OHOS::Ace::NG
