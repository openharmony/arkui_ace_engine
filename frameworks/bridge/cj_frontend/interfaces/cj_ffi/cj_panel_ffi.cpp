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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_panel_ffi.h"

#include "cj_lambda.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<PanelMode> PANEL_MODES = { PanelMode::MINI, PanelMode::HALF, PanelMode::FULL, PanelMode::AUTO };
const std::vector<PanelType> PANEL_TYPES = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR, PanelType::TEMP_DISPLAY };
const std::vector<VisibleType> PANEL_VISIBLE_TYPES = { VisibleType::GONE, VisibleType::VISIBLE,
    VisibleType::INVISIBLE };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkPanelCreate(bool isShow)
{
    SlidingPanelModel::GetInstance()->Create(isShow);
}

void FfiOHOSAceFrameworkPanelType(int32_t type)
{
    if (!Utils::CheckParamsValid(type, PANEL_TYPES.size())) {
        LOGE("invalid value for panel type");
        return;
    }
    SlidingPanelModel::GetInstance()->SetPanelType(PANEL_TYPES[type]);
}

void FfiOHOSAceFrameworkPanelMode(int32_t mode)
{
    if (!Utils::CheckParamsValid(mode, PANEL_MODES.size())) {
        LOGE("invalid value for panel mode");
        return;
    }
    SlidingPanelModel::GetInstance()->SetPanelMode(PANEL_MODES[mode]);
}

void FfiOHOSAceFrameworkPanelDragBar(bool val)
{
    SlidingPanelModel::GetInstance()->SetHasDragBar(val);
}

void FfiOHOSAceFrameworkPanelFullHeight(double height, int32_t unit)
{
    Dimension fullHeight = Dimension(height, static_cast<DimensionUnit>(unit));
    SlidingPanelModel::GetInstance()->SetFullHeight(fullHeight);
}
void FfiOHOSAceFrameworkPanelHalfHeight(double height, int32_t unit)
{
    Dimension halfHeight = Dimension(height, static_cast<DimensionUnit>(unit));
    SlidingPanelModel::GetInstance()->SetHalfHeight(halfHeight);
}
void FfiOHOSAceFrameworkPanelMiniHeight(double height, int32_t unit)
{
    Dimension minHeight = Dimension(height, static_cast<DimensionUnit>(unit));
    SlidingPanelModel::GetInstance()->SetMiniHeight(minHeight);
}

void FfiOHOSAceFrameworkPanelShow(bool isShow)
{
    SlidingPanelModel::GetInstance()->SetIsShow(isShow);
}

void FfiOHOSAceFrameworkPanelShowCloseIcon(bool showCloseIcon)
{
    SlidingPanelModel::GetInstance()->SetShowCloseIcon(showCloseIcon);
}

void FfiOHOSAceFrameworkPanelBackgroundMask(uint32_t color)
{
    SlidingPanelModel::GetInstance()->SetBackgroundMask(Color(color));
}

void FfiOHOSAceFrameworkPanelOnChange(void (*callback)(double width, double height, int32_t mode))
{
    auto onSizeChangeNG = [ffiCallback = CJLambda::Create(callback)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        auto height = eventInfo->GetHeight();
        auto width = eventInfo->GetWidth();
        auto mode = static_cast<int32_t>(eventInfo->GetMode());
        ffiCallback(width, height, mode);
    };
    SlidingPanelModel::GetInstance()->SetOnSizeChange(std::move(onSizeChangeNG));
}

void FfiOHOSAceFrameworkPanelOnHeightChange(void (*callback)(double height))
{
    auto onHeightChangeNG = [ffiCallback = CJLambda::Create(callback)](double height) { ffiCallback(height); };
    SlidingPanelModel::GetInstance()->SetOnHeightChange(std::move(onHeightChangeNG));
}

void FfiOHOSAceFrameworkPanelPop()
{
    SlidingPanelModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameworkPanelBackgroundColor(uint32_t color)
{
    SlidingPanelModel::GetInstance()->SetBackgroundColor(Color(color));
}
void FfiOHOSAceFrameworkPanelBorder(CJBorder params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension radiusDime(params.radius, static_cast<DimensionUnit>(params.radiusUnit));
    if (!Utils::CheckParamsValid(params.style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }
    SlidingPanelModel::GetInstance()->SetBorderWidth(widthDime);
    SlidingPanelModel::GetInstance()->SetBorderStyle(BORDER_STYLES[params.style]);
    SlidingPanelModel::GetInstance()->SetBorderColor(Color(params.color));
    ViewAbstractModel::GetInstance()->SetBorderRadius(radiusDime);
}
void FfiOHOSAceFrameworkPanelBorderWidth(double width, int32_t unit)
{
    SlidingPanelModel::GetInstance()->SetBorderWidth(Dimension(width, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPanelBorderColor(uint32_t color)
{
    SlidingPanelModel::GetInstance()->SetBorderColor(Color(color));
}
void FfiOHOSAceFrameworkPanelBorderRadius(double radius, int32_t unit)
{
    ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension(radius, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPanelBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }
    SlidingPanelModel::GetInstance()->SetBorderStyle(BORDER_STYLES[style]);
}
}
