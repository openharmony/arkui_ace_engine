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

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme
constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";
constexpr Dimension DEFAULT_SINGLE_TEXT_FONT_SIZE = 16.0_fp;
constexpr Dimension DEFAULT_SMALL_TEXT_FONT_SIZE = 10.0_fp;
constexpr Dimension DEFAULT_IMAGE_SIZE = 24.0_vp;
constexpr Dimension TAB_BAR_SPACE = 2.0_vp;

} // namespace

void TabContentModelNG::Create(std::function<void()>&& deepRenderFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        deepRenderFunc();
        auto deepChild = ViewStackProcessor::GetInstance()->Finish();
        auto parent = FrameNode::GetFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId);
        if (deepChild && parent) {
            deepChild->MountToParent(parent);
        }
        return deepChild;
    };
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<TabContentPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
    SetTabBar(DEFAULT_TAB_BAR_NAME, "", nullptr, true); // Set default tab bar.
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, DEFAULT_TAB_BAR_NAME);
}

void TabContentModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(
        V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    stack->Push(frameNode);
}

void TabContentModelNG::Pop()
{
    auto tabContent = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    NG::ViewStackProcessor::GetInstance()->PopContainer();

}

RefPtr<TabsNode> TabContentView::FindTabsNode(const RefPtr<UINode>& tabContent)
{
    CHECK_NULL_RETURN(tabContent, nullptr);
    RefPtr<UINode> parent = tabContent->GetParent();

    while(parent) {
        if (AceType::InstanceOf<TabsNode>(parent)) {
            return AceType::DynamicCast<TabsNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void TabContentView::AddTabBarItem(const RefPtr<UINode>& tabContent, int32_t position)
{
    LOGD("position %{public}d", position);
    CHECK_NULL_VOID(tabContent);
    auto tabContentId = tabContent->GetId();

    auto tabContentFrameNode = AceType::DynamicCast<FrameNode>(tabContent);
    CHECK_NULL_VOID(tabContentFrameNode);

    auto tabsNode = FindTabsNode(tabContent);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = tabsNode->GetTabBar();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarParam = tabContentFrameNode->GetPattern<TabContentPattern>()->GetTabBarParam();

    // Create column node to contain image and text or builder.
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, tabsNode->GetTabBarByContentId(tabContentId),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto linearLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(linearLayoutProperty);
    linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateSpace(TAB_BAR_SPACE);

    // Create tab bar with builder.
    if (tabBarParam->HasBuilder()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        tabBarParam->builder();
        auto builderNode = ViewStackProcessor::GetInstance()->Finish();
        builderNode->MountToParent(columnNode);
        tabBarNode->ReplaceChild(tabsNode->GetBuilderByContentId(tabContentId, columnNode), columnNode);
        return;
    }

    if (tabBarParam->text.empty()) {
        LOGW("Text is empty.");
        return;
    }

    LOGD("Text %{public}s", tabBarParam->text.c_str());

    // Create text node and image node.
    RefPtr<FrameNode> textNode;
    RefPtr<FrameNode> imageNode;
    if (static_cast<int32_t>(columnNode->GetChildren().size()) == 0) {
        LOGD("Text new child to column %{public}s", tabBarParam->text.c_str());
        ImageSourceInfo imageSourceInfo(tabBarParam->icon);
        imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(textNode);
        CHECK_NULL_VOID(imageNode);
        columnNode->MountToParent(tabBarNode, position);
        imageNode->MountToParent(columnNode);
        textNode->MountToParent(columnNode);
    } else {
        imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    }
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(imageNode);

    // Update property of text.
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(tabBarParam->text);
    textLayoutProperty->UpdateFontSize(DEFAULT_SINGLE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);

    // Update property of image.
    auto imageProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageProperty);
    if (!tabBarParam->icon.empty()) {
        textLayoutProperty->UpdateFontSize(DEFAULT_SMALL_TEXT_FONT_SIZE);
        imageProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(DEFAULT_IMAGE_SIZE), NG::CalcLength(DEFAULT_IMAGE_SIZE)));
    } else {
        imageProperty->UpdateUserDefinedIdealSize(CalcSize());
    }
    ImageSourceInfo imageSourceInfo(tabBarParam->icon);
    imageProperty->UpdateImageSourceInfo(imageSourceInfo);

    imageNode->MarkModifyDone();
    textNode->MarkModifyDone();
    columnNode->MarkModifyDone();
}

void TabContentView::RemoveTabBarItem(const RefPtr<TabsNode>& tabsNode, int32_t tabContentId)
{
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = tabsNode->GetTabBar();
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarItemId = tabsNode->GetTabBarByContentId(tabContentId);
    LOGD("Tab ID: %{public}d, Bar item ID: %{public}d", tabContentId, tabBarItemId);

    auto tabBarItemNode = ElementRegister::GetInstance()->GetUINodeById(tabBarItemId);
    tabBarNode->RemoveChild(tabBarItemNode);
}

void TabContentModelNG::SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
    TabBarBuilderFunc&& builder, bool /*useContentOnly*/)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, icon.value_or(""));
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, text.value_or(""));
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(text.value_or(""), icon.value_or(""), std::move(builder));
}

} // namespace OHOS::Ace::NG
