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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_FOCUS_FOCUS_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_FOCUS_FOCUS_NODE_H

#include <functional>
#include <list>

#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/event/key_event.h"

namespace OHOS::Ace {

class FocusNode;
class FocusGroup;
class ClickInfo;

using TabIndexNodeList = std::list<std::pair<int32_t, WeakPtr<FocusNode>>>;
constexpr int32_t DEFAULT_TAB_FOCUSED_INDEX = -2;
constexpr int32_t NONE_TAB_FOCUSED_INDEX = -1;

class ACE_FORCE_EXPORT FocusNode : public virtual AceType {
    DECLARE_ACE_TYPE(FocusNode, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(FocusNode);

public:
    explicit FocusNode(bool focusable = true) : focusable_(focusable) {}
    ~FocusNode() override = default;

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    void CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes);
    bool GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx);
    bool HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusGroup>& mainNode);
    bool RequestFocusImmediately();
    void UpdateAccessibilityFocusInfo();
    // Use pipeline to request focus. In this case that node gets focus when the layout needs to be completed.
    void RequestFocus();
    void LostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH);
    void LostSelfFocus();

    virtual bool IsFocusable() const
    {
        return enabled_ && show_ && focusable_ && parentFocusable_;
    }

    virtual bool IsFocusableByTab() const;

    bool IsFocusableWholePath() const;

    virtual bool AcceptFocusByRectOfLastFocus(const Rect& rect)
    {
        return IsFocusable();
    }

    void SetFocusable(bool focusable);

    bool IsParentFocusable() const
    {
        return parentFocusable_;
    }

    void SetParentFocusable(bool parentFocusable)
    {
        parentFocusable_ = parentFocusable;
    }

    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }

    void SetOnKeyCallback(std::function<bool(const KeyEvent&)>&& onKeyCallback)
    {
        onKeyCallback_ = std::move(onKeyCallback);
    }
    void SetOnKeyCallback(std::function<void(const std::shared_ptr<KeyEventInfo>&)>&& onKeyCallback)
    {
        onKeyEventCallback_ = std::move(onKeyCallback);
    }
    void SetOnClickCallback(std::function<void()>&& onClickCallback)
    {
        onClickCallback_ = std::move(onClickCallback);
    }
    void SetOnClickCallback(std::function<void(const std::shared_ptr<ClickInfo>&)>&& onClickCallback)
    {
        onClickEventCallback_ = std::move(onClickCallback);
    }
    void SetOnFocusCallback(std::function<void()>&& onFocusCallback)
    {
        onFocusCallback_ = std::move(onFocusCallback);
    }
    void SetOnBlurCallback(std::function<void()>&& onBlurCallback)
    {
        onBlurCallback_ = std::move(onBlurCallback);
    }
    void SetFocusMoveCallback(std::function<void()>&& focusMoveCallback)
    {
        focusMoveCallback_ = std::move(focusMoveCallback);
    }
    void SetOnDeleteCallback(std::function<void()>&& onDeleteCallback)
    {
        onDeleteCallback_ = std::move(onDeleteCallback);
    }

    void SetFocusIndex(int32_t focusIndex)
    {
        focusIndex_ = focusIndex;
        autoFocusIndex_ = false;
    }

    void RemoveSelf();

    WeakPtr<FocusGroup> GetParent() const
    {
        return parent_;
    }
    void SetParent(WeakPtr<FocusGroup>&& parent)
    {
        parent_ = std::move(parent);
    }

    virtual bool IsChild() const
    {
        return true;
    }

    void SetRect(const Rect& rect)
    {
        rectFromOrigin_ = rect;
    }
    const Rect& GetRect() const
    {
        return rectFromOrigin_;
    }

    bool CanShow() const
    {
        return show_;
    }
    virtual void SetShow(bool show);

    bool IsEnabled() const
    {
        return enabled_;
    }
    virtual void SetEnabled(bool enabled);

    virtual void DumpFocusTree(int32_t depth);

    virtual void DumpFocus();

    void RefreshFocus();

    virtual void RefreshParentFocusable(bool focusable);

    virtual void OnClick()
    {
        if (onClickCallback_) {
            onClickCallback_();
        }
    }

    virtual bool OnClick(const KeyEvent& event);

    int32_t GetTabIndex() const
    {
        return tabIndex_;
    }

    void SetTabIndex(int32_t tabIndex)
    {
        tabIndex_ = tabIndex;
    }

    const std::string& GetInspectorKey() const
    {
        return inspectorKey_;
    }

    void SetInspectorKey(std::string& inspectorKey)
    {
        inspectorKey_ = inspectorKey;
    }

    RefPtr<FocusNode> GetChildDefaultFocusNode(bool isGetDefaultFocus = true);

    RefPtr<FocusNode> GetChildFocusNodeById(const std::string& id);

    bool RequestFocusImmediatelyById(const std::string& id);

    bool IsDefaultFocus() const
    {
        return isDefaultFocus_;
    }
    void SetIsDefaultFocus(bool isDefaultFocus)
    {
        isDefaultFocus_ = isDefaultFocus;
    }

    bool IsDefaultGroupFocus() const
    {
        return isDefaultGroupFocus_;
    }
    void SetIsDefaultGroupFocus(bool isDefaultGroupFocus)
    {
        isDefaultGroupFocus_ = isDefaultGroupFocus;
    }

protected:
    virtual bool OnKeyEvent(const KeyEvent& keyEvent);

    virtual void OnFocus()
    {
        if (onFocusCallback_) {
            onFocusCallback_();
        }
        if (onFocus_) {
            onFocus_();
        }
    }
    virtual void OnBlur()
    {
        OnBlur(blurReason_);
        if (onBlurCallback_) {
            onBlurCallback_();
        }
        if (onBlur_) {
            onBlur_();
        }
    }
    virtual void OnBlur(BlurReason reason) {}
    virtual void OnFocusMove(KeyCode keyCode)
    {
        bool flag = keyCode == KeyCode::TV_CONTROL_UP || keyCode == KeyCode::TV_CONTROL_DOWN ||
                    keyCode == KeyCode::TV_CONTROL_LEFT || keyCode == KeyCode::TV_CONTROL_RIGHT ||
                    keyCode == KeyCode::KEY_TAB;
        if (onFocusMove_ && flag) {
            onFocusMove_((int)keyCode);
        }
    }

    virtual void HandleFocus()
    {
        if ((!AceType::InstanceOf<FocusGroup>(this)) && focusMoveCallback_) {
            focusMoveCallback_();
        }
        OnFocus();
    }

    virtual void OnDeleteEvent()
    {
        if (onDeleteCallback_) {
            onDeleteCallback_();
        }
    }

    virtual bool IsDeleteDisabled()
    {
        return false;
    }

    std::function<void(int)> onFocusMove_;
    std::function<void()> onFocus_;
    std::function<void()> onBlur_;
    int32_t tabIndex_ = 0;
    std::string inspectorKey_;
    bool isFocusOnTouch_ = false;
    bool isDefaultFocus_ = false;
    bool isDefaultGroupFocus_ = false;
    BlurReason blurReason_ = BlurReason::FOCUS_SWITCH;

private:
    static int32_t GenerateFocusIndex();

    WeakPtr<FocusGroup> parent_;

    std::function<void(std::shared_ptr<ClickInfo>&)> onClickEventCallback_;
    std::function<bool(const KeyEvent&)> onKeyCallback_;
    std::function<void(const std::shared_ptr<KeyEventInfo>&)> onKeyEventCallback_;
    std::function<void()> onClickCallback_;
    std::function<void()> onFocusCallback_;
    std::function<void()> onBlurCallback_;
    std::function<void()> focusMoveCallback_;
    std::function<void()> onDeleteCallback_;

    int32_t focusIndex_ { GenerateFocusIndex() };
    bool autoFocusIndex_ { true };

    bool focusable_ { true };
    bool parentFocusable_ { true };
    bool currentFocus_ { false };
    bool show_ { true };
    bool enabled_ { true };

    Rect rectFromOrigin_;
};

class ACE_EXPORT FocusGroup : public FocusNode {
    DECLARE_ACE_TYPE(FocusGroup, FocusNode);

public:
    FocusGroup() : FocusNode(true) {}
    ~FocusGroup() override = default;

    bool IsFocusable() const override;

    bool IsFocusableByTab() const override;

    void AddChild(const RefPtr<FocusNode>& focusNode);
    void AddChild(const RefPtr<FocusNode>& focusNode, const RefPtr<FocusNode>& nextFocusNode);
    void RemoveChild(const RefPtr<FocusNode>& focusNode);
    void RebuildChild(std::list<RefPtr<FocusNode>>&& rebuildFocusNodes);

    void SwitchFocus(const RefPtr<FocusNode>& focusNode);
    bool GoToNextFocus(bool reverse, const Rect& rect = Rect());

    int32_t GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes);

    const std::list<RefPtr<FocusNode>>& GetChildrenList() const
    {
        return focusNodes_;
    }

    bool IsChild() const override
    {
        return false;
    }

    void DumpFocusTree(int32_t depth) override;

    void SetShow(bool show) override;

    void SetEnabled(bool enabled) override;

    void RefreshParentFocusable(bool focusable) override;

    void SetIsGroupDefaultFocused(bool isGroupDefaultFocused)
    {
        isGroupDefaultFocused_ = isGroupDefaultFocused;
    }
    bool IsGroupDefaultFocused() const
    {
        return isGroupDefaultFocused_;
    }

    void SetIsDefaultHasFocused(bool isDefaultHasFocused)
    {
        isDefaultHasFocused_ = isDefaultHasFocused;
    }
    bool IsDefaultHasFocused() const
    {
        return isDefaultHasFocused_;
    }

protected:
    bool OnKeyEvent(const KeyEvent& keyEvent) override;
    void OnFocus() override;
    void OnBlur() override;

    bool TryRequestFocus(const RefPtr<FocusNode>& focusNode, const Rect& rect);
    bool CalculateRect(const RefPtr<FocusNode>& node, Rect& rect);
    bool AcceptFocusByRectOfLastFocus(const Rect& rect) override;

    virtual bool RequestNextFocus(bool vertical, bool reverse, const Rect& rect) = 0;

    std::list<RefPtr<FocusNode>> focusNodes_;
    std::list<RefPtr<FocusNode>>::iterator itLastFocusNode_ { focusNodes_.end() };

private:
    bool CalculatePosition();
    bool isDefaultHasFocused_ { false };
    bool isGroupDefaultFocused_ { false };
    bool isFirstFocusInPage_ { true };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_FOCUS_FOCUS_NODE_H
