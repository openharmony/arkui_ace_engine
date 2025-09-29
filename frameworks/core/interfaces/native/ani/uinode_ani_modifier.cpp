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

#include "base/log/log.h"
#include "core/components_ng/base/ui_node.h"
#include "uinode_ani_modifier.h"
    
    
namespace OHOS::Ace::NG {
    
void OnUpdateDone(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node)
{
    // auto* uiNode = reinterpret_cast<UINode*>(node);
    // CHECK_NULL_VOID(uiNode);
    // uiNode->OnChildUpdateDone();
    // return;
}

void SetUINodeIsStatic(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node)
{
    // auto* uiNode = reinterpret_cast<UINode*>(node);
    // CHECK_NULL_VOID(uiNode);
    // uiNode->SetIsStatic(true);
    // return;
}
    
const ArkUIAniUINodeOnUpdateDoneAniModifier* GetUINodeOnUpdateDoneAniModifier()
{
    static const ArkUIAniUINodeOnUpdateDoneAniModifier impl = {
        .onUpdateDone = OHOS::Ace::NG::OnUpdateDone,
        .setUINodeIsStatic = OHOS::Ace::NG::SetUINodeIsStatic,
    };
    return &impl;
}
    
} // namespace OHOS::Ace::NG