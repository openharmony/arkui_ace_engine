/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/tabs/tabs.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/ace_type.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"

namespace OHOS::Ace::Kit {

Tabs::Tabs()
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceNode = NG::TabsModelNG::CreateFrameNode(nodeId);
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
}

Tabs::Tabs(RefPtr<FrameNode>& node)
{
    node_ = node;
}

Tabs::~Tabs() = default;

RefPtr<Tabs> Tabs::Create()
{
    return Referenced::MakeRefPtr<Tabs>();
}

RefPtr<Tabs> Tabs::Create(RefPtr<FrameNode>& node)
{
    return Referenced::MakeRefPtr<Tabs>(node);
}

RefPtr<NG::TabsNode> GetTabsNode(const RefPtr<FrameNode>& node)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_RETURN(frameNodeImpl, nullptr);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_RETURN(aceFrameNode, nullptr);
    return AceType::DynamicCast<NG::TabsNode>(aceFrameNode);
}

void Tabs::UpdateDividerOpacity(const double opacity)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto divider = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(divider);
    NG::ViewAbstract::SetOpacity(Referenced::RawPtr(divider), opacity);
}

void Tabs::UpdateTabBarBrightness(const BrightnessOption& brightnessOption)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    NG::ViewAbstract::SetBgDynamicBrightness(Referenced::RawPtr(tabBarNode), brightnessOption);
}

auto GetTabBarFrameRect(const RefPtr<FrameNode>& node)
{
    auto tabsNode = GetTabsNode(node);
    CHECK_NULL_RETURN(tabsNode, NG::RectF {});
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, NG::RectF {});
    auto geometryNode = tabBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, NG::RectF {});
    return geometryNode->GetFrameRect();
}

double Tabs::GetTabBarTop()
{
    const auto tabBarRect = GetTabBarFrameRect(node_);
    return tabBarRect.Top();
}

double Tabs::GetTabBarBottom()
{
    const auto tabBarRect = GetTabBarFrameRect(node_);
    return tabBarRect.Bottom();
}

void Tabs::SetDivider(const TabsItemDivider& divider)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);

    Ace::TabsItemDivider aceDivider;
    aceDivider.strokeWidth = divider.strokeWidth;
    aceDivider.color = divider.color;
    aceDivider.startMargin = divider.startMargin;
    aceDivider.endMargin = divider.endMargin;
    aceDivider.isNull = divider.isNull;
    NG::TabsModelNG::SetDivider(Referenced::RawPtr(tabsNode), aceDivider);
}

RefPtr<FrameNode> Tabs::GetTabBar()
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    return AceType::MakeRefPtr<FrameNodeImpl>(Referenced::RawPtr(tabBarNode));
}

void Tabs::SetOnChange(OnChangeEvent onChangeEvent)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node_);
    CHECK_NULL_VOID(frameNodeImpl);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_VOID(aceFrameNode);
    auto tabPattern = aceFrameNode->GetPattern<NG::TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    auto onChange = [onChangeEvent](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            return;
        }
        onChangeEvent(tabsInfo->GetIndex());
    };
    tabPattern->SetOnChangeEvent(std::move(onChange));
}

} // namespace OHOS::Ace::Kit