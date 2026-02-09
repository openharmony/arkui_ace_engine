/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
void CreateDynamicLayout(void* params, ArkUI_Int32 type)
{
    static DynamicLayoutModelNG model;
    auto algorithmParams = AceType::Claim(reinterpret_cast<AlgorithmParamBase*>(params));
    model.Create(algorithmParams, static_cast<DynamicLayoutType>(type));
}

namespace NodeModifier {
const ArkUIDynamicLayoutModifier* GetDynamicLayoutDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDynamicLayoutModifier modifier = {
        .createDynamicLayout = CreateDynamicLayout,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
}