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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageDataAccessor {
void DestroyPeerImpl(Ark_ImageData peer)
{
}
Ark_ImageData CtorImpl(const Ark_Number* width,
                       const Ark_Number* height,
                       const Opt_Buffer* data)
{
    CHECK_NULL_RETURN(width && height, nullptr);
    auto widthConv = Converter::Convert<int32_t>(*width);
    auto heightConv = Converter::Convert<int32_t>(*height);
    if (Negative(widthConv) || Negative(heightConv)) {
        return nullptr;
    }

    OHOS::Ace::ImageData imgData = {.dirtyWidth = widthConv, .dirtyHeight = heightConv};
    if (data != nullptr) {
        auto dataOpt = Converter::OptConvert<std::vector<uint32_t>>(*data);
        auto size = dataOpt.has_value() ? dataOpt.value().size() : 0;
        if (size > 0) {
            imgData.data = std::move(dataOpt.value());
        }
    }
    return ImageDataPeer::Create(imgData);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Buffer GetDataImpl(Ark_ImageData peer)
{
    return {};
}
Ark_Number GetHeightImpl(Ark_ImageData peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    return Converter::ArkValue<Ark_Number>(peer->value.dirtyHeight);
}
Ark_Number GetWidthImpl(Ark_ImageData peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    return Converter::ArkValue<Ark_Number>(peer->value.dirtyWidth);
}
} // ImageDataAccessor
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor()
{
    static const GENERATED_ArkUIImageDataAccessor ImageDataAccessorImpl {
        ImageDataAccessor::DestroyPeerImpl,
        ImageDataAccessor::CtorImpl,
        ImageDataAccessor::GetFinalizerImpl,
        ImageDataAccessor::GetDataImpl,
        ImageDataAccessor::GetHeightImpl,
        ImageDataAccessor::GetWidthImpl,
    };
    return &ImageDataAccessorImpl;
}

struct ImageDataPeer {
    virtual ~ImageDataPeer() = default;
};
}
