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

#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> RichEditorDragPattern::CreateDragNode(const RefPtr<FrameNode>& hostNode,
    const TextDragInfo& info)
{
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    CHECK_NULL_RETURN(hostPattern, nullptr);
    const auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dragNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_DRAG_ETS_TAG, nodeId, [hostPattern, info]() {
        auto dragInfo = std::make_shared<TextDragInfo>(info);
        return MakeRefPtr<RichEditorDragPattern>(DynamicCast<TextPattern>(hostPattern), dragInfo);
    });
    auto dragContext = dragNode->GetRenderContext();
    CHECK_NULL_RETURN(dragContext, nullptr);
    auto hostContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(hostContext, nullptr);
    if (hostContext->HasForegroundColor()) {
        dragContext->UpdateForegroundColor(hostContext->GetForegroundColor().value());
    }
    if (hostContext->HasForegroundColorStrategy()) {
        dragContext->UpdateForegroundColorStrategy(hostContext->GetForegroundColorStrategy().value());
    }
    auto dragPattern = dragNode->GetPattern<RichEditorDragPattern>();
    CHECK_NULL_RETURN(dragPattern, nullptr);
    auto hub = dragNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto data = CalculateTextDragData(hostPattern, dragNode);
    dragPattern->Initialize(data);
    dragPattern->SetLastLineHeight(data.lastLineHeight_);
    float frameWidth = dragPattern->GetFrameWidth();
    float frameHeight = dragPattern->GetFrameHeight();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "CreateDragNode width=%{public}f, height=%{public}f", frameWidth, frameHeight);
    CalcSize size(NG::CalcLength(dragPattern->GetFrameWidth()), NG::CalcLength(dragPattern->GetFrameHeight()));
    dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(size);
    dragPattern->SetDragNodeScale(dragContext, hostNode);
    return dragNode;
}

OffsetF RichEditorDragPattern::ConvertToGlobalOffset(const OffsetF& localOffset, const OffsetF& parentGlobalOffset)
{
    auto globalOffset = localOffset + parentGlobalOffset;
    auto textPattern = DynamicCast<TextPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textPattern, globalOffset);
    return textPattern->ConvertToGlobalOffsetWithTransform(localOffset);
}

void RichEditorDragPattern::SetDragNodeScale(
    const RefPtr<RenderContext>& dragContext, const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_VOID(dragContext);
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(TextBase::HasRenderTransform(hostNode));
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    auto textPattern = DynamicCast<TextPattern>(hostPattern);
    CHECK_NULL_VOID(textPattern);
    auto scale = textPattern->GetHostScale(hostNode);
    dragContext->UpdateTransformCenter(DimensionOffset(Offset(0.0, 0.0)));
    dragContext->SetScale(scale.x, scale.y);
    CHECK_NULL_VOID(info_);
    info_->scaleXY = { scale.x, scale.y };
}

void RichEditorDragPattern::AdjustMaxWidth(float& width, const RectF& contentRect, const std::vector<RectF>& boxes)
{
    auto richEditor = DynamicCast<RichEditorPattern>(hostPattern_.Upgrade());
    if (!richEditor) {
        TextDragPattern::AdjustMaxWidth(width, contentRect, boxes);
        return;
    }
    width = NearZero(info_->maxSelectedWidth) ? contentRect.Width() : info_->maxSelectedWidth;
    CHECK_NULL_VOID(richEditor->GetHorizontalScrolling());
    width = std::min(width, contentRect.Width());
}

TextDragData RichEditorDragPattern::CreateTextDragData(const RectF& textRect, const OffsetF& localDragOffset,
    const OffsetF& globalDragOffset, const RectF& leftHandler, const RectF& rightHandler)
{
    auto data = TextDragPattern::CreateTextDragData(textRect, localDragOffset, globalDragOffset, leftHandler,
        rightHandler);
    auto richEditor = DynamicCast<RichEditorPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(richEditor && richEditor->GetHorizontalScrolling(), data);
    auto contentRect = richEditor->GetTextContentRect();
    data.contentLeft_ = contentRect.Left() - localDragOffset.GetX();
    return data;
}

void RichEditorDragPattern::AdjustHandlers(const RectF& contentRect, RectF& leftHandler, RectF& rightHandler)
{
    auto richEditor = DynamicCast<RichEditorPattern>(hostPattern_.Upgrade());
    bool isHorizontalScrolling = richEditor && richEditor->GetHorizontalScrolling();
    CHECK_NULL_VOID(leftHandler.GetY() == rightHandler.GetY() || isHorizontalScrolling);
    leftHandler.SetLeft(std::clamp(leftHandler.GetX(), contentRect.Left(), contentRect.Right()));
    rightHandler.SetLeft(std::clamp(rightHandler.GetX(), contentRect.Left(), contentRect.Right()));
}

RefPtr<FrameNode> RichEditorDragPattern::CreateDragNode(
    const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren)
{
    TextDragInfo info;
    return RichEditorDragPattern::CreateDragNode(hostNode, imageChildren, info);
}

RefPtr<FrameNode> RichEditorDragPattern::CreateDragNode(
    const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren, const TextDragInfo& info)
{
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    CHECK_NULL_RETURN(hostPattern, nullptr);
    auto dragNode = CreateDragNode(hostNode, info);
    CHECK_NULL_RETURN(dragNode, nullptr);
    auto dragPattern = dragNode->GetPattern<RichEditorDragPattern>();
    CHECK_NULL_RETURN(dragPattern, nullptr);
    auto textPattern = hostNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, nullptr);
    auto placeholderIndex = textPattern->GetPlaceHolderIndex();
    CHECK_NULL_RETURN(imageChildren.size() <= placeholderIndex.size(), nullptr);
    auto rectsForPlaceholders = textPattern->GetRectsForPlaceholders();

    size_t index = 0;
    std::vector<RectF> realRectsForPlaceholders;
    std::list<RefPtr<FrameNode>> realImageChildren;
    auto boxes = hostPattern->GetTextBoxes();
    for (const auto& child : imageChildren) {
        auto imageIndex = placeholderIndex[index];
        if (imageIndex >= static_cast<int32_t>(rectsForPlaceholders.size())) {
            break;
        }
        auto rect = rectsForPlaceholders.at(imageIndex);

        for (const auto& box : boxes) {
            if (box.IsInRegion({rect.GetX() + rect.Width() / 2, rect.GetY() + rect.Height() / 2})) {
                auto gestureHub = child->GetOrCreateGestureEventHub();
                if (gestureHub) {
                    gestureHub->SetPixelMap(nullptr);
                }
                realImageChildren.emplace_back(child);
                realRectsForPlaceholders.emplace_back(rect);
            }
        }
        ++index;
    }
    dragPattern->InitSpanImageLayout(realImageChildren, realRectsForPlaceholders);
    return dragNode;
}
} // namespace OHOS::Ace::NG
