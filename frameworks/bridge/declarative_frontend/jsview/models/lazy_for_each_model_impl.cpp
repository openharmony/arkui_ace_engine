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
#include "core/common/dynamic_module_helper.h"
#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"

namespace OHOS::Ace::Framework {
namespace {
const ArkUIInnerTabsModifier* GetTabsInnerModifier()
{
    static const ArkUIInnerTabsModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tabs");
        CHECK_NULL_RETURN(loader, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIInnerTabsModifier*>(loader->GetCustomModifier());
    }
    return cachedModifier;
}
}

void LazyForEachModelImpl::Create(const RefPtr<LazyForEachActuator>& actuator)
{
    auto component = AceType::DynamicCast<JSLazyForEachComponent>(actuator);

    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto* modifier = GetTabsInnerModifier();
    if (modifier && modifier->isTabsComponent(mainComponent)) {
        component->ExpandChildrenOnInitial();
    }
    ViewStackProcessor::GetInstance()->Push(component);
}

} // namespace OHOS::Ace::Framework
