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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_symbol_span_ffi.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/text/span/symbol_span_model.h"
#include "core/components_ng/pattern/text/span/symbol_span_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {

// Should use CJUIModifier API later
NG::SymbolSpanModelNG* GetSymbolSpanModel()
{
    static NG::SymbolSpanModelNG* cachedModel = nullptr;
    if (!cachedModel) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("SymbolSpan");
        if (module == nullptr) {
            LOGF_ABORT("Can't find symbolspan dynamic module");
        }
        cachedModel = reinterpret_cast<NG::SymbolSpanModelNG*>(module->GetModel());
    }
    return cachedModel;
}
} // namespace OHOS::Ace

namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    // After Api22, alpha is handled on the cangjie.
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_TWO)) {
        return result;
    } else {
        if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
            result = origin | COLOR_ALPHA_VALUE;
        }
        return result;
    }
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSymbolSpanCreate(uint32_t id)
{
    GetSymbolSpanModel()->Create(id);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontColor(VectorUInt32Ptr colors)
{
    std::vector<Color> symbolColor;
    auto colorArrayPtr = reinterpret_cast<std::vector<uint32_t>*>(colors);
    for (auto color : *colorArrayPtr) {
        symbolColor.emplace_back(Color(ColorAlphaAdapt(color)));
    }
    GetSymbolSpanModel()->SetFontColor(symbolColor);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontSize(double size, int32_t unit)
{
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    GetSymbolSpanModel()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontWeight(const char* weight)
{
    GetSymbolSpanModel()->SetFontWeight(ConvertStrToFontWeight(weight));
}

void FfiOHOSAceFrameworkSymbolSpanSetSymbolRenderingStrategy(int32_t strategy)
{
    GetSymbolSpanModel()->SetSymbolRenderingStrategy(static_cast<uint32_t>(strategy));
}

void FfiOHOSAceFrameworkSymbolSpanSetEffectStrategy(int32_t strategy)
{
    GetSymbolSpanModel()->SetSymbolEffect(static_cast<uint32_t>(strategy));
}
}