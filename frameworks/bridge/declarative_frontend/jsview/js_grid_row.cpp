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

constexpr size_t MAX_NUMBER_BREAKPOINT = 6;

void InheritGridRowOption(const RefPtr<V2::GridContainerSize>& gridContainerSize,
    std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
{
    if (!containerSizeArray[0].has_value()) {
        containerSizeArray[0] = V2::DEFAULT_COLUMN_NUMBER;
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

void InheritGridRowGutterOption(const RefPtr<V2::Gutter>& gutter,
    std::optional<Dimension> (&gutterSizeArray)[MAX_NUMBER_BREAKPOINT], bool isHorizontal)
{
    if (!gutterSizeArray[0].has_value()) {
        gutterSizeArray[0] = Dimension(0);
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!gutterSizeArray[i].has_value()) {
            gutterSizeArray[i] = gutterSizeArray[i - 1].value();
        }
    }
    if (isHorizontal) {
        gutter->xXs = gutterSizeArray[0].value();
        gutter->xSm = gutterSizeArray[1].value();
        gutter->xMd = gutterSizeArray[2].value();
        gutter->xLg = gutterSizeArray[3].value();
        gutter->xXl = gutterSizeArray[4].value();
        gutter->xXXl = gutterSizeArray[5].value();
        return;
    }
    gutter->yXs = gutterSizeArray[0].value();
    gutter->ySm = gutterSizeArray[1].value();
    gutter->yMd = gutterSizeArray[2].value();
    gutter->yLg = gutterSizeArray[3].value();
    gutter->yXl = gutterSizeArray[4].value();
    gutter->yXXl = gutterSizeArray[5].value();
}

void ParseGutterObject(const JSRef<JSVal>& gutterObject, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    if (gutterObject->IsObject()) {
        std::optional<Dimension> gutterOptions[MAX_NUMBER_BREAKPOINT];
        auto gutterParam = JSRef<JSObject>::Cast(gutterObject);
        auto xs = gutterParam->GetProperty("xs");
        Dimension xsDimension;
        if (JSContainerBase::ParseJsDimensionVp(xs, xsDimension)) {
            gutterOptions[0] = xsDimension;
        }
        auto sm = gutterParam->GetProperty("sm");
        Dimension smDimension;
        if (JSContainerBase::ParseJsDimensionVp(sm, smDimension)) {
            gutterOptions[1] = smDimension;
        }
        auto md = gutterParam->GetProperty("md");
        Dimension mdDimension;
        if (JSContainerBase::ParseJsDimensionVp(md, mdDimension)) {
            gutterOptions[2] = mdDimension;
        }
        auto lg = gutterParam->GetProperty("lg");
        Dimension lgDimension;
        if (JSContainerBase::ParseJsDimensionVp(lg, lgDimension)) {
            gutterOptions[3] = lgDimension;
        }
        auto xl = gutterParam->GetProperty("xl");
        Dimension xlDimension;
        if (JSContainerBase::ParseJsDimensionVp(xl, xlDimension)) {
            gutterOptions[4] = xlDimension;
        }
        auto xxl = gutterParam->GetProperty("xxl");
        Dimension xxlDimension;
        if (JSContainerBase::ParseJsDimensionVp(xxl, xxlDimension)) {
            gutterOptions[5] = xxlDimension;
        }
        InheritGridRowGutterOption(gutter, gutterOptions, isHorizontal);
    } else if (gutterObject->IsNumber()) {
        if (isHorizontal) {
            gutter->SetXGutter(Dimension(gutterObject->ToNumber<double>()));
        } else {
            gutter->SetYGutter(Dimension(gutterObject->ToNumber<double>()));
        }
    }
}

void ParserGutter(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent>& gridRow)
{
    Dimension result;
    if (JSContainerBase::ParseJsDimensionVp(jsValue, result)) {
        auto gutter = AceType::MakeRefPtr<V2::Gutter>(result);
        gridRow->SetGutter(gutter);
    } else {
        if (!jsValue->IsObject()) {
            return;
        }
        auto paramGutter = JSRef<JSObject>::Cast(jsValue);
        auto xObject = paramGutter->GetProperty("x");
        auto yObject = paramGutter->GetProperty("y");
        auto gutter = AceType::MakeRefPtr<V2::Gutter>();
        ParseGutterObject(xObject, gutter, true);
        ParseGutterObject(yObject, gutter, false);
        gridRow->SetGutter(gutter);
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
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() > 0) {
            containerSizeArray[0] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() > 0) {
            containerSizeArray[1] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() > 0) {
            containerSizeArray[2] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() > 0) {
            containerSizeArray[3] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() > 0) {
            containerSizeArray[4] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() > 0) {
            containerSizeArray[5] = xxl->ToNumber<int32_t>();
        }
        InheritGridRowOption(gridContainerSize, containerSizeArray);
        gridRow->SetTotalCol(gridContainerSize);
    } else {
        LOGI("parse column error");
    }
}

void ParserBreakpoints(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent> gridRow)
{
    if (!jsValue->IsObject()) {
        return;
    }
    auto breakpoints = JSRef<JSObject>::Cast(jsValue);
    auto value = breakpoints->GetProperty("value");
    auto reference = breakpoints->GetProperty("reference");
    auto breakpoint = AceType::MakeRefPtr<V2::BreakPoints>();
    if (!gridRow) {
        return;
    }
    if (reference->IsNumber()) {
        breakpoint->reference = static_cast<V2::BreakPointsReference>(reference->ToNumber<int32_t>());
    }
    if (value->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(value);
        breakpoint->breakpoints.clear();
        if (array->Length() > MAX_NUMBER_BREAKPOINT - 1) {
            LOGI("The maximum number of breakpoints is %{public}zu", MAX_NUMBER_BREAKPOINT);
            gridRow->SetBreakPoints(breakpoint);
            return;
        }
        double width = -1.0;
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> threshold = array->GetValueAt(i);
            if (threshold->IsString() || threshold->IsNumber()) {
                Dimension valueDimension;
                JSContainerBase::ParseJsDimensionVp(threshold, valueDimension);
                if (GreatNotEqual(width, valueDimension.Value())) {
                    LOGI("Array data must be sorted in ascending order");
                    gridRow->SetBreakPoints(breakpoint);
                    return;
                }
                width = valueDimension.Value();
                breakpoint->breakpoints.push_back(threshold->ToString());
            }
        }
    }
    gridRow->SetBreakPoints(breakpoint);
}

void ParserDirection(const JSRef<JSVal>& jsValue, RefPtr<V2::GridRowComponent> gridRow)
{
    if (gridRow && jsValue->IsNumber()) {
        gridRow->SetDirection(static_cast<V2::GridRowDirection>(jsValue->ToNumber<int32_t>()));
    }
}

} // namespace

void JSGridRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridRow>::Declare("GridRow");
    JSClass<JSGridRow>::StaticMethod("create", &JSGridRow::Create, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("height", &JSGridRow::Height, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("columns", &JSGridRow::Columns, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("gutter", &JSGridRow::Gutter, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("breakpoints", &JSGridRow::Breakpoints, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("direction", &JSGridRow::Direction, MethodOptions::NONE);
    JSClass<JSGridRow>::StaticMethod("onBreakpointChange", &JSGridRow::JsBreakpointEvent, MethodOptions::NONE);
    JSClass<JSGridRow>::Inherit<JSContainerBase>();
    JSClass<JSGridRow>::Bind<>(globalObj);
}

void JSGridRow::Height(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    JSViewAbstract::JsHeight(info[0]);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<V2::GridRowComponent>(component);
    if (grid) {
        grid->SetHasContainerHeight(true);
    }
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
