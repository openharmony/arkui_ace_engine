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

#include "core/components_ng/pattern/refresh/bridge/refresh_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/refresh/bridge/arkts_native_refresh_bridge.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/refresh/refresh_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Refresh()
{
    return new OHOS::Ace::RefreshDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIRefreshModifier* GetRefreshModifier();
const CJUIRefreshModifier* GetCJUIRefreshModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIRefreshModifier* GetRefreshModifier();
}
#endif
} // namespace NG

void RefreshDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RefreshBridge::RegisterRefreshAttributes(object, vm);
}

const void* RefreshDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetRefreshModifier();
}

const void* RefreshDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRefreshModifier();
#else
    return nullptr;
#endif
}

const void* RefreshDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIRefreshModifier();
}

void* RefreshDynamicModule::GetModel()
{
    static NG::RefreshModelNG model;
    return &model;
}

} // namespace OHOS::Ace
