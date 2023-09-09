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

#include "core/components_ng/pattern/navigation/nav_bar_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

RefPtr<NavBarNode> NavBarNode::GetOrCreateNavBarNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<NavBarNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(tag, nodeId, pattern);
    navBarNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navBarNode);
    return navBarNode;
}

void NavBarNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto contentNode = GetNavBarContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(
            V2::NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        SetNavBarContentNode(contentNode);
        auto layoutProperty = GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        AddChild(contentNode);
    }
    contentNode->AddChild(child);
}

std::string NavBarNode::GetTitleString() const
{
    auto title = DynamicCast<FrameNode>(GetTitle());
    CHECK_NULL_RETURN(title, "");
    if (title->GetTag() != V2::TEXT_ETS_TAG) {
        return "";
    }
    auto textLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    return textLayoutProperty->GetContentValue("");
}

std::string NavBarNode::GetSubtitleString() const
{
    auto subtitle = DynamicCast<FrameNode>(GetSubtitle());
    CHECK_NULL_RETURN(subtitle, "");
    if (subtitle->GetTag() != V2::TEXT_ETS_TAG) {
        return "";
    }
    auto textLayoutProperty = subtitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    return textLayoutProperty->GetContentValue("");
}

std::string NavBarNode::GetBarItemsString(bool isMenu) const
{
    auto jsonValue = JsonUtil::Create(true);
    auto parentNodeOfBarItems = isMenu ? DynamicCast<FrameNode>(GetMenu()) : DynamicCast<FrameNode>(GetToolBarNode());
    CHECK_NULL_RETURN(parentNodeOfBarItems, "");
    if (!parentNodeOfBarItems->GetChildren().empty()) {
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
                    jsonToolBarItem->Put("value", textLayoutProperty->GetContentValue("").c_str());
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
    return "";
}

void NavBarNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("title", GetTitleString().c_str());
    json->Put("subtitle", GetSubtitleString().c_str());
    json->Put("menus", GetBarItemsString(true).c_str());
    json->Put("toolBar", GetBarItemsString(false).c_str());
    auto layoutProperty = GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ToJsonValue(json);
}

} // namespace OHOS::Ace::NG
