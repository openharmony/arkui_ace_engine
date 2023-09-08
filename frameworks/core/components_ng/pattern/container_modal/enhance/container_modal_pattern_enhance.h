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
    virtual void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize) override;

protected:
    virtual RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& titleNode, int32_t originIndex) override;
    virtual void ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus) override;

    virtual void ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus) override;

    virtual void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus) override;

    virtual bool CanHideFloatingTitle() override;

private:
    static OffsetF RecalculateMenuOffset(OffsetF menuPosition);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
