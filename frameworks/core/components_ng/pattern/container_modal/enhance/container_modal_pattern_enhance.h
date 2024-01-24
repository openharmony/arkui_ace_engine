/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalPatternEnhance : public ContainerModalPattern {
    DECLARE_ACE_TYPE(ContainerModalPatternEnhance, ContainerModalPattern);

public:
    ContainerModalPatternEnhance() = default;
    ~ContainerModalPatternEnhance() override = default;
    void OnWindowFocused() override;
    void OnWindowUnfocused() override;
    void OnWindowForceUnfocused() override;
    void UpdateTitleInTargetPos(bool isShow, int32_t height);
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize) override;
    void ShowTitle(bool isShow, bool hasDeco = true, bool needUpdate = false) override;

protected:
    RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex) override;
    void ChangeFloatingTitle(bool isFocus) override;

    void ChangeCustomTitle(bool isFocus) override;

    void ChangeControlButtons(bool isFocus) override;

    void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus) override;

    bool CanHideFloatingTitle() override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
