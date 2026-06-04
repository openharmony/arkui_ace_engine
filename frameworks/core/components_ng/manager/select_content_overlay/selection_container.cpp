/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/select_content_overlay/selection_container.h"

#include <algorithm>
#include <cmath>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float POSITION_COMPARE_EPSILON = 0.5f;

bool GetChildOriginInContainer(
    const RefPtr<FrameNode>& containerNode, const RefPtr<SelectionContainerChild>& child, OffsetF& point)
{
    CHECK_NULL_RETURN(containerNode, false);
    CHECK_NULL_RETURN(child, false);
    auto childNode = child->GetHostNode();
    CHECK_NULL_RETURN(childNode, false);
    point = childNode->ConvertPoint(OffsetF(0.0f, 0.0f), containerNode);
    return true;
}

bool ShouldSwapSelectionBoundaryPoints(const OffsetF& left, const OffsetF& right)
{
    const auto yDiff = left.GetY() - right.GetY();
    if (GreatNotEqual(std::fabs(yDiff), POSITION_COMPARE_EPSILON)) {
        return GreatNotEqual(yDiff, 0.0f);
    }
    const auto xDiff = left.GetX() - right.GetX();
    return GreatNotEqual(xDiff, POSITION_COMPARE_EPSILON);
}

bool IsChildNodeMatchId(const WeakPtr<SelectionContainerChild>& weakChild, int32_t childId)
{
    auto child = weakChild.Upgrade();
    auto node = child ? child->GetHostNode() : nullptr;
    return node && node->GetId() == childId;
}

void SelectByPoints(
    const RefPtr<SelectionContainerChild>& child, const OffsetF& topPoint, const OffsetF& bottomPoint,
    int32_t fixedIndex = -1, bool topPointIsFixed = true, bool fixedHandleIsTopOnStart = true)
{
    CHECK_NULL_VOID(child);
    auto oldIndexes = child->GetSelectionIndexes();
    if (fixedIndex >= 0) {
        auto movingPoint = topPointIsFixed ? bottomPoint : topPoint;
        auto movingIndex = child->GetSelectionIndexByPoint(movingPoint);
        auto top = fixedHandleIsTopOnStart ? fixedIndex : movingIndex;
        auto bottom = fixedHandleIsTopOnStart ? movingIndex : fixedIndex;
        child->SelectTextByIndex(top, bottom);
    } else {
        auto indexes = child->GetSelectionIndexesByPoints(topPoint, bottomPoint);
        auto top = std::min(indexes.startIndex, indexes.endIndex);
        auto bottom = std::max(indexes.startIndex, indexes.endIndex);
        child->SelectTextByIndex(top, bottom);
    }
    auto newIndexes = child->GetSelectionIndexes();
    if (newIndexes.startIndex != oldIndexes.startIndex) {
        child->StartVibratorByIndexChange(newIndexes.startIndex, oldIndexes.startIndex);
    } else if (newIndexes.endIndex != oldIndexes.endIndex) {
        child->StartVibratorByIndexChange(newIndexes.endIndex, oldIndexes.endIndex);
    }
}

void HandleSelectionForChild(const RefPtr<FrameNode>& containerNode, const RefPtr<SelectionContainerChild>& child,
    const OffsetF& topPointInContainer, const OffsetF& bottomPointInContainer,
    const RefPtr<SelectionContainerChild>& fixedChild, int32_t fixedIndex, bool topPointIsFixed,
    bool fixedHandleIsTopOnStart)
{
    CHECK_NULL_VOID(containerNode);
    CHECK_NULL_VOID(child);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto geometryNode = childNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childRect = geometryNode->GetFrameRect();
    const auto width = childRect.Width();
    const auto height = childRect.Height();
    const auto topPointInChild = containerNode->ConvertPoint(topPointInContainer, childNode);
    const auto bottomPointInChild = containerNode->ConvertPoint(bottomPointInContainer, childNode);
    // Compare in child-local space to avoid affine-transform mismatch.
    if (GreatNotEqual(topPointInChild.GetY(), height) || LessNotEqual(bottomPointInChild.GetY(), 0.0f)) {
        child->SelectTextByIndex(-1, -1);
        return;
    }
    const bool topInChild = GreatOrEqual(topPointInChild.GetY(), 0.0f) && LessOrEqual(topPointInChild.GetY(), height);
    const bool bottomInChild =
        GreatOrEqual(bottomPointInChild.GetY(), 0.0f) && LessOrEqual(bottomPointInChild.GetY(), height);
    const bool useFixedIndex = child == fixedChild && fixedIndex >= 0;

    // 1. top and bottom in the same child.
    if (topInChild && bottomInChild) {
        SelectByPoints(child, topPointInChild, bottomPointInChild,
            useFixedIndex ? fixedIndex : -1, topPointIsFixed, fixedHandleIsTopOnStart);
        return;
    }

    // 2. topLocal inside child.
    if (topInChild) {
        // Process current child and same-row right-side children.
        if (LessOrEqual(topPointInChild.GetX(), width)) {
            auto topPoint = OffsetF(std::clamp(topPointInChild.GetX(), 0.0f, width), topPointInChild.GetY());
            SelectByPoints(child, topPoint, OffsetF(width, height),
                useFixedIndex && topPointIsFixed ? fixedIndex : -1, true, fixedHandleIsTopOnStart);
            return;
        }
        child->SelectTextByIndex(-1, -1);
        return;
    }

    // 3. Child fully covered by [top, bottom] in child-local Y.
    if (LessNotEqual(topPointInChild.GetY(), 0.0f) && GreatNotEqual(bottomPointInChild.GetY(), height)) {
        SelectByPoints(child, OffsetF(0.0f, 0.0f), OffsetF(width, height));
        return;
    }

    // 4. bottomLocal inside child.
    if (bottomInChild) {
        SelectByPoints(child, OffsetF(0.0f, 0.0f), bottomPointInChild,
            useFixedIndex && !topPointIsFixed ? fixedIndex : -1, false, fixedHandleIsTopOnStart);
        return;
    }
    child->SelectTextByIndex(-1, -1);
}
} // namespace

void SelectionContainer::RegisterChild(const RefPtr<SelectionContainerChild>& child)
{
    CHECK_NULL_VOID(child);
    auto& childList = registeredChildList_;
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);
    const auto childId = childNode->GetId();
    for (auto iter = childList.begin(); iter != childList.end();) {
        auto child = iter->Upgrade();
        if (!child) {
            iter = childList.erase(iter);
            continue;
        }
        auto iterChildNode = child->GetHostNode();
        if (iterChildNode && iterChildNode->GetId() == childId) {
            return;
        }
        ++iter;
    }
    childList.emplace_back(child);
    MarkChildSortDirty();
}

void SelectionContainer::UnregisterChild(int32_t childId)
{
    auto& childList = registeredChildList_;
    for (auto childIter = childList.begin(); childIter != childList.end();) {
        auto child = childIter->Upgrade();
        auto childNode = child ? child->GetHostNode() : nullptr;
        bool isExpired = !child || !childNode;
        bool isTarget = childNode && childNode->GetId() == childId;
        if (!isExpired && !isTarget) {
            ++childIter;
            continue;
        }
        if (child) {
            child->ClearSelectionContainer();
        }
        if (isTarget) {
            if (IsChildNodeMatchId(selectionStartChild_, childId)) {
                selectionStartChild_.Reset();
            }
            if (IsChildNodeMatchId(selectionEndChild_, childId)) {
                selectionEndChild_.Reset();
            }
            if (IsChildNodeMatchId(selectionFixedChild_, childId)) {
                selectionFixedChild_.Reset();
                selectionFixedIndex_ = -1;
            }
        }
        childIter = childList.erase(childIter);
    }
    MarkChildSortDirty();
}

bool SelectionContainer::HandleSelectionStart(const SelectionStartEventInfo& eventInfo)
{
    auto sourceChild = eventInfo.child.Upgrade();
    CHECK_NULL_RETURN(sourceChild, false);
    auto sourceNode = sourceChild->GetHostNode();
    CHECK_NULL_RETURN(sourceNode, false);
    auto containerNode = GetHostNode();
    CHECK_NULL_RETURN(containerNode, false);

    auto fixedPointInContainer = sourceNode->ConvertPoint(eventInfo.localPoint, containerNode);
    return HandleSelectionStart(fixedPointInContainer, sourceChild, eventInfo.startIndex, eventInfo.endIndex);
}

bool SelectionContainer::HandleSelectionStart(const OffsetF& fixedPointInContainer,
    const RefPtr<SelectionContainerChild>& startChild, int32_t startIndex, int32_t endIndex,
    bool fixedHandleIsTopOnStart)
{
    CHECK_NULL_RETURN(startChild, false);
    fixedPointInContainer_ = fixedPointInContainer;
    selectionFixedChild_ = startChild;
    selectionFixedIndex_ = startIndex >= 0 ? startIndex : endIndex;
    selectionStartIndex_ = startIndex;
    selectionEndIndex_ = endIndex;
    fixedHandleIsTopOnStart_ = fixedHandleIsTopOnStart;
    hasSelectionStartEvent_ = true;
    return true;
}

bool SelectionContainer::IsSelectionSessionOwner(const RefPtr<SelectionContainerChild>& child) const
{
    CHECK_NULL_RETURN(child, false);
    auto fixedChild = selectionFixedChild_.Upgrade();
    return fixedChild == child;
}

bool SelectionContainer::HandleSelectionUpdate(const SelectionEndEventInfo& eventInfo)
{
    auto sourceChild = eventInfo.child;
    CHECK_NULL_RETURN(sourceChild, false);
    auto sourceNode = sourceChild->GetHostNode();
    CHECK_NULL_RETURN(sourceNode, false);

    auto containerNode = GetHostNode();
    CHECK_NULL_RETURN(containerNode, false);
    auto movingPointInContainer = sourceNode->ConvertPoint(eventInfo.localPoint, containerNode);
    return HandleSelectionUpdate(movingPointInContainer);
}

bool SelectionContainer::HandleSelectionUpdate(const OffsetF& movingPointInContainer)
{
    CHECK_NULL_RETURN(hasSelectionStartEvent_, false);

    auto containerNode = GetHostNode();
    CHECK_NULL_RETURN(containerNode, false);
    auto topPointInContainer = fixedPointInContainer_;
    auto bottomPointInContainer = movingPointInContainer;
    bool topPointIsFixed = true;
    if (ShouldSwapSelectionBoundaryPoints(topPointInContainer, bottomPointInContainer)) {
        std::swap(topPointInContainer, bottomPointInContainer);
        topPointIsFixed = false;
    }

    auto childList = GetChildList();
    CHECK_NULL_RETURN(!childList.empty(), false);

    RefPtr<SelectionContainerChild> firstSelectedChild;
    RefPtr<SelectionContainerChild> lastSelectedChild;
    auto fixedChild = selectionFixedChild_.Upgrade();
    auto fixedIndex = selectionFixedIndex_;
    std::vector<std::u16string> selectedTexts;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (!child->CanSelect()) {
            child->SelectTextByIndex(-1, -1);
            continue;
        }
        HandleSelectionForChild(containerNode, child, topPointInContainer, bottomPointInContainer, fixedChild,
            fixedIndex, topPointIsFixed, fixedHandleIsTopOnStart_);
        auto childSelectionText = child->GetSelectionText();
        if (childSelectionText.empty()) {
            continue;
        }
        selectedTexts.push_back(std::move(childSelectionText));
        if (!firstSelectedChild) {
            firstSelectedChild = child;
        }
        lastSelectedChild = child;
    }
    OnSelectionRangeChanged(selectedTexts);
    selectionStartChild_ = firstSelectedChild;
    selectionEndChild_ = lastSelectedChild;
    if (firstSelectedChild) {
        firstSelectedChild->UpdateSelectionHandleInfo();
    }
    if (lastSelectedChild && lastSelectedChild != firstSelectedChild) {
        lastSelectedChild->UpdateSelectionHandleInfo();
    }
    return firstSelectedChild && lastSelectedChild;
}

bool SelectionContainer::ExtendSelectionFromFixedAnchor(const SelectionEndEventInfo& eventInfo)
{
    auto fixedChild = selectionFixedChild_.Upgrade();
    CHECK_NULL_RETURN(fixedChild, false);
    CHECK_NULL_RETURN(selectionFixedIndex_ >= 0, false);
    selectionStartIndex_ = selectionFixedIndex_;
    selectionEndIndex_ = selectionFixedIndex_;
    fixedHandleIsTopOnStart_ = true;
    hasSelectionStartEvent_ = true;
    return HandleSelectionUpdate(eventInfo);
}

bool SelectionContainer::ProcessSelectionEndCommon(bool showOverlay)
{
    if (!hasSelectionStartEvent_) {
        return false;
    }

    auto selectionStartChild = selectionStartChild_.Upgrade();
    auto selectionEndChild = selectionEndChild_.Upgrade();
    auto selectionFixedChild = selectionFixedChild_.Upgrade();
    bool hasSelectableText = false;
    if (!selectionStartChild && !selectionEndChild) {
        selectionStartChild = selectionFixedChild;
        selectionEndChild = selectionFixedChild;
        selectionStartChild_ = selectionFixedChild_;
        selectionEndChild_ = selectionFixedChild_;
    } else if (!selectionStartChild) {
        selectionStartChild = selectionEndChild;
        selectionStartChild_ = selectionEndChild_;
    } else if (!selectionEndChild) {
        selectionEndChild = selectionStartChild;
        selectionEndChild_ = selectionStartChild_;
    }
    if (selectionStartChild) {
        hasSelectableText |= selectionStartChild->HasSelectableText();
        selectionStartChild->UpdateSelectionHandleInfo();
    }
    if (selectionEndChild && selectionEndChild != selectionStartChild) {
        hasSelectableText |= selectionEndChild->HasSelectableText();
        selectionEndChild->UpdateSelectionHandleInfo();
    }
    if (hasSelectableText) {
        SaveOldSelectedType();
        if (showOverlay) {
            ProcessOverlay({ .animation = true });
        }
    }
    ReportSelectionText();
    ResetSelectionSessionState();
    return selectionStartChild && selectionEndChild;
}

bool SelectionContainer::ProcessGestureSelectionEnd(const SelectionEndEventInfo& eventInfo)
{
    return ProcessSelectionEndCommon(true);
}

bool SelectionContainer::ProcessMouseLeftRelease(const SelectionEndEventInfo& eventInfo)
{
    return ProcessSelectionEndCommon(false);
}

bool SelectionContainer::ProcessHandleMoveSelectionEnd(const OffsetF& movingPointInContainer)
{
    if (!hasSelectionStartEvent_) {
        return false;
    }
    auto selectionStartChild = selectionStartChild_.Upgrade();
    auto selectionEndChild = selectionEndChild_.Upgrade();
    if (selectionStartChild) {
        selectionStartChild->UpdateSelectionHandleInfo();
    }
    if (selectionEndChild && selectionEndChild != selectionStartChild) {
        selectionEndChild->UpdateSelectionHandleInfo();
    }
    ResetSelectionSessionState();
    ReportSelectionText();
    return selectionStartChild && selectionEndChild;
}

bool SelectionContainer::BetweenSelectedPosition(const Offset& globalOffset) const
{
    for (const auto& weakChild : registeredChildList_) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->BetweenSelectedPosition(globalOffset)) {
            return true;
        }
    }
    return false;
}

void SelectionContainer::ResetSelectionSessionState()
{
    hasSelectionStartEvent_ = false;
    selectionStartIndex_ = -1;
    selectionEndIndex_ = -1;
    fixedHandleIsTopOnStart_ = true;
}

void SelectionContainer::ResetAllSelection()
{
    auto childList = GetChildList();
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        child->SelectTextByIndex(-1, -1);
        child->ReportSelectionText();
    }
    selectionStartChild_.Reset();
    selectionEndChild_.Reset();
    selectionStartIndex_ = -1;
    selectionEndIndex_ = -1;
    hasSelectionStartEvent_ = false;
    OnSelectionRangeChanged({});
}

void SelectionContainer::CollectAndNotifySelectionChange()
{
    std::vector<std::u16string> selectedTexts;
    for (const auto& weakChild : GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto text = child->GetSelectionText();
        if (!text.empty()) {
            selectedTexts.push_back(std::move(text));
        }
    }
    OnSelectionRangeChanged(selectedTexts);
}

void SelectionContainer::ReportSelectionText()
{
    for (const auto& weakChild : GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        child->ReportSelectionText();
    }
}

void SelectionContainer::NotifyRegisteredChildrenPropertyUpdate(uint32_t flags)
{
    for (const auto& weakChild : GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        child->OnContainerPropertyUpdate(flags);
    }
}

bool SelectionContainer::IsSelectAll()
{
    auto childList = GetChildList();
    bool hasSelectableText = false;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (!child->HasSelectableText()) {
            continue;
        }
        hasSelectableText = true;
        if (!child->IsSelectAll()) {
            return false;
        }
    }
    return hasSelectableText;
}

bool SelectionContainer::HasSelectableText()
{
    auto childList = GetChildList();
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->HasSelectableText()) {
            return true;
        }
    }
    return false;
}

void SelectionContainer::UpdateSelectionBoundaryChild(const RefPtr<SelectionContainerChild>& child)
{
    CHECK_NULL_VOID(child);
    selectionStartChild_ = child;
    selectionEndChild_ = child;
}

void SelectionContainer::MarkChildSortDirty()
{
    sortDirty_ = true;
}

void SelectionContainer::RefreshChildSortResult()
{
    auto& childList = registeredChildList_;
    for (auto childIter = childList.begin(); childIter != childList.end();) {
        if (!childIter->Upgrade()) {
            childIter = childList.erase(childIter);
            continue;
        }
        ++childIter;
    }
    if (childList.empty()) {
        sortDirty_ = false;
        return;
    }

    SortChildList();
    sortDirty_ = false;
}

std::vector<WeakPtr<SelectionContainerChild>> SelectionContainer::GetChildList()
{
    if (sortDirty_) {
        RefreshChildSortResult();
    }

    std::vector<WeakPtr<SelectionContainerChild>> childList;
    childList.reserve(registeredChildList_.size());
    for (const auto& weakChild : registeredChildList_) {
        if (weakChild.Upgrade()) {
            childList.emplace_back(weakChild);
        }
    }
    return childList;
}

void SelectionContainer::SortChildList()
{
    auto& childList = registeredChildList_;
    auto containerNode = GetHostNode();
    CHECK_NULL_VOID(containerNode);

    std::vector<SelectionChildSortInfo> sortInfoList;
    sortInfoList.reserve(childList.size());
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto childNode = child->GetHostNode();
        CHECK_NULL_CONTINUE(childNode);
        SelectionChildSortInfo sortInfo;
        sortInfo.child = weakChild;
        sortInfo.positionInContainer = childNode->ConvertPoint(OffsetF(0.0f, 0.0f), containerNode);
        sortInfoList.emplace_back(sortInfo);
    }

    std::stable_sort(sortInfoList.begin(), sortInfoList.end(),
        [](const SelectionChildSortInfo& left, const SelectionChildSortInfo& right) {
            const auto yDiff = left.positionInContainer.GetY() - right.positionInContainer.GetY();
            if (GreatNotEqual(std::fabs(yDiff), POSITION_COMPARE_EPSILON)) {
                return LessNotEqual(yDiff, 0.0f);
            }
            const auto xDiff = left.positionInContainer.GetX() - right.positionInContainer.GetX();
            if (GreatNotEqual(std::fabs(xDiff), POSITION_COMPARE_EPSILON)) {
                return LessNotEqual(xDiff, 0.0f);
            }
            return false;
        });

    childList.clear();
    for (const auto& sortInfo : sortInfoList) {
        if (sortInfo.child.Upgrade()) {
            childList.emplace_back(sortInfo.child);
        }
    }
}

void SelectionContainer::SortSelectionBoundaryChildren(const RefPtr<FrameNode>& containerNode)
{
    CHECK_NULL_VOID(containerNode);
    auto startChild = selectionStartChild_.Upgrade();
    auto endChild = selectionEndChild_.Upgrade();
    CHECK_NULL_VOID(startChild);
    CHECK_NULL_VOID(endChild);

    OffsetF startPointInContainer;
    OffsetF endPointInContainer;
    CHECK_NULL_VOID(GetChildOriginInContainer(containerNode, startChild, startPointInContainer));
    CHECK_NULL_VOID(GetChildOriginInContainer(containerNode, endChild, endPointInContainer));

    const auto yDiff = startPointInContainer.GetY() - endPointInContainer.GetY();
    if (GreatNotEqual(std::fabs(yDiff), POSITION_COMPARE_EPSILON)) {
        if (GreatNotEqual(yDiff, 0.0f)) {
            selectionStartChild_ = endChild;
            selectionEndChild_ = startChild;
        }
        return;
    }

    const auto xDiff = startPointInContainer.GetX() - endPointInContainer.GetX();
    if (GreatNotEqual(std::fabs(xDiff), POSITION_COMPARE_EPSILON) && GreatNotEqual(xDiff, 0.0f)) {
        selectionStartChild_ = endChild;
        selectionEndChild_ = startChild;
    }
}
} // namespace OHOS::Ace::NG
