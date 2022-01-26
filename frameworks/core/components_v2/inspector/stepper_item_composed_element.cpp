/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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


#include "core/components_v2/inspector/stepper_item_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/stepper/render_stepper.h"
#include "core/components/stepper/render_stepper_item.h"
#include "core/components_v2/inspector/utils.h"
namespace OHOS::Ace::V2 {
namespace {
const std::unordered_map<std::string, std::function<std::string(const StepperItemComposedElement&)>> CREATE_JSON_MAP {
    { "prevLabel", [](const StepperItemComposedElement& inspector) { return inspector.GetPrevLabel(); } },
    { "nextLabel", [](const StepperItemComposedElement& inspector) { return inspector.GetNextLabel(); } },
    { "status", [](const StepperItemComposedElement& inspector) { return inspector.GetStatus(); } },
};
}

void StepperItemComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    for (const auto& value : CREATE_JSON_MAP) {
        DumpLog::GetInstance().AddDesc(std::string(value.first + ":").append(value.second(*this)));
    }
}

std::unique_ptr<JsonValue> StepperItemComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string StepperItemComposedElement::GetPrevLabel() const
{
    auto node = GetInspectorNode(StepperItemElement::TypeId());
    if (!node) {
        return "";
    }
    auto stepperItemRender = AceType::DynamicCast<RenderStepperItem>(node);
    if (!stepperItemRender) {
        return "";
    }
    auto index = stepperItemRender->GetIndex();
    auto stepperRender = stepperItemRender->GetParent().Upgrade();
    auto render = AceType::DynamicCast<RenderStepper>(stepperRender);
    auto label = render->GetStepperLabels();
    return label[index].leftLabel;
}

std::string StepperItemComposedElement::GetNextLabel() const
{
    auto node = GetInspectorNode(StepperItemElement::TypeId());
    if (!node) {
        return "";
    }
    auto stepperItemRender = AceType::DynamicCast<RenderStepperItem>(node);
    if (!stepperItemRender) {
        return "";
    }
    auto index = stepperItemRender->GetIndex();
    auto stepperRender = stepperItemRender->GetParent().Upgrade();
    auto render = AceType::DynamicCast<RenderStepper>(stepperRender);
    auto label = render->GetStepperLabels();
    return label[index].rightLabel;
}

std::string StepperItemComposedElement::GetStatus() const
{
    auto node = GetInspectorNode(StepperItemElement::TypeId());
    if (!node) {
        return "";
    }
    auto stepperItemRender = AceType::DynamicCast<RenderStepperItem>(node);
    if (!stepperItemRender) {
        return "";
    }
    auto index = stepperItemRender->GetIndex();
    auto stepperRender = stepperItemRender->GetParent().Upgrade();
    auto render = AceType::DynamicCast<RenderStepper>(stepperRender);
    auto label = render->GetStepperLabels();
    return label[index].initialStatus;
}
} // namespace OHOS::Ace::V2