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

#include <cstdint>
#include <utility>

#include "arkoala_api_generated.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/scroll_window_adapter.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"

struct LazyForEachOpsPeer {
    virtual ~LazyForEachOpsPeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyForEachOpsAccessor {
void DestroyPeerImpl(LazyForEachOpsPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new LazyForEachOpsPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}

Ark_NativePointer NeedMoreElementsImpl(Ark_NativePointer node, Ark_NativePointer mark, Ark_Int32 direction)
{
    CHECK_NULL_RETURN(node, nullptr);
    constexpr int32_t requestMoreItemFlag = 0x01;
    auto* parent = reinterpret_cast<FrameNode*>(node);
    auto* scrollWindowAdapter = parent->GetScrollWindowAdapter();
    CHECK_NULL_RETURN(scrollWindowAdapter, reinterpret_cast<Ark_NativePointer>(requestMoreItemFlag));
    return scrollWindowAdapter->NeedMoreElements(
        reinterpret_cast<FrameNode*>(mark), static_cast<FillDirection>(direction));
}

void OnRangeUpdateImpl(Ark_NativePointer node, ArkUI_Int32 totalCount, const Callback_RangeUpdate* updater)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(updater);

    auto onEvent = [callback = CallbackHelper(*updater)](
                       const Ark_Int32 index, const Ark_NativePointer mark) { callback.Invoke(index, mark); };
    auto* scrollWindowAdapter = frameNode->GetOrCreateScrollWindowAdapter();
    CHECK_NULL_VOID(scrollWindowAdapter);
    scrollWindowAdapter->RegisterUpdater(std::move(onEvent));
    scrollWindowAdapter->SetTotalCount(totalCount);
}

void SetCurrentIndexImpl(Ark_NativePointer node, Ark_Int32 index) {}

} // namespace LazyForEachOpsAccessor
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
{
    static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
        LazyForEachOpsAccessor::DestroyPeerImpl,
        LazyForEachOpsAccessor::CtorImpl,
        LazyForEachOpsAccessor::GetFinalizerImpl,
        LazyForEachOpsAccessor::NeedMoreElementsImpl,
        LazyForEachOpsAccessor::OnRangeUpdateImpl,
        LazyForEachOpsAccessor::SetCurrentIndexImpl,
    };
    return &LazyForEachOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
