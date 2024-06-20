/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_MODIFIER_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/rating/rating_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class RatingModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RatingModifier, ContentModifier);

public:
    RatingModifier();
    ~RatingModifier() override = default;

    enum class RatingAnimationType {
        NONE = 0,
        HOVER,
        HOVERTOPRESS,
        PRESSTOHOVER,
        PRESS,
    };

    void PaintBoard(DrawingContext& context);
    void PaintStar(DrawingContext& context);
    void PaintReverseStar(DrawingContext& context);

    void onDraw(DrawingContext& context) override;

    void UpdateCanvasImage(const RefPtr<CanvasImage>& foregroundImageCanvas,
        const RefPtr<CanvasImage>& secondaryImageCanvas, const RefPtr<CanvasImage>& backgroundImageCanvas,
        const ImagePaintConfig& foregroundConfig, const ImagePaintConfig& secondaryConfig,
        const ImagePaintConfig& backgroundConfig)
    {
        SetNeedDraw(true);
        foregroundImageCanvas_ = foregroundImageCanvas;
        secondaryImageCanvas_ = secondaryImageCanvas;
        backgroundImageCanvas_ = backgroundImageCanvas;
        foregroundImageCanvas_->SetPaintConfig(foregroundConfig);
        secondaryImageCanvas_->SetPaintConfig(secondaryConfig);
        backgroundImageCanvas_->SetPaintConfig(backgroundConfig);
    }

    void UpdateImageSourceInfo(
        const ImageSourceInfo& foreground, const ImageSourceInfo& secondary, const ImageSourceInfo& background)
    {
        foreground_ = foreground;
        secondary_ = secondary;
        background_ = background;
    }

    bool JudgeImageSourceInfo(const ImageSourceInfo& foreground, const ImageSourceInfo& secondary,
        const ImageSourceInfo& background, const ImagePaintConfig& foregroundConfig)
    {
        if (foreground_ != foreground) {
            return true;
        }
        if (secondary_ != secondary) {
            return true;
        }
        if (background_ != background) {
            return true;
        }
        CHECK_NULL_RETURN(foregroundImageCanvas_, true);
        if (foregroundImageCanvas_->GetPaintConfig().dstRect_ != foregroundConfig.dstRect_) {
            return true;
        }
        if (foregroundImageCanvas_->GetPaintConfig().scaleX_ != foregroundConfig.scaleX_ ||
            foregroundImageCanvas_->GetPaintConfig().scaleY_ != foregroundConfig.scaleY_) {
            return true;
        }
        // No need to update three CanvasImages
        return false;
    }

    void SetNeedDraw(bool flag)
    {
        if (needDraw_) {
            needDraw_->Set(flag);
        }
    }

    void SetBoardColor(LinearColor color, int32_t duratuion, const RefPtr<CubicCurve>& curve)
    {
        if (boardColor_) {
            AnimationOption option = AnimationOption();
            option.SetDuration(duratuion);
            option.SetCurve(curve);
            AnimationUtils::Animate(option, [&]() { boardColor_->Set(color); });
        }
    }

    void SetContentOffset(OffsetF contentOffset)
    {
        if (contentOffset_) {
            contentOffset_->Set(contentOffset);
        }
    }

    void SetContentSize(SizeF contentSize)
    {
        if (contentSize_) {
            contentSize_->Set(contentSize);
        }
    }

    void SetDrawScore(double drawScore)
    {
        if (drawScore_) {
            drawScore_->Set(static_cast<float>(drawScore));
        }
    }

    void SetStepSize(double stepSize)
    {
        if (stepSize_) {
            stepSize_->Set(static_cast<float>(stepSize));
        }
    }

    void SetTouchStar(int32_t touchStar)
    {
        if (touchStar < 0 || touchStar >= starNum_->Get() || touchStar_->Get() != touchStar) {
            SetHoverState(RatingAnimationType::NONE);
        }
        if (touchStar_) {
            touchStar_->Set(touchStar);
        }
    }

    void SetStartNum(int32_t starNum)
    {
        if (starNum_) {
            starNum_->Set(starNum);
        }
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

    void SetHoverState(const RatingAnimationType& state)
    {
        if (state_ == state) {
            return;
        }
        state_ = state;
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto ratingTheme = pipeline->GetTheme<RatingTheme>();
        CHECK_NULL_VOID(ratingTheme);
        auto hoverDuration = static_cast<int32_t>(ratingTheme->GetHoverAnimationDuration());
        auto pressDuration = static_cast<int32_t>(ratingTheme->GetPressAnimationDuration());
        switch (state) {
            case RatingAnimationType::HOVER:
                SetBoardColor(LinearColor(ratingTheme->GetHoverColor()), hoverDuration, Curves::FRICTION);
                break;
            case RatingAnimationType::HOVERTOPRESS:
                SetBoardColor(LinearColor(ratingTheme->GetPressColor()), pressDuration, Curves::SHARP);
                break;
            case RatingAnimationType::PRESSTOHOVER:
                SetBoardColor(LinearColor(ratingTheme->GetHoverColor()), pressDuration, Curves::SHARP);
                break;
            case RatingAnimationType::PRESS:
                SetBoardColor(LinearColor(ratingTheme->GetPressColor()), hoverDuration, Curves::SHARP);
                break;
            case RatingAnimationType::NONE:
                SetBoardColor(LinearColor(Color::TRANSPARENT), hoverDuration, Curves::FRICTION);
                break;
            default:
                break;
        }
    }

    void SetReverse(bool reverse)
    {
        if (reverse_) {
            reverse_->Set(reverse);
        }
    }

private:
    // others
    RatingAnimationType state_ = RatingAnimationType::NONE;
    RefPtr<CanvasImage> foregroundImageCanvas_;
    RefPtr<CanvasImage> secondaryImageCanvas_;
    RefPtr<CanvasImage> backgroundImageCanvas_;
    ImageSourceInfo foreground_;
    ImageSourceInfo secondary_;
    ImageSourceInfo background_;
    // non-animatable property
    RefPtr<PropertyBool> needDraw_;
    RefPtr<PropertyInt> starNum_;
    RefPtr<PropertyInt> touchStar_;
    RefPtr<PropertyFloat> drawScore_;
    RefPtr<PropertyFloat> stepSize_;
    RefPtr<PropertyBool> useContentModifier_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    // animatable property
    RefPtr<AnimatablePropertyColor> boardColor_;
    RefPtr<PropertyBool> reverse_;
    ACE_DISALLOW_COPY_AND_MOVE(RatingModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_MODIFIER_H
