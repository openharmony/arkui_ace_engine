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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_H

#include <cstdint>
#include <string>
#include <unordered_set>

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_utils.h"

namespace OHOS::Ace::NG {
using ActionNoParam = std::function<void()>;
using ActionSetTextImpl = std::function<void(const std::string&)>;
using ActionScrollForwardImpl = ActionNoParam;
using ActionScrollBackwardImpl = ActionNoParam;
using ActionSetSelectionImpl = std::function<void(int32_t start, int32_t end)>;
using ActionCopyImpl = ActionNoParam;
using ActionCutImpl = ActionNoParam;
using ActionPasteImpl = ActionNoParam;
using ActionSelectImpl = ActionNoParam;
using ActionClearSelectionImpl = ActionNoParam;
using ActionMoveTextImpl = std::function<void(int32_t moveUnit, bool forward)>;

class FrameNode;
class ACE_EXPORT AccessibilityProperty : public virtual AceType {
    DECLARE_ACE_TYPE(AccessibilityProperty, AceType);

public:
    AccessibilityProperty() = default;

    ~AccessibilityProperty() override = default;

    virtual std::string GetText() const
    {
        return propText_.value_or("");
    }

    virtual void SetText(const std::string& text)
    {
        propText_ = text;
    }

    virtual bool IsCheckable() const
    {
        return false;
    }

    virtual bool IsChecked() const
    {
        return false;
    }

    virtual bool IsSelected() const
    {
        return false;
    }

    virtual bool IsPassword() const
    {
        return false;
    }

    virtual bool IsEditable() const
    {
        return false;
    }

    virtual bool IsMultiLine() const
    {
        return false;
    }

    virtual bool IsDeletable() const
    {
        return false;
    }

    virtual bool IsHint() const
    {
        return false;
    }

    virtual bool IsScrollable() const
    {
        return false;
    }

    virtual int32_t GetCurrentIndex() const
    {
        return -1;
    }

    virtual int32_t GetBeginIndex() const
    {
        return -1;
    }

    virtual int32_t GetEndIndex() const
    {
        return -1;
    }

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("scrollable", IsScrollable());
    }

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    virtual bool HasRange() const
    {
        return false;
    }

    virtual AccessibilityValue GetAccessibilityValue() const
    {
        return AccessibilityValue();
    }

    void SetHost(const WeakPtr<FrameNode>& host)
    {
        host_ = host;
    }

    virtual std::string GetHintText() const
    {
        return "";
    }

    virtual int32_t GetTextLengthLimit() const
    {
        return -1;
    }

    virtual AceCollectionInfo GetCollectionInfo() const
    {
        return AceCollectionInfo();
    }

    virtual AceCollectionItemInfo GetCollectionItemInfo() const
    {
        return AceCollectionItemInfo();
    }

    virtual std::string GetErrorText() const
    {
        return "";
    }

    virtual int32_t GetTextSelectionStart() const
    {
        return 0;
    }

    virtual int32_t GetTextSelectionEnd() const
    {
        return 0;
    }

    virtual AceTextCategory GetTextInputType() const
    {
        return AceTextCategory::INPUT_TYPE_DEFAULT;
    }

    virtual int32_t GetCollectionItemCounts() const
    {
        return 0;
    }

    virtual bool GetContentInvalid() const
    {
        return true;
    }

    void AddSupportAction(AceAction action)
    {
        supportActions_ |= (1UL << static_cast<uint32_t>(action));
    }

    std::unordered_set<AceAction> GetSupportAction() const;

    void ResetSupportAction()
    {
        supportActions_ = 0;
        SetSpecificSupportAction();
    };

    void SetActionSetText(const ActionSetTextImpl& actionSetTextImpl)
    {
        actionSetTextImpl_ = actionSetTextImpl;
    }

    bool ActActionSetText(const std::string& text)
    {
        if (actionSetTextImpl_) {
            actionSetTextImpl_(text);
            return true;
        }
        return false;
    }

    void SetActionSetSelection(const ActionSetSelectionImpl& actionSetSelection)
    {
        actionSetSelectionImpl_ = actionSetSelection;
    }

    bool ActActionSetSelection(int32_t start, int32_t end)
    {
        if (actionSetSelectionImpl_) {
            actionSetSelectionImpl_(start, end);
            return true;
        }
        return false;
    }

    void SetActionMoveText(const ActionMoveTextImpl& actionMoveText)
    {
        actionMoveTextImpl_ = actionMoveText;
    }

    bool ActActionMoveText(int32_t moveUnit, bool forward)
    {
        if (actionMoveTextImpl_) {
            actionMoveTextImpl_(moveUnit, forward);
            return true;
        }
        return false;
    }

    void SetActionScrollForward(const ActionScrollForwardImpl& actionScrollForwardImpl)
    {
        actionScrollForwardImpl_ = actionScrollForwardImpl;
    }

    bool ActActionScrollForward()
    {
        if (actionScrollForwardImpl_) {
            actionScrollForwardImpl_();
            return true;
        }
        return false;
    }

    void SetActionScrollBackward(const ActionScrollBackwardImpl& actionScrollBackwardImpl)
    {
        actionScrollBackwardImpl_ = actionScrollBackwardImpl;
    }

    bool ActActionScrollBackward()
    {
        if (actionScrollBackwardImpl_) {
            actionScrollBackwardImpl_();
            return true;
        }
        return false;
    }

    void SetActionCopy(const ActionCopyImpl& actionCopyImpl)
    {
        actionCopyImpl_ = actionCopyImpl;
    }

    bool ActActionCopy()
    {
        if (actionCopyImpl_) {
            actionCopyImpl_();
            return true;
        }
        return false;
    }

    void SetActionCut(const ActionCutImpl& actionCutImpl)
    {
        actionCutImpl_ = actionCutImpl;
    }

    bool ActActionCut()
    {
        if (actionCutImpl_) {
            actionCutImpl_();
            return true;
        }
        return false;
    }

    void SetActionPaste(const ActionPasteImpl& actionPasteImpl)
    {
        actionPasteImpl_ = actionPasteImpl;
    }

    bool ActActionPaste()
    {
        if (actionPasteImpl_) {
            actionPasteImpl_();
            return true;
        }
        return false;
    }

    void SetActionSelect(const ActionSelectImpl& actionSelectImpl)
    {
        actionSelectImpl_ = actionSelectImpl;
    }

    bool ActActionSelect()
    {
        if (actionSelectImpl_) {
            actionSelectImpl_();
            return true;
        }
        return false;
    }

    void SetActionClearSelection(const ActionClearSelectionImpl& actionClearSelectionImpl)
    {
        actionClearSelectionImpl_ = actionClearSelectionImpl;
    }

    bool ActActionClearSelection()
    {
        if (actionClearSelectionImpl_) {
            actionClearSelectionImpl_();
            return true;
        }
        return false;
    }

    void SetAccessibilityGroup(bool accessibilityGroup)
    {
        accessibilityGroup_ = accessibilityGroup;
    }

    void SetAccessibilityText(const std::string& text)
    {
        accessibilityText_ = text;
    }

    void SetAccessibilityDescription(const std::string& accessibilityDescription)
    {
        accessibilityDescription_ = accessibilityDescription;
    }

    void SetAccessibilityLevel(const std::string& accessibilityLevel)
    {
        accessibilityLevel_ = accessibilityLevel;
    }

    bool IsAccessibilityGroup() const
    {
        return accessibilityGroup_;
    }

    std::string GetAccessibilityText(bool isParentGroup = false);

    std::string GetAccessibilityDescription()
    {
        return accessibilityDescription_.value_or("");
    }

    virtual std::string GetAccessibilityLevel()
    {
        if (!accessibilityLevel_.has_value()) {
            return "yes";
        }
        accessibilityLevel_ = accessibilityLevel_ == "auto" ? "yes" : accessibilityLevel_;
        return accessibilityLevel_.value();
    }

protected:
    virtual void SetSpecificSupportAction() {}
    std::optional<std::string> propText_;
    WeakPtr<FrameNode> host_;
    uint64_t supportActions_ = 0;
    ActionSetTextImpl actionSetTextImpl_;
    ActionSetSelectionImpl actionSetSelectionImpl_;
    ActionMoveTextImpl actionMoveTextImpl_;
    ActionScrollForwardImpl actionScrollForwardImpl_;
    ActionScrollBackwardImpl actionScrollBackwardImpl_;
    ActionCopyImpl actionCopyImpl_;
    ActionCutImpl actionCutImpl_;
    ActionPasteImpl actionPasteImpl_;
    ActionSelectImpl actionSelectImpl_;
    ActionClearSelectionImpl actionClearSelectionImpl_;
    bool accessibilityGroup_ = false;
    std::optional<std::string> accessibilityText_;
    std::optional<std::string> accessibilityDescription_;
    std::optional<std::string> accessibilityLevel_;
    ACE_DISALLOW_COPY_AND_MOVE(AccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif
