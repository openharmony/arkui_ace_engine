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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

#include "core/components_ng/base/view_stack_model.h"


namespace OHOS::Ace::Framework {
void JSContainerBase::Pop()
{
    ViewStackModel::GetInstance()->PopContainer();
}

void JSContainerBase::JSBind(BindingTarget globalObj)
{
    JSClass<JSContainerBase>::Declare("JSContainerBase");
    // staticmethods
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSContainerBase>::StaticMethod("pop", &JSContainerBase::Pop, opt);
    JSClass<JSContainerBase>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
