/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {

template<>
void AssignCast(std::optional<VerticalAlign>& dst, const Ark_ImageSpanAlignment& src)
{
    switch (src) {
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_TOP: dst = VerticalAlign::TOP; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_CENTER: dst = VerticalAlign::CENTER; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM: dst = VerticalAlign::BOTTOM; break;
        case Ark_ImageSpanAlignment::ARK_IMAGE_SPAN_ALIGNMENT_BASELINE: dst = VerticalAlign::BASELINE; break;
        default: LOGE("Unexpected enum value in Ark_ImageSpanAlignment: %{public}d", src);
    }
}

} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageSpanInterfaceModifier {
void SetImageSpanOptionsImpl(Ark_NativePointer node,
                             const Ark_Union_ResourceStr_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageSpanModelNG::SetSetImageSpanOptions(frameNode, convValue);
}
} // ImageSpanInterfaceModifier
namespace ImageSpanAttributeModifier {
void VerticalAlignImpl(Ark_NativePointer node,
                       Ark_ImageSpanAlignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<VerticalAlign>(value);
    ImageSpanView::SetVerticalAlign(frameNode, convValue);
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Ark_Union_ColorFilter_DrawingColorFilter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageSpanModelNG::SetColorFilter(frameNode, convValue);
}
void ObjectFitImpl(Ark_NativePointer node,
                   Ark_ImageFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ImageFit>(value);
    ImageSpanView::SetObjectFit(frameNode, convValue);
}
void OnCompleteImpl(Ark_NativePointer node,
                    const ImageCompleteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageSpanModelNG::SetOnComplete(frameNode, convValue);
}
void OnErrorImpl(Ark_NativePointer node,
                 const ImageErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageSpanModelNG::SetOnError(frameNode, convValue);
}
void AltImpl(Ark_NativePointer node,
             const Ark_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageSpanModelNG::SetAlt(frameNode, convValue);
}
} // ImageSpanAttributeModifier
const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
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
