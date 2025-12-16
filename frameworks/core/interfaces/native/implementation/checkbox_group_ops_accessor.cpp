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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckboxGroupOpsAccessor {
Ark_NativePointer RegisterSelectAllCallbackImpl(Ark_NativePointer node,
                                                Ark_Boolean isAllSelected,
                                                const SelectAllCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::optional<bool> isAllSelectedOpt = Converter::Convert<bool>(isAllSelected);
    CheckBoxGroupModelStatic::SetSelectAll(frameNode, isAllSelectedOpt);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (eventInfo) {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(eventInfo->GetStatus() == 0));
        }
    };
    CheckBoxGroupModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // namespace CheckboxGroupOpsAccessor
const GENERATED_ArkUICheckboxGroupOpsAccessor* GetCheckboxGroupOpsAccessor()
{
    static const GENERATED_ArkUICheckboxGroupOpsAccessor CheckboxGroupOpsAccessorImpl {
        CheckboxGroupOpsAccessor::RegisterSelectAllCallbackImpl,
    };
    return &CheckboxGroupOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
