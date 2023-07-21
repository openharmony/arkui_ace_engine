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

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
ListContentModifier::ListContentModifier(const OffsetF& clipOffset, const SizeF& clipSize)
{
    clipOffset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(clipOffset);
    clipSize_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(clipSize);
    clip_ = AceType::MakeRefPtr<PropertyBool>(true);
    flushDivider_ = AceType::MakeRefPtr<PropertyBool>(true);

    AttachProperty(clipOffset_);
    AttachProperty(clipSize_);
    AttachProperty(clip_);
    AttachProperty(flushDivider_);
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
    if (dividerInfo_.has_value()) {
        PaintDivider(dividerInfo_.value(), itemPosition_, context.canvas);
    }
}

void ListContentModifier::PaintDivider(
    const DividerInfo& dividerInfo, const PositionMap& itemPosition, RSCanvas& canvas)
{
    float fSpacingTotal = (dividerInfo.lanes - 1) * dividerInfo.laneGutter;
    float laneLen =
        (dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;

    float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
    DividerPainter dividerPainter(
        dividerInfo.constrainStrokeWidth, crossLen, dividerInfo.isVertical, dividerInfo.color, LineCap::SQUARE);

    int32_t lanes = dividerInfo.lanes;
    int32_t laneIdx = 0;
    bool lastIsItemGroup = false;
    bool isFirstItem = (itemPosition.begin()->first == 0);
    std::list<int32_t> lastLineIndex;

    for (const auto& child : itemPosition) {
        if (!isFirstItem) {
            float divOffset = (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = child.second.startPos - divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !lastIsItemGroup && !child.second.isGroup) {
                crossPos +=
                    laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
                dividerPainter.SetDividerLength(laneLen);
            } else {
                dividerPainter.SetDividerLength(crossLen);
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset);
        }
        if (laneIdx == 0 || child.second.isGroup) {
            lastLineIndex.clear();
        }
        lastLineIndex.emplace_back(child.first);
        lastIsItemGroup = child.second.isGroup;
        laneIdx = (lanes <= 1 || (laneIdx + 1) >= lanes || child.second.isGroup) ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (!lastLineIndex.empty() && *lastLineIndex.rbegin() < dividerInfo.totalItemCount - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index + lanes >= dividerInfo.totalItemCount) {
                break;
            }
            float divOffset = (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = itemPosition.at(index).endPos + divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !itemPosition.at(index).isGroup) {
                crossPos +=
                    laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
                dividerPainter.SetDividerLength(laneLen);
            } else {
                dividerPainter.SetDividerLength(crossLen);
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset);
            laneIdx++;
        }
    }
}
} // namespace OHOS::Ace::NG
