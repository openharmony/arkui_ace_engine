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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SymbolModelStatic {
public:
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& fontWeight);
    static void SetRenderingStrategy(FrameNode* frameNode, const std::optional<uint32_t>& renderingStrategy);
    static void SetSymbolEffect(FrameNode* frameNode, const std::optional<uint32_t>& effectStrategy);
    static void SetMinFontScale(FrameNode* frameNode, const std::optional<float>& value);
    static void SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_STATIC_H
