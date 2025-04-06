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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"


#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"

#ifndef _NON_OHOS_
#include "pixel_map_impl.h"
#endif

using namespace OHOS::Ace;

namespace {
using VectorDoublePtr = void*;
using VectorInt32Ptr = void*;
const std::vector<LineCapStyle> LINE_CAP_STYLE_LIST = { LineCapStyle::BUTT, LineCapStyle::ROUND, LineCapStyle::SQUARE };
const std::vector<LineJoinStyle> LINE_JOIN_STYLE_LIST = { LineJoinStyle::MITER, LineJoinStyle::ROUND,
    LineJoinStyle::BEVEL };
} // namespace
extern "C" {
void FfiOHOSAceFrameworkShapeCreate()
{
    ShapeModel::GetInstance()->Create();
    ViewAbstractModel::GetInstance()->SetFocusable(true);
    RefPtr<PixelMap> pixMapOhos = nullptr;
    ShapeModel::GetInstance()->InitBox(pixMapOhos);
}

void FfiOHOSAceFrameworkShapeCreateWithPixelMap(int64_t pixelMapId)
{
#ifndef _NON_OHOS_
    ShapeModel::GetInstance()->Create();
    ViewAbstractModel::GetInstance()->SetFocusable(true);
    RefPtr<PixelMap> pixMapOhos = nullptr;
    do {
        if (pixelMapId <= 0) {
            LOGI("pixel map ID not valid");
            break;
        }
        auto instance = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
        if (instance == nullptr) {
            LOGE("create with pixel map error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
            break;
        }
        std::shared_ptr<OHOS::Media::PixelMap> pixelMap = instance->GetRealPixelMap();
        if (pixelMap == nullptr) {
            LOGE("create with pixel map error, Cannot get pixMap in PixelMapProxy");
            break;
        }
        pixMapOhos = PixelMap::CreatePixelMap(&pixelMap);
        if (pixMapOhos == nullptr) {
            LOGE("create with pixel map error, Cannot create PixelMapOhos by pixMap");
            break;
        }
    } while (false);
    ShapeModel::GetInstance()->InitBox(pixMapOhos);
#endif
}

void FfiOHOSAceFrameworkShapeSetViewPort(FFIAtCViewPort viewPort)
{
    Dimension dimLeft(viewPort.x, static_cast<DimensionUnit>(viewPort.unitX));
    Dimension dimTop(viewPort.y, static_cast<DimensionUnit>(viewPort.unitY));
    Dimension dimWidth(viewPort.width, static_cast<DimensionUnit>(viewPort.unitWidth));
    Dimension dimHeight(viewPort.height, static_cast<DimensionUnit>(viewPort.unitHeight));
    ShapeModel::GetInstance()->SetViewPort(dimLeft, dimTop, dimWidth, dimHeight);
}

void FfiOHOSAceFrameworkShapeSetFill(uint32_t color)
{
    ShapeModel::GetInstance()->SetFill(Color(color));
}

void FfiOHOSAceFrameworkShapeSetFillOpacity(double fillOpacity)
{
    // Not display when fill opacity is negative
    if (fillOpacity < 0.0f) {
        fillOpacity = 0.0f;
    }
    ShapeModel::GetInstance()->SetFillOpacity(fillOpacity);
}

void FfiOHOSAceFrameworkShapeSetStroke(uint32_t color)
{
    ShapeModel::GetInstance()->SetStroke(Color(color));
}

void FfiOHOSAceFrameworkShapeSetStrokeDashArray(VectorFloat64Ptr vecValue, VectorInt32Ptr vecUnit)
{
    const auto& dashValue = *reinterpret_cast<std::vector<double>*>(vecValue);
    const auto& dashUnit = *reinterpret_cast<std::vector<int32_t>*>(vecUnit);
    std::vector<Dimension> dashArray;

    for (size_t i = 0; i < dashValue.size(); ++i) {
        DimensionUnit defaultUnit = DimensionUnit::VP;
        if (i < dashUnit.size()) {
            defaultUnit = static_cast<DimensionUnit>(dashUnit.at(i));
        }
        dashArray.emplace_back(Dimension(dashValue.at(i), defaultUnit));
    }
    // if odd,add twice
    if ((static_cast<uint32_t>(dashValue.size()) & 1)) {
        for (size_t i = 0; i < dashValue.size(); i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeModel::GetInstance()->SetStrokeDashArray(dashArray);
}

void FfiOHOSAceFrameworkShapeSetStrokeDashOffset(double offset, int32_t offsetUnit)
{
    Dimension dimOffset(offset, static_cast<DimensionUnit>(offsetUnit));
    ShapeModel::GetInstance()->SetStrokeDashOffset(dimOffset);
}

void FfiOHOSAceFrameworkShapeSetStrokeLineCap(int32_t lineCap)
{
    if (lineCap < 0 || lineCap >= static_cast<int32_t>(LINE_CAP_STYLE_LIST.size())) {
        return;
    }
    ShapeModel::GetInstance()->SetStrokeLineCap(static_cast<int32_t>(LINE_CAP_STYLE_LIST[lineCap]));
}

void FfiOHOSAceFrameworkShapeSetStrokeLineJoin(int32_t lineJoin)
{
    if (lineJoin < 0 || lineJoin >= static_cast<int32_t>(LINE_JOIN_STYLE_LIST.size())) {
        return;
    }
    ShapeModel::GetInstance()->SetStrokeLineJoin(static_cast<int32_t>(LINE_JOIN_STYLE_LIST[lineJoin]));
}

void FfiOHOSAceFrameworkShapeSetStrokeMiterLimit(double miterLimit)
{
    ShapeModel::GetInstance()->SetStrokeMiterLimit(miterLimit);
}

void FfiOHOSAceFrameworkShapeSetStrokeOpacity(double strokeOpacity)
{
    // Not display when fill stroke is negative
    if (strokeOpacity < 0.0f) {
        strokeOpacity = 0.0f;
    }
    ShapeModel::GetInstance()->SetStrokeOpacity(strokeOpacity);
}

void FfiOHOSAceFrameworkShapeSetStrokeWidth(double strokeWidth, int32_t widthUnit)
{
    Dimension dimStrokeWidth(strokeWidth, static_cast<DimensionUnit>(widthUnit));
    ShapeModel::GetInstance()->SetStrokeWidth(dimStrokeWidth);
}

void FfiOHOSAceFrameworkShapeSetAntiAlias(bool antiAlias)
{
    ShapeModel::GetInstance()->SetAntiAlias(antiAlias);
}

void FfiOHOSAceFrameworkShapeSetMesh(VectorFloat64Handle vecValue, uint32_t column, uint32_t row)
{
    if (vecValue == nullptr) {
        LOGE("mesh array is empty");
        return;
    }
    auto meshValue = reinterpret_cast<std::vector<double>*>(vecValue);
    LOGI("FfiOHOSAceFrameworkShapeSetMesh mesh meshValue szie: %{public}d", meshValue->size());
    auto tempMeshSize = static_cast<uint64_t>(column + 1) * (row + 1) * 2;
    if (tempMeshSize != meshValue->size()) {
        ShapeModel::GetInstance()->SetBitmapMesh(std::vector<float>(), 0, 0);
        return;
    }
    std::vector<float> mesh;
    for (size_t i = 0; i < meshValue->size(); ++i) {
        mesh.emplace_back(static_cast<float>((*meshValue)[i]));
    }
    ShapeModel::GetInstance()->SetBitmapMesh(mesh, static_cast<int32_t>(column), static_cast<int32_t>(row));
}

void FfiOHOSAceFrameworkShapeSetWidth(double width, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);
    ShapeModel::GetInstance()->SetWidth();
}

void FfiOHOSAceFrameworkShapeSetHeight(double height, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
    ShapeModel::GetInstance()->SetHeight();
}

void FfiOHOSAceFrameworkShapeSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    FfiOHOSAceFrameworkShapeSetWidth(width, widthUnit);
    FfiOHOSAceFrameworkShapeSetHeight(height, heightUnit);
}

void FfiOHOSAceFrameworkShapeSetInsWidth(int64_t shapeId, double value, int32_t unit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        Dimension dValue(value, static_cast<DimensionUnit>(unit));
        if (LessNotEqual(dValue.Value(), 0.0)) {
            dValue.SetValue(0.0);
        }
        context->SetWidth(dValue);
    } else {
        LOGI("set shape width error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkShapeSetInsHeight(int64_t shapeId, double value, int32_t unit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        Dimension dValue(value, static_cast<DimensionUnit>(unit));
        if (LessNotEqual(dValue.Value(), 0.0)) {
            dValue.SetValue(0.0);
        }
        context->SetHeight(dValue);
    } else {
        LOGI("set shape height error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkShapeSetInsSize(
    int64_t shapeId, double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        Dimension dWidth(width, static_cast<DimensionUnit>(widthUnit));
        Dimension dHeight(height, static_cast<DimensionUnit>(heightUnit));
        if (LessNotEqual(dWidth.Value(), 0.0)) {
            dWidth.SetValue(0.0);
        }
        if (LessNotEqual(dHeight.Value(), 0.0)) {
            dHeight.SetValue(0.0);
        }
        context->SetSize(dWidth, dHeight);
    } else {
        LOGI("set shape size error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkShapeSetInsOffset(int64_t shapeId, double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension offsetX(x, static_cast<DimensionUnit>(xUnit));
    Dimension offsetY(y, static_cast<DimensionUnit>(yUnit));
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        context->SetOffset(offsetX, offsetY);
    } else {
        LOGI("set shape offset error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkShapeSetInsFill(int64_t shapeId, uint32_t color)
{
    auto context = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        context->SetFill(Color(color));
    } else {
        LOGI("set shape fill error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}
}
