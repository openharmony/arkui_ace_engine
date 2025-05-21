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
namespace Drawing_FontAccessor {
void DestroyPeerImpl(Ark_drawing_Font peer)
{
}
Ark_drawing_Font CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void EnableSubpixelImpl(Ark_drawing_Font peer,
                        Ark_Boolean isSubpixel)
{
}
void EnableEmboldenImpl(Ark_drawing_Font peer,
                        Ark_Boolean isEmbolden)
{
}
void EnableLinearMetricsImpl(Ark_drawing_Font peer,
                             Ark_Boolean isLinearMetrics)
{
}
void SetSizeImpl(Ark_drawing_Font peer,
                 const Ark_Number* textSize)
{
}
Ark_Number GetSizeImpl(Ark_drawing_Font peer)
{
    return {};
}
void SetTypefaceImpl(Ark_drawing_Font peer,
                     Ark_drawing_Typeface typeface)
{
}
Ark_drawing_Typeface GetTypefaceImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_drawing_FontMetrics GetMetricsImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_Number MeasureSingleCharacterImpl(Ark_drawing_Font peer,
                                      const Ark_String* text)
{
    return {};
}
Ark_Number MeasureTextImpl(Ark_drawing_Font peer,
                           const Ark_String* text,
                           Ark_drawing_TextEncoding encoding)
{
    return {};
}
void SetScaleXImpl(Ark_drawing_Font peer,
                   const Ark_Number* scaleX)
{
}
void SetSkewXImpl(Ark_drawing_Font peer,
                  const Ark_Number* skewX)
{
}
void SetEdgingImpl(Ark_drawing_Font peer,
                   Ark_drawing_FontEdging edging)
{
}
void SetHintingImpl(Ark_drawing_Font peer,
                    Ark_drawing_FontHinting hinting)
{
}
Ark_Number CountTextImpl(Ark_drawing_Font peer,
                         const Ark_String* text)
{
    return {};
}
void SetBaselineSnapImpl(Ark_drawing_Font peer,
                         Ark_Boolean isBaselineSnap)
{
}
Ark_Boolean IsBaselineSnapImpl(Ark_drawing_Font peer)
{
    return {};
}
void SetEmbeddedBitmapsImpl(Ark_drawing_Font peer,
                            Ark_Boolean isEmbeddedBitmaps)
{
}
Ark_Boolean IsEmbeddedBitmapsImpl(Ark_drawing_Font peer)
{
    return {};
}
void SetForceAutoHintingImpl(Ark_drawing_Font peer,
                             Ark_Boolean isForceAutoHinting)
{
}
Ark_Boolean IsForceAutoHintingImpl(Ark_drawing_Font peer)
{
    return {};
}
Array_Number GetWidthsImpl(Ark_drawing_Font peer,
                           const Array_Number* glyphs)
{
    return {};
}
Array_Number TextToGlyphsImpl(Ark_drawing_Font peer,
                              const Ark_String* text,
                              const Ark_Number* glyphCount)
{
    return {};
}
Ark_Boolean IsSubpixelImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_Boolean IsLinearMetricsImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_Number GetSkewXImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_Boolean IsEmboldenImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_Number GetScaleXImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_drawing_FontHinting GetHintingImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_drawing_FontEdging GetEdgingImpl(Ark_drawing_Font peer)
{
    return {};
}
Ark_drawing_Path CreatePathForGlyphImpl(Ark_drawing_Font peer,
                                        const Ark_Number* index)
{
    return {};
}
Array_common2D_Rect GetBoundsImpl(Ark_drawing_Font peer,
                                  const Array_Number* glyphs)
{
    return {};
}
Ark_drawing_Path GetTextPathImpl(Ark_drawing_Font peer,
                                 const Ark_String* text,
                                 const Ark_Number* byteLength,
                                 const Ark_Number* x,
                                 const Ark_Number* y)
{
    return {};
}
} // Drawing_FontAccessor
const GENERATED_ArkUIDrawing_FontAccessor* GetDrawing_FontAccessor()
{
    static const GENERATED_ArkUIDrawing_FontAccessor Drawing_FontAccessorImpl {
        Drawing_FontAccessor::DestroyPeerImpl,
        Drawing_FontAccessor::CtorImpl,
        Drawing_FontAccessor::GetFinalizerImpl,
        Drawing_FontAccessor::EnableSubpixelImpl,
        Drawing_FontAccessor::EnableEmboldenImpl,
        Drawing_FontAccessor::EnableLinearMetricsImpl,
        Drawing_FontAccessor::SetSizeImpl,
        Drawing_FontAccessor::GetSizeImpl,
        Drawing_FontAccessor::SetTypefaceImpl,
        Drawing_FontAccessor::GetTypefaceImpl,
        Drawing_FontAccessor::GetMetricsImpl,
        Drawing_FontAccessor::MeasureSingleCharacterImpl,
        Drawing_FontAccessor::MeasureTextImpl,
        Drawing_FontAccessor::SetScaleXImpl,
        Drawing_FontAccessor::SetSkewXImpl,
        Drawing_FontAccessor::SetEdgingImpl,
        Drawing_FontAccessor::SetHintingImpl,
        Drawing_FontAccessor::CountTextImpl,
        Drawing_FontAccessor::SetBaselineSnapImpl,
        Drawing_FontAccessor::IsBaselineSnapImpl,
        Drawing_FontAccessor::SetEmbeddedBitmapsImpl,
        Drawing_FontAccessor::IsEmbeddedBitmapsImpl,
        Drawing_FontAccessor::SetForceAutoHintingImpl,
        Drawing_FontAccessor::IsForceAutoHintingImpl,
        Drawing_FontAccessor::GetWidthsImpl,
        Drawing_FontAccessor::TextToGlyphsImpl,
        Drawing_FontAccessor::IsSubpixelImpl,
        Drawing_FontAccessor::IsLinearMetricsImpl,
        Drawing_FontAccessor::GetSkewXImpl,
        Drawing_FontAccessor::IsEmboldenImpl,
        Drawing_FontAccessor::GetScaleXImpl,
        Drawing_FontAccessor::GetHintingImpl,
        Drawing_FontAccessor::GetEdgingImpl,
        Drawing_FontAccessor::CreatePathForGlyphImpl,
        Drawing_FontAccessor::GetBoundsImpl,
        Drawing_FontAccessor::GetTextPathImpl,
    };
    return &Drawing_FontAccessorImpl;
}

}
