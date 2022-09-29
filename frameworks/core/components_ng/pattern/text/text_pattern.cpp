/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_pattern.h"

#include <stack>

#include "base/geometry/ng/rect_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {

void TextPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureEventHub->AddLongPressEvent(longPressEvent_);
}

void TextPattern::OnDetachFromFrameNode(FrameNode* node)
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close();
    }
}

void TextPattern::HandleLongPress(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rect = host->GetGeometryNode()->GetFrameRect();
    const auto& offset = info.GetLocalLocation();
    // TODO: add text char match operation.
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), rect.Height() };
    RectF firstHandle;
    firstHandle.SetOffset({ offset.GetX(), offset.GetY() });
    firstHandle.SetSize(handlePaintSize);
    RectF secondHandle;
    secondHandle.SetOffset({ offset.GetX() + rect.Width() / 2, offset.GetY() + rect.Height() / 2 });
    secondHandle.SetSize(handlePaintSize);
    ShowSelectOverlay(firstHandle, secondHandle);
}

void TextPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    // TODO: add text select area update.
}

void TextPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    // TODO: use text area update handle position.
    CHECK_NULL_VOID(selectOverlayProxy_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rect = host->GetGeometryNode()->GetFrameRect();
    if (isFirstHandle) {
        SelectHandleInfo info;
        info.paintRect.SetOffset({ rect.Left(), rect.Top() });
        info.paintRect.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), rect.GetSize().Height() });
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(info);
        return;
    }
    SelectHandleInfo info;
    info.paintRect.SetOffset({ rect.Right(), rect.Bottom() });
    info.paintRect.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), rect.GetSize().Height() });
    selectOverlayProxy_->UpdateSecondSelectHandleInfo(info);
}

void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.paintRect = firstHandle;
    selectInfo.secondHandle.paintRect = secondHandle;
    selectInfo.onHandleMove = [weak = WeakClaim(this)](const RectF& handleRect, bool isFirst) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleMove(handleRect, isFirst);
    };
    selectInfo.onHandleMoveDone = [weak = WeakClaim(this)](const RectF& handleRect, bool isFirst) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleMoveDone(handleRect, isFirst);
    };

    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuCallback.onSelectAll = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnSelectAll();
    };

    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close();
    }
    selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo);
}

void TextPattern::HandleOnSelectAll()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto rect = host->GetGeometryNode()->GetFrameRect();
    // TODO: use text area update handle position.
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), rect.Height() };
    RectF firstHandle;
    firstHandle.SetOffset({ rect.Left(), rect.Top() });
    firstHandle.SetSize(handlePaintSize);
    RectF secondHandle;
    secondHandle.SetOffset({ rect.Right(), rect.Bottom() });
    secondHandle.SetSize(handlePaintSize);
    ShowSelectOverlay(firstHandle, secondHandle);
}

void TextPattern::OnModifyDone()
{
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    bool shouldClipToContent = textLayoutProperty->GetTextOverflow().value_or(TextOverflow::NONE) == TextOverflow::CLIP;
    host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto paragraph = textLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        LOGD("on layout process, just return");
        return false;
    }
    paragraph_ = textLayoutAlgorithm->GetParagraph();
    baselineOffset_ = textLayoutAlgorithm->GetBaselineOffset();
    return true;
}

void TextPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    auto flag = layoutProperty ? layoutProperty->GetPropertyChangeFlag() : PROPERTY_UPDATE_NORMAL;
    if (paragraph_) {
        // When updating the scenario, needs to determine whether the SpanNode node is refreshed.
        if ((flag & PROPERTY_UPDATE_BY_CHILD_REQUEST) != PROPERTY_UPDATE_BY_CHILD_REQUEST) {
            LOGD("no need to refresh span node");
            return;
        }
    }

    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        return;
    }
    spanItemChildren_.clear();

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<RefPtr<UINode>> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push(*iter);
    }
    while (!nodes.empty()) {
        auto current = nodes.top();
        nodes.pop();
        // TODO: Add the judgment of display.
        if (!current) {
            continue;
        }
        auto spanNode = DynamicCast<SpanNode>(current);
        if (spanNode) {
            spanNode->CleanSpanItemChildren();
            spanNode->MountToParagraph();
        }
        const auto& nextChildren = current->GetChildren();
        for (auto iter = nextChildren.rbegin(); iter != nextChildren.rend(); ++iter) {
            nodes.push(*iter);
        }
    }
}
} // namespace OHOS::Ace::NG
