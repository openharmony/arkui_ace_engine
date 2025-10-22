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

#ifndef ARKUI_CAPI_DEMO_RELATIVECONTAINER_COMPONENT_H
#define ARKUI_CAPI_DEMO_RELATIVECONTAINER_COMPONENT_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_node.h>

#include "./relativeContainer/ruleOption.h"
#include "components/component.h"
namespace ArkUICApiDemo {
class RelativeContainerComponent : public Component {
public:
    RelativeContainerComponent() : Component(ARKUI_NODE_RELATIVE_CONTAINER) {}
    RelativeContainerComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    ~RelativeContainerComponent() = default;

    void SetRelativeContainerGuideLine(const std::shared_ptr<GuideLineOption> guidelineOption)
    {
        ArkUI_AttributeItem item = { .object = guidelineOption->GetOption() };
        _nodeAPI->setAttribute(_component, NODE_RELATIVE_CONTAINER_GUIDE_LINE, &item);
        guidelineOption_ = guidelineOption;
    }

    void SetRelativeContainerBarrier(const std::shared_ptr<BarrierOption> barrierOption)
    {
        ArkUI_AttributeItem item = { .object = barrierOption->GetOption() };
        _nodeAPI->setAttribute(_component, NODE_RELATIVE_CONTAINER_BARRIER, &item);
        barrierOption_ = barrierOption;
    }

    std::shared_ptr<RuleOption> GetRuleOption() const
    {
        return ruleOption_;
    }
    std::shared_ptr<GuideLineOption> GetGuideLineOption() const
    {
        return guidelineOption_;
    }
    std::shared_ptr<BarrierOption> GetBarrierOption() const
    {
        return barrierOption_;
    }

private:
    std::shared_ptr<RuleOption> ruleOption_ = nullptr;
    std::shared_ptr<GuideLineOption> guidelineOption_ = nullptr;
    std::shared_ptr<BarrierOption> barrierOption_ = nullptr;
};
;
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_RELATIVECONTAINER_COMPONENT_H
