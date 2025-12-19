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
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/image/image_model_static.h"
#include "core/interfaces/native/implementation/image_common_methods.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/implementation/content_transition_effect_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_color_filter_peer.h"
#include "core/interfaces/native/implementation/drawing_lattice_peer.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t UNION_ONE = 1;
// similar as in the js_image.cpp
constexpr float CEIL_SMOOTHEDGE_VALUE = 1.333f;
constexpr float FLOOR_SMOOTHEDGE_VALUE = 0.334f;
constexpr int32_t SELECTOR_INDEX = 3;
constexpr float DEFAULT_HDR_BRIGHTNESS = 1.0f;
constexpr float HDR_BRIGHTNESS_MIN = 0.0f;
constexpr float HDR_BRIGHTNESS_MAX = 1.0f;
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
        case ARK_IMAGE_ROTATE_ORIENTATION_UP_MIRRORED: dst = ImageRotateOrientation::UP_MIRRORED; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_RIGHT_MIRRORED: dst = ImageRotateOrientation::RIGHT_MIRRORED; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_DOWN_MIRRORED: dst = ImageRotateOrientation::DOWN_MIRRORED; break;
        case ARK_IMAGE_ROTATE_ORIENTATION_LEFT_MIRRORED: dst = ImageRotateOrientation::LEFT_MIRRORED; break;
        default: LOGE("Unexpected enum value in Ark_ImageRotateOrientation: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<Color>& dst, const Ark_ColorContent& src)
{
    // Currently ColorContent have only one value: ORIGIN
    // which corresponds to default value. We reset to default value when optional is empty.
    // So, all we need to do is reset optional.
    // Need to check that ColorContent is indeed ORIGIN. There can be other types in future.
    dst.reset();
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
void SetImageOptionsImpl(Ark_NativePointer node,
                         const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src,
                         const Opt_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    Converter::VisitUnion(*src,
        [frameNode](const Ark_DrawableDescriptor& value) {
            auto desc = Converter::Convert<DrawableDescriptor *>(value);
            ImageModelStatic::SetDrawableDescriptor(frameNode, desc);
        },
        [frameNode](const auto& value) {
            auto info = Converter::OptConvert<ImageSourceInfo>(value);
            // Note.
            // This function should skip InitImage invocation if info's optional is empty.
            CHECK_NULL_VOID(info);
            if (auto pixelMap = info->GetPixmap(); pixelMap) {
                ImageModelNG::SetInitialPixelMap(frameNode, pixelMap);
            } else {
                ImageModelNG::SetInitialSrc(frameNode, info->GetSrc(), info->GetBundleName(),
                    info->GetModuleName(), info->GetIsUriPureNumber());
            }
        },
        []() {});
    CHECK_NULL_VOID(imageAIOptions);
}
} // ImageInterfaceModifier
namespace ImageAttributeModifier {
void SetAltImpl(Ark_NativePointer node, const Opt_Union_String_Resource_PixelMap_ImageAlt* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag != INTEROP_TAG_UNDEFINED && value->value.selector == SELECTOR_ID_3) {
        auto imageAltPlaceholder = Converter::OptConvert<ImageSourceInfo>(value->value.value3.placeholder);
        if (imageAltPlaceholder.has_value() &&
            ImageSourceInfo::ResolveURIType(imageAltPlaceholder->GetSrc()) != SrcType::NETWORK) {
            ImageModelStatic::SetAltPlaceholder(frameNode, imageAltPlaceholder);
        }
        auto imageAltError = Converter::OptConvert<ImageSourceInfo>(value->value.value3.error);
        if (imageAltError.has_value()) {
            ImageModelStatic::SetAltError(frameNode, imageAltError);
        }
    } else {
        auto info = Converter::OptConvertPtr<ImageSourceInfo>(value);
        if (!info.has_value() || ImageSourceInfo::ResolveURIType(info->GetSrc()) == SrcType::NETWORK) {
            ImageModelStatic::SetAlt(frameNode, std::nullopt);
            return;
        }
        ImageModelStatic::SetAlt(frameNode, info);
    }
}
void SetMatchTextDirectionImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelNG::SetMatchTextDirection(frameNode, false);
        return;
    }
    ImageModelNG::SetMatchTextDirection(frameNode, *convValue);
}
void SetFitOriginalSizeImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelNG::SetFitOriginSize(frameNode, false);
        return;
    }
    ImageModelNG::SetFitOriginSize(frameNode, *convValue);
}
void SetFillColorImpl(Ark_NativePointer node,
                      const Opt_Union_ResourceColor_ColorContent_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->value.selector == UNION_ONE) {
        ImageModelNG::ResetImageFill(frameNode);
        return;
    }
    ImageModelStatic::SetImageFill(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetObjectFitImpl(Ark_NativePointer node,
                      const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fit = Converter::OptConvertPtr<ImageFit>(value);
    ImageModelStatic::SetImageFit(frameNode, fit);
}
void SetImageMatrixImpl(Ark_NativePointer node,
                        const Opt_matrix4_Matrix4Transit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto matrixOpt = Converter::OptConvertPtr<Matrix4>(value);
    ImageModelStatic::SetImageMatrix(frameNode, matrixOpt);
}
void SetObjectRepeatImpl(Ark_NativePointer node,
                         const Opt_ImageRepeat* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageRepeat(frameNode, Converter::OptConvertPtr<ImageRepeat>(value));
}
void SetAutoResizeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelNG::ResetAutoResize(frameNode);
        return;
    }
    ImageModelNG::SetAutoResize(frameNode, *convValue);
}
void SetRenderModeImpl(Ark_NativePointer node,
                       const Opt_ImageRenderMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageRenderMode(frameNode, Converter::OptConvertPtr<ImageRenderMode>(value));
}
void SetDynamicRangeModeImpl(Ark_NativePointer node,
                             const Opt_DynamicRangeMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetDynamicRangeMode(frameNode, Converter::OptConvertPtr<DynamicRangeMode>(value));
}
void SetHdrBrightnessImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateByRange(convValue, HDR_BRIGHTNESS_MIN, HDR_BRIGHTNESS_MAX);
    ImageModelStatic::SetHdrBrightness(frameNode, convValue.value_or(DEFAULT_HDR_BRIGHTNESS));
}
void SetInterpolationImpl(Ark_NativePointer node,
                          const Opt_ImageInterpolation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetImageInterpolation(frameNode, Converter::OptConvertPtr<ImageInterpolation>(value));
}
void SetSourceSizeImpl(Ark_NativePointer node,
                       const Opt_ImageSourceSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto sourceSize = Converter::OptConvert<std::pair<CalcDimension, CalcDimension>>(*value);
    std::pair<CalcDimension, CalcDimension> defaultSize =
        std::make_pair(CalcDimension(0.0, DimensionUnit::VP), CalcDimension(0.0, DimensionUnit::VP));
    ImageModelStatic::SetImageSourceSize(frameNode, sourceSize.value_or(defaultSize));
}
void SetSyncLoadImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelNG::SetSyncMode(frameNode, false);
        return;
    }
    ImageModelNG::SetSyncMode(frameNode, *convValue);
}
void SetColorFilterImpl(Ark_NativePointer node,
                        const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
    ImageCommonMethods::ApplyColorFilterValues(node, value);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelStatic::SetCopyOption(frameNode, Converter::OptConvertPtr<CopyOptions>(value));
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelStatic::ResetDraggable(frameNode);
        return;
    }
    ImageModelNG::SetDraggable(frameNode, *convValue);
}
void SetPointLightImpl(Ark_NativePointer node,
                       const Opt_PointLightStyle* value)
{
#ifdef POINT_LIGHT_ENABLE
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pointLightStyle = Converter::OptConvertPtr<Converter::PointLightStyle>(value);
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
void SetEdgeAntialiasingImpl(Ark_NativePointer node,
                             const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateByRange(convValue, FLOOR_SMOOTHEDGE_VALUE, CEIL_SMOOTHEDGE_VALUE);
    ImageModelStatic::SetSmoothEdge(frameNode, convValue);
}
void SetOnCompleteImpl(Ark_NativePointer node,
                       const Opt_ImageOnCompleteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageModelNG::SetOnComplete(frameNode, nullptr);
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](const LoadImageSuccessEvent& info) {
        Ark_ImageCompleteEvent event;
        event.width = Converter::ArkValue<Ark_Int32>(info.GetWidth());
        event.height = Converter::ArkValue<Ark_Int32>(info.GetHeight());
        event.componentWidth = Converter::ArkValue<Ark_Int32>(info.GetComponentWidth());
        event.componentHeight = Converter::ArkValue<Ark_Int32>(info.GetComponentHeight());
        event.loadingStatus = Converter::ArkValue<Ark_Int32>(info.GetLoadingStatus());
        event.contentOffsetX = Converter::ArkValue<Ark_Int32>(info.GetContentOffsetX());
        event.contentOffsetY = Converter::ArkValue<Ark_Int32>(info.GetContentOffsetY());
        event.contentWidth = Converter::ArkValue<Ark_Int32>(info.GetContentWidth());
        event.contentHeight = Converter::ArkValue<Ark_Int32>(info.GetContentHeight());
        auto optEvent = Converter::ArkValue<Opt_ImageCompleteEvent>(event);
        callback.Invoke(optEvent);
    };
    ImageModelNG::SetOnComplete(frameNode, std::move(onEvent));
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_ImageErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageModelNG::SetOnError(frameNode, nullptr);
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*optValue)](const LoadImageFailEvent& info) {
        auto arkInfo = Converter::ArkValue<Ark_ImageError>(info);
        arkCallback.Invoke(arkInfo);
    };
    ImageModelNG::SetOnError(frameNode, std::move(onError));
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ImageModelNG::SetOnSvgPlayFinish(frameNode, nullptr);
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(onFinish));
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ImageModelNG::EnableAnalyzer(frameNode, false);
        return;
    }
    ImageModelNG::EnableAnalyzer(frameNode, *convValue);
}
void SetAnalyzerConfigImpl(Ark_NativePointer node,
                           const Opt_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    ImageModelNG::SetImageAnalyzerConfig(frameNode, reinterpret_cast<void*>(optValue->types.array));
}
void SetResizableImpl(Ark_NativePointer node,
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
    if (optValue->lattice.value) {
        ImageModelStatic::SetResizableLattice(frameNode, optValue->lattice.value->drawingLattice);
        drawing_LatticePeer::Destroy(optValue->lattice.value);
    }
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ViewAbstractModelStatic::SetPrivacySensitive(frameNode, convValue);
}
void SetEnhancedImageQualityImpl(Ark_NativePointer node,
                                 const Opt_image_ResolutionQuality* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetOrientationImpl(Ark_NativePointer node,
                        const Opt_ImageRotateOrientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<ImageRotateOrientation>(value);
    ImageModelStatic::SetOrientation(frameNode, convValue);
}
void SetSupportSvg2Impl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (convValue) {
        ImageModelStatic::SetSupportSvg2(frameNode, convValue.value());
    } else {
        ImageModelStatic::SetSupportSvg2(frameNode, false);
    }
}
void SetContentTransitionImpl(Ark_NativePointer node, const Opt_ContentTransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (optValue.has_value()) {
        auto* peer = optValue.value();
        CHECK_NULL_VOID(peer);
        ImageModelStatic::SetContentTransition(frameNode, peer->type_);
    }
}
} // namespace ImageAttributeModifier
const GENERATED_ArkUIImageModifier* GetImageModifier()
{
    static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
        ImageModifier::ConstructImpl,
        ImageInterfaceModifier::SetImageOptionsImpl,
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
        ImageAttributeModifier::SetHdrBrightnessImpl,
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
        ImageAttributeModifier::SetSupportSvg2Impl,
        ImageAttributeModifier::SetContentTransitionImpl,
    };
    return &ArkUIImageModifierImpl;
}

}
