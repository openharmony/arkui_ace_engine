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
struct EllipsePeer {
    OHOS::Ace::RefPtr<OHOS::Ace::Ellipse> ellipseShape;
};

void ANICreateEllipseShape(ani_env* env, [[maybe_unused]] ani_object object)
{
    static const char* className = "@ohos.arkui.shape.EllipseShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return;
    }
    EllipsePeer* shapePeer = new EllipsePeer();
    auto ellipse = AceType::MakeRefPtr<Ellipse>();
    shapePeer->ellipseShape = ellipse;

    if (ANI_OK !=
        env->Object_SetPropertyByName_Long(object, "ellipseShapeResult", reinterpret_cast<ani_long>(shapePeer))) {
        return;
    }
}

void ANICreateEllipseShapeWithParam(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return;
    }
    static const char* className = "@ohos.arkui.shape.EllipseShape";
    if (!IsInstanceOfCls(env, object, className)) {
        return;
    }

    EllipsePeer* shapePeer = new EllipsePeer();
    auto ellipse = AceType::MakeRefPtr<Ellipse>();

    OHOS::Ace::CalcDimension width;
    ParseStringAndNumberOption(
        env, aniOption, width, "width", "@ohos.arkui.shape.ShapeSize");
    ellipse->SetWidth(width);

    OHOS::Ace::CalcDimension height;
    ParseStringAndNumberOption(
        env, aniOption, height, "height", "@ohos.arkui.shape.ShapeSize");
    ellipse->SetHeight(height);
    shapePeer->ellipseShape = ellipse;
    if (ANI_OK !=
        env->Object_SetPropertyByName_Long(object, "ellipseShapeResult", reinterpret_cast<ani_long>(shapePeer))) {
        return;
    }
}

EllipsePeer* GetEllipseShape(ani_env* env, ani_object obj)
{
    ani_long ellipseAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "ellipseShapeResult", &ellipseAni)) {
        return nullptr;
    }

    auto ellipse = reinterpret_cast<EllipsePeer*>(ellipseAni);
    return ellipse;
}

ani_object ANIEllipseShapeWidth(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    static const char* className = "@ohos.arkui.shape.EllipseShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetWidth(width);
    }
    return object;
}

ani_object ANIEllipseShapeHeight(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    static const char* className = "@ohos.arkui.shape.EllipseShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetHeight(width);
    }
    return object;
}

ani_object ANIEllipseShapeSize(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    CalcDimension width;
    ParseOption(env, aniOption, width, "width", "arkui.component.units.SizeOptions");
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetWidth(width);
    }
    CalcDimension height;
    ParseOption(env, aniOption, height, "height", "arkui.component.units.SizeOptions");
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetHeight(height);
    }
    return object;
}

ani_object ANIEllipseShapePosition(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetPosition(position);
    }
    return object;
}

ani_object ANIEllipseShapeOffset(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetOffset(position);
    }
    return object;
}

ani_object ANIEllipseShapeColor(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    OHOS::Ace::Color resourceColor;
    if (!ParseAniColor(env, aniOption, resourceColor)) {
        return object;
    }
    EllipsePeer* ellipseObj = GetEllipseShape(env, object);
    if (!ellipseObj) {
        return object;
    }
    if (ellipseObj->ellipseShape) {
        ellipseObj->ellipseShape->SetColor(resourceColor);
    }
    return object;
}

ani_status EllipseShape::BindEllipseShape(ani_env* env)
{
    static const char* className = "@ohos.arkui.shape.EllipseShape";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(ANICreateEllipseShape) },
        ani_native_function {
            "<ctor>", "C{@ohos.arkui.shape.ShapeSize}:", reinterpret_cast<void*>(ANICreateEllipseShapeWithParam) },
        ani_native_function { "width", nullptr, reinterpret_cast<void*>(ANIEllipseShapeWidth) },
        ani_native_function { "height", nullptr, reinterpret_cast<void*>(ANIEllipseShapeHeight) },
        ani_native_function { "size", nullptr, reinterpret_cast<void*>(ANIEllipseShapeSize) },
        ani_native_function { "position", nullptr, reinterpret_cast<void*>(ANIEllipseShapePosition) },
        ani_native_function { "offset", nullptr, reinterpret_cast<void*>(ANIEllipseShapeOffset) },
        ani_native_function { "fill", nullptr, reinterpret_cast<void*>(ANIEllipseShapeColor) },
    };
    ani_status tmp = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != tmp) {
        return ANI_ERROR;
    };
    return ANI_OK;
}
} // namespace OHOS::Ace