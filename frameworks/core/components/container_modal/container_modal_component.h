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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONTAINER_MODAL_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONTAINER_MODAL_COMPONENT_H

#include "core/components/button/button_component.h"
#include "core/components/flex/flex_component.h"
#include "core/components/image/image_component.h"
#include "core/components/text/text_component.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class ContainerModalComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(ContainerModalComponent, SoleChildComponent);

public:
    explicit ContainerModalComponent(const WeakPtr<PipelineContext>& context)
    {
        context_ = context;
        auto pipelineContext = context_.Upgrade();
        if (pipelineContext) {
            isDeclarative_ = pipelineContext->GetIsDeclarative();
        }
    }

    ~ContainerModalComponent() override = default;
    static RefPtr<Component> Create(const WeakPtr<PipelineContext>& context, const RefPtr<Component>& child);
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;
    void BuildInnerChild();
    std::list<RefPtr<Component>> BuildTitleChildren(bool isFloating, bool isFocus = true, bool isFullWindow = true);

    RefPtr<ImageComponent> GetTitleIcon() const
    {
        return titleIcon_;
    }

    RefPtr<TextComponent> GetTitleLabel() const
    {
        return titleLabel_;
    }

    void SetTitleButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
    {
        hideSplit_ = hideSplit;
        hideMaximize_ = hideMaximize;
        hideMinimize_ = hideMinimize;
        hideClose_ = hideClose;
    }

    bool GetSplitButtonHide() const
    {
        return hideSplit_;
    }

private:
    RefPtr<Component> BuildTitle();
    RefPtr<Component> BuildFloatingTitle();
    RefPtr<Component> BuildContent();
    RefPtr<Component> BuildControlButton(
        InternalResource::ResourceId icon, std::function<void()>&& clickCallback, bool isFocus, bool isFloating);
    void CreateAccessibilityNode(const std::string& tag, int32_t nodeId, int32_t parentNodeId);
    static RefPtr<Component> SetPadding(
        const RefPtr<Component>& component, const Dimension& leftPadding, const Dimension& rightPadding);

    WeakPtr<PipelineContext> context_;
    RefPtr<ImageComponent> titleIcon_;
    RefPtr<TextComponent> titleLabel_;
    bool isDeclarative_ = true;
    bool hideSplit_ = false;
    bool hideMaximize_ = false;
    bool hideMinimize_ = false;
    bool hideClose_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONTAINER_MODAL_COMPONENT_H
