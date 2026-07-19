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

#include "cj_lambda.h"

#include "base/utils/utils.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_v2/grid/grid_event.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };
}

NG::GridModelNG* GetGridModel()
{
    static NG::GridModelNG* cachedModel = nullptr;
    if (!cachedModel) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Grid");
        if (module == nullptr) {
            LOGF_ABORT("Can't find Grid dynamic module");
        }
        cachedModel = reinterpret_cast<NG::GridModelNG*>(module->GetModel());
    }
    return cachedModel;
}

extern "C" {
void FfiOHOSAceFrameworkGridCreate()
{
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    if (GetGridModel()) {
        GetGridModel()->Create(positionController, scrollBarProxy);
    } else {
        LOGE("Grid Instance is null");
        return;
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
    if (GetGridModel()) {
        if (!scrollBarProxy) {
            scrollBarProxy = GetGridModel()->CreateScrollBarProxy();
            scroller->SetScrollBarProxy(scrollBarProxy);
        }
        RefPtr<ScrollControllerBase> positionController;
        positionController = GetGridModel()->CreatePositionController();
        scroller->SetController(positionController);
        GetGridModel()->Create(positionController, scrollBarProxy);
    }
}

void FfiOHOSAceFrameworkGridSetCachedCount(int32_t cachedCount)
{
    if (GetGridModel()) {
        GetGridModel()->SetCachedCount(cachedCount);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridColumnsTemplate(const char* value)
{
    if (GetGridModel()) {
        GetGridModel()->SetColumnsTemplate(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridRowsTemplate(const char* value)
{
    if (GetGridModel()) {
        GetGridModel()->SetRowsTemplate(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridColumnsGapWithString(const char* value)
{
    Dimension valueFFI;
    // use default 'DimensionUnit::VP', 'vp' -> the value varies with pixel density of device.
    valueFFI = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP);
    if (GetGridModel()) {
        GetGridModel()->SetColumnsGap(valueFFI);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridColumnsGapWithNum(int32_t value)
{
    Dimension valueFFI = Dimension(value, DimensionUnit::VP);
    if (GetGridModel()) {
        GetGridModel()->SetColumnsGap(valueFFI);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridRowsGapWithString(const char* value)
{
    Dimension valueFFI;
    // use default 'VP', 'vp' -> the value varies with pixel density of device.
    valueFFI = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP);
    if (GetGridModel()) {
        GetGridModel()->SetRowsGap(valueFFI);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridRowsGapWithNum(int32_t value)
{
    Dimension valueFFI = Dimension(value, DimensionUnit::VP);
    if (GetGridModel()) {
        GetGridModel()->SetRowsGap(valueFFI);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridScrollBar(int32_t value)
{
    auto displayMode = static_cast<DisplayMode>(value);
    if (GetGridModel()) {
        GetGridModel()->SetScrollBarMode(displayMode);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridScrollBarColor(uint32_t color)
{
    if (GetGridModel()) {
        GetGridModel()->SetScrollBarColor(Color(color).ColorToString());
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridScrollBarWidth(double value, int32_t valueUnit)
{
    Dimension dimWidth(value, static_cast<DimensionUnit>(valueUnit));
    CalcDimension scrollBarWidth = CalcDimension(dimWidth);
    if (scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        return;
    }
    if (GetGridModel()) {
        GetGridModel()->SetScrollBarWidth(scrollBarWidth.ToString());
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridCachedCount(int32_t cacheCount, bool show)
{
    if (cacheCount < 0) {
        cacheCount = 1;
    }
    if (GetGridModel()) {
        GetGridModel()->SetCachedCount(cacheCount, show);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridEditMode(bool isEditMode)
{
    if (GetGridModel()) {
        GetGridModel()->SetEditable(isEditMode);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridLayoutDirection(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        return;
    }
    if (GetGridModel()) {
        GetGridModel()->SetLayoutDirection(LAYOUT_DIRECTION[value]);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridMaxCount(int32_t value)
{
    if (value < 1) {
        value = Infinity<int32_t>();
    }
    if (GetGridModel()) {
        GetGridModel()->SetMaxCount(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridMinCount(int32_t value)
{
    if (value < 1) {
        value = 1;
    }
    if (GetGridModel()) {
        GetGridModel()->SetMinCount(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridCellLength(int32_t value)
{
    if (GetGridModel()) {
        GetGridModel()->SetCellLength(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridMultiSelectable(bool isSelectable)
{
    if (GetGridModel()) {
        GetGridModel()->SetMultiSelectable(isSelectable);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridSupportAnimation(bool isSupportAnimation)
{
    if (GetGridModel()) {
        GetGridModel()->SetSupportAnimation(isSupportAnimation);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridEdgeEffect(int32_t value, bool isEnabled)
{
    auto edgeEffect = value;
    if (edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(EdgeEffect::NONE);
    }
    if (GetGridModel()) {
        GetGridModel()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect), isEnabled);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridEnableScrollInteraction(bool isEnable)
{
    if (GetGridModel()) {
        GetGridModel()->SetScrollEnabled(isEnable);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
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
    if (GetGridModel()) {
        GetGridModel()->SetNestedScroll(nestedOpt);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridFriction(double value)
{
    if (GetGridModel()) {
        GetGridModel()->SetFriction(value);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridAlignItems(int32_t value)
{
    auto itemAlign = static_cast<GridItemAlignment>(value);
    if (itemAlign < GridItemAlignment::DEFAULT || itemAlign > GridItemAlignment::STRETCH) {
        itemAlign = GridItemAlignment::DEFAULT;
    }
    if (GetGridModel()) {
        GetGridModel()->SetAlignItems(itemAlign);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
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
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollToIndex(onScrollIndex);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnScrollIndex2(void (*callback)(uint32_t first, uint32_t last))
{
    auto lambda = CJLambda::Create(callback);
    auto onScrollIndex = [lambda](const int32_t first, const int32_t last) { lambda(first, last); };
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollIndex(onScrollIndex);
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDragStart(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragStart = [node = targetNode, lambda](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        lambda(itemDragInfo, itemIndex);
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDragStart(std::move(onItemDragStart));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDragStartWithBack(
    CJDragItemInfo (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragStart = [node = targetNode, lambda](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        LOGI("FfiOHOSAceFrameworkGridOnItemDragStartWithBack lambda start");
        auto ret = lambda(itemDragInfo, itemIndex);
        if (ret.builder == nullptr) {
            LOGE("FfiOHOSAceFrameworkGridOnItemDragStartWithBack lambda ret is nullptr");
            return;
        }

        std::function<void(void)> builderFunc = CJLambda::Create(ret.builder);
        // use another VSP instance while executing the builder function
        PipelineContext::SetCallBackNode(node);
        builderFunc();
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDragStart(std::move(onItemDragStart));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDragEnter(void (*callback)(CJItemDragInfo dragInfo))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragEnter = [node = targetNode, lambda](const ItemDragInfo& dragInfo) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        lambda(itemDragInfo);
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDragEnter(std::move(onItemDragEnter));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDragMove(
    void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex, int32_t insertIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragMove = [node = targetNode, lambda](
                              const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        lambda(itemDragInfo, itemIndex, insertIndex);
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDragMove(std::move(onItemDragMove));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDragLeave(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDragLeave = [node = targetNode, lambda](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        lambda(itemDragInfo, itemIndex);
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDragLeave(std::move(onItemDragLeave));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnItemDrop(
    void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onItemDrop = [node = targetNode, lambda](
                          const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        PipelineContext::SetCallBackNode(node);
        auto x = dragInfo.GetX();
        auto y = dragInfo.GetY();
        CJItemDragInfo itemDragInfo = { .x = x, .y = y };
        lambda(itemDragInfo, itemIndex, insertIndex, isSuccess);
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnItemDrop(std::move(onItemDrop));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
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
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollBarUpdate(std::move(onScrollBarUpdate));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnReachStart(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onReachStart = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnReachStart(std::move(onReachStart));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnReachEnd(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onReachEnd = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnReachEnd(std::move(onReachEnd));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnScrollFrameBegin(CJOffsetRemain (*callback)(double offset, int32_t state))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollBegin = [node = targetNode, lambda](
                             const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        PipelineContext::SetCallBackNode(node);
        auto result = lambda(offset.Value(), static_cast<int32_t>(state));
        ScrollFrameResult scrollRes { .offset = Dimension(result.offsetRemain, DimensionUnit::VP) };
        return scrollRes;
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollFrameBegin(std::move(onScrollBegin));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnScrollStart(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollStart = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollStart(std::move(onScrollStart));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}

void FfiOHOSAceFrameworkGridOnScrollStop(void (*callback)())
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onScrollStop = [node = targetNode, lambda]() {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    if (GetGridModel()) {
        GetGridModel()->SetOnScrollStop(std::move(onScrollStop));
    } else {
        LOGE("Grid Instance is null");
        return;
    }
}
}
