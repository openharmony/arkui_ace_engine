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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_INSPECTOR_COMPOSED_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_INSPECTOR_COMPOSED_COMPONENT_H

#include "core/accessibility/accessibility_manager.h"
#include "core/pipeline/base/composed_component.h"

namespace OHOS::Ace::V2 {

using CreateElementFunc = std::function<RefPtr<ComposedElement>(const std::string& id)>;

class ACE_EXPORT InspectorComposedComponent : public ComposedComponent {
    DECLARE_ACE_TYPE(InspectorComposedComponent, ComposedComponent);

public:
    using ComposedComponent::ComposedComponent;
    ~InspectorComposedComponent() override = default;

    RefPtr<Element> CreateElement() override;
    bool IsInspector() override
    {
        return true;
    }

    static bool HasInspectorFinished(std::string tag);
    static RefPtr<AccessibilityManager> GetAccessibilityManager();
    static RefPtr<AccessibilityNode> CreateAccessibilityNode(const std::string& tag,
        int32_t nodeId, int32_t parentNodeId, int32_t itemIndex);
    static void AddElementToAccessibilityManager(const RefPtr<ComposedElement>& composedElement);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_INSPECTOR_COMPOSED_COMPONENT_H
