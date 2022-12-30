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
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
const Dimension RING_RADIUS = 10.5_vp;
const Dimension ORBIT_RADIUS = 17.0_vp;
const float RING_MOVEMENT = 0.06f;
const float FULL_COUNT = 100.0f;
const float COUNT = 50.0f;
const float HALF = 0.5f;
const int32_t LOADING_DURATION = 300;
const float LOADING_TEMPO = 0.2f;

class LoadingProgressModifier : public ContentModifier {
    DECLARE_ACE_TYPE(LoadingProgressModifier, ContentModifier);

public:
    LoadingProgressModifier();
    ~LoadingProgressModifier() override = default;
    void onDraw(DrawingContext& context) override
    {
        float scale_ = 1.0;
        float date = date_->Get();
        UpdateLoadingSize(std::min(context.width, context.height));
        scale_ = std::min((context.width / (ORBIT_RADIUS.ConvertToPx() + cometRadius_ / HALF)),
            (context.height / (RING_RADIUS.ConvertToPx() * (1 + RING_MOVEMENT) + ringWidth_ * HALF))) * HALF;
        if (date > COUNT) {
            DrawRing(context, date, scale_);
            DrawOrbit(context, date, scale_);
        } else {
            DrawOrbit(context, date, scale_);
            DrawRing(context, date, scale_);
        }
    }

    void DrawRing(DrawingContext& canvas, float date, float scale_) const;
    void DrawOrbit(DrawingContext& canvas, float date, float scale_) const;
    void UpdateLoadingSize(float diameter);
    void CalculateValue(int32_t start, int32_t end, double percent = 1.0);

    void SetDate(float date)
    {
        if (date_) {
            AnimationOption option = AnimationOption();
            RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
            option.SetDuration(LOADING_DURATION);
            option.SetDelay(0);
            option.SetCurve(curve);
            option.SetIteration(-1);
            option.SetTempo(LOADING_TEMPO);
            AnimationUtils::Animate(option, [&]() { date_->Set(date); });
        }
    }

    void SetColor(LinearColor color)
    {
        if (color_) {
            color_->Set(color);
        }
    }

private:
    RefPtr<AnimatablePropertyFloat> date_;
    RefPtr<AnimatablePropertyColor> color_;
    float ringWidth_ = 0.0f;
    float cometRadius_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H
