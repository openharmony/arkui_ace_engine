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

#include "shapeUtil.h"

namespace OHOS::Ace {
namespace {
const char* ANI_COMMON_SHAPE_NAME = "@ohos.arkui.shape.CommonShapeMethod";
const char* ANI_BASIC_SHAPE_NAME = "@ohos.arkui.shape.BaseShape";
ani_status BindShapeInnerMethods(ani_env* env)
{
    static const char* className = "@ohos.arkui.shape.__ShapeInnerMethods__";
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(className, &cls)) != ANI_OK) {
        LOGW("find shapeInnerMethods class error, status:%{public}d", status);
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function { "CircleFromPtr", nullptr, reinterpret_cast<void*>(CircleShape::ANICircleShapeFromPtr) },
        ani_native_function { "RectFromPtr", nullptr, reinterpret_cast<void*>(RectShape::ANIRectShapeFromPtr) },
        ani_native_function {
            "EllipseFromPtr", nullptr, reinterpret_cast<void*>(EllipseShape::ANIEllipseShapeFromPtr) },
        ani_native_function { "PathFromPtr", nullptr, reinterpret_cast<void*>(PathShape::ANIPathShapeFromPtr) },
    };
    status = env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size());
    if (status != ANI_OK) {
        LOGW("bind shapeInnerMethods error, status:%{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}

BasicPeer* GetBasicShape(ani_env* env, ani_object obj)
{
    ani_long basicAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "basicShapeResult", &basicAni)) {
        return nullptr;
    }
    auto circle = reinterpret_cast<BasicPeer*>(basicAni);
    return circle;
}

ani_object ANIBasicShapePosition(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (basicObj->basicShape) {
        basicObj->basicShape->SetPosition(position);
    }
    return object;
}

ani_object ANIBasicShapeOffset(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (basicObj->basicShape) {
        basicObj->basicShape->SetOffset(position);
    }
    return object;
}

ani_object ANIBasicShapeColor(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    OHOS::Ace::Color resourceColor;
    if (!ParseAniColor(env, aniOption, resourceColor)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    if (basicObj->basicShape) {
        basicObj->basicShape->SetColor(resourceColor);
    }
    return object;
}

ani_object ANIBasicShapeWidth(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (basicObj->basicShape) {
        basicObj->basicShape->SetWidth(width);
    }
    return object;
}

ani_object ANIBasicShapeHeight(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    CalcDimension width;
    if (!ParseLength(env, object, aniOption, width)) {
        return object;
    }
    if (basicObj->basicShape) {
        basicObj->basicShape->SetHeight(width);
    }
    return object;
}

ani_object ANIBasicShapeSize(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    BasicPeer* basicObj = GetBasicShape(env, object);
    if (!basicObj) {
        return object;
    }
    CalcDimension width;
    ParseOption(env, aniOption, width, "width", "arkui.component.units.SizeOptions");
    if (basicObj->basicShape) {
        basicObj->basicShape->SetWidth(width);
    }
    CalcDimension height;
    ParseOption(env, aniOption, height, "height", "arkui.component.units.SizeOptions");
    if (basicObj->basicShape) {
        basicObj->basicShape->SetHeight(height);
    }
    return object;
}

ani_status BindCommonMethod(ani_env* env)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_COMMON_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGW("BindCommonMethod class error, status:%{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "position", nullptr, reinterpret_cast<void*>(ANIBasicShapePosition) },
        ani_native_function { "offset", nullptr, reinterpret_cast<void*>(ANIBasicShapeOffset) },
        ani_native_function { "fill", nullptr, reinterpret_cast<void*>(ANIBasicShapeColor) },
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != status) {
        LOGW("BindCommonMethod methods error, status:%{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}

ani_status BindBasicMethod(ani_env* env)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_BASIC_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGW("BindBasicMethod class error, status:%{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "width", nullptr, reinterpret_cast<void*>(ANIBasicShapeWidth) },
        ani_native_function { "height", nullptr, reinterpret_cast<void*>(ANIBasicShapeHeight) },
        ani_native_function { "size", nullptr, reinterpret_cast<void*>(ANIBasicShapeSize) },
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != status) {
        LOGW("BindBasicMethod methods error, status:%{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}
} // namespace
} // namespace OHOS::Ace

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_status retBindCommonMethod = OHOS::Ace::BindCommonMethod(env);
    if (retBindCommonMethod == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    ani_status retBasicMethod = OHOS::Ace::BindBasicMethod(env);
    if (retBasicMethod == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    ani_status retCircleBind = OHOS::Ace::CircleShape::BindCircleShape(env);
    if (retCircleBind == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    ani_status retEllipseBind = OHOS::Ace::EllipseShape::BindEllipseShape(env);
    if (retEllipseBind == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    ani_status retPathBind = OHOS::Ace::PathShape::BindPathShape(env);
    if (retPathBind == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    ani_status retRectBind = OHOS::Ace::RectShape::BindRectShape(env);
    if (retRectBind == ANI_OK) {
        *result = ANI_VERSION_1;
    }

    OHOS::Ace::BindShapeInnerMethods(env);
    *result = ANI_VERSION_1;
    return ANI_OK;
}