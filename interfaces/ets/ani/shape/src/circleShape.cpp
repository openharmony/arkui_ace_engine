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
const char* ANI_SHAPE_NAME = "@ohos.arkui.shape.CircleShape";
} // namespace

void ANICreateCircleShape(ani_env* env, [[maybe_unused]] ani_object object)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGE("Not find CircleShape class, status:%{public}d", status);
        return;
    }
    CirclePeer* shapePeer = new CirclePeer();
    auto circle = AceType::MakeRefPtr<Circle>();
    shapePeer->circleShape = circle;

    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("CircleShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

void ANICreateCircleShapeWithParam(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return;
    }
    if (!IsInstanceOfCls(env, object, ANI_SHAPE_NAME)) {
        return;
    }
    CirclePeer* shapePeer = new CirclePeer();
    auto circle = AceType::MakeRefPtr<Circle>();
    std::optional<OHOS::Ace::CalcDimension> width;
    ParseStringNumberUndefinedOption(env, aniOption, width, "width", "@ohos.arkui.shape.ShapeSize");
    if (width.has_value() && width->IsValid()) {
        circle->SetWidth(width.value());
    }
    std::optional<OHOS::Ace::CalcDimension> height;
    ParseStringNumberUndefinedOption(env, aniOption, height, "height", "@ohos.arkui.shape.ShapeSize");
    if (height.has_value() && height->IsValid()) {
        circle->SetHeight(height.value());
    }
    shapePeer->circleShape = circle;

    ani_status status;
    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("CircleShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

CirclePeer* GetCircleShape(ani_env* env, ani_object obj)
{
    ani_long circleAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "basicShapeResult", &circleAni)) {
        return nullptr;
    }

    auto circle = reinterpret_cast<CirclePeer*>(circleAni);
    return circle;
}

ani_object ANICircleShapeWidth(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return nullptr;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (circleObj->circleShape) {
        circleObj->circleShape->SetWidth(width);
    }
    return object;
}

ani_object ANICircleShapeHeight(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return nullptr;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (circleObj->circleShape) {
        circleObj->circleShape->SetHeight(width);
    }
    return object;
}

ani_object ANICircleShapeSize(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    CalcDimension width;
    ParseOption(env, aniOption, width, "width", "arkui.component.units.SizeOptions");
    if (circleObj->circleShape) {
        circleObj->circleShape->SetWidth(width);
    }
    CalcDimension height;
    ParseOption(env, aniOption, height, "height", "arkui.component.units.SizeOptions");
    if (circleObj->circleShape) {
        circleObj->circleShape->SetHeight(height);
    }
    return object;
}

ani_object ANICircleShapePosition(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (circleObj->circleShape) {
        circleObj->circleShape->SetPosition(position);
    }
    return object;
}

ani_object ANICircleShapeOffset(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (circleObj->circleShape) {
        circleObj->circleShape->SetOffset(position);
    }
    return object;
}

ani_object ANICircleShapeColor(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    OHOS::Ace::Color resourceColor;
    if (!ParseAniColor(env, aniOption, resourceColor)) {
        return object;
    }
    CirclePeer* circleObj = GetCircleShape(env, object);
    if (!circleObj) {
        return object;
    }
    if (circleObj->circleShape) {
        circleObj->circleShape->SetColor(resourceColor);
    }
    return object;
}

ani_object CircleShape::ANICircleShapeFromPtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    return ANIShapeFromPtr<CirclePeer>(env, ptr, ANI_SHAPE_NAME, "basicShapeResult");
}

ani_status CircleShape::BindCircleShape(ani_env* env)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGW("find CircleShape class error, status:%{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(ANICreateCircleShape) },
        ani_native_function {
            "<ctor>", "C{@ohos.arkui.shape.ShapeSize}:", reinterpret_cast<void*>(ANICreateCircleShapeWithParam) },
        ani_native_function { "width", nullptr, reinterpret_cast<void*>(ANICircleShapeWidth) },
        ani_native_function { "height", nullptr, reinterpret_cast<void*>(ANICircleShapeHeight) },
        ani_native_function { "size", nullptr, reinterpret_cast<void*>(ANICircleShapeSize) },
        ani_native_function { "position", nullptr, reinterpret_cast<void*>(ANICircleShapePosition) },
        ani_native_function { "offset", nullptr, reinterpret_cast<void*>(ANICircleShapeOffset) },
        ani_native_function { "fill", nullptr, reinterpret_cast<void*>(ANICircleShapeColor) },
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != status) {
        LOGW("bind CircleShape methods error, status:%{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}
} // namespace OHOS::Ace