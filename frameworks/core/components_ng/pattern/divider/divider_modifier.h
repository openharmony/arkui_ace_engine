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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
class DividerModifier : public ContentModifier {
    DECLARE_ACE_TYPE(DividerModifier, ContentModifier);
public:
    DividerModifier();
    ~DividerModifier() override = default;
    void PaintDivider(DrawingContext& context) const;
    void onDraw(DrawingContext& context) override;
    
    void SetColor(LinearColor color)
    {
        color_->Set(color);
    }

    void SetStrokeWidth(float strokeWidth)
    {
        strokeWidth_->Set(strokeWidth);
    }

    void SetDividerLength(float dividerLength)
    {
        dividerLength_->Set(dividerLength);
    }

    void SetLineCap(LineCap lineCap)
    {
        lineCap_->Set(static_cast<int>(lineCap));
    }

    void SetVertical(bool vertical)
    {
        vertical_->Set(vertical);
    }

    void SetOffset(OffsetF offset)
    {
        offset_->Set(offset);
    }

    void SetStrokeWidthLimitation(bool limite)
    {
        strokeWidthLimitation_->Set(limite);
    }

private:
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<PropertyFloat> dividerLength_;
    RefPtr<PropertyInt> lineCap_;
    RefPtr<PropertyBool> vertical_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertyBool> strokeWidthLimitation_;

    ACE_DISALLOW_COPY_AND_MOVE(DividerModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_MODIFIER_H
