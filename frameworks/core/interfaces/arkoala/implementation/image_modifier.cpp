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
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
Ark_ImageError ArkValue(const LoadImageFailEvent& event)
{
    Ark_ImageError arkEvent;
    arkEvent.componentWidth = Converter::ArkValue<Ark_Number>(event.GetComponentWidth());
    arkEvent.componentHeight = Converter::ArkValue<Ark_Number>(event.GetComponentHeight());
    arkEvent.message = Converter::ArkValue<Ark_String>(event.GetErrorMessage());
    return arkEvent;
}
} // OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG::GeneratedModifier {
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    //auto convValue = Converter::OptConvert<type_name>(*src);
    //ImageModelNG::SetSetImageOptions1(frameNode, convValue);
    LOGE("Arkoala: Image.SetImageOptions1Impl - method not implemented");
}
void SetImageOptions2Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //ImageModelNG::SetSetImageOptions2(frameNode, convValue);
    LOGE("Arkoala: Image.SetImageOptions2Impl - method not implemented");
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void AltImpl(Ark_NativePointer node,
             const Ark_Union_String_Resource_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto info = Converter::OptConvert<ImageSourceInfo>(*value);
    LOGE("Arkoala: GENERATED_ArkUIImageModifier.AltImpl - method doesn't support PixelMap");
    ImageModelNG::SetAlt(frameNode, info);
}
void MatchTextDirectionImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, Converter::Convert<bool>(value));
}
void FitOriginalSizeImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, Converter::Convert<bool>(value));
}
void FillColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ImageModelNG::SetImageFill(frameNode, Converter::OptConvert<Color>(*value));
}
void ObjectFitImpl(Ark_NativePointer node,
                   Ark_ImageFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fit = Converter::OptConvert<ImageFit>(value);
    ImageModelNG::SetImageFit(frameNode, fit);
}
void ObjectRepeatImpl(Ark_NativePointer node,
                      Ark_ImageRepeat value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRepeat(frameNode, Converter::OptConvert<ImageRepeat>(value));
}
void AutoResizeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAutoResize(frameNode, Converter::Convert<bool>(value));
}
void RenderModeImpl(Ark_NativePointer node,
                    Ark_ImageRenderMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRenderMode(frameNode, Converter::OptConvert<ImageRenderMode>(value));
}
void DynamicRangeModeImpl(Ark_NativePointer node,
                          Ark_DynamicRangeMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDynamicRangeMode(frameNode, Converter::OptConvert<DynamicRangeMode>(value));
}
void InterpolationImpl(Ark_NativePointer node,
                       Ark_ImageInterpolation value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageInterpolation(frameNode, Converter::OptConvert<ImageInterpolation>(value));
}
void SourceSizeImpl(Ark_NativePointer node,
                    const Ark_ImageSourceSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CalcDimension widthObj(Converter::Convert<float>(value->width), DimensionUnit::VP);
    CalcDimension heightObj(Converter::Convert<float>(value->height), DimensionUnit::VP);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>(widthObj, heightObj));
}
void SyncLoadImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, Converter::Convert<bool>(value));
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Ark_Union_ColorFilter_DrawingColorFilter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageModelNG::SetColorFilter(frameNode, convValue);
    LOGE("Arkoala: Image.ColorFilterImpl - method not implemented");
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(value));
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, Converter::Convert<bool>(value));
}
void PointLightImpl(Ark_NativePointer node,
                    const Ark_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageModelNG::SetPointLight(frameNode, convValue);
    LOGE("Arkoala: Image.ResizableImpl - method not implemented");
}
void EdgeAntialiasingImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ImageModelNG::SetSmoothEdge(frameNode, Converter::Convert<float>(*value));
}
void OnCompleteImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](const LoadImageSuccessEvent& info) {
        Opt_Type_ImageAttribute_onComplete_callback_event event;
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](const LoadImageFailEvent& info) {
        auto arkInfo = Converter::ArkValue<Ark_ImageError>(info);
        GetFullAPI()->getEventsAPI()->getImageEventsReceiver()->onError(frameNode->GetId(), arkInfo);
    };
    ImageModelNG::SetOnError(frameNode, std::move(onEvent));
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getImageEventsReceiver()->onFinish(frameNode->GetId());
    };
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(onEvent));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::EnableAnalyzer(frameNode, Converter::Convert<bool>(enable));
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(config);
    ImageModelNG::SetImageAnalyzerConfig(frameNode, reinterpret_cast<void*>(config->types.array));
}
void ResizableImpl(Ark_NativePointer node,
                   const Ark_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageModelNG::SetResizable(frameNode, convValue);
    LOGE("Arkoala: Image.ResizableImpl - method not implemented");
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean supported)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(Converter::Convert<bool>(supported));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void EnhancedImageQualityImpl(Ark_NativePointer node,
                              const Ark_CustomObject* imageQuality)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(imageQuality);
    //auto convValue = Converter::OptConvert<type_name>(*imageQuality);
    //ImageModelNG::SetEnhancedImageQuality(frameNode, convValue);
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
