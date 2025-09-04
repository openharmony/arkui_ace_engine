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

#include "content_slot_module.h"

#include "load.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Ani {
ani_long ContentSlotConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id)
{
    auto nodeId = reinterpret_cast<ArkUI_Int32>(id);
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    auto slot = modifier->getContentSlotAniModifier()->construct(nodeId);
    CHECK_NULL_RETURN(slot, nativeObj);
    return reinterpret_cast<ani_long>(slot);
}

void SetContentSlotOptions(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node, ani_long value)
{
    auto* slot = reinterpret_cast<ArkUIContentSlot>(node);
    CHECK_NULL_VOID(slot);
    auto* content = reinterpret_cast<ArkUINodeContent>(value);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getContentSlotAniModifier()->setContentSlotOptions(slot, content);
}
} // namespace OHOS::Ace::Ani
