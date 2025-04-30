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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    RefPtr<PixelMap> pixmap = nullptr;
    auto frameNode = ImageModelNG::CreateFrameNode(id, "", pixmap, "", "", false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ImageModifier
namespace ImageInterfaceModifier {
void SetImageOptions0Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src)
{
    CHECK_NULL_VOID(src);
    auto info = Converter::OptConvert<ImageSourceInfo>(*src);
    if (info) {
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        ImageModelNG::InitImage(frameNode, info->GetSrc());
    }
}
void SetImageOptions1Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    auto info = Converter::OptConvert<ImageSourceInfo>(*src);
    // Note.
    // This function should skip InitImage invocation if info's optinal is empty.
    if (info) {
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        ImageModelNG::InitImage(frameNode, info->GetSrc());
    }
}
void SetImageOptions2Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void AltImpl(Ark_NativePointer node, const Opt_Union_String_Resource_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto info = Converter::OptConvert<ImageSourceInfo>(value->value);
    if (!info.has_value() || ImageSourceInfo::ResolveURIType(info->GetSrc()) == SrcType::NETWORK) {
        return;
    }
    ImageModelNG::SetAlt(frameNode, info);
}

void MatchTextDirectionImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, Converter::Convert<bool>(value->value));
}
void FitOriginalSizeImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
}
void FillColor0Impl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void FillColor1Impl(Ark_NativePointer node,
                    const Opt_Union_ResourceColor_ColorContent* value)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto fit = Converter::OptConvert<ImageFit>(value->value);
    ImageModelNG::SetImageFit(frameNode, fit);
}
void ImageMatrixImpl(Ark_NativePointer node,
                     const Opt_Matrix4Transit* value)
{
}
void ObjectRepeatImpl(Ark_NativePointer node,
                      const Opt_ImageRepeat* value)
{
}
void AutoResizeImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void RenderModeImpl(Ark_NativePointer node,
                    const Opt_ImageRenderMode* value)
{
}
void DynamicRangeModeImpl(Ark_NativePointer node,
                          const Opt_DynamicRangeMode* value)
{
}
void InterpolationImpl(Ark_NativePointer node,
                       const Opt_ImageInterpolation* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageInterpolation(frameNode, Converter::OptConvert<ImageInterpolation>(value->value));
}
void SourceSizeImpl(Ark_NativePointer node,
                    const Opt_ImageSourceSize* value)
{
}
void SyncLoadImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, Converter::Convert<bool>(value->value));
}
void PointLightImpl(Ark_NativePointer node,
                    const Opt_PointLightStyle* value)
{
}
void EdgeAntialiasingImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void OnCompleteImpl(Ark_NativePointer node,
                    const Opt_Callback_Type_ImageAttribute_onComplete_callback_event_Void* value)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_ImageErrorCallback* value)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Opt_ImageAnalyzerConfig* value)
{
}
void ResizableImpl(Ark_NativePointer node,
                   const Opt_ResizableOptions* value)
{
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void EnhancedImageQualityImpl(Ark_NativePointer node,
                              const Opt_ResolutionQuality* value)
{
}
void OrientationImpl(Ark_NativePointer node,
                     const Opt_ImageRotateOrientation* value)
{
}
} // ImageAttributeModifier
const GENERATED_ArkUIImageModifier* GetImageModifier()
{
    static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
        ImageModifier::ConstructImpl,
        ImageInterfaceModifier::SetImageOptions0Impl,
        ImageInterfaceModifier::SetImageOptions1Impl,
        ImageInterfaceModifier::SetImageOptions2Impl,
        ImageAttributeModifier::AltImpl,
        ImageAttributeModifier::MatchTextDirectionImpl,
        ImageAttributeModifier::FitOriginalSizeImpl,
        ImageAttributeModifier::FillColor0Impl,
        ImageAttributeModifier::FillColor1Impl,
        ImageAttributeModifier::ObjectFitImpl,
        ImageAttributeModifier::ImageMatrixImpl,
        ImageAttributeModifier::ObjectRepeatImpl,
        ImageAttributeModifier::AutoResizeImpl,
        ImageAttributeModifier::RenderModeImpl,
        ImageAttributeModifier::DynamicRangeModeImpl,
        ImageAttributeModifier::InterpolationImpl,
        ImageAttributeModifier::SourceSizeImpl,
        ImageAttributeModifier::SyncLoadImpl,
        ImageAttributeModifier::ColorFilterImpl,
        ImageAttributeModifier::CopyOptionImpl,
        ImageAttributeModifier::DraggableImpl,
        ImageAttributeModifier::PointLightImpl,
        ImageAttributeModifier::EdgeAntialiasingImpl,
        ImageAttributeModifier::OnCompleteImpl,
        ImageAttributeModifier::OnErrorImpl,
        ImageAttributeModifier::OnFinishImpl,
        ImageAttributeModifier::EnableAnalyzerImpl,
        ImageAttributeModifier::AnalyzerConfigImpl,
        ImageAttributeModifier::ResizableImpl,
        ImageAttributeModifier::PrivacySensitiveImpl,
        ImageAttributeModifier::EnhancedImageQualityImpl,
        ImageAttributeModifier::OrientationImpl,
    };
    return &ArkUIImageModifierImpl;
}

}
