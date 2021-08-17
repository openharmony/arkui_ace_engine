/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSGrid::Create()
{
    LOGD("Create component: Grid");
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    RefPtr<OHOS::Ace::GridLayoutComponent> gridComponent = AceType::MakeRefPtr<GridLayoutComponent>(componentChildren);
    ViewStackProcessor::GetInstance()->Push(gridComponent);
}

void JSGrid::SetColumnsTemplate(std::string value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetColumnsArgs(value);
    }
}

void JSGrid::SetRowsTemplate(std::string value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetRowsArgs(value);
    }
}

void JSGrid::SetColumnsGap(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetColumnGap(StringUtils::StringToDimension(value, true));
    }
}

void JSGrid::SetRowsGap(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetRowGap(StringUtils::StringToDimension(value, true));
    }
}

void JSGrid::JSBind(BindingTarget globalObj)
{
    LOGD("JSGrid:V8Bind");
    JSClass<JSGrid>::Declare("Grid");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSGrid>::StaticMethod("create", &JSGrid::Create, opt);
    JSClass<JSGrid>::StaticMethod("columnsTemplate", &JSGrid::SetColumnsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("rowsTemplate", &JSGrid::SetRowsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("columnsGap", &JSGrid::SetColumnsGap, opt);
    JSClass<JSGrid>::StaticMethod("rowsGap", &JSGrid::SetRowsGap, opt);
    JSClass<JSGrid>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGrid>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGrid>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGrid>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGrid>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSGrid>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);

    JSClass<JSGrid>::Inherit<JSContainerBase>();
    JSClass<JSGrid>::Inherit<JSViewAbstract>();
    JSClass<JSGrid>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
