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

#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
void NavDestinationModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    if (!navDestinationNode->GetTitleBarNode()) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            CreateImageButton(navDestinationNode);
        } else {
            CreateBackButton(navDestinationNode);
        }
    }
    // content node
    if (!navDestinationNode->GetTitleBarNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navDestinationNode->AddChild(contentNode);
        navDestinationNode->SetContentNode(contentNode);
    }

    stack->Push(navDestinationNode);
}

void NavDestinationModelNG::CreateImageButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->AddChild(titleBarNode);
    navDestinationNode->SetTitleBarNode(titleBarNode);

    int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto backButtonNode =
        FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<ImagePattern>());
    titleBarNode->AddChild(backButtonNode);
    titleBarNode->SetBackButton(backButtonNode);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(theme->GetBackResourceId());
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    backButtonLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
    backButtonNode->MarkModifyDone();

    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
}

void NavDestinationModelNG::CreateBackButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->AddChild(titleBarNode);
    navDestinationNode->SetTitleBarNode(titleBarNode);

    int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto backButtonNode =
        FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->AddChild(backButtonNode);
    titleBarNode->SetBackButton(backButtonNode);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
    backButtonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BACK_BUTTON_SIZE.ConvertToPx()), CalcLength(BACK_BUTTON_SIZE.ConvertToPx())));
    backButtonLayoutProperty->UpdateType(ButtonType::NORMAL);
    backButtonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(BUTTON_RADIUS));
    backButtonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto renderContext = backButtonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    PaddingProperty padding;
    padding.SetEdges(CalcLength(BUTTON_PADDING.ConvertToPx()));
    backButtonLayoutProperty->UpdatePadding(padding);

    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(backButtonImageNode);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(theme->GetBackResourceId());
    auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);

    auto navDestinationEventHub = navDestinationNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(navDestinationEventHub);
    auto paintProperty = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!navDestinationEventHub->IsEnabled()) {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    } else {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor());
    }
    backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    backButtonNode->AddChild(backButtonImageNode);
    backButtonImageNode->MarkModifyDone();
    backButtonNode->MarkModifyDone();

    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
}

void NavDestinationModelNG::Create(std::function<void()>&& deepRenderFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        auto parent = AceType::DynamicCast<UINode>(FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId));
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(parent);
        if (navDestinationNode && navDestinationNode->GetContentNode()) {
            parent = navDestinationNode->GetContentNode();
        }
        ScopedViewStackProcessor scopedViewStackProcessor;
        ViewStackProcessor::GetInstance()->Push(parent);
        deepRenderFunc();
        ViewStackProcessor::GetInstance()->PopContainer();
        ViewStackProcessor::GetInstance()->Finish();
        return parent;
    };
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<NavDestinationPattern>(shallowBuilder);
        });
    if (!navDestinationNode->GetTitleBarNode()) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            CreateImageButton(navDestinationNode);
        } else {
            CreateBackButton(navDestinationNode);
        }
    }
    // content node
    if (!navDestinationNode->GetContentNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navDestinationNode->AddChild(contentNode);
        navDestinationNode->SetContentNode(contentNode);
    }
    stack->Push(navDestinationNode);
}

void NavDestinationModelNG::SetHideTitleBar(bool hideTitleBar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, HideTitleBar, hideTitleBar);
}

void NavDestinationModelNG::SetTitle(const std::string& title, bool hasSubTitle)
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
        if (!hasSubTitle) {
            if (navDestinationNode->GetSubtitle()) {
                navDestinationNode->SetSubtitle(nullptr);
            }
            titleProperty->UpdateMaxLines(2); // 2:title's maxLine.
        } else {
            titleProperty->UpdateMaxLines(1); // 1:title's maxLine = 1.
        }
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
        titleNode->MarkModifyDone();
        titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        navDestinationNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
        return;
    } while (false);
    int32_t titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(title);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    textLayoutProperty->UpdateFontSize(theme->GetTitleFontSizeMin());
    textLayoutProperty->UpdateTextColor(theme->GetTitleColor());
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    if (!hasSubTitle) {
        textLayoutProperty->UpdateMaxLines(2); // 2:title's maxLine.
    } else {
        textLayoutProperty->UpdateMaxLines(1); // 1:title's maxLine = 1.
    }
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    navDestinationNode->SetTitle(titleNode);
    navDestinationNode->UpdatePrevTitleIsCustom(false);
}

void NavDestinationModelNG::SetSubtitle(const std::string& subtitle)
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
    auto subtitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, subtitleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(subtitle);
    textLayoutProperty->UpdateFontSize(SUBTITLE_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(SUBTITLE_COLOR);
    textLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateMaxLines(1); // 1:title's maxLine = 1.
    navDestinationNode->SetSubtitle(subtitleNode);
}

void NavDestinationModelNG::SetCustomTitle(const RefPtr<AceType>& customNode)
{
    auto customTitle = AceType::DynamicCast<NG::UINode>(customNode);
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

void NavDestinationModelNG::SetTitleHeight(int32_t height)
{
    if (height == 0) {
        ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, TitleBarHeight, FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
    }
    if (height == 1) {
        ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, TitleBarHeight, FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
    }
}

void NavDestinationModelNG::SetTitleHeight(const Dimension& titleHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, TitleBarHeight, titleHeight);
}

void NavDestinationModelNG::SetOnShown(std::function<void()>&& onShow)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnShown(onShow);
}

void NavDestinationModelNG::SetOnHidden(std::function<void()>&& onHidden)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnHidden(onHidden);
}

void NavDestinationModelNG::SetOnBackPressed(std::function<bool()>&& onBackPressed)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnBackPressed(onBackPressed);
}

RefPtr<AceType> NavDestinationModelNG::CreateEmpty()
{
    ScopedViewStackProcessor processor;
    Create();
    auto uiNode = ViewStackProcessor::GetInstance()->Finish();
    uiNode->SetRemoveSilently(true);
    return uiNode;
}
} // namespace OHOS::Ace::NG
