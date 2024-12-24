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
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer NeedMoreElementsImpl(Ark_NativePointer node,
                                       Ark_NativePointer mark,
                                       Ark_Int32 direction)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetNeedMoreElements(frameNode, convValue);
    return nullptr;
}
void OnRangeUpdateImpl(Ark_NativePointer node,
                       const Callback_RangeUpdate* updater)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetOnRangeUpdate(frameNode, convValue);
}
} // LazyForEachOpsAccessor
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
{
    static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
        LazyForEachOpsAccessor::DestroyPeerImpl,
        LazyForEachOpsAccessor::CtorImpl,
        LazyForEachOpsAccessor::GetFinalizerImpl,
        LazyForEachOpsAccessor::NeedMoreElementsImpl,
        LazyForEachOpsAccessor::OnRangeUpdateImpl,
    };
    return &LazyForEachOpsAccessorImpl;
}

}
