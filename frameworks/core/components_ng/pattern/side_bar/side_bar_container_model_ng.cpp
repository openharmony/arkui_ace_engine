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

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
static Dimension DEFAULT_MIN_CONTENT_WIDTH = 0.0_vp;
constexpr static int32_t PLATFORM_VERSION_TEN = 10;
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;

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
bool SideBarContainerModelNG::sideBarWidthDoubleBind_ = false;

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
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SIDE_BAR_ETS_TAG, nodeId);
    auto sideBarContainerNode = FrameNode::GetOrCreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SideBarContainerPattern>(); });

    CHECK_NULL_VOID(sideBarContainerNode);

    stack->Push(sideBarContainerNode);
    auto pattern = sideBarContainerNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRightToLeftMode(AceApplicationInfo::GetInstance().IsRightToLeft());
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

void SideBarContainerModelNG::ParseAndSetWidth(WidthType widthType, Dimension& width, bool isDoubleBind)
{
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            SetSideBarWidth(width.IsNonNegative() ? width : DEFAULT_SIDE_BAR_WIDTH, isDoubleBind);
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

void SideBarContainerModelNG::SetSideBarWidth(const Dimension& sideBarWidth, bool isDoubleBind)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    sideBarWidthDoubleBind_ = isDoubleBind;
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth);
}

void SideBarContainerModelNG::SetMinSideBarWidth(const Dimension& minSideBarWidth)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth);
}

void SideBarContainerModelNG::SetMaxSideBarWidth(const Dimension& maxSideBarWidth)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth();
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth);
}

void SideBarContainerModelNG::ParseAndSetWidth(WidthType widthType, const RefPtr<ResourceObject>& resObj)
{
    CalcDimension sideBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, sideBarWidth);
    ParseAndSetWidth(widthType, sideBarWidth, false);
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            SetSideBarWidth(resObj);
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            SetMinSideBarWidth(resObj);
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            SetMaxSideBarWidth(resObj);
            break;
        default:
            break;
    }
}

void SideBarContainerModelNG::SetSideBarWidth(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateSideBarWidthFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->MarkNeedInitRealSideBarWidth(true);
        CalcDimension sideBarWidth;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, sideBarWidth);
        sideBarWidth = sideBarWidth.IsNonNegative() ? sideBarWidth : DEFAULT_SIDE_BAR_WIDTH;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.sideBarWidth", resObj, std::move(updateSideBarWidthFunc));
}

void SideBarContainerModelNG::SetMinSideBarWidth(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateMinSideBarWidthFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->MarkNeedInitRealSideBarWidth(true);
        CalcDimension minSideBarWidth;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, minSideBarWidth);
        minSideBarWidth = minSideBarWidth.IsNonNegative() ? minSideBarWidth : DEFAULT_MIN_SIDE_BAR_WIDTH;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.minSideBarWidth", resObj, std::move(updateMinSideBarWidthFunc));
}

void SideBarContainerModelNG::SetMaxSideBarWidth(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateMaxSideBarWidthFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->MarkNeedInitRealSideBarWidth(true);
        CalcDimension maxSideBarWidth;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, maxSideBarWidth);
        maxSideBarWidth = maxSideBarWidth.IsNonNegative() ? maxSideBarWidth : DEFAULT_MAX_SIDE_BAR_WIDTH;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.maxSideBarWidth", resObj, std::move(updateMaxSideBarWidthFunc));
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

void SideBarContainerModelNG::ResetControlButtonLeft()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(SideBarContainerLayoutProperty, ControlButtonLeft, PROPERTY_UPDATE_LAYOUT);
}

void SideBarContainerModelNG::SetControlButtonTop(const Dimension& top)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top);
}

void SideBarContainerModelNG::SetControlButtonShowIconInfo(const std::string& showIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonShowIconInfo = CreateSourceInfo(showIconStr, isPixelMap, pixMap);
    if (controlButtonShowIconInfo.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonShowIconInfo, controlButtonShowIconInfo);
    }
}

void SideBarContainerModelNG::SetControlButtonHiddenIconInfo(const std::string& hiddenIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonHiddenIconInfo = CreateSourceInfo(hiddenIconStr, isPixelMap, pixMap);
    if (controlButtonHiddenIconInfo.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, controlButtonHiddenIconInfo);
    }
}

void SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(const std::string& switchingIconStr,
    bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonSwitchingIconInfo = CreateSourceInfo(switchingIconStr, isPixelMap, pixMap);
    if (controlButtonSwitchingIconInfo.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, controlButtonSwitchingIconInfo);
    }
}

void SideBarContainerModelNG::SetControlButtonShowIconInfo(
    const RefPtr<ResourceObject>& showIconResObj, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    std::string showIconStr;
    ResourceParseUtils::ParseResMedia(showIconResObj, showIconStr);
    SetControlButtonShowIconInfo(showIconStr, isPixelMap, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateShowIconFunc = [weakFrameNode = AceType::WeakClaim(frameNode), isPixelMap,
                                    weakPixMap = AceType::WeakClaim(AceType::RawPtr(pixMap))](
                                    const RefPtr<ResourceObject>& resObj) {
        std::string showIconStr;
        ResourceParseUtils::ParseResMedia(resObj, showIconStr);
        auto pixMap = weakPixMap.Upgrade();
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto controlButtonShowIconInfo = CreateSourceInfo(showIconStr, isPixelMap, pixMap);
        if (controlButtonShowIconInfo.IsValid()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                SideBarContainerLayoutProperty, ControlButtonShowIconInfo, controlButtonShowIconInfo, frameNode);
        }
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.buttonIconOptions.shown", showIconResObj, std::move(updateShowIconFunc));
}

void SideBarContainerModelNG::SetControlButtonHiddenIconInfo(
    const RefPtr<ResourceObject>& hiddenIconResObj, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    std::string hiddenIconStr;
    ResourceParseUtils::ParseResMedia(hiddenIconResObj, hiddenIconStr);
    SetControlButtonHiddenIconInfo(hiddenIconStr, isPixelMap, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateHiddenIconFunc = [weakFrameNode = AceType::WeakClaim(frameNode), isPixelMap,
                                      weakPixMap = AceType::WeakClaim(AceType::RawPtr(pixMap))](
                                      const RefPtr<ResourceObject>& resObj) {
        std::string hiddenIconStr;
        ResourceParseUtils::ParseResMedia(resObj, hiddenIconStr);
        auto pixMap = weakPixMap.Upgrade();
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto controlButtonHiddenIconInfo = CreateSourceInfo(hiddenIconStr, isPixelMap, pixMap);
        if (controlButtonHiddenIconInfo.IsValid()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, controlButtonHiddenIconInfo, frameNode);
        }
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.buttonIconOptions.hidden", hiddenIconResObj, std::move(updateHiddenIconFunc));
}

void SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(
    const RefPtr<ResourceObject>& switchingIconResObj, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    std::string switchingIconStr;
    ResourceParseUtils::ParseResMedia(switchingIconResObj, switchingIconStr);
    SetControlButtonSwitchingIconInfo(switchingIconStr, isPixelMap, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateSwitchingIconFunc = [weakFrameNode = AceType::WeakClaim(frameNode), isPixelMap,
                                         weakPixMap = AceType::WeakClaim(AceType::RawPtr(pixMap))](
                                         const RefPtr<ResourceObject>& resObj) {
        std::string switchingIconStr;
        ResourceParseUtils::ParseResMedia(resObj, switchingIconStr);
        auto pixMap = weakPixMap.Upgrade();
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto controlButtonSwitchingIconInfo = CreateSourceInfo(switchingIconStr, isPixelMap, pixMap);
        if (controlButtonSwitchingIconInfo.IsValid()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo,
                controlButtonSwitchingIconInfo, frameNode);
        }
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(
        "sideBarContainer.buttonIconOptions.switching", switchingIconResObj, std::move(updateSwitchingIconFunc));
}

void SideBarContainerModelNG::ResetControlButtonIconInfo()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonShowIconInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, PROPERTY_UPDATE_LAYOUT);
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

void SideBarContainerModelNG::SetDividerStrokeWidth(const RefPtr<ResourceObject>& strokeWidthResObj)
{
    CalcDimension strokeWidth;
    ResourceParseUtils::ParseResDimensionVpNG(strokeWidthResObj, strokeWidth);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateDividerStrokeWidthFunc = [weakFrameNode = AceType::WeakClaim(frameNode)](
                                              const RefPtr<ResourceObject>& strokeWidthResObj) {
        CalcDimension strokeWidth;
        ResourceParseUtils::ParseResDimensionVpNG(strokeWidthResObj, strokeWidth);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(
        "sideBarContainer.dividerStyle.strokeWidth", strokeWidthResObj, std::move(updateDividerStrokeWidthFunc));
}

void SideBarContainerModelNG::SetDividerColor(const RefPtr<ResourceObject>& colorResObj)
{
    Color color;
    ResourceParseUtils::ParseResColor(colorResObj, color);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateDividerColorFunc = [weakFrameNode = AceType::WeakClaim(frameNode)](
                                        const RefPtr<ResourceObject>& colorResObj) {
        Color color;
        ResourceParseUtils::ParseResColor(colorResObj, color);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.dividerStyle.color", colorResObj, std::move(updateDividerColorFunc));
}

void SideBarContainerModelNG::SetDividerStartMargin(const RefPtr<ResourceObject>& startMarginResObj)
{
    CalcDimension startMargin;
    ResourceParseUtils::ParseResDimensionVpNG(startMarginResObj, startMargin);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateDividerStartMarginFunc = [weakFrameNode = AceType::WeakClaim(frameNode)](
                                              const RefPtr<ResourceObject>& startMarginResObj) {
        CalcDimension startMargin;
        ResourceParseUtils::ParseResDimensionVpNG(startMarginResObj, startMargin);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(
        "sideBarContainer.dividerStyle.startMargin", startMarginResObj, std::move(updateDividerStartMarginFunc));
}

void SideBarContainerModelNG::SetDividerEndMargin(const RefPtr<ResourceObject>& endMarginResObj)
{
    CalcDimension endMargin;
    ResourceParseUtils::ParseResDimensionVpNG(endMarginResObj, endMargin);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateDividerEndMarginFunc = [weakFrameNode = AceType::WeakClaim(frameNode)](
                                            const RefPtr<ResourceObject>& endMarginResObj) {
        CalcDimension endMargin;
        ResourceParseUtils::ParseResDimensionVpNG(endMarginResObj, endMargin);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(
        "sideBarContainer.dividerStyle.endMargin", endMarginResObj, std::move(updateDividerEndMarginFunc));
}

void SideBarContainerModelNG::SetMinContentWidth(const Dimension& minContentWidth)
{
    if (minContentWidth.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, DEFAULT_MIN_CONTENT_WIDTH);
    }
}

void SideBarContainerModelNG::SetMinContentWidth(const RefPtr<ResourceObject>& resObj)
{
    CalcDimension minContentWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, minContentWidth);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto&& updateMinContentFunc = [weakFrameNode = AceType::WeakClaim(frameNode)](
                                      const RefPtr<ResourceObject>& resObj) {
        CalcDimension minContentWidth;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, minContentWidth);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth, frameNode);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("sideBarContainer.minContentWidth", resObj, std::move(updateMinContentFunc));
}

void SideBarContainerModelNG::SetOnChange(std::function<void(const bool)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<SideBarContainerEventHub>();
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
    auto eventHub = frameNode->GetOrCreateEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void SideBarContainerModelNG::SetOnChange(FrameNode* frameNode, std::function<void(const bool)>&& onChange)
{
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SideBarContainerModelNG::SetOnSideBarWidthChangeEvent(OnSideBarWidthChangeEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSideBarWidthChangeEvent(std::move(event));
}

void SideBarContainerModelNG::SetSideBarWidth(FrameNode* frameNode, const Dimension& sideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarWidth, sideBarWidth, frameNode);
}

void SideBarContainerModelNG::SetMinSideBarWidth(FrameNode* frameNode, const Dimension& minSideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinSideBarWidth, minSideBarWidth, frameNode);
}

void SideBarContainerModelNG::SetControlButtonWidth(FrameNode* frameNode, const Dimension& width)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, width, frameNode);
}

void SideBarContainerModelNG::SetControlButtonHeight(FrameNode* frameNode, const Dimension& height)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, height, frameNode);
}

void SideBarContainerModelNG::SetControlButtonLeft(FrameNode* frameNode, const Dimension& left)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonLeft, left, frameNode);
}

void SideBarContainerModelNG::SetControlButtonTop(FrameNode* frameNode, const Dimension& top)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, top, frameNode);
}

void SideBarContainerModelNG::SetControlButtonShowIconInfo(
    FrameNode* frameNode, const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonShowIconInfo = CreateSourceInfo(showIconStr, isPixelMap, pixMap);
    if (controlButtonShowIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonShowIconInfo, controlButtonShowIconInfo, frameNode);
    }
}

void SideBarContainerModelNG::SetControlButtonHiddenIconInfo(
    FrameNode* frameNode, const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonHiddenIconInfo = CreateSourceInfo(hiddenIconStr, isPixelMap, pixMap);
    if (controlButtonHiddenIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, controlButtonHiddenIconInfo, frameNode);
    }
}

void SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(
    FrameNode* frameNode, const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap)
{
    auto controlButtonSwitchingIconInfo = CreateSourceInfo(switchingIconStr, isPixelMap, pixMap);
    if (controlButtonSwitchingIconInfo.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, controlButtonSwitchingIconInfo, frameNode);
    }
}

void SideBarContainerModelNG::MarkNeedInitRealSideBarWidth(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedInitRealSideBarWidth(true);
}

void SideBarContainerModelNG::SetShowControlButton(FrameNode* frameNode, bool showControlButton)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowControlButton, showControlButton, frameNode);
}

void SideBarContainerModelNG::SetAutoHide(FrameNode* frameNode, bool autoHide)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, AutoHide, autoHide, frameNode);
}

void SideBarContainerModelNG::SetMaxSideBarWidth(FrameNode* frameNode, const Dimension& maxSideBarWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsDoubleBindBlock(pattern)) {
        return;
    }
    MarkNeedInitRealSideBarWidth(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MaxSideBarWidth, maxSideBarWidth, frameNode);
}

void SideBarContainerModelNG::SetMinContentWidth(FrameNode* frameNode, const Dimension& minContentWidth)
{
    if (minContentWidth.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, MinContentWidth, minContentWidth, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SideBarContainerLayoutProperty, MinContentWidth, DEFAULT_MIN_CONTENT_WIDTH, frameNode);
    }
}

void SideBarContainerModelNG::SetSideBarPosition(FrameNode* frameNode, SideBarPosition sideBarPosition)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, SideBarPosition, sideBarPosition, frameNode);
}

void SideBarContainerModelNG::SetShowSideBar(FrameNode* frameNode, bool isShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ShowSideBar, isShow, frameNode);
}

void SideBarContainerModelNG::SetDividerStrokeWidth(FrameNode* frameNode, const Dimension& strokeWidth)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStrokeWidth, strokeWidth, frameNode);
}

void SideBarContainerModelNG::SetDividerColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerColor, color, frameNode);
}

void SideBarContainerModelNG::SetDividerStartMargin(FrameNode* frameNode, const Dimension& startMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerStartMargin, startMargin, frameNode);
}

void SideBarContainerModelNG::SetDividerEndMargin(FrameNode* frameNode, const Dimension& endMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, DividerEndMargin, endMargin, frameNode);
}

void SideBarContainerModelNG::ResetControlButtonLeft(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(SideBarContainerLayoutProperty, ControlButtonLeft,
        PROPERTY_UPDATE_LAYOUT, frameNode);
}

void SideBarContainerModelNG::ResetControlButtonIconInfo(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonShowIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, PROPERTY_UPDATE_LAYOUT, frameNode);
}

void SideBarContainerModelNG::ResetControlButton()
{
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonWidth, DEFAULT_CONTROL_BUTTON_WIDTH);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonHeight, DEFAULT_CONTROL_BUTTON_HEIGHT);
    ACE_UPDATE_LAYOUT_PROPERTY(SideBarContainerLayoutProperty, ControlButtonTop, DEFAULT_CONTROL_BUTTON_TOP);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(SideBarContainerLayoutProperty, ControlButtonLeft, PROPERTY_UPDATE_LAYOUT);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonShowIconInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonHiddenIconInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(
        SideBarContainerLayoutProperty, ControlButtonSwitchingIconInfo, PROPERTY_UPDATE_LAYOUT);
}

bool SideBarContainerModelNG::IsDoubleBindBlock(const RefPtr<SideBarContainerPattern>& sideBarContainerPattern)
{
    return sideBarWidthDoubleBind_ && sideBarContainerPattern->GetIsInDividerDrag();
}
} // namespace OHOS::Ace::NG
