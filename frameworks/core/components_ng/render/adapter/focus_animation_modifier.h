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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_ANIMATION_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_ANIMATION_MODIFIER_H

#include <tuple>

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/adapter/focus_modifier.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
class FocusAnimationModifier : public FocusModifier, public OverlayModifier {
public:
    FocusAnimationModifier();
    ~FocusAnimationModifier() = default;

    void onDraw(DrawingContext& context) override;
    void StartFocusAnimation();
    void StopFocusAnimation();

private:
    void PaintFocusState(const RSRoundRect&, RSCanvas&, float);
    void InitTrajectoryData(const RSRoundRect&);
    float CalArcAngle(float, float);
    float CalArcLen(float);
    std::tuple<float, float> GetPosition(float);
    float GetIncludeAngleOfVector(float, float, float, float, float, float);
    void InitRoundRectTrajectory(const RSRoundRect&);
    void InitCircleTrajectory(float);
    void InitTrajectDataFunc();
    std::tuple<float, float, float, std::vector<RSScalar>> GetRenderParams(float, float, float);
    float GetSweepGradientRenderPos(float, float, float, float, float);
    RefPtr<AnimatablePropertyFloat> focusProcessFloat_;
    std::shared_ptr<AnimationUtils::Animation> focusAnimation_;
    bool isRise_ = true;
    bool animating_ = false;
    float grith_ = 0.0f;
    float longerSide_ = 0.0f;
    float shorterSide_ = 0.0f;
    std::map<int32_t, std::function<std::tuple<float, float>(float, float)>> trajectDataFunc_;
    std::map<int32_t, float> trajectoryData_;
    float topLeftX_ = 0.0f;
    float topLeftY_ = 0.0f;
    float topRightX_ = 0.0f;
    float topRightY_ = 0.0f;
    float bottomLeftX_ = 0.0f;
    float bottomLeftY_ = 0.0f;
    float bottomRightX_ = 0.0f;
    float bottomRightY_ = 0.0f;
    RSMatrix rsMatrix_;
};
} // namespace OHOS::Ace::NG
#endif