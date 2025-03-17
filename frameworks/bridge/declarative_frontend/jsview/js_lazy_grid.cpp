/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_grid.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"

namespace OHOS::Ace::Framework {
void JSLazyVGridLayout::Create()
{
    NG::LazyVGridLayoutModel::Create();
}

void JSLazyVGridLayout::JsRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension rowGap;
    if (!ParseLengthMetricsToDimension(info[0], rowGap) || rowGap.Value() < 0) {
        rowGap.SetValue(0.0);
    }
    NG::LazyGridLayoutModel::SetRowGap(rowGap);
}

void JSLazyVGridLayout::JsColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension colGap;
    if (!ParseLengthMetricsToDimension(info[0], colGap) || colGap.Value() < 0) {
        colGap.SetValue(0.0);
    }
    NG::LazyGridLayoutModel::SetColumnGap(colGap);
}

void JSLazyVGridLayout::JsColumnsTemplate(const std::string& value)
{
    NG::LazyVGridLayoutModel::SetColumnsTemplate(value);
}

void JSLazyVGridLayout::JSBind(BindingTarget globalObj)
{
    JSClass<JSLazyVGridLayout>::Declare("LazyVGridLayout");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSLazyVGridLayout>::StaticMethod("create", &JSLazyVGridLayout::Create, opt);
    JSClass<JSLazyVGridLayout>::StaticMethod("rowsGap", &JSLazyVGridLayout::JsRowsGap, opt);
    JSClass<JSLazyVGridLayout>::StaticMethod("columnsGap", &JSLazyVGridLayout::JsColumnsGap, opt);
    JSClass<JSLazyVGridLayout>::StaticMethod("columnsTemplate", &JSLazyVGridLayout::JsColumnsTemplate, opt);

    JSClass<JSLazyVGridLayout>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSLazyVGridLayout>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSLazyVGridLayout>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSLazyVGridLayout>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSLazyVGridLayout>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSLazyVGridLayout>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSLazyVGridLayout>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSLazyVGridLayout>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSLazyVGridLayout>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSLazyVGridLayout>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSLazyVGridLayout>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
