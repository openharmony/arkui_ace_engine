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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_col.h"

#include <cstdint>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/grid_col/grid_col_view.h"
#include "core/components_v2/grid_layout/grid_col_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr size_t MAX_NUMBER_BREAKPOINT = 6;

void InheritGridContainerSize(const RefPtr<V2::GridContainerSize>& gridContainerSize,
    std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT], int32_t defaultVal)
{
    if (!containerSizeArray[0].has_value()) {
        containerSizeArray[0] = defaultVal;
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    gridContainerSize->xs = containerSizeArray[0].value();
    gridContainerSize->sm = containerSizeArray[1].value();
    gridContainerSize->md = containerSizeArray[2].value();
    gridContainerSize->lg = containerSizeArray[3].value();
    gridContainerSize->xl = containerSizeArray[4].value();
    gridContainerSize->xxl = containerSizeArray[5].value();
}

RefPtr<V2::GridContainerSize> ParserGridContianerSize(const JSRef<JSVal>& jsValue, int32_t defaultVal)
{
    if (jsValue->IsNumber()) {
        double columnNumber = 0.0;
        JSViewAbstract::ParseJsDouble(jsValue, columnNumber);
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber);
        return gridContainerSize;
    } else if (jsValue->IsObject()) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(defaultVal);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() >= 0) {
            containerSizeArray[0] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0) {
            containerSizeArray[1] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() >= 0) {
            containerSizeArray[2] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0) {
            containerSizeArray[3] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[4] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[5] = xxl->ToNumber<int32_t>();
        }
        InheritGridContainerSize(gridContainerSize, containerSizeArray, defaultVal);
        return gridContainerSize;
    } else {
        LOGI("parse column error null or undefined");
        return AceType::MakeRefPtr<V2::GridContainerSize>(defaultVal);
    }
}

} // namespace

void JSGridCol::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridCol>::Declare("GridCol");
    JSClass<JSGridCol>::StaticMethod("create", &JSGridCol::Create, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("span", &JSGridCol::Span, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("offset", &JSGridCol::Offset, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("order", &JSGridCol::Order, MethodOptions::NONE);
    JSClass<JSGridCol>::Inherit<JSContainerBase>();
    JSClass<JSGridCol>::Bind<>(globalObj);
}

void JSGridCol::Create(const JSCallbackInfo& info)
{
    bool isNewPipeline = Container::IsCurrentUseNewPipeline();

    if (info.Length() > 0 && info[0]->IsObject()) {
        auto gridParam = JSRef<JSObject>::Cast(info[0]);
        auto spanParam = gridParam->GetProperty("span");
        auto offsetParam = gridParam->GetProperty("offset");
        auto orderParam = gridParam->GetProperty("order");
        auto span = ParserGridContianerSize(spanParam, 1);
        auto offset = ParserGridContianerSize(offsetParam, 0);
        auto order = ParserGridContianerSize(orderParam, 0);

        if (isNewPipeline) {
            NG::GridColView::Create(span, offset, order);
        } else {
            auto component = AceType::MakeRefPtr<V2::GridColComponent>();
            ViewStackProcessor::GetInstance()->Push(component);
            component->SetSpan(span);
            component->SetOffset(offset);
            component->SetOrder(order);
        }
        return;
    }

    if (isNewPipeline) {
        NG::GridColView::Create();
    } else {
        auto component = AceType::MakeRefPtr<V2::GridColComponent>();
        ViewStackProcessor::GetInstance()->Push(component);
    }
}

void JSGridCol::Span(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto span = ParserGridContianerSize(info[0], 1);
    
    if (Container::IsCurrentUseNewPipeline()) {
        NG::GridColView::SetSpan(span);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetSpan(span);
    }
}

void JSGridCol::Offset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto offset = ParserGridContianerSize(info[0], 0);
    
    if (Container::IsCurrentUseNewPipeline()) {
        NG::GridColView::SetOffset(offset);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetOffset(offset);
    }
}

void JSGridCol::Order(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto order = ParserGridContianerSize(info[0], 0);
    
    if (Container::IsCurrentUseNewPipeline()) {
        NG::GridColView::SetOrder(order);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetOrder(order);
    }
}

} // namespace OHOS::Ace::Framework
