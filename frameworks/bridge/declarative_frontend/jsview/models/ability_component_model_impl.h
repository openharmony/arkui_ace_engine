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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_ABILITY_COMPONENT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_ABILITY_COMPONENT_MODEL_IMPL_H

#include <functional>
#include <string>

#include "frameworks/core/components_ng/pattern/ability_component/ability_component_model.h"
#include "frameworks/core/components_v2/ability_component/ability_component.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT AbilityComponentModelImpl : public AbilityComponentModel {
public:
    void Create(const std::string& bundleName, const std::string& abilityName) override;
    void SetWant(const std::string& want) override;
    void SetOnConnect(std::function<void()>&& onConnect) override;
    void SetOnDisConnect(std::function<void()>&& onDisConnect) override;
    void SetWidth(Dimension value) override;
    void SetHeight(Dimension value) override;

private:
    static RefPtr<OHOS::Ace::V2::AbilityComponent> GetComponent();
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_ABILITY_COMPONENT_MODEL_IMPL_H
