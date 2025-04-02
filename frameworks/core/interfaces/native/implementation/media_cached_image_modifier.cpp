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

namespace OHOS::Ace::NG {
namespace {
struct ASTCdata {
    std::vector<std::string> sources;
    int32_t column;
};
} // namespace

namespace Converter {
template<>
void AssignCast(std::optional<ImageSourceInfo>& dst, const Ark_ASTCResource& src)
{
    auto sources = OptConvert<ASTCdata>(src);
    if (sources) {
        dst.reset();
    }
}

template<>
void AssignCast(std::optional<ASTCdata>& dst, const Ark_ASTCResource& src)
{
    auto sources = Convert<std::vector<std::string>>(src.sources);
    if (sources.empty()) {
        dst.reset();
        return;
    }
    dst->sources = std::move(sources);
    dst->column = Convert<int32_t>(src.column);
}
} // Converter
} // OHOS::Ace::NG


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
    auto info = Converter::OptConvert<ImageSourceInfo>(*src);
    // Note.
    // This function should skip InitImage invocation if info's optional is empty.
    if (info) {
        if (info->GetPixmap()) {
            auto pixelMap = info->GetPixmap(); // GetPixmap return const RefPtr
            ImageModelNG::SetInitialPixelMap(frameNode, pixelMap);
        } else {
            ImageModelNG::SetInitialSrc(frameNode, info->GetSrc(), info->GetBundleName(),
                info->GetModuleName(), info->GetIsUriPureNumber());
        }
    }
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
