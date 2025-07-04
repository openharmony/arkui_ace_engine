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
namespace ImageModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ImageModifier
namespace ImageInterfaceModifier {
void SetImageOptions0Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    //auto convValue = Converter::OptConvert<type_name>(*src);
    //ImageModelNG::SetSetImageOptions0(frameNode, convValue);
}
void SetImageOptions1Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //ImageModelNG::SetSetImageOptions1(frameNode, convValue);
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void SetAltImpl(Ark_NativePointer node,
                const Opt_Union_String_Resource_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetAlt(frameNode, convValue);
}
void SetMatchTextDirectionImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetMatchTextDirection(frameNode, convValue);
}
void SetFitOriginalSizeImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetFitOriginalSize(frameNode, convValue);
}
void SetFillColorImpl(Ark_NativePointer node,
                      const Opt_Union_ResourceColor_ColorContent_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetFillColor(frameNode, convValue);
}
void SetObjectFitImpl(Ark_NativePointer node,
                      const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetObjectFit(frameNode, convValue);
}
void SetImageMatrixImpl(Ark_NativePointer node,
                        const Opt_matrix4_Matrix4Transit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetImageMatrix(frameNode, convValue);
}
void SetObjectRepeatImpl(Ark_NativePointer node,
                         const Opt_ImageRepeat* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetObjectRepeat(frameNode, convValue);
}
void SetAutoResizeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetAutoResize(frameNode, convValue);
}
void SetRenderModeImpl(Ark_NativePointer node,
                       const Opt_ImageRenderMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetRenderMode(frameNode, convValue);
}
void SetDynamicRangeModeImpl(Ark_NativePointer node,
                             const Opt_DynamicRangeMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetDynamicRangeMode(frameNode, convValue);
}
void SetInterpolationImpl(Ark_NativePointer node,
                          const Opt_ImageInterpolation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetInterpolation(frameNode, convValue);
}
void SetSourceSizeImpl(Ark_NativePointer node,
                       const Opt_ImageSourceSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetSourceSize(frameNode, convValue);
}
void SetSyncLoadImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetSyncLoad(frameNode, convValue);
}
void SetColorFilterImpl(Ark_NativePointer node,
                        const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetColorFilter(frameNode, convValue);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetCopyOption(frameNode, convValue);
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetDraggable(frameNode, convValue);
}
void SetPointLightImpl(Ark_NativePointer node,
                       const Opt_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetPointLight(frameNode, convValue);
}
void SetEdgeAntialiasingImpl(Ark_NativePointer node,
                             const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetEdgeAntialiasing(frameNode, convValue);
}
void SetOnCompleteImpl(Ark_NativePointer node,
                       const Opt_ImageOnCompleteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetOnComplete(frameNode, convValue);
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_ImageErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetOnError(frameNode, convValue);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetOnFinish(frameNode, convValue);
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetEnableAnalyzer(frameNode, convValue);
}
void SetAnalyzerConfigImpl(Ark_NativePointer node,
                           const Opt_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetAnalyzerConfig(frameNode, convValue);
}
void SetResizableImpl(Ark_NativePointer node,
                      const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetResizable(frameNode, convValue);
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetPrivacySensitive(frameNode, convValue);
}
void SetEnhancedImageQualityImpl(Ark_NativePointer node,
                                 const Opt_image_ResolutionQuality* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetEnhancedImageQuality(frameNode, convValue);
}
void SetOrientationImpl(Ark_NativePointer node,
                        const Opt_ImageRotateOrientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageModelNG::SetSetOrientation(frameNode, convValue);
}
} // ImageAttributeModifier
const GENERATED_ArkUIImageModifier* GetImageModifier()
{
    static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
        ImageModifier::ConstructImpl,
        ImageInterfaceModifier::SetImageOptions0Impl,
        ImageInterfaceModifier::SetImageOptions1Impl,
        ImageAttributeModifier::SetAltImpl,
        ImageAttributeModifier::SetMatchTextDirectionImpl,
        ImageAttributeModifier::SetFitOriginalSizeImpl,
        ImageAttributeModifier::SetFillColorImpl,
        ImageAttributeModifier::SetObjectFitImpl,
        ImageAttributeModifier::SetImageMatrixImpl,
        ImageAttributeModifier::SetObjectRepeatImpl,
        ImageAttributeModifier::SetAutoResizeImpl,
        ImageAttributeModifier::SetRenderModeImpl,
        ImageAttributeModifier::SetDynamicRangeModeImpl,
        ImageAttributeModifier::SetInterpolationImpl,
        ImageAttributeModifier::SetSourceSizeImpl,
        ImageAttributeModifier::SetSyncLoadImpl,
        ImageAttributeModifier::SetColorFilterImpl,
        ImageAttributeModifier::SetCopyOptionImpl,
        ImageAttributeModifier::SetDraggableImpl,
        ImageAttributeModifier::SetPointLightImpl,
        ImageAttributeModifier::SetEdgeAntialiasingImpl,
        ImageAttributeModifier::SetOnCompleteImpl,
        ImageAttributeModifier::SetOnErrorImpl,
        ImageAttributeModifier::SetOnFinishImpl,
        ImageAttributeModifier::SetEnableAnalyzerImpl,
        ImageAttributeModifier::SetAnalyzerConfigImpl,
        ImageAttributeModifier::SetResizableImpl,
        ImageAttributeModifier::SetPrivacySensitiveImpl,
        ImageAttributeModifier::SetEnhancedImageQualityImpl,
        ImageAttributeModifier::SetOrientationImpl,
    };
    return &ArkUIImageModifierImpl;
}

}
