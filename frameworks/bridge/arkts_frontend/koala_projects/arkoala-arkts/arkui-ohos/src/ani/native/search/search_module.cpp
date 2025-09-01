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

#include "search_module.h"

#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/pipeline/pipeline_base.h"
#include "load.h"
#include "log/log.h"

namespace OHOS::Ace::Ani {

void SetSearchIconSymbol(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node,
    ani_object symbolModifierAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }

    ani_class cls;
    static const char *className = "Larkui/SymbolGlyphModifier/SymbolGlyphModifier;";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        HILOGE("SearchIcon findClass failed, className: %{public}s", className);
        return;
    }

    ani_static_method etsFunc = nullptr;
    if (ANI_OK != env->Class_FindStaticMethod(cls, "applySymbolGlyphModifierToNode", nullptr, &etsFunc)) {
        HILOGE("SearchIcon findMethod failed");
        return;
    }

    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply =
        [env, cls, etsFunc, symbolModifierAni](WeakPtr<NG::FrameNode> frameNode) -> void {
            auto node = frameNode.Upgrade();
            env->Class_CallStaticMethod_Void(cls, etsFunc, symbolModifierAni, node.GetRawPtr());
        };

    modifier->getSearchAniModifier()->setSearchIconSymbol(arkNode, symbolApply);
}
} // namespace OHOS::Ace::Ani
