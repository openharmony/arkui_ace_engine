/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_symbol_glyph_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    static const ArkUISymbolGlyphModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("SymbolGlyph");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUISymbolGlyphModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISymbolGlyphModifier* GetCJUISymbolGlyphModifier()
{
    static const CJUISymbolGlyphModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("SymbolGlyph");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUISymbolGlyphModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUISymbolGlyphCustomModifier* GetSymbolGlyphCustomModifier()
{
    static const ArkUISymbolGlyphCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("SymbolGlyph");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUISymbolGlyphCustomModifier*>(module->GetCustomModifier());
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
