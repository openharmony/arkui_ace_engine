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

#include "core/components_ng/pattern/symbol/bridge/symbol_glyph_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/symbol/bridge/arkts_native_symbol_glyph_bridge.h"
#include "core/components_ng/pattern/symbol/bridge/symbol_glyph_custom_modifier.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/symbol/symbol_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_SymbolGlyph()
{
    return new OHOS::Ace::SymbolGlyphDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUISymbolGlyphModifier* GetSymbolGlyphDynamicModifier();
const CJUISymbolGlyphModifier* GetCJUISymbolGlyphModifier();
const ArkUISymbolGlyphCustomModifier* GetSymbolGlyphCustomModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void SymbolGlyphDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SymbolGlyphBridge::RegisterSymbolGlyphAttributes(object, vm);
}

const void* SymbolGlyphDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetSymbolGlyphDynamicModifier();
}

const void* SymbolGlyphDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSymbolGlyphStaticModifier();
#else
    return nullptr;
#endif
}

const void* SymbolGlyphDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUISymbolGlyphModifier();
}

void* SymbolGlyphDynamicModule::GetModel()
{
    static NG::SymbolModelNG model;
    return &model;
}

const void* SymbolGlyphDynamicModule::GetCustomModifier(const std::string& name)
{
    return NG::NodeModifier::GetSymbolGlyphCustomModifier();
}

} // namespace OHOS::Ace
