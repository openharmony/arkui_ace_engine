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

#include "ani_animatable_arithmetic.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

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
RefPtr<Curve> ParseCurveObject(const ArkUIAniUnionCurveStringICurve& object)
{
    switch (object.selector) {
        case 0: {
            auto curve = Framework::CreateCurve(object.value0, false);
            // if curve is invalid, may return null.
            return curve;
        }
        case 1: {
            std::string curveString(object.value1);
            auto curve = Framework::CreateCurve(curveString, false);
            // if curve is invalid, may return null.
            return curve;
        }
        case 2: {
            auto curveObjPtr = reinterpret_cast<CurvesObj*>(object.value2);
            return curveObjPtr ? curveObjPtr->curve : nullptr;
        }
        default: {
            return nullptr;
        }
    }
}

PageTransitionOption ParseTransitionOption(const ArkUIAniPageTransitionOption& options)
{
    PageTransitionOption result;
    result.routeType = static_cast<RouteType>(options.routeType);
    result.duration = options.duration;
    result.delay = options.delay;
    RefPtr<Curve> curve = ParseCurveObject(options.curve);
    if (curve) {
        result.curve = curve;
    } else {
        result.curve = Curves::LINEAR;
    }
    return result;
}

bool ParseDimensionVp(const ArkUIAniNumberString& value, CalcDimension& result)
{
    if (value.selector == 0) {
        result = CalcDimension(value.value0, DimensionUnit::VP);
        return true;
    }
    if (value.selector == 1) {
        std::string stringValue(value.value1);
        // notice: not consider the string is invalid string, to keep same with ArkTS1.1
        result = StringUtils::StringToCalcDimension(stringValue, false, DimensionUnit::VP);
        return true;
    }
    return false;
}

using FloatUpdateFunction = std::function<bool(float)>;
using ArithmeticUpdateFunction = std::function<bool(ani_object)>;
using AniRouteUpdateFunction = std::function<void(ArkUIAniRouteType, float)>;

} // namespace

static bool HasAnimatableProperty(ArkUINodeHandle node, const char* name)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    std::string propertyName(name);
    return frameNode->HasAnimatableProperty(propertyName);
}

static void UpdateAnimatableFloat(ArkUINodeHandle node, const char* propertyName, float property)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string propertyNameStr(propertyName);
    frameNode->UpdateAnimatablePropertyFloat(propertyNameStr, property);
}

static void CreateAnimatableFloat(ArkUINodeHandle node, const char* propertyName, float property, void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    std::string propertyNameStr(propertyName);
    auto updateCallback = [callbackFunc = *(reinterpret_cast<FloatUpdateFunction*>(callback)),
                              id = Container::CurrentIdSafelyWithCheck(),
                              weakNode = AceType::WeakClaim(frameNode)](float value) {
        ContainerScope scope(id);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        PipelineContext::SetCallBackNode(weakNode);
        if (callbackFunc && callbackFunc(value)) {
            frameNode->MarkDirtyNode();
        }
    };
    frameNode->CreateAnimatablePropertyFloat(propertyNameStr, property, updateCallback);
}

static void UpdateAnimatableArithmetic(
    ArkUINodeHandle node, const char* propertyName, ArkUIAniAnimatableArithmeticObject object)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string propertyNameStr(propertyName);
    auto arithmeticImpl = AceType::MakeRefPtr<AniAnimatableArithmetic>(object.property, object.env);
    RefPtr<CustomAnimatableArithmetic> arithmetic = AceType::DynamicCast<CustomAnimatableArithmetic>(arithmeticImpl);
    frameNode->UpdateAnimatableArithmeticProperty(propertyNameStr, arithmetic);
}

static void CreateAnimatableArithmetic(
    ArkUINodeHandle node, const char* propertyName, ArkUIAniAnimatableArithmeticObject object, void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    std::string propertyNameStr(propertyName);
    auto arithmeticImpl = AceType::MakeRefPtr<AniAnimatableArithmetic>(object.property, object.env);
    RefPtr<CustomAnimatableArithmetic> arithmetic = AceType::DynamicCast<CustomAnimatableArithmetic>(arithmeticImpl);
    std::function<void(const RefPtr<CustomAnimatableArithmetic>&)> updateCallback =
        [callbackFunc = *(reinterpret_cast<ArithmeticUpdateFunction*>(callback)),
            id = Container::CurrentIdSafelyWithCheck(),
            weakNode = AceType::WeakClaim(frameNode)](const RefPtr<CustomAnimatableArithmetic>& value) {
            ContainerScope scope(id);
            RefPtr<AniAnimatableArithmetic> impl = AceType::DynamicCast<AniAnimatableArithmetic>(value);
            CHECK_NULL_VOID(impl);
            auto frameNode = weakNode.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto valueAni = impl->GetObject();
            PipelineContext::SetCallBackNode(weakNode);
            if (callbackFunc && callbackFunc(valueAni)) {
                frameNode->MarkDirtyNode();
            }
        };
    frameNode->CreateAnimatableArithmeticProperty(propertyNameStr, arithmetic, updateCallback);
}

static void InitAnimatableArithmeticClass(const ArkUIAniAnimatableArithmeticFuncs* funcs)
{
    CHECK_NULL_VOID(funcs);
    AniAnimatableArithmetic::InitFuncs(*funcs);
}

static void CreatePageTransitionEnter(const ArkUIAniPageTransitionOption* options)
{
    auto pagePattern = GetCurrentPage();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(options);
    auto pageTransitionOption = ParseTransitionOption(*options);
    auto transition = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::ENTER, pageTransitionOption);
    pagePattern->AddPageTransition(transition);
}

static void PageTransitionSetOnEnter(void* callback)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    CHECK_NULL_VOID(callback);
    std::function<void(RouteType, const float&)> handler =
        [callbackFunc = *(reinterpret_cast<AniRouteUpdateFunction*>(callback)),
            id = Container::CurrentIdSafelyWithCheck()](RouteType type, const float& value) {
            ACE_SCORING_EVENT("PageTransition.onEnter");
            ContainerScope scope(id);
            if (callbackFunc) {
                callbackFunc(static_cast<ArkUIAniRouteType>(type), value);
            }
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "PageTransition.onEnter");
        };
    effect->SetUserCallback(std::move(handler));
}

static void CreatePageTransitionExit(const ArkUIAniPageTransitionOption* options)
{
    auto pagePattern = GetCurrentPage();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(options);
    auto pageTransitionOption = ParseTransitionOption(*options);
    auto transition = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::EXIT, pageTransitionOption);
    pagePattern->AddPageTransition(transition);
}

static void PageTransitionSetOnExit(void* callback)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    CHECK_NULL_VOID(callback);
    std::function<void(RouteType, const float&)> handler =
        [callbackFunc = *(reinterpret_cast<AniRouteUpdateFunction*>(callback)),
            id = Container::CurrentIdSafelyWithCheck()](RouteType type, const float& value) {
            ACE_SCORING_EVENT("PageTransition.onExit");
            ContainerScope scope(id);
            if (callbackFunc) {
                callbackFunc(static_cast<ArkUIAniRouteType>(type), value);
            }
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "PageTransition.onExit");
        };
    effect->SetUserCallback(std::move(handler));
}

static void PageTransitionSetSlide(ArkUIAniSlideEffect slide)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    effect->SetSlideEffect(static_cast<SlideEffect>(slide));
}

static void PageTransitionSetTranslate(const ArkUIAniTranslateOptions* options)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    CHECK_NULL_VOID(options);
    TranslateOptions translateOptions;
    CalcDimension length;
    if (ParseDimensionVp(options->x, length)) {
        translateOptions.x = length;
    }
    if (ParseDimensionVp(options->y, length)) {
        translateOptions.y = length;
    }
    if (ParseDimensionVp(options->z, length)) {
        translateOptions.z = length;
    }
    effect->SetTranslateEffect(translateOptions);
}

static void PageTransitionSetScale(const ArkUIAniScaleOptions* options)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    CHECK_NULL_VOID(options);
    // default centerX, centerY 50% 50%;
    CalcDimension centerX = 0.5_pct;
    CalcDimension centerY = 0.5_pct;
    CalcDimension length;
    if (ParseDimensionVp(options->centerX, length)) {
        centerX = length;
    }
    if (ParseDimensionVp(options->centerY, length)) {
        centerY = length;
    }
    NG::ScaleOptions scaleOptions(static_cast<float>(options->x), static_cast<float>(options->y),
        static_cast<float>(options->z), centerX, centerY);
    effect->SetScaleEffect(scaleOptions);
}

static void PageTransitionSetOpacity(float opacity)
{
    auto effect = GetCurrentEffect();
    CHECK_NULL_VOID(effect);
    float opacityValue = opacity;
    if (LessNotEqual(opacityValue, 0.0)) {
        opacityValue = 1.0f;
    }
    effect->SetOpacityEffect(opacityValue);
}

const ArkUIAniAnimationModifier* GetAnimationAniModifier()
{
    static const ArkUIAniAnimationModifier impl = {
        .hasAnimatableProperty = OHOS::Ace::NG::HasAnimatableProperty,
        .updateAnimatableFloat = OHOS::Ace::NG::UpdateAnimatableFloat,
        .createAnimatableFloat = OHOS::Ace::NG::CreateAnimatableFloat,
        .updateAnimatableArithmetic = OHOS::Ace::NG::UpdateAnimatableArithmetic,
        .createAnimatableArithmetic = OHOS::Ace::NG::CreateAnimatableArithmetic,
        .initAnimatableArithmeticClass = OHOS::Ace::NG::InitAnimatableArithmeticClass,
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
