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

#include "cj_side_bar_container_ffi.h"

#include "cj_lambda.h"

#include "base/log/log_wrapper.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_END_MARGIN = 0.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);

enum class CJWidthType : uint32_t {
    SIDEBAR_WIDTH = 0,
    MIN_SIDEBAR_WIDTH,
    MAX_SIDEBAR_WIDTH,
    STROKE_WIDTH,
    START_MARGIN,
    END_MARGIN,
};

const std::vector<SideBarContainerType> SIDE_BAR_TYPE = { SideBarContainerType::EMBED, SideBarContainerType::OVERLAY,
    SideBarContainerType::AUTO };
const std::vector<SideBarPosition> SIDE_BAR_POSITION = { SideBarPosition::START, SideBarPosition::END };

// Should use CJUIModifier API later
NG::SideBarContainerModelNG* GetSideBarContainerModel()
{
    static NG::SideBarContainerModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Sidebar");
        if (module == nullptr) {
            LOGF("Can't find sidebar module");
            abort();
        }
        model = reinterpret_cast<NG::SideBarContainerModelNG*>(module->GetModel());
    }
    return model;
}

void ParseAndSetWidth(Dimension dimension, CJWidthType widthType)
{
    switch (widthType) {
        case CJWidthType::SIDEBAR_WIDTH:
            GetSideBarContainerModel()->SetSideBarWidth(dimension.IsNonNegative() ? dimension : DEFAULT_SIDE_BAR_WIDTH);
            break;
        case CJWidthType::MIN_SIDEBAR_WIDTH:
            GetSideBarContainerModel()->SetMinSideBarWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_MIN_SIDE_BAR_WIDTH);
            break;
        case CJWidthType::MAX_SIDEBAR_WIDTH:
            GetSideBarContainerModel()->SetMaxSideBarWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_MAX_SIDE_BAR_WIDTH);
            break;
        case CJWidthType::STROKE_WIDTH:
            GetSideBarContainerModel()->SetDividerStrokeWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_DIVIDER_STROKE_WIDTH);
            break;
        case CJWidthType::START_MARGIN:
            GetSideBarContainerModel()->SetDividerStartMargin(
                dimension.IsNonNegative() ? dimension : DEFAULT_DIVIDER_START_MARGIN);
            break;
        case CJWidthType::END_MARGIN:
            GetSideBarContainerModel()->SetDividerEndMargin(
                dimension.IsNonNegative() ? dimension : DEFAULT_DIVIDER_END_MARGIN);
            break;
        default:
            break;
    }
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSideBarCreate(int32_t type)
{
    if (!Utils::CheckParamsValid(type, SIDE_BAR_TYPE.size())) {
        LOGE("invalid value for sidebar type");
        return;
    }
    GetSideBarContainerModel()->Create();
    SideBarContainerType style = static_cast<SideBarContainerType>(type);
    GetSideBarContainerModel()->SetSideBarContainerType(style);
}
void FfiOHOSAceFrameworkSideBarShowSideBar(bool isShow)
{
    GetSideBarContainerModel()->SetShowSideBar(isShow);
}
void FfiOHOSAceFrameworkSideBarControlButton(CJSideBarButtonStyle style)
{
    auto controlButtonWidth = Dimension(style.width, DimensionUnit::VP);
    if (LessNotEqual(controlButtonWidth.Value(), 0.0)) {
        controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
    }
    GetSideBarContainerModel()->SetControlButtonWidth(controlButtonWidth);

    auto controlButtonHeight = Dimension(style.height, DimensionUnit::VP);
    if (LessNotEqual(controlButtonHeight.Value(), 0.0)) {
        controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
    }
    GetSideBarContainerModel()->SetControlButtonHeight(controlButtonHeight);
    GetSideBarContainerModel()->SetControlButtonLeft(Dimension(style.left, DimensionUnit::VP));
    GetSideBarContainerModel()->SetControlButtonTop(Dimension(style.top, DimensionUnit::VP));

    auto iconsInfo = style.icons;
    if (iconsInfo.shown) {
        GetSideBarContainerModel()->SetControlButtonShowIconInfo(iconsInfo.shown, false, nullptr);
    }
    if (iconsInfo.hidden) {
        GetSideBarContainerModel()->SetControlButtonHiddenIconInfo(iconsInfo.hidden, false, nullptr);
    }
    if (iconsInfo.switching) {
        GetSideBarContainerModel()->SetControlButtonSwitchingIconInfo(iconsInfo.switching, false, nullptr);
    }
}
void FfiOHOSAceFrameworkSideBarShowControlButton(bool isShow)
{
    GetSideBarContainerModel()->SetShowControlButton(isShow);
}

void FfiOHOSAceFrameworkSideBarResetControlButton()
{
    GetSideBarContainerModel()->SetControlButtonWidth(DEFAULT_CONTROL_BUTTON_WIDTH);
    GetSideBarContainerModel()->SetControlButtonHeight(DEFAULT_CONTROL_BUTTON_HEIGHT);
    GetSideBarContainerModel()->ResetControlButtonLeft();
    GetSideBarContainerModel()->SetControlButtonTop(DEFAULT_CONTROL_BUTTON_TOP);
    GetSideBarContainerModel()->ResetControlButtonIconInfo();
}

void FfiOHOSAceFrameworkSideBarResetControlButtonIcons()
{
    GetSideBarContainerModel()->ResetControlButtonIconInfo();
}

void FfiOHOSAceFrameworkSideBarOnChange(void (*callback)(bool isShow))
{
    auto onChange = [ffiCallback = CJLambda::Create(callback)](bool isShow) { ffiCallback(isShow); };
    GetSideBarContainerModel()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkSideBarSideBarWidth(double width, int32_t unit)
{
    ParseAndSetWidth(Dimension(width, static_cast<DimensionUnit>(unit)), CJWidthType::SIDEBAR_WIDTH);
}

void FfiOHOSAceFrameworkSideBarMinSideBarWidth(double width, int32_t unit)
{
    ParseAndSetWidth(Dimension(width, static_cast<DimensionUnit>(unit)), CJWidthType::MIN_SIDEBAR_WIDTH);
}
void FfiOHOSAceFrameworkSideBarMaxSideBarWidth(double width, int32_t unit)
{
    ParseAndSetWidth(Dimension(width, static_cast<DimensionUnit>(unit)), CJWidthType::MAX_SIDEBAR_WIDTH);
}
void FfiOHOSAceFrameworkSideBarAutoHide(bool autoHide)
{
    GetSideBarContainerModel()->SetAutoHide(autoHide);
}
void FfiOHOSAceFrameworkSideBarSideBarPosition(int32_t position)
{
    if (!Utils::CheckParamsValid(position, SIDE_BAR_POSITION.size())) {
        LOGE("invalid value for sidebar position");
        return;
    }
    SideBarPosition sideBarPosition = static_cast<SideBarPosition>(position);
    GetSideBarContainerModel()->SetSideBarPosition(sideBarPosition);
}
void FfiOHOSAceFrameworkSideBarPop()
{
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void FfiOHOSAceFrameworkSideBarDividerNull()
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        // sideBar divider set default width when input illegal value
        GetSideBarContainerModel()->SetDividerStrokeWidth(DEFAULT_DIVIDER_STROKE_WIDTH);
    } else {
        GetSideBarContainerModel()->SetDividerStrokeWidth(0.0_vp);
    }
}

void FfiOHOSAceFrameworkSideBarDivider(CJDividerStyle info)
{
    ParseAndSetWidth(
        Dimension(info.strokeWidth, static_cast<DimensionUnit>(info.strokeWidthUnit)), CJWidthType::STROKE_WIDTH);

    Color color = info.hasColor ? Color(info.color) : DEFAULT_DIVIDER_COLOR;
    GetSideBarContainerModel()->SetDividerColor(color);
    ParseAndSetWidth(
        Dimension(info.startMargin, static_cast<DimensionUnit>(info.startMarginUnit)), CJWidthType::START_MARGIN);
    ParseAndSetWidth(
        Dimension(info.endMargin, static_cast<DimensionUnit>(info.endMarginUnit)), CJWidthType::END_MARGIN);
}

void FfiOHOSAceFrameworkSideBarMinContentWidth(double width, int32_t unit)
{
    CalcDimension minContentWidth(width, static_cast<DimensionUnit>(unit));
    GetSideBarContainerModel()->SetMinContentWidth(minContentWidth);
}
}
