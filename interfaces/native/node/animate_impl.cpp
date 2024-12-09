/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "node/animate_impl.h"

#include "node/node_model.h"

#include "base/error/error_code.h"

namespace OHOS::Ace::AnimateModel {

int32_t AnimateTo(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
    ArkUI_AnimateCompleteCallback* complete)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !context || !option || !update || !update->callback) {
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUIAnimateOption animateOption {};
    animateOption.duration = option->duration;
    animateOption.tempo = option->tempo;
    animateOption.curve = static_cast<ArkUI_Int32>(option->curve);
    animateOption.delay = option->delay;
    animateOption.iterations = option->iterations;
    if (option->iCurve) {
        animateOption.iCurve = option->iCurve->curve;
        animateOption.curveType = option->iCurve->baseCurveType;
    }
    animateOption.playMode = static_cast<ArkUI_Int32>(option->playMode);
    if (option->expectedFrameRateRange) {
        animateOption.expectedFrameRateRange =
            reinterpret_cast<ArkUIExpectedFrameRateRange*>(option->expectedFrameRateRange);
    }

    if (complete && complete->callback) {
        animateOption.onFinishCallback = reinterpret_cast<void*>(complete->callback);
    }

    if (complete && complete->userData) {
        animateOption.user = complete->userData;
    }
    auto finishCallbackType = static_cast<ArkUI_Int32>(ARKUI_FINISH_CALLBACK_REMOVED);
    if (complete && complete->type == ARKUI_FINISH_CALLBACK_LOGICALLY) {
        finishCallbackType = static_cast<ArkUI_Int32>(ARKUI_FINISH_CALLBACK_LOGICALLY);
    }
    animateOption.finishCallbackType = finishCallbackType;

    impl->getAnimation()->animateTo(reinterpret_cast<ArkUIContext*>(context), animateOption,
        reinterpret_cast<void*>(update->callback), update->userData);
    return ERROR_CODE_NO_ERROR;
}

int32_t KeyframeAnimateTo(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !context || !option || option->keyframes.size() == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUIKeyframeAnimateOption animateOption {};
    animateOption.delay = option->delay;
    animateOption.iterations = option->iterations;
    animateOption.onFinish = option->onFinish;
    animateOption.userData = option->userData;
    ArkUIKeyframeState keyframes[option->keyframes.size()];
    for (size_t i = 0; i < option->keyframes.size(); i++) {
        keyframes[i].duration = option->keyframes[i].duration;
        keyframes[i].event = option->keyframes[i].event;
        keyframes[i].userData = option->keyframes[i].userData;

        auto curve = option->keyframes[i].curve;
        if (!curve) {
            continue;
        }
        //不支持当前curve
        if (curve->type == ARKUI_CURVE_TYPE_SPRING_MOTION || curve->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            curve->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING) {
            continue;
        }
        keyframes[i].curve = curve->curve;
        keyframes[i].curveType = curve->type;
    }
    animateOption.keyframes = keyframes;
    animateOption.keyframeSize = static_cast<int32_t>(option->keyframes.size());

    impl->getAnimation()->keyframeAnimateTo(reinterpret_cast<ArkUIContext*>(context), &animateOption);
    return ERROR_CODE_NO_ERROR;
}

ArkUIAnimatorOption* ConvertAnimatorOption(ArkUI_AnimatorOption* option)
{
    ArkUIAnimatorOption* animatorOption = new ArkUIAnimatorOption;
    animatorOption->duration = option->duration;
    animatorOption->delay = option->delay;
    animatorOption->iterations = option->iterations;
    animatorOption->begin = option->begin;
    animatorOption->end = option->end;
    animatorOption->fill = option->fill;
    animatorOption->direction = option->direction;
    if (option->easing) {
        animatorOption->easing = option->easing->curve;
        animatorOption->curveType = option->easing->type;
    } else {
        animatorOption->easing = nullptr;
    }

    if (option->expectedFrameRateRange) {
        animatorOption->isHasExpectedFrameRateRange = 1;
        animatorOption->expectedFrameRateRange = { option->expectedFrameRateRange->min,
            option->expectedFrameRateRange->max, option->expectedFrameRateRange->expected };
    } else {
        animatorOption->isHasExpectedFrameRateRange = 0;
    }

    int32_t keyframeSize = static_cast<int32_t>(option->keyframes.size());
    if (keyframeSize > 0) {
        animatorOption->keyframes = new ArkUIKeyframe[keyframeSize];
        for (int32_t i = 0; i < keyframeSize; ++i) {
            animatorOption->keyframes[i].keyTime = option->keyframes[i].keyTime;
            animatorOption->keyframes[i].keyValue = option->keyframes[i].keyValue;
            if (option->keyframes[i].curve) {
                animatorOption->keyframes[i].curve = option->keyframes[i].curve->curve;
                animatorOption->keyframes[i].curveType = option->keyframes[i].curve->type;
            } else {
                animatorOption->keyframes[i].curve = nullptr;
                animatorOption->keyframes[i].curveType = 0; // 默认或无效的曲线类型
            }
        }
    } else {
        animatorOption->keyframes = nullptr;
    }
    animatorOption->keyframeSize = keyframeSize;

    animatorOption->onFrame = option->onFrame;
    animatorOption->onFinish = option->onFinish;
    animatorOption->onCancel = option->onCancel;
    animatorOption->onRepeat = option->onRepeat;

    animatorOption->frameUserData = option->frameUserData;
    animatorOption->finishUserData = option->finishUserData;
    animatorOption->cancelUserData = option->cancelUserData;
    animatorOption->repeatUserData = option->repeatUserData;
    return animatorOption;
}

ArkUI_AnimatorHandle CreateAnimator(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !context || !option) {
        return nullptr;
    }

    auto animatorOption = ConvertAnimatorOption(option);
    auto animator = impl->getAnimation()->createAnimator(reinterpret_cast<ArkUIContext*>(context), animatorOption);
    ArkUI_Animator* animatorHandle = new ArkUI_Animator { animator, option, animatorOption };
    return animatorHandle;
}

void DisposeAnimator(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!animatorHandle || !animatorHandle->animator) {
        return;
    }
    impl->getAnimation()->disposeAnimator(animatorHandle->animator);
    if (animatorHandle->animatorOption) {
        auto* animatorOption = reinterpret_cast<ArkUIAnimatorOption*>(animatorHandle->animatorOption);
        if (animatorOption->keyframes) {
            delete[] animatorOption->keyframes;
            animatorOption->keyframes = nullptr;
        }
        delete animatorOption;
        animatorHandle->animatorOption = nullptr;
    }
    delete animatorHandle;
}

int32_t AnimatorReset(ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator || !option) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto animatorOption = ConvertAnimatorOption(option);
    impl->getAnimation()->animatorReset(animatorHandle->animator, animatorOption);
    if (animatorHandle->animatorOption) {
        auto* animatorOption = reinterpret_cast<ArkUIAnimatorOption*>(animatorHandle->animatorOption);
        if (animatorOption->keyframes) {
            delete[] animatorOption->keyframes;
            animatorOption->keyframes = nullptr;
        }
        delete animatorOption;
        animatorHandle->animatorOption = nullptr;
    }
    animatorHandle->animatorOption = animatorOption;
    return ERROR_CODE_NO_ERROR;
}

int32_t AnimatorPlay(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator) {
        return ERROR_CODE_PARAM_INVALID;
    }
    impl->getAnimation()->animatorPlay(animatorHandle->animator);
    return ERROR_CODE_NO_ERROR;
}

int32_t AnimatorFinish(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator) {
        return ERROR_CODE_PARAM_INVALID;
    }
    impl->getAnimation()->animatorFinish(animatorHandle->animator);
    return ERROR_CODE_NO_ERROR;
}

int32_t AnimatorPause(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator) {
        return ERROR_CODE_PARAM_INVALID;
    }
    impl->getAnimation()->animatorPause(animatorHandle->animator);
    return ERROR_CODE_NO_ERROR;
}

int32_t AnimatorCancel(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator) {
        return ERROR_CODE_PARAM_INVALID;
    }
    impl->getAnimation()->animatorCancel(animatorHandle->animator);
    return ERROR_CODE_NO_ERROR;
}

int32_t AnimatorReverse(ArkUI_AnimatorHandle animatorHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !animatorHandle || !animatorHandle->animator) {
        return ERROR_CODE_PARAM_INVALID;
    }
    impl->getAnimation()->animatorReverse(animatorHandle->animator);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_CurveHandle InitCurve(ArkUI_AnimationCurve animationCurve)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    auto curve = impl->getAnimation()->initCurve(animationCurve);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_BASE, curve, animationCurve });
    return iCurve;
}

ArkUI_CurveHandle StepsCurve(int32_t count, bool end)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || count < 1) {
        return nullptr;
    }
    auto curve = impl->getAnimation()->stepsCurve(count, end);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_STEPS, curve });
    return iCurve;
}

ArkUI_CurveHandle CubicBezierCurve(float x1, float y1, float x2, float y2)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    x1 = std::clamp(x1, 0.0f, 1.0f);
    x2 = std::clamp(x2, 0.0f, 1.0f);
    auto curve = impl->getAnimation()->cubicBezierCurve(x1, y1, x2, y2);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_CUBIC_BEZIER, curve });
    return iCurve;
}

ArkUI_CurveHandle SpringCurve(float velocity, float mass, float stiffness, float damping)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    if (mass <= 0) {
        mass = 1;
    }
    if (stiffness <= 0) {
        stiffness = 1;
    }
    if (damping <= 0) {
        damping = 1;
    }
    auto curve = impl->getAnimation()->springCurve(velocity, mass, stiffness, damping);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_SPRING, curve });
    return iCurve;
}

ArkUI_CurveHandle SpringMotion(float response, float dampingFraction, float overlapDuration)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    //default
    if (response <= 0) {
        response = 0.55f;
    }
    //default
    if (dampingFraction <= 0) {
        dampingFraction = 0.825f;
    }
    //default
    if (overlapDuration < 0) {
        overlapDuration = 0;
    }
    auto curve = impl->getAnimation()->springMotion(response, dampingFraction, overlapDuration);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_SPRING_MOTION, curve });
    return iCurve;
}

ArkUI_CurveHandle ResponsiveSpringMotion(float response, float dampingFraction, float overlapDuration)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    //default
    if (response <= 0) {
        response = 0.15f;
    }
    //default
    if (dampingFraction < 0) {
        dampingFraction = 0.86f;
    }
    //default
    if (overlapDuration < 0) {
        overlapDuration = 0.25f;
    }
    auto curve = impl->getAnimation()->responsiveSpringMotion(response, dampingFraction, overlapDuration);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION, curve });
    return iCurve;
}

ArkUI_CurveHandle InterpolatingSpring(float velocity, float mass, float stiffness, float damping)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    if (mass <= 0) {
        mass = 1;
    }
    if (stiffness <= 0) {
        stiffness = 1;
    }
    if (damping <= 0) {
        damping = 1;
    }
    auto curve = impl->getAnimation()->interpolatingSpring(velocity, mass, stiffness, damping);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_INTERPOLATING_SPRING, curve });
    return iCurve;
}

ArkUI_CurveHandle CustomCurve(void* userData, float (*interpolate)(float fraction, void* userdata))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    auto curve = impl->getAnimation()->customCurve(interpolate, userData);
    ArkUI_Curve* iCurve = new ArkUI_Curve({ ARKUI_CURVE_TYPE_CUSTOM, curve });
    return iCurve;
}

void DisposeCurve(ArkUI_CurveHandle curveHandle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !curveHandle) {
        return;
    }
    impl->getAnimation()->disposeCurve(curveHandle->curve);
    delete curveHandle;
}
} // namespace OHOS::Ace::AnimateModel