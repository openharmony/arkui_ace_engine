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
#include "animation_ani_impl.h"

#include "utils/ani_utils.h"
#include "core/interfaces/ani/ani_api.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "load.h"

namespace OHOS::Ace::Ani {

void SetOrCreateAnimatableProperty(
    ani_env* env, ani_object aniClass, ani_long node, ani_string name, ani_object property, ani_fn_object callback)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(frameNode);
    if (animationModifier->hasAnimatableProperty(env, frameNode, name)) {
        animationModifier->updateAnimatableProperty(env, frameNode, name, property);
    } else {
        animationModifier->createAnimatableProperty(env, frameNode, name, property, callback);
        ani_ref propertyRef = static_cast<ani_ref>(property);
        ani_ref result;
        env->FunctionalObject_Call(callback, 1, &propertyRef, &result);
    }
}

void CreatePageTransitionEnter(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->createPageTransitionEnter(env, options);
}

void PageTransitionSetOnEnter(ani_env* env, ani_object aniClass, ani_fn_object onEnter)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetOnEnter(env, onEnter);
}

void CreatePageTransitionExit(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->createPageTransitionExit(env, options);
}

void PageTransitionSetOnExit(ani_env* env, ani_object aniClass, ani_fn_object onExit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetOnExit(env, onExit);
}

void PageTransitionSetSlide(ani_env* env, ani_object aniClass, ani_object slide)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetSlide(env, slide);
}

void PageTransitionSetTranslate(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetTranslate(env, options);
}

void PageTransitionSetScale(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetScale(env, options);
}

void PageTransitionSetOpacity(ani_env* env, ani_object aniClass, ani_double opacity)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetOpacity(env, opacity);
}

} // namespace OHOS::Ace::Ani
