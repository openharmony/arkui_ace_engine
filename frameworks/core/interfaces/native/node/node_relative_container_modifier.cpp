/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/node/node_relative_container_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {
const ArkUIRelativeContainerModifier* GetRelativeContainerModifier()
{
    static const ArkUIRelativeContainerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("RelativeContainer");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIRelativeContainerModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIRelativeContainerModifier* GetCJUIRelativeContainerModifier()
{
    static const CJUIRelativeContainerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("RelativeContainer");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIRelativeContainerModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}
} // namespace NodeModifier

} // namespace OHOS::Ace::NG
