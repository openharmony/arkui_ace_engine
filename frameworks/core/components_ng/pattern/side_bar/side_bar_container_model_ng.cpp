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

#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER = 1;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
static Dimension DEFAULT_MIN_CONTENT_WIDTH = 0.0_vp;
constexpr static int32_t PLATFORM_VERSION_TEN = 10;
constexpr static int32_t DEFAULT_CONTROL_BUTTON_ZINDEX = 3;

ImageSourceInfo CreateSourceInfo(const std::string& src, bool isPixelMap, RefPtr<PixelMap>& pixMap)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (isPixelMap && pixMap) {
        return ImageSourceInfo(pixMap);
    }
#endif
    return ImageSourceInfo(src);
}
} // namespace

void SideBarContainerModelNG::Create()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto sideBarContainerNode = FrameNode::GetOrCreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SideBarContainerPattern>(); });

    CHECK_NULL_VOID(sideBarContainerNode);

    stack->Push(sideBarContainerNode);
}

void SideBarContainerModelNG::Pop()
{
    auto sideBarContainerNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(sideBarContainerNode);

    auto children = sideBarContainerNode->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER) {
        LOGE("SideBarContainerView::Pop children's size is wrong[%{public}zu].", children.size());
        NG::ViewStackProcessor::GetInstance()->PopContainer();
        return;
    }

    auto pattern = sideBarContainerNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);

    if (pattern->HasControlButton()) {
        return;
    }

    auto sideBarNode = children.front();
    sideBarNode->MovePosition(DEFAULT_NODE_SLOT);

    auto sideBarFrameNode = AceType::DynamicCast<FrameNode>(sideBarNode);
    if (sideBarFrameNode) {
        auto renderContext = sideBarFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (!renderContext->HasBackgroundColor()) {
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto sideBarTheme = context->GetTheme<SideBarTheme>();
            CHECK_NULL_VOID(sideBarTheme);
            Color bgColor = sideBarTheme->GetSideBarBackgroundColor();
            renderContext->UpdateBackgroundColor(bgColor);
        }
    }
    sideBarContainerNode->RebuildRenderContextTree();

    CreateAndMountDivider(sideBarContainerNode);
    CreateAndMountControlButton(sideBarContainerNode);
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void SideBarContainerModelNG::CreateAndMountControlButton(const RefPtr<NG::FrameNode>& parentNode)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sideBarTheme);

    auto buttonNode = CreateControlButton(sideBarTheme);
    CHECK_NULL_VOID(buttonNode);
    auto imgNode = CreateControlImage(sideBarTheme, parentNode);
    CHECK_NULL_VOID(imgNode);

    auto buttonHub = buttonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(buttonHub);
    auto gestureHub = buttonHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    parentPattern->SetHasControlButton(true);
    parentPattern->InitControlButtonTouchEvent(gestureHub);

    imgNode->MountToParent(buttonNode);
    buttonNode->MountToParent(parentNode);
    imgNode->MarkModifyDone();
    buttonNode->MarkModifyDone();
}

RefPtr<FrameNode> SideBarContainerModelNG::CreateControlButton(const RefPtr<SideBarTheme>& sideBarTheme)
{
    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    auto butttonRadius = sideBarTheme->GetControlButtonRadius();
    buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(butttonRadius));
    auto buttonRenderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(buttonRenderContext, nullptr);
    buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonRenderContext->UpdateZIndex(DEFAULT_CONTROL_BUTTON_ZINDEX);
    return buttonNode;
}

RefPtr<FrameNode> SideBarContainerModelNG::CreateControlImage(
    const RefPtr<SideBarTheme>& sideBarTheme, const RefPtr<FrameNode>& parentNode)
{
    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imgNode, nullptr);

    auto layoutProperty = parentNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto isShowSideBar = layoutProperty->GetShowSideBar().value_or(true);
    std::optional<ImageSourceInfo> info = std::nullopt;
    if (isShowSideBar) {
        info = layoutProperty->GetControlButtonShowIconInfo();
    } else {
        info = layoutProperty->GetControlButtonHiddenIconInfo();
    }
    if (!info.has_value()) {
        info = std::make_optional<ImageSourceInfo>();
        info->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        Color controlButtonColor = sideBarTheme->GetControlImageColor();
        info->SetFillColor(controlButtonColor);
    }
    auto imageLayoutProperty = imgNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(info.value());
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateAlignment(Alignment::CENTER);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_RETURN(parentPattern, nullptr);
    Dimension imageWidth;
    Dimension imageHeight;
    parentPattern->GetControlImageSize(imageWidth, imageHeight);
    CalcSize imageCalcSize((CalcLength(imageWidth)), CalcLength(imageHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    return imgNode;
}

void SideBarContainerModelNG::CreateAndMountDivider(const RefPtr<NG::FrameNode>& parentNode)
{
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto dividerColor = layoutProperty->GetDividerColor().value_or(DEFAULT_DIVIDER_COLOR);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);

    int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });

    auto dividerHub = dividerNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(dividerHub);
    auto inputHub = dividerHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto parentPattern = parentNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(parentPattern);
    parentPattern->InitDividerMouseEvent(inputHub);

    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(true);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);

    dividerNode->MountToParent(parentNode);
    dividerNode->MarkModifyDone();
}

void SideBarContainerModelNG::SetSideBarContainerType(SideBarContainerType type)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarContainerType, type);
}

void SideBarContainerModelNG::SetShowSideBar(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowSideBar, isShow);
}

void SideBarContainerModelNG::SetShowControlButton(bool showControlButton)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowControlButton, showControlButton);
}

void SideBarContainerModelNG::ParseAndSetWidth(WidthType widthType, Dimension& width)
{
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            SetSideBarWidth(width.IsNonNegative() ? width : DEFAULT_SIDE_BAR_WIDTH);
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            SetMinSideBarWidth(width.IsNonNegative() ? width : DEFAULT_MIN_SIDE_BAR_WIDTH);
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            SetMaxSideBarWidth(width.IsNonNegative() ? width : DEFAULT_MAX_SIDE_BAR_WIDTH);
            break;
        default:
            break;
    }
}

void SideBarContainerModelNG::SetSideBarWidth(const Dimension& sideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth);
}

void SideBarContainerModelNG::SetMinSideBarWidth(const Dimension& minSideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth);
}

void SideBarContainerModelNG::SetMaxSideBarWidth(const Dimension& maxSideBarWidth)
{
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth);
}

void SideBarContainerModelNG::SetAutoHide(bool autoHide)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, AutoHide, autoHide);
}

void SideBarContainerModelNG::SetSideBarPosition(SideBarPosition sideBarPosition)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarPosition, sideBarPosition);
}

void SideBarContainerModelNG::SetControlButtonWidth(const Dimension& width)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, width);
}

void SideBarContainerModelNG::SetControlButtonHeight(const Dimension& height)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, height);
}

void SideBarContainerModelNG::SetControlButtonLeft(const Dimension& left)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonLeft, left);
}

void SideBarContainerModelNG::SetControlButtonTop(const Dimension& top)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top);
}

void SideBarContainerModelNG::SetControlButtonShowIconInfo(const std::string& showIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonShowIconInfo,
        CreateSourceInfo(showIconStr, isPixelMap, pixMap));
}

void SideBarContainerModelNG::SetControlButtonHiddenIconInfo(const std::string& hiddenIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo,
        CreateSourceInfo(hiddenIconStr, isPixelMap, pixMap));
}

void SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(const std::string& switchingIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo,
        CreateSourceInfo(switchingIconStr, isPixelMap, pixMap));
}

void SideBarContainerModelNG::SetDividerStrokeWidth(const Dimension& strokeWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth);
}

void SideBarContainerModelNG::SetDividerColor(const Color& color)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color);
}

void SideBarContainerModelNG::SetDividerStartMargin(const Dimension& startMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin);
}

void SideBarContainerModelNG::SetDividerEndMargin(const Dimension& endMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin);
}

void SideBarContainerModelNG::SetMinContentWidth(const Dimension& minContentWidth)
{
    if (minContentWidth.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, DEFAULT_MIN_CONTENT_WIDTH);
    }
}

void SideBarContainerModelNG::SetOnChange(std::function<void(const bool)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SideBarContainerModelNG::MarkNeedInitRealSideBarWidth()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedInitRealSideBarWidth(true);
}

void SideBarContainerModelNG::SetOnChangeEvent(std::function<void(const bool)>&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
