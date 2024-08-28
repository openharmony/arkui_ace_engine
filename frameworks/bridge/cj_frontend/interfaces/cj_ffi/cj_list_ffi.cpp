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
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/list/list_model.h"

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
            LOGE("invalid scrollerID");
            return;
        }
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

void FfiOHOSAceFrameworkListSetLanesByLengthConstrain(double min, int32_t minUnit, double max, int32_t maxUnit)
{
    Dimension minDime(min, static_cast<DimensionUnit>(minUnit));
    Dimension maxDime(max, static_cast<DimensionUnit>(maxUnit));
    ListModel::GetInstance()->SetLaneConstrain(minDime, maxDime);
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
}
