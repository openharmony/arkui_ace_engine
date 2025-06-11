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
#include <utility>

#include "arkoala_api_generated.h"

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
void OnRangeUpdateImpl(Ark_NativePointer node,
                       Ark_Int32 totalCount,
                       const Callback_RangeUpdate* updater)
{
}
void SetCurrentIndexImpl(Ark_NativePointer node,
                         Ark_Int32 index)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void PrepareImpl(Ark_NativePointer node, Ark_Int32, Ark_Int32)
{
}
void NotifyChangeImpl(Ark_NativePointer node, int32_t startIdx, int32_t endIdx, int32_t changeCnt)
{
}
} // LazyForEachOpsAccessor
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
{
    static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
        LazyForEachOpsAccessor::NeedMoreElementsImpl,
        LazyForEachOpsAccessor::OnRangeUpdateImpl,
        LazyForEachOpsAccessor::SetCurrentIndexImpl,
        LazyForEachOpsAccessor::PrepareImpl,
        LazyForEachOpsAccessor::NotifyChangeImpl,
    };
    return &LazyForEachOpsAccessorImpl;
}

}
