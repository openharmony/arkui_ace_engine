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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_ffi.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"

#include "bridge/common/utils/utils.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "cj_lambda.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "base/utils/utils.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
    const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
        FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };
}

extern "C" {
void FfiOHOSAceFrameworkGridCreate()
{
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    if (!GridModel::GetInstance()) {
        GridModel::GetInstance()->Create(positionController, scrollBarProxy);
    } else {
        LOGE("Grid Instance is null");
    }
}

void FfiOHOSAceFrameworkGridCreateScroller(int64_t scrollerID)
{
    auto scroller = FFIData::GetData<NativeNGScroller>(scrollerID);
    if (scroller == nullptr) {
        LOGE("invalid scrollerID");
        return;
    }
    RefPtr<ScrollProxy> scrollBarProxy;
    // Init scroll bar proxy.
    scrollBarProxy = scroller->GetScrollBarProxy();
    if (!scrollBarProxy) {
        scrollBarProxy = GridModel::GetInstance()->CreateScrollBarProxy();
        scroller->SetScrollBarProxy(scrollBarProxy);
    }
    RefPtr<ScrollControllerBase> positionController;
    positionController = GridModel::GetInstance()->CreatePositionController();
    scroller->SetController(positionController);
    GridModel::GetInstance()->Create(positionController, scrollBarProxy);
}

void FfiOHOSAceFrameworkGridSetCachedCount(int32_t cachedCount)
{
    GridModel::GetInstance()->SetCachedCount(cachedCount);
}

void FfiOHOSAceFrameworkGridColumnsTemplate(const char* value)
{
    GridModel::GetInstance()->SetColumnsTemplate(value);
}

void FfiOHOSAceFrameworkGridRowsTemplate(const char* value)
{
    GridModel::GetInstance()->SetRowsTemplate(value);
}

void FfiOHOSAceFrameworkGridColumnsGapWithString(const char* value)
{
    Dimension valueFFI;
    // use default 'DimensionUnit::VP', 'vp' -> the value varies with pixel density of device.
    valueFFI = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP);
    GridModel::GetInstance()->SetColumnsGap(valueFFI);
}

void FfiOHOSAceFrameworkGridColumnsGapWithNum(int32_t value)
{
    Dimension valueFFI = Dimension(value, DimensionUnit::VP);
    GridModel::GetInstance()->SetColumnsGap(valueFFI);
}

void FfiOHOSAceFrameworkGridRowsGapWithString(const char* value)
{
    Dimension valueFFI;
    // use default 'VP', 'vp' -> the value varies with pixel density of device.
    valueFFI = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP);
    GridModel::GetInstance()->SetRowsGap(valueFFI);
}

void FfiOHOSAceFrameworkGridRowsGapWithNum(int32_t value)
{
    Dimension valueFFI = Dimension(value, DimensionUnit::VP);
    GridModel::GetInstance()->SetRowsGap(valueFFI);
}

void FfiOHOSAceFrameworkGridScrollBar(int32_t value)
{
    auto displayMode = static_cast<DisplayMode>(value);
    GridModel::GetInstance()->SetScrollBarMode(displayMode);
}

void FfiOHOSAceFrameworkGridScrollBarColor(uint32_t color)
{
    GridModel::GetInstance()->SetScrollBarColor(Color(color).ColorToString());
}

void FfiOHOSAceFrameworkGridScrollBarWidth(double value, int32_t valueUnit)
{
    Dimension dimWidth(value, static_cast<DimensionUnit>(valueUnit));
    CalcDimension scrollBarWidth = CalcDimension(dimWidth);
    if (scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        return;
    }
    GridModel::GetInstance()->SetScrollBarWidth(scrollBarWidth.ToString());
}

void FfiOHOSAceFrameworkGridCachedCount(int32_t cacheCount, bool show)
{
    if (cacheCount < 0) {
        cacheCount = 1;
    }
    GridModel::GetInstance()->SetCachedCount(cacheCount, show);
}

void FfiOHOSAceFrameworkGridEditMode(bool isEditMode)
{
    GridModel::GetInstance()->SetEditable(isEditMode);
}

void FfiOHOSAceFrameworkGridLayoutDirection(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        return;
    }
    GridModel::GetInstance()->SetLayoutDirection(LAYOUT_DIRECTION[value]);
}

void FfiOHOSAceFrameworkGridMaxCount(int32_t value)
{
    if (value < 1) {
        value = Infinity<int32_t>();
    }
    GridModel::GetInstance()->SetMaxCount(value);
}

void FfiOHOSAceFrameworkGridMinCount(int32_t value)
{
    if (value < 1) {
        value = 1;
    }
    GridModel::GetInstance()->SetMinCount(value);
}

void FfiOHOSAceFrameworkGridCellLength(int32_t value)
{
    GridModel::GetInstance()->SetCellLength(value);
}

void FfiOHOSAceFrameworkGridMultiSelectable(bool isSelectable)
{
    GridModel::GetInstance()->SetMultiSelectable(isSelectable);
}

void FfiOHOSAceFrameworkGridSupportAnimation(bool isSupportAnimation)
{
    GridModel::GetInstance()->SetSupportAnimation(isSupportAnimation);
}

void FfiOHOSAceFrameworkGridEdgeEffect(int32_t value, bool isEnabled)
{
    auto edgeEffect = value;
    if (edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(EdgeEffect::NONE);
    }
    GridModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect), isEnabled);
}

void FfiOHOSAceFrameworkGridEnableScrollInteraction(bool isEnable)
{
    GridModel::GetInstance()->SetScrollEnabled(isEnable);
}

void FfiOHOSAceFrameworkGridNestedScroll(int32_t forward, int32_t backward)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (forward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        forward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        forward = 0;
    }
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(forward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    GridModel::GetInstance()->SetNestedScroll(nestedOpt);
}

void FfiOHOSAceFrameworkGridFriction(double value)
{
    GridModel::GetInstance()->SetFriction(value);
}

void FfiOHOSAceFrameworkGridAlignItems(int32_t value)
{
    auto itemAlign = static_cast<GridItemAlignment>(value);
    if (itemAlign < GridItemAlignment::DEFAULT || itemAlign > GridItemAlignment::STRETCH) {
        itemAlign = GridItemAlignment::DEFAULT;
    }
    GridModel::GetInstance()->SetAlignItems(itemAlign);
}

void FfiOHOSAceFrameworkGridOnScrollIndex(void (*callback)(uint32_t))
{
    auto eventIndex = CJLambda::Create(callback);
    auto onScrollIndex = [eventIndex](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::GridEventInfo>(event);
        if (!eventInfo) {
            return;
        }
        eventIndex(eventInfo->GetScrollIndex());
    };
    GridModel::GetInstance()->SetOnScrollToIndex(onScrollIndex);
}

void FfiOHOSAceFrameworkGridOnScrollIndex2(void (*callback)(uint32_t first, uint32_t last))
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollIndex = [lambda](const int32_t first, const int32_t last) {
        lambda(first, last);
    };
    GridModel::GetInstance()->SetOnScrollIndex(onScrollIndex);
}

void FfiOHOSAceFrameworkGridOnItemDragStart(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragStart = [node = targetNode, lambda](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = {
            .x = x, .y = y
        };
        lambda(itemDragInfo, itemIndex);
    };
    GridModel::GetInstance()->SetOnItemDragStart(std::move(onItemDragStart));
}

void FfiOHOSAceFrameworkGridOnItemDragEnter(void (*callback)(CJItemDragInfo dragInfo))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragEnter = [node = targetNode, lambda](const ItemDragInfo& dragInfo) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = {
            .x = x, .y = y
        };
        lambda(itemDragInfo);
    };
    GridModel::GetInstance()->SetOnItemDragEnter(std::move(onItemDragEnter));
}

void FfiOHOSAceFrameworkGridOnItemDragMove(
    void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex, int32_t insertIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragMove = [node = targetNode, lambda](const ItemDragInfo& dragInfo,
        int32_t itemIndex, int32_t insertIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = {
            .x = x, .y = y
        };
        lambda(itemDragInfo, itemIndex, insertIndex);
    };
    GridModel::GetInstance()->SetOnItemDragMove(std::move(onItemDragMove));
}

void FfiOHOSAceFrameworkGridOnItemDragLeave(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragLeave = [node = targetNode, lambda](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = {
            .x = x, .y = y
        };
        lambda(itemDragInfo, itemIndex);
    };
    GridModel::GetInstance()->SetOnItemDragLeave(std::move(onItemDragLeave));
}

void FfiOHOSAceFrameworkGridOnItemDrop(void (*callback)(CJItemDragInfo dragInfo,
    int32_t itemIndex, int32_t insertIndex, bool isSuccess))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDrop = [node = targetNode, lambda](const ItemDragInfo& dragInfo,
        int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = {
            .x = x, .y = y
        };
        lambda(itemDragInfo, itemIndex, insertIndex, isSuccess);
    };
    GridModel::GetInstance()->SetOnItemDrop(std::move(onItemDrop));
}

void FfiOHOSAceFrameworkGridOnScrollBarUpdate(CJComputedBarAttribute (*callback)(int32_t index, double offset))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollBarUpdate = [node = targetNode, lambda](int32_t index, const Dimension& offset) {
        PipelineContext::SetCallBackNode(node);
        CJComputedBarAttribute result = lambda(index, offset.Value());
        Dimension totalOffset_ = Dimension { result.totalOffset, DimensionUnit::VP };
        Dimension totalLength_ = Dimension { result.totalLength, DimensionUnit::VP };
        return std::pair<float, float>(totalOffset_.ConvertToPx(), totalLength_.ConvertToPx());
    };
    GridModel::GetInstance()->SetOnScrollBarUpdate(std::move(onScrollBarUpdate));
}

void FfiOHOSAceFrameworkGridOnReachStart(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onReachStart = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    GridModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
}

void FfiOHOSAceFrameworkGridOnReachEnd(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onReachEnd = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    GridModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
}

void FfiOHOSAceFrameworkGridOnScrollFrameBegin(CJOffsetRemain (*callback)(double offset, int32_t state))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollBegin = [node = targetNode, lambda]
        (const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        PipelineContext::SetCallBackNode(node);
        auto result = lambda(offset.Value(), static_cast<int32_t>(state));
        ScrollFrameResult scrollRes { .offset = offset };
        scrollRes.offset = Dimension(result.offsetRemain, DimensionUnit::VP);
        return scrollRes;
    };
    GridModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
}

void FfiOHOSAceFrameworkGridOnScrollStart(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollStart = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    GridModel::GetInstance()->SetOnScrollStart(std::move(onScrollStart));
}

void FfiOHOSAceFrameworkGridOnScrollStop(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollStop = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    GridModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
}
}
