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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_GRAPHICS_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_GRAPHICS_MODULE_H

#include <cstdint>

#include "core/components_ng/base/modifier.h"

typedef class __ani_object* ani_object;
typedef struct __ani_env ani_env;
typedef int64_t ani_long;
typedef class __ani_fn_object *ani_fn_object;

namespace OHOS::Ace::Framework {
class AniGraphicsModule final {
public:
    static void SetDrawCallback(ani_env* env, ani_long ptr, ani_fn_object fnObj);
    static void SetDrawModifier(ani_env* env, ani_long ptr, ani_object fnObj);
    static void Invalidate(ani_env* env, ani_long ptr);

private:
    static ani_object CreateDrawingContext(ani_env* env, const NG::DrawingContext& context);
};
} // namespace OHOS::Ace::Framework
#endif
