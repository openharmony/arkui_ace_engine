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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_row.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/components_v2/grid_layout/grid_row_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
void ParserGutter(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent>& gridRow)
{
    Dimension result;
    if (JSContainerBase::ParseJsDimensionVp(jsValue, result)) {
        auto gutter = AceType::MakeRefPtr<V2::Getter>(result);
        gridRow->SetGetter(gutter);
    } else {
        if (!jsValue->IsObject()) {
            return;
        }
        auto paramGutter = JSRef<JSObject>::Cast(jsValue);
        auto xObject = paramGutter->GetProperty("x");
        auto yObject = paramGutter->GetProperty("y");
        auto gutter = AceType::MakeRefPtr<V2::Getter>();
        if (xObject->IsObject()) {
            auto xParamGutter = JSRef<JSObject>::Cast(xObject);
            auto xs = xParamGutter->GetProperty("xs");
            Dimension xsDimension;
            if (JSContainerBase::ParseJsDimensionVp(xs, xsDimension)) {
                gutter->xXs = xsDimension;
            }
            auto sm = xParamGutter->GetProperty("sm");
            Dimension xsmDimension;
            if (JSContainerBase::ParseJsDimensionVp(sm, xsDimension)) {
                gutter->xSm = xsmDimension;
            }
            auto md = xParamGutter->GetProperty("md");
            Dimension xmdDimension;
            if (JSContainerBase::ParseJsDimensionVp(md, xsDimension)) {
                gutter->xMd = xmdDimension;
            }
            auto lg = xParamGutter->GetProperty("lg");
            Dimension xlgDimension;
            if (JSContainerBase::ParseJsDimensionVp(lg, xlgDimension)) {
                gutter->xLg = xlgDimension;
            }
            auto xl = xParamGutter->GetProperty("xl");
            Dimension xxlDimension;
            if (JSContainerBase::ParseJsDimensionVp(xl, xxlDimension)) {
                gutter->xXl = xxlDimension;
            }
            auto xxl = xParamGutter->GetProperty("xxl");
            Dimension xxxlDimension;
            if (JSContainerBase::ParseJsDimensionVp(xxl, xxxlDimension)) {
                gutter->xXXl = xxxlDimension;
            }
        } else if (xObject->IsNumber()) {
            gutter->SetYGutter(Dimension(xObject->ToNumber<double>()));
        }
        if (yObject->IsObject()) {
            auto yParamGutter = JSRef<JSObject>::Cast(yObject);
            auto xs = yParamGutter->GetProperty("xs");
            Dimension xsDimension;
            if (JSContainerBase::ParseJsDimensionVp(xs, xsDimension)) {
                gutter->yXs = xsDimension;
            }
            auto sm = yParamGutter->GetProperty("sm");
            Dimension xsmDimension;
            if (JSContainerBase::ParseJsDimensionVp(sm, xsDimension)) {
                gutter->ySm = xsmDimension;
            }
            auto md = yParamGutter->GetProperty("md");
            Dimension xmdDimension;
            if (JSContainerBase::ParseJsDimensionVp(md, xsDimension)) {
                gutter->yMd = xmdDimension;
            }
            auto lg = yParamGutter->GetProperty("lg");
            Dimension xlgDimension;
            if (JSContainerBase::ParseJsDimensionVp(lg, xlgDimension)) {
                gutter->yLg = xlgDimension;
            }
            auto xl = yParamGutter->GetProperty("xl");
            Dimension xxlDimension;
            if (JSContainerBase::ParseJsDimensionVp(xl, xxlDimension)) {
                gutter->yXl = xxlDimension;
            }
            auto xxl = yParamGutter->GetProperty("xxl");
            Dimension xxxlDimension;
            if (JSContainerBase::ParseJsDimensionVp(xxl, xxxlDimension)) {
                gutter->yXXl = xxxlDimension;
            }
        } else if (yObject->IsNumber()) {
            gutter->SetYGutter(Dimension(yObject->ToNumber<double>()));
        }
        gridRow->SetGetter(gutter);
    }
}

void ParserColumns(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent> gridRow)
{
    if (jsValue->IsNumber()) {
        double columnNumber = 0.0;
        JSViewAbstract::ParseJsDouble(jsValue, columnNumber);
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber);
        gridRow->SetTotalCol(gridContainerSize);
    } else if (jsValue->IsObject()) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(12);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() > 0) {
            gridContainerSize->xs = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() > 0) {
            gridContainerSize->sm = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() > 0) {
            gridContainerSize->md = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() > 0) {
            gridContainerSize->lg = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() > 0) {
            gridContainerSize->xl = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() > 0) {
            gridContainerSize->xxl = xxl->ToNumber<int32_t>();
        }
        gridRow->SetTotalCol(gridContainerSize);
    } else {
        LOGI("parse column error");
    }
}

void ParserBreakpoints(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent> gridRow)
{
    auto breakpoints = JSRef<JSObject>::Cast(jsValue);
    auto value = breakpoints->GetProperty("value");
    auto reference = breakpoints->GetProperty("reference");
    auto breakpoint = AceType::MakeRefPtr<V2::BreakPoints>();
    if (!gridRow) {
        return;
    }
    if (value->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        breakpoint->breakpoints.clear();
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> thredhold = array->GetValueAt(i);
            if (thredhold->IsString()) {
                breakpoint->breakpoints.push_back(thredhold->ToString());
            }
        }
    }
    if (reference->IsNumber()) {
        if (reference->ToNumber<int32_t>() == 0) {
            breakpoint->reference = V2::BreakPointsReference::WindowSize;
        } else if (reference->ToNumber<int32_t>() == 1) {
            breakpoint->reference = V2::BreakPointsReference::ComponentSize;
        }
    }
    gridRow->SetBreakPoints(breakpoint);
}

void ParserDirection(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent> gridRow)
{
    if (gridRow && jsValue->IsNumber()) {
        int32_t value = jsValue->ToNumber<int32_t>();
        if (value == 0) {
            gridRow->SetDirection(V2::GridRowDirection::Row);
        } else if (value == 1) {
            gridRow->SetDirection(V2::GridRowDirection::RowReverse);
        } else {
            return;
        }
    }
}

} // namespace

void JSGridRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridRow>::Declare("GridRow");
    JSClass<JSGridRow>::StaticMethod("create", &JSGridRow::Create, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("columns", &JSGridRow::Columns, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("gutter", &JSGridRow::Gutter, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("breakpoints", &JSGridRow::Breakpoints, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("direction", &JSGridRow::Direction, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("onBreakpointChange", &JSGridRow::JsBreakpointEvent, MethodOptions::NONE);
    JSClass<JSGridRow>::Inherit<JSContainerBase>();
    JSClass<JSGridRow>::Bind<>(globalObj);
}

void JSGridRow::Create(const JSCallbackInfo& info)
{
    auto component = AceType::MakeRefPtr<V2::GridRowComponent>();
    ViewStackProcessor::GetInstance()->Push(component);
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto gridRow = JSRef<JSObject>::Cast(info[0]);
        auto columns = gridRow->GetProperty("columns");
        auto gutter = gridRow->GetProperty("gutter");
        auto breakpoints = gridRow->GetProperty("breakpoints");
        auto direction = gridRow->GetProperty("direction");
        ParserColumns(columns, component);
        ParserGutter(gutter, component);
        ParserBreakpoints(breakpoints, component);
        ParserDirection(direction, component);
    }
}

void JSGridRow::Columns(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<V2::GridRowComponent>(component);
    if (grid) {
        ParserColumns(info[0], grid);
    }
}
void JSGridRow::Gutter(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<V2::GridRowComponent>(component);
    if (grid) {
        ParserGutter(info[0], grid);
    }
}

void JSGridRow::Breakpoints(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<V2::GridRowComponent>(component);
    if (grid) {
        ParserBreakpoints(info[0], grid);
    }
}

void JSGridRow::Direction(const JSCallbackInfo& info)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<V2::GridRowComponent>(component);
    if (grid) {
        ParserDirection(info[0], grid);
    }
}

void JSGridRow::JsBreakpointEvent(const JSCallbackInfo& info)
{
    JSViewBindEvent(&V2::GridRowComponent::SetbreakPointChange, info);
}

} // namespace OHOS::Ace::Framework
