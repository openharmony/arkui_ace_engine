/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H

#include "core/components/rating/rating_theme.h"
#include "core/components_ng/pattern/rating/rating_modifier.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_ng/render/image_painter.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RatingPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RatingPaintMethod, NodePaintMethod)
public:
    RatingPaintMethod(const RefPtr<RatingModifier>& ratingModifier, int32_t starNum,
        RatingModifier::RatingAnimationType state, bool reverse)
        : ratingModifier_(ratingModifier), starNum_(starNum), state_(state), reverse_(reverse)
    {}
    ~RatingPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(ratingModifier_, nullptr);
        return ratingModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(ratingModifier_);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto ratingTheme = pipeline->GetTheme<RatingTheme>();
        CHECK_NULL_VOID(ratingTheme);
        auto paintProperty = DynamicCast<RatingRenderProperty>(paintWrapper->GetPaintProperty());
        ratingModifier_->SetContentOffset(paintWrapper->GetContentOffset());
        ratingModifier_->SetContentSize(paintWrapper->GetContentSize());
        ratingModifier_->SetStartNum(starNum_);
        if (paintProperty) {
            constexpr double DEFAULT_RATING_TOUCH_STAR_NUMBER = -1;
            ratingModifier_->SetDrawScore(isfocus_ ? focusRatingScore_ : paintProperty->GetRatingScoreValue(0.f));
            ratingModifier_->SetStepSize(paintProperty->GetStepSize().value_or(ratingTheme->GetStepSize()));
            ratingModifier_->SetTouchStar(paintProperty->GetTouchStar().value_or(DEFAULT_RATING_TOUCH_STAR_NUMBER));
        }
        ratingModifier_->SetReverse(reverse_);
        ratingModifier_->SetHoverState(state_);
    }

    void UpdateFocusState(bool isfocus, double focusRatingScore)
    {
        isfocus_ = isfocus;
        focusRatingScore_ = focusRatingScore;
    }

private:
    RefPtr<RatingModifier> ratingModifier_;
    bool isfocus_ = false;
    double focusRatingScore_ = .0f;
    int32_t starNum_ = 0;
    RatingModifier::RatingAnimationType state_;
    bool reverse_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(RatingPaintMethod);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H
