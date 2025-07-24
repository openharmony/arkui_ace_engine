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
#include "core/components_ng/pattern/stepper/stepper_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace StepperOpsAccessor {
Ark_NativePointer RegisterStepperIndexCallbackImpl(Ark_NativePointer node,
                                                   const Ark_Number* value,
                                                   const StepperIndexCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    StepperModelStatic::SetIndex(frameNode, Converter::Convert<int32_t>(*value));
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto changeEvent = [arkCallback = CallbackHelper(*callback), weakNode](int32_t stepperIndex) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(stepperIndex));
    };
    StepperModelStatic::SetOnChangeEvent(frameNode, std::move(changeEvent));
    return node;
}
} // StepperOpsAccessor
const GENERATED_ArkUIStepperOpsAccessor* GetStepperOpsAccessor()
{
    static const GENERATED_ArkUIStepperOpsAccessor StepperOpsAccessorImpl {
        StepperOpsAccessor::RegisterStepperIndexCallbackImpl,
    };
    return &StepperOpsAccessorImpl;
}

}