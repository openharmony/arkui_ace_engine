/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {
const ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const ArkUICheckboxModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Checkbox");
        if (module == nullptr) {
            LOGF("Can't find checkbox dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const ArkUICheckboxModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUICheckboxModifier* GetCJUICheckboxModifier()
{
    static const CJUICheckboxModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Checkbox");
        if (module == nullptr) {
            LOGF("Can't find checkbox dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const CJUICheckboxModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUICheckboxCustomModifier* GetCheckboxCustomModifier()
{
    static const ArkUICheckboxCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Checkbox");
        if (module == nullptr) {
            LOGF("Can't find checkbox dynamic module");
            abort();
        }
        cachedModifier =
            reinterpret_cast<const ArkUICheckboxCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}

void SetCheckboxChange(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetCheckboxCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setCheckboxOnChangeExtraParam(node, extraParam);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
