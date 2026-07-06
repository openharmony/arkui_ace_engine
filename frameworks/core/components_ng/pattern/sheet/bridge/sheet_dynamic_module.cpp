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

#include "core/components_ng/pattern/sheet/bridge/sheet_dynamic_module.h"

#include "ecmascript/napi/include/jsnapi.h"

#include "core/components_ng/pattern/sheet/bridge/sheet_manager_inner_modifier.h"
#include "core/components_ng/pattern/sheet/bridge/sheet_pattern_inner_modifier.h"
#include "core/components_ng/pattern/sheet/bridge/sheet_view_inner_modifier.h"
#include "core/components_ng/pattern/sheet/bridge/sheet_wrapper_inner_modifier.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Sheet()
{
    return new OHOS::Ace::SheetDynamicModule();
}

namespace OHOS::Ace {

void SheetDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) {}

const void* SheetDynamicModule::GetDynamicModifier()
{
    return nullptr;
}

const void* SheetDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* SheetDynamicModule::GetCjModifier()
{
    return nullptr;
}

const void* SheetDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::InnerModifier::SHEET_MANAGER_INNER_MODIFIER) {
        return NG::InnerModifier::GetSheetManagerInnerModifier();
    }
    if (name == NG::InnerModifier::SHEET_PATTERN_INNER_MODIFIER) {
        return NG::InnerModifier::GetSheetPatternInnerModifier();
    }
    if (name == NG::InnerModifier::SHEET_WRAPPER_INNER_MODIFIER) {
        return NG::InnerModifier::GetSheetWrapperInnerModifier();
    }
    if (name == NG::InnerModifier::SHEET_VIEW_INNER_MODIFIER) {
        return NG::InnerModifier::GetSheetViewInnerModifier();
    }
    return nullptr;
}

} // namespace OHOS::Ace
