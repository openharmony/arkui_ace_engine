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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

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
}
