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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerModalPattern : public Pattern {
    DECLARE_ACE_TYPE(ContainerModalPattern, Pattern);

public:
    ContainerModalPattern() = default;
    ~ContainerModalPattern() override = default;

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

    void ShowTitle(bool isShow);

    void SetAppTitle(const std::string& title);

    void SetAppIcon(const RefPtr<PixelMap>& icon);

private:
    void OnModifyDone() override;

    void WindowFocus(bool isFocus);

    void ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus = true);

    static void ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus = true);

    static void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus = true);

    bool CanShowFloatingTitle();

    WindowMode windowMode_;
    float moveX_ = 0.0f;
    float moveY_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H
