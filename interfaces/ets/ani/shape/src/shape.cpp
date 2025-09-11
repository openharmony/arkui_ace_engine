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
} // namespace
} // namespace OHOS::Ace

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
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