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
namespace text_TextLineAccessor {
void DestroyPeerImpl(Ark_text_TextLine peer)
{
}
Ark_text_TextLine ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetGlyphCountImpl(Ark_text_TextLine peer)
{
    return {};
}
Ark_text_Range GetTextRangeImpl(Ark_text_TextLine peer)
{
    return {};
}
Array_text_Run GetGlyphRunsImpl(Ark_text_TextLine peer)
{
    return {};
}
void PaintImpl(Ark_text_TextLine peer,
               Ark_drawing_Canvas canvas,
               const Ark_Number* x,
               const Ark_Number* y)
{
}
Ark_text_TextLine CreateTruncatedLineImpl(Ark_text_TextLine peer,
                                          const Ark_Number* width,
                                          Ark_text_EllipsisMode ellipsisMode,
                                          const Ark_String* ellipsis)
{
    return {};
}
Ark_text_TypographicBounds GetTypographicBoundsImpl(Ark_text_TextLine peer)
{
    return {};
}
Ark_common2D_Rect GetImageBoundsImpl(Ark_text_TextLine peer)
{
    return {};
}
Ark_Number GetTrailingSpaceWidthImpl(Ark_text_TextLine peer)
{
    return {};
}
Ark_Number GetStringIndexForPositionImpl(Ark_text_TextLine peer,
                                         const Ark_common2D_Point* point)
{
    return {};
}
Ark_Number GetOffsetForStringIndexImpl(Ark_text_TextLine peer,
                                       const Ark_Number* index)
{
    return {};
}
void EnumerateCaretOffsetsImpl(Ark_text_TextLine peer,
                               const text_Callback_Number_Number_Boolean_Boolean* callback_)
{
}
Ark_Number GetAlignmentOffsetImpl(Ark_text_TextLine peer,
                                  const Ark_Number* alignmentFactor,
                                  const Ark_Number* alignmentWidth)
{
    return {};
}
} // text_TextLineAccessor
const GENERATED_ArkUIText_TextLineAccessor* GetText_TextLineAccessor()
{
    static const GENERATED_ArkUIText_TextLineAccessor Text_TextLineAccessorImpl {
        text_TextLineAccessor::DestroyPeerImpl,
        text_TextLineAccessor::ConstructImpl,
        text_TextLineAccessor::GetFinalizerImpl,
        text_TextLineAccessor::GetGlyphCountImpl,
        text_TextLineAccessor::GetTextRangeImpl,
        text_TextLineAccessor::GetGlyphRunsImpl,
        text_TextLineAccessor::PaintImpl,
        text_TextLineAccessor::CreateTruncatedLineImpl,
        text_TextLineAccessor::GetTypographicBoundsImpl,
        text_TextLineAccessor::GetImageBoundsImpl,
        text_TextLineAccessor::GetTrailingSpaceWidthImpl,
        text_TextLineAccessor::GetStringIndexForPositionImpl,
        text_TextLineAccessor::GetOffsetForStringIndexImpl,
        text_TextLineAccessor::EnumerateCaretOffsetsImpl,
        text_TextLineAccessor::GetAlignmentOffsetImpl,
    };
    return &Text_TextLineAccessorImpl;
}

}
