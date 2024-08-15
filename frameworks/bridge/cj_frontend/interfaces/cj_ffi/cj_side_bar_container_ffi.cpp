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
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;

enum class CJWidthType : uint32_t {
    SIDEBAR_WIDTH = 0,
    MIN_SIDEBAR_WIDTH,
    MAX_SIDEBAR_WIDTH,
};

const std::vector<SideBarContainerType> SIDE_BAR_TYPE = { SideBarContainerType::EMBED, SideBarContainerType::OVERLAY };
const std::vector<SideBarPosition> SIDE_BAR_POSITION = { SideBarPosition::START, SideBarPosition::END };

void ParseAndSetWidth(Dimension dimension, CJWidthType widthType)
{
    switch (widthType) {
        case CJWidthType::SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->SetSideBarWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_SIDE_BAR_WIDTH);
            break;
        case CJWidthType::MIN_SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->SetMinSideBarWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_MIN_SIDE_BAR_WIDTH);
            break;
        case CJWidthType::MAX_SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->SetMaxSideBarWidth(
                dimension.IsNonNegative() ? dimension : DEFAULT_MAX_SIDE_BAR_WIDTH);
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
    SideBarContainerModel::GetInstance()->Create();
    SideBarContainerType style = static_cast<SideBarContainerType>(type);
    SideBarContainerModel::GetInstance()->SetSideBarContainerType(style);
}
void FfiOHOSAceFrameworkSideBarShowSideBar(bool isShow)
{
    SideBarContainerModel::GetInstance()->SetShowSideBar(isShow);
}
void FfiOHOSAceFrameworkSideBarControlButton(CJSideBarButtonStyle style)
{
    auto controlButtonWidth = Dimension(style.width, DimensionUnit::VP);
    if (LessNotEqual(controlButtonWidth.Value(), 0.0)) {
        controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
    }
    SideBarContainerModel::GetInstance()->SetControlButtonWidth(controlButtonWidth);

    auto controlButtonHeight = Dimension(style.height, DimensionUnit::VP);
    if (LessNotEqual(controlButtonHeight.Value(), 0.0)) {
        controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
    }
    SideBarContainerModel::GetInstance()->SetControlButtonHeight(controlButtonHeight);
    SideBarContainerModel::GetInstance()->SetControlButtonLeft(Dimension(style.left, DimensionUnit::VP));
    SideBarContainerModel::GetInstance()->SetControlButtonTop(Dimension(style.top, DimensionUnit::VP));

    auto iconsInfo = style.icons;
    if (iconsInfo.shown) {
        SideBarContainerModel::GetInstance()->SetControlButtonShowIconInfo(iconsInfo.shown, false, nullptr);
    }
    if (iconsInfo.hidden) {
        SideBarContainerModel::GetInstance()->SetControlButtonHiddenIconInfo(iconsInfo.hidden, false, nullptr);
    }
    if (iconsInfo.switching) {
        SideBarContainerModel::GetInstance()->SetControlButtonSwitchingIconInfo(iconsInfo.switching, false, nullptr);
    }
}
void FfiOHOSAceFrameworkSideBarShowControlButton(bool isShow)
{
    SideBarContainerModel::GetInstance()->SetShowControlButton(isShow);
}
void FfiOHOSAceFrameworkSideBarOnChange(void (*callback)(bool isShow))
{
    auto onChange = [ffiCallback = CJLambda::Create(callback)](bool isShow) { ffiCallback(isShow); };
    SideBarContainerModel::GetInstance()->SetOnChange(std::move(onChange));
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
    SideBarContainerModel::GetInstance()->SetAutoHide(autoHide);
}
void FfiOHOSAceFrameworkSideBarSideBarPosition(int32_t position)
{
    if (!Utils::CheckParamsValid(position, SIDE_BAR_POSITION.size())) {
        LOGE("invalid value for sidebar position");
        return;
    }
    SideBarPosition sideBarPosition = static_cast<SideBarPosition>(position);
    SideBarContainerModel::GetInstance()->SetSideBarPosition(sideBarPosition);
}
void FfiOHOSAceFrameworkSideBarPop()
{
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}
}
