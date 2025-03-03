/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/form_button/form_button_model_ng.h"

#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form_button/form_button_pattern.h"

namespace OHOS::Ace::NG {

void FormButtonModelNG::Create(const std::string& action, const RequestFormInfo& info)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::FORM_BUTTON_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FORM_BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FormButtonPattern>(); });
    auto pattern = frameNode->GetPattern<FormButtonPattern>();
    pattern->SetAction(action);
    pattern->SetBundleName(info.bundleName);
    pattern->SetAbilityName(info.abilityName);
    pattern->SetModuleName(info.moduleName);
    pattern->SetCardName(info.cardName);
    pattern->SetDimension(info.dimension);
    stack->Push(frameNode);
    frameNode->SetExclusiveEventForChild(true);
}

void FormButtonModelNG::Create(Alignment alignment, const std::string& action, const RequestFormInfo& info)
{
    Create(action, info);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}
} // namespace OHOS::Ace::NG