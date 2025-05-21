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

#include "bridge/declarative_frontend/jsview/js_water_flow_sections.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::Framework {
bool SetMarginProperty(const JSRef<JSObject>& paddingObj, NG::MarginProperty& margin)
{
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    JSViewAbstract::ParseMarginOrPaddingCorner(paddingObj, top, bottom, left, right);
    bool isMarginObject = false;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            margin.top = NG::CalcLength(top.value().CalcValue());
        } else {
            margin.top = NG::CalcLength(top.value());
        }
        isMarginObject = true;
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            margin.bottom = NG::CalcLength(bottom.value().CalcValue());
        } else {
            margin.bottom = NG::CalcLength(bottom.value());
        }
        isMarginObject = true;
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            margin.left = NG::CalcLength(left.value().CalcValue());
        } else {
            margin.left = NG::CalcLength(left.value());
        }
        isMarginObject = true;
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            margin.right = NG::CalcLength(right.value().CalcValue());
        } else {
            margin.right = NG::CalcLength(right.value());
        }
        isMarginObject = true;
    }
    return isMarginObject;
}

void ParseMargin(const JSRef<JSVal>& jsValue, NG::MarginProperty& margin)
{
    if (jsValue->IsObject()) {
        auto marginObj = JSRef<JSObject>::Cast(jsValue);
        if (SetMarginProperty(marginObj, margin)) {
            return;
        }
    }

    CalcDimension length;
    if (!JSViewAbstract::ParseJsDimensionVp(jsValue, length)) {
        length.Reset();
    }
    if (length.Unit() == DimensionUnit::CALC) {
        margin.SetEdges(NG::CalcLength(length.CalcValue()));
    } else {
        margin.SetEdges(NG::CalcLength(length));
    }
}

namespace {
void ParseGaps(const JSRef<JSObject>& obj, NG::WaterFlowSections::Section& section)
{
    if (obj->HasProperty("columnsGap")) {
        auto columnsGap = obj->GetProperty("columnsGap");
        CalcDimension colGap;
        if (!JSViewAbstract::ParseJsDimensionVp(columnsGap, colGap) || colGap.Value() < 0) {
            colGap.SetValue(0.0);
        }
        section.columnsGap = colGap;
    }

    if (obj->HasProperty("rowsGap")) {
        auto rowsGap = obj->GetProperty("rowsGap");
        CalcDimension rowGap;
        if (!JSViewAbstract::ParseJsDimensionVp(rowsGap, rowGap) || rowGap.Value() < 0) {
            rowGap.SetValue(0.0);
        }
        section.rowsGap = rowGap;
    }

    if (obj->HasProperty("margin")) {
        auto margin = obj->GetProperty("margin");
        NG::MarginProperty marginProperty;
        ParseMargin(margin, marginProperty);
        section.margin = marginProperty;
    }
}
} // namespace

bool JSWaterFlowSections::ParseSectionOptions(
    const JSCallbackInfo& args, const JSRef<JSVal>& jsValue, NG::WaterFlowSections::Section& section)
{
    if (!jsValue->IsObject()) {
        LOGW("The arg must be object");
        return false;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
    if (!obj->HasProperty("itemsCount")) {
        return false;
    }
    auto itemsCount = obj->GetProperty("itemsCount");
    JSViewAbstract::ParseJsInteger(itemsCount, section.itemsCount);
    if (section.itemsCount < 0) {
        LOGW("itemsCount can not be less than 0");
        return false;
    }

    if (obj->HasProperty("crossCount")) {
        auto crossCount = obj->GetProperty("crossCount");
        int32_t crossCountValue = 1;
        JSViewAbstract::ParseJsInteger(crossCount, crossCountValue);
        if (crossCountValue <= 0) {
            crossCountValue = 1;
        }
        section.crossCount = crossCountValue;
    }

    ParseGaps(obj, section);

    if (!obj->HasProperty("onGetItemMainSizeByIndex")) {
        return true;
    }
    auto getSizeByIndex = obj->GetProperty("onGetItemMainSizeByIndex");
    if (!getSizeByIndex->IsFunction()) {
        return true;
    }

    auto vm = args.GetVm();
    auto jsFunc = JSRef<JSFunc>::Cast(getSizeByIndex);
    auto func = jsFunc->GetLocalHandle();
    auto onGetItemMainSizeByIndex = [vm, func = panda::CopyableGlobal(vm, func)](int32_t index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, index) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (!result->IsNumber()) {
            return 0.0f;
        }

        return static_cast<float>(result->ToNumber(vm)->Value());
    };
    section.onGetItemMainSizeByIndex = std::move(onGetItemMainSizeByIndex);
    return true;
}
} // namespace OHOS::Ace::Framework
