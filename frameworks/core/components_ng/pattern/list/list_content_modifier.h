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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/list/list_divider_arithmetic.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class ListContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ListContentModifier, ContentModifier);
public:
    ListContentModifier(const OffsetF& clipOffset, const SizeF& clipSize);
    ~ListContentModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetClipOffset(OffsetF offset)
    {
        clipOffset_->Set(offset);
    }

    void SetClipSize(SizeF size)
    {
        clipSize_->Set(size);
    }

    void SetClip(bool clip)
    {
        clip_->Set(clip);
    }

    void SetDividerPainter(float width, bool isVertical, Color color)
    {
        width_ = width;
        isVertical_ = isVertical;
        color_->Set(LinearColor(color));
    }

    void SetDividerMap(const ListDividerMap& dividerMap)
    {
        CHECK_NULL_VOID(refDivider_);
        refDivider_->SetMap(dividerMap);
        RefPtr<ListDividerArithmetic> lda = AceType::MakeRefPtr<ListDividerArithmetic>(dividerMap, refDivider_);
        CHECK_NULL_VOID(dividerList_);
        dividerList_->Set(AceType::DynamicCast<CustomAnimatableArithmetic>(lda));
    }

private:
    RefPtr<AnimatableArithmeticProperty> dividerList_;
    RefPtr<AnimatablePropertyOffsetF> clipOffset_;
    RefPtr<AnimatablePropertySizeF> clipSize_;
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<PropertyBool> clip_;
    RefPtr<RefDividerMap> refDivider_;

    float width_ = 0.0f;
    bool isVertical_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(ListContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H
