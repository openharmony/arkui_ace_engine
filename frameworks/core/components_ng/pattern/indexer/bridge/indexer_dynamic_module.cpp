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

#include "core/components_ng/pattern/indexer/bridge/indexer_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/indexer/bridge/arkts_native_alphabet_indexer_bridge.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/indexer/indexer_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Indexer()
{
    return new OHOS::Ace::IndexerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIAlphabetIndexerModifier* GetAlphabetIndexerDynamicModifier();
const CJUIAlphabetIndexerModifier* GetCJUIAlphabetIndexerModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* EXTENDER_ACCESSOR = "ExtenderAccessor";
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerStaticModifier();
const GENERATED_ArkUIArcAlphabetIndexerExtenderAccessor* GetArcAlphabetIndexerStaticExtenderAccessor();
}
#endif
} // namespace NG

void IndexerDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::AlphabetIndexerBridge::RegisterIndexerAttributes(object, vm);
}

const void* IndexerDynamicModule::GetDynamicModifier()
{
    return NG::GetAlphabetIndexerDynamicModifier();
}

const void* IndexerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetAlphabetIndexerStaticModifier();
#else
    return nullptr;
#endif
}

const void* IndexerDynamicModule::GetCjModifier()
{
    return NG::GetCJUIAlphabetIndexerModifier();
}

void* IndexerDynamicModule::GetModel()
{
    static NG::IndexerModelNG model;
    return &model;
}

const void* IndexerDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::EXTENDER_ACCESSOR) {
        return NG::GeneratedModifier::GetArcAlphabetIndexerStaticExtenderAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
