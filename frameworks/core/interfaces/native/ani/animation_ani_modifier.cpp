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
#include "animation_ani_modifier.h"

#include "ace_ani_global_reference.h"
#include "ani_animatable_arithmetic.h"
#include "ani_utils.h"

#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

enum class AnimatableExtendPropertyType : int32_t {
    UNKNOWN = -1,
    NUMBER = 0,
    ARITHMETIC,
};
AnimatableExtendPropertyType GetPropertyType(ani_env* env, ani_object property)
{
    ani_class doubleClass {};
    ani_boolean isDouble = ANI_FALSE;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("std.core.Double", &doubleClass)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "cannot find double class, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if ((status = env->Object_InstanceOf(property, doubleClass, &isDouble)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Object_InstanceOf double error, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if (isDouble) {
        return AnimatableExtendPropertyType::NUMBER;
    }
    ani_class arithmeticClass {};
    ani_boolean isArithmetic = ANI_FALSE;
    if ((status = env->FindClass("Larkui/component/common/AnimatableArithmetic;", &arithmeticClass)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "cannot find AnimatableArithmetic class, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if ((status = env->Object_InstanceOf(property, arithmeticClass, &isArithmetic)) != ANI_OK) {
        TAG_LOGW(
            AceLogTag::ACE_ANIMATION, "Object_InstanceOf AnimatableArithmetic error, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    return isArithmetic ? AnimatableExtendPropertyType::ARITHMETIC : AnimatableExtendPropertyType::UNKNOWN;
}

} // namespace

static bool HasAnimatableProperty(ani_env* env, ArkUINodeHandle node, ani_string name)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto propertyName = AniUtils::ANIStringToStdString(env, name);
    return frameNode->HasAnimatableProperty(propertyName);
}

static void UpdateAnimatableProperty(ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto propertyNameStr = AniUtils::ANIStringToStdString(env, propertyName);
    auto propertyType = GetPropertyType(env, property);
    if (propertyType == AnimatableExtendPropertyType::NUMBER) {
        ani_double valueAniDouble = 0.0;
        if (env->Object_CallMethodByName_Double(property, "unboxed", ":d", &valueAniDouble) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "unbox double failed when UpdateAnimatableProperty");
            return;
        }
        frameNode->UpdateAnimatablePropertyFloat(propertyNameStr, static_cast<float>(valueAniDouble));
    } else if (propertyType == AnimatableExtendPropertyType::ARITHMETIC) {
        auto arithmeticImpl = AceType::MakeRefPtr<AniAnimatableArithmetic>(property, env);
        RefPtr<CustomAnimatableArithmetic> arithmetic =
            AceType::DynamicCast<CustomAnimatableArithmetic>(arithmeticImpl);
        frameNode->UpdateAnimatableArithmeticProperty(propertyNameStr, arithmetic);
    }
}

static std::function<void(const RefPtr<CustomAnimatableArithmetic>&)> GetAnimatableArithmeticCallback(
    ani_env* env, const WeakPtr<FrameNode>& node, const RefPtr<AceAniGlobalReference>& globalCallback)
{
    return [env, globalCallback, id = Container::CurrentIdSafelyWithCheck(), weakNode = node](
               const RefPtr<CustomAnimatableArithmetic>& value) {
        ContainerScope scope(id);
        RefPtr<AniAnimatableArithmetic> impl = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        CHECK_NULL_VOID(impl);
        auto valueAni = impl->GetObject();
        ani_ref valueAniRef = static_cast<ani_ref>(valueAni);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ani_ref result;
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        PipelineContext::SetCallBackNode(weakNode);
        if ((status = env->FunctionalObject_Call(callback, 1, &valueAniRef, &result)) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "call animatable arithmetic callback error, status:%{public}d", status);
            return;
        }
        frameNode->MarkDirtyNode();
    };
}

static std::function<void(float)> GetAnimatableNumberCallback(
    ani_env* env, const WeakPtr<FrameNode>& node, const RefPtr<AceAniGlobalReference>& globalCallback)
{
    return [env, globalCallback, id = Container::CurrentIdSafelyWithCheck(), weakNode = node](float value) {
        ContainerScope scope(id);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ani_ref result;
        ani_object valueObject = AniUtils::CreateDouble(env, value);
        ani_ref valueRef = static_cast<ani_ref>(valueObject);
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        PipelineContext::SetCallBackNode(weakNode);
        if ((status = env->FunctionalObject_Call(callback, 1, &valueRef, &result)) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "call animatable number callback error, status:%{public}d", status);
            return;
        }
        frameNode->MarkDirtyNode();
    };
}

static void CreateAnimatableProperty(
    ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property, ani_fn_object callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto propertyNameStr = AniUtils::ANIStringToStdString(env, propertyName);
    auto globalCallback = AceType::MakeRefPtr<AceAniGlobalReference>(env, callback);
    auto propertyType = GetPropertyType(env, property);
    if (propertyType == AnimatableExtendPropertyType::NUMBER) {
        ani_double valueAniDouble = 0.0;
        if (env->Object_CallMethodByName_Double(property, "unboxed", ":d", &valueAniDouble) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "unbox double failed when CreateAnimatableProperty");
            return;
        }
        auto updateCallback { GetAnimatableNumberCallback(env, AceType::WeakClaim(frameNode), globalCallback) };
        frameNode->CreateAnimatablePropertyFloat(propertyNameStr, static_cast<float>(valueAniDouble), updateCallback);
    } else if (propertyType == AnimatableExtendPropertyType::ARITHMETIC) {
        auto arithmeticImpl = AceType::MakeRefPtr<AniAnimatableArithmetic>(property, env);
        RefPtr<CustomAnimatableArithmetic> arithmetic =
            AceType::DynamicCast<CustomAnimatableArithmetic>(arithmeticImpl);
        auto updateCallback { GetAnimatableArithmeticCallback(env, AceType::WeakClaim(frameNode), globalCallback) };
        frameNode->CreateAnimatableArithmeticProperty(propertyNameStr, arithmetic, updateCallback);
    }
}

const ArkUIAniAnimationModifier* GetAnimationAniModifier()
{
    static const ArkUIAniAnimationModifier impl = {
        .hasAnimatableProperty = OHOS::Ace::NG::HasAnimatableProperty,
        .updateAnimatableProperty = OHOS::Ace::NG::UpdateAnimatableProperty,
        .createAnimatableProperty = OHOS::Ace::NG::CreateAnimatableProperty,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
