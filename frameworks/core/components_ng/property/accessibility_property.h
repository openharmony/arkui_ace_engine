/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "interfaces/native/native_type.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Accessibility {
class ExtraElementInfo;
}

namespace OHOS::Ace::NG {
struct WindowSceneInfo {
    int32_t left = 0;
    int32_t top = 0;
    int32_t innerWindowId = -1;
    float_t scaleX = 1.0f;
    float_t scaleY = 1.0f;
};
using ActionNoParam = std::function<void()>;
using ActionSetTextImpl = std::function<void(const std::string&)>;
using ActionScrollForwardImpl = ActionNoParam;
using ActionScrollForwardWithParamImpl = std::function<void(AccessibilityScrollType scrollType)>;;
using ActionScrollBackwardImpl = ActionNoParam;
using ActionScrollBackwardWithParamImpl = std::function<void(AccessibilityScrollType scrollType)>;;
using ActionSetSelectionImpl = std::function<void(int32_t start, int32_t end, bool isForward)>;
using ActionCopyImpl = ActionNoParam;
using ActionCutImpl = ActionNoParam;
using ActionPasteImpl = ActionNoParam;
using ActionSelectImpl = ActionNoParam;
using ActionClearSelectionImpl = ActionNoParam;
using ActionMoveTextImpl = std::function<void(int32_t moveUnit, bool forward)>;
using ActionSetCursorIndexImpl = std::function<void(int32_t index)>;
using ActionExecSubComponentImpl = std::function<bool(int32_t spanId)>;
using ActionGetCursorIndexImpl = std::function<int32_t(void)>;
using ActionClickImpl = ActionNoParam;
using ActionLongClickImpl = ActionNoParam;
using ActionsImpl = std::function<void((uint32_t actionType))>;
using GetRelatedElementInfoImpl = std::function<void(Accessibility::ExtraElementInfo& extraElementInfo)>;
using OnAccessibilityFocusCallbackImpl = std::function<void((bool isFocus))>;

using GetWindowScenePositionImpl = std::function<void((WindowSceneInfo& windowSceneInfo))>;

class FrameNode;
using AccessibilityHoverTestPath = std::vector<RefPtr<FrameNode>>;

class ACE_FORCE_EXPORT AccessibilityProperty : public virtual AceType {
    DECLARE_ACE_TYPE(AccessibilityProperty, AceType);

public:
    AccessibilityProperty() = default;

    ~AccessibilityProperty() override = default;

    virtual std::string GetText() const;

    virtual std::string GetGroupText(bool forceGetChildren = false) const;

    virtual std::string GetGroupPreferAccessibilityText(bool forceGetChildren = false) const;

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

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        json->PutFixedAttr("scrollable", IsScrollable(), filter, FIXED_ATTR_SCROLLABLE);
        json->PutExtAttr("accessibilityLevel", GetAccessibilityLevel().c_str(), filter);
        json->PutExtAttr("accessibilityGroup", IsAccessibilityGroup(), filter);
        json->PutExtAttr("accessibilityVirtualNode", HasAccessibilityVirtualNode(), filter);
        json->PutExtAttr("accessibilityText", GetAccessibilityText().c_str(), filter);
        json->PutExtAttr("accessibilityTextHint", GetTextType().c_str(), filter);
        json->PutExtAttr("accessibilityDescription", GetAccessibilityDescription().c_str(), filter);
    }

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    virtual bool HasRange() const
    {
        return false;
    }

    virtual bool HasSubComponent() const
    {
        return false;
    }

    virtual void GetSubComponentInfo(std::vector<SubComponentInfo>& subComponentInfos) const {}

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

    virtual float GetScrollOffSet() const;

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

    bool ActActionSetSelection(int32_t start, int32_t end, bool isForward = false)
    {
        if (actionSetSelectionImpl_) {
            actionSetSelectionImpl_(start, end, isForward);
            return true;
        }
        return false;
    }

    void SetActionSetIndex(const ActionSetCursorIndexImpl& actionSetCursorIndexImpl)
    {
        actionSetCursorIndexImpl_ = actionSetCursorIndexImpl;
    }

    bool ActActionSetIndex(int32_t index)
    {
        if (actionSetCursorIndexImpl_) {
            actionSetCursorIndexImpl_(index);
            return true;
        }
        return false;
    }

    void SetActionExecSubComponent(const ActionExecSubComponentImpl& actionExecSubComponentImpl)
    {
        actionExecSubComponentImpl_ = actionExecSubComponentImpl;
    }

    bool ActActionExecSubComponent(int32_t spanId)
    {
        if (actionExecSubComponentImpl_) {
            return actionExecSubComponentImpl_(spanId);
        }
        return false;
    }

    void SetActionGetIndex(const ActionGetCursorIndexImpl& actionGetCursorIndexImpl)
    {
        actionGetCursorIndexImpl_ = actionGetCursorIndexImpl;
    }

    int32_t ActActionGetIndex()
    {
        if (actionGetCursorIndexImpl_) {
            return actionGetCursorIndexImpl_();
        }
        return -1;
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

    void SetActionScrollForward(const ActionScrollForwardWithParamImpl& actionScrollForwardImpl)
    {
        actionScrollForwardWithParamImpl_ = actionScrollForwardImpl;
    }

    bool ActActionScrollForward(AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_DEFAULT)
    {
        if (actionScrollForwardWithParamImpl_ == nullptr) {
            scrollType = AccessibilityScrollType::SCROLL_DEFAULT;
        }

        if ((scrollType == AccessibilityScrollType::SCROLL_DEFAULT) && (actionScrollForwardImpl_)) {
            actionScrollForwardImpl_();
            return true;
        }

        if (actionScrollForwardWithParamImpl_) {
            actionScrollForwardWithParamImpl_(scrollType);
            return true;
        }
        return false;
    }

    void SetActionScrollBackward(const ActionScrollBackwardImpl& actionScrollBackwardImpl)
    {
        actionScrollBackwardImpl_ = actionScrollBackwardImpl;
    }

    void SetActionScrollBackward(const ActionScrollBackwardWithParamImpl& actionScrollBackwardImpl)
    {
        actionScrollBackwardWithParamImpl_ = actionScrollBackwardImpl;
    }

    bool ActActionScrollBackward(AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_DEFAULT)
    {
        if (actionScrollBackwardWithParamImpl_ == nullptr) {
            scrollType = AccessibilityScrollType::SCROLL_DEFAULT;
        }

        if ((scrollType == AccessibilityScrollType::SCROLL_DEFAULT) && (actionScrollBackwardImpl_)) {
            actionScrollBackwardImpl_();
            return true;
        }

        if (actionScrollBackwardWithParamImpl_) {
            actionScrollBackwardWithParamImpl_(scrollType);
            return true;
        }
        return false;
    }

    void SetActionCopy(const ActionCopyImpl& actionCopyImpl)
    {
        actionCopyImpl_ = actionCopyImpl;
    }

    bool ActActionCopy();

    void SetActionCut(const ActionCutImpl& actionCutImpl);

    bool ActActionCut();

    void SetActionPaste(const ActionPasteImpl& actionPasteImpl);

    bool ActActionPaste();

    void SetActionLongClick(const ActionLongClickImpl& actionLongClickImpl);

    bool ActActionLongClick();

    void SetActionClick(const ActionClickImpl& actionClickImpl);

    bool ActActionClick();

    void SetActionSelect(const ActionSelectImpl& actionSelectImpl);

    bool ActActionSelect();

    void SetActionClearSelection(const ActionClearSelectionImpl& actionClearSelectionImpl);

    bool ActActionClearSelection();

    void SetOnAccessibilityFocusCallback(const OnAccessibilityFocusCallbackImpl& onAccessibilityFocusCallbackImpl);
    void ResetUserOnAccessibilityFocusCallback();

    void SetUserOnAccessibilityFocusCallback(
        const OnAccessibilityFocusCallbackImpl& onUserAccessibilityFocusCallbackImpl);

    void OnAccessibilityFocusCallback(bool isFocus);

    void SetGetWindowScenePosition(const GetWindowScenePositionImpl& getWindowScenePositionImpl);

    void GetWindowScenePosition(WindowSceneInfo& windowSceneInfo);

    bool GetAccessibilityFocusState() const;

    void SetAccessibilityFocusState(bool state);

    void SetAccessibilityGroup(bool accessibilityGroup);

    void SetAccessibilityTextPreferred(bool accessibilityTextPreferred);

    void SetChildTreeId(int32_t childTreeId);

    void SetChildWindowId(int32_t childWindowId);

    void SetAccessibilityText(const std::string& text);

    void SetAccessibilityNextFocusInspectorKey(const std::string& accessibilityNextFocusInspectorKey);

    void SetAccessibilityTextWithEvent(const std::string& text);

    void SetAccessibilityTextHint(const std::string& text);

    void SetAccessibilityDescription(const std::string& accessibilityDescription);

    void SetAccessibilityDescriptionWithEvent(const std::string& accessibilityDescription);

    bool IsAccessibilityGroup() const;

    bool IsAccessibilityTextPreferred() const;

    void NotifyComponentChangeEvent(AccessibilityEventType eventType);

    int32_t GetChildTreeId() const;

    int32_t GetChildWindowId() const;

    void SaveAccessibilityVirtualNode(const RefPtr<UINode>& node);

    RefPtr<UINode> GetAccessibilityVirtualNode();

    NG::UINode* GetAccessibilityVirtualNodePtr();

    bool HasAccessibilityVirtualNode() const;

    virtual std::string GetAccessibilityText() const
    {
        return accessibilityText_.value_or("");
    }

    virtual std::string GetAccessibilityNextFocusInspectorKey() const
    {
        return accessibilityNextFocusInspectorKey_.value_or("");
    }

    std::string GetAccessibilityDescription() const;

    std::string GetTextType() const;

    class Level {
    public:
        inline static const std::string AUTO = "auto";
        inline static const std::string YES_STR = "yes";
        inline static const std::string NO_STR = "no";
        inline static const std::string NO_HIDE_DESCENDANTS = "no-hide-descendants";
    };

    virtual std::string GetAccessibilityLevel() const
    {
        if (!accessibilityLevel_.has_value()) {
            return Level::AUTO;
        }
        return accessibilityLevel_.value();
    }

    void SetAccessibilityLevel(const std::string& accessibilityLevel);


    struct HoverTestDebugTraceInfo {
        std::vector<std::unique_ptr<JsonValue>> trace;
    };


    /*
    * Get path from root to node which hit the hoverPoint.
    * return: path contains nodes whose border cover the hoverPoint.
    */
    static AccessibilityHoverTestPath HoverTest(
        const PointF& point,
        const RefPtr<FrameNode>& root,
        std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo
    );

    /*
    * Judge whether a node can be accessibility focused.
    * return: if node is accessibility focusable, return true.
    * param: {node} should be not-null
    */
    static bool IsAccessibilityFocusable(const RefPtr<FrameNode>& node);

    /*
    * param: {node}, {info} should be not-null
    */
    static bool IsAccessibilityFocusableDebug(const RefPtr<FrameNode>& node, std::unique_ptr<JsonValue>& info);

    /*
    * Judge whether a node's tag is default accessibility focusable.
    * return: if a node's tag is default accessibility focusable, return true.
    * param: {tag} should be not-null
    */
    static bool IsAccessibilityFocusableTag(const std::string &tag);

    static bool IsTagInSubTreeComponent(const std::string& tag);

    static bool IsTagInModalDialog(const RefPtr<FrameNode>& node);

    static bool HitAccessibilityHoverPriority(const RefPtr<FrameNode>& node);

    virtual void GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo) {}

    void SetRelatedElementInfoCallback(const GetRelatedElementInfoImpl& getRelatedElementInfoImpl);

    void GetAllExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo);

    void SetAccessibilityActions(uint32_t actions);
    void ResetAccessibilityActions();
    bool HasAccessibilityActions();
    uint32_t GetAccessibilityActions() const;

    void SetAccessibilityRole(const std::string& role);
    void ResetAccessibilityRole();
    bool HasAccessibilityRole();
    std::string GetAccessibilityRole() const;
    void SetAccessibilityCustomRole(const std::string& role);
    void ResetAccessibilityCustomRole();
    bool HasAccessibilityCustomRole();
    std::string GetAccessibilityCustomRole() const;

    void SetActions(const ActionsImpl& actionsImpl);
    bool ActionsDefined(uint32_t action);

    void SetUserDisabled(const bool& isDisabled);
    bool HasUserDisabled();
    bool IsUserDisabled();

    void SetUserSelected(const bool& isSelected);
    bool HasUserSelected();
    bool IsUserSelected();
    void ResetUserSelected();

    void SetUserCheckedType(const int32_t& checkedType);
    bool HasUserCheckedType();
    int32_t GetUserCheckedType();
    void ResetUserCheckedType();

    void SetUserMinValue(const int32_t& minValue);
    bool HasUserMinValue();
    int32_t GetUserMinValue();

    void SetUserMaxValue(const int32_t& maxValue);
    bool HasUserMaxValue();
    int32_t GetUserMaxValue();

    void SetUserCurrentValue(const int32_t& currentValue);
    bool HasUserCurrentValue();
    int32_t GetUserCurrentValue();

    void SetUserRangeMinValue(const int32_t rangeMinValue);
    bool HasUserRangeMinValue() const;
    int32_t GetUserRangeMinValue() const;

    void SetUserRangeMaxValue(const int32_t rangeMaxValue);
    bool HasUserRangeMaxValue() const;
    int32_t GetUserRangeMaxValue() const;

    void SetUserRangeCurrentValue(const int32_t rangeCurrentValue);
    bool HasUserRangeCurrentValue() const;
    int32_t GetUserRangeCurrentValue() const;

    void SetUserTextValue(const std::string& textValue);
    bool HasUserTextValue();
    std::string GetUserTextValue();

    void SetUserCheckable(const bool& checkable);
    bool HasUserCheckable();
    bool IsUserCheckable();
    void ResetUserCheckable();

    virtual bool IsAccessibilityHoverPriority() const;
    void SetAccessibilityHoverPriority(bool hoverPriority);

private:
    // node should be not-null
    static bool HoverTestRecursive(
        const PointF& parentPoint,
        const RefPtr<FrameNode>& node,
        AccessibilityHoverTestPath& path,
        std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo,
        bool& ancestorGroupFlag
    );

    struct RecursiveParam {
        bool hitTarget;
        bool ancestorGroupFlag;
    };

    static bool ProcessHoverTestRecursive(const PointF& noOffsetPoint, const RefPtr<FrameNode>& node,
        AccessibilityHoverTestPath& path, std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo,
        RecursiveParam recursiveParam);

    static std::unique_ptr<JsonValue> CreateNodeSearchInfo(const RefPtr<FrameNode>& node, const PointF& parentPoint,
        bool& ancestorGroupFlag);

    /*
    * Get whether node and its children should be searched.
    * return: first: node itself should be searched.
    *         second: children of node should be searched.
    * param: {node} should be not-null
    */
    static std::tuple<bool, bool, bool> GetSearchStrategy(const RefPtr<FrameNode>& node, bool& ancestorGroupFlag);

    void GetGroupTextRecursive(bool forceGetChildren, std::string& text, bool preferAccessibilityText) const;

    bool HasAccessibilityTextOrDescription() const;

    bool HasAction() const;

protected:
    virtual void SetSpecificSupportAction() {}
    std::optional<std::string> propText_;
    WeakPtr<FrameNode> host_;
    uint64_t supportActions_ = 0;
    ActionSetTextImpl actionSetTextImpl_;
    ActionSetSelectionImpl actionSetSelectionImpl_;
    ActionMoveTextImpl actionMoveTextImpl_;
    ActionScrollForwardImpl actionScrollForwardImpl_;
    ActionScrollForwardWithParamImpl actionScrollForwardWithParamImpl_;
    ActionScrollBackwardImpl actionScrollBackwardImpl_;
    ActionScrollBackwardWithParamImpl actionScrollBackwardWithParamImpl_;
    ActionCopyImpl actionCopyImpl_;
    ActionCutImpl actionCutImpl_;
    ActionPasteImpl actionPasteImpl_;
    ActionSelectImpl actionSelectImpl_;
    ActionClearSelectionImpl actionClearSelectionImpl_;
    ActionSetCursorIndexImpl actionSetCursorIndexImpl_;
    ActionExecSubComponentImpl actionExecSubComponentImpl_;
    ActionGetCursorIndexImpl actionGetCursorIndexImpl_;
    ActionClickImpl actionClickImpl_;
    ActionLongClickImpl actionLongClickImpl_;
    ActionsImpl actionsImpl_;
    GetRelatedElementInfoImpl getRelatedElementInfoImpl_;
    OnAccessibilityFocusCallbackImpl onAccessibilityFocusCallbackImpl_;
    GetWindowScenePositionImpl getWindowScenePositionImpl_;
    OnAccessibilityFocusCallbackImpl onUserAccessibilityFocusCallbackImpl_;

    bool isAccessibilityFocused_ = false;
    bool accessibilityGroup_ = false;
    bool accessibilityTextPreferred_ = false;
    bool accessibilityHoverPriority_ = false;
    int32_t childTreeId_ = -1;
    int32_t childWindowId_ = 0;
    RefPtr<UINode> accessibilityVirtualNode_;
    std::optional<std::string> accessibilityText_;
    std::optional<std::string> accessibilityDescription_;
    std::optional<std::string> accessibilityLevel_;
    std::optional<std::string> textTypeHint_;
    std::optional<std::string> accessibilityNextFocusInspectorKey_;
    std::optional<uint32_t> accessibilityActions_;
    std::optional<std::string> accessibilityRole_;
    std::optional<std::string> accessibilityCustomRole_;
    ACE_DISALLOW_COPY_AND_MOVE(AccessibilityProperty);

    std::optional<bool> isDisabled_;
    std::optional<bool> isSelected_;
    std::optional<int32_t> checkedType_;
    std::optional<bool> isUserCheckable_;

    std::optional<int32_t> minValue_;
    std::optional<int32_t> maxValue_;
    std::optional<int32_t> currentValue_;
    std::optional<int32_t> rangeMinValue_;
    std::optional<int32_t> rangeMaxValue_;
    std::optional<int32_t> rangeCurrentValue_;
    std::optional<std::string> textValue_;
};
} // namespace OHOS::Ace::NG

#endif
