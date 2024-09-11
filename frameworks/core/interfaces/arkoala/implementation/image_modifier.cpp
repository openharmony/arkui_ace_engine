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
#include "core/interfaces/arkoala/utility/converter.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "frameworks/core/components/common/layout/constants.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageInterfaceModifier {
void SetImageOptions0Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions_Arg0* src)
{
    ImageSourceInfo info = Converter::Convert(node, *src);
    std::string imageSrc = info.GetSrc();

    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::InitImage(frameNode, imageSrc);
}
void SetImageOptions1Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions1_Arg0* src)
{
    LOGE("Arkoala: Image.SetImageOptions1Impl - method not implemented");
}
void SetImageOptions2Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions2_Arg0* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
    LOGE("Arkoala: Image.SetImageOptions2Impl - method not implemented");
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void AltImpl(Ark_NativePointer node,
             const Type_ImageAttribute_alt_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSourceInfo info = Converter::Convert(frameNode, *value);
    ImageModelNG::SetAlt(frameNode, info);
}
void MatchTextDirectionImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, Converter::ConvertOrDefault(value, false));
}
void FitOriginalSizeImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, Converter::ConvertOrDefault(value, false));
}
void FillColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFill(frameNode, Converter::ConvertOrDefault(*value, Color()));
}
void ObjectFitImpl(Ark_NativePointer node,
                   Ark_ImageFit value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(value);
    if (objectFitValue < ImageFit::FILL || objectFitValue > ImageFit::SCALE_DOWN) {
        objectFitValue = ImageFit::COVER;
    }
    ImageModelNG::SetImageFit(frameNode, Converter::ConvertOrDefault((Ark_ImageFit)objectFitValue, ImageFit::COVER));
}
void ObjectRepeatImpl(Ark_NativePointer node,
                      Ark_ImageRepeat value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto repeat = static_cast<ImageRepeat>(value);
    if (repeat < ImageRepeat::NO_REPEAT || repeat > ImageRepeat::REPEAT) {
        repeat = ImageRepeat::NO_REPEAT;
    }
    ImageModelNG::SetImageRepeat(frameNode,
        Converter::ConvertOrDefault((Ark_ImageRepeat)repeat, ImageRepeat::NO_REPEAT));
}
void AutoResizeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAutoResize(frameNode, Converter::ConvertOrDefault(value, false));
}
void RenderModeImpl(Ark_NativePointer node,
                    Ark_ImageRenderMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderMode = static_cast<ImageRenderMode>(value);
    if (renderMode < ImageRenderMode::ORIGINAL || renderMode > ImageRenderMode::TEMPLATE) {
        renderMode = ImageRenderMode::ORIGINAL;
    }
    ImageModelNG::SetImageRenderMode(frameNode,
        Converter::ConvertOrDefault((Ark_ImageRenderMode)renderMode, ImageRenderMode::ORIGINAL));
}
void DynamicRangeModeImpl(Ark_NativePointer node,
                          Ark_DynamicRangeMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DynamicRangeMode dynamicRangeModeValue = static_cast<DynamicRangeMode>(value);
    if (dynamicRangeModeValue < DynamicRangeMode::HIGH || dynamicRangeModeValue > DynamicRangeMode::STANDARD) {
        dynamicRangeModeValue = DynamicRangeMode::STANDARD;
    }
    ImageModelNG::SetDynamicRangeMode(frameNode,
        Converter::ConvertOrDefault((Ark_DynamicRangeMode)dynamicRangeModeValue, DynamicRangeMode::HIGH));
}
void InterpolationImpl(Ark_NativePointer node,
                       Ark_ImageInterpolation value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto interpolation = static_cast<Ace::ImageInterpolation>(value);
    if (interpolation < Ace::ImageInterpolation::NONE || interpolation > Ace::ImageInterpolation::HIGH) {
        interpolation = Ace::ImageInterpolation::NONE;
    }
    ImageModelNG::SetImageInterpolation(frameNode, Converter::ConvertOrDefault((Ark_ImageInterpolation)interpolation,
                                                                               ImageInterpolation::NONE));
}
void SourceSizeImpl(Ark_NativePointer node,
                    const Type_ImageAttribute_sourceSize_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension widthObj(Converter::Convert<float>(value->width), DimensionUnit::VP);
    CalcDimension heightObj(Converter::Convert<float>(value->height), DimensionUnit::VP);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>(widthObj, heightObj));
}
void SyncLoadImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, Converter::ConvertOrDefault(value, false));
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Type_ImageAttribute_colorFilter_Arg0* value)
{
    LOGE("Arkoala: Image.ColorFilterImpl - method not implemented");
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = static_cast<CopyOptions>(value);
    if (copyOptions < CopyOptions::None || copyOptions > CopyOptions::Distributed) {
        copyOptions = CopyOptions::None;
    }
    ImageModelNG::SetCopyOption(frameNode,
        Converter::ConvertOrDefault((Ark_CopyOptions)copyOptions, CopyOptions::None));
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, Converter::ConvertOrDefault(value, false));
}
void PointLightImpl(Ark_NativePointer node,
                    const Ark_PointLightStyle* value)
{
    LOGE("Arkoala: Image.ResizableImpl - method not implemented");
}
void EdgeAntialiasingImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSmoothEdge(frameNode, Converter::Convert<float>(*value));
}
void OnCompleteImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](const LoadImageSuccessEvent& info) {
        Opt_Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY event;
        event.value.width.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.width.f32 = info.GetWidth();
        event.value.height.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.height.f32 = info.GetHeight();
        event.value.componentWidth.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.componentWidth.f32 = info.GetComponentWidth();
        event.value.componentHeight.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.componentWidth.f32 = info.GetComponentHeight();
        event.value.loadingStatus.tag = Ark_Tag::ARK_TAG_INT32;
        event.value.loadingStatus.i32 = info.GetLoadingStatus();
        event.value.contentOffsetX.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.contentOffsetX.f32 = info.GetContentOffsetX();
        event.value.contentOffsetY.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.contentOffsetY.f32 = info.GetContentOffsetY();
        event.value.contentWidth.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.contentWidth.f32 = info.GetContentWidth();
        event.value.contentHeight.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.value.contentHeight.f32 = info.GetContentHeight();
        GetFullAPI()->getEventsAPI()->getImageEventsReceiver()->onComplete(frameNode->GetId(), event);
    };
    ImageModelNG::SetOnComplete(frameNode, std::move(onEvent));
}
void OnErrorImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](const LoadImageFailEvent& info) {
        Ark_ImageError event;
        event.componentWidth.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.componentWidth.f32 = info.GetComponentWidth();
        event.componentHeight.tag = Ark_Tag::ARK_TAG_FLOAT32;
        event.componentHeight.f32 = info.GetComponentHeight();
        std::string message = info.GetErrorMessage();
        event.message.chars = message.c_str();
        event.message.length = message.length();
        GetFullAPI()->getEventsAPI()->getImageEventsReceiver()->onError(frameNode->GetId(), event);
    };
    ImageModelNG::SetOnError(frameNode, std::move(onEvent));
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getImageEventsReceiver()->onFinish(frameNode->GetId());
    };
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(onEvent));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::EnableAnalyzer(frameNode, Converter::ConvertOrDefault(enable, false));
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* config)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageAnalyzerConfig(frameNode, reinterpret_cast<void*>(config->types.array));
}
void ResizableImpl(Ark_NativePointer node,
                   const Ark_ResizableOptions* value)
{
    LOGE("Arkoala: Image.ResizableImpl - method not implemented");
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean supported)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(Converter::Convert<bool>(supported));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void EnhancedImageQualityImpl(Ark_NativePointer node,
                              const Ark_CustomObject* imageQuality)
{
    LOGE("Arkoala: Image.EnhancedImageQualityImpl - method not implemented");
}
} // ImageAttributeModifier
const GENERATED_ArkUIImageModifier* GetImageModifier()
{
    static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
        ImageInterfaceModifier::SetImageOptions0Impl,
        ImageInterfaceModifier::SetImageOptions1Impl,
        ImageInterfaceModifier::SetImageOptions2Impl,
        ImageAttributeModifier::AltImpl,
        ImageAttributeModifier::MatchTextDirectionImpl,
        ImageAttributeModifier::FitOriginalSizeImpl,
        ImageAttributeModifier::FillColorImpl,
        ImageAttributeModifier::ObjectFitImpl,
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
    };
    return &ArkUIImageModifierImpl;
}

}
