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

#include "core/components_ng/pattern/shape/bridge/path_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_path_bridge.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/bridge/path_custom_modifier.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const struct GENERATED_ArkUIPathModifier* GetPathStaticModifier();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIPathModifier* GetPathDynamicModifier();
const CJUIPathModifier* GetCJUIPathModifier();
const ArkUIPathCustomModifier* GetPathCustomModifier();
}
} // namespace NG

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Path()
{
    return new OHOS::Ace::PathDynamicModule();
}

void PathDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::PathBridge::RegisterPathAttributes(object, vm);
}

const void* PathDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetPathDynamicModifier();
}

const void* PathDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetPathStaticModifier();
#else
    return nullptr;
#endif
}

const void* PathDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIPathModifier();
}

void* PathDynamicModule::GetModel()
{
    static NG::PathModelNG model;
    return &model;
}

const void* PathDynamicModule::GetCustomModifier(const std::string& name)
{
    return NG::NodeModifier::GetPathCustomModifier();
}

} // namespace OHOS::Ace

