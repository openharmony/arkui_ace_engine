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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_TIP_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_TIP_MODIFIER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/slider/slider_content_modifier.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class SliderTipModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(SliderTipModifier, OverlayModifier);

public:
    explicit SliderTipModifier(std::function<std::pair<OffsetF, float>()> getBubbleVertexFunc,
        std::function<void()> onFinishEventTipSize = nullptr);
    ~SliderTipModifier() override;

    void PaintTip(DrawingContext& context);
    void PaintBubble(DrawingContext& context);

    void onDraw(DrawingContext& context) override;

    void SetParagraph(const RefPtr<NG::Paragraph>& paragraph)
    {
        paragraph_ = paragraph;
    }

    void SetBubbleVertex(const OffsetF& bubbleVertex)
    {
        if (bubbleVertex_) {
            bubbleVertex_->Set(bubbleVertex);
        }
    }

    void SetTextFontSize(const Dimension& fontSize)
    {
        textFontSize_ = fontSize;
    }

    void SetContent(const std::string& content)
    {
        if (content_) {
            content_->Set(content);
        }
    }

    void SetTextColor(const Color& textColor)
    {
        textColor_ = textColor;
    }

    void SetDirection(const Axis& axis)
    {
        axis_ = axis;
    }

    void SetTipColor(const Color& color)
    {
        tipColor_ = color;
    }

    void SetTipFlag(bool flag, const RefPtr<FrameNode>& host);

    void SetContentOffset(const OffsetF& contentOffset)
    {
        if (contentOffset_) {
            contentOffset_->Set(contentOffset);
        }
    }

    void SetContentSize(const SizeF& contentSize)
    {
        if (contentSize_) {
            contentSize_->Set(contentSize);
        }
    }

    void SetBubbleSize(const SizeF& bubbleSize)
    {
        bubbleSize_ = bubbleSize;
    }

    void SetSliderGlobalOffset(const OffsetF& sliderGlobalOffset)
    {
        if (sliderGlobalOffset_) {
            sliderGlobalOffset_->Set(sliderGlobalOffset);
        }
    }

    void SetBubbleOffset(const OffsetF& bubbleOffset)
    {
        bubbleOffset_ = bubbleOffset;
    }

    void SetTextOffset(const OffsetF& textOffset)
    {
        textOffset_ = textOffset;
    }

    void SetSliderMode(const SliderModel::SliderMode& sliderMode)
    {
        sliderMode_ = sliderMode;
    }

    void SetBlockSize(const SizeF& blockSize)
    {
        blockSize_ = blockSize;
    }

    void BuildParagraph();
    void UpdateBubbleSize();
    bool UpdateOverlayRect(const SizeF& frameSize);
    void UpdateThemeParams(const RefPtr<SliderTheme>& theme);

private:
    void PaintHorizontalBubble(float vertexOffsetFromBlock, RSPath& path);
    void PaintVerticalBubble(float vertexOffsetFromBlock, RSPath& path);
    void PaintHorizontalBubbleSuitableAging(float vertexOffsetFromBlock, RSPath& path);
    void PaintVerticalBubbleSuitableAging(float vertexOffsetFromBlock, RSPath& path);
    void PaintText(DrawingContext& context);
    void SetBubbleDisplayAnimation(const RefPtr<FrameNode>& host);
    void SetBubbleDisappearAnimation(const RefPtr<FrameNode>& host);
    void CreateParagraphAndLayout(
        const TextStyle& textStyle, const std::string& content);
    bool CreateParagraph(const TextStyle& textStyle, std::string content);
    std::pair<OffsetF, float> GetBubbleVertex();

private:
    RefPtr<PropertyBool> tipFlag_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<NG::Paragraph> paragraph_;

    RefPtr<AnimatablePropertyFloat> sizeScale_;
    RefPtr<AnimatablePropertyFloat> opacityScale_;
    RefPtr<PropertyString> content_;
    RefPtr<PropertyOffsetF> bubbleVertex_;
    SizeF blockSize_;
    SizeF bubbleSize_;
    RefPtr<PropertyOffsetF> sliderGlobalOffset_;
    OffsetF bubbleOffset_;
    OffsetF textOffset_;
    OffsetF vertex_;
    bool isMask_ = false;
    Axis axis_ = Axis::HORIZONTAL;
    SliderModel::SliderMode sliderMode_ = SliderModelNG::SliderMode::OUTSET;
    Color tipColor_ = Color::BLACK;
    Color textColor_ = Color::TRANSPARENT;
    Dimension textFontSize_;
    std::function<std::pair<OffsetF, float>()> getBubbleVertexFunc_;
    int32_t taskId_ = 0;
    int32_t tipDelayTime_ = 0;
    std::function<void()> onFinishEventTipSize_;

    ACE_DISALLOW_COPY_AND_MOVE(SliderTipModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_TIP_MODIFIER_H
