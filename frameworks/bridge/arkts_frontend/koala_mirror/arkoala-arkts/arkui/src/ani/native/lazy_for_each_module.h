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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LAZY_FOR_EACH_NODE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LAZY_FOR_EACH_NODE_H

#include "load.h"

#include <memory>
 
namespace OHOS::Ace::Ani {
 
ani_long ConstructLazyForEachNode(ani_env* env, [[maybe_unused]] ani_object aniClass,
                             ani_int id, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }

    ani_long node = modifier->getLazyForEachNodeAniModifier()->constructLazyForEachNode(id);
    return node;
}
 
} // namespace OHOS::Ace::Ani
#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LAZY_FOR_EACH_NODE_H
