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

#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "image_analyzer_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_ImageAnalyzerType& dst, const ImageAnalyzerType& src, ConvContext* ctx)
{
    switch (src) {
        case ImageAnalyzerType::SUBJECT: dst = ARK_IMAGE_ANALYZER_TYPE_SUBJECT; break;
        case ImageAnalyzerType::TEXT: dst = ARK_IMAGE_ANALYZER_TYPE_TEXT; break;
        default:
            dst = static_cast<Ark_ImageAnalyzerType>(-1);
            LOGE("Unexpected enum value in ImageAnalyzerType: %{public}d", src);
            break;
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAnalyzerControllerAccessor {
void DestroyPeerImpl(Ark_ImageAnalyzerController peer)
{
    auto peerImpl = reinterpret_cast<ImageAnalyzerControllerPeer*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_ImageAnalyzerController ConstructImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<ImageAnalyzerControllerPeer>();
    peerImpl->IncRefCount();
    return Referenced::RawPtr(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_ImageAnalyzerType GetImageAnalyzerSupportTypesImpl(Ark_ImageAnalyzerController peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto types = peer->GetImageAnalyzerSupportTypes();
    return Converter::ArkValue<Array_ImageAnalyzerType>(types, Converter::FC);
}
} // ImageAnalyzerControllerAccessor
const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor()
{
    static const GENERATED_ArkUIImageAnalyzerControllerAccessor ImageAnalyzerControllerAccessorImpl {
        ImageAnalyzerControllerAccessor::DestroyPeerImpl,
        ImageAnalyzerControllerAccessor::ConstructImpl,
        ImageAnalyzerControllerAccessor::GetFinalizerImpl,
        ImageAnalyzerControllerAccessor::GetImageAnalyzerSupportTypesImpl,
    };
    return &ImageAnalyzerControllerAccessorImpl;
}

}
