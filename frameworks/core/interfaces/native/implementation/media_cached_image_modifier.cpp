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
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "animated_drawable_descriptor_peer.h"
namespace OHOS::Ace::NG::GeneratedModifier {
namespace MediaCachedImageModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    RefPtr<PixelMap> pixmap = nullptr;
    auto frameNode = ImageModelNG::CreateFrameNode(id, "", pixmap, "", "", false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // MediaCachedImageModifier
namespace MediaCachedImageInterfaceModifier {
void SetMediaCachedImageOptionsImpl(Ark_NativePointer node,
                                    const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource* src)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    Converter::VisitUnion(
        *src,
        [frameNode](const Ark_PixelMap& pixmap) {
            auto pixelMapPeer = pixmap;
            ImageModelNG::SetInitialPixelMap(frameNode, pixelMapPeer->pixelMap);
        },
        [&frameNode](const Ark_ResourceStr& src) {
            auto info = Converter::OptConvert<ImageSourceInfo>(src);
            if (info) {
                ImageModelNG::SetInitialSrc(frameNode, info->GetSrc(), info->GetBundleName(), info->GetModuleName(),
                    info->GetIsUriPureNumber());
            }
        },
        [frameNode](const Ark_DrawableDescriptor drawableDescriptor) {
            CHECK_NULL_VOID(drawableDescriptor);
            auto animatedDrawableDescriptor = AceType::DynamicCast<AnimatedDrawableDescriptorPeer>(drawableDescriptor);
            if (animatedDrawableDescriptor) {
                std::vector<ImageProperties> imageList;
                auto pixelMaps = animatedDrawableDescriptor->GetPixelMapList();
                for (int i = 0; i < pixelMaps.size(); i++) {
                    ImageProperties image;
                    image.pixelMap = pixelMaps[i];
                    imageList.push_back(image);
                }
                ImageModelNG::CreateAnimation(frameNode, imageList,
                    animatedDrawableDescriptor->GetDuration(),
                    animatedDrawableDescriptor->GetIterations());
            } else {
                auto pixelMap = drawableDescriptor->GetPixelMap();
                ImageModelNG::SetInitialPixelMap(frameNode, pixelMap);
            }
        },
        [frameNode](const Ark_ASTCResource& astcResource) {
            // no need to do anything
        },
        []() {});
}
} // MediaCachedImageInterfaceModifier
const GENERATED_ArkUIMediaCachedImageModifier* GetMediaCachedImageModifier()
{
    static const GENERATED_ArkUIMediaCachedImageModifier ArkUIMediaCachedImageModifierImpl {
        MediaCachedImageModifier::ConstructImpl,
        MediaCachedImageInterfaceModifier::SetMediaCachedImageOptionsImpl,
    };
    return &ArkUIMediaCachedImageModifierImpl;
}

}
