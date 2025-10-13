/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SelectOpsAccessor {
Ark_NativePointer RegisterSelectedCallbackImpl(Ark_NativePointer node,
                                               const Ark_Union_I32_Resource* numCount,
                                               const SelectSelectedCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(numCount, nullptr);
    CHECK_NULL_RETURN(callback, nullptr);
    auto convVal = Converter::OptConvert<int32_t>(*numCount);
    SelectModelStatic::SetSelected(frameNode, convVal);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](int32_t index) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Ark_Union_I32_Resource, Ark_Int32>(index));
    };
    SelectModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
    return node;
}
Ark_NativePointer RegisterValueCallbackImpl(Ark_NativePointer node,
                                            const Ark_ResourceStr* resStr,
                                            const SelectValueCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(resStr, nullptr);
    CHECK_NULL_RETURN(callback, nullptr);
    auto resStrOpt = Converter::OptConvert<std::string>(*resStr);
    SelectModelStatic::SetValue(frameNode, resStrOpt);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Ark_ResourceStr, Ark_String>(value));
    };
    SelectModelStatic::SetValueChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // namespace SelectOpsAccessor
const GENERATED_ArkUISelectOpsAccessor* GetSelectOpsAccessor()
{
    static const GENERATED_ArkUISelectOpsAccessor SelectOpsAccessorImpl {
        SelectOpsAccessor::RegisterSelectedCallbackImpl,
        SelectOpsAccessor::RegisterValueCallbackImpl,
    };
    return &SelectOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
