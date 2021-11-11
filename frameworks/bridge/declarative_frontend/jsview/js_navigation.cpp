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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigation.h"

#include "core/components/navigation_bar/navigation_container_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSNavigation::Create()
{
    auto navigationContainer = AceType::MakeRefPtr<NavigationContainerComponent>();
    ViewStackProcessor::GetInstance()->Push(navigationContainer);
}

void JSNavigation::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigation>::Declare("Navigation");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNavigation>::StaticMethod("create", &JSNavigation::Create, opt);
    JSClass<JSNavigation>::Inherit<JSContainerBase>();
    JSClass<JSNavigation>::Inherit<JSViewAbstract>();
    JSClass<JSNavigation>::Bind(globalObj);
}

} // namespace OHOS::Ace::Framework
