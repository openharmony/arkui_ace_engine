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

#include <cstdint>

#include "arkoala_api_generated.h"
#include "ui/base/utils/utils.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyForEachOpsAccessor {
Ark_NativePointer NeedMoreElementsImpl(Ark_NativePointer node, Ark_NativePointer mark, Ark_Int32 direction)
{
    return nullptr;
}
void OnRangeUpdateImpl(Ark_NativePointer node, Ark_Int32 totalCount, const Callback_RangeUpdate* updater) {}
void SetCurrentIndexImpl(Ark_NativePointer node, Ark_Int32 index) {}
void PrepareImpl(Ark_NativePointer node, Ark_Int32 totalCount, Ark_Int32 offset) {}
void NotifyChangeImpl(Ark_NativePointer node, int32_t startIdx, int32_t endIdx, int32_t changeCnt)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (startIdx >= 0) {
        frameNode->ChildrenUpdatedFrom(startIdx);
    }
    if (endIdx >= 0) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->NotifyDataChange(endIdx, changeCnt);
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode->ArkoalaRemoveItemsOnChange(startIdx);
}

void SyncImpl(Ark_NativePointer node, Ark_Int32 totalCount, const Callback_CreateItem* creator,
    const Callback_RangeUpdate* updater)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode && creator && updater);
    frameNode->ArkoalaSynchronize(
        [callback = CallbackHelper(*creator)](
            int32_t index) { return AceType::DynamicCast<FrameNode>(callback.BuildSync(index)); },
        [cb = CallbackHelper(*updater)](int32_t start, int32_t end) { cb.InvokeSync(start, end); }, totalCount);
}
} // namespace LazyForEachOpsAccessor
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
{
    static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
        LazyForEachOpsAccessor::NeedMoreElementsImpl,
        LazyForEachOpsAccessor::OnRangeUpdateImpl,
        LazyForEachOpsAccessor::SetCurrentIndexImpl,
        LazyForEachOpsAccessor::PrepareImpl,
        LazyForEachOpsAccessor::NotifyChangeImpl,
        LazyForEachOpsAccessor::SyncImpl,
    };
    return &LazyForEachOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
