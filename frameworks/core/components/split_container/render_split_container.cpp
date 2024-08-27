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

#include "core/components/split_container/render_split_container.h"

#include "core/components/display/render_display.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t DISABLE_HIDE = -1;

} // namespace

void RenderSplitContainer::Update(const RefPtr<Component>& component)
{
    ResetComponentMember();
    UpdateComponentAttr(component);
    InitializeRecognizer();
    MarkNeedLayout();
}

void RenderSplitContainer::ResetComponentMember()
{
    dragDetector_.Reset();
    resizable_ = false;
    layoutWidth_ = 0.0;
    layoutHeight_ = 0.0;
}

void RenderSplitContainer::UpdateComponentAttr(const RefPtr<Component>& component)
{
    auto splitComponent = AceType::DynamicCast<SplitContainerComponent>(component);
    resizable_ = splitComponent->GetResizable();
    splitType_ = splitComponent->GetSplitType();
}

void RenderSplitContainer::InitProperties()
{
    magicNodes_.clear();
    displayNodes_.clear();
    disableHideNodes_.clear();
    for (const auto& child : GetChildren()) {
        MagicLayoutNode node;
        node.node = child;
        auto displayIndexSetted = child->GetDisplayIndexSetted();
        auto idx = displayIndexSetted ? child->GetDisplayIndex() : DISABLE_HIDE;
        if (idx == DISABLE_HIDE) {
            disableHideNodes_.insert(child);
            continue;
        }

        if (magicNodes_.find(idx) != magicNodes_.end()) {
            magicNodes_[idx].emplace_back(node);
        } else {
            std::list<MagicLayoutNode> nodes;
            nodes.emplace_back(node);
            magicNodes_[idx] = nodes;
        }
    }
}

double RenderSplitContainer::GetMainSize(const RefPtr<RenderNode>& renderNode) const
{
    auto layoutSize = renderNode->GetLayoutSize();
    if (splitType_ == SplitType::ROW_SPLIT) {
        return layoutSize.Width();
    } else {
        return layoutSize.Height();
    }
}

double RenderSplitContainer::GetMainMinSize(const RefPtr<RenderNode>& renderNode) const
{
    Size minSize;
    auto flexItem = AceType::DynamicCast<RenderFlexItem>(renderNode);
    if (flexItem) {
        minSize = flexItem->GetNormalizedConstraints().GetMinSize();
    }

    if (splitType_ == SplitType::ROW_SPLIT) {
        return minSize.Width();
    } else {
        return minSize.Height();
    }
}

void RenderSplitContainer::UpdateDisplayNode()
{
    auto maxSize = GetLayoutParam().GetMaxSize();
    double allocatedSize = 0.0;
    double totalMainSize = 0.0;
    for (const auto& node : disableHideNodes_) {
        auto layoutSize = node->GetLayoutSize();
        totalMainSize += splitType_ == SplitType::ROW_SPLIT ? layoutSize.Width() : layoutSize.Height();
    }

    auto maxMainSize = splitType_ == SplitType::ROW_SPLIT ? maxSize.Width() : maxSize.Height();
    maxMainSize -= totalMainSize;
    for (auto iter = magicNodes_.rbegin(); iter != magicNodes_.rend();) {
        auto nodeList = (*iter).second;
        for (const auto& node : nodeList) {
            auto child = node.node;
            allocatedSize += GetMainSize(child);
            allocatedSize += DEFAULT_SPLIT_HEIGHT;
        }

        if ((allocatedSize - DEFAULT_SPLIT_HEIGHT) > maxMainSize) {
            for (const auto& node : nodeList) {
                auto child = node.node;
                allocatedSize -= GetMainSize(child);
                allocatedSize -= DEFAULT_SPLIT_HEIGHT;
            }
            break;
        }
        for (const auto& node : nodeList) {
            auto child = node.node;
            if (child->GetLayoutSize().IsValid()) {
                displayNodes_.insert(child);
            }
        }
        if (NearEqual(allocatedSize, maxMainSize)) {
            break;
        }
        iter++;
    }
}

void RenderSplitContainer::PerformLayout()
{
    InitProperties();
    layoutHeight_ = 0.0;
    layoutWidth_ = 0.0;
    for (const auto& item : GetChildren()) {
        item->Layout(GetLayoutParam());
    }

    UpdateDisplayNode();
    Size maxSize = GetLayoutParam().GetMaxSize();
    splitRects_.clear();
    if (dragSplitOffset_.size() == 0) {
        dragSplitOffset_ = std::vector<double>(GetChildren().size(), 0.0);
    }
    layoutHeight_ = splitType_ == SplitType::ROW_SPLIT ? maxSize.Height() : 0.0;
    layoutWidth_ = splitType_ == SplitType::ROW_SPLIT ? 0.0 : maxSize.Width();
    LayoutChildren();

    if (!displayNodes_.empty() || !disableHideNodes_.empty()) {
        if (splitType_ == SplitType::ROW_SPLIT) {
            layoutWidth_ -= DEFAULT_SPLIT_HEIGHT;
        } else {
            layoutHeight_ -= DEFAULT_SPLIT_HEIGHT;
        }
    }

    double maxHeight = GetLayoutParam().GetMaxSize().Height();
    double maxWidth = GetLayoutParam().GetMaxSize().Width();
    layoutHeight_ = LessNotEqual(layoutHeight_, maxHeight) ? layoutHeight_ : maxHeight;
    layoutWidth_ = LessNotEqual(layoutWidth_, maxWidth) ? layoutWidth_ : maxWidth;
    SetLayoutSize(Size { layoutWidth_, layoutHeight_ });
}

void RenderSplitContainer::LayoutChildren()
{
    Size maxSize = GetLayoutParam().GetMaxSize();
    size_t index = 0;
    double childOffsetMain = 0.0;
    for (const auto& item : GetChildren()) {
        auto renderDisplay = FindChildOfClass<RenderDisplay>(item);
        if (displayNodes_.find(item) == displayNodes_.end() &&
            disableHideNodes_.find(item) == disableHideNodes_.end()) {
            if (renderDisplay) {
                renderDisplay->UpdateVisibleType(VisibleType::INVISIBLE);
            }

            item->Layout(LayoutParam(Size(), Size()));
            index++;
            continue;
        }

        if (renderDisplay) {
            renderDisplay->UpdateVisibleType(VisibleType::VISIBLE);
        }
        Offset offset;
        if (splitType_ == SplitType::ROW_SPLIT) {
            offset = Offset(childOffsetMain, 0);
            layoutWidth_ += GetMainSize(item);
            layoutWidth_ += DEFAULT_SPLIT_HEIGHT;
        } else {
            offset = Offset(0, childOffsetMain);
            layoutHeight_ += GetMainSize(item);
            layoutHeight_ += DEFAULT_SPLIT_HEIGHT;
        }
        item->SetPosition(offset);
        childOffsetMain += GetMainSize(item);
        if (dragSplitOffset_[index] > 0.0) {
            childOffsetMain += dragSplitOffset_[index];
        }
        double posMain = childOffsetMain;
        if (splitType_ == SplitType::ROW_SPLIT) {
            splitRects_.push_back(Rect(posMain, 0, DEFAULT_SPLIT_HEIGHT, maxSize.Height()));
        } else {
            splitRects_.push_back(Rect(0, posMain, maxSize.Width(), DEFAULT_SPLIT_HEIGHT));
        }

        childOffsetMain += DEFAULT_SPLIT_HEIGHT;

        index++;
    }
    if (splitType_ == SplitType::ROW_SPLIT) {
        layoutWidth_ = childOffsetMain > maxSize.Width() ? maxSize.Width() : childOffsetMain;
    } else {
        layoutHeight_ = childOffsetMain > maxSize.Height() ? maxSize.Height() : childOffsetMain;
    }
}

void RenderSplitContainer::InitializeRecognizer()
{
    if (!resizable_) {
        return;
    }
    if (!dragDetector_) {
        dragDetector_ = AceType::MakeRefPtr<VerticalDragRecognizer>();
        dragDetector_->SetOnDragStart([weak = WeakClaim(this)](const DragStartInfo& startInfo) {
            auto splitContainer = weak.Upgrade();
            if (splitContainer) {
                splitContainer->HandleDragStart(startInfo.GetLocalLocation());
            }
        });
        dragDetector_->SetOnDragUpdate([weakDrag = AceType::WeakClaim(this)](const DragUpdateInfo& info) {
            auto splitContainer = weakDrag.Upgrade();
            if (splitContainer) {
                splitContainer->HandleDragUpdate(info.GetLocalLocation());
            }
        });
        dragDetector_->SetOnDragEnd([weakDrag = AceType::WeakClaim(this)](const DragEndInfo& info) {
            auto splitContainer = weakDrag.Upgrade();
            if (splitContainer) {
                splitContainer->HandleDragEnd(info.GetLocalLocation(), info.GetMainVelocity());
            }
        });
    }
}

void RenderSplitContainer::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (dragDetector_) {
        dragDetector_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDetector_);
    }
}

bool RenderSplitContainer::HandleMouseEvent(const MouseEvent& event)
{
    if (isDragedMoving_) {
        return false;
    }
    MouseInfo info;
    info.SetButton(event.button);
    info.SetAction(event.action);
    info.SetGlobalLocation(event.GetOffset());
    info.SetLocalLocation(event.GetOffset() - Offset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY()));
    info.SetScreenLocation(event.GetScreenOffset());
    info.SetTimeStamp(event.time);
    if (splitType_ == SplitType::ROW_SPLIT) {
        for (int32_t i = 0; i < static_cast<int32_t>(splitRects_.size()) - 1; i++) {
            auto lowBound = splitRects_[i].GetOffset().GetX();
            auto upBound = splitRects_[i].GetOffset().GetX() + DEFAULT_SPLIT_HEIGHT;
            if (info.GetLocalLocation().GetX() >= lowBound && info.GetLocalLocation().GetX() <= upBound) {
                isDraged_ = true;
                break;
            } else {
                isDraged_ = false;
            }
        }
        if (preIsDraged_ != isDraged_) {
            preIsDraged_ = isDraged_;
            auto mouseStyle = MouseStyle::CreateMouseStyle();
            auto context = GetContext().Upgrade();
            auto windowId = context->GetWindowId();
            if (isDraged_) {
                MouseFormat leftRightStyle = MouseFormat::WEST_EAST;
                mouseStyle->SetPointerStyle(windowId, leftRightStyle);
            } else {
                MouseFormat defaultStyle = MouseFormat::DEFAULT;
                mouseStyle->SetPointerStyle(windowId, defaultStyle);
            }
        }
    } else {
        for (int32_t i = 0; i < static_cast<int32_t>(splitRects_.size()) - 1; i++) {
            auto lowBound = splitRects_[i].GetOffset().GetY();
            auto upBound = splitRects_[i].GetOffset().GetY() + DEFAULT_SPLIT_HEIGHT;
            if (info.GetLocalLocation().GetY() >= lowBound && info.GetLocalLocation().GetY() <= upBound) {
                isDraged_ = true;
                break;
            } else {
                isDraged_ = false;
            }
        }
        if (preIsDraged_ != isDraged_) {
            preIsDraged_ = isDraged_;
            auto mouseStyle = MouseStyle::CreateMouseStyle();
            auto context = GetContext().Upgrade();
            auto windowId = context->GetWindowId();
            if (isDraged_) {
                MouseFormat upDownStyle = MouseFormat::NORTH_SOUTH;
                mouseStyle->SetPointerStyle(windowId, upDownStyle);
            } else {
                MouseFormat defaultStyle = MouseFormat::DEFAULT;
                mouseStyle->SetPointerStyle(windowId, defaultStyle);
            }
        }
    }
    return true;
}

void RenderSplitContainer::HandleMouseHoverEvent(MouseState mouseState) {}

} // namespace OHOS::Ace