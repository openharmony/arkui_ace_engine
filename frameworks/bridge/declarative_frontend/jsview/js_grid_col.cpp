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
#include "core/components_v2/grid_layout/grid_col_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
RefPtr<V2::GridContainerSize> ParserGridContianerSize(const JSRef<JSVal>& jsValue, int32_t defalut)
{
    if (jsValue->IsNumber()) {
        double columnNumber = 0.0;
        JSViewAbstract::ParseJsDouble(jsValue, columnNumber);
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber);
        return gridContainerSize;
    } else if (jsValue->IsObject()) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(defalut);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        if (jsValue->IsObject()) {
            auto xs = gridParam->GetProperty("xs");
            if (xs->IsNumber() && xs->ToNumber<int32_t>() >= 0) {
                gridContainerSize->xs = xs->ToNumber<int32_t>();
            }
            auto sm = gridParam->GetProperty("sm");
            if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0) {
                gridContainerSize->sm = sm->ToNumber<int32_t>();
            }
            auto md = gridParam->GetProperty("md");
            if (md->IsNumber() && md->ToNumber<int32_t>() >= 0) {
                gridContainerSize->md = md->ToNumber<int32_t>();
            }
            auto lg = gridParam->GetProperty("lg");
            if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0) {
                gridContainerSize->lg = lg->ToNumber<int32_t>();
            }
            auto xl = gridParam->GetProperty("xl");
            if (xl->IsNumber() && xl->ToNumber<int32_t>() >= 0) {
                gridContainerSize->xl = xl->ToNumber<int32_t>();
            }
            auto xxl = gridParam->GetProperty("xxl");
            if (xxl->IsNumber() && xxl->ToNumber<int32_t>() >= 0) {
                gridContainerSize->xxl = xxl->ToNumber<int32_t>();
            }
        }
        return gridContainerSize;
    } else {
        LOGI("parse column error null or undefined");
        return AceType::MakeRefPtr<V2::GridContainerSize>(defalut);
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
    auto component = AceType::MakeRefPtr<V2::GridColComponent>();
    ViewStackProcessor::GetInstance()->Push(component);
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto gridParam = JSRef<JSObject>::Cast(info[0]);
        auto spanParam = gridParam->GetProperty("span");
        auto offsetParam = gridParam->GetProperty("offset");
        auto orderParam = gridParam->GetProperty("order");
        auto span = ParserGridContianerSize(spanParam, 1);
        auto offset = ParserGridContianerSize(offsetParam, 0);
        auto order = ParserGridContianerSize(orderParam, 0);
        component->SetSpan(span);
        component->SetOffset(offset);
        component->SetOrder(order);
    }
}

void JSGridCol::Span(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto span = ParserGridContianerSize(info[0], 1);
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
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetOrder(order);
    }
}

} // namespace OHOS::Ace::Framework
