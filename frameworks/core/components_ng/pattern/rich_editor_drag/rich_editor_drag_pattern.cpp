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
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> RichEditorDragPattern::CreateDragNode(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    const auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dragNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_DRAG_ETS_TAG, nodeId, [hostPattern]() {
        return MakeRefPtr<RichEditorDragPattern>(DynamicCast<RichEditorPattern>(hostPattern));
    });
    auto dragContext = dragNode->GetRenderContext();
    auto hostContext = hostNode->GetRenderContext();
    if (hostContext->HasForegroundColor()) {
        dragContext->UpdateForegroundColor(hostContext->GetForegroundColor().value());
    }
    if (hostContext->HasForegroundColorStrategy()) {
        dragContext->UpdateForegroundColorStrategy(hostContext->GetForegroundColorStrategy().value());
    }
    auto dragPattern = dragNode->GetPattern<RichEditorDragPattern>();
    auto data = CalculateTextDragData(hostPattern, dragNode);
    dragPattern->Initialize(data);
    dragPattern->SetLastLineHeight(data.lineHeight_);

    CalcSize size(NG::CalcLength(dragPattern->GetFrameWidth()), NG::CalcLength(dragPattern->GetFrameHeight()));
    dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(size);
    return dragNode;
}

RefPtr<FrameNode> RichEditorDragPattern::CreateDragNode(
    const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren)
{
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    auto dragNode = CreateDragNode(hostNode);
    auto dragPattern = dragNode->GetPattern<RichEditorDragPattern>();
    auto richEditor = hostNode->GetPattern<RichEditorPattern>();
    auto placeHolderIndex = richEditor->GetPlaceHolderIndex();
    auto rectsForPlaceholders = richEditor->GetRectsForPlaceholders();

    size_t index = 0;
    std::vector<RectF> realRectsForPlaceholders;
    std::list<RefPtr<FrameNode>> realImageChildren;
    auto boxes = hostPattern->GetTextBoxes();
    for (const auto& child : imageChildren) {
        auto imageIndex = placeHolderIndex[index];
        auto rect = rectsForPlaceholders.at(imageIndex);

        for (const auto& box : boxes) {
            if (LessOrEqual(box.Left(), rect.Left()) && GreatOrEqual(box.Right(), rect.Right()) &&
                LessOrEqual(box.Top(), rect.Top()) && GreatOrEqual(box.Bottom(), rect.Bottom())) {
                realImageChildren.emplace_back(child);
                realRectsForPlaceholders.emplace_back(rect);
            }
        }
        ++index;
    }
    dragPattern->SetLastLineHeight(boxes.back().Height());
    dragPattern->InitSpanImageLayout(realImageChildren, realRectsForPlaceholders);
    return dragNode;
}
} // namespace OHOS::Ace::NG
