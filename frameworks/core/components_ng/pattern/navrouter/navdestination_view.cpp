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

#include "core/components_ng/pattern/navrouter/navdestination_view.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void NavDestinationView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    
    // titleBar node
    if (!navDestinationNode->GetTitleBarNode()) {
        int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
            V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
        navDestinationNode->AddChild(titleBarNode);
        navDestinationNode->SetTitleBarNode(titleBarNode);

        int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto backButtonNode = FrameNode::CreateFrameNode(
            V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<ImagePattern>());
        titleBarNode->AddChild(backButtonNode);
        titleBarNode->SetBackButton(backButtonNode);

        auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);

        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAVDESTINATION);
    }
    
    // content node
    if (!navDestinationNode->GetTitleBarNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG,
            contentNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navDestinationNode->AddChild(contentNode);
        navDestinationNode->SetContentNode(contentNode);
    }

    stack->Push(navDestinationNode);
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    navDestinationLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
}

void NavDestinationView::SetHideTitleBar(bool hideTitleBar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, HideTitleBar, hideTitleBar);
}

void NavDestinationView::SetTitle(const std::string& title)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    do {
        if (!navDestinationNode->GetTitle()) {
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::ADD);
            break;
        }
        // if previous title is not a frame node, we remove it and create a new node
        auto titleNode = AceType::DynamicCast<FrameNode>(navDestinationNode->GetTitle());
        if (!titleNode) {
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        auto titleProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
        // previous title is not a text node and might be custom, we remove it and create a new node
        if (!titleProperty) {
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        // text content is the same, do nothing
        if (titleProperty->GetContentValue() == title) {
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        // update title content only without changing node
        titleProperty->UpdateContent(title);
        navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
        return;
    } while (false);
    int32_t titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(title);
    textLayoutProperty->UpdateFontSize(TITLE_TEXT_SIZE);
    textLayoutProperty->UpdateTextColor(TITLE_TEXT_COLOR);
    textLayoutProperty->UpdateFontWeight(FontWeight::BOLD);
    navDestinationNode->SetTitle(titleNode);
    navDestinationNode->UpdatePrevTitleIsCustom(false);
}

void NavDestinationView::SetSubtitle(const std::string& subtitle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    do {
        if (!navDestinationNode->GetSubtitle()) {
            navDestinationNode->UpdateSubtitleNodeOperation(ChildNodeOperation::ADD);
            break;
        }
        auto subtitleNode = AceType::DynamicCast<FrameNode>(navDestinationNode->GetSubtitle());
        if (!subtitleNode) {
            navDestinationNode->UpdateSubtitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        auto subtitleProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
        if (!subtitleProperty) {
            navDestinationNode->UpdateSubtitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        if (subtitleProperty->GetContentValue() == subtitle) {
            navDestinationNode->UpdateSubtitleNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        subtitleProperty->UpdateContent(subtitle);
        navDestinationNode->UpdateSubtitleNodeOperation(ChildNodeOperation::NONE);
        return;
    } while (false);
    int32_t subtitleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto subtitleNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, subtitleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(subtitle);
    textLayoutProperty->UpdateFontSize(SUBTITLE_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(SUBTITLE_COLOR);
    textLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    navDestinationNode->SetSubtitle(subtitleNode);
}

void NavDestinationView::SetCustomTitle(const RefPtr<UINode>& customTitle)
{
    CHECK_NULL_VOID(customTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    if (navDestinationNode->GetTitle()) {
        if (customTitle->GetId() == navDestinationNode->GetTitle()->GetId()) {
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
        } else {
            navDestinationNode->SetTitle(customTitle);
            navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
        }
        return;
    }
    navDestinationNode->SetTitle(customTitle);
    navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::ADD);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
}

void NavDestinationView::SetTitleHeight(const Dimension& height)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, TitleBarHeight, height);
}

} // namespace OHOS::Ace::NG