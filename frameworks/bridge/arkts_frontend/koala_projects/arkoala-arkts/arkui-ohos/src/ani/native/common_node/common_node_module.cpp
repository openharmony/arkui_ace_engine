/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "common_node_module.h"
#include "load.h"
#include "utils/ani_utils.h"
#include <memory>

namespace OHOS::Ace::Ani {

ani_long Commonconstruct(ani_env* env, [[maybe_unused]] ani_object aniClass,
                             ani_int id, ani_int flags)
{
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    ani_long customNode = modifier->getCommonNodeAniModifier()->construct(id, flags);
    return customNode;
}
void SetCommonOptions(ani_env* env, [[maybe_unused]] ani_object aniClass,
                             ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getCommonNodeAniModifier()->setCommonOptions(pointer);
}
} // namespace OHOS::Ace::Ani