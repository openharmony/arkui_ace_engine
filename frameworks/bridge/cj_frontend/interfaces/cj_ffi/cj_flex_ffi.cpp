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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_flex_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FlexAlign> FLEX_ALIGNS = { FlexAlign::AUTO, FlexAlign::FLEX_START, FlexAlign::CENTER,
    FlexAlign::FLEX_END, FlexAlign::SPACE_BETWEEN, FlexAlign::SPACE_AROUND, FlexAlign::SPACE_EVENLY };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkFlexCreate()
{
    FlexModel::GetInstance()->CreateFlexRow();
}

void FfiOHOSAceFrameworkFlexCreateWithParams(CJFlexParams params)
{
    if (params.wrap == 0) {
        FlexCreateFlexComponent(params);
    } else {
        FlexCreateWrapComponent(params);
    }
}

void FfiOHOSAceFrameworkFlexSetFlexWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);
    FlexModel::GetInstance()->SetFlexWidth();
}

void FfiOHOSAceFrameworkFlexSetFlexHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
    FlexModel::GetInstance()->SetFlexHeight();
}

void FfiOHOSAceFrameworkFlexSetFlexSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, widthUnit);
    FlexModel::GetInstance()->SetFlexWidth();
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, heightUnit);
    FlexModel::GetInstance()->SetFlexHeight();
}

void FfiOHOSAceFrameworkFlexCreateByOptions(CJFlexOptions options)
{
    if (options.wrap == 0) {
        FlexCreateFlexComponentByOptions(options);
    } else {
        FlexCreateWrapComponentByOptions(options);
    }
}
}

namespace OHOS::Ace {
void FlexCreateFlexComponent(CJFlexParams params)
{
    FlexModel::GetInstance()->CreateFlexRow();
    if (params.direction >= 0 && params.direction <= DIRECTION_MAX_VALUE) {
        FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(params.direction));
    }
    auto justifyVal = static_cast<int32_t>(FLEX_ALIGNS[params.justifyContent]);
    if (justifyVal >= 0 && justifyVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetMainAxisAlign(static_cast<FlexAlign>(justifyVal));
    }
    if (params.alignItems >= 0 && params.alignItems <= CROSS_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetCrossAxisAlign(static_cast<FlexAlign>(params.alignItems));
    }
}
void FlexCreateWrapComponent(CJFlexParams params)
{
    FlexModel::GetInstance()->CreateWrap();
    if (params.direction >= 0 && params.direction <= DIRECTION_MAX_VALUE) {
        FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(params.direction));
        // WrapReverse means wrapVal = 2. Wrap means wrapVal = 1.
        constexpr int reverseDirection = 2;
        if (params.direction <= 1) {
            params.direction += reverseDirection * (params.wrap - 1);
        } else {
            params.direction -= reverseDirection * (params.wrap - 1);
        }
        FlexModel::GetInstance()->SetWrapDirection(static_cast<WrapDirection>(params.direction));
    }
    auto justifyVal = static_cast<int32_t>(FLEX_ALIGNS[params.justifyContent]);
    if (justifyVal >= 0 && justifyVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapMainAlignment(WRAP_TABLE[justifyVal]);
    }
    if (params.alignItems >= 0 && params.alignItems <= CROSS_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapCrossAlignment(WRAP_TABLE[params.alignItems]);
    }
    auto alignContentVal = static_cast<int32_t>(FLEX_ALIGNS[params.alignContent]);
    if (alignContentVal >= 0 && alignContentVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapAlignment(WRAP_TABLE[alignContentVal]);
    }
}

void FlexCreateFlexComponentByOptions(CJFlexOptions options)
{
    FlexModel::GetInstance()->CreateFlexRow();
    if (options.direction >= 0 && options.direction <= DIRECTION_MAX_VALUE) {
        FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(options.direction));
    }
    auto justifyVal = static_cast<int32_t>(FLEX_ALIGNS[options.justifyContent]);
    if (justifyVal >= 0 && justifyVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetMainAxisAlign(static_cast<FlexAlign>(justifyVal));
    }
    if (options.alignItems >= 0 && options.alignItems <= CROSS_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetCrossAxisAlign(static_cast<FlexAlign>(options.alignItems));
    }
    if (options.mainSpace >= 0.0 && options.mainSpaceUnit != static_cast<int32_t>(DimensionUnit::PERCENT)) {
        FlexModel::GetInstance()->SetMainSpace(
            CalcDimension(options.mainSpace, static_cast<DimensionUnit>(options.mainSpaceUnit)));
    }
}

void FlexCreateWrapComponentByOptions(CJFlexOptions options)
{
    FlexModel::GetInstance()->CreateWrap();
    if (options.direction >= 0 && options.direction <= DIRECTION_MAX_VALUE) {
        FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(options.direction));
        // WrapReverse means wrapVal = 2. Wrap means wrapVal = 1.
        constexpr int reverseDirection = 2;
        if (options.direction <= 1) {
            options.direction += reverseDirection * (options.wrap - 1);
        } else {
            options.direction -= reverseDirection * (options.wrap - 1);
        }
        FlexModel::GetInstance()->SetWrapDirection(static_cast<WrapDirection>(options.direction));
    }
    auto justifyVal = static_cast<int32_t>(FLEX_ALIGNS[options.justifyContent]);
    if (justifyVal >= 0 && justifyVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapMainAlignment(WRAP_TABLE[justifyVal]);
    }
    if (options.alignItems >= 0 && options.alignItems <= CROSS_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapCrossAlignment(WRAP_TABLE[options.alignItems]);
    }
    auto alignContentVal = static_cast<int32_t>(FLEX_ALIGNS[options.alignContent]);
    if (alignContentVal >= 0 && alignContentVal <= MAIN_ALIGN_MAX_VALUE) {
        FlexModel::GetInstance()->SetWrapAlignment(WRAP_TABLE[alignContentVal]);
    }

    if (options.mainSpace >= 0.0 && options.mainSpaceUnit != static_cast<int32_t>(DimensionUnit::PERCENT)) {
        FlexModel::GetInstance()->SetMainSpace(
            CalcDimension(options.mainSpace, static_cast<DimensionUnit>(options.mainSpaceUnit)));
    }
    if (options.crossSpace >= 0.0 && options.crossSpaceUnit != static_cast<int32_t>(DimensionUnit::PERCENT)) {
        FlexModel::GetInstance()->SetCrossSpace(
            CalcDimension(options.crossSpace, static_cast<DimensionUnit>(options.crossSpaceUnit)));
    }
}
} // namespace OHOS::Ace
