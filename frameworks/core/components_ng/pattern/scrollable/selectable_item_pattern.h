/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_ITEM_PATTERN_H

#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class InputEvent;
class TouchEventImpl;
class ACE_FORCE_EXPORT SelectableItemPattern : public virtual Pattern {
    DECLARE_ACE_TYPE(SelectableItemPattern, Pattern);

public:
    SelectableItemPattern() = default;
    ACE_FORCE_EXPORT ~SelectableItemPattern() override = default;

    bool IsSelected() const
    {
        return isSelected_;
    }

    void SetSelected(bool selected)
    {
        isSelected_ = selected;
    }

    bool Selectable() const
    {
        return selectable_;
    }

    void SetSelectable(bool selectable)
    {
        selectable_ = selectable;
    }

    bool IsHover() const
    {
        return isHover_;
    }

    bool IsPressed() const
    {
        return isPressed_;
    }

    ACE_FORCE_EXPORT void SetEditModeEnabled(bool enabled);
    ACE_FORCE_EXPORT void SyncCheckBoxFromItem();
    virtual void MarkIsSelectedWithoutCheckbox(bool isSelected) {}

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        UpdateEditModeCheckBoxPosition();
        return false;
    }

    ACE_FORCE_EXPORT void BeforeCreateLayoutWrapper() override;

protected:
    bool isSelected_ = false;
    bool selectable_ = true;
    bool isHover_ = false;
    bool isPressed_ = false;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<FrameNode> editModeCheckBoxNode_;

    ACE_FORCE_EXPORT virtual void UpdateEditModeCheckBoxPosition();

private:
    void CreateEditModeCheckBox();
    void RemoveEditModeCheckBox();
};
} // namespace OHOS::Ace::NG

#endif
