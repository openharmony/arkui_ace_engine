/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/symbol/symbol_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SymbolModelNG : public SymbolModel {
public:
    void Create(const std::uint32_t& unicode) override;
    void SetFontWeight(const Ace::FontWeight& value) override;
    void SetFontSize(const CalcDimension& value) override;
    void SetSymbolRenderingStrategy(const std::uint32_t renderingStrategy) override;
    void SetFontColor(std::vector<Color>& symbolColor) override;
    void SetSymbolEffect(const std::uint32_t effectStrategy) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H
