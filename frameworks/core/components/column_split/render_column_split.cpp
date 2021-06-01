/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/column_split/render_column_split.h"

#include "core/components/column_split/flutter_render_column_split.h"
#include "core/components/flex/render_flex.h"
#include "core/pipeline/base/position_layout_utils.h"

namespace OHOS::Ace {

namespace {

constexpr double DEFAULT_SPLIT_RESPOND_WIDTH = 25.0;
constexpr size_t DEFAULT_DRAG_INDEX = -1;

} // namespace

RefPtr<RenderNode> RenderColumnSplit::Create()
{
    return AceType::MakeRefPtr<FlutterRenderColumnSplit>();
}

void RenderColumnSplit::Update(const RefPtr<Component>& component)
{
    InitializeRecognizer();
    MarkNeedLayout();
}

void RenderColumnSplit::PerformLayout()
{
    LayoutChildren();
    SetLayoutSize(GetLayoutParam().GetMaxSize());
}

void RenderColumnSplit::LayoutChildren()
{
    splitRects_.clear();
    if (dragSplitOffset_.size() == 0) {
        dragSplitOffset_ = std::vector<double>(GetChildren().size(), 0.0);
    }
    Size maxSize = GetLayoutParam().GetMaxSize();
    size_t index = 0;
    double childOffsetY = 0.0;
    for (const auto& item : GetChildren()) {
        Offset offset = Offset(0, childOffsetY);
        item->SetPosition(offset);
        item->Layout(GetLayoutParam());
        childOffsetY += item->GetPaintRect().Height();
        if (dragSplitOffset_[index] > 0) {
            childOffsetY += dragSplitOffset_[index];
        }
        double posY = childOffsetY > DEFAULT_SPLIT_RESPOND_WIDTH ? (childOffsetY - DEFAULT_SPLIT_RESPOND_WIDTH) : 0.0;
        splitRects_.push_back(Rect(0, posY, maxSize.Width(), 2 * DEFAULT_SPLIT_RESPOND_WIDTH + DEFAULT_SPLIT_HEIGHT));
        childOffsetY += DEFAULT_SPLIT_HEIGHT;
        index++;
    }
}

void RenderColumnSplit::InitializeRecognizer()
{
    if (!dragDetector_) {
        dragDetector_ = AceType::MakeRefPtr<VerticalDragRecognizer>();
        dragDetector_->SetOnDragStart([weak = WeakClaim(this)](const DragStartInfo& startInfo) {
            auto columnSplit = weak.Upgrade();
            if (columnSplit) {
                columnSplit->HandleDragStart(startInfo.GetLocalLocation());
            }
        });
        dragDetector_->SetOnDragUpdate([weakDrag = AceType::WeakClaim(this)](const DragUpdateInfo& info) {
            auto columnSplit = weakDrag.Upgrade();
            if (columnSplit) {
                columnSplit->HandleDragUpdate(info.GetLocalLocation());
            }
        });
        dragDetector_->SetOnDragEnd([weakDrag = AceType::WeakClaim(this)](const DragEndInfo& info) {
            auto columnSplit = weakDrag.Upgrade();
            if (columnSplit) {
                columnSplit->HandleDragEnd(info.GetLocalLocation(), info.GetMainVelocity());
            }
        });
    }
}

void RenderColumnSplit::HandleDragStart(const Offset& startPoint)
{
    dragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(startPoint.GetX(), startPoint.GetY()))) {
            dragedSplitIndex_ = i;
            LOGD("dragedSplitIndex_ = %lu", dragedSplitIndex_);
            break;
        }
    }
    startY_ = startPoint.GetY();
}

void RenderColumnSplit::HandleDragUpdate(const Offset& currentPoint)
{
    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
        return;
    }
    dragSplitOffset_[dragedSplitIndex_] += currentPoint.GetY() - startY_;
    startY_ = currentPoint.GetY();
    MarkNeedLayout();
}

void RenderColumnSplit::HandleDragEnd(const Offset& endPoint, double velocity)
{
    startY_ = 0.0;
}

bool RenderColumnSplit::TouchTest(const Point& globalPoint, const Point& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    return RenderNode::TouchTest(globalPoint, parentLocalPoint, touchRestrict, result);
}

void RenderColumnSplit::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (dragDetector_) {
        dragDetector_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDetector_);
    }
}

} // namespace OHOS::Ace