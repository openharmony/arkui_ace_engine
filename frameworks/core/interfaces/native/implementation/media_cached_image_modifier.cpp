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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MediaCachedImageModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // MediaCachedImageModifier
namespace MediaCachedImageInterfaceModifier {
void SetMediaCachedImageOptionsImpl(Ark_NativePointer node,
                                    const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource* src)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    //auto convValue = Converter::OptConvert<type_name>(*src);
    //MediaCachedImageModelNG::SetSetMediaCachedImageOptions(frameNode, convValue);
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
