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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_rect_ffi.h"


#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"

using namespace OHOS::Ace;

extern "C" {
void FfiOHOSAceFrameworkRectCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    RectModel::GetInstance()->Create();
    if (width > 0.0) {
        FfiOHOSAceFrameworkShapeSetWidth(width, widthUnit);
    }
    if (height > 0.0) {
        FfiOHOSAceFrameworkShapeSetHeight(height, heightUnit);
    }
}

int64_t FfiOHOSAceFrameworkRectInsCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    OHOS::Ace::Dimension dWidth(width, static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    OHOS::Ace::Dimension dHeight(height, static_cast<OHOS::Ace::DimensionUnit>(heightUnit));
    auto ret_ = OHOS::FFI::FFIData::Create<OHOS::Ace::Framework::NativeRect>(dWidth, dHeight);
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkRectSetRadiusWidth(double radiusWidth, int32_t radiusWidthUnit)
{
    Dimension value(radiusWidth, static_cast<DimensionUnit>(radiusWidthUnit));
    RectModel::GetInstance()->SetRadiusWidth(value);
}

void FfiOHOSAceFrameworkRectSetRadiusHeight(double radiusHeight, int32_t radiusHeightUnit)
{
    Dimension value(radiusHeight, static_cast<DimensionUnit>(radiusHeightUnit));
    RectModel::GetInstance()->SetRadiusHeight(value);
}

void FfiOHOSAceFrameworkRectSetRadius(double radius, int32_t radiusUnit)
{
    Dimension value(radius, static_cast<DimensionUnit>(radiusUnit));
    RectModel::GetInstance()->SetRadiusWidth(value);
    RectModel::GetInstance()->SetRadiusHeight(value);
}

void FfiOHOSAceFrameworkRectSetRadiusArray(VectorDoubleHandle voidValue, VectorInt32Handle voidUnit)
{
    std::vector<double>* vecValue = (std::vector<double>*)voidValue;
    std::vector<int32_t>* vecUnit = (std::vector<int32_t>*)voidUnit;

    if (vecValue == nullptr) {
        LOGE("rect radius array is empty");
        return;
    }
    unsigned int length = vecValue->size() > 4 ? 4 : vecValue->size();
    for (unsigned int i = 0; i < length; ++i) {
        DimensionUnit unit = DimensionUnit::VP;
        if (vecUnit != nullptr && i < vecUnit->size()) {
            unit = static_cast<DimensionUnit>(vecUnit->at(i));
        }

        Dimension value(vecValue->at(i), static_cast<DimensionUnit>(unit));
        RectModel::GetInstance()->SetRadiusValue(value, value, i);
    }
}

void FfiOHOSAceFrameworkRectSetRadiusTupleArray(VectorDoubleHandle voidWidthValue, VectorInt32Handle voidWidthUnit,
    VectorDoubleHandle voidHeightValue, VectorInt32Handle voidHeightUnit)
{
    std::vector<double>* vecWidthValue = (std::vector<double>*)voidWidthValue;
    std::vector<int32_t>* vecWidthUnit = (std::vector<int32_t>*)voidWidthUnit;
    std::vector<double>* vecHeightValue = (std::vector<double>*)voidHeightValue;
    std::vector<int32_t>* vecHeightUnit = (std::vector<int32_t>*)voidHeightUnit;

    if (vecWidthValue == nullptr) {
        LOGE("rect radius array is empty");
        return;
    }
    unsigned int length = vecWidthValue->size() > 4 ? 4 : vecWidthValue->size();
    for (unsigned int i = 0; i < length; ++i) {
        DimensionUnit widthUnit = DimensionUnit::VP;
        DimensionUnit heightUnit = DimensionUnit::VP;

        if (vecWidthUnit != nullptr && i < vecWidthUnit->size()) {
            widthUnit = static_cast<DimensionUnit>(vecWidthUnit->at(i));
        }

        if (vecHeightUnit != nullptr && i < vecHeightUnit->size()) {
            heightUnit = static_cast<DimensionUnit>(vecHeightUnit->at(i));
        }

        Dimension width(vecWidthValue->at(i), widthUnit);
        Dimension height(vecHeightValue->at(i), heightUnit);

        RectModel::GetInstance()->SetRadiusValue(width, height, i);
    }
}

void FfiOHOSAceFrameworkRectSetInsRadiusWidth(int64_t shapeId, double radiusWidth, int32_t radiusWidthUnit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeRect>(shapeId);
    if (context != nullptr) {
        Dimension dValue(radiusWidth, static_cast<DimensionUnit>(radiusWidthUnit));
        context->SetRadiusWidth(dValue);
    } else {
        LOGI("set shape radiusWidth error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkRectSetInsRadiusHeight(int64_t shapeId, double radiusHeight, int32_t radiusHeightUnit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeRect>(shapeId);
    if (context != nullptr) {
        Dimension dValue(radiusHeight, static_cast<DimensionUnit>(radiusHeightUnit));
        context->SetRadiusHeight(dValue);
    } else {
        LOGI("set shape radiusHeight error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkRectSetInsRadius(int64_t shapeId, double radius, int32_t radiusUnit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeRect>(shapeId);
    if (context != nullptr) {
        Dimension dValue(radius, static_cast<DimensionUnit>(radiusUnit));
        context->SetRadius(dValue);
    } else {
        LOGI("set shape radius error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}
}
