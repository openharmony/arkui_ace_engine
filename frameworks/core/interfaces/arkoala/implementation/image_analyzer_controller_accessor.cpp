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

#include "core/interfaces/native/node/node_api.h"
#include "arkoala_api_generated.h"
#include "image_analyzer_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"


namespace OHOS::Ace::NG::Converter {

void AssignArkValue(Ark_ImageAnalyzerType& dst, const ImageAnalyzerType& src)
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

void AssignArkValue(Array_ImageAnalyzerType& dst, const std::vector<ImageAnalyzerType>& src)
{
    std::vector<Ark_ImageAnalyzerType> array;
    std::transform(src.begin(), src.end(), std::back_inserter(array),
        [](auto val) { return Converter::ArkValue<Ark_ImageAnalyzerType>(val); });

    dst.array = reinterpret_cast<Ark_ImageAnalyzerType*>(array.data());
    dst.length = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(src.size()));
}

} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAnalyzerControllerAccessor {

static void DestroyPeer(ImageAnalyzerControllerPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_NativePointer CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<ImageAnalyzerControllerPeerImpl>();
    peerImpl->IncRefCount();
    return Referenced::RawPtr(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeer);
}
void GetImageAnalyzerSupportTypesImpl(ImageAnalyzerControllerPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<ImageAnalyzerControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    std::vector<ImageAnalyzerType> src = peerImpl->TriggerGetImageAnalyzerSupportTypes();
    Array_ImageAnalyzerType dst = Converter::ArkValue<Array_ImageAnalyzerType>(src);

    if (dst.length == 0) {
        return;
    }

    LOGE("ARKOALA ImageAnalyzerControllerPeerImpl::GetImageAnalyzerSupportTypesImpl return type not implemented.");
}
} // ImageAnalyzerControllerAccessor
const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor()
{
    static const GENERATED_ArkUIImageAnalyzerControllerAccessor ImageAnalyzerControllerAccessorImpl {
        ImageAnalyzerControllerAccessor::CtorImpl,
        ImageAnalyzerControllerAccessor::GetFinalizerImpl,
        ImageAnalyzerControllerAccessor::GetImageAnalyzerSupportTypesImpl,
    };
    return &ImageAnalyzerControllerAccessorImpl;
}

}