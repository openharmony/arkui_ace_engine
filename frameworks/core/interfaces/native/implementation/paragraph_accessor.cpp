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
namespace Text_ParagraphAccessor {
void DestroyPeerImpl(Ark_text_Paragraph peer)
{
}
Ark_text_Paragraph CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void LayoutSyncImpl(Ark_text_Paragraph peer,
                    const Ark_Number* width)
{
}
void LayoutImpl(Ark_VMContext vmContext,
                Ark_AsyncWorkerPtr asyncWorker,
                Ark_text_Paragraph peer,
                const Ark_Number* width,
                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void PaintImpl(Ark_text_Paragraph peer,
               Ark_drawing_Canvas canvas,
               const Ark_Number* x,
               const Ark_Number* y)
{
}
void PaintOnPathImpl(Ark_text_Paragraph peer,
                     Ark_drawing_Canvas canvas,
                     Ark_drawing_Path path,
                     const Ark_Number* hOffset,
                     const Ark_Number* vOffset)
{
}
Ark_Number GetMaxWidthImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetHeightImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetLongestLineImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetLongestLineWithIndentImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetMinIntrinsicWidthImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetMaxIntrinsicWidthImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetAlphabeticBaselineImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetIdeographicBaselineImpl(Ark_text_Paragraph peer)
{
    return {};
}
Array_text_TextBox GetRectsForRangeImpl(Ark_text_Paragraph peer,
                                        const Ark_text_Range* range,
                                        Ark_text_RectWidthStyle widthStyle,
                                        Ark_text_RectHeightStyle heightStyle)
{
    return {};
}
Array_text_TextBox GetRectsForPlaceholdersImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_text_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_text_Paragraph peer,
                                                               const Ark_Number* x,
                                                               const Ark_Number* y)
{
    return {};
}
Ark_text_Range GetWordBoundaryImpl(Ark_text_Paragraph peer,
                                   const Ark_Number* offset)
{
    return {};
}
Ark_Number GetLineCountImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_Number GetLineHeightImpl(Ark_text_Paragraph peer,
                             const Ark_Number* line)
{
    return {};
}
Ark_Number GetLineWidthImpl(Ark_text_Paragraph peer,
                            const Ark_Number* line)
{
    return {};
}
Ark_Boolean DidExceedMaxLinesImpl(Ark_text_Paragraph peer)
{
    return {};
}
Array_text_TextLine GetTextLinesImpl(Ark_text_Paragraph peer)
{
    return {};
}
Ark_text_Range GetActualTextRangeImpl(Ark_text_Paragraph peer,
                                      const Ark_Number* lineNumber,
                                      Ark_Boolean includeSpaces)
{
    return {};
}
Array_text_LineMetrics GetLineMetrics0Impl(Ark_text_Paragraph peer)
{
    return {};
}
Opt_text_LineMetrics GetLineMetrics1Impl(Ark_text_Paragraph peer,
                                         const Ark_Number* lineNumber)
{
    return {};
}
} // Text_ParagraphAccessor
const GENERATED_ArkUIText_ParagraphAccessor* GetText_ParagraphAccessor()
{
    static const GENERATED_ArkUIText_ParagraphAccessor Text_ParagraphAccessorImpl {
        Text_ParagraphAccessor::DestroyPeerImpl,
        Text_ParagraphAccessor::CtorImpl,
        Text_ParagraphAccessor::GetFinalizerImpl,
        Text_ParagraphAccessor::LayoutSyncImpl,
        Text_ParagraphAccessor::LayoutImpl,
        Text_ParagraphAccessor::PaintImpl,
        Text_ParagraphAccessor::PaintOnPathImpl,
        Text_ParagraphAccessor::GetMaxWidthImpl,
        Text_ParagraphAccessor::GetHeightImpl,
        Text_ParagraphAccessor::GetLongestLineImpl,
        Text_ParagraphAccessor::GetLongestLineWithIndentImpl,
        Text_ParagraphAccessor::GetMinIntrinsicWidthImpl,
        Text_ParagraphAccessor::GetMaxIntrinsicWidthImpl,
        Text_ParagraphAccessor::GetAlphabeticBaselineImpl,
        Text_ParagraphAccessor::GetIdeographicBaselineImpl,
        Text_ParagraphAccessor::GetRectsForRangeImpl,
        Text_ParagraphAccessor::GetRectsForPlaceholdersImpl,
        Text_ParagraphAccessor::GetGlyphPositionAtCoordinateImpl,
        Text_ParagraphAccessor::GetWordBoundaryImpl,
        Text_ParagraphAccessor::GetLineCountImpl,
        Text_ParagraphAccessor::GetLineHeightImpl,
        Text_ParagraphAccessor::GetLineWidthImpl,
        Text_ParagraphAccessor::DidExceedMaxLinesImpl,
        Text_ParagraphAccessor::GetTextLinesImpl,
        Text_ParagraphAccessor::GetActualTextRangeImpl,
        Text_ParagraphAccessor::GetLineMetrics0Impl,
        Text_ParagraphAccessor::GetLineMetrics1Impl,
    };
    return &Text_ParagraphAccessorImpl;
}

}
