/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/core/interfaces/native/node/animation_group_util.h"

#include "frameworks/base/log/log_wrapper.h"
#include "interfaces/native/node/animate_impl.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t DEFAULT_ANIMATION_DURATION = 1000;

AnimationDirection ToAnimationDirection(bool autoReverse)
{
    return autoReverse ? AnimationDirection::ALTERNATE : AnimationDirection::NORMAL;
}

RefPtr<Curve> GetCurveFromHandle(ArkUI_CurveHandle curveHandle)
{
    if (!curveHandle || !curveHandle->curve) {
        return nullptr;
    }
    return AceType::Claim(reinterpret_cast<Curve*>(curveHandle->curve));
}

bool IsDurationIndependentCurve(ArkUI_CurveHandle curveHandle)
{
    if (!curveHandle || !curveHandle->curve) {
        return false;
    }
    auto* aceCurve = reinterpret_cast<Curve*>(curveHandle->curve);
    return AceType::InstanceOf<InterpolatingSpring>(aceCurve) ||
           AceType::InstanceOf<ResponsiveSpringMotion>(aceCurve);
}

AnimationOption BuildGroupAnimationOption(const OH_ArkUI_AnimationGroup* group)
{
    AnimationOption option;
    option.SetDuration(group->hasDuration ? group->duration : DEFAULT_ANIMATION_DURATION);
    option.SetDelay(group->delay);
    option.SetTempo(group->tempo);
    option.SetIteration(group->iterations);
    option.SetAnimationDirection(ToAnimationDirection(group->autoReverse));
    if (group->expectedFrameRateRange) {
        auto rateRange = AceType::MakeRefPtr<FrameRateRange>(
            group->expectedFrameRateRange->min, group->expectedFrameRateRange->max,
            group->expectedFrameRateRange->expected);
        option.SetFrameRateRange(rateRange);
    }
    return option;
}

AnimationOption BuildChildAnimationOption(const OH_ArkUI_AnimationGroup* group, int32_t childDuration,
    bool hasChildDuration, int32_t childDelay, float childTempo, int32_t childIterations,
    bool childAutoReverse)
{
    AnimationOption option;
    option.SetDuration(hasChildDuration ? childDuration
        : (group->hasDuration ? group->duration : DEFAULT_ANIMATION_DURATION));
    option.SetDelay(childDelay);
    option.SetTempo(childTempo);
    option.SetIteration(childIterations);
    option.SetAnimationDirection(ToAnimationDirection(childAutoReverse));
    if (group->expectedFrameRateRange) {
        auto rateRange = AceType::MakeRefPtr<FrameRateRange>(
            group->expectedFrameRateRange->min, group->expectedFrameRateRange->max,
            group->expectedFrameRateRange->expected);
        option.SetFrameRateRange(rateRange);
    }
    return option;
}

bool HasInvalidKeyframeCurve(const OH_ArkUI_KeyframeAnimationHandle& handle)
{
    for (const auto& keyframe : handle->keyframes) {
        if (keyframe.curve && IsDurationIndependentCurve(keyframe.curve)) {
            return true;
        }
    }
    return false;
}

bool HasInvalidChildCurve(const ChildAnimation& child)
{
    if (const auto* keyframeAnim = std::get_if<OH_ArkUI_KeyframeAnimationHandle>(&child)) {
        return *keyframeAnim && HasInvalidKeyframeCurve(*keyframeAnim);
    }
    if (const auto* pathAnim = std::get_if<OH_ArkUI_PathAnimationHandle>(&child)) {
        return *pathAnim && IsDurationIndependentCurve((*pathAnim)->curve);
    }
    return false;
}

ArkUI_ErrorCode ValidateChildAnimations(const OH_ArkUI_AnimationGroup* group)
{
    for (const auto& child : group->childAnimations) {
        if (HasInvalidChildCurve(child)) {
            return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
        }
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

void BuildPropertyChild(const OH_ArkUI_AnimationGroup* group, const OH_ArkUI_PropertyAnimationHandle& handle,
    const RefPtr<Curve>& groupCurve, ChildView& outChild)
{
    PropertyChildView view;
    view.option = BuildChildAnimationOption(group, handle->duration, handle->hasDuration, handle->delay,
        handle->tempo, handle->iterations, handle->autoReverse);
    RefPtr<Curve> childCurve = GetCurveFromHandle(handle->curve);
    view.curve = childCurve ? childCurve : groupCurve;
    view.propertyType = handle->propertyType;
    view.fromValue = handle->fromValue;
    view.toValue = handle->toValue;
    outChild = std::move(view);
}

void BuildKeyframeChild(const OH_ArkUI_AnimationGroup* group, const OH_ArkUI_KeyframeAnimationHandle& handle,
    const RefPtr<Curve>& groupCurve, ChildView& outChild)
{
    KeyframeChildView view;
    view.option = BuildChildAnimationOption(group, handle->duration, handle->hasDuration, handle->delay,
        handle->tempo, handle->iterations, handle->autoReverse);
    view.implicitCurve = groupCurve;
    view.propertyType = handle->propertyType;
    int32_t totalDuration = view.option.GetDuration();
    int32_t prevAbsTime = 0;
    float lastKeyTime = 0.0f;
    for (const auto& keyframe : handle->keyframes) {
        KeyframeChildView::Keyframe kfView;
        RefPtr<Curve> kfCurve = GetCurveFromHandle(keyframe.curve);
        kfView.curve = kfCurve ? kfCurve : view.implicitCurve;
        kfView.values = keyframe.values;
        kfView.fraction = keyframe.keyTime;
        lastKeyTime = keyframe.keyTime;
        int32_t absTime = static_cast<int32_t>(keyframe.keyTime * totalDuration);
        kfView.segmentDuration = absTime - prevAbsTime;
        prevAbsTime = absTime;
        view.keyframes.emplace_back(std::move(kfView));
    }
    if (prevAbsTime < totalDuration && !view.keyframes.empty()) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION,
            "BuildKeyframeChild: append filler keyframe, lastKeyTime=%{public}f, "
            "gap=%{public}d ms, total=%{public}d ms",
            lastKeyTime, totalDuration - prevAbsTime, totalDuration);
        KeyframeChildView::Keyframe filler;
        filler.segmentDuration = totalDuration - prevAbsTime;
        filler.curve = view.keyframes.back().curve;
        filler.values = view.keyframes.back().values;
        view.keyframes.emplace_back(std::move(filler));
    }
    outChild = std::move(view);
}

void BuildPathChild(const OH_ArkUI_AnimationGroup* group, const OH_ArkUI_PathAnimationHandle& handle,
    const RefPtr<Curve>& groupCurve, ChildView& outChild)
{
    PathChildView view;
    view.option = BuildChildAnimationOption(group, handle->duration, handle->hasDuration, handle->delay,
        handle->tempo, handle->iterations, handle->autoReverse);
    RefPtr<Curve> childCurve = GetCurveFromHandle(handle->curve);
    view.curve = childCurve ? childCurve : groupCurve;
    view.path = handle->path ? std::string(handle->path) : std::string();
    view.autoRotation = handle->autoRotation;
    outChild = std::move(view);
}

} // namespace

ArkUI_ErrorCode BuildAnimationGroupView(ArkUIAnimationGroupHandle group, AnimationGroupView& out)
{
    if (!group) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    auto validateResult = ValidateChildAnimations(group);
    if (validateResult != ARKUI_ERROR_CODE_NO_ERROR) {
        return validateResult;
    }

    out.option = BuildGroupAnimationOption(group);
    out.curve = GetCurveFromHandle(group->curve);

    if (group->onFinish) {
        auto onFinish = group->onFinish;
        auto userData = group->userData;
        out.onFinish = [onFinish, userData]() { onFinish(userData); };
    } else {
        out.onFinish = nullptr;
    }

    out.children.clear();
    out.children.reserve(group->childAnimations.size());
    for (const auto& child : group->childAnimations) {
        ChildView childView;
        if (const auto* propAnim = std::get_if<OH_ArkUI_PropertyAnimationHandle>(&child)) {
            if (*propAnim) {
                BuildPropertyChild(group, *propAnim, out.curve, childView);
                out.children.emplace_back(std::move(childView));
            }
        } else if (const auto* keyframeAnim = std::get_if<OH_ArkUI_KeyframeAnimationHandle>(&child)) {
            if (*keyframeAnim) {
                BuildKeyframeChild(group, *keyframeAnim, out.curve, childView);
                out.children.emplace_back(std::move(childView));
            }
        } else if (const auto* pathAnim = std::get_if<OH_ArkUI_PathAnimationHandle>(&child)) {
            if (*pathAnim) {
                BuildPathChild(group, *pathAnim, out.curve, childView);
                out.children.emplace_back(std::move(childView));
            }
        }
    }

    return ARKUI_ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::NG
