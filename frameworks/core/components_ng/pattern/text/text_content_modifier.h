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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_CONTENT_MODIFIER_H

#include <optional>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/marquee_option.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/linear_vector.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

enum class MarqueeState {
    IDLE, RUNNING, PAUSED, STOPPED
};

struct FadeoutInfo {
    bool isLeftFadeout = false;
    bool isRightFadeout = false;
    double fadeoutPercent = 0.0;
    float paragraph1StartPosition = 0.0f;
    float paragraph1EndPosition = 0.0f;
    float paragraph2StartPosition = 0.0f;
    float paragraph2EndPosition = 0.0f;

    bool IsFadeout() const
    {
        return isLeftFadeout || isRightFadeout;
    }
};

class TextContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(TextContentModifier, ContentModifier);

public:
    explicit TextContentModifier(const std::optional<TextStyle>& textStyle, const WeakPtr<Pattern>& pattern = nullptr);
    ~TextContentModifier() override = default;

    void onDraw(DrawingContext& drawingContext) override;

    void SetFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset = false);
    void SetAdaptMinFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset = false);
    void SetAdaptMaxFontSize(const Dimension& value, const TextStyle& textStyle, bool isReset = false);
    void SetFontWeight(const FontWeight& value, bool isReset = false);
    void SetTextColor(const Color& value, bool isReset = false);
    void SetSymbolColor(const std::vector<Color>& value, bool isReset = false);
    void SetTextShadow(const std::vector<Shadow>& value);
    void SetTextDecoration(const TextDecoration& value, bool isReset = false);
    void SetTextDecorationColor(const Color& value, bool isReset = false);
    void SetBaselineOffset(const Dimension& value, const TextStyle& textStyle, bool isReset = false);
    void SetLineHeight(const Dimension& value, const TextStyle& textStyle, bool isReset = false);
    void SetContentOffset(OffsetF& value);
    void SetContentSize(SizeF& value);

    void ContentChange();

    void ModifyTextStyle(TextStyle& textStyle, Color& textColor);

    void StartTextRace(const MarqueeOption& option);
    void StopTextRace();
    void ResumeAnimation();
    void PauseAnimation();
    void SetIsFocused(const bool isFocused);
    void SetIsHovered(const bool isHovered);

    void SetPrintOffset(const OffsetF& paintOffset)
    {
        paintOffset_ = paintOffset;
    }

    void SetIfPaintObscuration(bool value)
    {
        ifPaintObscuration_ = value;
    }

    void SetDrawObscuredRects(const std::vector<RectF>& drawObscuredRects)
    {
        drawObscuredRects_ = drawObscuredRects;
    }

    bool NeedMeasureUpdate(PropertyChangeFlag& flag);

    void SetClip(bool clip);

    void SetFontReady(bool value);
    void ChangeDragStatus();

    void SetImageSpanNodeList(std::vector<WeakPtr<FrameNode>> imageNodeList)
    {
        imageNodeList_ = imageNodeList;
    }
    void TextColorModifier(const Color& value);
    void ContentModifierDump();
    void SetHybridRenderTypeIfNeeded(DrawingContext& drawingContext, const RefPtr<TextPattern>& textPattern,
        const RefPtr<ParagraphManager>& pManager, RefPtr<FrameNode>& host);
    void SetRacePercentFloat(float value);
protected:
    OffsetF GetPaintOffset() const
    {
        return paintOffset_;
    }

private:
    double NormalizeToPx(const Dimension& dimension);
    void SetDefaultAnimatablePropertyValue(const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode);
    void SetDefaultFontSize(const TextStyle& textStyle);
    void SetDefaultAdaptMinFontSize(const TextStyle& textStyle);
    void SetDefaultAdaptMaxFontSize(const TextStyle& textStyle);
    void SetDefaultFontWeight(const TextStyle& textStyle);
    void SetDefaultTextColor(const TextStyle& textStyle);
    void SetDefaultSymbolColor(const TextStyle& textStyle);
    void SetSymbolColors(const LinearVector<LinearColor>& value);
    LinearVector<LinearColor> Convert2VectorLinearColor(const std::vector<Color>& colorList);
    void SetDefaultTextShadow(const TextStyle& textStyle);
    void AddShadow(const Shadow& shadow);
    void AddDefaultShadow();
    void SetDefaultTextDecoration(const TextStyle& textStyle);
    void SetDefaultBaselineOffset(const TextStyle& textStyle);
    void SetDefaultLineHeight(const TextStyle& textStyle);
    float GetTextRacePercent();
    TextDirection GetTextRaceDirection() const;
    TextDirection GetTextRaceDirectionByContent() const;
    void ResetTextRacePercent();
    bool SetTextRace(const MarqueeOption& option);
    void ResumeTextRace(bool bounce);
    void SetTextRaceAnimation(const AnimationOption& option);
    void PauseTextRace();
    bool AllowTextRace();
    void DetermineTextRace();

    void ModifyFontSizeInTextStyle(TextStyle& textStyle);
    void ModifyAdaptMinFontSizeInTextStyle(TextStyle& textStyle);
    void ModifyAdaptMaxFontSizeInTextStyle(TextStyle& textStyle);
    void ModifyFontWeightInTextStyle(TextStyle& textStyle);
    void ModifyTextColorInTextStyle(Color& textColor);
    void ModifySymbolColorInTextStyle(TextStyle& textStyle);
    std::vector<Color> Convert2VectorColor(const LinearVector<LinearColor>& colorList);
    void ModifyTextShadowsInTextStyle(TextStyle& textStyle);
    void ModifyDecorationInTextStyle(TextStyle& textStyle);
    void ModifyBaselineOffsetInTextStyle(TextStyle& textStyle);
    void ModifyLineHeightInTextStyle(TextStyle& textStyle);

    void UpdateFontSizeMeasureFlag(PropertyChangeFlag& flag);
    void UpdateAdaptMinFontSizeMeasureFlag(PropertyChangeFlag& flag);
    void UpdateAdaptMaxFontSizeMeasureFlag(PropertyChangeFlag& flag);
    void UpdateFontWeightMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextColorMeasureFlag(PropertyChangeFlag& flag);
    void UpdateSymbolColorMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextShadowMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag);
    void UpdateBaselineOffsetMeasureFlag(PropertyChangeFlag& flag);
    void UpdateLineHeightMeasureFlag(PropertyChangeFlag& flag);
    bool CheckNeedMeasure(float finalValue, float lastValue, float currentValue);

    void ChangeParagraphColor(const RefPtr<Paragraph>& paragraph);
    void DrawObscuration(DrawingContext& drawingContext);
    void UpdateImageNodeVisible(const VisibleType visible);
    void PaintImage(RSCanvas& canvas, float x, float y);
    bool DrawImage(const RefPtr<FrameNode>& imageNode, RSCanvas& canvas, float x, float y, const RectF& rect);
    void PaintCustomSpan(DrawingContext& drawingContext);
    void DrawTextRacing(DrawingContext& drawingContext, const FadeoutInfo& info, RefPtr<ParagraphManager> pManager);
    void DrawText(RSCanvas& canvas, const RefPtr<ParagraphManager>& pManager, const RefPtr<TextPattern>& textPattern);
    void DrawContent(DrawingContext& drawingContext, const FadeoutInfo& info);
    void DrawActualText(DrawingContext& drawingContext, const RefPtr<TextPattern>& textPattern,
        const RefPtr<ParagraphManager>& pManager, const FadeoutInfo& fadeoutInfo);
    void DrawFadeout(DrawingContext& drawingContext, const FadeoutInfo& info);
    FadeoutInfo GetFadeoutInfo(DrawingContext& drawingContext);
    float GetFadeoutPercent();
    void SetMarqueeState(MarqueeState state);
    bool CheckMarqueeState(MarqueeState state)
    {
        return marqueeState_ == state;
    }
    bool IsMarqueeVisible() const;
    void UpdateTextDecorationColorAlpha();

    std::optional<Dimension> fontSize_;
    float lastFontSize_ = 0.0f;
    RefPtr<AnimatablePropertyFloat> fontSizeFloat_;

    std::optional<Dimension> adaptMinFontSize_;
    RefPtr<AnimatablePropertyFloat> adaptMinFontSizeFloat_;
    float lastMinFontSize_ = 0.0f;

    std::optional<Dimension> adaptMaxFontSize_;
    RefPtr<AnimatablePropertyFloat> adaptMaxFontSizeFloat_;
    float lastMaxFontSize_ = 0.0f;

    std::optional<FontWeight> fontWeight_;
    RefPtr<AnimatablePropertyFloat> fontWeightFloat_;
    float lastFontWeight_ = 0.0f;

    std::optional<Color> textColor_;
    RefPtr<AnimatablePropertyColor> animatableTextColor_;
    Color lastTextColor_;
    bool onlyTextColorAnimation_ = false;

    std::optional<LinearVector<LinearColor>> symbolColors_;
    RefPtr<AnimatablePropertyVectorLinearVector> animatableSymbolColor_;
    LinearVector<LinearColor> lastSymbolColors_;

    struct ShadowProp {
        Shadow shadow; // final shadow configuration of the animation
        Shadow lastShadow;
        RefPtr<AnimatablePropertyFloat> blurRadius;
        RefPtr<AnimatablePropertyFloat> offsetX;
        RefPtr<AnimatablePropertyFloat> offsetY;
        RefPtr<AnimatablePropertyColor> color;
    };
    std::vector<ShadowProp> shadows_;

    std::optional<TextDecoration> textDecoration_;
    std::optional<Color> textDecorationColor_;
    Color lastTextDecorationColor_;
    RefPtr<AnimatablePropertyFloat> textDecorationColorAlpha_;
    float lastTextDecorationColorAlpha_ = 0.0f;
    bool textDecorationAnimatable_ { false };

    std::optional<Dimension> baselineOffset_;
    RefPtr<AnimatablePropertyFloat> baselineOffsetFloat_;
    float lastBaselineOffsetFloat_ = 0.0f;

    std::optional<Dimension> lineHeight_;
    RefPtr<AnimatablePropertyFloat> lineHeightFloat_;
    float lastLineHeight_ = 0.0f;

    WeakPtr<Pattern> pattern_;

    RefPtr<AnimatablePropertyFloat> racePercentFloat_;
    std::shared_ptr<AnimationUtils::Animation> raceAnimation_;

    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyInt> contentChange_;
    RefPtr<PropertyBool> clip_;
    RefPtr<PropertyBool> fontReady_;
    RefPtr<PropertyBool> dragStatus_;
    OffsetF paintOffset_;
    float textRaceSpaceWidth_ = 0;

    bool ifPaintObscuration_ = false;
    std::vector<RectF> drawObscuredRects_;
    std::vector<WeakPtr<FrameNode>> imageNodeList_;
    MarqueeState marqueeState_ = MarqueeState::IDLE;

    bool textRacing_ = false;
    bool marqueeSet_ = false;
    MarqueeOption marqueeOption_;
    int32_t marqueeCount_ = 0;
    int32_t marqueeAnimationId_ = 0;
    bool marqueeFocused_ = false;
    bool marqueeHovered_ = false;
    int32_t marqueeDuration_ = 0;
    float marqueeGradientPercent_ = 0.0f;
    float marqueeRaceMaxPercent_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(TextContentModifier);
};
} // namespace OHOS::Ace::NG

#endif