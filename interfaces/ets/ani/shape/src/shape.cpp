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

    *result = ANI_VERSION_1;
    return ANI_OK;
}