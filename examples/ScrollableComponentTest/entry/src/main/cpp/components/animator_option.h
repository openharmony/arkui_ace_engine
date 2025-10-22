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

#ifndef CAPIDEMO_ANIMATOR_OPTION_H
#define CAPIDEMO_ANIMATOR_OPTION_H

#include <arkui/native_animate.h>
#include <arkui/native_interface.h>
#include <functional>
#include <vector>

#include "components/component.h"

namespace ArkUICApiDemo {

struct Keyframe {
    float keyTime;
    float keyValue;
    ArkUI_CurveHandle curve;
};

struct AnimatorOption {
    int32_t duration;
    int32_t delay;
    int32_t iterations;
    ArkUI_AnimationFillMode fill;
    ArkUI_AnimationDirection direction;
    float begin;
    float end;
    ArkUI_ExpectedFrameRateRange* expectedFrameRateRange;
    ArkUI_CurveHandle easing;
};

class Animator {
public:
    explicit Animator(ArkUI_NodeHandle node, int32_t keyframeSize)
        : _option(OH_ArkUI_AnimatorOption_Create(keyframeSize))
    {
        ArkUI_NativeAnimateAPI_1* animateAPI = nullptr;
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_ANIMATE, ArkUI_NativeAnimateAPI_1, animateAPI);
        auto context = OH_ArkUI_GetContextByNode(node);
        _animatorHandle = animateAPI->createAnimator(context, _option);
        RegisterReceiver();
    }
    ~Animator()
    {
        OH_ArkUI_AnimatorOption_Dispose(_option);
        _option = nullptr;
    }

    bool SetOptionParam(const AnimatorOption& param);
    AnimatorOption GetOptionParam();
    bool SetKeyframeParams(const std::vector<Keyframe>& params);
    Keyframe GetKeyframeParam(int32_t index);
    void RegisterOnFrame(const std::function<void(float)>& onFrame);
    void RegisterOnFinish(const std::function<void()>& onFinish);
    void RegisterOnCancel(const std::function<void()>& onCancel);
    void RegisterOnRepeat(const std::function<void()>& onRepeat);

    bool Play();
    bool Finish();
    bool Pause();
    bool Cancel();
    bool Reverse();
    bool Reset();

protected:
    void RegisterReceiver();

private:
    ArkUI_AnimatorOption* _option;
    ArkUI_AnimatorHandle _animatorHandle;
    std::function<void(float)> _onFrame;
    std::function<void()> _onFinish;
    std::function<void()> _onCancel;
    std::function<void()> _onRepeat;
};
} // namespace ArkUICApiDemo

#endif // CAPIDEMO_ANIMATOR_OPTION_H
