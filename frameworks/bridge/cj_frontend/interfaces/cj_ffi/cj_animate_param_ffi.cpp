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

#include "cj_animate_param_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<AnimationDirection> ANIMATION_DIRECTION = {
    AnimationDirection::NORMAL, AnimationDirection::REVERSE,
    AnimationDirection::ALTERNATE, AnimationDirection::ALTERNATE_REVERSE
};
const std::vector<FinishCallbackType> FINISH_CALLBACK_TYPE = {
    FinishCallbackType::REMOVED, FinishCallbackType::LOGICALLY
};
}

namespace OHOS::Ace::Framework {
void ParseCjAnimation(NativeAnimateParam animationValue, AnimationOption& result)
{
    if (animationValue.duration.hasValue) {
        result.SetDuration(animationValue.duration.value);
    }

    if (animationValue.delay.hasValue) {
        result.SetDelay(animationValue.delay.value);
    }

    if (animationValue.iterations.hasValue) {
        result.SetIteration(animationValue.iterations.value);
    }

    if (animationValue.tempo.hasValue) {
        float tempo = animationValue.tempo.value;
        if (NonPositive(tempo)) {
            tempo = 1.0f;
        }
        result.SetTempo(tempo);
    }

    if (animationValue.playMode.hasValue) {
        result.SetAnimationDirection(ANIMATION_DIRECTION[animationValue.playMode.value]);
    }

    if (animationValue.curve.hasValue) {
        RefPtr<Curve> curve = CreateCurve(animationValue.curve.value);
        result.SetCurve(curve);
    }

    if (animationValue.finishCallbackType.hasValue) {
        result.SetFinishCallbackType(FINISH_CALLBACK_TYPE[animationValue.finishCallbackType.value]);
    }

    if (animationValue.min.hasValue && animationValue.max.hasValue && animationValue.expected.hasValue) {
        RefPtr<FrameRateRange> range = AceType::MakeRefPtr<FrameRateRange>(
            animationValue.min.hasValue,
            animationValue.max.hasValue,
            animationValue.expected.hasValue
        );
        result.SetFrameRateRange(range);
    }

    if (animationValue.onFinish.hasValue) {
        auto id = Container::CurrentIdSafely();
        WeakPtr<NG::FrameNode> frameNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onFinishEvent = [node = frameNode, id, cjCallback = CJLambda::Create(animationValue.onFinish.value)]() {
            ContainerScope scope(id);
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            cjCallback();
        };
        result.SetOnFinishEvent(onFinishEvent);
    }
}
}
