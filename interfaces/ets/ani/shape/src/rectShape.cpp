/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "shape.h"

namespace OHOS::Ace {
namespace {
const char* ANI_SHAPE_NAME = "@ohos.arkui.shape.RectShape";
void ParseWidthAndHeight(ani_env* env, ani_object object, OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect>& rectShape)
{
    std::optional<OHOS::Ace::CalcDimension> widthOpt;
    std::optional<OHOS::Ace::CalcDimension> heightOpt;
    ani_ref width_ref;
    ani_ref height_ref;
    if (env->Object_GetPropertyByName_Ref(object, "width", &width_ref) != ANI_OK) {
        return;
    }
    ParseStringNumberUndefinedObject(env, width_ref, OHOS::Ace::DimensionUnit::VP, widthOpt);
    if (widthOpt.has_value() && widthOpt->IsValid()) {
        rectShape->SetWidth(widthOpt.value());
    }
    if (env->Object_GetPropertyByName_Ref(object, "height", &height_ref) != ANI_OK) {
        return;
    }
    ParseStringNumberUndefinedObject(env, height_ref, OHOS::Ace::DimensionUnit::VP, heightOpt);
    if (heightOpt.has_value() && heightOpt->IsValid()) {
        rectShape->SetHeight(heightOpt.value());
    }
}
}

void ANICreateRectShape(ani_env* env, [[maybe_unused]] ani_object object)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGE("Not find RectShape class, status:%{public}d", status);
        return;
    }
    RectPeer* shapePeer = new RectPeer();
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    shapePeer->rectShape = rect;

    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("RectShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

void ANICreateRectShapeWithParam(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return;
    }

    RectPeer* shapePeer = new RectPeer();
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    ani_status status;

    if (IsInstanceOfCls(env, aniOption, "@ohos.arkui.shape.RectShapeOptions")) {
        ani_ref params_ref;
        if ((status = env->Object_GetPropertyByName_Ref(aniOption, "radius", &params_ref)) != ANI_OK) {
            LOGE("Get radius failed, status:%{public}d", status);
            delete shapePeer;
            return;
        }
        if (!GetIsUndefinedObject(env, params_ref) && GetIsArrayObject(env, params_ref)) {
            OHOS::Ace::CalcDimension radius;
            ParseArray(env, rect, static_cast<ani_object>(params_ref));
        } else {
            std::optional<OHOS::Ace::CalcDimension> radiusOpt;
            if (ParseStringNumberUndefinedObject(env, params_ref, OHOS::Ace::DimensionUnit::VP, radiusOpt) &&
                radiusOpt.has_value()) {
                rect->SetRadiusWidth(radiusOpt.value());
                rect->SetRadiusHeight(radiusOpt.value());
            }
        }
    } else if (IsInstanceOfCls(env, aniOption, "@ohos.arkui.shape.RoundRectShapeOptions")) {
        std::optional<OHOS::Ace::CalcDimension> radiusWidthOpt;
        if (ParseStringNumberUndefinedOption(
            env, aniOption, radiusWidthOpt, "radiusWidth", "@ohos.arkui.shape.RoundRectShapeOptions") &&
            radiusWidthOpt.has_value()) {
            rect->SetRadiusWidth(radiusWidthOpt.value());
        }
        std::optional<OHOS::Ace::CalcDimension> radiusHeightOpt;
        if (ParseStringNumberUndefinedOption(
            env, aniOption, radiusHeightOpt, "radiusHeight", "@ohos.arkui.shape.RoundRectShapeOptions") &&
            radiusHeightOpt.has_value()) {
            rect->SetRadiusHeight(radiusHeightOpt.value());
        }
    }
    ParseWidthAndHeight(env, aniOption, rect);
    shapePeer->rectShape = rect;
    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("RectShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

RectPeer* GetRectShape(ani_env* env, ani_object obj)
{
    ani_long rectAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "basicShapeResult", &rectAni)) {
        return nullptr;
    }

    auto rect = reinterpret_cast<RectPeer*>(rectAni);
    return rect;
}

ani_object ANIRectShapeWidth(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    CHECK_NULL_RETURN(rectObj, object);
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetWidth(width);
    }
    return object;
}

ani_object ANIRectShapeHeight(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    CHECK_NULL_RETURN(rectObj, object);
    CalcDimension height;
    if (!ParseLength(env, object, aniOption, height)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetHeight(height);
    }
    return object;
}

ani_object ANIRectShapeSize(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    CalcDimension width;
    ParseOption(env, aniOption, width, "width", "arkui.component.units.SizeOptions");
    if (rectObj->rectShape) {
        rectObj->rectShape->SetWidth(width);
    }
    CalcDimension height;
    ParseOption(env, aniOption, height, "height", "arkui.component.units.SizeOptions");
    if (rectObj->rectShape) {
        rectObj->rectShape->SetHeight(height);
    }
    return object;
}

ani_object ANIRectShapePosition(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (rectObj->rectShape) {
        rectObj->rectShape->SetPosition(position);
    }
    return object;
}

ani_object ANIRectShapeOffset(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (rectObj->rectShape) {
        rectObj->rectShape->SetOffset(position);
    }
    return object;
}

ani_object ANIRectShapeColor(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    OHOS::Ace::Color resourceColor;
    if (!ParseAniColor(env, aniOption, resourceColor)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetColor(resourceColor);
    }
    return object;
}

ani_object ANIRectShapeRadiusWidth(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    std::optional<OHOS::Ace::CalcDimension> radiusVal;
    if (!ParseStringNumberUndefinedObject(
        env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetRadiusWidth(radiusVal.value_or(OHOS::Ace::CalcDimension()));
    }
    return object;
}

ani_object ANIRectShapeRadiusHeight(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    std::optional<OHOS::Ace::CalcDimension> radiusVal;
    if (!ParseStringNumberUndefinedObject(
        env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetRadiusHeight(radiusVal.value_or(OHOS::Ace::CalcDimension()));
    }
    return object;
}

ani_object ANIRectShapeRadius(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    RectPeer* rectObj = GetRectShape(env, object);
    if (!rectObj) {
        return object;
    }
    if (!rectObj->rectShape) {
        return object;
    }
    if (GetIsArrayObject(env, static_cast<ani_ref>(aniOption))) {
        OHOS::Ace::CalcDimension radius;
        ParseArray(env, rectObj->rectShape, aniOption);
    } else {
        std::optional<OHOS::Ace::CalcDimension> radiusVal;
        ParseStringNumberUndefinedObject(env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal);
        auto radius = radiusVal.value_or(OHOS::Ace::CalcDimension());
        rectObj->rectShape->SetRadiusWidth(radius);
        rectObj->rectShape->SetRadiusHeight(radius);
    }
    return object;
}

ani_object RectShape::ANIRectShapeFromPtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    return ANIShapeFromPtr<RectPeer>(env, ptr, ANI_SHAPE_NAME, "basicShapeResult");
}

ani_status RectShape::BindRectShape(ani_env* env)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(ANICreateRectShape) },
        ani_native_function { "<ctor>",
            "X{C{@ohos.arkui.shape.RectShapeOptions}C{@ohos.arkui.shape.RoundRectShapeOptions}}:",
            reinterpret_cast<void*>(ANICreateRectShapeWithParam) },
        ani_native_function { "width", nullptr, reinterpret_cast<void*>(ANIRectShapeWidth) },
        ani_native_function { "radiusWidth", nullptr, reinterpret_cast<void*>(ANIRectShapeRadiusWidth) },
        ani_native_function { "radiusHeight", nullptr, reinterpret_cast<void*>(ANIRectShapeRadiusHeight) },
        ani_native_function { "radius", nullptr, reinterpret_cast<void*>(ANIRectShapeRadius) },
        ani_native_function { "height", nullptr, reinterpret_cast<void*>(ANIRectShapeHeight) },
        ani_native_function { "size", nullptr, reinterpret_cast<void*>(ANIRectShapeSize) },
        ani_native_function { "position", nullptr, reinterpret_cast<void*>(ANIRectShapePosition) },
        ani_native_function { "offset", nullptr, reinterpret_cast<void*>(ANIRectShapeOffset) },
        ani_native_function { "fill", nullptr, reinterpret_cast<void*>(ANIRectShapeColor) },
    };
    ani_status tmp = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != tmp) {
        LOGW("bind Rect methods error, status:%{public}d", tmp);
        return ANI_ERROR;
    }
    return ANI_OK;
}
} // namespace OHOS::Ace