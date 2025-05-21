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
namespace Drawing_TextBlobAccessor {
void DestroyPeerImpl(Ark_drawing_TextBlob peer)
{
}
Ark_drawing_TextBlob CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_TextBlob MakeFromStringImpl(const Ark_String* text,
                                        Ark_drawing_Font font,
                                        Ark_drawing_TextEncoding encoding)
{
    return {};
}
Ark_drawing_TextBlob MakeFromPosTextImpl(const Ark_String* text,
                                         const Ark_Number* len,
                                         const Array_common2D_Point* points,
                                         Ark_drawing_Font font)
{
    return {};
}
Ark_drawing_TextBlob MakeFromRunBufferImpl(const Array_drawing_TextBlobRunBuffer* pos,
                                           Ark_drawing_Font font,
                                           const Ark_common2D_Rect* bounds)
{
    return {};
}
Ark_common2D_Rect BoundsImpl(Ark_drawing_TextBlob peer)
{
    return {};
}
Ark_Number UniqueIDImpl(Ark_drawing_TextBlob peer)
{
    return {};
}
} // Drawing_TextBlobAccessor
const GENERATED_ArkUIDrawing_TextBlobAccessor* GetDrawing_TextBlobAccessor()
{
    static const GENERATED_ArkUIDrawing_TextBlobAccessor Drawing_TextBlobAccessorImpl {
        Drawing_TextBlobAccessor::DestroyPeerImpl,
        Drawing_TextBlobAccessor::CtorImpl,
        Drawing_TextBlobAccessor::GetFinalizerImpl,
        Drawing_TextBlobAccessor::MakeFromStringImpl,
        Drawing_TextBlobAccessor::MakeFromPosTextImpl,
        Drawing_TextBlobAccessor::MakeFromRunBufferImpl,
        Drawing_TextBlobAccessor::BoundsImpl,
        Drawing_TextBlobAccessor::UniqueIDImpl,
    };
    return &Drawing_TextBlobAccessorImpl;
}

}
