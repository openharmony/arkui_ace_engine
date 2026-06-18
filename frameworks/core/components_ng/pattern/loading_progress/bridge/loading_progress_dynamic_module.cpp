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

#include "core/components_ng/pattern/loading_progress/bridge/loading_progress_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#include "core/components_ng/pattern/loading_progress/bridge/arkts_native_loading_progress_bridge.h"
#include "core/components_ng/pattern/loading_progress/bridge/content_modifier_helper.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/loading_progress/loading_progress_model_static.h"
#include "loading_progress_dynamic_module.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_LoadingProgress()
{
    return new OHOS::Ace::LoadingProgressDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUILoadingProgressModifier* GetLoadingProgressDynamicModifier();
const CJUILoadingProgressModifier* GetCJUILoadingProgressModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressStaticModifier();
const ArkUILoadingProgressContentModifier* GetLoadingProgressStaticContentModifier();
}
#endif
} // namespace NG

void LoadingProgressDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::LoadingProgressBridge::RegisterLoadingProgressAttributes(object, vm);
}

const void* LoadingProgressDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetLoadingProgressDynamicModifier();
}

const void* LoadingProgressDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetLoadingProgressStaticModifier();
#else
    return nullptr;
#endif
}

const void* LoadingProgressDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUILoadingProgressModifier();
}

void* LoadingProgressDynamicModule::GetModel()
{
    static NG::LoadingProgressModelNG model;
    return &model;
}

const void* LoadingProgressDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetLoadingProgressStaticContentModifier();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace