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

#include "core/components_ng/pattern/search/bridge/search_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/search/bridge/arkts_native_search_bridge.h"
#include "core/components_ng/pattern/search/bridge/search_custom_modifier.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/search/search_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Search()
{
    return new OHOS::Ace::SearchDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUISearchModifier* GetSearchDynamicModifier();
const CJUISearchModifier* GetCJUISearchModifier();
const ArkUISearchCustomModifier* GetSearchCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUISearchModifier* GetSearchStaticModifier();
}
#endif
} // namespace NG

void SearchDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SearchBridge::RegisterSearchAttributes(object, vm);
}

const void* SearchDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetSearchDynamicModifier();
}

const void* SearchDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSearchStaticModifier();
#else
    return nullptr;
#endif
}

const void* SearchDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUISearchModifier();
}

void* SearchDynamicModule::GetModel()
{
    static NG::SearchModelNG model;
    return &model;
}

const void* SearchDynamicModule::GetCustomModifier(const std::string& name)
{
    return NG::NodeModifier::GetSearchCustomModifier();
}
} // namespace OHOS::Ace