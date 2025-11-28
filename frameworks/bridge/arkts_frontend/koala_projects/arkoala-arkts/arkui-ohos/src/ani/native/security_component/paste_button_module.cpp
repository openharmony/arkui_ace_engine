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

#include "paste_button_module.h"

#include "lattice_ani/ani_lattice.h"
#include "load.h"
#include "log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
void PasteButton_SetOnClickCallback(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object onClickCallback)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    if (AniUtils::IsUndefined(env, onClickCallback)) {
        return;
    }
    modifier->getPasteButtonAniModifier()->setPasteButtonOnClickCallback(env, arkNode, onClickCallback);
}
} // namespace OHOS::Ace::Ani