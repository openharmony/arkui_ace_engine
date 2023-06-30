/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_accessibility_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalPattern : public Pattern {
    DECLARE_ACE_TYPE(ContainerModalPattern, Pattern);

public:
    ContainerModalPattern() = default;
    ~ContainerModalPattern() override = default;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ContainerModalAccessibilityProperty>();
    }

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    }

    void OnWindowFocused() override;

    void OnWindowUnfocused() override;

    void InitContainerEvent();

    void ShowTitle(bool isShow, bool hasDeco = true);

    void SetAppTitle(const std::string& title);

    void SetAppIcon(const RefPtr<PixelMap>& icon);

    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize);

protected:
    virtual RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& titleNode, int32_t originIndex)
    {
        return titleNode->GetChildAtIndex(originIndex);
    }

    virtual void ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus);

    virtual void ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus);

    virtual void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus);

    WindowMode windowMode_;

private:
    void WindowFocus(bool isFocus);

    void SetTitleButtonHide(
        const RefPtr<FrameNode>& titleNode, bool hideSplit, bool hideMaximize, bool hideMinimize);

    bool CanShowFloatingTitle();

    float moveX_ = 0.0f;
    float moveY_ = 0.0f;
    bool hasDeco_ = true;
    bool isFocus_ = true;
    bool hideSplitButton_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H
