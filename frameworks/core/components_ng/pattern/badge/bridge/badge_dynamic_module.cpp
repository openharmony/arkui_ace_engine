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

#include "core/components_ng/pattern/badge/bridge/badge_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/badge/bridge/badge_custom_modifier.h"
#include "core/components_ng/pattern/badge/bridge/arkts_native_badge_bridge.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Badge()
{
    return new OHOS::Ace::BadgeDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIBadgeModifier* GetBadgeDynamicModifier();
const ArkUIBadgeCustomModifier* GetBadgeCustomModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIBadgeModifier* GetBadgeStaticModifier();
}
#endif
} // namespace NG

void BadgeDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::BadgeBridge::RegisterBadgeAttributes(object, vm);
}

const void* BadgeDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetBadgeDynamicModifier();
}

const void* BadgeDynamicModule::GetCustomModifier(const std::string& /* name */)
{
    return NG::NodeModifier::GetBadgeCustomModifier();
}

const void* BadgeDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetBadgeStaticModifier();
#else
    return nullptr;
#endif
}

const void* BadgeDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* BadgeDynamicModule::GetModel()
{
    static NG::BadgeModelNG model;
    return &model;
}

} // namespace OHOS::Ace
