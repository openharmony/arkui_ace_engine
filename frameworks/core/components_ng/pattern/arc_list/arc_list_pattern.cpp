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
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/common/vibrator/vibrator_utils.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr float ARC_LIST_FRICTION = 0.8f;
constexpr float FRICTION_SCALE = -4.2f;
constexpr float DRAG_FIX_OFFSET_RATIO = 0.85f;
constexpr float ARC_LIST_DRAG_OVER_RATES = 0.6f;
constexpr float ARC_LIST_DRAG_OVER_KVALUE = 0.84f;
constexpr float ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO = 0.4f;
constexpr float FLOAT_TWO = 2.0f;
} // namespace

ArcListPattern::ArcListPattern()
{
#ifdef ARKUI_CIRCLE_FEATURE
    SetScrollBarShape(ScrollBarShape::ARC);
#endif
    SetFriction(ARC_LIST_FRICTION);
    scrollAlign_ = ScrollAlign::CENTER;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto arcListTheme = pipelineContext->GetTheme<ArcListTheme>();
    CHECK_NULL_VOID(arcListTheme);
    SetVelocityScale(arcListTheme->GetVelocityScale());
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
    headerOffset_ = listLayoutAlgorithm->GetHeaderOffset();
    oldHeaderSize_ = listLayoutAlgorithm->GetOldHeaderSize();
    oldFirstItemSize_ = listLayoutAlgorithm->GetOldFirstItemSize();
    headerStayNear_ = listLayoutAlgorithm->GetHeaderStayNear();
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

    SetLayoutAlgorithmParams(listLayoutAlgorithm, listLayoutProperty);

    listLayoutAlgorithm->SetStartHeaderPos(startHeaderPos_);
    listLayoutAlgorithm->SetHeaderOffset(headerOffset_);
    listLayoutAlgorithm->SetOldHeaderSize(oldHeaderSize_);
    listLayoutAlgorithm->SetOldFirstItemSize(oldFirstItemSize_);
    listLayoutAlgorithm->SetHeaderStayNear(headerStayNear_);
    listLayoutAlgorithm->SetIsInitialized(isInitialized_);
    return listLayoutAlgorithm;
}

bool ArcListPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        scrollStartMidIndex_ = GetMidIndex();
    }
    offset = FixScrollOffset(offset, source);
    return ListPattern::OnScrollCallback(offset, source);
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
    auto pipeline = GetContext();
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

void ArcListPattern::HandleScrollBarOutBoundary()
{
    if (itemPosition_.empty()) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    if (!IsOutOfBoundary(false) || !isScrollable_) {
        ScrollablePattern::HandleScrollBarOutBoundary(0);
        return;
    }

    float overScroll = 0.0f;
    float itemHeight = itemPosition_[centerIndex_].endPos - itemPosition_[centerIndex_].startPos;
    float snapSize = ArcListLayoutAlgorithm::GetItemSnapSize();
    float snapHeight = LessOrEqual(itemHeight, snapSize) ? itemHeight : snapSize;
    if (startIndex_ == 0 && Positive(startMainPos_ + snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO)) {
        overScroll = startMainPos_ + snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO;
    } else if ((endIndex_ == maxListItemIndex_) &&
                LessNotEqual(endMainPos_ - snapHeight / FLOAT_TWO, contentMainSize_ / FLOAT_TWO)) {
        overScroll = endMainPos_ - snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO;
    }
    ScrollablePattern::HandleScrollBarOutBoundary(overScroll);
}

float ArcListPattern::GetSnapCenterOverScrollPos(float startPos, float prevScroll)
{
    float overScroll = prevScroll;
    float itemHeight = itemPosition_[centerIndex_].endPos - itemPosition_[centerIndex_].startPos;
    float snapSize = ArcListLayoutAlgorithm::GetItemSnapSize();
    float snapHeight = LessOrEqual(itemHeight, snapSize) ? itemHeight : snapSize;
    auto endPos = endMainPos_ - currentDelta_;
    if (startIndex_ == 0 && Positive(startPos + snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO)) {
        overScroll = startPos + snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO;
    } else if ((endIndex_ == maxListItemIndex_) &&
               LessNotEqual(endPos - snapHeight / FLOAT_TWO, contentMainSize_ / FLOAT_TWO)) {
        overScroll = endPos - snapHeight / FLOAT_TWO - contentMainSize_ / FLOAT_TWO;
    }

    return overScroll;
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
    float stopOnScreen = GetMainAxisSize(contentConstraint.maxSize, Axis::VERTICAL) / FLOAT_TWO;
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
        if (GreatOrEqual(predictStop, itemInfo.startPos - space / FLOAT_TWO) &&
            LessNotEqual(predictStop, itemInfo.endPos + space / FLOAT_TWO)) {
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
    float midPos = contentMainSize_ / FLOAT_TWO;
    for (auto& pos : itemPosition_) {
        if (midPos <= pos.second.endPos + spaceWidth_ / FLOAT_TWO) {
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
    if (LessOrEqual(mainSize, ArcListLayoutAlgorithm::GetItemSnapSize())) {
        snapInfo.snapLow = snapInfo.snapHigh = (itemStart + itemEnd) / FLOAT_TWO;
        snapInfo.moveThreshold = mainSize * ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO;
    } else {
        snapInfo.snapLow = itemStart + ArcListLayoutAlgorithm::GetItemSnapSize() / FLOAT_TWO;
        snapInfo.snapHigh = itemEnd - ArcListLayoutAlgorithm::GetItemSnapSize() / FLOAT_TWO;
        snapInfo.moveThreshold = ArcListLayoutAlgorithm::GetItemSnapSize() * ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO;
    }

    return true;
}

float ArcListPattern::FixScrollOffset(float offset, int32_t source)
{
    if (!GetIsDragging() || itemPosition_.empty()) {
        return offset;
    }

    float fixOffset = offset;

    float originTotal = 0.0f;
    float realTotal = 0.0f;
    for (auto& pos : itemPosition_) {
        float height = pos.second.endPos - pos.second.startPos;
        float realHeight = height * pos.second.scale;
        originTotal += height + spaceWidth_;
        realTotal += realHeight + spaceWidth_;
    }
    originTotal -= spaceWidth_;
    realTotal -= spaceWidth_;

    if (GreatNotEqual(realTotal, 0.0f)) {
        float scale = (originTotal / realTotal - 1) * DRAG_FIX_OFFSET_RATIO + 1;
        fixOffset = offset * scale;
    }

    return fixOffset;
}

bool ArcListPattern::StartSnapAnimation(SnapAnimationOptions snapAnimationOptions)
{
    if (IsAtTop() && NearZero(snapAnimationOptions.animationVelocity)) {
        return false;
    }
    return ListPattern::StartSnapAnimation(snapAnimationOptions);
}

float ArcListPattern::GetScrollUpdateFriction(float overScroll)
{
    float contentMoveSize = contentMainSize_ / FLOAT_TWO * ARC_LIST_DRAG_OVER_RATES;
    float scale = (contentMoveSize - overScroll) / contentMoveSize;
    if (LessOrEqual(scale, 0.0f)) {
        return 0.0f;
    } else if (GreatOrEqual(scale, 1.0f)) {
        return ARC_LIST_DRAG_OVER_RATES;
    }
    return -exp(-ARC_LIST_DRAG_OVER_KVALUE * scale) + 1;
}

} // namespace OHOS::Ace::NG
