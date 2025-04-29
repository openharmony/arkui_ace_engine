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

#include "core/components_ng/pattern/list/list_content_modifier.h"

#include "core/components_ng/render/divider_painter.h"

namespace OHOS::Ace::NG {
ListContentModifier::ListContentModifier(const OffsetF& clipOffset, const SizeF& clipSize)
{
    color_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT);
    clipOffset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(clipOffset);
    clipSize_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(clipSize);
    clip_ = AceType::MakeRefPtr<PropertyBool>(true);
    refDivider_ = AceType::MakeRefPtr<RefDividerMap>();
    ListDividerMap dividerMap;
    RefPtr<ListDividerArithmetic> lda = AceType::MakeRefPtr<ListDividerArithmetic>(dividerMap, refDivider_);
    dividerList_ = AceType::MakeRefPtr<AnimatableArithmeticProperty>(
        AceType::DynamicCast<CustomAnimatableArithmetic>(lda));

    AttachProperty(color_);
    AttachProperty(clipOffset_);
    AttachProperty(clipSize_);
    AttachProperty(clip_);
    AttachProperty(dividerList_);
}

void ListContentModifier::onDraw(DrawingContext& context)
{
    if (clip_->Get()) {
        auto offset = clipOffset_->Get();
        auto size = clipSize_->Get();
        auto clipRect = RSRect(offset.GetX(), offset.GetY(),
            offset.GetX() + size.Width(), offset.GetY() + size.Height());
        context.canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }

    CHECK_NULL_VOID(dividerList_);
    auto dividerlist = dividerList_->Get();
    CHECK_NULL_VOID(dividerlist);
    auto lda = AceType::DynamicCast<ListDividerArithmetic>(dividerlist);
    CHECK_NULL_VOID(lda);
    const auto& dividerMap = isNeedDividerAnimation_ ? lda->GetDividerMap() : refDivider_->GetMap();
    if (!dividerMap.empty()) {
        DividerPainter dividerPainter(
            width_, 0, isVertical_, color_->Get().ToColor(), LineCap::SQUARE);
        for (const auto& child : dividerMap) {
            if (child.second.length > 0) {
                dividerPainter.SetDividerLength(child.second.length);
                dividerPainter.DrawLine(context.canvas, child.second.offset);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
