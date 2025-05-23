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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_STATIC_H

#include <functional>
#include <string>

#include "core/components_ng/pattern/text/symbol_span_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SymbolSpanModelStatic {
public:
    static RefPtr<UINode> CreateFrameNode(int32_t nodeId);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetSymbolRenderingStrategy(FrameNode* frameNode, const std::optional<uint32_t>& renderingStrategy);
    static void SetSymbolEffect(FrameNode* frameNode, const std::optional<uint32_t>& effectStrategy);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_STATIC_H
