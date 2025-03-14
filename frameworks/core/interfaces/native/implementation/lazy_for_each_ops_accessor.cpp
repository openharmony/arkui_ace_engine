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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyForEachOpsAccessor {
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
                       Ark_Int32 totalCount,
                       const Callback_RangeUpdate* updater)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetOnRangeUpdate(frameNode, convValue);
}
void SetCurrentIndexImpl(Ark_NativePointer node,
                         Ark_Int32 index)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetSetCurrentIndex(frameNode, convValue);
}
void PrepareImpl(Ark_NativePointer node,
                 Ark_Int32,
                 Ark_Int32)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetPrepare(frameNode, convValue);
}
void NotifyChangeImpl(Ark_NativePointer node,
                      int32_t startIdx,
                      int32_t endIdx,
                      int32_t changeCnt)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
