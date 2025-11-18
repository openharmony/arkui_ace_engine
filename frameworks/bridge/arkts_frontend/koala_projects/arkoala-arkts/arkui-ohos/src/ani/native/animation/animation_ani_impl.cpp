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

#include <functional>
#include <mutex>

#include "ani_global_reference.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "load.h"
#include "utils/ani_utils.h"
#include "utils/string_holder.h"

#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::Ani {

namespace {
enum class AnimatableExtendPropertyType : int32_t {
    UNKNOWN = -1,
    NUMBER = 0,
    ARITHMETIC,
};

struct AniAnimatableExtendStruct {
    ani_env* env;
    ani_fn_object callback;
    ani_object property;
};

std::once_flag g_arithmeticOnceFlag;

AnimatableExtendPropertyType GetPropertyType(ani_env* env, ani_object property)
{
    ani_class doubleClass {};
    ani_boolean isDouble = ANI_FALSE;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("std.core.Double", &doubleClass)) != ANI_OK) {
        HILOGW("cannot find double class, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if ((status = env->Object_InstanceOf(property, doubleClass, &isDouble)) != ANI_OK) {
        HILOGW("Object_InstanceOf double error, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if (isDouble) {
        return AnimatableExtendPropertyType::NUMBER;
    }
    ani_class arithmeticClass {};
    ani_boolean isArithmetic = ANI_FALSE;
    if ((status = env->FindClass("arkui.component.common.AnimatableArithmetic", &arithmeticClass)) != ANI_OK) {
        HILOGW("cannot find AnimatableArithmetic class, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    if ((status = env->Object_InstanceOf(property, arithmeticClass, &isArithmetic)) != ANI_OK) {
        HILOGW("Object_InstanceOf AnimatableArithmetic error, errorCode:%{public}d", status);
        return AnimatableExtendPropertyType::UNKNOWN;
    }
    return isArithmetic ? AnimatableExtendPropertyType::ARITHMETIC : AnimatableExtendPropertyType::UNKNOWN;
}

ani_object ArithmeticAdd(ani_env* env, ani_object obj, ani_object otherObj)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref result;
    ani_status status = env->Object_CallMethodByName_Ref(obj, "plus", nullptr, &result, static_cast<ani_ref>(otherObj));
    if (status != ANI_OK) {
        HILOGW("AnimatableArithmetic call plus func fail, errorCode:%{public}d", status);
        return nullptr;
    }
    return static_cast<ani_object>(result);
}

ani_object ArithmeticMinus(ani_env* env, ani_object obj, ani_object otherObj)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref result;
    ani_status status =
        env->Object_CallMethodByName_Ref(obj, "subtract", nullptr, &result, static_cast<ani_ref>(otherObj));
    if (status != ANI_OK) {
        HILOGW("AnimatableArithmetic call subtract func fail, errorCode:%{public}d", status);
        return nullptr;
    }
    return static_cast<ani_object>(result);
}

ani_object ArithmeticMultiply(ani_env* env, ani_object obj, float scale)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref result;
    ani_float aniScale = scale;
    ani_status status = env->Object_CallMethodByName_Ref(obj, "multiply", nullptr, &result, aniScale);
    if (status != ANI_OK) {
        HILOGW("AnimatableArithmetic call multiply func fail, errorCode:%{public}d", status);
        return nullptr;
    }
    return static_cast<ani_object>(result);
}

bool ArithmeticEqual(ani_env* env, ani_object obj, ani_object otherObj)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean result;
    ani_ref otherRef = static_cast<ani_ref>(otherObj);
    ani_status status = env->Object_CallMethodByName_Boolean(obj, "equals", nullptr, &result, otherRef);
    if (status != ANI_OK) {
        HILOGW("AnimatableArithmetic call equals func fail, errorCode:%{public}d", status);
        return false;
    }
    return static_cast<bool>(result);
}

ani_object CreateAniGlobalObject(ani_env* env, ani_object localObj)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref globalRef;
    env->GlobalReference_Create(static_cast<ani_ref>(localObj), &globalRef);
    return static_cast<ani_object>(globalRef);
}

void DeleteAniGlobalObject(ani_env* env, ani_object globalObj)
{
    CHECK_NULL_VOID(env && globalObj);
    env->GlobalReference_Delete(static_cast<ani_ref>(globalObj));
}

bool ParseRouteType(ani_env* env, ani_ref routeTypeRef, ArkUIAniRouteType& type)
{
    ani_boolean isUndefined;
    ani_status status;
    if ((status = env->Reference_IsUndefined(routeTypeRef, &isUndefined)) != ANI_OK) {
        HILOGW("reference is undefined error, status:%{public}d", status);
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_enum_item typeEnum = static_cast<ani_enum_item>(routeTypeRef);
    ani_int routeTypeValue;
    if ((status = env->EnumItem_GetValue_Int(typeEnum, &routeTypeValue)) == ANI_OK) {
        switch (routeTypeValue) {
            case 0: {
                type = ArkUIAniRouteType::NONE;
                return true;
            }
            case 1: {
                type = ArkUIAniRouteType::PUSH;
                return true;
            }
            case 2: {
                type = ArkUIAniRouteType::POP;
                return true;
            }
            default: {
                HILOGW("RouteType is invalid, type:%{public}d", routeTypeValue);
            }
        }
    }
    return false;
}

bool ParseSlideEffect(ani_env* env, ani_ref slide, ArkUIAniSlideEffect& result)
{
    ani_status status;
    ani_enum_item slideItem = static_cast<ani_enum_item>(slide);
    ani_int slideValue;
    if ((status = env->EnumItem_GetValue_Int(slideItem, &slideValue)) == ANI_OK) {
        if (slideValue >= static_cast<int32_t>(ArkUIAniSlideEffect::NONE) &&
            slideValue <= static_cast<int32_t>(ArkUIAniSlideEffect::END)) {
            result = static_cast<ArkUIAniSlideEffect>(slideValue);
            return true;
        }
        HILOGW("SlideType is invalid, type:%{public}d", slideValue);
    }
    return false;
}

bool ParseCurveObject(ani_env* env, ani_ref curveRef, ArkUIAniUnionCurveStringICurve& result, StringHolder& holder)
{
    ani_boolean isUndefined;
    ani_status status;
    if (env->Reference_IsUndefined(curveRef, &isUndefined) == ANI_OK) {
        if (isUndefined) {
            return false;
        }
    }
    ani_object curveObject = static_cast<ani_object>(curveRef);
    if (AniUtils::IsString(env, curveObject)) {
        auto curveString = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(curveObject));
        result.selector = 1;
        result.value1 = holder.CreateCString(curveString);
        return true;
    }
    // for ICurve
    ani_long iCurve = 0L;
    if ((status = env->Object_GetFieldByName_Long(curveObject, "nativeContext", &iCurve)) == ANI_OK) {
        result.selector = 2;
        result.value2 = reinterpret_cast<void*>(iCurve);
        return true;
    }
    // for Curve enum
    ani_enum curveEnum {};
    if ((status = env->FindEnum("@ohos.curves.curves.Curve", &curveEnum)) != ANI_OK) {
        HILOGW("GetCurve enum class error, status:%{public}d", status);
        return false;
    }
    ani_boolean isCurveEnum = ANI_FALSE;
    if ((status = env->Object_InstanceOf(curveObject, curveEnum, &isCurveEnum)) != ANI_OK) {
        HILOGW("InstanceOfCurve error, status:%{public}d", status);
        return false;
    }
    if (isCurveEnum) {
        ani_enum_item curveEnumItem = static_cast<ani_enum_item>(curveObject);
        ani_int curveValue;
        if (env->EnumItem_GetValue_Int(curveEnumItem, &curveValue) == ANI_OK) {
            result.selector = 0;
            result.value0 = curveValue;
            return true;
        }
    }
    return false;
}

ArkUIAniPageTransitionOption ParseTransitionOption(ani_env* env, ani_object options, StringHolder& holder)
{
    ArkUIAniPageTransitionOption option;
    const int32_t defaultDuration = 1000;
    option.duration = defaultDuration;
    ani_boolean isUndefined;
    ani_status status;
    if ((status = env->Reference_IsUndefined(options, &isUndefined)) != ANI_OK) {
        HILOGW("ParseTransitionOption isUndefined error, status:%{public}d", status);
        return option;
    }
    if (isUndefined) {
        return option;
    }
    ani_ref durationRef;
    if ((status = env->Object_GetPropertyByName_Ref(options, "duration", &durationRef)) == ANI_OK) {
        int32_t duration = defaultDuration;
        if (AniUtils::GetOptionalInt(env, durationRef, duration)) {
            option.duration = static_cast<int32_t>(duration);
            if (option.duration < 0) {
                option.duration = defaultDuration;
            }
        }
    } else {
        HILOGW("GetDuration error, status:%{public}d", status);
    }
    ani_ref delayRef = 0;
    if ((status = env->Object_GetPropertyByName_Ref(options, "delay", &delayRef)) == ANI_OK) {
        int32_t delay = 0.0;
        if (AniUtils::GetOptionalInt(env, delayRef, delay)) {
            option.delay = static_cast<int32_t>(delay);
        }
    } else {
        HILOGW("GetDelay error, status:%{public}d", status);
    }
    ani_ref routeTypeRef = nullptr;
    if ((status = env->Object_GetPropertyByName_Ref(options, "type", &routeTypeRef)) == ANI_OK) {
        ArkUIAniRouteType routeType = ArkUIAniRouteType::NONE;
        if (ParseRouteType(env, routeTypeRef, routeType)) {
            option.routeType = routeType;
        }
    } else {
        HILOGW("GetRouteType error, status:%{public}d", status);
    }
    ani_ref curveRef = nullptr;
    if ((status = env->Object_GetPropertyByName_Ref(options, "curve", &curveRef)) == ANI_OK) {
        ArkUIAniUnionCurveStringICurve curve;
        if (ParseCurveObject(env, curveRef, curve, holder)) {
            option.curve = curve;
        }
    } else {
        HILOGW("GetCurve error, status:%{public}d", status);
    }
    return option;
}

bool GetRouteTypeEnum(ani_env* env, ArkUIAniRouteType type, ani_enum_item& item)
{
    const static std::unordered_map<ArkUIAniRouteType, std::string> mpRouteType = {
        { ArkUIAniRouteType::NONE, "None" },
        { ArkUIAniRouteType::PUSH, "Push" },
        { ArkUIAniRouteType::POP, "Pop" },
    };
    auto iter = mpRouteType.find(type);
    if (iter == mpRouteType.end()) {
        return false;
    }
    ani_enum enumType;
    ani_status status;
    if ((status = env->FindEnum("arkui.component.pageTransition.RouteType", &enumType)) != ANI_OK) {
        HILOGW("find routeType class error, status:%{public}d", status);
        return false;
    }
    if ((status = env->Enum_GetEnumItemByName(enumType, iter->second.c_str(), &item)) != ANI_OK) {
        HILOGW("find routeType %{public}s error, status:%{public}d", iter->second.c_str(), status);
        return false;
    }
    return true;
}

void ParseNumberString(ani_env* env, ani_ref value, ArkUIAniNumberString& result, StringHolder& holder)
{
    ani_object valueObj = static_cast<ani_object>(value);
    result.selector = -1;
    if (AniUtils::IsUndefined(env, valueObj)) {
        return;
    }
    if (AniUtils::IsNumber(env, valueObj)) {
        ani_double doubleValue;
        if (env->Object_CallMethodByName_Double(valueObj, "unboxed", ":d", &doubleValue) == ANI_OK) {
            result.selector = 0;
            result.value0 = doubleValue;
            return;
        }
        HILOGW("%{public}s toDouble failed", __func__);
        return;
    }
    if (AniUtils::IsString(env, valueObj)) {
        result.selector = 1;
        auto str = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(value));
        result.value1 = holder.CreateCString(str);
        return;
    }
}

void HandleAnimatablePropertyFloat(
    ArkUINodeHandle frameNode, const std::string& name, ani_env* env, ani_object property, ani_fn_object callback)
{
    ani_double valueAniDouble = 0.0;
    if (env->Object_CallMethodByName_Double(property, "unboxed", ":d", &valueAniDouble) != ANI_OK) {
        HILOGW("unbox double failed when %{public}s", __func__);
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    if (animationModifier->hasAnimatableProperty(frameNode, name.c_str())) {
        animationModifier->updateAnimatableFloat(frameNode, name.c_str(), static_cast<float>(valueAniDouble));
    } else {
        auto globalCallback = std::make_shared<AniGlobalReference>(env, callback);
        std::function<bool(float)> updateCallback = [env, globalCallback](float value) -> bool {
            ani_object valueObject = AniUtils::CreateDouble(env, value);
            ani_ref valueRef = static_cast<ani_ref>(valueObject);
            ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
            ani_status status = ANI_OK;
            ani_ref result;
            if ((status = env->FunctionalObject_Call(callback, 1, &valueRef, &result)) == ANI_OK) {
                return true;
            }
            HILOGW("call animatable number callback error, status:%{public}d", status);
            return false;
        };
        animationModifier->createAnimatableFloat(
            frameNode, name.c_str(), static_cast<float>(valueAniDouble), &updateCallback);
        ani_ref propertyRef = static_cast<ani_ref>(property);
        ani_ref result;
        env->FunctionalObject_Call(callback, 1, &propertyRef, &result);
    }
}

void HandleAnimatablePropertyArithmetic(
    ArkUINodeHandle frameNode, const std::string& name, ani_env* env, ani_object property, ani_fn_object callback)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    ArkUIAniAnimatableArithmeticFuncs funcs {
        .addFunc = ArithmeticAdd,
        .minusFunc = ArithmeticMinus,
        .multiplyFunc = ArithmeticMultiply,
        .equalFunc = ArithmeticEqual,
        .createFunc = CreateAniGlobalObject,
        .deleteFunc = DeleteAniGlobalObject,
    };
    std::call_once(g_arithmeticOnceFlag,
        [animationModifier, funcs]() { animationModifier->initAnimatableArithmeticClass(&funcs); });
    ArkUIAniAnimatableArithmeticObject aniArithmetic { .env = env, .property = property };
    if (animationModifier->hasAnimatableProperty(frameNode, name.c_str())) {
        animationModifier->updateAnimatableArithmetic(frameNode, name.c_str(), aniArithmetic);
    } else {
        auto globalCallback = std::make_shared<AniGlobalReference>(env, callback);
        std::function<bool(ani_object)> updateCallback = [env, globalCallback](ani_object value) -> bool {
            ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
            ani_ref valueRef = static_cast<ani_ref>(value);
            ani_status status = ANI_OK;
            ani_ref result;
            if ((status = env->FunctionalObject_Call(callback, 1, &valueRef, &result)) == ANI_OK) {
                return true;
            }
            HILOGW("call animatable arithmetic callback error, status:%{public}d", status);
            return false;
        };
        animationModifier->createAnimatableArithmetic(frameNode, name.c_str(), aniArithmetic, &updateCallback);
        ani_ref propertyRef = static_cast<ani_ref>(property);
        ani_ref result;
        env->FunctionalObject_Call(callback, 1, &propertyRef, &result);
    }
}

} // namespace

void SetOrCreateAnimatableProperty(
    ani_env* env, ani_object aniClass, ani_long node, ani_string name, ani_object property, ani_fn_object callback)
{
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(frameNode);
    auto nameStr = AniUtils::ANIStringToStdString(env, name);
    auto propertyType = GetPropertyType(env, property);
    if (propertyType == AnimatableExtendPropertyType::NUMBER) {
        HandleAnimatablePropertyFloat(frameNode, nameStr, env, property, callback);
    } else if (propertyType == AnimatableExtendPropertyType::ARITHMETIC) {
        HandleAnimatablePropertyArithmetic(frameNode, nameStr, env, property, callback);
    } else {
        HILOGW("AnimatableExtend error, input must be number or AnimatableArithmetic");
        return;
    }
}

void CreatePageTransitionEnter(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    StringHolder holder;
    auto pageTransitionOption = ParseTransitionOption(env, options, holder);
    animationModifier->createPageTransitionEnter(&pageTransitionOption);
}

void PageTransitionSetOnEnter(ani_env* env, ani_object aniClass, ani_fn_object onEnter)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    auto globalCallback = std::make_shared<AniGlobalReference>(env, onEnter);
    std::function<void(ArkUIAniRouteType, float)> onEnterEvent = [env, globalCallback](
                                                                     ArkUIAniRouteType type, float value) {
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        ani_enum_item typeEnum;
        bool getEnumResult = GetRouteTypeEnum(env, type, typeEnum);
        if (!getEnumResult) {
            HILOGW("onEnter failed. GetRouteTypeEnum error");
            return;
        }
        ani_object valueRef = AniUtils::CreateDouble(env, value);
        ani_ref valueArr[2] = { static_cast<ani_ref>(typeEnum), static_cast<ani_ref>(valueRef) };
        ani_ref result;
        if ((status = env->FunctionalObject_Call(callback, 2, valueArr, &result)) != ANI_OK) {
            HILOGW("call onEnter function error, status:%{public}d", status);
        }
    };
    animationModifier->pageTransitionSetOnEnter(&onEnterEvent);
}

void CreatePageTransitionExit(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    StringHolder holder;
    auto pageTransitionOption = ParseTransitionOption(env, options, holder);
    animationModifier->createPageTransitionExit(&pageTransitionOption);
}

void PageTransitionSetOnExit(ani_env* env, ani_object aniClass, ani_fn_object onExit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    auto globalCallback = std::make_shared<AniGlobalReference>(env, onExit);
    std::function<void(ArkUIAniRouteType, float)> onExitEvent = [env, globalCallback](
                                                                    ArkUIAniRouteType type, float value) {
        ani_fn_object callback = static_cast<ani_fn_object>(globalCallback->GetValue());
        ani_status status = ANI_OK;
        ani_enum_item typeEnum;
        bool getEnumResult = GetRouteTypeEnum(env, type, typeEnum);
        if (!getEnumResult) {
            HILOGW("onExit failed. GetRouteTypeEnum error");
            return;
        }
        ani_object valueRef = AniUtils::CreateDouble(env, value);
        ani_ref valueArr[2] = { static_cast<ani_ref>(typeEnum), static_cast<ani_ref>(valueRef) };
        ani_ref result;
        if ((status = env->FunctionalObject_Call(callback, 2, valueArr, &result)) != ANI_OK) {
            HILOGW("call onExit function error, status:%{public}d", status);
        }
    };
    animationModifier->pageTransitionSetOnExit(&onExitEvent);
}

void PageTransitionSetSlide(ani_env* env, ani_object aniClass, ani_object slide)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    ArkUIAniSlideEffect slideEffect;
    if (ParseSlideEffect(env, slide, slideEffect)) {
        animationModifier->pageTransitionSetSlide(slideEffect);
    }
}

void PageTransitionSetTranslate(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    ani_ref xRef;
    ani_ref yRef;
    ani_ref zRef;
    StringHolder holder;
    ArkUIAniTranslateOptions translateOptions;
    if (env->Object_GetPropertyByName_Ref(options, "x", &xRef) == ANI_OK) {
        ParseNumberString(env, xRef, translateOptions.x, holder);
    }
    if (env->Object_GetPropertyByName_Ref(options, "y", &yRef) == ANI_OK) {
        ParseNumberString(env, yRef, translateOptions.y, holder);
    }
    if (env->Object_GetPropertyByName_Ref(options, "z", &zRef) == ANI_OK) {
        ParseNumberString(env, zRef, translateOptions.z, holder);
    }
    animationModifier->pageTransitionSetTranslate(&translateOptions);
}

void PageTransitionSetScale(ani_env* env, ani_object aniClass, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    ArkUIAniScaleOptions scaleOptions {
        .x = 1.0,
        .y = 1.0,
        .z = 1.0,
    };
    double tmp = 0.0;
    ani_ref scaleXRef;
    ani_ref scaleYRef;
    ani_ref scaleZRef;
    ani_ref centerXRef;
    ani_ref centerYRef;
    StringHolder holder;
    if (env->Object_GetPropertyByName_Ref(options, "x", &scaleXRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleXRef, tmp)) {
            scaleOptions.x = tmp;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "y", &scaleYRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleYRef, tmp)) {
            scaleOptions.y = tmp;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "z", &scaleZRef) == ANI_OK) {
        if (AniUtils::GetOptionalDouble(env, scaleZRef, tmp)) {
            scaleOptions.z = tmp;
        }
    }
    if (env->Object_GetPropertyByName_Ref(options, "centerX", &centerXRef) == ANI_OK) {
        ParseNumberString(env, centerXRef, scaleOptions.centerX, holder);
    }
    if (env->Object_GetPropertyByName_Ref(options, "centerY", &centerYRef) == ANI_OK) {
        ParseNumberString(env, centerYRef, scaleOptions.centerY, holder);
    }
    animationModifier->pageTransitionSetScale(&scaleOptions);
}

void PageTransitionSetOpacity(ani_env* env, ani_object aniClass, ani_double opacity)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto animationModifier = modifier->getAnimationAniModifier();
    CHECK_NULL_VOID(animationModifier);
    animationModifier->pageTransitionSetOpacity(static_cast<float>(opacity));
}

} // namespace OHOS::Ace::Ani
