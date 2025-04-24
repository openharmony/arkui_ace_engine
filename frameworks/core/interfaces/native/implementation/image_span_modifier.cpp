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
namespace ImageSpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ImageSpanModifier
namespace ImageSpanInterfaceModifier {
void SetImageSpanOptionsImpl(Ark_NativePointer node,
                             const Ark_Union_ResourceStr_PixelMap* value)
{
}
} // ImageSpanInterfaceModifier
namespace ImageSpanAttributeModifier {
void VerticalAlignImpl(Ark_NativePointer node,
                       const Opt_ImageSpanAlignment* value)
{
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   const Opt_ImageFit* value)
{
}
void OnCompleteImpl(Ark_NativePointer node,
                    const Opt_ImageCompleteCallback* value)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_ImageErrorCallback* value)
{
}
void AltImpl(Ark_NativePointer node,
             const Opt_PixelMap* value)
{
}
} // ImageSpanAttributeModifier
const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
        ImageSpanModifier::ConstructImpl,
        ImageSpanInterfaceModifier::SetImageSpanOptionsImpl,
        ImageSpanAttributeModifier::VerticalAlignImpl,
        ImageSpanAttributeModifier::ColorFilterImpl,
        ImageSpanAttributeModifier::ObjectFitImpl,
        ImageSpanAttributeModifier::OnCompleteImpl,
        ImageSpanAttributeModifier::OnErrorImpl,
        ImageSpanAttributeModifier::AltImpl,
    };
    return &ArkUIImageSpanModifierImpl;
}

}
