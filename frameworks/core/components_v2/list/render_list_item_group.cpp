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

#include "core/components_v2/list/render_list_item_group.h"

namespace OHOS::Ace::V2 {

void RenderListItemGroup::RemoveAllItems()
{
    items_.clear();
    ClearChildren();
}

LayoutParam RenderListItemGroup::MakeInnerLayout()
{
    Size maxSize;
    Size minSize;
    if (vertical_) {
        auto maxCrossSize = GetLayoutParam().GetMaxSize().Width();
        if (Positive(maxLaneLength_)) {
            maxSize = Size(std::min(maxCrossSize / lanes_, maxLaneLength_), Size::INFINITE_SIZE);
        } else {
            maxSize = Size(maxCrossSize / lanes_, Size::INFINITE_SIZE);
        }
        minSize = Size(GetLayoutParam().GetMinSize().Width(), 0.0);
    } else {
        auto maxCrossSize = GetLayoutParam().GetMaxSize().Height();
        if (Positive(maxLaneLength_)) {
            maxSize = Size(Size::INFINITE_SIZE, std::min(maxCrossSize / lanes_, maxLaneLength_));
        } else {
            maxSize = Size(Size::INFINITE_SIZE, maxCrossSize / lanes_);
        }
        minSize = Size(0.0, GetLayoutParam().GetMinSize().Height());
    }
    return { maxSize, minSize };
}

RefPtr<RenderListItem> RenderListItemGroup::RequestListItem(size_t index, bool atStart)
{
    auto generator = itemGenerator_.Upgrade();
    auto newItem = generator ? generator->RequestListItem(index) : RefPtr<RenderListItem>();
    if (!newItem) {
        return newItem;
    }

    if (!newItem->GetVisible()) {
        newItem->SetVisible(true);
    }

    const auto innerLayout = MakeInnerLayout();
    AddChild(newItem);
    newItem->Layout(innerLayout);

    if (atStart) {
        items_.emplace_front(newItem);
    } else {
        items_.emplace_back(newItem);
    }
    return newItem;
}

void RenderListItemGroup::RecycleListItem(size_t index)
{
    auto generator = itemGenerator_.Upgrade();
    if (generator) {
        generator->RecycleListItem(index);
    }
}

RefPtr<RenderNode> RenderListItemGroup::RequestListItemHeader()
{
    auto generator = itemGenerator_.Upgrade();
    header_ =  generator ? generator->RequestListItemHeader() : RefPtr<RenderNode>();
    if (header_) {
        AddChild(header_);
    }
    return header_;
}

RefPtr<RenderNode> RenderListItemGroup::RequestListItemFooter()
{
    auto generator = itemGenerator_.Upgrade();
    footer_ = generator ? generator->RequestListItemFooter() : RefPtr<RenderNode>();
    if (footer_) {
        AddChild(footer_);
    }
    return footer_;
}

size_t RenderListItemGroup::TotalCount()
{
    auto generator = itemGenerator_.Upgrade();
    return generator ? generator->TotalCount() : 0;
}

void RenderListItemGroup::Update(const RefPtr<Component>& component)
{
    LOGI("RenderListItemGroup::Update");
    component_ = AceType::DynamicCast<ListItemGroupComponent>(component);
    if (!component_) {
        return;
    }
    const auto& divider = component_->GetItemDivider();
    listSpace_ = component_->GetSpace();
    spaceWidth_ = std::max(NormalizePercentToPx(component_->GetSpace(), vertical_),
        divider ? NormalizePercentToPx(divider->strokeWidth, vertical_) : 0.0);
    RemoveAllItems();
    MarkNeedLayout();
}

void RenderListItemGroup::RecycleStartCacheItems()
{
    double curMainPosForRecycle = startIndexOffset_;
    size_t curIndex = startIndex_;
    size_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (auto it = items_.begin(); it != items_.end() && currStartCacheCount_ > startCacheCount_; curIndex += lanes_) {
        double rowSize = 0;
        for (size_t i = 0; i < lanes && it != items_.end(); i++) {
            const auto& child = *(it);
            double childSize = GetMainSize(child->GetLayoutSize());
            rowSize = std::max(childSize, rowSize);
            // Recycle list items out of view port
            RecycleListItem(curIndex + i);
            it = items_.erase(it);
        }
        curMainPosForRecycle += rowSize + spaceWidth_;
        startIndexOffset_ = curMainPosForRecycle;
        startIndex_ = curIndex + lanes;
        currStartCacheCount_--;
    }
}

double RenderListItemGroup::LayoutALine(std::list<RefPtr<RenderListItem>>::iterator& it)
{
    double rowSize = 0;
    for (size_t i = 0; i < lanes_; i++) {
        RefPtr<RenderListItem> child;
        if (it == items_.end()) {
            if (i == 0) {
                break;
            }
            child = RequestListItem(startIndex_ + items_.size(), false);
            if (!child) {
                break;
            }
            it = items_.end();
        } else {
            child = *(it++);
        }
        child->Layout(MakeInnerLayout());
        double childSize = GetMainSize(child->GetLayoutSize());
        rowSize = std::max(childSize, rowSize);
    }
    return rowSize;
}

double RenderListItemGroup::LayoutOrRecycleCurrentItems()
{
    double curMainPos = startIndexOffset_;
    size_t curIndex = startIndex_;
    currStartCacheCount_ = 0;
    currEndCacheCount_ = 0;

    size_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (auto it = items_.begin(); it != items_.end(); curIndex += lanes_) {
        if (GreatNotEqual(curMainPos, endMainPos_) && currEndCacheCount_ >= endCacheCount_) {
            for (size_t i = 0; i < lanes && it != items_.end(); i++) {
                // Recycle list items out of view port
                RecycleListItem(curIndex + i);
                it = items_.erase(it);
            }
            continue;
        }
        if (GreatNotEqual(curMainPos, endMainPos_)) {
            currEndCacheCount_++;
        }
        double rowSize = LayoutALine(it);
        curMainPos += rowSize + spaceWidth_;
        if (LessNotEqual(curMainPos, startMainPos_)) {
            currStartCacheCount_++;
        }
    }
    RecycleStartCacheItems();
    return curMainPos;
}

void RenderListItemGroup::RequestNewItemsAtEnd(double& curMainPos)
{
    size_t lanes = lanes_ > 1 ? lanes_ : 1;
    size_t newIndex = startIndex_ + items_.size();
    while (true) {
        if (GreatOrEqual(curMainPos, endMainPos_) && currEndCacheCount_ >= endCacheCount_) {
            break;
        }
        double rowSize = 0;
        size_t idx = 0;
        for (; idx < lanes; idx++) {
            auto child = RequestListItem(newIndex + idx, false);
            if (!child) {
                break;
            }
            double childSize = GetMainSize(child->GetLayoutSize());
            rowSize = std::max(childSize, rowSize);
        }
        if (idx == 0) {
            break;
        }
        if (GreatOrEqual(curMainPos, endMainPos_)) {
            currEndCacheCount_++;
        }
        curMainPos += rowSize + spaceWidth_;
        newIndex += idx;
        if (idx < lanes) {
            break;
        }
    }
    if (startIndex_ + items_.size() >= TotalCount() && !items_.empty()) {
        curMainPos -= spaceWidth_;
    }
}

void RenderListItemGroup::RequestNewItemsAtStart()
{
    while (true) {
        if (LessOrEqual(startIndexOffset_, startMainPos_) && currStartCacheCount_ >= startCacheCount_) {
            break;
        }
        double rowSize = 0;
        size_t count = lanes_;
        if (startIndex_ >= TotalCount()) {
            count = startIndex_ % lanes_;
            if (count == 0) {
                count = lanes_;
            }
        }
        size_t idx = 0;
        for (; idx < count && startIndex_ - idx > 0; idx++) {
            auto child = RequestListItem(startIndex_ - idx - 1, true);
            if (!child) {
                break;
            }
            double childSize = GetMainSize(child->GetLayoutSize());
            rowSize = std::max(childSize, rowSize);
        }
        if (idx == 0) {
            break;
        }
        if (LessOrEqual(startIndexOffset_, startMainPos_)) {
            currStartCacheCount_++;
        }
        if (startIndex_ >= TotalCount()) {
            startIndexOffset_ -= rowSize;
        } else {
            startIndexOffset_ -= rowSize + spaceWidth_;
        }
        startIndex_ -= idx;
        if (idx < lanes_) {
            break;
        }
    }
}

void RenderListItemGroup::LayoutHeaderFooter(bool reachEnd)
{
    if ((stickyHeader_ || startIndex_ == 0) && !header_) {
        RequestListItemHeader();
    } else if (!stickyHeader_ && startIndex_ > 0 && header_) {
        RemoveChild(header_);
        header_ = nullptr;
    }

    if ((stickyFooter_ || reachEnd) && !footer_) {
        RequestListItemFooter();
    } else if (!stickyFooter_ && !reachEnd && footer_) {
        RemoveChild(footer_);
        footer_ = nullptr;
    }

    if (header_) {
        header_->Layout(GetLayoutParam());
    }

    if (footer_) {
        footer_->Layout(GetLayoutParam());
    }
}

double RenderListItemGroup::CalculateCrossOffset(double crossSize, double childCrossSize)
{
    double delta = crossSize - childCrossSize;
    switch (align_) {
        case ListItemAlign::START:
            return 0.0;
        case ListItemAlign::CENTER:
            return delta / 2; /* 2 average */
        case ListItemAlign::END:
            return delta;
        default:
            LOGW("Invalid ListItemAlign: %{public}d", align_);
            return 0.0;
    }
}

void RenderListItemGroup::SetItemsPostion()
{
    double crossSize = GetCrossSize(GetLayoutParam().GetMaxSize());
    double layoutPos = forwardLayout_ ? (startIndexOffset_ - forwardReferencePos_) : 0.0;
    if (header_) {
        double crossOffset = CalculateCrossOffset(crossSize, GetCrossSize(header_->GetLayoutSize()));
        double headerSize = GetMainSize(header_->GetLayoutSize());
        if (stickyHeader_ && Negative(forwardReferencePos_)) {
            double headerPos = backwardReferencePos_ - headerSize;
            if (footer_) {
                headerPos -= GetMainSize(footer_->GetLayoutSize());
            }
            headerPos = std::min(0.0, headerPos);
            header_->SetPosition(MakeValue<Offset>(headerPos - forwardReferencePos_, crossOffset));
        } else {
            auto offset = MakeValue<Offset>(layoutPos - headerSize, crossOffset);
            header_->SetPosition(offset);
        }
    }
    double laneCrossSize = GetCrossSize(GetLayoutSize()) / lanes_;
    for (auto it = items_.begin(); it != items_.end();) {
        double rowSize = 0;
        for (size_t i = 0; i < lanes_ && it != items_.end(); i++) {
            auto child = *(it++);
            double childSize = GetMainSize(child->GetLayoutSize());
            rowSize = std::max(childSize, rowSize);
            double crossOffset = CalculateCrossOffset(laneCrossSize, GetCrossSize(child->GetLayoutSize()));
            auto offset = MakeValue<Offset>(layoutPos, i * laneCrossSize + crossOffset);
            child->SetPosition(offset);
        }
        layoutPos += (rowSize + spaceWidth_);
    }
    if (!items_.empty()) {
        layoutPos -= spaceWidth_;
    }
    endIndexOffset_ = layoutPos;
    if (footer_) {
        double crossOffset = CalculateCrossOffset(crossSize, GetCrossSize(footer_->GetLayoutSize()));
        if (stickyFooter_ && GreatNotEqual(backwardReferencePos_, listMainSize_)) {
            double footerSize = GetMainSize(footer_->GetLayoutSize());
            double footerPos = forwardReferencePos_;
            if (header_) {
                footerPos += GetMainSize(header_->GetLayoutSize());
            }
            footerPos = std::max(footerPos, listMainSize_ - footerSize);
            footer_->SetPosition(MakeValue<Offset>(footerPos - forwardReferencePos_, crossOffset));
        } else {
            auto offset = MakeValue<Offset>(layoutPos, crossOffset);
            footer_->SetPosition(offset);
        }
    }
}

void RenderListItemGroup::PerformLayout()
{
    double curMainPos = LayoutOrRecycleCurrentItems();
    RequestNewItemsAtEnd(curMainPos);
    RequestNewItemsAtStart();

    bool reachEnd = (startIndex_ + items_.size() >= TotalCount());
    LayoutHeaderFooter(reachEnd);

    double headerSize = header_ && (startIndex_ == 0) ? GetMainSize(header_->GetLayoutSize()) : 0.0;
    double footerSize = footer_ && reachEnd ? GetMainSize(footer_->GetLayoutSize()) : 0.0;
    if (forwardLayout_ && LessNotEqual(startIndexOffset_ - headerSize, forwardReferencePos_)) {
        startIndexOffset_ = forwardReferencePos_ + headerSize;
        curMainPos += headerSize;
    }
    if (!forwardLayout_ && GreatNotEqual(curMainPos + footerSize, backwardReferencePos_)) {
        startIndexOffset_ -= curMainPos + footerSize - backwardReferencePos_;
        curMainPos = backwardReferencePos_ - footerSize;
    }
    double currMainSize = forwardLayout_ ?
        (curMainPos + footerSize - forwardReferencePos_) : (backwardReferencePos_ - startIndexOffset_ + headerSize);
    const auto& layoutParam = GetLayoutParam();
    auto size = MakeValue<Size>(currMainSize, GetCrossSize(layoutParam.GetMaxSize()));
    auto layoutSize = layoutParam.Constrain(size);
    SetLayoutSize(layoutSize);
    if (forwardLayout_) {
        backwardReferencePos_ = forwardReferencePos_ + currMainSize;
    } else {
        forwardReferencePos_ = backwardReferencePos_ - currMainSize;
    }

    if (startIndex_ == 0) {
        forwardLayout_ = true;
    }

    SetItemsPostion();
}

RefPtr<RenderNode> RenderListItemGroup::GetRenderNode()
{
    auto parent = renderNode_.Upgrade();
    if (parent) {
        return parent;
    }
    return Claim(this);
}

void RenderListItemGroup::SetNeedLayoutDeep()
{
    SetNeedLayout(true);
    auto topRenderNode = renderNode_.Upgrade();
    if (topRenderNode) {
        auto parent = GetParent().Upgrade();
        while (parent != nullptr && topRenderNode != parent) {
            parent->SetNeedLayout(true);
            parent = parent->GetParent().Upgrade();
        }
        topRenderNode->SetNeedLayout(true);
    }
}

void RenderListItemGroup::SetItemGroupLayoutParam(const ListItemLayoutParam &param)
{
    startMainPos_ = param.startMainPos;
    endMainPos_ = param.endMainPos;
    startCacheCount_ = param.startCacheCount;
    endCacheCount_ = param.endCacheCount;
    listMainSize_ = param.listMainSize;
    maxLaneLength_ = param.maxLaneLength;
    vertical_ = param.isVertical;
    align_ = param.align;
    stickyHeader_ = (param.sticky == StickyStyle::HEADER) || (param.sticky == StickyStyle::BOTH);
    stickyFooter_ = (param.sticky == StickyStyle::FOOTER) || (param.sticky == StickyStyle::BOTH);
    lanes_ = static_cast<size_t>(param.lanes);
    if (!isInitialized_) {
        isInitialized_ = true;
        startIndex_ = param.forwardLayout ? 0 : TotalCount();
        startIndexOffset_ = param.referencePos;
        forwardReferencePos_ = param.referencePos;
        backwardReferencePos_ = param.referencePos;
    }
    if (param.forwardLayout) {
        startIndexOffset_ += param.referencePos - forwardReferencePos_;
        forwardReferencePos_ = param.referencePos;
    } else {
        startIndexOffset_ += param.referencePos - backwardReferencePos_;
        backwardReferencePos_ = param.referencePos;
    }
    forwardLayout_ = param.forwardLayout;
}

void RenderListItemGroup::SetChainOffset(double offset)
{
    if (NearZero(offset)) {
        return;
    }

    if (header_ && stickyHeader_) {
        double crossSize = GetCrossSize(GetLayoutParam().GetMaxSize());
        double layoutPos = forwardLayout_ ? (startIndexOffset_ - forwardReferencePos_) : spaceWidth_;
        double crossOffset = CalculateCrossOffset(crossSize, GetCrossSize(header_->GetLayoutSize()));
        double headerSize = GetMainSize(header_->GetLayoutSize());
        if (Negative(forwardReferencePos_ + offset)) {
            double headerPos = backwardReferencePos_ + offset - headerSize;
            if (footer_) {
                headerPos -= GetMainSize(footer_->GetLayoutSize());
            }
            headerPos = std::min(0.0, headerPos);
            header_->SetPosition(MakeValue<Offset>(headerPos - (forwardReferencePos_ + offset), crossOffset));
        } else {
            auto offset = MakeValue<Offset>(layoutPos - headerSize, crossOffset);
            header_->SetPosition(offset);
        }
    }
    if (footer_ && stickyFooter_) {
        double crossSize = GetCrossSize(GetLayoutParam().GetMaxSize());
        double crossOffset = CalculateCrossOffset(crossSize, GetCrossSize(footer_->GetLayoutSize()));
        if (GreatNotEqual(backwardReferencePos_ + offset, listMainSize_)) {
            double footerSize = GetMainSize(footer_->GetLayoutSize());
            double footerPos = forwardReferencePos_ + offset;
            if (header_) {
                footerPos += GetMainSize(header_->GetLayoutSize());
            }
            footerPos = std::max(footerPos, listMainSize_ - footerSize);
            footer_->SetPosition(MakeValue<Offset>(footerPos - (forwardReferencePos_ + offset), crossOffset));
        } else {
            auto offset = MakeValue<Offset>(endIndexOffset_, crossOffset);
            footer_->SetPosition(offset);
        }
    }
}

void RenderListItemGroup::Paint(RenderContext& context, const Offset& offset)
{
    for (const auto& child : GetItems()) {
        PaintChild(child, context, offset);
    }
    PaintDivider(context);
    if (header_) {
        PaintChild(header_, context, offset);
    }
    if (footer_) {
        PaintChild(footer_, context, offset);
    }
}
} // namespace OHOS::Ace::V2
