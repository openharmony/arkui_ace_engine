/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"

#include <string>

#include "base/geometry/axis.h"
#include "base/geometry/rect.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/bilateral_spring_node.h"
#include "core/animation/spring_model.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/list/arc_list_theme.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float ARC_LIST_VELOCITY_SCALE = 0.6f;
constexpr float ARC_LIST_FRICTION = 0.8f;
constexpr float FRICTION_SCALE = -4.2f;
constexpr float DRAG_FIX_OFFSET_RATIO = 0.6f;
} // namespace

ArcListPattern::ArcListPattern() : ListPattern(ListType::ARC_LIST) 
{
    SetFriction(ARC_LIST_FRICTION);
    SetVelocityScale(ARC_LIST_VELOCITY_SCALE);
    scrollAlign_ = ScrollAlign::CENTER;
}

void ArcListPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!GetScrollableEvent()) {
        AddScrollEvent();
        auto scrollableEvent = GetScrollableEvent();
        CHECK_NULL_VOID(scrollableEvent);
        scrollable_ = scrollableEvent->GetScrollable();
#ifdef SUPPORT_DIGITAL_CROWN
        scrollable_->ListenDigitalCrownEvent(host);
        scrollable_->SetDigitalCrownSensitivity(crownSensitivity_);
#endif
        scrollable_->RegisterFixScrollParamCallback(
            [weak = WeakClaim(this)](float mainPos, float& velocity, float& finalPos) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FixScrollParam(mainPos, velocity, finalPos);
            });
    }

    SetEdgeEffect();

    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetScrollBarProperty()) {
        SetScrollBar(paintProperty->GetScrollBarProperty());
    }

    SetChainAnimation();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    Register2DragDropManager();
    SetAccessibilityAction();
    if (IsNeedInitClickEventRecorder()) {
        Pattern::InitClickEventRecorder();
    }
    ReadThemeToFadingEdge();
}

void ArcListPattern::ReadThemeToFadingEdge()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto conlist = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(conlist);
    auto listTheme = conlist->GetTheme<ArcListTheme>();
    CHECK_NULL_VOID(listTheme);
    auto listThemeFadingEdge = listTheme->GetFadingEdge();
    if (listLayoutProperty->GetFadingEdge().has_value()) {
        isFadingEdge_ = listLayoutProperty->GetFadingEdge().value_or(listThemeFadingEdge);
    } else if (GetAxis() == Axis::HORIZONTAL) {
        isFadingEdge_ = false;
    } else {
        isFadingEdge_ = listThemeFadingEdge;
    }
    auto overlayNode = host->GetOverlayNode();
    if (!overlayNode && isFadingEdge_) {
        ListPattern::CreateAnalyzerOverlay(host);
    }
}

bool ArcListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ArcListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    startHeaderPos_ = listLayoutAlgorithm->GetStartHeaderPos();

    return ListPattern::OnDirtyLayoutWrapperSwap(dirty, config);
}

RefPtr<LayoutAlgorithm> ArcListPattern::CreateLayoutAlgorithm()
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, nullptr);
    int32_t headerIndex = -1;
    int32_t itemStartIndex = 0;
    if (header_) {
        auto count = header_->FrameCount();
        if (count > 0) {
            headerIndex = itemStartIndex;
            itemStartIndex += count;
        }
    }
    itemStartIndex_ = itemStartIndex;
    RefPtr<ArcListLayoutAlgorithm> listLayoutAlgorithm;
    listLayoutAlgorithm.Swap(MakeRefPtr<ArcListLayoutAlgorithm>(headerIndex, itemStartIndex));
    if (!posMap_) {
        posMap_ = MakeRefPtr<ArcListPositionMap>(itemStartIndex_);
    }
    if (childrenSize_) {
        listLayoutAlgorithm->SetListChildrenMainSize(childrenSize_);
        listLayoutAlgorithm->SetListPositionMap(posMap_);
    }
    if (!isInitialized_) {
        jumpIndex_ = listLayoutProperty->GetInitialIndex().value_or(0);
    }
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
        jumpIndex_.reset();
    }
    if (targetIndex_) {
        listLayoutAlgorithm->SetTargetIndex(targetIndex_.value());
    }
    if (predictSnapOffset_.has_value()) {
        listLayoutAlgorithm->SetPredictSnapOffset(predictSnapOffset_.value());
    }
    listLayoutAlgorithm->SetTotalOffset(GetTotalOffset());
    listLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    listLayoutAlgorithm->SetIsNeedCheckOffset(isNeedCheckOffset_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);
    listLayoutAlgorithm->SetPrevContentMainSize(contentMainSize_);
    if (IsOutOfBoundary(false) && GetScrollSource() != SCROLL_FROM_AXIS) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    listLayoutAlgorithm->SetIsSpringEffect(IsScrollableSpringEffect());
    listLayoutAlgorithm->SetCanOverScroll(CanOverScroll(GetScrollSource()));
    if (chainAnimation_) {
        SetChainAnimationLayoutAlgorithm(listLayoutAlgorithm, listLayoutProperty);
        SetChainAnimationToPosMap();
    }
    if (predictSnapEndPos_.has_value()) {
        listLayoutAlgorithm->SetPredictSnapEndPosition(predictSnapEndPos_.value());
    }
    listLayoutAlgorithm->SetStartHeaderPos(startHeaderPos_);
    return listLayoutAlgorithm;
}

bool ArcListPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        scrollStartMidIndex_ = GetMidIndex();
    }

    return ListPattern::OnScrollCallback(offset, source);
}

void ArcListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        return list->startMainPos_ + list->GetChainDelta(list->startIndex_) - list->currentDelta_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_ + list->GetChainDelta(list->endIndex_);
        auto startPos = list->startMainPos_ + list->GetChainDelta(list->startIndex_);
        if (!list->itemPosition_.empty()) {
            float endItemHeight =
                list->itemPosition_.rbegin()->second.endPos - list->itemPosition_.rbegin()->second.startPos;
            float snapSize = ARC_LIST_ITEM_SNAP_SIZE;
            float snapHeight = LessOrEqual(endItemHeight, snapSize) ? endItemHeight : snapSize;
            return list->contentMainSize_ / 2.0f + snapHeight / 2.0f - (endPos - startPos);
        }
        float leading = list->contentMainSize_ - (endPos - startPos) - list->contentEndOffset_;
        return (list->startIndex_ == 0) ? std::min(leading, list->contentStartOffset_) : leading;
    });
    scrollEffect->SetTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        if (!list->itemPosition_.empty()) {
            float startItemHeight =
                list->itemPosition_.begin()->second.endPos - list->itemPosition_.begin()->second.startPos;
            float snapSize = ARC_LIST_ITEM_SNAP_SIZE;
            float snapHeight = LessOrEqual(startItemHeight, snapSize) ? startItemHeight : snapSize;
            return list->contentMainSize_ / 2.0f - snapHeight / 2.0f;
        }

        return list->contentStartOffset_;
    });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_ + list->GetChainDelta(list->endIndex_);
        auto startPos = list->startMainPos_ + list->GetChainDelta(list->startIndex_);
        if (!list->itemPosition_.empty()) {
            float endItemHeight =
                list->itemPosition_.rbegin()->second.endPos - list->itemPosition_.rbegin()->second.startPos;
            float snapSize = ARC_LIST_ITEM_SNAP_SIZE;
            float snapHeight = LessOrEqual(endItemHeight, snapSize) ? endItemHeight : snapSize;
            return list->contentMainSize_ / 2.0f + snapHeight / 2.0f - (endPos - startPos);
        }
        float leading = list->contentMainSize_ - (endPos - startPos) - list->contentEndOffset_;
        return (list->startIndex_ == 0) ? std::min(leading, list->contentStartOffset_) : leading;
    });
    scrollEffect->SetInitTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        if (!list->itemPosition_.empty()) {
            float startItemHeight =
                list->itemPosition_.begin()->second.endPos - list->itemPosition_.begin()->second.startPos;
            float snapSize = ARC_LIST_ITEM_SNAP_SIZE;
            float snapHeight = LessOrEqual(startItemHeight, snapSize) ? startItemHeight : snapSize;
            return list->contentMainSize_ / 2.0f - snapHeight / 2.0f;
        }

        return list->contentStartOffset_;
    });
}

std::function<bool(int32_t)> ArcListPattern::GetScrollIndexAbility()
{
    return [wp = WeakClaim(this)](int32_t index) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (index == FocusHub::SCROLL_TO_HEAD) {
            pattern->ScrollToIndex(0, false, ScrollAlign::CENTER);
        } else if (index == FocusHub::SCROLL_TO_TAIL) {
            pattern->ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, false, ScrollAlign::CENTER);
        } else {
            pattern->ScrollToIndex(index, false, ScrollAlign::CENTER);
        }
        return true;
    };
}

bool ArcListPattern::ScrollListForFocus(int32_t nextIndex, int32_t curIndex, int32_t nextIndexInGroup)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    ScrollToIndex(nextIndex, smooth_, ScrollAlign::CENTER);
    pipeline->FlushUITasks();
    return true;
}

void ArcListPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ScrollablePattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("startIndex", startIndex_, filter);
    if (!itemPosition_.empty()) {
        json->PutExtAttr("itemStartPos", itemPosition_.begin()->second.startPos, filter);
    }
    std::string sensitivity = "CrownSensitivity.MEDIUM";
#ifdef SUPPORT_DIGITAL_CROWN
    if (crownSensitivity_ == CrownSensitivity::LOW) {
        sensitivity = "CrownSensitivity.LOW";
    } else if (crownSensitivity_ == CrownSensitivity::HIGH) {
        sensitivity = "CrownSensitivity.HIGH";
    } else {
        sensitivity = "CrownSensitivity.MEDIUM";
    }
#endif
    json->PutExtAttr("digitalCrownSensitivity", sensitivity.c_str(), filter);
}

void ArcListPattern::OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag)
{
    if (!posMap_) {
        posMap_ = MakeRefPtr<ArcListPositionMap>(itemStartIndex_);
    }
    posMap_->MarkDirty(flag);
    MarkDirtyNodeSelf();
}

void ArcListPattern::FixScrollParam(float mainPos, float& correctVelocity, float& finalPos)
{
    float friction = GetFriction();
    float fixPos = finalPos;
    if (GetOneItemSnapPosByFinalPos(mainPos, finalPos, fixPos)) {
        finalPos = fixPos;
        correctVelocity = (finalPos - mainPos) * (friction * -FRICTION_SCALE);
    }
}

void ArcListPattern::SetFriction(double friction)
{
    if (LessOrEqual(friction, 0.0)) {
        friction = ARC_LIST_FRICTION;
    }

    ScrollablePattern::SetFriction(friction);
}

bool ArcListPattern::GetOneItemSnapPosByFinalPos(float mainPos, float finalPos, float& snapPos)
{
    if (scrollStartMidIndex_ == -1) {
        return false;
    }

    snapPos = finalPos;
    float deltaPos = mainPos - finalPos;
    int32_t nCurIdx = GetMidIndex();

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    int32_t totalCnt = host->GetTotalChildCount() - itemStartIndex_;
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(listLayoutProperty, false);
    auto contentConstraint = listLayoutProperty->GetContentLayoutConstraint().value();
    float stopOnScreen = GetMainAxisSize(contentConstraint.maxSize, Axis::VERTICAL) / 2.0f;
    float predictStop = stopOnScreen + deltaPos;

    int32_t deltaIdx = LessOrEqual(mainPos, finalPos) ? -1 : 1;
    auto space = listLayoutProperty->GetSpace().value_or(0.0_vp).ConvertToPx();

    ListItemInfo itemInfo;
    int32_t index = 0;
    for (index = nCurIdx; index >= 0 && index < totalCnt; index += deltaIdx) {
        if (itemPosition_.find(index) == itemPosition_.end()) {
            break;
        }
        itemInfo = GetItemDisplayInfo(index);
        if (GreatOrEqual(predictStop, itemInfo.startPos - space / 2) &&
            LessNotEqual(predictStop, itemInfo.endPos + space / 2)) { /* 2:half */
            break;
        }
    }

    ItemSnapInfo snapInfo;
    if (index != scrollStartMidIndex_ || !GetItemSnapPosition(scrollStartMidIndex_, snapInfo)) {
        return false;
    }

    float moveDis = LessNotEqual(predictStop, snapInfo.snapLow) ? snapInfo.snapLow - predictStop : 0.0f;
    moveDis = LessNotEqual(snapInfo.snapHigh, predictStop) ? predictStop - snapInfo.snapHigh : moveDis;
    deltaIdx = LessNotEqual(predictStop, snapInfo.snapLow) ? -1 : 1;
    if (GreatNotEqual(moveDis, snapInfo.moveThreshold) && index + deltaIdx >= 0 && index + deltaIdx < totalCnt) {
        index += deltaIdx;
        if (!GetItemSnapPosition(index, snapInfo)) {
            return false;
        }
    } else {
        return false;
    }

    predictStop = LessNotEqual(predictStop, snapInfo.snapLow) ? snapInfo.snapLow : predictStop;
    predictStop = LessNotEqual(snapInfo.snapHigh, predictStop) ? snapInfo.snapHigh : predictStop;
    snapPos = mainPos - (predictStop - stopOnScreen);

    scrollStartMidIndex_ = -1;

    return true;
}

int32_t ArcListPattern::GetMidIndex()
{
    float midPos = contentMainSize_ / 2.0f;
    for (auto& pos : itemPosition_) {
        if (midPos <= pos.second.endPos + spaceWidth_ / 2) { /* 2:half */
            return pos.first;
        }
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    return host->GetTotalChildCount() - 1 - itemStartIndex_;
}

ListItemInfo ArcListPattern::GetItemDisplayInfo(int32_t index)
{
    ListItemInfo info;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, info);
    auto wrapper = host->GetOrCreateChildByIndex(index + itemStartIndex_, false);
    if (!wrapper) {
        return info;
    }
    auto geometryNode = wrapper->GetGeometryNode();
    if (!geometryNode) {
        return info;
    }

    if (itemPosition_.find(index) != itemPosition_.end()) {
        info = itemPosition_[index];
    }

    return info;
}

bool ArcListPattern::GetItemSnapPosition(int32_t nIndex, ItemSnapInfo& snapInfo)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto wrapper = host->GetOrCreateChildByIndex(nIndex + itemStartIndex_, false);
    if (!wrapper) {
        return false;
    }
    if (wrapper->GetHostTag() != V2::ARC_LIST_ITEM_ETS_TAG) {
        return false;
    }
    auto geometryNode = wrapper->GetGeometryNode();
    if (!geometryNode) {
        return false;
    }

    if (itemPosition_.find(nIndex) == itemPosition_.end()) {
        return false;
    }

    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(listLayoutProperty, false);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);

    float mainSize = geometryNode->GetMarginFrameSize().MainSize(axis);
    float itemStart = itemPosition_[nIndex].startPos;
    float itemEnd = itemPosition_[nIndex].endPos;
    if (LessOrEqual(mainSize, ARC_LIST_ITEM_SNAP_SIZE)) {
        snapInfo.snapLow = snapInfo.snapHigh = (itemStart + itemEnd) / 2.0f;
        snapInfo.moveThreshold = mainSize * ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO;
    } else {
        snapInfo.snapLow = itemStart + ARC_LIST_ITEM_SNAP_SIZE / 2.0f;
        snapInfo.snapHigh = itemEnd - ARC_LIST_ITEM_SNAP_SIZE / 2.0f;
        snapInfo.moveThreshold = ARC_LIST_ITEM_SNAP_SIZE * ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO;
    }

    return true;
}

float ArcListPattern::FixScrollOffset(float offset, int32_t source)
{
    if (!GetIsDragging())
    {
        return offset;
    }

    float fixOffset = offset;

    float originTotal = 0.0f;
    float realTotal = 0.0f;
    for (auto& pos : itemPosition_) {
        float height = pos.second.endPos - pos.second.startPos;
        float realHeight = height * pos.second.scale;
        originTotal = height + spaceWidth_;
        realTotal = realHeight + spaceWidth_;
    }

    float scale = (originTotal / realTotal - 1) * DRAG_FIX_OFFSET_RATIO + 1;
    fixOffset = offset * scale;

    return fixOffset;
}

} // namespace OHOS::Ace::NG
