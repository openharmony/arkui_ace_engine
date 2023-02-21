/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_owner.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LOADING_DURATION = 300;
constexpr float LOADING_TEMPO = 0.2f;
constexpr float FOLLOW_START = 58.0f;
constexpr float FOLLOW_SPAN = 18.0f;
constexpr float FOLLOW_TO_RECYCLE_START = 76.0f;
constexpr float FOLLOW_TO_RECYCLE_SPAN = 24.0f;
constexpr float FULL_COUNT = 100.0f;
}
class LoadingProgressModifier : public ContentModifier {
    DECLARE_ACE_TYPE(LoadingProgressModifier, ContentModifier);

public:
    LoadingProgressModifier(LoadingProgressOwner loadingProgressOwner = LoadingProgressOwner::SELF);
    ~LoadingProgressModifier() override = default;
    void onDraw(DrawingContext& context) override;
    void DrawOrbit(DrawingContext& canvas, float date, float scale_);
    void DrawRing(DrawingContext& canvas, float date, float scale_);
    void UpdateLoadingSize(float diameter);
    void CalculateValue(int32_t start, int32_t end, double percent = 1.0);
    void StartRecycle()
    {
        if (isLoading_) {
            return;
        }
        if (date_) {
            isLoading_ = true;
            date_->Set(0.0f);
            AnimationOption option = AnimationOption();
            RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
            option.SetDuration(LOADING_DURATION);
            option.SetDelay(0);
            option.SetCurve(curve);
            option.SetIteration(-1);
            option.SetTempo(LOADING_TEMPO);
            AnimationUtils::Animate(option, [&]() { date_->Set(FULL_COUNT); });
        }
    }

    void SetColor(LinearColor color)
    {
        if (color_) {
            color_->Set(color);
        }
    }

    void DrawCustomStyle(DrawingContext& context);

    void RefreshRecycle(DrawingContext& context, Color& color, float scale);

    void ChangeRefreshFollowData(float refreshFollowRatio)
    {
        CHECK_NULL_VOID(date_);
        auto ratio = CorrectNormalize(refreshFollowRatio);
        date_->Set(FOLLOW_START + FOLLOW_SPAN * ratio);
    }

    void ChangeRefreshTansitionData(float refreshTransitionRatio)
    {
        CHECK_NULL_VOID(date_);
        auto ratio = CorrectNormalize(refreshTransitionRatio);
        date_->Set(FOLLOW_TO_RECYCLE_START + FOLLOW_TO_RECYCLE_SPAN * ratio);
    }

    void ChangeRefreshFadeAwayData(float refreshTransitionRatio)
    {
        CHECK_NULL_VOID(date_);
        auto ratio = CorrectNormalize(refreshTransitionRatio);
        date_->Set(FOLLOW_TO_RECYCLE_START + FOLLOW_TO_RECYCLE_SPAN * ratio);
    }

    float CorrectNormalize(float originData)
    {
        auto ratio = originData;
        if (ratio < 0.0f) {
            ratio = 0.0f;
        }
        if (ratio > 1.0f) {
            ratio = 1.0f;
        };
        return ratio;
    }

    LoadingProgressOwner GetOwner()
    {
        return loadingProgressOwner_;
    }

private:
    RefPtr<AnimatablePropertyFloat> date_;
    RefPtr<AnimatablePropertyColor> color_;
    float ringWidth_ = 0.0f;
    float cometRadius_ = 0.0f;
    LoadingProgressOwner loadingProgressOwner_;
    bool isLoading_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H

