/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MASK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MASK_PATTERN_H

#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"

const char DIALOG_MASK_ETS_TAG[] = "DialogMask";

namespace OHOS::Ace::NG {
class DialogMaskPattern : virtual public PopupBasePattern {
    DECLARE_ACE_TYPE(DialogMaskPattern, PopupBasePattern);

public:
    DialogMaskPattern() = default;
    DialogMaskPattern(const DialogProperties& param, const RefPtr<FrameNode>& dialog)
        : dialogProperties_(param), dialogNode_(dialog)
    {}
    ~DialogMaskPattern() override = default;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, false };
    }

    const DialogProperties& GetDialogProperties() const
    {
        return dialogProperties_;
    }

    const RefPtr<FrameNode> GetDialogNode()
    {
        return dialogNode_.Upgrade();
    }

    void OnAttachToFrameNode() override;
    void InitClickEvent();
    void ShowMask();
    void CloseMask();

protected:
    bool AvoidKeyboard() const override
    {
        return false;
    }

    bool AvoidBottom() const override
    {
        return false;
    }

private:
    DialogProperties dialogProperties_;
    WeakPtr<FrameNode> dialogNode_;
    RefPtr<ClickEvent> onClick_;

    ACE_DISALLOW_COPY_AND_MOVE(DialogMaskPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MASK_PATTERN_H
