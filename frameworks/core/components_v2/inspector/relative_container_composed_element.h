/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_RELATIVE_CONTAINER_COMPOSED_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_RELATIVE_CONTAINER_COMPOSED_ELEMENT_H

#include "core/components/common/layout/position_param.h"
#include "core/components/relative_container/relative_container_element.h"
#include "core/components/relative_container/render_relative_container.h"
#include "core/components_v2/inspector/inspector_composed_element.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace::V2 {

class ACE_EXPORT RelativeContainerComposedElement : public InspectorComposedElement {
    DECLARE_ACE_TYPE(RelativeContainerComposedElement, InspectorComposedElement);

public:
    explicit RelativeContainerComposedElement(const ComposeId& id) : InspectorComposedElement(id) {}
    ~RelativeContainerComposedElement() override = default;

    void Dump() override;
    std::unique_ptr<JsonValue> ToJsonObject() const override;

    std::string GetAlignRulesMap() const;
    std::string GetAlignDirectionStr(AlignDirection alignDirection) const;
    std::string GetAlignRuleStr(AlignRule alignRule) const;

    AceType::IdType GetTargetTypeId() const override
    {
        return RelativeContainerComposedElement::TypeId();
    }

    RefPtr<Element> GetRenderElement() const override
    {
        return GetContentElement<RelativeContainerElement>(RelativeContainerElement::TypeId());
    }

private:
    RefPtr<RenderRelativeContainer> GetRenderRelativeContainer() const;
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_RELATIVE_CONTAINER_COMPOSED_ELEMENT_H