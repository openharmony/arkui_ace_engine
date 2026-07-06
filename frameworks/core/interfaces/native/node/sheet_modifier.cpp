/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/sheet_modifier.h"

#include <cstdlib>

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG::NodeModifier {
namespace {
template<typename Modifier>
const Modifier* GetSheetInnerModifier(const char* modifierName)
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Sheet");
    if (module == nullptr) {
        LOGF_ABORT("Can't find Sheet dynamic module");
    }
    return reinterpret_cast<const Modifier*>(module->GetCustomModifier(modifierName));
}
} // namespace

const ArkUISheetManagerInnerModifier* GetSheetManagerInnerModifier()
{
    static const ArkUISheetManagerInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        modifier = GetSheetInnerModifier<ArkUISheetManagerInnerModifier>(InnerModifier::SHEET_MANAGER_INNER_MODIFIER);
    }
    return modifier;
}

const ArkUISheetPatternInnerModifier* GetSheetPatternInnerModifier()
{
    static const ArkUISheetPatternInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        modifier = GetSheetInnerModifier<ArkUISheetPatternInnerModifier>(InnerModifier::SHEET_PATTERN_INNER_MODIFIER);
    }
    return modifier;
}

const ArkUISheetWrapperInnerModifier* GetSheetWrapperInnerModifier()
{
    static const ArkUISheetWrapperInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        modifier = GetSheetInnerModifier<ArkUISheetWrapperInnerModifier>(InnerModifier::SHEET_WRAPPER_INNER_MODIFIER);
    }
    return modifier;
}

const ArkUISheetViewInnerModifier* GetSheetViewInnerModifier()
{
    static const ArkUISheetViewInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        modifier = GetSheetInnerModifier<ArkUISheetViewInnerModifier>(InnerModifier::SHEET_VIEW_INNER_MODIFIER);
    }
    return modifier;
}
} // namespace OHOS::Ace::NG::NodeModifier
