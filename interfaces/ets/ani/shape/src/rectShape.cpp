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
struct RectPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect> rectShape;
};

void ANICreateRectShape(ani_env* env, [[maybe_unused]] ani_object object)
{
    static const char* className = "@ohos.arkui.shape.RectShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return;
    }
    RectPeer* shapePeer = new RectPeer();
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    shapePeer->rectShape = rect;

    if (ANI_OK !=
        env->Object_SetPropertyByName_Long(object, "rectShapeResult", reinterpret_cast<ani_long>(shapePeer))) {
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

    if (IsInstanceOfCls(env, aniOption, "@ohos.arkui.shape.RectShapeOptions")) {
        ani_ref params_ref;
        if (ANI_OK != env->Object_GetPropertyByName_Ref(aniOption, "radius", &params_ref)) {
            return;
        }
        if (GetIsArrayObject(env, params_ref)) {
            OHOS::Ace::CalcDimension radius;
            ParseArray(env, rect, static_cast<ani_object>(params_ref));
        } else {
            OHOS::Ace::CalcDimension radiusVal;
            ParseStringAndNumberObject(env, params_ref, OHOS::Ace::DimensionUnit::VP, radiusVal);
            rect->SetRadiusWidth(radiusVal);
            rect->SetRadiusWidth(radiusVal);
        }
    } else if (IsInstanceOfCls(env, aniOption, "@ohos.arkui.shape.RoundRectShapeOptions")) {
        OHOS::Ace::CalcDimension radiusWidthVal;
        ParseStringAndNumberOption(env, aniOption, radiusWidthVal, "radiusWidth",
            "@ohos.arkui.shape.RoundRectShapeOptions");
        OHOS::Ace::CalcDimension radiusHeightVal;
        ParseStringAndNumberOption(env, aniOption, radiusHeightVal, "radiusHeight",
            "@ohos.arkui.shape.RoundRectShapeOptions");
        rect->SetRadiusWidth(radiusWidthVal);
        rect->SetRadiusHeight(radiusHeightVal);
    }
    shapePeer->rectShape = rect;
    if (ANI_OK !=
        env->Object_SetPropertyByName_Long(object, "rectShapeResult", reinterpret_cast<ani_long>(shapePeer))) {
        return;
    }
}

RectPeer* GetRectShape(ani_env* env, ani_object obj)
{
    ani_long rectAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "rectShapeResult", &rectAni)) {
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
    static const char* className = "@ohos.arkui.shape.RectShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    RectPeer* rectObj = GetRectShape(env, object);
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
    static const char* className = "@ohos.arkui.shape.RectShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    RectPeer* rectObj = GetRectShape(env, object);
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
    OHOS::Ace::CalcDimension radiusVal;
    if (!ParseStringAndNumberObject(env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetRadiusWidth(radiusVal);
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
    OHOS::Ace::CalcDimension radiusVal;
    if (!ParseStringAndNumberObject(env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal)) {
        return object;
    }
    if (rectObj->rectShape) {
        rectObj->rectShape->SetRadiusHeight(radiusVal);
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
        OHOS::Ace::CalcDimension radiusVal;
        ParseStringAndNumberObject(env, static_cast<ani_ref>(aniOption), OHOS::Ace::DimensionUnit::VP, radiusVal);
        rectObj->rectShape->SetRadiusWidth(radiusVal);
        rectObj->rectShape->SetRadiusWidth(radiusVal);
    }
    return object;
}

ani_status RectShape::BindRectShape(ani_env* env)
{
    static const char* className = "@ohos.arkui.shape.RectShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(ANICreateRectShape) },
        ani_native_function { "<ctor>", "C{std.core.Object}:", reinterpret_cast<void*>(ANICreateRectShapeWithParam) },
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
        return ANI_ERROR;
    };
    return ANI_OK;
}
} // namespace OHOS::Ace