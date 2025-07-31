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

#include "base/log/ace_scoring_log.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {

namespace {

enum class AnimatableExtendPropertyType : int32_t {
    UNKNOWN = -1,
    NUMBER = 0,
    ARITHMETIC,
};

struct CurvesObj {
    OHOS::Ace::RefPtr<OHOS::Ace::Curve> curve;
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
    if ((status = env->FindClass("C{arkui.component.common.AnimatableArithmetic}", &arithmeticClass)) != ANI_OK) {
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
RefPtr<PagePattern> GetCurrentPage()
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    CHECK_NULL_RETURN(pageNode, nullptr);
    return pageNode->GetPattern<PagePattern>();
}
RefPtr<PageTransitionEffect> GetCurrentEffect()
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto pattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTopTransition();
}
// Parse curve, support Curve enum and valid string format.
RefPtr<Curve> ParseCurveObject(ani_env* env, ani_ref curveRef)
{
    ani_boolean isUndefined;
    ani_status status;
    if (env->Reference_IsUndefined(curveRef, &isUndefined) == ANI_OK) {
        if (isUndefined) {
            return nullptr;
        }
    }
    ani_object curveObject = static_cast<ani_object>(curveRef);
    ani_class stringClass {};
    if ((status = env->FindClass("std.core.String", &stringClass)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetString class error, status:%{public}d", status);
        return nullptr;
    }
    ani_boolean isString = ANI_FALSE;
    if ((status = env->Object_InstanceOf(curveObject, stringClass, &isString)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "InstanceOfString error, status:%{public}d", status);
        return nullptr;
    }
    if (isString) {
        auto curveString = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(curveObject));
        auto curve = Framework::CreateCurve(curveString, false);
        // if curve is invalid, may return null.
        return curve;
    }
    // for ICurve
    ani_long iCurve = 0L;
    if ((status = env->Object_GetFieldByName_Long(curveObject, "nativeContext", &iCurve)) == ANI_OK) {
        auto curveObjPtr = reinterpret_cast<CurvesObj*>(iCurve);
        return curveObjPtr ? curveObjPtr->curve : nullptr;
    }
    // for Curve enum
    ani_enum curveEnum {};
    if ((status = env->FindEnum("@ohos.curves.curves.Curve", &curveEnum)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetCurve enum class error, status:%{public}d", status);
        return nullptr;
    }
    ani_boolean isCurveEnum = ANI_FALSE;
    if ((status = env->Object_InstanceOf(curveObject, curveEnum, &isCurveEnum)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "InstanceOfCurve error, status:%{public}d", status);
        return nullptr;
    }
    if (isCurveEnum) {
        ani_enum_item curveEnumItem = static_cast<ani_enum_item>(curveObject);
        ani_int curveValue;
        if (env->EnumItem_GetValue_Int(curveEnumItem, &curveValue) == ANI_OK) {
            auto curve = Framework::CreateCurve(static_cast<int32_t>(curveValue), false);
            return curve;
        }
    }
    return nullptr;
}
bool ParseRouteType(ani_env* env, ani_ref routeTypeRef, RouteType& type)
{
    ani_boolean isUndefined;
    ani_status status;
    if ((status = env->Reference_IsUndefined(routeTypeRef, &isUndefined)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "reference is undefined error, status:%{public}d", status);
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_enum_item typeEnum = static_cast<ani_enum_item>(routeTypeRef);
    ani_int routeTypeValue;
    if ((status = env->EnumItem_GetValue_Int(typeEnum, &routeTypeValue)) == ANI_OK) {
        if (routeTypeValue >= static_cast<int32_t>(RouteType::NONE) &&
            routeTypeValue <= static_cast<int32_t>(RouteType::POP)) {
            type = static_cast<RouteType>(routeTypeValue);
            return true;
        }
    }
    return false;
}
PageTransitionOption ParseTransitionOption(ani_env* env, ani_object options)
{
    PageTransitionOption option;
    const int32_t defaultDuration = 1000;
    option.duration = defaultDuration;
    option.curve = Curves::LINEAR;
    ani_boolean isUndefined;
    ani_status status;
    if ((status = env->Reference_IsUndefined(options, &isUndefined)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "ParseTransitionOption isUndefined error, status:%{public}d", status);
        return option;
    }
    if (isUndefined) {
        return option;
    }
    ani_ref durationRef;
    if ((status = env->Object_GetPropertyByName_Ref(options, "duration", &durationRef)) == ANI_OK) {
        double duration = defaultDuration;
        if (AniUtils::GetOptionalDouble(env, durationRef, duration)) {
            option.duration = static_cast<int32_t>(duration);
            if (option.duration < 0) {
                option.duration = defaultDuration;
            }
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetDuration error, status:%{public}d", status);
    }
    ani_ref delayRef = 0;
    if ((status = env->Object_GetPropertyByName_Ref(options, "delay", &delayRef)) == ANI_OK) {
        double delay = 0.0;
        if (AniUtils::GetOptionalDouble(env, delayRef, delay)) {
            option.delay = static_cast<int32_t>(delay);
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetDelay error, status:%{public}d", status);
    }
    ani_ref routeTypeRef = nullptr;
    if ((status = env->Object_GetPropertyByName_Ref(options, "type", &routeTypeRef)) == ANI_OK) {
        RouteType routeType;
        if (ParseRouteType(env, routeTypeRef, routeType)) {
            option.routeType = routeType;
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetRouteType error, status:%{public}d", status);
    }
    ani_ref curveRef = nullptr;
    if ((status = env->Object_GetPropertyByName_Ref(options, "curve", &curveRef)) == ANI_OK) {
        RefPtr<Curve> curve = ParseCurveObject(env, curveRef);
        if (curve) {
            option.curve = curve;
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "GetCurve error, status:%{public}d", status);
    }
    return option;
}
bool GetRouteTypeEnum(ani_env* env, RouteType type, ani_enum_item& item)
{
    const static std::unordered_map<RouteType, std::string> mpRouteType = {
        { RouteType::NONE, "None" },
        { RouteType::PUSH, "Push" },
        { RouteType::POP, "Pop" },
    };
    auto iter = mpRouteType.find(type);
    if (iter == mpRouteType.end()) {
        return false;
    }
    ani_enum enumType;
    ani_status status;
    if ((status = env->FindEnum("arkui.component.pageTransition.RouteType", &enumType)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "find routeType class error, status:%{public}d", status);
        return false;
    }
    if ((status = env->Enum_GetEnumItemByName(enumType, iter->second.c_str(), &item)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "find routeType %{public}s error, status:%{public}d", iter->second.c_str(),
            status);
        return false;
    }
    return true;
}
// Parse dimension, support number and string. Not support resource.
bool ParseDimensionVp(ani_env* env, ani_ref value, CalcDimension& result)
{
    ani_status status;
    ani_boolean isUndefined;
    if (env->Reference_IsUndefined(value, &isUndefined) == ANI_OK) {
        if (isUndefined) {
            return false;
        }
    }
    ani_object valueObj = static_cast<ani_object>(value);
    ani_class doubleClass {};
    ani_boolean isDouble;
    if (env->FindClass("std.core.Double", &doubleClass) != ANI_OK) {
        return false;
    }
    if (env->Object_InstanceOf(valueObj, doubleClass, &isDouble) != ANI_OK) {
        return false;
    }
    if (isDouble) {
        ani_double doubleValue;
        if (env->Object_CallMethodByName_Double(valueObj, "unboxed", ":d", &doubleValue) == ANI_OK) {
            result = CalcDimension(doubleValue, DimensionUnit::VP);
            return true;
        }
        return false;
    }
    ani_class stringClass {};
    ani_boolean isString;
    if (env->FindClass("std.core.String", &stringClass) != ANI_OK) {
        return false;
    }
    if (env->Object_InstanceOf(valueObj, stringClass, &isString) != ANI_OK) {
        return false;
    }
    if (isString) {
        auto stdStr = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(valueObj));
        result = StringUtils::StringToCalcDimension(stdStr, false, DimensionUnit::VP);
        return true;
    }
    return false;
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

static void CreatePageTransitionEnter(ani_env* env, ani_object options)
{
    auto pagePattern = GetCurrentPage();
    CHECK_NULL_VOID(pagePattern);
    auto pageTransitionOption = ParseTransitionOption(env, options);
    auto transition = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::ENTER, pageTransitionOption);
    pagePattern->AddPageTransition(transition);
}

static void PageTransitionSetOnEnter(ani_env* env, ani_fn_object callback)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    auto globalCallback = AceType::MakeRefPtr<AceAniGlobalReference>(env, callback);
    auto handler = [env, globalCallback, id = Container::CurrentIdSafelyWithCheck()](
                       RouteType type, const float& value) {
        ACE_SCORING_EVENT("PageTransition.onEnter");
        ContainerScope scope(id);
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        ani_enum_item typeEnum;
        bool getEnumResult = GetRouteTypeEnum(env, type, typeEnum);
        if (!getEnumResult) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "onEnter failed. GetRouteTypeEnum error");
            return;
        }
        ani_object valueRef = AniUtils::CreateDouble(env, value);
        ani_ref valueArr[2] = { static_cast<ani_ref>(typeEnum), static_cast<ani_ref>(valueRef) };
        ani_ref result;
        if ((status = env->FunctionalObject_Call(callback, 2, valueArr, &result)) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "call onEnter function error, status:%{public}d", status);
            return;
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "PageTransition.onEnter");
    };
    effect->SetUserCallback(std::move(handler));
}

static void CreatePageTransitionExit(ani_env* env, ani_object options)
{
    auto pagePattern = GetCurrentPage();
    CHECK_NULL_VOID(pagePattern);
    auto pageTransitionOption = ParseTransitionOption(env, options);
    auto transition = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::EXIT, pageTransitionOption);
    pagePattern->AddPageTransition(transition);
}

static void PageTransitionSetOnExit(ani_env* env, ani_fn_object callback)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    auto globalCallback = AceType::MakeRefPtr<AceAniGlobalReference>(env, callback);
    auto handler = [env, globalCallback, id = Container::CurrentIdSafelyWithCheck()](
                       RouteType type, const float& value) {
        ACE_SCORING_EVENT("PageTransition.onExit");
        ContainerScope scope(id);
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        ani_enum_item typeEnum;
        bool getEnumResult = GetRouteTypeEnum(env, type, typeEnum);
        if (!getEnumResult) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "onExit failed. GetRouteTypeEnum error");
            return;
        }
        ani_object valueRef = AniUtils::CreateDouble(env, value);
        ani_ref valueArr[2] = { static_cast<ani_ref>(typeEnum), static_cast<ani_ref>(valueRef) };
        ani_ref result;
        if ((status = env->FunctionalObject_Call(callback, 2, valueArr, &result)) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "call onExit function error, status:%{public}d", status);
            return;
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "PageTransition.onExit");
    };
    effect->SetUserCallback(std::move(handler));
}

static void PageTransitionSetSlide(ani_env* env, ani_object slide)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    ani_status status;
    ani_enum_item slideItem = static_cast<ani_enum_item>(slide);
    ani_int slideValue;
    if ((status = env->EnumItem_GetValue_Int(slideItem, &slideValue)) != ANI_OK) {
        return;
    }
    if (slideValue >= static_cast<int32_t>(SlideEffect::LEFT) && slideValue <= static_cast<int32_t>(SlideEffect::END)) {
        effect->SetSlideEffect(static_cast<SlideEffect>(slideValue));
    }
}

static void PageTransitionSetTranslate(ani_env* env, ani_object options)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    ani_ref xRef;
    ani_ref yRef;
    ani_ref zRef;
    TranslateOptions translateOptions;
    CalcDimension length;
    if (env->Object_GetPropertyByName_Ref(options, "x", &xRef) == ANI_OK) {
        if (ParseDimensionVp(env, xRef, length)) {
            translateOptions.x = length;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "y", &yRef) == ANI_OK) {
        if (ParseDimensionVp(env, yRef, length)) {
            translateOptions.y = length;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "z", &zRef) == ANI_OK) {
        if (ParseDimensionVp(env, zRef, length)) {
            translateOptions.z = length;
        }
    }
    effect->SetTranslateEffect(translateOptions);
}

static void PageTransitionSetScale(ani_env* env, ani_object options)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    double scaleX = 1.0;
    double scaleY = 1.0;
    double scaleZ = 1.0;
    ani_ref scaleXRef;
    ani_ref scaleYRef;
    ani_ref scaleZRef;
    double tmp = 0.0;
    if (env->Object_GetPropertyByName_Ref(options, "x", &scaleXRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleXRef, tmp)) {
            scaleX = tmp;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "y", &scaleYRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleYRef, tmp)) {
            scaleY = tmp;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "z", &scaleZRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleZRef, tmp)) {
            scaleZ = tmp;
        }
    }
    // default centerX, centerY 50% 50%;
    CalcDimension centerX = 0.5_pct;
    CalcDimension centerY = 0.5_pct;
    CalcDimension length;
    ani_ref centerXRef;
    ani_ref centerYRef;
    if (env->Object_GetPropertyByName_Ref(options, "centerX", &centerXRef) == ANI_OK) {
        if (ParseDimensionVp(env, centerXRef, length)) {
            centerX = length;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "centerY", &centerYRef) == ANI_OK) {
        if (ParseDimensionVp(env, centerYRef, length)) {
            centerY = length;
        }
    }
    NG::ScaleOptions scaleOptions(
        static_cast<float>(scaleX), static_cast<float>(scaleY), static_cast<float>(scaleZ), centerX, centerY);
    effect->SetScaleEffect(scaleOptions);
}

static void PageTransitionSetOpacity(ani_env* env, ani_double opacity)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    float opacityValue = static_cast<float>(opacity);
    if (LessNotEqual(opacityValue, 0.0)) {
        opacityValue = 1.0;
    }
    effect->SetOpacityEffect(opacityValue);
}

const ArkUIAniAnimationModifier* GetAnimationAniModifier()
{
    static const ArkUIAniAnimationModifier impl = {
        .hasAnimatableProperty = OHOS::Ace::NG::HasAnimatableProperty,
        .updateAnimatableProperty = OHOS::Ace::NG::UpdateAnimatableProperty,
        .createAnimatableProperty = OHOS::Ace::NG::CreateAnimatableProperty,
        .createPageTransitionEnter = OHOS::Ace::NG::CreatePageTransitionEnter,
        .pageTransitionSetOnEnter = OHOS::Ace::NG::PageTransitionSetOnEnter,
        .createPageTransitionExit = OHOS::Ace::NG::CreatePageTransitionExit,
        .pageTransitionSetOnExit = OHOS::Ace::NG::PageTransitionSetOnExit,
        .pageTransitionSetSlide = OHOS::Ace::NG::PageTransitionSetSlide,
        .pageTransitionSetTranslate = OHOS::Ace::NG::PageTransitionSetTranslate,
        .pageTransitionSetScale = OHOS::Ace::NG::PageTransitionSetScale,
        .pageTransitionSetOpacity = OHOS::Ace::NG::PageTransitionSetOpacity,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
