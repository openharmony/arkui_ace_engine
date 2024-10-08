/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/split_container/render_column_split.h"

namespace OHOS::Ace {

namespace {

constexpr size_t DEFAULT_DRAG_INDEX = -1;

} // namespace

void RenderColumnSplit::HandleDragStart(const Offset& startPoint)
{
    dragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    isDragedMoving_ = true;
    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(startPoint.GetX(), startPoint.GetY()))) {
            auto context = GetContext().Upgrade();
            if (context) {
                auto windowId = context->GetWindowId();
                MouseFormat upDownStyle = MouseFormat::NORTH_SOUTH;
                auto mouseStyle = MouseStyle::CreateMouseStyle();
                mouseStyle->SetPointerStyle(windowId, upDownStyle);
            }
            dragedSplitIndex_ = i;
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
    Rect dragRect(Offset(0.0, 0.0), GetPaintRect().GetSize());
    if (!dragRect.IsInRegion(Point(currentPoint.GetX(), currentPoint.GetY()))) {
        return;
    }
    dragSplitOffset_[dragedSplitIndex_] += (currentPoint.GetY() - startY_);
    dragSplitOffset_[dragedSplitIndex_] =
        dragSplitOffset_[dragedSplitIndex_] < 0.0 ? 0.0 : dragSplitOffset_[dragedSplitIndex_];
    startY_ = currentPoint.GetY();
    auto context = GetContext().Upgrade();
    if (context) {
        auto windowId = context->GetWindowId();
        MouseFormat upDownStyle = MouseFormat::NORTH_SOUTH;
        auto mouseStyle = MouseStyle::CreateMouseStyle();
        mouseStyle->SetPointerStyle(windowId, upDownStyle);
    }
    MarkNeedLayout();
}

void RenderColumnSplit::HandleDragEnd(const Offset& endPoint, double velocity)
{
    startY_ = 0.0;
    isDragedMoving_ = false;
    auto context = GetContext().Upgrade();
    if (context) {
        auto windowId = context->GetWindowId();
        MouseFormat defaultStyle = MouseFormat::DEFAULT;
        auto mouseStyle = MouseStyle::CreateMouseStyle();
        mouseStyle->SetPointerStyle(windowId, defaultStyle);
    }
}

} // namespace OHOS::Ace