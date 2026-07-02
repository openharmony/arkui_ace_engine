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

#include "core/components_ng/pattern/select/bridge/select_dynamic_module.h"

#include "core/common/container.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/select/bridge/arkts_native_select_bridge.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/select/select_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Select()
{
    return new OHOS::Ace::SelectDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUISelectModifier* GetSelectDynamicModifier();
const CJUISelectModifier* GetCJUISelectModifier();
const ArkUISelectCustomModifier* GetSelectCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUISelectModifier* GetSelectStaticModifier();
}
#endif
} // namespace NG

void SelectDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SelectBridge::RegisterSelectAttributes(object, vm);
}

const void* SelectDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetSelectDynamicModifier();
}

const void* SelectDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSelectStaticModifier();
#else
    return nullptr;
#endif
}

const void* SelectDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUISelectModifier();
}

void* SelectDynamicModule::GetModel()
{
    static NG::SelectModelNG model;
    return &model;
}

const void* SelectDynamicModule::GetCustomModifier(const std::string& name)
{
    return NG::NodeModifier::GetSelectCustomModifier();
}
} // namespace OHOS::Ace