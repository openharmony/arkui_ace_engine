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
#include "core/interfaces/native/utility/buffer_keeper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageDataAccessor {
void DestroyPeerImpl(Ark_ImageData peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ImageData ConstructImpl(const Ark_Number* width,
                            const Ark_Number* height,
                            const Opt_Buffer* data,
                            const Opt_LengthMetricsUnit* unit)
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
    return PeerUtils::CreatePeer<ImageDataPeer>(imgData);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Buffer GetDataImpl(Ark_ImageData peer)
{
    CHECK_NULL_RETURN(peer, {});
    int64_t size = peer->value.data.size() * sizeof(decltype(peer->value.data)::value_type);
    Ark_Buffer result = BufferKeeper::Allocate(size);
    if (!result.data || result.length < size) {
        return {};
    }
    auto dst = reinterpret_cast<uint32_t*>(result.data);
    std::copy(peer->value.data.begin(), peer->value.data.end(), dst);
    return result;
}
void SetDataImpl(Ark_ImageData peer,
                 const Ark_Buffer* data)
{
    CHECK_NULL_VOID(peer && data && data->data && data->length > 0);
    const uint32_t* ptr = reinterpret_cast<const uint32_t*>(data->data);
    CHECK_NULL_VOID(ptr);
    size_t size = data->length / sizeof(uint32_t);
    peer->value.data.assign(ptr, ptr + size);
}
Ark_Int32 GetHeightImpl(Ark_ImageData peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Int32>(0));
    return Converter::ArkValue<Ark_Int32>(peer->value.dirtyHeight);
}
void SetHeightImpl(Ark_ImageData peer,
                   Ark_Int32 height)
{
    CHECK_NULL_VOID(peer);
    if (Negative(height)) {
        return;
    }
    peer->value.dirtyHeight = height;
}
Ark_Int32 GetWidthImpl(Ark_ImageData peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Int32>(0));
    return Converter::ArkValue<Ark_Int32>(peer->value.dirtyWidth);
}
void SetWidthImpl(Ark_ImageData peer,
                  Ark_Int32 width)
{
    CHECK_NULL_VOID(peer);
    if (Negative(width)) {
        return;
    }
    peer->value.dirtyWidth = width;
}
} // ImageDataAccessor
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor()
{
    static const GENERATED_ArkUIImageDataAccessor ImageDataAccessorImpl {
        ImageDataAccessor::DestroyPeerImpl,
        ImageDataAccessor::ConstructImpl,
        ImageDataAccessor::GetFinalizerImpl,
        ImageDataAccessor::GetDataImpl,
        ImageDataAccessor::SetDataImpl,
        ImageDataAccessor::GetHeightImpl,
        ImageDataAccessor::SetHeightImpl,
        ImageDataAccessor::GetWidthImpl,
        ImageDataAccessor::SetWidthImpl,
    };
    return &ImageDataAccessorImpl;
}

}
