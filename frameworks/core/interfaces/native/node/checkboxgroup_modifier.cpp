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
#include "core/interfaces/native/node/checkboxgroup_modifier.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
{
    static const ArkUICheckboxGroupModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CheckboxGroup");
        if (module == nullptr) {
        LOGF("Can't find checkboxGroup dynamic module");
        abort();
        }
        cachedModifier = reinterpret_cast<const ArkUICheckboxGroupModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUICheckboxGroupModifier* GetCJUICheckboxGroupModifier()
{
    static const CJUICheckboxGroupModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CheckboxGroup");
        if (module == nullptr) {
        LOGF("Can't find checkboxGroup dynamic module");
        abort();
        }
        cachedModifier = reinterpret_cast<const CJUICheckboxGroupModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUICheckboxGroupCustomModifier* GetCheckboxGroupCustomModifier()
{
    static const ArkUICheckboxGroupCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CheckboxGroup");
        if (module == nullptr) {
        LOGF("Can't find checkboxGroup dynamic module");
        abort();
        }
        cachedModifier =
            reinterpret_cast<const ArkUICheckboxGroupCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}

void SetCheckboxGroupChange(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetCheckboxGroupCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setCheckboxGroupOnChangeExtraParam(node, extraParam);
}

void ResetCheckboxGroupChange(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetCheckboxGroupCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetCheckboxGroupOnChange(node);
}
}
}
