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
#include "core/interfaces/native/implementation/children_main_size_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ChildrenMainSizeAccessor {

constexpr float DEFAULT_SIZE = -1.0f;

void DestroyPeerImpl(Ark_ChildrenMainSize peer)
{
    delete peer;
}
Ark_ChildrenMainSize CtorImpl(const Ark_Number* childDefaultSize)
{
    CHECK_NULL_RETURN(childDefaultSize, nullptr);
    float size = Converter::Convert<float>(*childDefaultSize);
    return NonNegative(size) ? new ChildrenMainSizePeer(size) : nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SpliceImpl(Ark_VMContext vmContext,
                Ark_ChildrenMainSize peer,
                const Ark_Number* start,
                const Opt_Number* deleteCount,
                const Opt_Array_Number* childrenSize)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(start);

    auto handler = peer->GetHandler();
    CHECK_NULL_VOID(handler);

    auto convStart = Converter::Convert<int32_t>(*start);
    if (convStart < 0) {
        return; // throw an exception by TS
    }
    auto convDeleteCount = deleteCount ? Converter::OptConvert<int32_t>(*deleteCount) : std::nullopt;
    if (convDeleteCount.has_value() && convDeleteCount.value() < 0) {
        convDeleteCount = 0;
    }
    auto delCount = convDeleteCount.value_or(-1); // -1 update all from 'start'

    auto convFloatArray = childrenSize ? Converter::OptConvert<std::vector<float>>(*childrenSize) : std::nullopt;
    auto floatArray = convFloatArray.value_or(std::vector<float>());
    std::for_each(floatArray.begin(), floatArray.end(), [](float& size) {
        if (size < 0.0f) {
            size = DEFAULT_SIZE; // -1 represent default size.
        }
    });

    handler->ChangeData(convStart, delCount, floatArray);
}
void UpdateImpl(Ark_VMContext vmContext,
                Ark_ChildrenMainSize peer,
                const Ark_Number* index,
                const Ark_Number* childSize)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(index);
    CHECK_NULL_VOID(childSize);

    auto handler = peer->GetHandler();
    CHECK_NULL_VOID(handler);

    auto convIndex = Converter::Convert<int32_t>(*index);
    if (convIndex < 0) {
        return; // throw an exception by TS
    }
    auto convChildSize = Converter::Convert<float>(*childSize);
    auto array = std::vector<float>{convChildSize >= 0 ? convChildSize : DEFAULT_SIZE};
    handler->ChangeData(convIndex, 1, array);
}
Ark_Number GetChildDefaultSizeImpl(Ark_ChildrenMainSize peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    auto handler = peer->GetHandler();
    CHECK_NULL_RETURN(handler, errValue);
    return Converter::ArkValue<Ark_Number>(static_cast<float>(handler->GetChildSize(-1)));
}
void SetChildDefaultSizeImpl(Ark_ChildrenMainSize peer,
                             const Ark_Number* childDefaultSize)
{
    CHECK_NULL_VOID(peer && childDefaultSize);
    float size = Converter::Convert<float>(*childDefaultSize);
    if (NonNegative(size)) {
        peer->SetDefaultSize(size);
    }
}
} // ChildrenMainSizeAccessor
const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor()
{
    static const GENERATED_ArkUIChildrenMainSizeAccessor ChildrenMainSizeAccessorImpl {
        ChildrenMainSizeAccessor::DestroyPeerImpl,
        ChildrenMainSizeAccessor::CtorImpl,
        ChildrenMainSizeAccessor::GetFinalizerImpl,
        ChildrenMainSizeAccessor::SpliceImpl,
        ChildrenMainSizeAccessor::UpdateImpl,
        ChildrenMainSizeAccessor::GetChildDefaultSizeImpl,
        ChildrenMainSizeAccessor::SetChildDefaultSizeImpl,
    };
    return &ChildrenMainSizeAccessorImpl;
}

}
