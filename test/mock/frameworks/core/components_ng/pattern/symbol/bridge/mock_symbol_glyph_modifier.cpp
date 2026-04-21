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

#include "core/components_ng/pattern/symbol/bridge/symbol_glyph_custom_modifier.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace::NG {

void InitialSymbol(FrameNode* frameNode, ArkUI_Uint32 symbolId)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::InitialSymbol(frameNode, symbolId);
}
void SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontSize(frameNode, value);
}
void SetFontColor(FrameNode* frameNode, const std::vector<Color>& symbolColor)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontColor(frameNode, symbolColor);
}
ArkUINodeHandle CreateSymbolGlyphFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SymbolModelNG::CreateFrameNode(static_cast<int32_t>(nodeId));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

namespace NodeModifier {
const ArkUISymbolGlyphCustomModifier* GetSymbolGlyphCustomModifier()
{
    static const ArkUISymbolGlyphCustomModifier modifier = {
        .initialSymbol = InitialSymbol,
        .setFontSize = SetFontSize,
        .setFontColor = SetFontColor,
        .createFrameNode = CreateSymbolGlyphFrameNode,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG