/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace {
GridRowModel* GridRowModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::GridRowModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::GridRowModelNG instance;
        return &instance;
    } else {
        static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("grid_row");
        static GridRowModel* instance = loader ? reinterpret_cast<GridRowModel*>(loader->CreateModel()) : nullptr;
        return instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

constexpr size_t MAX_NUMBER_BREAKPOINT = 6;
constexpr size_t XS = 0;
constexpr size_t SM = 1;
constexpr size_t MD = 2;
constexpr size_t LG = 3;
constexpr size_t XL = 4;
constexpr size_t XXL = 5;
constexpr int32_t PARAMS_NUM_TOW = 2;
constexpr int32_t PARAMS_NUM_THREE = 3;
constexpr int32_t PARAMS_NUM_FOUR = 4;
constexpr int32_t PARAMS_NUM_FIVE = 5;

void ParseGutterObjectSub(const JSRef<JSObject>& gutterParam, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    std::optional<CalcDimension> gutterOptions[MAX_NUMBER_BREAKPOINT];
    RefPtr<ResourceObject> gutterOptionsResObj[MAX_NUMBER_BREAKPOINT];
    auto xs = gutterParam->GetProperty("xs");
    CalcDimension xsDimension;
    RefPtr<ResourceObject> xsDimensionResObj;
    if (JSContainerBase::ParseJsDimensionVp(xs, xsDimension, xsDimensionResObj)) {
        gutterOptions[0] = xsDimension;
    }
    auto sm = gutterParam->GetProperty("sm");
    CalcDimension smDimension;
    RefPtr<ResourceObject> smDimensionnResObj;
    if (JSContainerBase::ParseJsDimensionVp(sm, smDimension, smDimensionnResObj)) {
        gutterOptions[1] = smDimension;
    }
    auto md = gutterParam->GetProperty("md");
    CalcDimension mdDimension;
    RefPtr<ResourceObject> mdDimensionResObj;
    if (JSContainerBase::ParseJsDimensionVp(md, mdDimension, mdDimensionResObj)) {
        gutterOptions[PARAMS_NUM_TOW] = mdDimension;
    }
    auto lg = gutterParam->GetProperty("lg");
    CalcDimension lgDimension;
    RefPtr<ResourceObject> lgDimensionResObj;
    if (JSContainerBase::ParseJsDimensionVp(lg, lgDimension, lgDimensionResObj)) {
        gutterOptions[PARAMS_NUM_THREE] = lgDimension;
    }
    auto xl = gutterParam->GetProperty("xl");
    CalcDimension xlDimension;
    RefPtr<ResourceObject> xlDimensionResObj;
    if (JSContainerBase::ParseJsDimensionVp(xl, xlDimension, xlDimensionResObj)) {
        gutterOptions[PARAMS_NUM_FOUR] = xlDimension;
    }
    auto xxl = gutterParam->GetProperty("xxl");
    CalcDimension xxlDimension;
    RefPtr<ResourceObject> xxlDimensionResObj;
    if (JSContainerBase::ParseJsDimensionVp(xxl, xxlDimension, xxlDimensionResObj)) {
        gutterOptions[PARAMS_NUM_FIVE] = xxlDimension;
    }
    if (SystemProperties::ConfigChangePerform()) {
        gutterOptionsResObj[0] = xsDimensionResObj;
        gutterOptionsResObj[1] = smDimensionnResObj;
        gutterOptionsResObj[PARAMS_NUM_TOW] = mdDimensionResObj;
        gutterOptionsResObj[PARAMS_NUM_THREE] = lgDimensionResObj;
        gutterOptionsResObj[PARAMS_NUM_FOUR] = xlDimensionResObj;
        gutterOptionsResObj[PARAMS_NUM_FIVE] = xxlDimensionResObj;
    }
    
    V2::GridContainerUtils::InheritGridRowGutterOption(gutter, gutterOptions, gutterOptionsResObj, isHorizontal);
}

void SetXGutterResObj(RefPtr<ResourceObject> xDimension, RefPtr<V2::Gutter>& gutter)
{
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
        gutter->xXs = result;
        gutter->xSm = result;
        gutter->xMd = result;
        gutter->xLg = result;
        gutter->xXl = result;
        gutter->xXXl = result;
    };
    gutter->AddResource("gridrow.gutter.x", xDimension, std::move(updateFunc));
}

void SetYGutterResObj(RefPtr<ResourceObject> yDimension, RefPtr<V2::Gutter>& gutter)
{
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
        gutter->yXs = result;
        gutter->ySm = result;
        gutter->yMd = result;
        gutter->yLg = result;
        gutter->yXl = result;
        gutter->yXXl = result;
    };
    gutter->AddResource("gridrow.gutter.y", yDimension, std::move(updateFunc));
}

void ParseGutterObject(const JSRef<JSVal>& gutterObject, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    CalcDimension dim;
    RefPtr<ResourceObject> dimResObj;
    if (JSContainerBase::ParseJsDimensionVp(gutterObject, dim, dimResObj)) {
        if (SystemProperties::ConfigChangePerform() && dimResObj) {
            isHorizontal ? SetXGutterResObj(dimResObj, gutter) : SetYGutterResObj(dimResObj, gutter);
        }
        isHorizontal ? gutter->SetXGutter(dim) : gutter->SetYGutter(dim);
        return;
    }
    if (!gutterObject->IsObject()) {
        return;
    }
    auto gutterParam = JSRef<JSObject>::Cast(gutterObject);
    ParseGutterObjectSub(gutterParam, gutter, isHorizontal);
}

RefPtr<V2::Gutter> ParserGutter(const JSRef<JSVal>& jsValue)
{
    CalcDimension result;
    if (JSContainerBase::ParseJsDimensionVp(jsValue, result)) {
        auto gutter = AceType::MakeRefPtr<V2::Gutter>(result);
        return gutter;
    } else {
        if (!jsValue->IsObject()) {
            return AceType::MakeRefPtr<V2::Gutter>();
        }
        auto paramGutter = JSRef<JSObject>::Cast(jsValue);
        auto xObject = paramGutter->GetProperty("x");
        auto yObject = paramGutter->GetProperty("y");
        auto gutter = AceType::MakeRefPtr<V2::Gutter>();
        ParseGutterObject(xObject, gutter, true);
        ParseGutterObject(yObject, gutter, false);
        return gutter;
    }
}

RefPtr<V2::GridContainerSize> ParserColumns(const JSRef<JSVal>& jsValue)
{
    if (jsValue->IsNumber()) {
        auto columnNumber = jsValue->ToNumber<int32_t>();
        return columnNumber > 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber)
                                : AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
    } else if (jsValue->IsObject()) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() > 0) {
            containerSizeArray[XS] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() > 0) {
            containerSizeArray[SM] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() > 0) {
            containerSizeArray[MD] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() > 0) {
            containerSizeArray[LG] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() > 0) {
            containerSizeArray[XL] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() > 0) {
            containerSizeArray[XXL] = xxl->ToNumber<int32_t>();
        }
        V2::GridContainerUtils::InheritGridRowOption(gridContainerSize, containerSizeArray);
        return gridContainerSize;
    } else {
        return AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
    }
}

RefPtr<V2::GridContainerSize> ParserColumnsNG(const JSRef<JSVal>& jsValue)
{
    if (jsValue->IsNumber()) {
        auto columnNumber = jsValue->ToNumber<int32_t>();
        return columnNumber > 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(columnNumber)
                                : AceType::MakeRefPtr<V2::GridContainerSize>();
    }
    if (jsValue->IsObject()) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() > 0) {
            containerSizeArray[XS] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() > 0) {
            containerSizeArray[SM] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() > 0) {
            containerSizeArray[MD] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() > 0) {
            containerSizeArray[LG] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() > 0) {
            containerSizeArray[XL] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() > 0) {
            containerSizeArray[XXL] = xxl->ToNumber<int32_t>();
        }
        V2::GridContainerUtils::InheritGridColumns(gridContainerSize, containerSizeArray);
        return gridContainerSize;
    }
    return AceType::MakeRefPtr<V2::GridContainerSize>();
}

RefPtr<V2::BreakPoints> ParserBreakpoints(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return AceType::MakeRefPtr<V2::BreakPoints>();
    }
    auto breakpoints = JSRef<JSObject>::Cast(jsValue);
    auto value = breakpoints->GetProperty("value");
    auto reference = breakpoints->GetProperty("reference");
    auto breakpoint = AceType::MakeRefPtr<V2::BreakPoints>();
    if (reference->IsNumber()) {
        breakpoint->reference = static_cast<V2::BreakPointsReference>(reference->ToNumber<int32_t>());
    }
    if (value->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(value);
        breakpoint->breakpoints.clear();
        if (array->Length() > MAX_NUMBER_BREAKPOINT - 1) {
            return breakpoint;
        }
        double width = -1.0;
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> threshold = array->GetValueAt(i);
            if (threshold->IsString() || threshold->IsNumber()) {
                CalcDimension valueDimension;
                JSContainerBase::ParseJsDimensionVp(threshold, valueDimension);
                breakpoint->userDefine = true;
                if (GreatNotEqual(width, valueDimension.Value())) {
                    return breakpoint;
                }
                width = valueDimension.Value();
                breakpoint->breakpoints.push_back(threshold->ToString());
            }
        }
    }
    return breakpoint;
}

V2::GridRowDirection ParserDirection(const JSRef<JSVal>& jsValue)
{
    V2::GridRowDirection direction(V2::GridRowDirection::Row);
    if (jsValue->IsNumber()) {
        direction = static_cast<V2::GridRowDirection>(jsValue->ToNumber<int32_t>());
    }
    return direction;
}

} // namespace

void JSGridRow::Create(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        auto gridRow = JSRef<JSObject>::Cast(info[0]);
        auto columns = gridRow->GetProperty("columns");
        auto gutter = gridRow->GetProperty("gutter");
        auto breakpoints = gridRow->GetProperty("breakpoints");
        auto direction = gridRow->GetProperty("direction");

        RefPtr<V2::GridContainerSize> parsedColumns;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            parsedColumns = ParserColumns(columns);
        } else {
            parsedColumns = ParserColumnsNG(columns);
        }
        auto parsedGutter = ParserGutter(gutter);
        auto parsedBreakpoints = ParserBreakpoints(breakpoints);
        auto parsedDirection = ParserDirection(direction);
        GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
    } else {
        GridRowModel::GetInstance()->Create();
    }
}

void JSGridRow::JsBreakpointEvent(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onBreakpointChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                  const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("GridRow.onBreakpointChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS(1, &newJSVal);
    };
    GridRowModel::GetInstance()->SetOnBreakPointChange(onBreakpointChange);
}

void JSGridRow::Height(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info[0]);
    GridRowModel::GetInstance()->SetHeight();
}

void JSGridRow::AlignItems(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber()) {
        auto value = info[0]->ToNumber<int32_t>();
        ParseAlignItems(value);
    } else if (info[0]->IsUndefined()) {
        GridRowModel::GetInstance()->SetAlignItems(FlexAlign::FLEX_START);
    }
}

void JSGridRow::ParseAlignItems(int32_t alignItem)
{
    if (alignItem == static_cast<int32_t>(FlexAlign::FLEX_START) ||
        alignItem == static_cast<int32_t>(FlexAlign::FLEX_END) ||
        alignItem == static_cast<int32_t>(FlexAlign::CENTER) || alignItem == static_cast<int32_t>(FlexAlign::STRETCH)) {
        GridRowModel::GetInstance()->SetAlignItems(static_cast<FlexAlign>(alignItem));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        GridRowModel::GetInstance()->SetAlignItems(FlexAlign::FLEX_START);
    }
}

void JSGridRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridRow>::Declare("GridRow");
    JSClass<JSGridRow>::StaticMethod("create", &JSGridRow::Create);
    JSClass<JSGridRow>::StaticMethod("onBreakpointChange", &JSGridRow::JsBreakpointEvent);
    JSClass<JSGridRow>::StaticMethod("height", &JSGridRow::Height);
    JSClass<JSGridRow>::StaticMethod("alignItems", &JSGridRow::AlignItems);
    JSClass<JSGridRow>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSGridRow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGridRow>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSGridRow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGridRow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGridRow>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
