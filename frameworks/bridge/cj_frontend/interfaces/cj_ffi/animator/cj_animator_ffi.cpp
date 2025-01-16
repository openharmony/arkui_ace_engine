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

#include "cj_animator_ffi.h"

#include "cj_animator.h"

#include "bridge/common/utils/utils.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;

constexpr int32_t ANIMATOR_OK = 0;
constexpr int32_t INIT_ERROR = 100001;

extern "C" {
int64_t FfiAnimatorCreate(CAnimatorOptions option)
{
    auto opt = std::make_shared<AnimatorOption>();
    auto animator = CREATE_ANIMATOR("ohos.animator");
    if (animator == nullptr) {
        return INIT_ERROR;
    }
    if (!animator->AttachSchedulerOnContainer()) {
        return INIT_ERROR;
    }
    opt->duration = std::max(option.duration, 0);
    opt->delay = std::max(option.delay, 0);
    opt->iterations = option.iterations >= -1 ? option.iterations : 1;
    opt->begin = option.begin;
    opt->end = option.end;
    opt->easing = std::string(option.easing);
    opt->fill = std::string(option.fill);
    opt->direction = std::string(option.direction);
    auto nativeAnimatorResult = FFIData::Create<AnimatorResultImpl>(std::move(animator), std::move(opt));
    if (nativeAnimatorResult == nullptr) {
        return INIT_ERROR;
    }
    int64_t id = nativeAnimatorResult->GetID();
    return id;
}

int32_t FfiAnimatorReset(int64_t id, CAnimatorOptions cOption)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    auto option = nativeAnimatorResult->GetAnimatorOption();
    if (!option) {
        return INIT_ERROR;
    }
    option->duration = std::max(cOption.duration, 0);
    option->delay = std::max(cOption.delay, 0);
    option->iterations = cOption.iterations >= -1 ? cOption.iterations : 1;
    option->begin = cOption.begin;
    option->end = cOption.end;
    option->easing = cOption.easing;
    option->fill = cOption.fill;
    option->direction = cOption.direction;
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        return INIT_ERROR;
    }
    animator->ClearInterpolators();
    animator->ResetIsReverse();
    nativeAnimatorResult->ApplyOption();
    std::function<void(double)> onframeRef = nativeAnimatorResult->GetOnframeRef();
    if (onframeRef) {
        auto onFrameCallback = [onframeRef, weakOption = std::weak_ptr<AnimatorOption>(
                                                nativeAnimatorResult->GetAnimatorOption())](double value) {
            auto option = weakOption.lock();
            ACE_SCOPED_TRACE("ohos.animator onframe. duration:%d, curve:%s", option->duration, option->easing.c_str());
            onframeRef(value);
        };
        RefPtr<Animation<double>> animation;
        RefPtr<Motion> motion = ParseOptionToMotion(option);
        if (motion) {
            motion->AddListener(onFrameCallback);
            nativeAnimatorResult->SetMotion(motion);
        } else {
            auto curve = Framework::CreateCurve(option->easing);
            animation = AceType::MakeRefPtr<CurveAnimation<double>>(option->begin, option->end, curve);
            animation->AddListener(onFrameCallback);
            animator->AddInterpolator(animation);
            nativeAnimatorResult->SetMotion(nullptr);
        }
    }
    return ANIMATOR_OK;
}

int32_t FfiAnimatorPlay(int64_t id)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Animator: no animator is created when call play");
        return INIT_ERROR;
    }
    if (!animator->HasScheduler()) {
        auto result = animator->AttachSchedulerOnContainer();
        if (!result) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "Animator: play failed, animator is not bound to specific context, id:%{public}d", animator->GetId());
            return INIT_ERROR;
        }
    }
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "Animator: Play, id:%{public}d", animator->GetId());
    if (nativeAnimatorResult->GetMotion()) {
        animator->PlayMotion(nativeAnimatorResult->GetMotion());
    } else {
        animator->Play();
    }
    animator->PrintVsyncInfoIfNeed();
    return ANIMATOR_OK;
}

int32_t FfiAnimatorFinish(int64_t id)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Animator: no animator is created when call play");
        return INIT_ERROR;
    }
    animator->Finish();
    return ANIMATOR_OK;
}

int32_t FfiAnimatorPause(int64_t id)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Animator: no animator is created when call play");
        return INIT_ERROR;
    }
    animator->Pause();
    return ANIMATOR_OK;
}

int32_t FfiAnimatorCancel(int64_t id)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Animator: no animator is created when call play");
        return INIT_ERROR;
    }
    animator->Cancel();
    return ANIMATOR_OK;
}

int32_t FfiAnimatorReverse(int64_t id)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    if (nativeAnimatorResult->GetMotion()) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "JsAnimator: interpolatingSpringCurve, cannot reverse");
        return INIT_ERROR;
    }
    auto animator = nativeAnimatorResult->GetAnimator();
    if (!animator) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "JsAnimator: no animator is created when call reverse");
        return INIT_ERROR;
    }
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "JsAnimator: JSReverse, id:%{public}d", animator->GetId());
    if (!animator->HasScheduler()) {
        auto result = animator->AttachSchedulerOnContainer();
        if (!result) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "JsAnimator: reverse failed, animator is not bound to specific context");
            return INIT_ERROR;
        }
    }
    animator->Reverse();
    return ANIMATOR_OK;
}

int32_t FfiAnimatorOnframe(int64_t id, int64_t funcId)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    nativeAnimatorResult->SetOnframe(funcId);
    return ANIMATOR_OK;
}

int32_t FfiAnimatorOncancel(int64_t id, int64_t funcId)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    nativeAnimatorResult->SetOncancel(funcId);
    return ANIMATOR_OK;
}

int32_t FfiAnimatorOnfinish(int64_t id, int64_t funcId)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    nativeAnimatorResult->SetOnfinish(funcId);
    return ANIMATOR_OK;
}

int32_t FfiAnimatorOnrepeat(int64_t id, int64_t funcId)
{
    auto nativeAnimatorResult = FFIData::GetData<AnimatorResultImpl>(id);
    if (!nativeAnimatorResult) {
        return INIT_ERROR;
    }
    nativeAnimatorResult->SetOnrepeat(funcId);
    return ANIMATOR_OK;
}
}
