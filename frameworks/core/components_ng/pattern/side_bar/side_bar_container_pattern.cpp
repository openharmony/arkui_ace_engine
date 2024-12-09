/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

#include <optional>

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/mousestyle/mouse_style.h"
#include "base/resource/internal_resource.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/container.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_paint_method.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif
namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE = 3;
constexpr int32_t DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_VALUE = 2;
constexpr float RATIO_NEGATIVE = -1.0f;
constexpr float RATIO_ZERO = 0.0f;
constexpr Dimension DEFAULT_DRAG_REGION = 20.0_vp;
constexpr int32_t SIDEBAR_DURATION = 500;
const RefPtr<CubicCurve> SIDEBAR_CURVE = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.2f, 0.1f, 1.0f);
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_VP = 2.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
constexpr static int32_t PLATFORM_VERSION_TEN = 10;
constexpr static int32_t SIDE_BAR_INDEX = 2;
constexpr static int32_t CONTENT_INDEX = 3;
Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
Dimension SIDEBAR_WIDTH_NEGATIVE = -1.0_vp;
constexpr static Dimension DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER = 1;
constexpr static int32_t DEFAULT_CONTROL_BUTTON_ZINDEX = 3;
constexpr static int32_t DEFAULT_SIDE_BAR_ZINDEX_EMBED = 0;
constexpr static int32_t DEFAULT_DIVIDER_ZINDEX_EMBED = 1;
constexpr static int32_t DEFAULT_CONTENT_ZINDEX_EMBED = 2;
constexpr static int32_t DEFAULT_SIDE_BAR_ZINDEX_OVERLAY = 2;
constexpr static int32_t DEFAULT_DIVIDER_ZINDEX_OVERLAY = 1;
constexpr static int32_t DEFAULT_CONTENT_ZINDEX_OVERLAY = 0;
constexpr static int32_t DEFAULT_DOUBLE_DRAG_REGION = 2;
} // namespace

void SideBarContainerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);

    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    userSetSidebarWidth_ = layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    auto sideBarTheme = pipelineContext->GetTheme<SideBarTheme>();
    if (sideBarTheme && sideBarTheme->GetSideBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }
}

void SideBarContainerPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    pipeline->RemoveWindowFocusChangedCallback(frameNode->GetId());
}

void SideBarContainerPattern::OnUpdateShowSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty)
{
    CHECK_NULL_VOID(layoutProperty);

    type_ = layoutProperty->GetSideBarContainerType().value_or(SideBarContainerType::EMBED);

    if (realSideBarWidth_.IsNegative()) {
        realSideBarWidth_ = layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE);
    }

    auto newShowSideBar = layoutProperty->GetShowSideBar().value_or(true);
    if (newShowSideBar == userSetShowSideBar_) {
        return;
    }

    if (hasInit_ && ((sideBarStatus_ == SideBarStatus::HIDDEN && newShowSideBar) ||
        (sideBarStatus_ == SideBarStatus::SHOW && !newShowSideBar))) {
        FireChangeEvent(newShowSideBar);
    }
    
    userSetShowSideBar_ = newShowSideBar;
    SetSideBarStatus(newShowSideBar ? SideBarStatus::SHOW : SideBarStatus::HIDDEN);
    UpdateControlButtonIcon();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sideBarNode = GetSideBarNode(host);
    CHECK_NULL_VOID(sideBarNode);
    if (!newShowSideBar && sideBarNode->IsFirstBuilding()) {
        SetSideBarActive(false, false);
    }
}

void SideBarContainerPattern::OnUpdateShowControlButton(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(host);

    auto showControlButton = layoutProperty->GetShowControlButton().value_or(true);

    auto children = host->GetChildren();
    if (children.empty()) {
        return;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::BUTTON_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        return;
    }

    controlImageWidth_ = layoutProperty->GetControlButtonWidth().value_or(DEFAULT_CONTROL_BUTTON_WIDTH);
    controlImageHeight_ = layoutProperty->GetControlButtonHeight().value_or(DEFAULT_CONTROL_BUTTON_HEIGHT);
    auto imageNode = controlButtonNode->GetFirstChild();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
    if (!imageFrameNode || imageFrameNode ->GetTag() != V2::IMAGE_ETS_TAG) {
        return;
    }
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    CalcSize imageCalcSize((CalcLength(controlImageWidth_)), CalcLength(controlImageHeight_));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(controlButtonNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    buttonLayoutProperty->UpdateVisibility(showControlButton ? VisibleType::VISIBLE : VisibleType::GONE);
    buttonFrameNode->MarkModifyDone();
}

void SideBarContainerPattern::OnUpdateShowDivider(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(host);

    auto dividerColor = layoutProperty->GetDividerColor().value_or(DEFAULT_DIVIDER_COLOR);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);

    auto children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return;
    }

    auto begin = children.rbegin();
    auto dividerNode = *(++begin);
    CHECK_NULL_VOID(dividerNode);
    if (dividerNode->GetTag() != V2::DIVIDER_ETS_TAG || !AceType::InstanceOf<FrameNode>(dividerNode)) {
        return;
    }

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);

    auto dividerLayoutProperty = dividerFrameNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);
    dividerFrameNode->MarkModifyDone();
}

void SideBarContainerPattern::GetControlImageSize(Dimension& width, Dimension& height)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TEN)) {
        DEFAULT_CONTROL_BUTTON_WIDTH = 24.0_vp;
        DEFAULT_CONTROL_BUTTON_HEIGHT = 24.0_vp;
    }
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    controlImageWidth_ = layoutProperty->GetControlButtonWidth().value_or(DEFAULT_CONTROL_BUTTON_WIDTH);
    controlImageHeight_ = layoutProperty->GetControlButtonHeight().value_or(DEFAULT_CONTROL_BUTTON_HEIGHT);
    width = controlImageWidth_;
    height = controlImageHeight_;
}

RefPtr<FrameNode> SideBarContainerPattern::GetContentNode(const RefPtr<FrameNode>& host) const
{
    CHECK_NULL_RETURN(host, nullptr);

    const auto& children = host->GetChildren();
    if (children.size() <= CONTENT_INDEX) {
        return nullptr;
    }

    auto iter = children.rbegin();
    std::advance(iter, CONTENT_INDEX);
    auto contentNode = AceType::DynamicCast<FrameNode>(*iter);
    if (!contentNode) {
        contentNode = GetFirstFrameNode(*iter);
    }

    return contentNode;
}

RefPtr<FrameNode> SideBarContainerPattern::GetSideBarNode(const RefPtr<FrameNode>& host) const
{
    CHECK_NULL_RETURN(host, nullptr);

    const auto& children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return nullptr;
    }

    auto iter = children.rbegin();
    std::advance(iter, SIDE_BAR_INDEX);
    auto sideBarNode = AceType::DynamicCast<FrameNode>(*iter);
    if (!sideBarNode) {
        sideBarNode = GetFirstFrameNode(*iter);
    }

    return sideBarNode;
}

RefPtr<FrameNode> SideBarContainerPattern::GetFirstFrameNode(const RefPtr<UINode>& host) const
{
    CHECK_NULL_RETURN(host, nullptr);
    auto children = host->GetChildren();
    while (!children.empty()) {
        auto firstChild = children.front();
        auto firstChildNode = AceType::DynamicCast<FrameNode>(firstChild);
        if (firstChildNode) {
            return firstChildNode;
        }
        children = firstChild->GetChildren();
    }
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "SideBarContainer can't find child frameNode to set ZIndex");
    return nullptr;
}

RefPtr<FrameNode> SideBarContainerPattern::GetSideBarNodeOrFirstChild() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    const auto& children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return nullptr;
    }

    auto iter = children.rbegin();
    std::advance(iter, SIDE_BAR_INDEX);
    if (AceType::InstanceOf<NG::CustomNode>(*iter)) {
        auto sideBarNode = AceType::DynamicCast<CustomNode>(*iter);
        CHECK_NULL_RETURN(sideBarNode, nullptr);
        auto sideBarFirstChild = sideBarNode->GetChildren().front();
        CHECK_NULL_RETURN(sideBarFirstChild, nullptr);
        auto sideBarFirstChildNode = AceType::DynamicCast<FrameNode>(sideBarFirstChild);
        CHECK_NULL_RETURN(sideBarFirstChildNode, nullptr);
        return sideBarFirstChildNode;
    }
    auto sideBarNode = AceType::DynamicCast<FrameNode>(*iter);
    CHECK_NULL_RETURN(sideBarNode, nullptr);
    return sideBarNode;
}

RefPtr<FrameNode> SideBarContainerPattern::GetControlButtonNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto children = host->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::BUTTON_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        return nullptr;
    }
    return AceType::DynamicCast<FrameNode>(controlButtonNode);
}

RefPtr<FrameNode> SideBarContainerPattern::GetControlImageNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);

    auto children = host->GetChildren();
    if (children.empty()) {
        return nullptr;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::BUTTON_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        return nullptr;
    }

    auto buttonChildren = controlButtonNode->GetChildren();
    if (buttonChildren.empty()) {
        return nullptr;
    }

    auto imageNode = buttonChildren.front();
    if (imageNode->GetTag() != V2::IMAGE_ETS_TAG || !AceType::InstanceOf<FrameNode>(imageNode)) {
        return nullptr;
    }
    return AceType::DynamicCast<FrameNode>(imageNode);
}

RefPtr<FrameNode> SideBarContainerPattern::GetDividerNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return nullptr;
    }

    auto begin = children.rbegin();
    auto dividerNode = *(++begin);
    CHECK_NULL_RETURN(dividerNode, nullptr);
    if (dividerNode->GetTag() != V2::DIVIDER_ETS_TAG || !AceType::InstanceOf<FrameNode>(dividerNode)) {
        return nullptr;
    }

    return AceType::DynamicCast<FrameNode>(dividerNode);
}

void SideBarContainerPattern::OnUpdateSideBarAndContent(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto sideBarNode = GetSideBarNode(host);
    CHECK_NULL_VOID(sideBarNode);
    auto sideBarContext = sideBarNode->GetRenderContext();
    CHECK_NULL_VOID(sideBarContext);

    if (!sideBarContext->GetClipEdge().has_value() && !sideBarContext->GetClipShape().has_value()) {
        sideBarContext->SetClipToBounds(true);
    }

    auto contentNode = GetContentNode(host);
    CHECK_NULL_VOID(contentNode);
    auto contentContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentContext);
    if (!contentContext->GetClipEdge().has_value() && !contentContext->GetClipShape().has_value()) {
        contentContext->SetClipToBounds(true);
    }
}

void SideBarContainerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    CreateAndMountNodes();

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitPanEvent(gestureHub);

    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    OnUpdateShowSideBar(layoutProperty);
    OnUpdateShowControlButton(layoutProperty, host);
    OnUpdateShowDivider(layoutProperty, host);
    UpdateControlButtonIcon();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        OnUpdateSideBarAndContent(host);
    }

    CHECK_NULL_VOID(layoutProperty);
    if ((userSetSidebarWidth_ != layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE)) ||
        (layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE) == DEFAULT_SIDE_BAR_WIDTH)) {
        preSidebarWidth_.Reset();
        userSetSidebarWidth_ = layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE);
    }

    if (!hasInit_) {
        hasInit_ = true;
    }
}

void SideBarContainerPattern::CreateAndMountNodes()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE_WITHOUT_BUTTON_AND_DIVIDER) {
        return;
    }

    if (HasControlButton()) {
        UpdateDividerShadow();
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
        if (SystemProperties::GetSideBarContainerBlurEnable() &&
            Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            !renderContext->GetBackBlurStyle().has_value()) {
            BlurStyleOption blurStyleOption;
            blurStyleOption.blurStyle = BlurStyle::COMPONENT_THICK;
            renderContext->UpdateBackBlurStyle(blurStyleOption);
        }
    }
    host->RebuildRenderContextTree();
    CreateAndMountDivider(host);
    CreateAndMountControlButton(host);
    UpdateDividerShadow();
}

void SideBarContainerPattern::UpdateDividerShadow() const
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sidebarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sidebarTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!sidebarTheme->GetDividerShadowEnable()) {
        return;
    }

    auto sideBarContainerType = layoutProperty->GetSideBarContainerType().value_or(SideBarContainerType::EMBED);
    auto sidebarNode = GetSideBarNode(host);
    if (sidebarNode) {
        auto renderContext = sidebarNode->GetRenderContext();
        renderContext->UpdateZIndex(SideBarContainerType::EMBED == sideBarContainerType
                                        ? DEFAULT_SIDE_BAR_ZINDEX_EMBED
                                        : DEFAULT_SIDE_BAR_ZINDEX_OVERLAY);
    }
    auto dividerNode = GetDividerNode();
    if (dividerNode) {
        auto renderContext = dividerNode->GetRenderContext();
        renderContext->UpdateZIndex(SideBarContainerType::EMBED == sideBarContainerType
                                        ? DEFAULT_DIVIDER_ZINDEX_EMBED
                                        : DEFAULT_DIVIDER_ZINDEX_OVERLAY);
        renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowXS);
    }
    auto contentNode = GetContentNode(host);
    if (contentNode) {
        auto renderContext = contentNode->GetRenderContext();
        renderContext->UpdateZIndex(SideBarContainerType::EMBED == sideBarContainerType
                                        ? DEFAULT_CONTENT_ZINDEX_EMBED
                                        : DEFAULT_CONTENT_ZINDEX_OVERLAY);
    }
    auto controlBtnNode = GetControlButtonNode();
    if (controlBtnNode) {
        auto renderContext = controlBtnNode->GetRenderContext();
        renderContext->UpdateZIndex(DEFAULT_CONTROL_BUTTON_ZINDEX);
    }
}

void SideBarContainerPattern::SetSideBarActive(bool isActive, bool onlyJsActive) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sideBarNode = GetSideBarNode(host);
    CHECK_NULL_VOID(sideBarNode);
    sideBarNode->SetJSViewActive(isActive);
    if (!onlyJsActive) {
        sideBarNode->SetActive(isActive);
    }
}

void SideBarContainerPattern::CreateAndMountDivider(const RefPtr<NG::FrameNode>& parentNode)
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
    InitDividerMouseEvent(inputHub);

    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(true);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sideBarTheme);
    auto renderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (sideBarTheme->GetDividerShadowEnable()) {
        renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowXS);
    }
    renderContext->UpdateZIndex(DEFAULT_DIVIDER_ZINDEX_EMBED);
    dividerNode->MountToParent(parentNode);
    dividerNode->MarkModifyDone();
}

void SideBarContainerPattern::CreateAndMountControlButton(const RefPtr<NG::FrameNode>& parentNode)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sideBarTheme);

    auto buttonNode = CreateControlButton(sideBarTheme);
    CHECK_NULL_VOID(buttonNode);
    RegisterElementInfoCallBack(buttonNode);
    auto imgNode = CreateControlImage(sideBarTheme, parentNode);
    CHECK_NULL_VOID(imgNode);

    auto buttonHub = buttonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(buttonHub);
    auto gestureHub = buttonHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    SetHasControlButton(true);
    InitControlButtonTouchEvent(gestureHub);
    InitLongPressEvent(buttonNode);

    imgNode->MountToParent(buttonNode);
    buttonNode->MountToParent(parentNode);
    imgNode->MarkModifyDone();
    buttonNode->MarkModifyDone();
}

RefPtr<FrameNode> SideBarContainerPattern::CreateControlButton(const RefPtr<SideBarTheme>& sideBarTheme)
{
    CHECK_NULL_RETURN(sideBarTheme, nullptr);
    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    auto buttonRadius = sideBarTheme->GetControlButtonRadius();
    buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(buttonRadius));
    buttonLayoutProperty->UpdateCreateWithLabel(false);
    auto buttonRenderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(buttonRenderContext, nullptr);
    buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonRenderContext->UpdateZIndex(DEFAULT_CONTROL_BUTTON_ZINDEX);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    return buttonNode;
}

RefPtr<FrameNode> SideBarContainerPattern::CreateControlImage(
    const RefPtr<SideBarTheme>& sideBarTheme, const RefPtr<FrameNode>& parentNode)
{
    CHECK_NULL_RETURN(sideBarTheme, nullptr);
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
    imageInfo_ = info.value();
    auto imageLayoutProperty = imgNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(info.value());
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateAlignment(Alignment::CENTER);
    Dimension imageWidth;
    Dimension imageHeight;
    GetControlImageSize(imageWidth, imageHeight);
    CalcSize imageCalcSize((CalcLength(imageWidth)), CalcLength(imageHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    InitImageErrorCallback(sideBarTheme, imgNode);
    return imgNode;
}

void SideBarContainerPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!dragEvent_);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };

    dragEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };

    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto dividerGestureHub = dividerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    dividerGestureHub->AddPanEvent(dragEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void SideBarContainerPattern::CreateAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!controller_) {
        controller_ = CREATE_ANIMATOR(host->GetContextRefPtr());
    }

    auto weak = AceType::WeakClaim(this);
    if (!rightToLeftAnimation_) {
        rightToLeftAnimation_ =
            AceType::MakeRefPtr<CurveAnimation<float>>(RATIO_ZERO, RATIO_NEGATIVE, Curves::FRICTION);
        rightToLeftAnimation_->AddListener(Animation<float>::ValueCallback([weak](float value) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateSideBarPosition(value);
            }
        }));
    }

    if (!leftToRightAnimation_) {
        leftToRightAnimation_ =
            AceType::MakeRefPtr<CurveAnimation<float>>(RATIO_NEGATIVE, RATIO_ZERO, Curves::FRICTION);
        leftToRightAnimation_->AddListener(Animation<float>::ValueCallback([weak](float value) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateSideBarPosition(value);
            }
        }));
    }
}

void SideBarContainerPattern::InitControlButtonTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!controlButtonClickEvent_);

    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->inAnimation_) {
            pattern->SetControlButtonClick(true);
            pattern->DoAnimation();
        }
    };
    controlButtonClickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(controlButtonClickEvent_);
}

void SideBarContainerPattern::UpdateAnimDir()
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);

    switch (sideBarStatus_) {
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                animDir_ = SideBarAnimationDirection::LTR;
            } else {
                animDir_ = SideBarAnimationDirection::RTL;
            }
            break;
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::START) {
                animDir_ = SideBarAnimationDirection::RTL;
            } else {
                animDir_ = SideBarAnimationDirection::LTR;
            }
            break;
        default:
            break;
    }
}

void SideBarContainerPattern::DoAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (autoHide_) {
        sideBarStatus_ = SideBarStatus::HIDDEN;
    }

    SetSideBarActive(true, false);
    UpdateAnimDir();

    AnimationOption option = AnimationOption();
    option.SetDuration(SIDEBAR_DURATION);
    option.SetCurve(SIDEBAR_CURVE);
    option.SetFillMode(FillMode::FORWARDS);

    auto sideBarStatus = sideBarStatus_;
    sideBarStatus_ = SideBarStatus::CHANGING;
    UpdateControlButtonIcon();

    // fire before animation to include user changes in onChange event
    FireChangeEvent(sideBarStatus == SideBarStatus::HIDDEN);

    auto weak = AceType::WeakClaim(this);
    auto context = PipelineContext::GetCurrentContext();
    inAnimation_ = true;
    context->OpenImplicitAnimation(option, option.GetCurve(), [weak, sideBarStatus]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (sideBarStatus == SideBarStatus::HIDDEN) {
                pattern->SetSideBarStatus(SideBarStatus::SHOW);
                pattern->UpdateControlButtonIcon();
            } else {
                pattern->SetSideBarStatus(SideBarStatus::HIDDEN);
                pattern->UpdateControlButtonIcon();
                pattern->SetSideBarActive(false, false);
            }
            pattern->inAnimation_ = false;
        }
    });

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    auto realSideBarWidthPx = DimensionConvertToPx(realSideBarWidth_).value_or(0.0);
    if (sideBarPosition == SideBarPosition::START) {
        if (animDir_ == SideBarAnimationDirection::LTR) {
            currentOffset_ = 0.0f;
        } else {
            currentOffset_ = -realSideBarWidthPx - realDividerWidth_;
        }
    } else {
        if (animDir_ == SideBarAnimationDirection::LTR) {
            currentOffset_ = 0.0f + realDividerWidth_;
        } else {
            currentOffset_ = -realSideBarWidthPx;
        }
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    context->CloseImplicitAnimation();
}

void SideBarContainerPattern::HandlePanEventEnd()
{
    if (sideBarStatus_ == SideBarStatus::HIDDEN) {
        DoAnimation();
    }
}

void SideBarContainerPattern::UpdateSideBarPosition(float value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (sideBarStatus_ != SideBarStatus::CHANGING) {
        sideBarStatus_ = SideBarStatus::CHANGING;
        UpdateControlButtonIcon();
    }

    auto realSideBarWidthPx = DimensionConvertToPx(realSideBarWidth_).value_or(0.0);
    currentOffset_ = value * (realSideBarWidthPx + realDividerWidth_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SideBarContainerPattern::FireChangeEvent(bool isShow)
{
    auto sideBarContainerEventHub = GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(sideBarContainerEventHub);

    sideBarContainerEventHub->FireChangeEvent(isShow);

    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto inspectorId = host->GetInspectorId().value_or("");
        builder.SetId(inspectorId)
            .SetType(host->GetTag())
            .SetChecked(isShow)
            .SetDescription(host->GetAutoEventParamValue(""));
        Recorder::EventRecorder::Get().OnChange(std::move(builder));
    }
}

void SideBarContainerPattern::UpdateControlButtonIcon()
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto imgFrameNode = GetControlImageNode();
    CHECK_NULL_VOID(imgFrameNode);

    auto imgRenderContext = imgFrameNode->GetRenderContext();
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    std::optional<ImageSourceInfo> imgSourceInfo = std::nullopt;

    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sideBarTheme);
    Color controlButtonColor = sideBarTheme->GetControlImageColor();

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            imgSourceInfo = layoutProperty->GetControlButtonShowIconInfo();
            break;
        case SideBarStatus::HIDDEN:
            imgSourceInfo = layoutProperty->GetControlButtonHiddenIconInfo();
            break;
        case SideBarStatus::CHANGING:
            imgSourceInfo = layoutProperty->GetControlButtonSwitchingIconInfo();
            break;
        default:
            break;
    }

    if (!imgSourceInfo.has_value()) {
        imgSourceInfo = std::make_optional<ImageSourceInfo>();
        imgSourceInfo->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        imgSourceInfo->SetFillColor(controlButtonColor);
    }
    imageInfo_ = imgSourceInfo.value();
    imageLayoutProperty->UpdateImageSourceInfo(imgSourceInfo.value());
    imgFrameNode->MarkModifyDone();
}

bool SideBarContainerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<SideBarContainerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);

    realDividerWidth_ = layoutAlgorithm->GetRealDividerWidth();
    realSideBarWidth_ = layoutAlgorithm->GetRealSideBarWidth();
    realSideBarHeight_ = layoutAlgorithm->GetRealSideBarHeight();
    AddDividerHotZoneRect(layoutAlgorithm);

    if (needInitRealSideBarWidth_) {
        needInitRealSideBarWidth_ = false;
    }

    if (isControlButtonClick_) {
        isControlButtonClick_ = false;
    }

    if (autoHide_ != layoutAlgorithm->GetAutoHide()) {
        FireChangeEvent(layoutAlgorithm->GetSideBarStatus() == SideBarStatus::SHOW);
    }

    if (!inAnimation_) {
        SetSideBarActive(layoutAlgorithm->GetSideBarStatus() == SideBarStatus::SHOW, true);
    }

    adjustMaxSideBarWidth_ = layoutAlgorithm->GetAdjustMaxSideBarWidth();
    adjustMinSideBarWidth_ = layoutAlgorithm->GetAdjustMinSideBarWidth();
    type_ = layoutAlgorithm->GetSideBarContainerType();
    autoHide_ = layoutAlgorithm->GetAutoHide();

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    return paddingProperty != nullptr;
}

void SideBarContainerPattern::AddDividerHotZoneRect(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm)
{
    CHECK_NULL_VOID(layoutAlgorithm);
    if (realDividerWidth_ < 0.0f) {
        return;
    }

    auto dividerFrameNode = GetDividerNode();
    CHECK_NULL_VOID(dividerFrameNode);
    auto geometryNode = dividerFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto dividerHeight = geometryNode->GetFrameSize().Height();
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(-DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_VP.ConvertToPx());
    SizeF hotZoneSize;
    auto baseWidth = NearZero(realDividerWidth_, 0.0f) ?
        DEFAULT_DIVIDER_STROKE_WIDTH.ConvertToPx() : realDividerWidth_;
    hotZoneSize.SetWidth(baseWidth + DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_VALUE *
                                                 DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_VP.ConvertToPx());
    hotZoneSize.SetHeight(dividerHeight);

    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize.Width()), Dimension(hotZoneSize.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));

    std::vector<DimensionRect> mouseRegion;
    mouseRegion.emplace_back(hotZoneRegion);

    dividerFrameNode->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    auto dividerGestureHub = dividerFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    dividerGestureHub->SetMouseResponseRegion(mouseRegion);

    auto dragRectOffset = layoutAlgorithm->GetSideBarOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_REGION.ConvertToPx());
    dragRect_.SetOffset(dragRectOffset);

    // divider drag rect height = dividerHeight - divider start margin - divider end margin
    dragRect_.SetSize(SizeF(DEFAULT_DRAG_REGION.ConvertToPx() * DEFAULT_DOUBLE_DRAG_REGION + realDividerWidth_,
        dividerHeight));

    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragRect_.Width(), DimensionUnit::PX),
        Dimension(dragRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dividerGestureHub->SetResponseRegion(responseRegion);
}

void SideBarContainerPattern::HandleDragStart()
{
    if (!isDividerDraggable_ || sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }
    isInDividerDrag_ = true;
    SetMouseStyle(MouseFormat::RESIZE_LEFT_RIGHT);
    preSidebarWidth_ = realSideBarWidth_;
}

void SideBarContainerPattern::HandleDragUpdate(float xOffset)
{
    if (sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() < PLATFORM_VERSION_TEN) {
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);

        auto frameSize = geometryNode->GetFrameSize();
        auto parentWidth = frameSize.Width();
        auto constraint = layoutProperty->GetLayoutConstraint();
        auto scaleProperty = constraint->scaleProperty;
        minSideBarWidth_ = ConvertToPx(adjustMinSideBarWidth_, scaleProperty, parentWidth).value_or(0);
        maxSideBarWidth_ = ConvertToPx(adjustMaxSideBarWidth_, scaleProperty, parentWidth).value_or(0);
    }

    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    bool isSideBarStart = sideBarPosition == SideBarPosition::START;

    bool isPercent = realSideBarWidth_.Unit() == DimensionUnit::PERCENT;
    auto preSidebarWidthPx = DimensionConvertToPx(preSidebarWidth_).value_or(0.0);
    auto sideBarLine = preSidebarWidthPx + (isSideBarStart ? xOffset : -xOffset);

    if (sideBarLine > minSideBarWidth_ && sideBarLine < maxSideBarWidth_) {
        realSideBarWidth_ = isPercent ? ConvertPxToPercent(sideBarLine) : Dimension(sideBarLine, DimensionUnit::PX);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    if (sideBarLine >= maxSideBarWidth_) {
        realSideBarWidth_ =
            isPercent ? ConvertPxToPercent(maxSideBarWidth_) : Dimension(maxSideBarWidth_, DimensionUnit::PX);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    auto halfDragRegionWidth = dragRect_.Width() / 2;
    if (sideBarLine > minSideBarWidth_ - halfDragRegionWidth) {
        realSideBarWidth_ =
            isPercent ? ConvertPxToPercent(minSideBarWidth_) : Dimension(minSideBarWidth_, DimensionUnit::PX);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    realSideBarWidth_ =
        isPercent ? ConvertPxToPercent(minSideBarWidth_) : Dimension(minSideBarWidth_, DimensionUnit::PX);

    auto autoHideProperty = layoutProperty->GetAutoHide().value_or(true);
    if (autoHideProperty) {
        DoAnimation();
    }
}

void SideBarContainerPattern::HandleDragEnd()
{
    isInDividerDrag_ = false;
    SetMouseStyle(MouseFormat::DEFAULT);
    if (!isDividerDraggable_ || sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }
    preSidebarWidth_ = realSideBarWidth_;
}

void SideBarContainerPattern::InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(inputHub);
    CHECK_NULL_VOID(!hoverEvent_);

    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        CHECK_NULL_VOID(!dividerMouseEvent_);
        auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->OnDividerMouseEvent(info);
            }
        };
        dividerMouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnMouseEvent(dividerMouseEvent_);
    }

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void SideBarContainerPattern::OnDividerMouseEvent(MouseInfo& info)
{
    // release the mouse button, to check if still in the divider's region
    if (info.GetAction() != MouseAction::RELEASE) {
        return;
    }
    auto dividerFrameNode = GetDividerNode();
    CHECK_NULL_VOID(dividerFrameNode);
    auto defaultRect = RectF();
    auto responseMouseRegionList = dividerFrameNode->GetResponseRegionList(defaultRect,
        static_cast<int32_t>(SourceType::MOUSE));
    auto localParentPoint = PointF(static_cast<float>(info.GetLocalLocation().GetX()),
        static_cast<float>(info.GetLocalLocation().GetY()));

    if (dividerFrameNode->InResponseRegionList(localParentPoint, responseMouseRegionList)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "sideBarContainer Divider is out of region.");
    SetMouseStyle(MouseFormat::DEFAULT);
}

void SideBarContainerPattern::OnHover(bool isHover)
{
    if (isInDividerDrag_) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SIDEBAR, "sideBarContainer onHover");
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);
    auto minSideBarWidth = layoutProperty->GetMinSideBarWidthValue(DEFAULT_MIN_SIDE_BAR_WIDTH);
    auto maxSideBarWidth = layoutProperty->GetMaxSideBarWidthValue(DEFAULT_MAX_SIDE_BAR_WIDTH);
    if (Negative(dividerStrokeWidth.Value()) || GreatOrEqual(minSideBarWidth.Value(), maxSideBarWidth.Value())) {
        isDividerDraggable_ = false;
        return;
    }
    isDividerDraggable_ = true;

    MouseFormat format = isHover ? MouseFormat::RESIZE_LEFT_RIGHT : MouseFormat::DEFAULT;
    if (sideBarStatus_ == SideBarStatus::SHOW) {
        SetMouseStyle(format);
    }
}

SideBarPosition SideBarContainerPattern::GetSideBarPositionWithRtl(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty)
{
    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    if (layoutProperty->GetLayoutDirection() == TextDirection::RTL ||
        AceApplicationInfo::GetInstance().IsRightToLeft()) {
        sideBarPosition = (sideBarPosition == SideBarPosition::START) ? SideBarPosition::END : SideBarPosition::START;
    }
    return sideBarPosition;
}

void SideBarContainerPattern::OnLanguageConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isRightToLeft_ != AceApplicationInfo::GetInstance().IsRightToLeft()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
    }
}

RefPtr<NodePaintMethod> SideBarContainerPattern::CreateNodePaintMethod()
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    bool needClipPadding = paddingProperty != nullptr;
    auto paintMethod = MakeRefPtr<SideBarContainerPaintMethod>();
    paintMethod->SetNeedClipPadding(needClipPadding);
    return paintMethod;
}

std::optional<float> SideBarContainerPattern::DimensionConvertToPx(const Dimension& value) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, std::nullopt);
    auto frameSize = geometryNode->GetFrameSize();
    auto parentWidth = frameSize.Width();
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    return ConvertToPx(value, scaleProperty, parentWidth);
}

Dimension SideBarContainerPattern::ConvertPxToPercent(float value) const
{
    auto result = Dimension(0.0, DimensionUnit::PERCENT);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, result);

    auto frameSize = geometryNode->GetFrameSize();
    auto parentWidth = frameSize.Width();
    if (!NearZero(parentWidth)) {
        result = Dimension(value / parentWidth, DimensionUnit::PERCENT);
    }

    return result;
}

void SideBarContainerPattern::InitLongPressEvent(const RefPtr<FrameNode>& buttonNode)
{
    if (longPressEvent_) {
        return;
    }

    auto buttonHub = buttonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(buttonHub);
    auto gestureHub = buttonHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto longPressTask = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleLongPressEvent();
        }
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressTask));
    gestureHub->SetLongPressEvent(longPressEvent_, false, false);

    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    CHECK_NULL_VOID(longPressRecognizer);
    if (!longPressActionEnd_) {
        auto longPressActionEnd = [weak = WeakClaim(this)] (GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleLongPressActionEnd();
        };
        longPressActionEnd_ = longPressActionEnd;
    }
    longPressRecognizer->SetOnActionEnd(longPressActionEnd_);
}

void SideBarContainerPattern::HandleLongPressEvent()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    float scale = pipeline->GetFontScale();
    if (LessNotEqual(scale, AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        return;
    }
    ShowDialogWithNode();
}

void SideBarContainerPattern::HandleLongPressActionEnd()
{
    if (!isDialogShow_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode_);
    dialogNode_ = nullptr;
    isDialogShow_ = false;
}

void SideBarContainerPattern::ShowDialogWithNode()
{
    if (isDialogShow_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_VOID(buttonNode);
    auto accessibilityProperty = buttonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto text = accessibilityProperty->GetAccessibilityText();

    dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(text, imageInfo_);

    isDialogShow_ = true;
}

void SideBarContainerPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "mark need retrieve sidebar property because of window rotation or resize");
    MarkNeedInitRealSideBarWidth(true);
}

void SideBarContainerPattern::RegisterElementInfoCallBack(const RefPtr<FrameNode>& buttonNode)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    CHECK_NULL_VOID(buttonNode);
    auto accessibilityProperty = buttonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto callBack = [weak = WeakClaim(this)] (Accessibility::ExtraElementInfo& extraElementInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto showSideBar = pattern->GetShowSideBar();
        extraElementInfo.SetExtraElementInfo(
            "SideBarContainerStates", static_cast<int32_t>(showSideBar));
    };
    accessibilityProperty->SetRelatedElementInfoCallback(callBack);
#endif
}

void SideBarContainerPattern::SetAccessibilityEvent()
{
    auto controlButton = GetControlButtonNode();
    CHECK_NULL_VOID(controlButton);
    // use TEXT_CHANGE event to report information update
    controlButton->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, "", "");
}

void SideBarContainerPattern::InitImageErrorCallback(const RefPtr<SideBarTheme>& sideBarTheme,
    const RefPtr<FrameNode>& imgNode)
{
    auto eventHub = imgNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto errorCallback = [weakPattern = WeakClaim(this), weakNode = WeakClaim(RawPtr(imgNode)),
        weakTheme = WeakClaim(RawPtr(sideBarTheme))] (const LoadImageFailEvent& info) {
        auto imgNode = weakNode.Upgrade();
        CHECK_NULL_VOID(imgNode);
        auto imageLayoutProperty = imgNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
        if (!imageSourceInfo.has_value()) {
            return;
        }
        auto infoValue = imageSourceInfo.value();
        infoValue.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        auto sideBarTheme = weakTheme.Upgrade();
        CHECK_NULL_VOID(sideBarTheme);
        auto controlButtonColor = sideBarTheme->GetControlImageColor();
        infoValue.SetFillColor(controlButtonColor);
        imageLayoutProperty->UpdateImageSourceInfo(infoValue);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetImageInfo(infoValue);
        imgNode->MarkModifyDone();
    };
    eventHub->SetOnError(errorCallback);
}

void SideBarContainerPattern::SetMouseStyle(MouseFormat format)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto frameNodeId = host->GetId();
    int32_t windowId = static_cast<int32_t>(pipeline->GetFocusWindowId());
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = static_cast<int32_t>(WindowSceneHelper::GetFocusSystemWindowId(host));
#endif
    pipeline->SetMouseStyleHoldNode(frameNodeId);
    pipeline->ChangeMouseStyle(frameNodeId, format, windowId);
    pipeline->FreeMouseStyleHoldNode(frameNodeId);
}
} // namespace OHOS::Ace::NG
