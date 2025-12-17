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

#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckboxOpsAccessor {
Ark_NativePointer RegisterSelectCallbackImpl(Ark_NativePointer node,
                                             Ark_Boolean isSelected,
                                             const SelectCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::optional<bool> isSelectedOpt = Converter::Convert<bool>(isSelected);
    CheckBoxModelStatic::SetSelect(frameNode, isSelectedOpt);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const bool value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    CheckBoxModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // namespace CheckboxOpsAccessor
const GENERATED_ArkUICheckboxOpsAccessor* GetCheckboxOpsAccessor()
{
    static const GENERATED_ArkUICheckboxOpsAccessor CheckboxOpsAccessorImpl {
        CheckboxOpsAccessor::RegisterSelectCallbackImpl,
    };
    return &CheckboxOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
