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

#include "components/animator_option.h"

namespace ArkUICApiDemo {
bool Animator::SetOptionParam(const AnimatorOption& param)
{
    if (OH_ArkUI_AnimatorOption_SetDuration(_option, param.duration) ||
        OH_ArkUI_AnimatorOption_SetDelay(_option, param.delay) ||
        OH_ArkUI_AnimatorOption_SetIterations(_option, param.iterations) ||
        OH_ArkUI_AnimatorOption_SetFill(_option, param.fill) ||
        OH_ArkUI_AnimatorOption_SetDirection(_option, param.direction) ||
        OH_ArkUI_AnimatorOption_SetBegin(_option, param.begin) || OH_ArkUI_AnimatorOption_SetEnd(_option, param.end) ||
        OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(_option, param.expectedFrameRateRange) ||
        OH_ArkUI_AnimatorOption_SetCurve(_option, param.easing)) {
        return false;
    }
    return true;
}

AnimatorOption Animator::GetOptionParam()
{
    AnimatorOption option;
    option.duration = OH_ArkUI_AnimatorOption_GetDuration(_option);
    option.delay = OH_ArkUI_AnimatorOption_GetDelay(_option);
    option.iterations = OH_ArkUI_AnimatorOption_GetIterations(_option);
    option.fill = OH_ArkUI_AnimatorOption_GetFill(_option);
    option.direction = OH_ArkUI_AnimatorOption_GetDirection(_option);
    option.begin = OH_ArkUI_AnimatorOption_GetBegin(_option);
    option.end = OH_ArkUI_AnimatorOption_GetEnd(_option);
    option.expectedFrameRateRange = OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(_option);
    option.easing = OH_ArkUI_AnimatorOption_GetCurve(_option);
    return option;
}

bool Animator::SetKeyframeParams(const std::vector<Keyframe>& params)
{
    for (size_t i = 0; i < params.size(); i++) {
        if (OH_ArkUI_AnimatorOption_SetKeyframe(_option, params[i].keyTime, params[i].keyValue, i) ||
            OH_ArkUI_AnimatorOption_SetKeyframeCurve(_option, params[i].curve, i)) {
            return false;
        }
    }
    return true;
}

Keyframe Animator::GetKeyframeParam(int32_t index)
{
    Keyframe keyframe;
    keyframe.keyTime = OH_ArkUI_AnimatorOption_GetKeyframeTime(_option, index);
    keyframe.keyValue = OH_ArkUI_AnimatorOption_GetKeyframeValue(_option, index);
    keyframe.curve = OH_ArkUI_AnimatorOption_GetKeyframeCurve(_option, index);
    return keyframe;
}

void Animator::RegisterOnFrame(const std::function<void(float)>& onFrame)
{
    if (onFrame) {
        _onFrame = onFrame;
    }
}

void Animator::RegisterOnFinish(const std::function<void()>& onFinish)
{
    if (onFinish) {
        _onFinish = onFinish;
    }
}

void Animator::RegisterOnCancel(const std::function<void()>& onCancel)
{
    if (onCancel) {
        _onCancel = onCancel;
    }
}

void Animator::RegisterOnRepeat(const std::function<void()>& onRepeat)
{
    if (onRepeat) {
        _onRepeat = onRepeat;
    }
}

bool Animator::Play()
{
    return !OH_ArkUI_Animator_Play(_animatorHandle);
}

bool Animator::Finish()
{
    return !OH_ArkUI_Animator_Finish(_animatorHandle);
}

bool Animator::Pause()
{
    return !OH_ArkUI_Animator_Pause(_animatorHandle);
}

bool Animator::Cancel()
{
    return !OH_ArkUI_Animator_Cancel(_animatorHandle);
}

bool Animator::Reverse()
{
    return !OH_ArkUI_Animator_Reverse(_animatorHandle);
}

bool Animator::Reset()
{
    return !OH_ArkUI_Animator_ResetAnimatorOption(_animatorHandle, _option);
}

void Animator::RegisterReceiver()
{
    OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(_option, this, [](ArkUI_AnimatorOnFrameEvent* event) {
        auto animator = static_cast<Animator*>(OH_ArkUI_AnimatorOnFrameEvent_GetUserData(event));
        auto value = OH_ArkUI_AnimatorOnFrameEvent_GetValue(event);
        animator->_onFrame(value);
    });
    OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(_option, this, [](ArkUI_AnimatorEvent* event) {
        auto animator = static_cast<Animator*>(OH_ArkUI_AnimatorEvent_GetUserData(event));
        animator->_onFinish();
    });
    OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(_option, this, [](ArkUI_AnimatorEvent* event) {
        auto animator = static_cast<Animator*>(OH_ArkUI_AnimatorEvent_GetUserData(event));
        animator->_onCancel();
    });
    OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(_option, this, [](ArkUI_AnimatorEvent* event) {
        auto animator = static_cast<Animator*>(OH_ArkUI_AnimatorEvent_GetUserData(event));
        animator->_onRepeat();
    });
}
} // namespace ArkUICApiDemo
