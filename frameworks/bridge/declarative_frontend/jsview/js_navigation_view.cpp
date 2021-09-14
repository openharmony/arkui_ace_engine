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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_view.h"

#include "core/components/navigation_bar/navigation_container_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSNavigationView::Create()
{
    auto navigationContainer = AceType::MakeRefPtr<NavigationContainerComponent>();
    ViewStackProcessor::GetInstance()->Push(navigationContainer);
}

void JSNavigationView::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigationView>::Declare("NavigationView");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNavigationView>::StaticMethod("create", &JSNavigationView::Create, opt);
    JSClass<JSNavigationView>::Inherit<JSContainerBase>();
    JSClass<JSNavigationView>::Inherit<JSViewAbstract>();
    JSClass<JSNavigationView>::Bind(globalObj);
}

} // namespace OHOS::Ace::Framework
