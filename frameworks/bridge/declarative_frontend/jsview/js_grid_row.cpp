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
#include "bridge/declarative_frontend/jsview/models/grid_row_model_impl.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"

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
        static Framework::GridRowModelImpl instance;
        return &instance;
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

void InheritGridColumns(const RefPtr<V2::GridContainerSize>& gridContainerSize,
    std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
{
    for (size_t i = 0; i < MAX_NUMBER_BREAKPOINT; ++i) {
        if (containerSizeArray[i].has_value()) {
            containerSizeArray[0] = containerSizeArray[i].value();
            break;
        }
    }
    CHECK_NULL_VOID(containerSizeArray[0].has_value());
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; ++i) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    gridContainerSize->xs = containerSizeArray[XS].value();
    gridContainerSize->sm = containerSizeArray[SM].value();
    gridContainerSize->md = containerSizeArray[MD].value();
    gridContainerSize->lg = containerSizeArray[LG].value();
    gridContainerSize->xl = containerSizeArray[XL].value();
    gridContainerSize->xxl = containerSizeArray[XXL].value();
}

void SaveGridRowGutterOptionxResObjXsSmMd(const RefPtr<V2::Gutter>& gutter,
    RefPtr<ResourceObject> (&gutterSizeArrayResObj)[MAX_NUMBER_BREAKPOINT])
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (gutterSizeArrayResObj[0]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xXs = result;
        };
        gutter->AddResource("gridrow.gutter.xXs", gutterSizeArrayResObj[0], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[1]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xSm = result;
        };
        gutter->AddResource("gridrow.gutter.xSm", gutterSizeArrayResObj[1], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_TOW]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xMd = result;
        };
        gutter->AddResource("gridrow.gutter.xMd", gutterSizeArrayResObj[PARAMS_NUM_TOW], std::move(updateFunc));
    }
}

void SaveGridRowGutterOptionxResObjLgXlXXl(const RefPtr<V2::Gutter>& gutter,
    RefPtr<ResourceObject> (&gutterSizeArrayResObj)[MAX_NUMBER_BREAKPOINT])
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_THREE]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xLg = result;
        };
        gutter->AddResource("gridrow.gutter.xLg", gutterSizeArrayResObj[PARAMS_NUM_THREE], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_FOUR]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xXl = result;
        };
        gutter->AddResource("gridrow.gutter.xXl", gutterSizeArrayResObj[PARAMS_NUM_FOUR], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_FIVE]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->xXXl = result;
        };
        gutter->AddResource("gridrow.gutter.xXXl", gutterSizeArrayResObj[PARAMS_NUM_FIVE], std::move(updateFunc));
    }
}

void SaveGridRowGutterOptionyResObjXsSmMd(const RefPtr<V2::Gutter>& gutter,
    RefPtr<ResourceObject> (&gutterSizeArrayResObj)[MAX_NUMBER_BREAKPOINT])
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (gutterSizeArrayResObj[0]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->yXs = result;
        };
        gutter->AddResource("gridrow.gutter.yXs", gutterSizeArrayResObj[0], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[1]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->ySm = result;
        };
        gutter->AddResource("gridrow.gutter.ySm", gutterSizeArrayResObj[1], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_TOW]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->yMd = result;
        };
        gutter->AddResource("gridrow.gutter.yMd", gutterSizeArrayResObj[PARAMS_NUM_TOW], std::move(updateFunc));
    }
}

void SaveGridRowGutterOptionyResObjLgXlXXl(const RefPtr<V2::Gutter>& gutter,
    RefPtr<ResourceObject> (&gutterSizeArrayResObj)[MAX_NUMBER_BREAKPOINT])
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_THREE]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->yLg = result;
        };
        gutter->AddResource("gridrow.gutter.yLg", gutterSizeArrayResObj[PARAMS_NUM_THREE], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_FOUR]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->yXl = result;
        };
        gutter->AddResource("gridrow.gutter.yXl", gutterSizeArrayResObj[PARAMS_NUM_FOUR], std::move(updateFunc));
    }
    if (gutterSizeArrayResObj[PARAMS_NUM_FIVE]) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, RefPtr<V2::Gutter>& gutter) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            gutter->yXXl = result;
        };
        gutter->AddResource("gridrow.gutter.yXXl", gutterSizeArrayResObj[PARAMS_NUM_FIVE], std::move(updateFunc));
    }
}

void InheritGridRowGutterOption(const RefPtr<V2::Gutter>& gutter,
    std::optional<CalcDimension> (&gutterSizeArray)[MAX_NUMBER_BREAKPOINT],
    RefPtr<ResourceObject> (&gutterSizeArrayResObj)[MAX_NUMBER_BREAKPOINT], bool isHorizontal)
{
    if (!gutterSizeArray[0].has_value()) {
        gutterSizeArray[0] = CalcDimension(0);
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!gutterSizeArray[i].has_value()) {
            gutterSizeArray[i] = gutterSizeArray[i - 1].value();
        }
        if (!gutterSizeArrayResObj[i]) {
            gutterSizeArrayResObj[i] = gutterSizeArrayResObj[i - 1];
        }
    }
    if (isHorizontal) {
        gutter->xXs = gutterSizeArray[0].value();
        gutter->xSm = gutterSizeArray[1].value();
        gutter->xMd = gutterSizeArray[2].value();
        gutter->xLg = gutterSizeArray[3].value();
        gutter->xXl = gutterSizeArray[4].value();
        gutter->xXXl = gutterSizeArray[5].value();
        SaveGridRowGutterOptionxResObjXsSmMd(gutter, gutterSizeArrayResObj);
        SaveGridRowGutterOptionxResObjLgXlXXl(gutter, gutterSizeArrayResObj);
        return;
    }
    gutter->yXs = gutterSizeArray[0].value();
    gutter->ySm = gutterSizeArray[1].value();
    gutter->yMd = gutterSizeArray[2].value();
    gutter->yLg = gutterSizeArray[3].value();
    gutter->yXl = gutterSizeArray[4].value();
    gutter->yXXl = gutterSizeArray[5].value();
    SaveGridRowGutterOptionyResObjXsSmMd(gutter, gutterSizeArrayResObj);
    SaveGridRowGutterOptionyResObjLgXlXXl(gutter, gutterSizeArrayResObj);
}

void ParseGutterObjectSub(const JSRef<JSVal>& gutterObject, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    std::optional<CalcDimension> gutterOptions[MAX_NUMBER_BREAKPOINT];
    RefPtr<ResourceObject> gutterOptionsResObj[MAX_NUMBER_BREAKPOINT];
    auto gutterParam = JSRef<JSObject>::Cast(gutterObject);
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
    
    InheritGridRowGutterOption(gutter, gutterOptions, gutterOptionsResObj, isHorizontal);
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
        } else {
            isHorizontal ? gutter->SetXGutter(dim) : gutter->SetYGutter(dim);
            return;
        }
    }
    if (!gutterObject->IsObject()) {
        return;
    }
    ParseGutterObjectSub(gutterObject, gutter, isHorizontal);
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
        InheritGridRowOption(gridContainerSize, containerSizeArray);
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
        InheritGridColumns(gridContainerSize, containerSizeArray);
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
