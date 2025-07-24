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
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_component.h"
#include "core/components_ng/pattern/image/image_model_static.h"
#include "core/interfaces/native/implementation/image_common_methods.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG {
namespace {
// similar as in the js_image.cpp
constexpr float CEIL_SMOOTHEDGE_VALUE = 1.333f;
constexpr float FLOOR_SMOOTHEDGE_VALUE = 0.334f;
constexpr int32_t SELECTOR_INDEX = 3;
} // namespace

namespace Converter {
template<>
void AssignCast(std::optional<std::pair<CalcDimension, CalcDimension>>& dst,
    const Ark_ImageSourceSize& src)
{
    auto width = Converter::OptConvert<float>(src.width);
    auto height = Converter::OptConvert<float>(src.height);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonNegative(height);
    if (width && height) {
        CalcDimension calcWidth(*width, DimensionUnit::VP);
        CalcDimension calcHeight(*height, DimensionUnit::VP);
        dst = std::make_pair(calcWidth, calcHeight);
    }
}
template<>
void AssignCast(std::optional<ImageSourceInfo>& dst, const Ark_ImageContent& src)
{
    dst.reset();
}

template<>
void AssignCast(std::optional<ImageRotateOrientation>& dst, const Ark_ImageRotateOrientation& src)
{
    switch (src) {
        case ARK_IMAGE_ROTATE_ORIENTATION_AUTO: dst = ImageRotateOrientation::AUTO; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_UP: dst = ImageRotateOrientation::UP; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_RIGHT: dst = ImageRotateOrientation::RIGHT; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_DOWN: dst = ImageRotateOrientation::DOWN; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_LEFT: dst = ImageRotateOrientation::LEFT; break;
        default: LOGE("Unexpected enum value in Ark_ImageRotateOrientation: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<ImageSourceInfo>& dst, const Ark_Union_String_Resource_PixelMap& src)
{
    Converter::VisitUnion(src,
        [&dst](const Ark_String& val) {
            dst = Converter::OptConvert<ImageSourceInfo>(val);
        },
        [&dst](const Ark_Resource& val) {
            dst = Converter::OptConvert<ImageSourceInfo>(val);
        },
        [&dst](const Ark_PixelMap& val) {
            dst = std::nullopt;
            auto pixMapRefPtr = Converter::OptConvert<RefPtr<PixelMap>>(val).value_or(nullptr);
            if (pixMapRefPtr) {
                dst = ImageSourceInfo(pixMapRefPtr);
            }
        },
        []() {}
    );
}
} // Converter
} // OHOS::Ace::NG

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
        std::string source = info->GetSrc();
        ImageModelNG::InitImage(frameNode, source);
    }
}
void SetImageOptions1Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    if (src->selector == SELECTOR_INDEX) {
        ImageModelNG::ResetImageSrc(frameNode);
        return;
    }
    auto info = Converter::OptConvert<ImageSourceInfo>(*src);
    // Note.
    // This function should skip InitImage invocation if info's optional is empty.
    if (info) {
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        std::string source = info->GetSrc();
        ImageModelNG::InitImage(frameNode, source);
    }
}
void SetImageOptions2Impl(Ark_NativePointer node,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                          const Ark_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("Arkoala: Image.SetImageOptions2Impl - method not implemented");
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void AltImpl(Ark_NativePointer node,
             const Opt_Union_String_Resource_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto info = Converter::OptConvert<ImageSourceInfo>(*value);
    if (!info.has_value() || ImageSourceInfo::ResolveURIType(info->GetSrc()) == SrcType::NETWORK) {
        ImageModelStatic::SetAlt(frameNode, std::nullopt);
        return;
    }
    ImageModelStatic::SetAlt(frameNode, info);
}
void MatchTextDirectionImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetMatchTextDirection(frameNode, *convValue);
}
void FitOriginalSizeImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetFitOriginSize(frameNode, *convValue);
}
void FillColor0Impl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageFill(frameNode, Converter::OptConvert<Color>(*value));
}
void FillColor1Impl(Ark_NativePointer node,
                    const Opt_Union_ResourceColor_ColorContent* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ObjectFitImpl(Ark_NativePointer node,
                   const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fit = Converter::OptConvert<ImageFit>(*value);
    ImageModelStatic::SetImageFit(frameNode, fit);
}
void ImageMatrixImpl(Ark_NativePointer node,
                     const Opt_Matrix4Transit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ObjectRepeatImpl(Ark_NativePointer node,
                      const Opt_ImageRepeat* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageRepeat(frameNode, Converter::OptConvert<ImageRepeat>(*value));
}
void AutoResizeImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetAutoResize(frameNode, *convValue);
}
void RenderModeImpl(Ark_NativePointer node,
                    const Opt_ImageRenderMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageRenderMode(frameNode, Converter::OptConvert<ImageRenderMode>(*value));
}
void DynamicRangeModeImpl(Ark_NativePointer node,
                          const Opt_DynamicRangeMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetDynamicRangeMode(frameNode, Converter::OptConvert<DynamicRangeMode>(*value));
}
void InterpolationImpl(Ark_NativePointer node,
                       const Opt_ImageInterpolation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageInterpolation(frameNode, Converter::OptConvert<ImageInterpolation>(*value));
}
void SourceSizeImpl(Ark_NativePointer node,
                    const Opt_ImageSourceSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto sourceSize = Converter::OptConvert<std::pair<CalcDimension, CalcDimension>>(*value);
    ImageModelStatic::SetImageSourceSize(frameNode, sourceSize);
}
void SyncLoadImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetSyncMode(frameNode, *convValue);
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
    ImageCommonMethods::ApplyColorFilterValues(node, value);
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(*value));
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetDraggable(frameNode, *convValue);
}
void PointLightImpl(Ark_NativePointer node,
                    const Opt_PointLightStyle* value)
{
#ifdef POINT_LIGHT_ENABLE
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pointLightStyle = Converter::OptConvert<Converter::PointLightStyle>(*value);
    auto uiNode = reinterpret_cast<Ark_NodeHandle>(node);
    auto themeConstants = Converter::GetThemeConstants(uiNode, "", "");
    CHECK_NULL_VOID(themeConstants);
    if (pointLightStyle) {
        if (pointLightStyle->lightSource) {
            ViewAbstractModelStatic::SetLightPosition(frameNode, pointLightStyle->lightSource->x,
                pointLightStyle->lightSource->y,
                pointLightStyle->lightSource->z);
            ViewAbstractModelStatic::SetLightIntensity(frameNode,
                pointLightStyle->lightSource->intensity);
            ViewAbstractModelStatic::SetLightColor(frameNode, pointLightStyle->lightSource->lightColor);
        } else {
            ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
            ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
            ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        }
        // illuminated
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, pointLightStyle->illuminationType, themeConstants);
        // bloom
        ViewAbstractModelStatic::SetBloom(frameNode, pointLightStyle->bloom, themeConstants);
    } else {
        ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
        ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, std::nullopt, themeConstants);
        ViewAbstractModelStatic::SetBloom(frameNode, std::nullopt, themeConstants);
    }
#endif
}
void EdgeAntialiasingImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateByRange(convValue, FLOOR_SMOOTHEDGE_VALUE, CEIL_SMOOTHEDGE_VALUE);
    ImageModelStatic::SetSmoothEdge(frameNode, convValue);
}
void OnCompleteImpl(Ark_NativePointer node,
                    const Opt_Callback_Type_ImageAttribute_onComplete_callback_event_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](const LoadImageSuccessEvent& info) {
        Ark_Type_ImageAttribute_onComplete_callback_event event;
        event.width = Converter::ArkValue<Ark_Number>(info.GetWidth());
        event.height = Converter::ArkValue<Ark_Number>(info.GetHeight());
        event.componentWidth = Converter::ArkValue<Ark_Number>(info.GetComponentWidth());
        event.componentHeight = Converter::ArkValue<Ark_Number>(info.GetComponentHeight());
        event.loadingStatus = Converter::ArkValue<Ark_Number>(info.GetLoadingStatus());
        event.contentOffsetX = Converter::ArkValue<Ark_Number>(info.GetContentOffsetX());
        event.contentOffsetY = Converter::ArkValue<Ark_Number>(info.GetContentOffsetY());
        event.contentWidth = Converter::ArkValue<Ark_Number>(info.GetContentWidth());
        event.contentHeight = Converter::ArkValue<Ark_Number>(info.GetContentHeight());
        auto optEvent = Converter::ArkValue<Opt_Type_ImageAttribute_onComplete_callback_event>(event);
        callback.Invoke(optEvent);
    };
    ImageModelNG::SetOnComplete(frameNode, std::move(onEvent));
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_ImageErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*optValue)](const LoadImageFailEvent& info) {
        auto arkInfo = Converter::ArkValue<Ark_ImageError>(info);
        arkCallback.Invoke(arkInfo);
    };
    ImageModelNG::SetOnError(frameNode, std::move(onError));
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(onFinish));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::EnableAnalyzer(frameNode, *convValue);
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Opt_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    ImageModelNG::SetImageAnalyzerConfig(frameNode, reinterpret_cast<void*>(optValue->types.array));
}
void ResizableImpl(Ark_NativePointer node,
                   const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageResizableSlice defSliceValue {};
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageModelNG::SetResizableSlice(frameNode, defSliceValue);
        return;
    }
    auto convSliceValue = Converter::OptConvert<ImageResizableSlice>(optValue->slice).value_or(defSliceValue);
    if (convSliceValue.bottom.IsValid() && convSliceValue.right.IsValid()) {
        ImageModelNG::SetResizableSlice(frameNode, convSliceValue);
    } else {
        ImageModelNG::SetResizableSlice(frameNode, defSliceValue);
    }
    // lattice .. This parameter will need to be implemented when Ark_DrawingLattice is supported.
    LOGE("Arkoala: Image.ResizableImpl - method not implemented");
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        return;
    }
    ViewAbstract::SetPrivacySensitive(frameNode, *convValue);
}
void EnhancedImageQualityImpl(Ark_NativePointer node,
                              const Opt_ResolutionQuality* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<AIImageQuality>(*value);
    ImageModelStatic::SetEnhancedImageQuality(frameNode, convValue);
}
void OrientationImpl(Ark_NativePointer node,
                     const Opt_ImageRotateOrientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ImageRotateOrientation>(*value);
    ImageModelStatic::SetOrientation(frameNode, convValue);
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
