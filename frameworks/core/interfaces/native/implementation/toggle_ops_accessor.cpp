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

#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ToggleOpsAccessor {
Ark_NativePointer RegisterIsOnCallbackImpl(Ark_NativePointer node,
                                           Ark_Boolean isOn,
                                           const IsOnCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    ToggleModelNG::SetToggleState(frameNode, Converter::Convert<bool>(isOn));
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool isOn) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isOn));
    };
    ToggleModelStatic::OnChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // namespace ToggleOpsAccessor
const GENERATED_ArkUIToggleOpsAccessor* GetToggleOpsAccessor()
{
    static const GENERATED_ArkUIToggleOpsAccessor ToggleOpsAccessorImpl {
        ToggleOpsAccessor::RegisterIsOnCallbackImpl,
    };
    return &ToggleOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
