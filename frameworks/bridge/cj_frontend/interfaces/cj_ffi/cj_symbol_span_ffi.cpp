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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_symbol_span_ffi.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/text/symbol_span_model.h"
#include "core/components_ng/pattern/text/text_model.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSymbolSpanCreate(uint32_t id)
{
    SymbolSpanModel::GetInstance()->Create(id);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontColor(VectorUInt32Ptr colors)
{
    std::vector<Color> symbolColor;
    auto colorArrayPtr = reinterpret_cast<std::vector<uint32_t>*>(colors);
    for (auto color : *colorArrayPtr) {
        symbolColor.emplace_back(Color(ColorAlphaAdapt(color)));
    }
    SymbolSpanModel::GetInstance()->SetFontColor(symbolColor);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontSize(double size, int32_t unit)
{
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    SymbolSpanModel::GetInstance()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkSymbolSpanSetFontWeight(const char* weight)
{
    SymbolSpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
}

void FfiOHOSAceFrameworkSymbolSpanSetSymbolRenderingStrategy(int32_t strategy)
{
    SymbolSpanModel::GetInstance()->SetSymbolRenderingStrategy(static_cast<uint32_t>(strategy));
}

void FfiOHOSAceFrameworkSymbolSpanSetEffectStrategy(int32_t strategy)
{
    SymbolSpanModel::GetInstance()->SetSymbolEffect(static_cast<uint32_t>(strategy));
}
}