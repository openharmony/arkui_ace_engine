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
namespace Text_RunAccessor {
void DestroyPeerImpl(Ark_text_Run peer)
{
}
Ark_text_Run CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetGlyphCountImpl(Ark_text_Run peer)
{
    return {};
}
Array_Number GetGlyphs0Impl(Ark_text_Run peer)
{
    return {};
}
Array_Number GetGlyphs1Impl(Ark_text_Run peer,
                            const Ark_text_Range* range)
{
    return {};
}
Array_common2D_Point GetPositions0Impl(Ark_text_Run peer)
{
    return {};
}
Array_common2D_Point GetPositions1Impl(Ark_text_Run peer,
                                       const Ark_text_Range* range)
{
    return {};
}
Array_common2D_Point GetOffsetsImpl(Ark_text_Run peer)
{
    return {};
}
Ark_drawing_Font GetFontImpl(Ark_text_Run peer)
{
    return {};
}
void PaintImpl(Ark_text_Run peer,
               Ark_drawing_Canvas canvas,
               const Ark_Number* x,
               const Ark_Number* y)
{
}
Array_Number GetStringIndicesImpl(Ark_text_Run peer,
                                  const Ark_text_Range* range)
{
    return {};
}
Ark_text_Range GetStringRangeImpl(Ark_text_Run peer)
{
    return {};
}
Ark_text_TypographicBounds GetTypographicBoundsImpl(Ark_text_Run peer)
{
    return {};
}
Ark_common2D_Rect GetImageBoundsImpl(Ark_text_Run peer)
{
    return {};
}
} // Text_RunAccessor
const GENERATED_ArkUIText_RunAccessor* GetText_RunAccessor()
{
    static const GENERATED_ArkUIText_RunAccessor Text_RunAccessorImpl {
        Text_RunAccessor::DestroyPeerImpl,
        Text_RunAccessor::CtorImpl,
        Text_RunAccessor::GetFinalizerImpl,
        Text_RunAccessor::GetGlyphCountImpl,
        Text_RunAccessor::GetGlyphs0Impl,
        Text_RunAccessor::GetGlyphs1Impl,
        Text_RunAccessor::GetPositions0Impl,
        Text_RunAccessor::GetPositions1Impl,
        Text_RunAccessor::GetOffsetsImpl,
        Text_RunAccessor::GetFontImpl,
        Text_RunAccessor::PaintImpl,
        Text_RunAccessor::GetStringIndicesImpl,
        Text_RunAccessor::GetStringRangeImpl,
        Text_RunAccessor::GetTypographicBoundsImpl,
        Text_RunAccessor::GetImageBoundsImpl,
    };
    return &Text_RunAccessorImpl;
}

}
