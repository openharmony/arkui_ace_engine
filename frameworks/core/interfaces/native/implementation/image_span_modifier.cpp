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

#include "core/common/multi_thread_build_manager.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/image/image_source_info.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/interfaces/native/implementation/image_common_methods.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "pixel_map_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
ImageSourceInfo CreateSourceInfo(
    const std::string& src, RefPtr<PixelMap>& pixmap, const std::string& bundleName, const std::string& moduleName)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (pixmap) {
        return ImageSourceInfo(pixmap);
    }
#endif
    return { src, bundleName, moduleName };
}
}

namespace ImageSpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    if (MultiThreadBuildManager::IsParallelScope()) {
        LOGF_ABORT("Unsupported UI components ImageSpan used in ParallelizeUI");
    }

    auto imageSpanNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, id, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageSpanNode, nullptr);
    imageSpanNode->SetDraggable(false);

    RefPtr<PixelMap> pixmap = nullptr;
    auto srcInfo = CreateSourceInfo("", pixmap, "", "");
    srcInfo.SetIsUriPureNumber(false);

    auto layoutProperty = imageSpanNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateImageSourceInfo(srcInfo);
    layoutProperty->UpdateHasPlaceHolderStyle(false);

    imageSpanNode->IncRefCount();
    return AceType::RawPtr(imageSpanNode);
}
} // ImageSpanModifier
namespace ImageSpanInterfaceModifier {
void SetImageSpanOptionsImpl(Ark_NativePointer node,
                             const Ark_Union_ResourceStr_image_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto imageSource = Converter::OptConvert<ImageSourceInfo>(*value);
    if (imageSource) {
        ImageSpanViewStatic::SetImageSpanSrc(frameNode, *imageSource);
    }
}
} // ImageSpanInterfaceModifier
namespace ImageSpanAttributeModifier {
void SetVerticalAlignImpl(Ark_NativePointer node,
                          const Opt_ImageSpanAlignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<VerticalAlign>(value);
    if (!convValue) {
        ImageSpanViewStatic::SetVerticalAlign(frameNode, VerticalAlign::BOTTOM);
        return;
    }
    ImageSpanViewStatic::SetVerticalAlign(frameNode, convValue);
}
void SetColorFilterImpl(Ark_NativePointer node,
                        const Opt_Union_ColorFilter_drawing_ColorFilter* value)
{
    ImageCommonMethods::ApplyColorFilterValues(node, value);
}
void SetObjectFitImpl(Ark_NativePointer node,
                      const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<ImageFit>(value);
    if (!convValue) {
        ImageSpanViewStatic::SetObjectFit(frameNode, ImageFit::COVER);
        return;
    }
    ImageSpanViewStatic::SetObjectFit(frameNode, convValue);
}
void SetOnCompleteImpl(Ark_NativePointer node,
                       const Opt_ImageCompleteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onComplete = [arkCallback = CallbackHelper(*optValue)](const LoadImageSuccessEvent& info) {
        Ark_ImageLoadResult result = Converter::ArkValue<Ark_ImageLoadResult>(info);
        arkCallback.InvokeSync(result);
    };
    ImageSpanView::SetOnComplete(frameNode, std::move(onComplete));
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_ImageErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*optValue)](const LoadImageFailEvent& info) {
        Ark_ImageError result = Converter::ArkValue<Ark_ImageError>(info);
        arkCallback.InvokeSync(result);
    };
    ImageSpanView::SetOnError(frameNode, std::move(onError));
}
void SetAltImpl(Ark_NativePointer node,
                const Opt_image_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto pixelMapPeer = *optValue;
    if (pixelMapPeer) {
        ImageModelNG::SetAlt(frameNode, ImageSourceInfo(pixelMapPeer->pixelMap));
    }
}
} // ImageSpanAttributeModifier
const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
        ImageSpanModifier::ConstructImpl,
        ImageSpanInterfaceModifier::SetImageSpanOptionsImpl,
        ImageSpanAttributeModifier::SetVerticalAlignImpl,
        ImageSpanAttributeModifier::SetColorFilterImpl,
        ImageSpanAttributeModifier::SetObjectFitImpl,
        ImageSpanAttributeModifier::SetOnCompleteImpl,
        ImageSpanAttributeModifier::SetOnErrorImpl,
        ImageSpanAttributeModifier::SetAltImpl,
    };
    return &ArkUIImageSpanModifierImpl;
}

}
