/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "ui/base/utils/utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_impl.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/interfaces/native/node/side_bar_container_modifier.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::SideBarContainerModelImpl* GetSideBarContainerModelImpl()
{
    static Framework::SideBarContainerModelImpl instance;
    return &instance;
}
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
const Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
const Dimension DEFAULT_SIDE_BAR_WIDTH_V10 = 240.0_vp;
const Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
const Dimension DEFAULT_MIN_SIDE_BAR_WIDTH_V10 = 240.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
const Dimension DEFAULT_SIDE_BAR_CONTAINER_MAX_SIDE_BAR_WIDTH(280.0, DimensionUnit::VP);
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
const bool DEFAULT_SHOW_SIDE_BAR = true;
const bool DEFAULT_SHOW_CONTROL_BUTTON = true;
const bool DEFAULT_AUTO_HIDE = true;
constexpr SideBarPosition DEFAULT_SIDE_BAR_POSITION = SideBarPosition::START;
constexpr uint32_t DEFAULT_SIDE_BAR_DIVIDER_COLOR = 0x08000000;
const Dimension DEFAULT_START_MARGIN(0.0, DimensionUnit::VP);
const Dimension DEFAULT_END_MARGIN(0.0, DimensionUnit::VP);

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetSideBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* sideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.sideBarWidth");
    Dimension sideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !sideBarWidthPtr) {
        SideBarContainerModelNG::SetSideBarWidth(frameNode, sideBarWidthDimension);
    } else {
        auto* sideBarWidth = reinterpret_cast<ResourceObject*>(sideBarWidthPtr);
        auto sideBarWidthObj = AceType::Claim(sideBarWidth);
        SideBarContainerModelNG::SetSideBarWidth(frameNode, sideBarWidthObj);
    }
}

void ResetSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.sideBarWidth");
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH);
}

void SetMinSideBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* minSideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minSideBarWidth");
    Dimension minSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !minSideBarWidthPtr) {
        SideBarContainerModelNG::SetMinSideBarWidth(frameNode, minSideBarWidthDimension);
    } else {
        auto* minSideBarWidth = reinterpret_cast<ResourceObject*>(minSideBarWidthPtr);
        auto minSideBarWidthObj = AceType::Claim(minSideBarWidth);
        SideBarContainerModelNG::SetMinSideBarWidth(frameNode, minSideBarWidthObj);
    }
}

void ResetMinSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minSideBarWidth");
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH);
}

void SetControlButton(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valueLength,
    const struct ArkUIIconsStruct* iconsStruct, void* iconsShownPtr, void* iconsHiddenPtr, void* iconsSwitchingPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.shown");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.hidden");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.switching");
    Dimension left = Dimension(values[0], DimensionUnit::VP);
    Dimension top = Dimension(values[1], DimensionUnit::VP);
    Dimension width = Dimension(values[2], DimensionUnit::VP);
    Dimension height = Dimension(values[3], DimensionUnit::VP);
    SideBarContainerModelNG::SetControlButtonLeft(frameNode, left);
    SideBarContainerModelNG::SetControlButtonTop(frameNode, top);
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, width);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, height);
    CHECK_NULL_VOID(iconsStruct);
    if (iconsStruct->HiddenIconInfo) {
        SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, iconsStruct->HiddenIconInfo, false, nullptr);
    }
    if (iconsStruct->ShowIconInfo) {
        SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, iconsStruct->ShowIconInfo, false, nullptr);
    }
    if (iconsStruct->SwitchingIconInfo) {
        SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(
            frameNode, iconsStruct->SwitchingIconInfo, false, nullptr);
    }
    if (SystemProperties::ConfigChangePerform() && iconsShownPtr) {
        auto* iconsShown = reinterpret_cast<ResourceObject*>(iconsShownPtr);
        auto iconsShownObj = AceType::Claim(iconsShown);
        SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, iconsShownObj, false, nullptr);
    }
    if (SystemProperties::ConfigChangePerform() && iconsHiddenPtr) {
        auto* iconsHidden = reinterpret_cast<ResourceObject*>(iconsHiddenPtr);
        auto iconsHiddenObj = AceType::Claim(iconsHidden);
        SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, iconsHiddenObj, false, nullptr);
    }
    if (SystemProperties::ConfigChangePerform() && iconsSwitchingPtr) {
        auto* iconsSwitching = reinterpret_cast<ResourceObject*>(iconsSwitchingPtr);
        auto iconsSwitchingObj = AceType::Claim(iconsSwitching);
        SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(frameNode, iconsSwitchingObj, false, nullptr);
    }
}

void ResetControlButton(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.shown");
        SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.hidden");
        SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.switching");
        SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
        SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
        SideBarContainerModelNG::ResetControlButtonLeft(frameNode);
        SideBarContainerModelNG::SetControlButtonTop(frameNode, DEFAULT_CONTROL_BUTTON_TOP);
        SideBarContainerModelNG::ResetControlButtonIconInfo(frameNode);
        return;
    }
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
}

void SetShowControlButton(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, isShow);
}

void ResetShowControlButton(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, DEFAULT_SHOW_CONTROL_BUTTON);
}

void SetAutoHide(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, static_cast<bool>(value));
}

void ResetAutoHide(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, DEFAULT_AUTO_HIDE);
}

void SetSideBarContainerMaxSideBarWidth(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* maxSideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.maxSideBarWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !maxSideBarWidthPtr) {
        SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, maxSideBarWidthDimension);
    } else {
        auto* maxSideBarWidth = reinterpret_cast<ResourceObject*>(maxSideBarWidthPtr);
        auto maxSideBarWidthObj = AceType::Claim(maxSideBarWidth);
        SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, maxSideBarWidthObj);
    }
}

void ResetSideBarContainerMaxSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.maxSideBarWidth");
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, DEFAULT_SIDE_BAR_CONTAINER_MAX_SIDE_BAR_WIDTH);
}

void SetSideBarContainerMinContentWidth(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* minContentWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minContentWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !minContentWidthPtr) {
        SideBarContainerModelNG::SetMinContentWidth(frameNode, maxSideBarWidthDimension);
    } else {
        auto* minContentWidth = reinterpret_cast<ResourceObject*>(minContentWidthPtr);
        auto minContentWidthObj = AceType::Claim(minContentWidth);
        SideBarContainerModelNG::SetMinContentWidth(frameNode, minContentWidthObj);
    }
}

void ResetSideBarContainerMinContentWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minContentWidth");
    SideBarContainerModelNG::SetMinContentWidth(frameNode, -1.0_vp);
}

void SetSideBarPosition(ArkUINodeHandle node, ArkUI_Int32 sideBarPosition)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, static_cast<SideBarPosition>(sideBarPosition));
}

void ResetSideBarPosition(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, DEFAULT_SIDE_BAR_POSITION);
}

void SetShowSideBar(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, isShow);
}

void ResetShowSideBar(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, DEFAULT_SHOW_SIDE_BAR);
}

void SetSideBarContainerDivider(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length, ArkUI_Uint32 color, void* strokeWidthPtr, void* startMarginPtr, void* endMarginPtr,
    void* colorPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.strokeWidth");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.startMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.endMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.color");
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    if (length != NUM_3) {
        return;
    }
    Dimension strokeWidth(values[NUM_0], static_cast<DimensionUnit>(units[NUM_0]));
    Dimension startMargin(values[NUM_1], static_cast<DimensionUnit>(units[NUM_1]));
    Dimension endMargin(values[NUM_2], static_cast<DimensionUnit>(units[NUM_2]));

    if (SystemProperties::ConfigChangePerform() && strokeWidthPtr) {
        auto* strokewidth = reinterpret_cast<ResourceObject*>(strokeWidthPtr);
        auto strokeWidthObj = AceType::Claim(strokewidth);
        SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, strokeWidthObj);
    } else {
        SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, strokeWidth);
    }

    if (SystemProperties::ConfigChangePerform() && startMarginPtr) {
        auto* startmargin = reinterpret_cast<ResourceObject*>(startMarginPtr);
        auto startMarginObj = AceType::Claim(startmargin);
        SideBarContainerModelNG::SetDividerStartMargin(frameNode, startMarginObj);
    } else {
        SideBarContainerModelNG::SetDividerStartMargin(frameNode, startMargin);
    }

    if (SystemProperties::ConfigChangePerform() && endMarginPtr) {
        auto* endmargin = reinterpret_cast<ResourceObject*>(endMarginPtr);
        auto endMarginObj = AceType::Claim(endmargin);
        SideBarContainerModelNG::SetDividerEndMargin(frameNode, endMarginObj);
    } else {
        SideBarContainerModelNG::SetDividerEndMargin(frameNode, endMargin);
    }

    if (SystemProperties::ConfigChangePerform() && colorPtr) {
        auto* sidebarcolor = reinterpret_cast<ResourceObject*>(colorPtr);
        auto colorObj = AceType::Claim(sidebarcolor);
        SideBarContainerModelNG::SetDividerColor(frameNode, colorObj);
    } else {
        SideBarContainerModelNG::SetDividerColor(frameNode, Color(color));
    }
}

void ResetSideBarContainerDivider(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.strokeWidth");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.startMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.endMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.color");
    SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
    SideBarContainerModelNG::SetDividerColor(frameNode, Color(DEFAULT_SIDE_BAR_DIVIDER_COLOR));
    SideBarContainerModelNG::SetDividerStartMargin(frameNode, DEFAULT_START_MARGIN);
    SideBarContainerModelNG::SetDividerEndMargin(frameNode, DEFAULT_END_MARGIN);
}

void SetSideBarOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        SideBarContainerModelNG::SetOnChange(frameNode, std::move(*sideBarOnChange));
    } else {
        SideBarContainerModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSideBarOnChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetOnChange(frameNode, nullptr);
}

void SetSideBarToolBarManager(ArkUINodeHandle node)
{
    auto* sideBarNode = GetFrameNode(node);
    auto sideBarPattern = AceType::DynamicCast<NG::SideBarContainerPattern>(sideBarNode->GetPattern());
    if (sideBarPattern) {
        sideBarPattern->InitToolBarManager();
        sideBarNode->MarkModifyDone();
    }
}

void SetSideBarOnChangeEvent(void* callback)
{
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        SideBarContainerModelNG::SetOnChangeEventModifier(std::move(*sideBarOnChange));
    } else {
        SideBarContainerModelNG::SetOnChangeEventModifier(nullptr);
    }
}

void SetOnSideBarWidthChangeEvent(void* callback)
{
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(const Dimension&)>*>(callback);
        SideBarContainerModelNG::SetOnSideBarWidthChangeEventStatic(std::move(*sideBarOnChange));
    } else {
        SideBarContainerModelNG::SetOnSideBarWidthChangeEventStatic(nullptr);
    }
}

void ParseAndSetWidthObj(ArkUIWidthType widthType, void* valueResObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(valueResObj);
    auto resObjTextColor = AceType::Claim(reinterpret_cast<ResourceObject*>(valueResObj));
    CHECK_NULL_VOID(resObjTextColor);
    switch (widthType) {
        case ArkUIWidthType::SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.sideBarWidth");
            break;
        case ArkUIWidthType::MIN_SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minSideBarWidth");
            break;
        case ArkUIWidthType::MAX_SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.maxSideBarWidth");
            break;
        default:
            break;
    }

    SideBarContainerModelNG::ParseAndSetWidthStatic(static_cast<WidthType>(widthType), resObjTextColor);
}

void ParseAndSetWidth(ArkUIWidthType widthType, void* value, ArkUI_Bool isDoubleBind)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(value);
    auto calcDimension = reinterpret_cast<CalcDimension*>(value);
    CHECK_NULL_VOID(calcDimension);
    switch (widthType) {
        case ArkUIWidthType::SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.sideBarWidth");
            break;
        case ArkUIWidthType::MIN_SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.minSideBarWidth");
            break;
        case ArkUIWidthType::MAX_SIDEBAR_WIDTH:
            SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.maxSideBarWidth");
            break;
        default:
            break;
    }

    CalcDimension dim = *calcDimension;
    SideBarContainerModelNG::ParseAndSetWidthStatic(static_cast<WidthType>(widthType), dim, isDoubleBind);
}

void SetDividerStrokeWidth(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, *dim);
    } else if (valueObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(valueObj));
        SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, resObj);
    }
}
void SetDividerColor(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto color = reinterpret_cast<Color*>(value);
        SideBarContainerModelNG::SetDividerColor(frameNode, *color);
    } else if (valueObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(valueObj));
        SideBarContainerModelNG::SetDividerColor(frameNode, resObj);
    }
}
void SetDividerStartMargin(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        SideBarContainerModelNG::SetDividerStartMargin(frameNode, *dim);
    } else if (valueObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(valueObj));
        SideBarContainerModelNG::SetDividerStartMargin(frameNode, resObj);
    }
}
void SetDividerEndMargin(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        SideBarContainerModelNG::SetDividerEndMargin(frameNode, *dim);
    } else if (valueObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(valueObj));
        SideBarContainerModelNG::SetDividerEndMargin(frameNode, resObj);
    }
}
void ResetResObjDivider()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.strokeWidth");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.startMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.endMargin");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.dividerStyle.color");
}

void Create()
{
    SideBarContainerModelNG::CreateStatic();
}

void SetSideBarContainerType(ArkUISideBarContainerType type)
{
    SideBarContainerModelNG::SetSideBarContainerTypeStatic(static_cast<SideBarContainerType>(type));
}

void SetControlButtonIconInfo(
    ArkUI_CharPtr showIconStr, void* showIconResObj, ArkUI_Bool isPixelMap, void* pixMap, const ArkUI_Int32 state)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (showIconStr) {
        std::string str = showIconStr;
        auto pixMapObj = AceType::Claim(reinterpret_cast<PixelMap*>(pixMap));
        switch (state) {
            case NUM_0:
                SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, str, !isPixelMap, pixMapObj);
                break;
            case NUM_1:
                SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, str, !isPixelMap, pixMapObj);
                break;
            case NUM_2:
                SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(frameNode, str, !isPixelMap, pixMapObj);
                break;
            default:
                break;
        }
    } else if (showIconResObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(showIconResObj));
        auto pixMapObj = AceType::Claim(reinterpret_cast<PixelMap*>(pixMap));
        switch (state) {
            case NUM_0:
                SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, resObj, !isPixelMap, pixMapObj);
                break;
            case NUM_1:
                SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, resObj, !isPixelMap, pixMapObj);
                break;
            case NUM_2:
                SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(frameNode, resObj, !isPixelMap, pixMapObj);
                break;
            default:
                break;
        }
    }
}

void SetControlButtonLayout(void* value, const ArkUI_Int32 layout)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        switch (layout) {
            case NUM_0:
                SideBarContainerModelNG::SetControlButtonWidth(frameNode, *dim);
                break;
            case NUM_1:
                SideBarContainerModelNG::SetControlButtonHeight(frameNode, *dim);
                break;
            case NUM_2:
                SideBarContainerModelNG::SetControlButtonLeft(frameNode, *dim);
                break;
            case NUM_3:
                SideBarContainerModelNG::SetControlButtonTop(frameNode, *dim);
                break;
            default:
                break;
        }
    }
}

void ResetControlButtonLeft()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetControlButtonLeft(frameNode);
}

void ResetControlButtonTwelve()
{
    SideBarContainerModelNG::ResetControlButtonStatic();
}

void ResetControlButtonIconRes()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.shown");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.hidden");
    SideBarContainerModelNG::ResetResObj(frameNode, "sideBarContainer.buttonIconOptions.switching");
}

void ResetControlButtonIconInfo()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::ResetControlButtonIconInfo(frameNode);
}

void SetSideBarContainerMinContentWidthJs(ArkUI_Float32 value, ArkUI_Int32 unit, void* minContentWidthPtr)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.minContentWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (minContentWidthPtr) {
        auto* minContentWidth = reinterpret_cast<ResourceObject*>(minContentWidthPtr);
        auto minContentWidthObj = AceType::Claim(minContentWidth);
        SideBarContainerModelNG::SetMinContentWidth(frameNode, minContentWidthObj);
    } else {
        SideBarContainerModelNG::SetMinContentWidth(frameNode, maxSideBarWidthDimension);
    }
}

#ifndef CROSS_PLATFORM
void SetSideBarWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* sideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.sideBarWidth");
    Dimension sideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !sideBarWidthPtr) {
        GetSideBarContainerModelImpl()->SetSideBarWidth(sideBarWidthDimension);
    }
}

void SetMinSideBarWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* minSideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.minSideBarWidth");
    Dimension minSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !minSideBarWidthPtr) {
        GetSideBarContainerModelImpl()->SetMinSideBarWidth(minSideBarWidthDimension);
    }
}

void SetControlButtonImpl(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valueLength,
    const struct ArkUIIconsStruct* iconsStruct, void* iconsShownPtr, void* iconsHiddenPtr, void* iconsSwitchingPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.shown");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.hidden");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.switching");
    Dimension left = Dimension(values[0], DimensionUnit::VP);
    Dimension top = Dimension(values[1], DimensionUnit::VP);
    Dimension width = Dimension(values[2], DimensionUnit::VP);
    Dimension height = Dimension(values[3], DimensionUnit::VP);
    GetSideBarContainerModelImpl()->SetControlButtonLeft(left);
    GetSideBarContainerModelImpl()->SetControlButtonTop(top);
    GetSideBarContainerModelImpl()->SetControlButtonWidth(width);
    GetSideBarContainerModelImpl()->SetControlButtonHeight(height);
    CHECK_NULL_VOID(iconsStruct);
    if (iconsStruct->HiddenIconInfo) {
        GetSideBarContainerModelImpl()->SetControlButtonHiddenIconInfo(iconsStruct->HiddenIconInfo, false, nullptr);
    }
    if (iconsStruct->ShowIconInfo) {
        GetSideBarContainerModelImpl()->SetControlButtonShowIconInfo(iconsStruct->ShowIconInfo, false, nullptr);
    }
    if (iconsStruct->SwitchingIconInfo) {
        GetSideBarContainerModelImpl()->SetControlButtonSwitchingIconInfo(
            iconsStruct->SwitchingIconInfo, false, nullptr);
    }
}

void SetShowControlButtonImpl(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->SetShowControlButton(isShow);
}

void SetAutoHideImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->SetAutoHide(static_cast<bool>(value));
}

void SetSideBarContainerMaxSideBarWidthImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* maxSideBarWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.maxSideBarWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !maxSideBarWidthPtr) {
        GetSideBarContainerModelImpl()->SetMaxSideBarWidth(maxSideBarWidthDimension);
    }
}

void SetSideBarContainerMinContentWidthImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* minContentWidthPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.minContentWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !minContentWidthPtr) {
        GetSideBarContainerModelImpl()->SetMinContentWidth(maxSideBarWidthDimension);
    }
}

void SetSideBarPositionImpl(ArkUINodeHandle node, ArkUI_Int32 sideBarPosition)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->SetSideBarPosition(static_cast<SideBarPosition>(sideBarPosition));
}

void SetShowSideBarImpl(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->SetShowSideBar(isShow);
}

void SetSideBarContainerDividerImpl(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length, ArkUI_Uint32 color, void* strokeWidthPtr, void* startMarginPtr, void* endMarginPtr,
    void* colorPtr)
{
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.strokeWidth");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.startMargin");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.endMargin");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.color");
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    if (length != NUM_3) {
        return;
    }
    Dimension strokeWidth(values[NUM_0], static_cast<DimensionUnit>(units[NUM_0]));
    Dimension startMargin(values[NUM_1], static_cast<DimensionUnit>(units[NUM_1]));
    Dimension endMargin(values[NUM_2], static_cast<DimensionUnit>(units[NUM_2]));

    GetSideBarContainerModelImpl()->SetDividerStrokeWidth(strokeWidth);
    GetSideBarContainerModelImpl()->SetDividerStartMargin(startMargin);
    GetSideBarContainerModelImpl()->SetDividerEndMargin(endMargin);
    GetSideBarContainerModelImpl()->SetDividerColor(Color(color));
}

void SetSideBarOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        GetSideBarContainerModelImpl()->SetOnChange(std::move(*sideBarOnChange));
    } else {
        GetSideBarContainerModelImpl()->SetOnChange(nullptr);
    }
}

void SetSideBarToolBarManagerImpl(ArkUINodeHandle node)
{
    auto* sideBarNode = GetFrameNode(node);
    auto sideBarPattern = AceType::DynamicCast<NG::SideBarContainerPattern>(sideBarNode->GetPattern());
    if (sideBarPattern) {
        sideBarPattern->InitToolBarManager();
        sideBarNode->MarkModifyDone();
    }
}

void SetSideBarOnChangeEventImpl(void* callback)
{
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        GetSideBarContainerModelImpl()->SetOnChangeEvent(std::move(*sideBarOnChange));
    } else {
        GetSideBarContainerModelImpl()->SetOnChangeEvent(nullptr);
    }
}

void SetOnSideBarWidthChangeEventImpl(void* callback)
{
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(const Dimension&)>*>(callback);
        GetSideBarContainerModelImpl()->SetOnSideBarWidthChangeEvent(std::move(*sideBarOnChange));
    } else {
        GetSideBarContainerModelImpl()->SetOnSideBarWidthChangeEvent(nullptr);
    }
}

void ParseAndSetWidthImpl(ArkUIWidthType widthType, void* value, ArkUI_Bool isDoubleBind)
{
    CHECK_NULL_VOID(value);
    auto calcDimension = reinterpret_cast<CalcDimension*>(value);
    CHECK_NULL_VOID(calcDimension);
    switch (widthType) {
        case ArkUIWidthType::SIDEBAR_WIDTH:
            GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.sideBarWidth");
            break;
        case ArkUIWidthType::MIN_SIDEBAR_WIDTH:
            GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.minSideBarWidth");
            break;
        case ArkUIWidthType::MAX_SIDEBAR_WIDTH:
            GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.maxSideBarWidth");
            break;
        default:
            break;
    }

    CalcDimension dim = *calcDimension;
    GetSideBarContainerModelImpl()->ParseAndSetWidth(static_cast<WidthType>(widthType), dim, isDoubleBind);
}

void SetDividerStrokeWidthImpl(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        GetSideBarContainerModelImpl()->SetDividerStrokeWidth(*dim);
    }
}
void SetDividerColorImpl(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto color = reinterpret_cast<Color*>(value);
        GetSideBarContainerModelImpl()->SetDividerColor(*color);
    }
}
void SetDividerStartMarginImpl(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        GetSideBarContainerModelImpl()->SetDividerStartMargin(*dim);
    }
}
void SetDividerEndMarginImpl(void* value, void* valueObj)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        GetSideBarContainerModelImpl()->SetDividerEndMargin(*dim);
    }
}
void ResetResObjDividerImpl()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.strokeWidth");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.startMargin");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.endMargin");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.dividerStyle.color");
}

void CreateImpl()
{
    GetSideBarContainerModelImpl()->Create();
}

void SetSideBarContainerTypeImpl(ArkUISideBarContainerType type)
{
    GetSideBarContainerModelImpl()->SetSideBarContainerType(static_cast<SideBarContainerType>(type));
}

void SetControlButtonIconInfoImpl(
    ArkUI_CharPtr showIconStr, void* showIconResObj, ArkUI_Bool isPixelMap, void* pixMap, const ArkUI_Int32 state)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (showIconStr) {
        std::string str = showIconStr;
        auto pixMapObj = AceType::Claim(reinterpret_cast<PixelMap*>(pixMap));
        switch (state) {
            case NUM_0:
                GetSideBarContainerModelImpl()->SetControlButtonShowIconInfo(str, !isPixelMap, pixMapObj);
                break;
            case NUM_1:
                GetSideBarContainerModelImpl()->SetControlButtonHiddenIconInfo(str, !isPixelMap, pixMapObj);
                break;
            case NUM_2:
                GetSideBarContainerModelImpl()->SetControlButtonSwitchingIconInfo(str, !isPixelMap, pixMapObj);
                break;
            default:
                break;
        }
    }
}

void SetControlButtonLayoutImpl(void* value, const ArkUI_Int32 layout)
{
    if (value) {
        auto dim = reinterpret_cast<Dimension*>(value);
        switch (layout) {
            case NUM_0:
                GetSideBarContainerModelImpl()->SetControlButtonWidth(*dim);
                break;
            case NUM_1:
                GetSideBarContainerModelImpl()->SetControlButtonHeight(*dim);
                break;
            case NUM_2:
                GetSideBarContainerModelImpl()->SetControlButtonLeft(*dim);
                break;
            case NUM_3:
                GetSideBarContainerModelImpl()->SetControlButtonTop(*dim);
                break;
            default:
                break;
        }
    }
}

void ResetControlButtonLeftImpl()
{
    GetSideBarContainerModelImpl()->ResetControlButtonLeft();
}

void ResetControlButtonTwelveImpl()
{
    GetSideBarContainerModelImpl()->ResetControlButton();
}

void ResetControlButtonIconResImpl()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.shown");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.hidden");
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.buttonIconOptions.switching");
}

void ResetControlButtonIconInfoImpl()
{
    GetSideBarContainerModelImpl()->ResetControlButtonIconInfo();
}

void SetSideBarContainerMinContentWidthJsImpl(ArkUI_Float32 value, ArkUI_Int32 unit, void* minContentWidthPtr)
{
    GetSideBarContainerModelImpl()->ResetResObj("sideBarContainer.minContentWidth");
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    if (!minContentWidthPtr) {
        GetSideBarContainerModelImpl()->SetMinContentWidth(maxSideBarWidthDimension);
    }
}
#endif

namespace NodeModifier {
const ArkUISideBarContainerModifier* GetSideBarContainerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUISideBarContainerModifier modifier = {
            .setSideBarWidth = SetSideBarWidthImpl,
            .resetSideBarWidth = nullptr,
            .setMinSideBarWidth = SetMinSideBarWidthImpl,
            .resetMinSideBarWidth = nullptr,
            .setControlButton = SetControlButtonImpl,
            .resetControlButton = nullptr,
            .setShowControlButton = SetShowControlButtonImpl,
            .resetShowControlButton = nullptr,
            .setAutoHide = SetAutoHideImpl,
            .resetAutoHide = nullptr,
            .setSideBarContainerMaxSideBarWidth = SetSideBarContainerMaxSideBarWidthImpl,
            .resetSideBarContainerMaxSideBarWidth = nullptr,
            .setSideBarContainerMinContentWidth = SetSideBarContainerMinContentWidthImpl,
            .resetSideBarContainerMinContentWidth = nullptr,
            .setSideBarPosition = SetSideBarPositionImpl,
            .resetSideBarPosition = nullptr,
            .setShowSideBar = SetShowSideBarImpl,
            .resetShowSideBar = nullptr,
            .setSideBarContainerDivider = SetSideBarContainerDividerImpl,
            .resetSideBarContainerDivider = nullptr,
            .setSideBarOnChange = SetSideBarOnChangeImpl,
            .resetSideBarOnChange = nullptr,
            .setSideBarToolBarManager = SetSideBarToolBarManagerImpl,
            .setSideBarOnChangeEvent = SetSideBarOnChangeEventImpl,
            .parseAndSetWidthObj = nullptr,
            .parseAndSetWidth = ParseAndSetWidthImpl,
            .setOnSideBarWidthChangeEvent = SetOnSideBarWidthChangeEventImpl,
            .setDividerStrokeWidth = SetDividerStrokeWidthImpl,
            .setDividerColor = SetDividerColorImpl,
            .setDividerStartMargin = SetDividerStartMarginImpl,
            .setDividerEndMargin = SetDividerEndMarginImpl,
            .resetResObjDivider = ResetResObjDividerImpl,
            .create = CreateImpl,
            .setSideBarContainerType = SetSideBarContainerTypeImpl,
            .setControlButtonIconInfo = SetControlButtonIconInfoImpl,
            .setControlButtonLayout = SetControlButtonLayoutImpl,
            .resetControlButtonLeft = ResetControlButtonLeftImpl,
            .resetControlButtonTwelve = ResetControlButtonTwelveImpl,
            .resetControlButtonIconInfo = ResetControlButtonIconInfoImpl,
            .resetControlButtonIconRes = ResetControlButtonIconResImpl,
            .setSideBarContainerMinContentWidthJs = SetSideBarContainerMinContentWidthJsImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#endif
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISideBarContainerModifier modifier = {
        .setSideBarWidth = SetSideBarWidth,
        .resetSideBarWidth = ResetSideBarWidth,
        .setMinSideBarWidth = SetMinSideBarWidth,
        .resetMinSideBarWidth = ResetMinSideBarWidth,
        .setControlButton = SetControlButton,
        .resetControlButton = ResetControlButton,
        .setShowControlButton = SetShowControlButton,
        .resetShowControlButton = ResetShowControlButton,
        .setAutoHide = SetAutoHide,
        .resetAutoHide = ResetAutoHide,
        .setSideBarContainerMaxSideBarWidth = SetSideBarContainerMaxSideBarWidth,
        .resetSideBarContainerMaxSideBarWidth = ResetSideBarContainerMaxSideBarWidth,
        .setSideBarContainerMinContentWidth = SetSideBarContainerMinContentWidth,
        .resetSideBarContainerMinContentWidth = ResetSideBarContainerMinContentWidth,
        .setSideBarPosition = SetSideBarPosition,
        .resetSideBarPosition = ResetSideBarPosition,
        .setShowSideBar = SetShowSideBar,
        .resetShowSideBar = ResetShowSideBar,
        .setSideBarContainerDivider = SetSideBarContainerDivider,
        .resetSideBarContainerDivider = ResetSideBarContainerDivider,
        .setSideBarOnChange = SetSideBarOnChange,
        .resetSideBarOnChange = ResetSideBarOnChange,
        .setSideBarToolBarManager = SetSideBarToolBarManager,
        .setSideBarOnChangeEvent = SetSideBarOnChangeEvent,
        .parseAndSetWidthObj = ParseAndSetWidthObj,
        .parseAndSetWidth = ParseAndSetWidth,
        .setOnSideBarWidthChangeEvent = SetOnSideBarWidthChangeEvent,
        .setDividerStrokeWidth = SetDividerStrokeWidth,
        .setDividerColor = SetDividerColor,
        .setDividerStartMargin = SetDividerStartMargin,
        .setDividerEndMargin = SetDividerEndMargin,
        .resetResObjDivider = ResetResObjDivider,
        .create = Create,
        .setSideBarContainerType = SetSideBarContainerType,
        .setControlButtonIconInfo = SetControlButtonIconInfo,
        .setControlButtonLayout = SetControlButtonLayout,
        .resetControlButtonLeft = ResetControlButtonLeft,
        .resetControlButtonTwelve = ResetControlButtonTwelve,
        .resetControlButtonIconInfo = ResetControlButtonIconInfo,
        .resetControlButtonIconRes = ResetControlButtonIconRes,
        .setSideBarContainerMinContentWidthJs = SetSideBarContainerMinContentWidthJs,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUISideBarContainerModifier* GetCJUISideBarContainerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISideBarContainerModifier modifier = {
        .setSideBarWidth = SetSideBarWidth,
        .resetSideBarWidth = ResetSideBarWidth,
        .setMinSideBarWidth = SetMinSideBarWidth,
        .resetMinSideBarWidth = ResetMinSideBarWidth,
        .setControlButton = SetControlButton,
        .resetControlButton = ResetControlButton,
        .setShowControlButton = SetShowControlButton,
        .resetShowControlButton = ResetShowControlButton,
        .setAutoHide = SetAutoHide,
        .resetAutoHide = ResetAutoHide,
        .setSideBarContainerMaxSideBarWidth = SetSideBarContainerMaxSideBarWidth,
        .resetSideBarContainerMaxSideBarWidth = ResetSideBarContainerMaxSideBarWidth,
        .setSideBarContainerMinContentWidth = SetSideBarContainerMinContentWidth,
        .resetSideBarContainerMinContentWidth = ResetSideBarContainerMinContentWidth,
        .setSideBarPosition = SetSideBarPosition,
        .resetSideBarPosition = ResetSideBarPosition,
        .setShowSideBar = SetShowSideBar,
        .resetShowSideBar = ResetShowSideBar,
        .setSideBarContainerDivider = SetSideBarContainerDivider,
        .resetSideBarContainerDivider = ResetSideBarContainerDivider,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
