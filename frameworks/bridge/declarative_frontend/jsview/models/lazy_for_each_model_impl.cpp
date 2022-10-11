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

#include "bridge/declarative_frontend/jsview/models/lazy_for_each_model_impl.h"

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_component.h"
#include "core/components_v2/tabs/tabs_component.h"

namespace OHOS::Ace::Framework {

void LazyForEachModelImpl::Create(const RefPtr<LazyForEachActuator>& actuator)
{
    auto component = AceType::DynamicCast<JSLazyForEachComponent>(actuator);

    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto tabsComponent = AceType::DynamicCast<V2::TabsComponent>(mainComponent);
    if (tabsComponent) {
        component->ExpandChildrenOnInitial();
    }
    ViewStackProcessor::GetInstance()->Push(component);
}

} // namespace OHOS::Ace::Framework
