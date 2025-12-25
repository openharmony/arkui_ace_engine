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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_col.h"

#include <cstdint>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/grid_col_model_impl.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"

namespace OHOS::Ace {
GridColModel* GridColModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::GridColModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::GridColModelNG instance;
        return &instance;
    } else {
        static Framework::GridColModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
constexpr size_t XS = 0;
constexpr size_t SM = 1;
constexpr size_t MD = 2;
constexpr size_t LG = 3;
constexpr size_t XL = 4;
constexpr size_t XXL = 5;
constexpr size_t MAX_NUMBER_BREAKPOINT = 6;

void InheritGridContainerSize(V2::GridContainerSize& gridContainerSize,
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
    gridContainerSize.xs = containerSizeArray[XS].value();
    gridContainerSize.sm = containerSizeArray[SM].value();
    gridContainerSize.md = containerSizeArray[MD].value();
    gridContainerSize.lg = containerSizeArray[LG].value();
    gridContainerSize.xl = containerSizeArray[XL].value();
    gridContainerSize.xxl = containerSizeArray[XXL].value();
}

void InheritGridSpans(
    V2::GridContainerSize& gridContainerSize, std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
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

    gridContainerSize.xs = containerSizeArray[XS].value();
    gridContainerSize.sm = containerSizeArray[SM].value();
    gridContainerSize.md = containerSizeArray[MD].value();
    gridContainerSize.lg = containerSizeArray[LG].value();
    gridContainerSize.xl = containerSizeArray[XL].value();
    gridContainerSize.xxl = containerSizeArray[XXL].value();
}

V2::GridContainerSize ParserGridContainerSize(const JSRef<JSVal>& jsValue, int32_t defaultVal)
{
    if (jsValue->IsNumber()) {
        double columnNumber = 0.0;
        JSViewAbstract::ParseJsDouble(jsValue, columnNumber);
        auto gridContainerSize = columnNumber >= 0 ? V2::GridContainerSize(columnNumber)
                                                   : V2::GridContainerSize(defaultVal);
        return gridContainerSize;
    } else if (jsValue->IsObject()) {
        auto gridContainerSize = V2::GridContainerSize(defaultVal);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XS] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0) {
            containerSizeArray[SM] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() >= 0) {
            containerSizeArray[MD] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0) {
            containerSizeArray[LG] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XL] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XXL] = xxl->ToNumber<int32_t>();
        }
        InheritGridContainerSize(gridContainerSize, containerSizeArray, defaultVal);
        return gridContainerSize;
    } else {
        return V2::GridContainerSize(defaultVal);
    }
}

V2::GridContainerSize ParserSpansNG(const JSRef<JSVal>& jsValue)
{
    if (jsValue->IsNumber()) {
        int32_t spanNumber = NG::DEFAULT_SPAN_NUMBER;
        JSViewAbstract::ParseJsInt32(jsValue, spanNumber);
        auto gridContainerSize =
            spanNumber >= 0 ? V2::GridContainerSize(spanNumber) : V2::GridContainerSize(NG::DEFAULT_SPAN_NUMBER);
        return gridContainerSize;
    }
    if (jsValue->IsObject()) {
        auto gridContainerSize = V2::GridContainerSize(NG::DEFAULT_SPAN_NUMBER);
        auto gridParam = JSRef<JSObject>::Cast(jsValue);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = gridParam->GetProperty("xs");
        if (xs->IsNumber() && xs->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XS] = xs->ToNumber<int32_t>();
        }
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0) {
            containerSizeArray[SM] = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() >= 0) {
            containerSizeArray[MD] = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0) {
            containerSizeArray[LG] = lg->ToNumber<int32_t>();
        }
        auto xl = gridParam->GetProperty("xl");
        if (xl->IsNumber() && xl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XL] = xl->ToNumber<int32_t>();
        }
        auto xxl = gridParam->GetProperty("xxl");
        if (xxl->IsNumber() && xxl->ToNumber<int32_t>() >= 0) {
            containerSizeArray[XXL] = xxl->ToNumber<int32_t>();
        }
        InheritGridSpans(gridContainerSize, containerSizeArray);
        return gridContainerSize;
    }
    return V2::GridContainerSize(NG::DEFAULT_SPAN_NUMBER);
}
} // namespace

void JSGridCol::Create(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto gridParam = JSRef<JSObject>::Cast(info[0]);
        auto spanParam = gridParam->GetProperty("span");
        auto offsetParam = gridParam->GetProperty("offset");
        auto orderParam = gridParam->GetProperty("order");
        V2::GridContainerSize span;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            span = ParserGridContainerSize(spanParam, 1);
        } else {
            span = ParserSpansNG(spanParam);
        }
        auto offset = ParserGridContainerSize(offsetParam, 0);
        auto order = ParserGridContainerSize(orderParam, 0);

        GridColModel::GetInstance()->Create(span, offset, order);
    } else {
        GridColModel::GetInstance()->Create();
    }
}

void JSGridCol::Span(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    V2::GridContainerSize span;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        span = ParserGridContainerSize(info[0], 1);
    } else {
        span = ParserSpansNG(info[0]);
    }
    GridColModel::GetInstance()->SetSpan(span);
}

void JSGridCol::Offset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto xVal = obj->GetProperty("x");
        auto yVal = obj->GetProperty("y");
        if (!xVal->IsUndefined() || !yVal->IsUndefined()) {
            JSViewAbstract::JsOffset(info);
            return;
        }
    }

    auto offset = ParserGridContainerSize(info[0], 0);
    GridColModel::GetInstance()->SetOffset(offset);
}

void JSGridCol::Order(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto order = ParserGridContainerSize(info[0], 0);
    GridColModel::GetInstance()->SetOrder(order);
}

void JSGridCol::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridCol>::Declare("GridCol");
    JSClass<JSGridCol>::StaticMethod("create", &JSGridCol::Create, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("span", &JSGridCol::Span, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("offset", &JSGridCol::Offset, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("gridColOffset", &JSGridCol::Offset, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("order", &JSGridCol::Order, MethodOptions::NONE);
    JSClass<JSGridCol>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSGridCol>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGridCol>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSGridCol>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGridCol>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGridCol>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
