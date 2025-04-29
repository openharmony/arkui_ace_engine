/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_NODE_H

#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "base/geometry/axis.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {

struct PositionInfo {
    double width = 0.0;
    double height = 0.0;
    double left = 0.0;
    double top = 0.0;
};

using ActionClickImpl = std::function<void()>;
using ActionLongClickImpl = std::function<void()>;
using ActionSetTextImpl = std::function<void(const std::string&)>;
using ActionScrollForwardImpl = std::function<bool()>;
using ActionScrollBackwardImpl = std::function<bool()>;
using ActionFocusImpl = std::function<void()>;
using ActionUpdateIdsImpl = std::function<void()>;
using FocusChangeCallback = std::function<void(const std::string&)>;
using ActionAccessibilityFocusImpl = std::function<void(bool)>;

using NodeId = int32_t;
// If no insertion location is specified, new child will be added to the end of children list by default.
constexpr int32_t DEFAULT_INDEX = -1;
constexpr uint64_t DEFAULT_ACTIONS = std::numeric_limits<uint64_t>::max();

class ACE_EXPORT AccessibilityNode : public AceType {
    DECLARE_ACE_TYPE(AccessibilityNode, AceType);

public:
    using ChartValue = std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>;

    AccessibilityNode(NodeId nodeId, const std::string& nodeName);
    ~AccessibilityNode() override = default;

    // node event action
    void SetActionClickImpl(const ActionClickImpl& actionClickImpl);
    bool ActionClick();
    void SetActionLongClickImpl(const ActionLongClickImpl& actionLongClickImpl);
    bool ActionLongClick();
    void SetActionSetTextImpl(const ActionSetTextImpl& actionSetTextImpl);
    bool ActionSetText(const std::string& text);
    void SetActionScrollForward(const ActionScrollForwardImpl& actionScrollForwardImpl);
    bool ActionScrollForward();
    void SetActionScrollBackward(const ActionScrollBackwardImpl& actionScrollBackwardImpl);
    bool ActionScrollBackward();
    void SetActionFocusImpl(const ActionFocusImpl& actionFocusImpl);
    bool ActionFocus();
    void SetActionUpdateIdsImpl(const ActionUpdateIdsImpl& actionUpdateIdsImpl);
    void ActionUpdateIds();
    void SetActionAccessibilityFocusImpl(const ActionAccessibilityFocusImpl& actionAccessibilityFocusImpl);
    bool ActionAccessibilityFocus(bool isFocus);

    // node base
    void SetAttr(const std::vector<std::pair<std::string, std::string>>& attrs);
    // used for inspector node in PC preview
    void SetStyle(const std::vector<std::pair<std::string, std::string>>& styles);
    void AddEvent(int32_t pageId, const std::vector<std::string>& events);
    void AddNode(const RefPtr<AccessibilityNode>& node, int32_t slot = DEFAULT_INDEX);
    void RemoveNode(const RefPtr<AccessibilityNode>& node);
    void Mount(int32_t slot);
    void AddOffsetForChildren(const Offset& offset);

    void SetWindowId(uint32_t windowId);

    uint32_t GetWindowId() const;

    void SetIsRootNode(bool isRootNode);

    bool IsRootNode() const;

    void ResetChildList(std::list<RefPtr<AccessibilityNode>>& children);

    const std::list<RefPtr<AccessibilityNode>> GetChildList() const;

    NodeId GetParentId() const;

    RefPtr<AccessibilityNode> GetParentNode() const;

    void SetParentNode(const RefPtr<AccessibilityNode>& parentNode);

    const std::string& GetTag() const;

    void SetTag(const std::string& tag);

    int32_t GetPageId() const;

    void SetPageId(int32_t pageId);

    void SetPositionInfo(const PositionInfo& positionInfo);

    const EventMarker& GetAccessibilityEventMarker() const;

    const EventMarker& GetClickEventMarker() const;

    const EventMarker& GetLongPressEventMarker() const;

    const EventMarker& GetSetTextEventMarker() const;

    const EventMarker& GetFocusEventMarker() const;

    void SetFocusChangeEventMarker(const EventMarker& eventId);

    void OnFocusChange(bool isFocus);

    const EventMarker& GetBlurEventMarker() const;

    // node attr need to barrierfree
    NodeId GetNodeId() const;

    const std::string& GetText() const;

    void SetText(const std::string& text);

    const std::string& GetHintText() const;

    void SetHintText(const std::string& hintText);

    const std::vector<int32_t>& GetChildIds() const;

    void SetChildIds(const std::vector<int32_t>& ids);

    double GetWidth() const;

    void SetWidth(double width);

    double GetHeight() const;

    void SetHeight(double height);

    double GetLeft() const;

    void SetLeft(double left);

    double GetTop() const;

    void SetTop(double top);

    bool GetCheckedState() const;

    void SetCheckedState(bool state);

    bool GetEnabledState() const;

    void SetEnabledState(bool state);

    bool GetEditable() const;

    void SetEditable(bool editable);

    bool GetFocusedState() const;

    void SetFocusedState(bool state);

    bool GetAccessibilityFocusedState() const;

    void SetAccessibilityFocusedState(bool state);

    bool GetSelectedState() const;

    void SetSelectedState(bool state);

    bool GetCheckableState() const;

    void SetCheckableState(bool state);

    bool GetClickableState() const;

    void SetClickableState(bool state);

    bool GetFocusableState() const;

    void SetFocusableState(bool state);

    bool GetScrollableState() const;

    void SetScrollableState(bool state);

    bool GetLongClickableState() const;

    void SetLongClickableState(bool state);

    bool GetIsMultiLine() const;

    void SetIsMultiLine(bool multiLine);

    bool GetIsPassword() const;

    void SetIsPassword(bool isPassword);

    std::unordered_set<AceAction> GetSupportAction(uint64_t enableActions = DEFAULT_ACTIONS) const;

    void AddSupportAction(AceAction action);

    void SetSupportAction(AceAction action, bool isEnable);

    const std::string& GetAccessibilityLabel() const;

    void SetAccessibilityLabel(const std::string& label);

    const std::string& GetAccessibilityHint() const;

    void SetAccessibilityHint(const std::string& hint);

    const std::string& GetImportantForAccessibility() const;

    void SetImportantForAccessibility(const std::string& importance);

    size_t GetMaxTextLength() const;

    void SetMaxTextLength(size_t length);

    int32_t GetTextSelectionStart() const;
    void SetTextSelectionStart(int32_t start);

    int32_t GetTextSelectionEnd() const;

    void SetTextSelectionEnd(int32_t end);

    const std::string& GetErrorText() const;

    void SetErrorText(const std::string& errorText);

    const std::string& GetJsComponentId() const;

    void SetJsComponentId(const std::string& jsComponentId);

    bool GetAccessible() const;

    void SetAccessible(bool accessible);

    AccessibilityValue GetAccessibilityValue() const;

    void SetAccessibilityValue(double cur, double min = 0.0, double max = 0.0);

    const std::unique_ptr<ChartValue>& GetChartValue() const;

    void PutChartValue(const std::string& groupName, const std::vector<std::pair<std::string, double>>& values);

    std::string GetInputType() const;

    AceTextCategory GetTextInputType() const;

    void SetTextInputType(AceTextCategory type);

    const AceCollectionInfo& GetCollectionInfo() const;

    void SetCollectionInfo(const AceCollectionInfo& collectionInfo);

    const AceCollectionItemInfo& GetCollectionItemInfo() const;

    void SetCollectionItemInfo(const AceCollectionItemInfo& collectionItemInfo);

    bool GetShown() const;

    bool GetVisible() const;

    void SetVisible(bool visible);

    const Rect& GetRect() const;

    void SetRect(const Rect& rect);

    const Rect& GetGlobalRect()
    {
        return globalRect_;
    }

    void SetGlobalRect(const Rect& rect)
    {
        globalRect_ = rect;
    }

    void ClearRect()
    {
        rect_ = Rect(0, 0, 0, 0);
    }

    bool IsValidRect() const
    {
        return isValidRect_;
    }

    bool GetClicked() const
    {
        return isClicked_;
    }

    void SetClicked(bool clicked)
    {
        isClicked_ = clicked;
    }

    void SetMarginSize(const Size& marginSize)
    {
        marginSize_ = marginSize;
    }

    Size GetMarginSize() const
    {
        return marginSize_;
    }

    const std::vector<std::pair<std::string, std::string>>& GetAttrs() const
    {
        return attrs_;
    }

    const std::vector<std::pair<std::string, std::string>>& GetStyles() const
    {
        return styles_;
    }

    void SetClipFlagToChild(bool clipFlag)
    {
        for (auto& child : children_) {
            child->SetClipFlagToChild(clipFlag);
        }
        clipFlag_ = clipFlag;
    }

    bool GetClipFlag()
    {
        return clipFlag_;
    }

    size_t GetListBeginIndex() const
    {
        return listBeginIndex_;
    }

    void SetListBeginIndex(const size_t& index)
    {
        listBeginIndex_ = index;
    }

    size_t GetListEndIndex() const
    {
        return listEndIndex_;
    }

    void SetListEndIndex(const size_t& index)
    {
        listEndIndex_ = index;
    }

    size_t GetListItemCounts() const
    {
        return listItemCounts_;
    }

    void SetListItemCounts(const size_t& index)
    {
        listItemCounts_ = index;
    }

    void SetTransformToChild(Matrix4 matrix4)
    {
        for (auto& child : children_) {
            child->SetTransformToChild(matrix4);
        }
        matrix4_ = matrix4;
    }

    Matrix4 GetMatrix4()
    {
        return matrix4_;
    }

    Rect GetRectWithTransform(const Rect& rect, Matrix4& matrix4)
    {
        Point ltPoint = matrix4 * Point(rect.Left(), rect.Top());
        Point rtPoint = matrix4 * Point(rect.Right(), rect.Top());
        Point lbPoint = matrix4 * Point(rect.Left(), rect.Bottom());
        Point rbPoint = matrix4 * Point(rect.Right(), rect.Bottom());
        auto left = std::min(std::min(ltPoint.GetX(), rtPoint.GetX()), std::min(lbPoint.GetX(), rbPoint.GetX()));
        auto right = std::max(std::max(ltPoint.GetX(), rtPoint.GetX()), std::max(lbPoint.GetX(), rbPoint.GetX()));
        auto top = std::min(std::min(ltPoint.GetY(), rtPoint.GetY()), std::min(lbPoint.GetY(), rbPoint.GetY()));
        auto bottom = std::max(std::max(ltPoint.GetY(), rtPoint.GetY()), std::max(lbPoint.GetY(), rbPoint.GetY()));
        return Rect(left, top, right - left, bottom - top);
    }

    bool GetMatrix4Flag()
    {
        if (matrix4_ == Matrix4()) {
            return false;
        }
        return true;
    }

#if defined(PREVIEW)
    // used for inspector node in PC preview
    bool GetClearRectInfoFlag() const
    {
        return isClearRectInfo_;
    }

    // used for inspector node in PC preview
    void SetClearRectInfoFlag(bool isClearRectInfo)
    {
        isClearRectInfo_ = isClearRectInfo;
    }

    // used for inspector node in PC preview
    void SetScaleToChild(double scale)
    {
        for (auto& child : children_) {
            child->SetScaleToChild(scale);
        }
        SetScale(scale);
    }

    // used for inspector node in PC preview
    void SetScaleCenterToChild(Offset center)
    {
        for (auto& child : children_) {
            child->SetScaleCenterToChild(center);
        }
        SetScaleCenter(center);
    }

    // used for inspector node in PC preview
    double GetScale()
    {
        return scale_;
    }

    // used for inspector node in PC preview
    void SetScale(double scale)
    {
        scale_ = scale;
        SetIsAnimationNode(true);
    }

    // used for inspector node in PC preview
    void SetScaleCenter(Offset center)
    {
        scaleCenter_ = center;
    }

    // used for inspector node in PC preview
    Offset GetScaleCenter()
    {
        return scaleCenter_;
    }

    // used for inspector node in PC preview
    void SetTranslateOffsetToChild(const Offset& offset)
    {
        for (auto& child : children_) {
            child->SetTranslateOffsetToChild(offset);
        }
        SetTranslateOffset(offset);
    }

    void SetTranslateOffset(const Offset& offset)
    {
        translateOffset_ = offset;
        SetIsAnimationNode(true);
    }

    Offset GetTranslateOffset() const
    {
        return translateOffset_;
    }

    // used for inspector node in PC preview
    void SetRotateToChild(const double& angle, const RotateAxis& Axis)
    {
        for (auto& child : children_) {
            child->SetRotateToChild(angle, Axis);
        }
        SetRotateAngle(angle);
        SetRotateAxis(Axis);
    }

    void SetRotateAngle(const double& angle)
    {
        rotateAngle_ = angle;
        SetIsAnimationNode(true);
    }

    double GetRotateAngle() const
    {
        return rotateAngle_;
    }

    void SetRotateAxis(const RotateAxis& Axis)
    {
        rotateAxis_ = Axis;
    }

    RotateAxis GetRotateAxis(RotateAxis Axis) const
    {
        return rotateAxis_;
    }

    bool IsAnimationNode() const
    {
        return isAnimationNode_;
    }

    void SetIsAnimationNode(bool IsAnimationNode)
    {
        isAnimationNode_ = IsAnimationNode;
    }

    int32_t GetZIndex()
    {
        return zIndex_;
    }

    void SetZIndex(int32_t index)
    {
        zIndex_ = index;
    }

    // only panel has ZIndex,others components is default value 0
    void SetZIndexToChild(int32_t index)
    {
        for (auto& child : children_) {
            child->SetZIndexToChild(index);
        }
        SetZIndex(index);
    }

    void UpdateRectWithChildRect()
    {
        if (children_.empty()) {
            return;
        }
        SetRect(children_.front()->GetRect());
    }
#endif

protected:
    // inner use, don't need to barrierfree
    NodeId nodeId_ = -1;
    int32_t pageId_ = -1;
    uint32_t windowId_ = 0;
    bool isRootNode_ = false;
    std::string inputType_;
    WeakPtr<AccessibilityNode> parentNode_;
    std::list<RefPtr<AccessibilityNode>> children_;
    ActionClickImpl actionClickImpl_;
    ActionLongClickImpl actionLongClickImpl_;
    ActionScrollForwardImpl actionScrollForwardImpl_;
    ActionScrollBackwardImpl actionScrollBackwardImpl_;
    ActionFocusImpl actionFocusImpl_;
    ActionUpdateIdsImpl actionUpdateIdsImpl_;
    ActionAccessibilityFocusImpl actionAccessibilityFocusIdsImpl_;
    ActionSetTextImpl actionSetTextImpl_;
    EventMarker onAccessibilityEventId_;
    EventMarker onClickId_;
    EventMarker onLongPressId_;
    EventMarker onSetTextId_;
    EventMarker onFocusId_;
    EventMarker onBlurId_;
    FocusChangeCallback focusChangeEventId_;

private:
    void SetOperableInfo();

    // node attr need to barrierfree
    size_t listBeginIndex_ = -1;
    size_t listEndIndex_ = -1;
    size_t listItemCounts_ = 0;
    size_t maxTextLength_ = 0;
    int32_t textSelectionStart_ = 0;
    int32_t textSelectionEnd_ = 0;
    std::string tag_;
    std::string text_;
    std::string hintText_;
    std::string errorText_;
    std::string jsComponentId_;
    std::string accessibilityLabel_;
    std::string accessibilityHint_;
    std::string importantForAccessibility_;
    AceTextCategory textInputType_ { AceTextCategory::INPUT_TYPE_DEFAULT };
    std::vector<int32_t> childIds_;
    uint64_t supportActions_ = 0;
    std::unique_ptr<ChartValue> chartValue_;

    Rect globalRect_;
    Rect rect_;
    Size marginSize_;
    union {
        struct {
            bool isValidRect_ : 1;
            bool isChecked_ : 1;
            bool isEditable_ : 1;
            bool isEnabled_ : 1;
            bool accessible_ : 1;
            bool isFocused_ : 1;
            bool isSelected_ : 1;
            bool isCheckable_ : 1;
            bool isClickable_ : 1;
            bool isFocusable_ : 1;
            bool isScrollable_ : 1;
            bool isLongClickable_ : 1;
            bool isMultiLine_ : 1;
            bool isPassword_ : 1;
            bool visible_ : 1;
            bool shown_ : 1;
            bool isClicked_ : 1;
            bool isAccessibilityFocused_ : 1;
        };
        uint64_t bits_ = 0;
    };
    AccessibilityValue accessibilityValue_;
    AceCollectionInfo collectionInfo_;
    AceCollectionItemInfo collectionItemInfo_;

    std::vector<std::pair<std::string, std::string>> attrs_;
    std::vector<std::pair<std::string, std::string>> styles_;
    bool clipFlag_ = false;
    Matrix4 matrix4_;
#if defined(PREVIEW)
    // used for inspector node in PC preview
    bool isClearRectInfo_ = false;
    // focus scale or translateScale for inspector node in PC preview
    double scale_ = 1.0;
    Offset scaleCenter_ { 0.0, 0.0 };
    Offset translateOffset_ { 0.0, 0.0 };
    double rotateAngle_ = 0.0;
    RotateAxis rotateAxis_ = RotateAxis::AXIS_Z;
    bool isAnimationNode_ = false;
    int32_t zIndex_ = 0;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_NODE_H
