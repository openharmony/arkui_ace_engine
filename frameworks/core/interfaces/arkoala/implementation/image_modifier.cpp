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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageInterfaceModifier {
void SetImageOptions0Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions_Arg0* src)
{
}
void SetImageOptions1Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions1_Arg0* src)
{
}
void SetImageOptions2Impl(Ark_NativePointer node,
                          const Type_ImageInterface_setImageOptions2_Arg0* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void AltImpl(Ark_NativePointer node,
             const Type_ImageAttribute_alt_Arg0* value)
{
}
void MatchTextDirectionImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
}
void FitOriginalSizeImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
}
void FillColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   enum Ark_ImageFit value)
{
}
void ObjectRepeatImpl(Ark_NativePointer node,
                      enum Ark_ImageRepeat value)
{
}
void AutoResizeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void RenderModeImpl(Ark_NativePointer node,
                    enum Ark_ImageRenderMode value)
{
}
void DynamicRangeModeImpl(Ark_NativePointer node,
                          enum Ark_DynamicRangeMode value)
{
}
void InterpolationImpl(Ark_NativePointer node,
                       enum Ark_ImageInterpolation value)
{
}
void SourceSizeImpl(Ark_NativePointer node,
                    const Ark_ImageSourceSize* value)
{
}
void SyncLoadImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Type_ImageAttribute_colorFilter_Arg0* value)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    enum Ark_CopyOptions value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void PointLightImpl(Ark_NativePointer node,
                    const Ark_PointLightStyle* value)
{
}
void EdgeAntialiasingImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
}
void OnCompleteImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* config)
{
}
void ResizableImpl(Ark_NativePointer node,
                   const Ark_ResizableOptions* value)
{
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean supported)
{
}
void EnhancedImageQualityImpl(Ark_NativePointer node,
                              const Ark_CustomObject* imageQuality)
{
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
