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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LAZY_FOR_EACH_NODE_ANI_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LAZY_FOR_EACH_NODE_ANI_MODIFIER_H

#include "core/interfaces/ani/ani_api.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {

ani_long ConstructLazyForEachNode(ani_int id, ani_boolean isRepeat)
{
    auto node = AceType::MakeRefPtr<ArkoalaLazyNode>(id, isRepeat);
    CHECK_NULL_RETURN(node, 0);
    node->RegisterArkoalaLazyNode();
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

ani_boolean IsChildInAnimation(ani_long lazyNodePtr, ani_int rid)
{
    auto* uiNode = reinterpret_cast<UINode*>(lazyNodePtr);
    CHECK_NULL_RETURN(uiNode, ANI_FALSE);
    auto lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_RETURN(lazyNode, ANI_FALSE);
    return lazyNode->IsChildInAnimation(rid) ? ANI_TRUE : ANI_FALSE;
}

ani_boolean IsChildOnMainTree(ani_long lazyNodePtr, ani_int rid)
{
    auto* uiNode = reinterpret_cast<UINode*>(lazyNodePtr);
    CHECK_NULL_RETURN(uiNode, ANI_FALSE);
    auto lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_RETURN(lazyNode, ANI_FALSE);
    return lazyNode->IsChildOnMainTree(rid) ? ANI_TRUE : ANI_FALSE;
}

ani_boolean IsAllowAnimation(ani_long lazyNodePtr)
{
    auto* uiNode = reinterpret_cast<UINode*>(lazyNodePtr);
    CHECK_NULL_RETURN(uiNode, ANI_FALSE);
    auto lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_RETURN(lazyNode, ANI_FALSE);
    return lazyNode->IsAllowAnimation() ? ANI_TRUE : ANI_FALSE;
}

ani_boolean IsImplicitAnimationOpen(ani_long lazyNodePtr)
{
    return AnimationUtils::IsImplicitAnimationOpen() ? ANI_TRUE : ANI_FALSE;
}

const ArkUIAniLazyForEachNodeModifier* GetLazyForEachNodeAniModifier()
{
    static const ArkUIAniLazyForEachNodeModifier impl = {
        .constructLazyForEachNode = ConstructLazyForEachNode,
        .isChildInAnimation = IsChildInAnimation,
        .isChildOnMainTree = IsChildOnMainTree,
        .isAllowAnimation = IsAllowAnimation,
        .isImplicitAnimationOpen = IsImplicitAnimationOpen
    };
    return &impl;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LAZY_FOR_EACH_NODE_ANI_MODIFIER_H
