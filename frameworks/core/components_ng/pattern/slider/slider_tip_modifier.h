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
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class SliderTipModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(SliderTipModifier, OverlayModifier);

public:
    SliderTipModifier();
    ~SliderTipModifier() override = default;

    void PaintTip(DrawingContext& context);
    void PaintBubble(DrawingContext& context);

    void onDraw(DrawingContext& context) override
    {
        if (tipFlag_->Get()) {
            PaintTip(context);
        }
    }

    void SetParagraph(const RefPtr<NG::Paragraph>& paragraph)
    {
        paragraph_ = paragraph;
    }

    void SetDirection(const Axis& axis)
    {
        axis_ = axis;
    }

    void SetTipColor(const Color& color)
    {
        tipColor_ = color;
    }

    void SetTipFlag(bool flag)
    {
        if (tipFlag_) {
            tipFlag_->Set(flag);
        }
    }

    void SetContentOffset(OffsetF contentOffset)
    {
        if (contentOffset_) {
            contentOffset_->Set(contentOffset);
        }
    }

    void SetBubbleSize(SizeF bubbleSize)
    {
        if (bubbleSize_) {
            bubbleSize_->Set(bubbleSize);
        }
    }

    void SetBubbleOffset(OffsetF bubbleOffset)
    {
        if (bubbleOffset_) {
            bubbleOffset_->Set(bubbleOffset);
        }
    }

    void SetTextOffset(OffsetF textOffset)
    {
        if (textOffset_) {
            textOffset_->Set(textOffset);
        }
    }

private:
    RefPtr<PropertyBool> tipFlag_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> bubbleSize_;
    RefPtr<PropertyOffsetF> bubbleOffset_;
    RefPtr<PropertyOffsetF> textOffset_;
    RefPtr<NG::Paragraph> paragraph_;
    Axis axis_ = Axis::HORIZONTAL;
    Color tipColor_ = Color::BLACK;
    ACE_DISALLOW_COPY_AND_MOVE(SliderTipModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_TIP_MODIFIER_H
