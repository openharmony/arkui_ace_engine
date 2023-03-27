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
#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_owner.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class LoadingProgressModifier : public ContentModifier {
    DECLARE_ACE_TYPE(LoadingProgressModifier, ContentModifier);

public:
    LoadingProgressModifier(LoadingProgressOwner loadingProgressOwner = LoadingProgressOwner::SELF);
    ~LoadingProgressModifier() override = default;
    void onDraw(DrawingContext& context) override;
    void DrawOrbit(DrawingContext& canvas, const CometParam& cometParam, float orbitRadius, float date);
    void DrawRing(DrawingContext& canvas, const RingParam& ringParam);
    void StartRecycle();
    void StartRecycleRingAnimation();
    void StartRecycleCometAnimation();
    void StartCometTailAnimation();
    void StartTransToRecycleAnimation();
    void SetColor(LinearColor color)
    {
        if (color_) {
            color_->Set(color);
        }
    }

    void DrawCustomStyle(DrawingContext& context);
    void RefreshRecycle(DrawingContext& context, Color& color, float scale);
    void ChangeRefreshFollowData(float refreshFollowRatio);
    void ChangeFadeAwayData(float fadeAwayRatio);
    float CorrectNormalize(float originData);

    LoadingProgressOwner GetOwner()
    {
        return loadingProgressOwner_;
    }

private:
    float GetCurentCometOpacity(float baseOpacity, uint32_t index, uint32_t totalNumber);
    float GetCurentCometAngle(float baseAngle, uint32_t index, uint32_t totalNumber);

    uint32_t GetCometNumber();
    RefPtr<AnimatablePropertyFloat> date_;
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<AnimatablePropertyFloat> centerDeviation_;
    RefPtr<AnimatablePropertyFloat> cometOpacity_;
    RefPtr<AnimatablePropertyFloat> cometSizeScale_;
    RefPtr<AnimatablePropertyFloat> cometTailLen_;
    RefPtr<AnimatablePropertyFloat> sizeScale_;

    LoadingProgressOwner loadingProgressOwner_;
    bool isLoading_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H

