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

#include "core/components_ng/pattern/text/span/bridge/symbol_span/symbol_span_dynamic_module.h"

#include "core/common/container.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text/span/bridge/symbol_span/arkts_native_symbol_span_bridge.h"
#include "core/components_ng/pattern/text/span/symbol_span_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/text/span/symbol_span_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_SymbolSpan()
{
    return new OHOS::Ace::SymbolSpanDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUISymbolSpanModifier* GetSymbolSpanDynamicModifier();
const CJUISymbolSpanModifier* GetCJUISymbolSpanDynamicModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanStaticModifier();
}
#endif
} // namespace NG

void SymbolSpanDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SymbolSpanBridge::RegisterSymbolSpanAttributes(object, vm);
}

const void* SymbolSpanDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetSymbolSpanDynamicModifier();
}

const void* SymbolSpanDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSymbolSpanStaticModifier();
#else
    return nullptr;
#endif
}

const void* SymbolSpanDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUISymbolSpanDynamicModifier();
}

void* SymbolSpanDynamicModule::GetModel()
{
    static NG::SymbolSpanModelNG model;
    return &model;
}

const void* SymbolSpanDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}
} // namespace OHOS::Ace
