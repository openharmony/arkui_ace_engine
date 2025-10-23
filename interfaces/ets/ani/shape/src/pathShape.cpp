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
const char* ANI_SHAPE_NAME = "@ohos.arkui.shape.PathShape";
} // namespace

void ANICreatePathShape(ani_env* env, [[maybe_unused]] ani_object object)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass(ANI_SHAPE_NAME, &cls)) != ANI_OK) {
        LOGE("Not find PathShape class, status:%{public}d", status);
        return;
    }
    PathPeer* shapePeer = new PathPeer();
    auto path = AceType::MakeRefPtr<Path>();
    shapePeer->pathShape = path;

    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("PathShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

void ANICreatePathShapeWithParam(
    ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return;
    }
    if (!IsInstanceOfCls(env, object, ANI_SHAPE_NAME)) {
        return;
    }
    std::string commands = ParseCommands(env, aniOption);
    PathPeer* shapePeer = new PathPeer();
    auto path = AceType::MakeRefPtr<Path>();
    path->SetValue(commands);
    shapePeer->pathShape = path;

    ani_status status;
    if ((status = env->Object_SetPropertyByName_Long(
             object, "basicShapeResult", reinterpret_cast<ani_long>(shapePeer))) != ANI_OK) {
        LOGE("PathShape set addr failed, status:%{public}d", status);
        delete shapePeer;
        return;
    }
}

PathPeer* GetPathShape(ani_env* env, ani_object obj)
{
    ani_long pathAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "basicShapeResult", &pathAni)) {
        return nullptr;
    }

    auto path = reinterpret_cast<PathPeer*>(pathAni);
    return path;
}

ani_object ANIPathShapePosition(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    PathPeer* pathObj = GetPathShape(env, object);
    if (!pathObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (pathObj->pathShape) {
        pathObj->pathShape->SetPosition(position);
    }
    return object;
}

ani_object ANIPathShapeOffset(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    PathPeer* pathObj = GetPathShape(env, object);
    if (!pathObj) {
        return object;
    }
    CalcDimension dx;
    ParseOption(env, aniOption, dx, "x", "arkui.component.units.Position");
    CalcDimension dy;
    ParseOption(env, aniOption, dy, "y", "arkui.component.units.Position");
    DimensionOffset position(dx, dy);
    if (pathObj->pathShape) {
        pathObj->pathShape->SetOffset(position);
    }
    return object;
}

ani_object ANIPathShapeColor(ani_env* env, ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    OHOS::Ace::Color resourceColor;
    if (!ParseAniColor(env, aniOption, resourceColor)) {
        return object;
    }
    PathPeer* pathObj = GetPathShape(env, object);
    if (!pathObj) {
        return object;
    }
    if (pathObj->pathShape) {
        pathObj->pathShape->SetColor(resourceColor);
    }
    return object;
}

ani_object ANIPathShapeCommands(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return object;
    }
    PathPeer* pathObj = GetPathShape(env, object);
    if (!pathObj) {
        return object;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(aniOption, &isUndefined)) {
        return object;
    }
    if (!GetIsStringObject(env, aniOption)) {
        return object;
    }
    auto commands = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(aniOption));

    if (pathObj->pathShape) {
        pathObj->pathShape->SetValue(commands);
    }
    return object;
}

ani_object PathShape::ANIPathShapeFromPtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    return ANIShapeFromPtr<PathPeer>(env, ptr, ANI_SHAPE_NAME, "basicShapeResult");
}

ani_status PathShape::BindPathShape(ani_env* env)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_SHAPE_NAME, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(ANICreatePathShape) },
        ani_native_function {
            "<ctor>", "C{@ohos.arkui.shape.PathShapeOptions}:", reinterpret_cast<void*>(ANICreatePathShapeWithParam) },
        ani_native_function { "commands", nullptr, reinterpret_cast<void*>(ANIPathShapeCommands) },
        ani_native_function { "position", nullptr, reinterpret_cast<void*>(ANIPathShapePosition) },
        ani_native_function { "offset", nullptr, reinterpret_cast<void*>(ANIPathShapeOffset) },
        ani_native_function { "fill", nullptr, reinterpret_cast<void*>(ANIPathShapeColor) },
    };
    ani_status tmp = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != tmp) {
        return ANI_ERROR;
    };
    return ANI_OK;
}
} // namespace OHOS::Ace