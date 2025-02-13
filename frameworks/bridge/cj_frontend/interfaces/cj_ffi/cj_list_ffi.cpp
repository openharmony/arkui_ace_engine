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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_list_ffi.h"
#include "cj_lambda.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_ng/base/view_stack_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL };
const std::vector<EdgeEffect> LIST_EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<ScrollState> SCROLL_STATE = { ScrollState::IDLE, ScrollState::SCROLL,
    ScrollState::FLING };
const std::vector<V2::ListItemAlign> LIST_ITEM_ALIGN = { V2::ListItemAlign::START, V2::ListItemAlign::CENTER,
    V2::ListItemAlign::END };
const std::vector<V2::StickyStyle> STICKY_STYLE = { V2::StickyStyle::NONE, V2::StickyStyle::HEADER,
    V2::StickyStyle::FOOTER, V2::StickyStyle::BOTH };
const std::vector<ScrollSnapAlign> SCROLL_SNAP_ALIGN = { ScrollSnapAlign::NONE, ScrollSnapAlign::START,
    ScrollSnapAlign::CENTER, ScrollSnapAlign::END };
const std::vector<ScrollAlign> SCROLL_ALIGN_LIST = { ScrollAlign::START, ScrollAlign::CENTER, ScrollAlign::END,
    ScrollAlign::AUTO, ScrollAlign::NONE };

std::function<void(Dimension, ScrollState)> FormatOnScrollFunction(void (*callback)(double offset, int32_t state))
{
    auto result = [lambda = CJLambda::Create(callback)](const Dimension& offset, const ScrollState& state) -> void {
        int32_t offseState = 0;
        for (size_t  i = 0; i < SCROLL_STATE.size(); i++) {
            if (SCROLL_STATE[i] == state) {
                offseState = static_cast<int32_t>(i);
            }
        }
        lambda(offset.Value(), offseState);
    };
    return result;
}

OnScrollBeginEvent FormatOnScrollBeginFunction(FfiOffsetRemain (*callback)(double dx, double dy))
{
    auto result = [lambda = CJLambda::Create(callback)](const Dimension& dx, const Dimension& dy) -> ScrollInfo {
        ScrollInfo scrollInfo;
        FfiOffsetRemain result = lambda(dx.Value(), dy.Value());
        scrollInfo.dx = Dimension { result.dxRemain, DimensionUnit::VP };
        scrollInfo.dy = Dimension { result.dyRemain, DimensionUnit::VP };
        return scrollInfo;
    };
    return result;
}
} // namespace

namespace OHOS::Ace::Framework {
Rect NativeListScroller::GetItemRectInGroup(int32_t index, int32_t indexInGroup)
{
    auto listController = this->GetController();
    if (!listController) {
        LOGE("listController is nullptr");
        return Rect();
    }
    return listController->GetItemRectInGroup(index, indexInGroup);
}

void NativeListScroller::ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    auto listController = this->GetController();
    if (!listController) {
        LOGE("listController is nullptr");
        return;
    }
    listController->JumpToItemInGroup(index, indexInGroup, smooth, align, SCROLL_FROM_JUMP);
}

ListItemGroupIndex NativeListScroller::GetVisibleListContentInfo(double x, double y)
{
    auto listController = this->GetController();
    if (!listController) {
        LOGE("listController is nullptr");
        return ListItemGroupIndex();
    }
    return listController->GetItemIndexInGroup(x, y);
}

void NativeListScroller::CloseAllSwipeActions()
{
    auto listController = this->GetController();
    if (!listController) {
        LOGE("listController is nullptr");
        return;
    }
    listController->CloseAllSwipeActions(nullptr);
}

void NativeListScroller::CloseAllSwipeActionsWithCallback(const std::function<void()>& onFinishCallback)
{
    auto listController = this->GetController();
    if (!listController) {
        LOGE("listController is nullptr");
        return;
    }
    std::function<void()> callback = onFinishCallback;
    listController->CloseAllSwipeActions(std::move(callback));
}
}

extern "C" {
void FfiOHOSAceFrameworkListCreate(double space, int32_t unit, int32_t initialIndex, int64_t scrollerID)
{
    Dimension spaceDime(space, static_cast<DimensionUnit>(unit));

    ListModel::GetInstance()->Create();
    ListModel::GetInstance()->SetSpace(spaceDime);
    if (initialIndex >= 0) {
        ListModel::GetInstance()->SetInitialIndex(initialIndex);
    }
    if (scrollerID > 0) {
        auto scroller = FFIData::GetData<NativeNGScroller>(scrollerID);
        if (scroller == nullptr) {
            auto listScroller = FFIData::GetData<NativeListScroller>(scrollerID);
            if (listScroller == nullptr) {
                LOGE("invalid scrollerID");
                return;
            }
            RefPtr<ScrollControllerBase> listController = ListModel::GetInstance()->CreateScrollController();
            listScroller->SetController(listController);
            auto proxy = AceType::DynamicCast<NG::ScrollBarProxy>(listScroller->GetScrollBarProxy());
            if (!proxy) {
                proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
                listScroller->SetScrollBarProxy(proxy);
            }
            ListModel::GetInstance()->SetScroller(listController, proxy);
        } else {
            RefPtr<ScrollControllerBase> listController = ListModel::GetInstance()->CreateScrollController();
            scroller->SetController(listController);
            auto proxy = AceType::DynamicCast<NG::ScrollBarProxy>(scroller->GetScrollBarProxy());
            if (!proxy) {
                proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
                scroller->SetScrollBarProxy(proxy);
            }
            ListModel::GetInstance()->SetScroller(listController, proxy);
        }
    }
}

void FfiOHOSAceFrameworkListSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    if (value.Value() < 0.0f) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetHeight(value);
    ListModel::GetInstance()->SetHasHeight(true);
}

void FfiOHOSAceFrameworkListSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    if (value.Value() < 0.0f) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetWidth(value);
    ListModel::GetInstance()->SetHasWidth(true);
}

void FfiOHOSAceFrameworkListSetDirection(int32_t direction)
{
    if (!Utils::CheckParamsValid(direction, AXIS.size())) {
        LOGE("bindContextMenu error, invalid value for responseType");
        return;
    }
    ListModel::GetInstance()->SetListDirection(AXIS[direction]);
}

void FfiOHOSAceFrameworkListSetDivider(DividerParams params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension startMarginDime(params.startMargin, static_cast<DimensionUnit>(params.startMarginUnit));
    Dimension endMarginDime(params.endMargin, static_cast<DimensionUnit>(params.endMarginUnit));

    V2::ItemDivider divider;
    divider.strokeWidth = widthDime;
    divider.color = Color(params.color);
    divider.startMargin = startMarginDime;
    divider.endMargin = endMarginDime;

    ListModel::GetInstance()->SetDivider(divider);
}

void FfiOHOSAceFrameworkListSetEditMode(bool flag)
{
    ListModel::GetInstance()->SetEditMode(flag);
}

void FfiOHOSAceFrameworkListSetEdgeEffect(int32_t edgeEffect)
{
    if (!Utils::CheckParamsValid(edgeEffect, LIST_EDGE_EFFECT.size())) {
        LOGE("bindContextMenu error, invalid value for responseType");
        return;
    }
    ListModel::GetInstance()->SetEdgeEffect(LIST_EDGE_EFFECT[edgeEffect], true);
}

void FfiOHOSAceFrameworkListSetEdgeEffectWithOption(int32_t edgeEffect, bool options)
{
    if (!Utils::CheckParamsValid(edgeEffect, LIST_EDGE_EFFECT.size())) {
        LOGE("bindContextMenu error, invalid value for responseType");
        return;
    }
    ListModel::GetInstance()->SetEdgeEffect(LIST_EDGE_EFFECT[edgeEffect], options);
}

void FfiOHOSAceFrameworkListSetChainAnimation(bool flag)
{
    ListModel::GetInstance()->SetChainAnimation(flag);
}

void FfiOHOSAceFrameworkListSetMultiSelectable(bool flag)
{
    ListModel::GetInstance()->SetMultiSelectable(flag);
}

void FfiOHOSAceFrameworkListSetLanes(int32_t lanes)
{
    ListModel::GetInstance()->SetLanes(lanes);
}

void FfiOHOSAceFrameworkListSetLanesGutter(int32_t lanes, double gutter, int32_t gutterUnit)
{
    ListModel::GetInstance()->SetLanes(lanes);

    Dimension laneGutter(gutter, static_cast<DimensionUnit>(gutterUnit));
    ListModel::GetInstance()->SetLaneGutter(laneGutter);
}

void FfiOHOSAceFrameworkListSetLanesByLengthConstrain(double min, int32_t minUnit, double max, int32_t maxUnit)
{
    Dimension minDime(min, static_cast<DimensionUnit>(minUnit));
    Dimension maxDime(max, static_cast<DimensionUnit>(maxUnit));
    ListModel::GetInstance()->SetLaneConstrain(minDime, maxDime);
}

void FfiOHOSAceFrameworkListSetLanesGutterByLengthConstrain(LanesParams lanesParams)
{
    Dimension minDime(lanesParams.min, static_cast<DimensionUnit>(lanesParams.minUnit));
    Dimension maxDime(lanesParams.max, static_cast<DimensionUnit>(lanesParams.maxUnit));
    ListModel::GetInstance()->SetLaneConstrain(minDime, maxDime);

    Dimension laneGutter(lanesParams.gutter, static_cast<DimensionUnit>(lanesParams.gutterUnit));
    ListModel::GetInstance()->SetLaneGutter(laneGutter);
}

void FfiOHOSAceFrameworkListSetAlignListItem(int32_t align)
{
    if (!Utils::CheckParamsValid(align, LIST_ITEM_ALIGN.size())) {
        LOGE("bindContextMenu error, invalid value for listItemAlign");
        return;
    }
    ListModel::GetInstance()->SetListItemAlign(LIST_ITEM_ALIGN[align]);
}

void FfiOHOSAceFrameworkListSetSticky(int32_t style)
{
    if (!Utils::CheckParamsValid(style, STICKY_STYLE.size())) {
        LOGE("bindContextMenu error, invalid value for listItemAlign");
        return;
    }
    ListModel::GetInstance()->SetSticky(STICKY_STYLE[style]);
}

void FfiOHOSAceFrameworkListSetNestedScroll(int32_t scrollForward, int32_t scrollBackward)
{
    NestedScrollOptions localNestedScrollOptions = {.forward = NestedScrollMode(scrollForward),
        .backward = NestedScrollMode(scrollBackward)};
    ListModel::GetInstance()->SetNestedScroll(localNestedScrollOptions);
}

void FfiOHOSAceFrameworkListSetCachedCount(int32_t cachedCount)
{
    int32_t value = cachedCount < 0 ? 1 : cachedCount;
    ListModel::GetInstance()->SetCachedCount(value);
}

void FfiOHOSAceFrameworkListSetScrollBar(int32_t barState)
{
    if (!Utils::CheckParamsValid(barState, DISPLAY_MODE.size())) {
        LOGE("bindContextMenu error, invalid value for barState");
        return;
    }
    ListModel::GetInstance()->SetScrollBar(DISPLAY_MODE[barState]);
}

void FfiOHOSAceFrameworkListScrollBarColor(uint32_t color)
{
    ListModel::GetInstance()->SetScrollBarColor(Color(color).ColorToString());
}

void FfiOHOSAceFrameworkListScrollBarWidth(double value, int32_t valueUnit)
{
    Dimension dimWidth(value, static_cast<DimensionUnit>(valueUnit));
    CalcDimension scrollBarWidth = CalcDimension(dimWidth);
    if (scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        return;
    }
    ListModel::GetInstance()->SetScrollBarWidth(scrollBarWidth.ToString());
}

void FfiOHOSAceFrameworkListSetFriction(double friction)
{
    double value = friction < 0.0 ? 0.0 : friction;
    ListModel::GetInstance()->SetFriction(value);
}

void FfiOHOSAceFrameworkListSetEnableScrollInteraction(bool flag)
{
    ListModel::GetInstance()->SetScrollEnabled(flag);
}

void FfiOHOSAceFrameworkListSetContentStartOffset(double offset)
{
    float value = offset < 0.0 ? 0.0 : offset;
    ListModel::GetInstance()->SetContentStartOffset(value);
}
void FfiOHOSAceFrameworkListSetContentEndOffset(double offset)
{
    float value = offset < 0.0 ? 0.0 : offset;
    ListModel::GetInstance()->SetContentEndOffset(value);
}

void FfiOHOSAceFrameworkListSetScrollSnapAlign(int32_t scrollSnapAlign)
{
    if (!Utils::CheckParamsValid(scrollSnapAlign, SCROLL_SNAP_ALIGN.size())) {
        LOGE("bindContextMenu error, invalid value for scrollSnapAlign");
        return;
    }
    ListModel::GetInstance()->SetScrollSnapAlign(SCROLL_SNAP_ALIGN[scrollSnapAlign]);
}

void FfiOHOSAceFrameworkListSetMaintainPosition(bool enabled)
{
    ListModel::GetInstance()->SetMaintainVisibleContentPosition(enabled);
}

void FfiOHOSAceFrameworkListSetItemDeleteCallback(bool (*callback)(int32_t value))
{
    ListModel::GetInstance()->SetOnItemDelete(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetScrollIndexCallback(void (*callback)(int32_t firstIndex, int32_t lastIndex))
{
    auto lambda = [callback = CJLambda::Create(callback)](int32_t a, int32_t b, int32_t c) {
        callback(a, b);
    };
    ListModel::GetInstance()->SetOnScrollIndex(lambda);
}

void FfiOHOSAceFrameworkListSetOnScrollIndexCallback(void (*callback)(int32_t firstIndex,
    int32_t lastIndex, int32_t centerIndex))
{
    auto lambda = [callback = CJLambda::Create(callback)](int32_t a, int32_t b, int32_t c) {
        callback(a, b, c);
    };
    ListModel::GetInstance()->SetOnScrollIndex(lambda);
}

void FfiOHOSAceFrameworkListSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state))
{
    auto lambda = [callback = CJLambda::Create(callback)](const Dimension& offset, const ScrollState& state)
     -> ScrollFrameResult {
        auto res = callback(offset.Value(), static_cast<int32_t>(state));
        ScrollFrameResult scrollRes { .offset = Dimension { res, DimensionUnit::VP } };
        return scrollRes;
    };
    ListModel::GetInstance()->SetOnScrollFrameBegin(lambda);
}

void FfiOHOSAceFrameworkListSetOnScrollCallback(void (*callback)(double offset, int32_t state))
{
    ListModel::GetInstance()->SetOnScroll(FormatOnScrollFunction(callback));
}

void FfiOHOSAceFrameworkListSetOnReachStartCallback(void (*callback)())
{
    ListModel::GetInstance()->SetOnReachStart(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetOnReachEndCallback(void (*callback)())
{
    ListModel::GetInstance()->SetOnReachEnd(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetOnScrollStartCallback(void (*callback)())
{
    ListModel::GetInstance()->SetOnScrollStart(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetOnScrollStopCallback(void (*callback)())
{
    ListModel::GetInstance()->SetOnScrollStop(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetOnScrollBeginCallback(FfiOffsetRemain (*callback)(double dx, double dy))
{
    ListModel::GetInstance()->SetOnScrollBegin(FormatOnScrollBeginFunction(callback));
}

void FfiOHOSAceFrameworkListSetOnItemMoveCallback(bool (*callback)(int32_t start, int32_t end))
{
    ListModel::GetInstance()->SetOnItemMove(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkListSetOnScrollVisibleContentChange(void (*callback)(
    CJVisibleListContentInfo start, CJVisibleListContentInfo end))
{
    auto lambda = [ffiCallback = CJLambda::Create(callback)](
        const ListItemIndex startInfo, const ListItemIndex endInfo) -> void {
            CJVisibleListContentInfo start_ {startInfo.index, startInfo.area, startInfo.indexInGroup};
            CJVisibleListContentInfo end_ {endInfo.index, endInfo.area, endInfo.indexInGroup};
            ffiCallback(start_, end_);
    };
    ListModel::GetInstance()->SetOnScrollVisibleContentChange(std::move(lambda));
}

void FfiOHOSAceFrameworkListSetOnItemDragStartCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [ffiCallback = CJLambda::Create(callback), node = frameNode](
        const ItemDragInfo& itemInfo, int32_t itemIndexVal) -> RefPtr<AceType> {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            int32_t itemIndex_ = itemIndexVal;
            ViewStackModel::GetInstance()->NewScope();
            {
                PipelineContext::SetCallBackNode(node);
                ffiCallback(itemDragInfo_, itemIndex_);
            }
            return ViewStackModel::GetInstance()->Finish();
    };
    ListModel::GetInstance()->SetOnItemDragStart(std::move(lambda));
}

void FfiOHOSAceFrameworkListOnItemDragStartWithBack(
    CJDragItemInfo (*callback)(CJPosition itemDragInfo, int32_t itemIndex))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [ffiCallback = CJLambda::Create(callback), node = frameNode](
        const ItemDragInfo& itemInfo, int32_t itemIndexVal) -> RefPtr<AceType> {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            int32_t itemIndex_ = itemIndexVal;
            LOGI("FfiOHOSAceFrameworkListOnItemDragStartWithBack lambda start");
            auto ret = ffiCallback(itemDragInfo_, itemIndex_);
            // use another VSP instance while executing the builder function
            if (ret.builder == nullptr) {
                LOGE("FfiOHOSAceFrameworkListOnItemDragStartWithBack lambda ret is nullptr");
                return nullptr;
            }
            std::function<void(void)> builderFunc = CJLambda::Create(ret.builder);
            ViewStackModel::GetInstance()->NewScope();
            {
                PipelineContext::SetCallBackNode(node);
                builderFunc();
            }
            return ViewStackModel::GetInstance()->Finish();
    };
    ListModel::GetInstance()->SetOnItemDragStart(std::move(lambda));
}

void FfiOHOSAceFrameworkListSetOnItemDragEnterCallback(void (*callback)(CJPosition itemDragInfo))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [ffiCallback = CJLambda::Create(callback), node = frameNode](
        const ItemDragInfo& itemInfo) -> void {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            PipelineContext::SetCallBackNode(node);
            ffiCallback(itemDragInfo_);
    };
    ListModel::GetInstance()->SetOnItemDragEnter(std::move(lambda));
}

void FfiOHOSAceFrameworkListSetOnItemDragMoveCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex, int32_t insertIndex))
{
    auto lambda = [ffiCallback = CJLambda::Create(callback)](
        const ItemDragInfo& itemInfo, int32_t itemIndexVal, int32_t insertIndexVal) -> void {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            int32_t itemIndex_ = itemIndexVal;
            int32_t insertIndex_ = insertIndexVal;
            ffiCallback(itemDragInfo_, itemIndex_, insertIndex_);
    };
    ListModel::GetInstance()->SetOnItemDragMove(std::move(lambda));
}

void FfiOHOSAceFrameworkListSetOnItemDragLeaveCallback(void (*callback)(CJPosition itemDragInfo, int32_t itemIndex))
{
    auto lambda = [ffiCallback = CJLambda::Create(callback)](
        const ItemDragInfo& itemInfo, int32_t itemIndexVal) -> void {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            int32_t itemIndex_ = itemIndexVal;
            ffiCallback(itemDragInfo_, itemIndex_);
    };
    ListModel::GetInstance()->SetOnItemDragLeave(std::move(lambda));
}
void FfiOHOSAceFrameworkListSetOnItemDropCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess))
{
    auto lambda = [ffiCallback = CJLambda::Create(callback)](
        const ItemDragInfo& itemInfo, int32_t itemIndexVal, int32_t insertIndexVal, bool isSuccessVal) -> void {
            CJPosition itemDragInfo_ {itemInfo.GetX(), itemInfo.GetY()};
            int32_t itemIndex_ = itemIndexVal;
            int32_t insertIndex_ = insertIndexVal;
            bool isSuccess_ = isSuccessVal;
            ffiCallback(itemDragInfo_, itemIndex_, insertIndex_, isSuccess_);
    };
    ListModel::GetInstance()->SetOnItemDrop(std::move(lambda));
}

int64_t FfiOHOSAceFrameworkListScrollerCtor()
{
    auto nativeListScroller = FFIData::Create<NativeListScroller>();
    if (nativeListScroller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return nativeListScroller->GetID();
}

CJRectResult FfiOHOSAceFrameworkListScrollerGetItemRectInGroup(int64_t selfId, int32_t index, int32_t indexInGroup)
{
    CJRectResult cjRectResult = { 0.0, 0.0, 0.0, 0.0 };
    auto self_ = FFIData::GetData<NativeListScroller>(selfId);
    if (self_ != nullptr) {
        auto rectResult = self_->GetItemRectInGroup(index, indexInGroup);
        cjRectResult.x = rectResult.Left();
        cjRectResult.y = rectResult.Top();
        cjRectResult.width = rectResult.Width();
        cjRectResult.height = rectResult.Height();
    } else {
        LOGE("invalid listScrollerID");
    }
    return cjRectResult;
}

void FfiOHOSAceFrameworkListScrollerScrollToItemInGroup(
    int64_t selfId, int32_t index, int32_t indexInGroup, bool smooth, int32_t align)
{
    auto self_ = FFIData::GetData<NativeListScroller>(selfId);
    if (self_ == nullptr) {
        LOGE("invalid listScrollerID");
        return;
    }
    if (index < 0) {
        return;
    }
    if (indexInGroup < 0) {
        return;
    }
    if (!Utils::CheckParamsValid(align, SCROLL_ALIGN_LIST.size())) {
        LOGE("bindContextMenu error, invalid value for ScrollAlign");
        return;
    }
    self_->ScrollToItemInGroup(index, indexInGroup, smooth, SCROLL_ALIGN_LIST[align]);
}

CJVisibleListContentInfo FfiOHOSAceFrameworkListScrollerGetVisibleListContentInfo(
    int64_t selfId, double x, double y)
{
    Dimension xOffset = Dimension { x, DimensionUnit::VP };
    Dimension yOffset = Dimension { y, DimensionUnit::VP };
    auto self_ = FFIData::GetData<NativeListScroller>(selfId);
    CJVisibleListContentInfo listContentInfo = { -1, -1, -1 };
    if (self_ == nullptr) {
        LOGE("invalid listScrollerID");
        return listContentInfo;
    }
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            auto deltaX = context->NormalizeToPx(xOffset);
            auto deltaY = context->NormalizeToPx(yOffset);
            auto itemGroup = self_->GetVisibleListContentInfo(deltaX, deltaY);
            listContentInfo.index = itemGroup.index;
            if (itemGroup.area != -1) {
                listContentInfo.itemGroupArea = itemGroup.area;
            }
            if (itemGroup.indexInGroup != -1) {
                listContentInfo.itemIndexInGroup = itemGroup.indexInGroup;
            }
        }
    }
    return listContentInfo;
}
void FfiOHOSAceFrameworkListScrollerCloseAllSwipeActionsWithCallback(int64_t selfId, void (*onFinishCallback)())
{
    auto self_ = FFIData::GetData<NativeListScroller>(selfId);
    if (self_ != nullptr) {
        self_->CloseAllSwipeActionsWithCallback(CJLambda::Create(onFinishCallback));
    }
}
void FfiOHOSAceFrameworkListScrollerCloseAllSwipeActions(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeListScroller>(selfId);
    if (self_ != nullptr) {
        self_->CloseAllSwipeActions();
    }
}
}
