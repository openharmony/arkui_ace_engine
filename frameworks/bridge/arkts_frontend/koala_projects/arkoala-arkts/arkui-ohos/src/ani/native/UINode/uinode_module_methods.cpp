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

#include "base/utils/utils.h"
#include "load.h"
#include "uinode_module_methods.h"

namespace OHOS::Ace::Ani {

void OnUpdateDone(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto uiNodeOnUpdateDoneAniModifier = modifier->getUINodeOnUpdateDoneAniModifier();
    CHECK_NULL_VOID(uiNodeOnUpdateDoneAniModifier);
    return uiNodeOnUpdateDoneAniModifier->onUpdateDone(env, aniClass, node);
}

void SetUINodeIsStatic(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto uiNodeOnUpdateDoneAniModifier = modifier->getUINodeOnUpdateDoneAniModifier();
    CHECK_NULL_VOID(uiNodeOnUpdateDoneAniModifier);
    return uiNodeOnUpdateDoneAniModifier->setUINodeIsStatic(env, aniClass, node);
}

} // namespace OHOS::Ace::Ani