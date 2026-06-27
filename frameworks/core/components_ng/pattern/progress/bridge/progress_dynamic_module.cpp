/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/progress/bridge/progress_dynamic_module.h"
#include "core/components_ng/pattern/progress/bridge/progress_dynamic_modifier.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/progress/bridge/arkts_native_progress_bridge.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"


#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/progress/progress_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Progress()
{
    return new OHOS::Ace::ProgressDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIProgressModifier* GetProgressModifier();
const CJUIProgressModifier* GetCJUIProgressModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIProgressModifier* GetProgressStaticModifier();
}
#endif
} // namespace NG

void ProgressDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ProgressBridge::RegisterAttributes(object, vm);
}

const void* ProgressDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetProgressModifier();
}

const void* ProgressDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetProgressStaticModifier();
#else
    return nullptr;
#endif
}

const void* ProgressDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIProgressModifier();
}

void* ProgressDynamicModule::GetModel()
{
    static NG::ProgressModelNG model;
    return &model;
}

} // namespace OHOS::Ace
