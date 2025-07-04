/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace text_ParagraphBuilderAccessor {
void DestroyPeerImpl(Ark_text_ParagraphBuilder peer)
{
}
Ark_text_ParagraphBuilder ConstructImpl(const Ark_text_ParagraphStyle* paragraphStyle,
                                        Ark_text_FontCollection fontCollection)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void PushStyleImpl(Ark_text_ParagraphBuilder peer,
                   const Ark_text_TextStyle* textStyle)
{
}
void PopStyleImpl(Ark_text_ParagraphBuilder peer)
{
}
void AddTextImpl(Ark_text_ParagraphBuilder peer,
                 const Ark_String* text)
{
}
void AddPlaceholderImpl(Ark_text_ParagraphBuilder peer,
                        const Ark_text_PlaceholderSpan* placeholderSpan)
{
}
Ark_text_Paragraph BuildImpl(Ark_text_ParagraphBuilder peer)
{
    return {};
}
Ark_text_LineTypeset BuildLineTypesetImpl(Ark_text_ParagraphBuilder peer)
{
    return {};
}
void AddSymbolImpl(Ark_text_ParagraphBuilder peer,
                   const Ark_Number* symbolId)
{
}
} // text_ParagraphBuilderAccessor
const GENERATED_ArkUIText_ParagraphBuilderAccessor* GetText_ParagraphBuilderAccessor()
{
    static const GENERATED_ArkUIText_ParagraphBuilderAccessor Text_ParagraphBuilderAccessorImpl {
        text_ParagraphBuilderAccessor::DestroyPeerImpl,
        text_ParagraphBuilderAccessor::ConstructImpl,
        text_ParagraphBuilderAccessor::GetFinalizerImpl,
        text_ParagraphBuilderAccessor::PushStyleImpl,
        text_ParagraphBuilderAccessor::PopStyleImpl,
        text_ParagraphBuilderAccessor::AddTextImpl,
        text_ParagraphBuilderAccessor::AddPlaceholderImpl,
        text_ParagraphBuilderAccessor::BuildImpl,
        text_ParagraphBuilderAccessor::BuildLineTypesetImpl,
        text_ParagraphBuilderAccessor::AddSymbolImpl,
    };
    return &Text_ParagraphBuilderAccessorImpl;
}

}
