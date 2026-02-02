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

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_symbol_glyph_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/symbol/constants.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

extern "C" {
// Should use CJUIModifier API later
NG::SymbolModelNG* GetSymbolModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("SymbolGlyph");
    if (module == nullptr) {
        LOGF("Can't find symbol dynamic module");
        abort();
    }
    return reinterpret_cast<NG::SymbolModelNG *>(module->GetModel());
}
void FfiOHOSAceFrameworkSymbolGlyphCreate(uint32_t symbolId)
{
    GetSymbolModel()->Create(symbolId);
}

void FfiOHOSAceFrameworkSymbolGlyphFontColor(VectorUInt32Ptr colors)
{
    std::vector<Color> symbolColor;
    const auto& vecColor = *reinterpret_cast<std::vector<uint32_t>*>(colors);
    for (size_t i = 0; i < vecColor.size(); ++i) {
        symbolColor.emplace_back(Color(vecColor[i]));
    }
    GetSymbolModel()->SetFontColor(symbolColor);
}

void FfiOHOSAceFrameworkSymbolGlyphFontSize(double size, int32_t unit)
{
    CalcDimension value(size, static_cast<DimensionUnit>(unit));
    GetSymbolModel()->SetFontSize(value);
}

void FfiOHOSAceFrameworkSymbolGlyphFontWeight(const char* fontWeight)
{
    GetSymbolModel()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkSymbolGlyphRenderingStrategy(int32_t value)
{
    GetSymbolModel()->SetSymbolRenderingStrategy(static_cast<uint32_t>(value));
}

void FfiOHOSAceFrameworkSymbolGlyphEffectStrategy(int32_t value)
{
    GetSymbolModel()->SetSymbolEffect(static_cast<uint32_t>(value));
}

void FfiOHOSAceFrameworkSymbolGlyphSymbolEffect(EffectOptions effectOptions)
{
    NG::SymbolEffectOptions symbolEffectOptions;

    symbolEffectOptions.SetEffectType(static_cast<SymbolEffectType>(effectOptions.effectType));
    symbolEffectOptions.SetScopeType(static_cast<ScopeType>(effectOptions.effectScope));
    symbolEffectOptions.SetCommonSubType(static_cast<CommonSubType>(effectOptions.effectDirection));
    symbolEffectOptions.SetFillStyle(static_cast<FillStyle>(effectOptions.fillStyle));
    if (effectOptions.activeExist) {
        symbolEffectOptions.SetIsActive(effectOptions.isActive);
    }
    if (effectOptions.triggerExist) {
        symbolEffectOptions.SetTriggerNum(effectOptions.triggerValue);
    }
    GetSymbolModel()->SetSymbolEffectOptions(symbolEffectOptions);
}
}