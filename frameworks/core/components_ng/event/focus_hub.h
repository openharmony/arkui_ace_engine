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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/touch_event.h"
#include "core/event/key_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class FrameNode;
class FocusHub;
class EventHub;

using TabIndexNodeList = std::list<std::pair<int32_t, WeakPtr<FocusHub>>>;
constexpr int32_t DEFAULT_TAB_FOCUSED_INDEX = -2;
constexpr int32_t NONE_TAB_FOCUSED_INDEX = -1;
enum class FocusType : int32_t {
    DISABLE = 0,
    NODE = 1,
    SCOPE = 2,
};
enum class FocusNodeType : int32_t {
    DEFAULT = 0,
    GROUP_DEFAULT = 1,
};
enum class ScopeType : int32_t {
    OTHERS = 0,
    FLEX = 1,
};
enum class FocusStep : int32_t {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
};
using GetNextFocusNodeFunc = std::function<void(FocusStep, const WeakPtr<FocusHub>&, WeakPtr<FocusHub>&)>;

struct FocusPattern final {
    FocusPattern() = default;
    FocusPattern(FocusType focusType, bool focusable) : focusType(focusType), focusable(focusable) {}
    ~FocusPattern() = default;

    FocusType focusType = FocusType::DISABLE;
    bool focusable = false;
};

struct ScopeFocusAlgorithm final {
    ScopeFocusAlgorithm() = default;
    ScopeFocusAlgorithm(bool isVertical, bool isLeftToRight, ScopeType scopeType)
        : isVertical(isVertical), isLeftToRight(isLeftToRight), scopeType(scopeType)
    {}
    ScopeFocusAlgorithm(bool isVertical, bool isLeftToRight, ScopeType scopeType, GetNextFocusNodeFunc&& function)
        : isVertical(isVertical), isLeftToRight(isLeftToRight), scopeType(scopeType),
          getNextFocusNode(std::move(function))
    {}
    ~ScopeFocusAlgorithm() = default;

    bool isVertical { true };
    bool isLeftToRight { true };
    ScopeType scopeType { ScopeType::OTHERS };
    GetNextFocusNodeFunc getNextFocusNode;
};

class ACE_EXPORT FocusCallbackEvents : public virtual AceType {
    DECLARE_ACE_TYPE(FocusCallbackEvents, AceType)
public:
    explicit FocusCallbackEvents() = default;
    ~FocusCallbackEvents() override = default;

    void SetOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        onFocusCallback_ = std::move(onFocusCallback);
    }
    const OnFocusFunc& GetOnFocusCallback()
    {
        return onFocusCallback_;
    }

    void SetOnBlurCallback(OnBlurFunc&& onBlurCallback)
    {
        onBlurCallback_ = std::move(onBlurCallback);
    }
    const OnBlurFunc& GetOnBlurCallback()
    {
        return onBlurCallback_;
    }

    void SetOnKeyEventCallback(OnKeyCallbackFunc&& onKeyEventCallback)
    {
        onKeyEventCallback_ = std::move(onKeyEventCallback);
    }
    const OnKeyCallbackFunc& GetOnKeyEventCallback()
    {
        return onKeyEventCallback_;
    }

    void SetOnClickCallback(GestureEventFunc&& onClickEventCallback)
    {
        onClickEventCallback_ = std::move(onClickEventCallback);
    }
    const GestureEventFunc& GetOnClickCallback()
    {
        return onClickEventCallback_;
    }

    int32_t GetTabIndex() const
    {
        return tabIndex_;
    }
    void SetTabIndex(int32_t tabIndex)
    {
        tabIndex_ = tabIndex;
    }

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

    bool IsFocusOnTouch() const
    {
        return isFocusOnTouch_;
    }
    void SetIsFocusOnTouch(bool isFocusOnTouch)
    {
        isFocusOnTouch_ = isFocusOnTouch;
    }

    void SetIsDefaultHasFocused(bool isDefaultHasFocused)
    {
        isDefaultHasFocused_ = isDefaultHasFocused;
    }
    bool IsDefaultHasFocused() const
    {
        return isDefaultHasFocused_;
    }

    void SetIsDefaultGroupHasFocused(bool isDefaultGroupHasFocused)
    {
        isDefaultGroupHasFocused_ = isDefaultGroupHasFocused;
    }
    bool IsDefaultGroupHasFocused() const
    {
        return isDefaultGroupHasFocused_;
    }

private:
    OnFocusFunc onFocusCallback_;
    OnBlurFunc onBlurCallback_;
    OnKeyCallbackFunc onKeyEventCallback_;
    GestureEventFunc onClickEventCallback_;

    bool isFocusOnTouch_ { false };
    bool isDefaultFocus_ = { false };
    bool isDefaultHasFocused_ = { false };
    bool isDefaultGroupFocus_ = { false };
    bool isDefaultGroupHasFocused_ { false };

    int32_t tabIndex_ = 0;
};

class ACE_EXPORT FocusHub : public virtual AceType {
    DECLARE_ACE_TYPE(FocusHub, AceType)
public:
    explicit FocusHub(const WeakPtr<EventHub>& eventHub, FocusType type = FocusType::DISABLE, bool focusable = false)
        : eventHub_(eventHub), focusable_(focusable), focusType_(type)
    {}
    ~FocusHub() override = default;

    RefPtr<FrameNode> GetFrameNode() const;
    RefPtr<GeometryNode> GetGeometryNode() const;
    RefPtr<FocusHub> GetParentFocusHub() const;
    std::string GetFrameName() const;

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool RequestFocusImmediately();
    void RequestFocus() const;
    void UpdateAccessibilityFocusInfo();
    void SwitchFocus(const RefPtr<FocusHub>& focusNode);

    void LostFocus();
    void LostSelfFocus();
    void RemoveSelf();
    void RemoveChild(const RefPtr<FocusHub>& focusNode);
    bool GoToNextFocusLinear(bool reverse, const RectF& rect = RectF());
    bool TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect);

    bool AcceptFocusByRectOfLastFocus(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusNode(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusScope(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusFlex(const RectF& rect);

    void CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes);
    bool GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx);
    bool HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusHub>& curPage);
    RefPtr<FocusHub> GetChildFocusNodeByType(FocusNodeType nodeType = FocusNodeType::DEFAULT);
    RefPtr<FocusHub> GetChildFocusNodeById(const std::string& id);
    int32_t GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes);
    bool RequestFocusImmediatelyById(const std::string& id);

    bool IsFocusableByTab();
    bool IsFocusableNodeByTab();
    bool IsFocusableScopeByTab();

    bool IsFocusableWholePath();

    bool IsFocusable();
    bool IsFocusableNode();
    bool IsFocusableScope();

    bool IsParentFocusable() const
    {
        return parentFocusable_;
    }
    void SetParentFocusable(bool parentFocusable)
    {
        parentFocusable_ = parentFocusable;
    }

    void RefreshParentFocusable(bool focusable);

    void RefreshFocus();

    void SetFocusable(bool focusable);
    void SetShow(bool show);
    void SetShowNode(bool show);
    void SetShowScope(bool show);
    void SetEnabled(bool enabled);
    void SetEnabledNode(bool enabled);
    void SetEnabledScope(bool enabled);
    bool CanShow() const
    {
        return show_;
    }

    bool IsEnabled() const;

    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }

    void SetOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetOnFocusCallback(std::move(onFocusCallback));
    }
    OnFocusFunc GetOnFocusCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetOnFocusCallback() : nullptr;
    }

    void SetOnBlurCallback(OnBlurFunc&& onBlurCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetOnBlurCallback(std::move(onBlurCallback));
    }
    OnBlurFunc GetOnBlurCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetOnBlurCallback() : nullptr;
    }

    void SetOnKeyCallback(OnKeyCallbackFunc&& onKeyCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetOnKeyEventCallback(std::move(onKeyCallback));
    }
    OnKeyCallbackFunc GetOnKeyCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetOnKeyEventCallback() : nullptr;
    }

    void SetOnClickCallback(GestureEventFunc&& onClickCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetOnClickCallback(std::move(onClickCallback));
    }
    GestureEventFunc GetOnClickCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetOnClickCallback() : nullptr;
    }

    void SetOnFocusInternal(OnFocusFunc&& onFocusInternal)
    {
        onFocusInternal_ = std::move(onFocusInternal);
    }
    void SetOnBlurInternal(OnBlurFunc&& onBlurInternal)
    {
        onBlurInternal_ = std::move(onBlurInternal);
    }
    void SetOnPreFocusCallback(OnPreFocusFunc&& onPreFocusCallback)
    {
        onPreFocusCallback_ = std::move(onPreFocusCallback);
    }
    void SetOnKeyEventInternal(OnKeyEventFunc&& onKeyEventInternal)
    {
        onKeyEventInternal_ = std::move(onKeyEventInternal);
    }

    void FlushChildrenFocusHub();

    std::list<RefPtr<FocusHub>>& GetChildren()
    {
        FlushChildrenFocusHub();
        return focusNodes_;
    }

    bool IsChild() const
    {
        return focusType_ == FocusType::NODE;
    }

    void SetRect(const RectF& rect)
    {
        rectFromOrigin_ = rect;
    }
    const RectF& GetRect() const
    {
        return rectFromOrigin_;
    }

    void DumpFocusTree(int32_t depth);
    void DumpFocusNodeTree(int32_t depth);
    void DumpFocusScopeTree(int32_t depth);

    void OnClick(const KeyEvent& event);

    void SetFocusType(FocusType type)
    {
        focusType_ = type;
    }
    FocusType GetFocusType() const
    {
        return focusType_;
    }

    int32_t GetTabIndex() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetTabIndex() : 0;
    }
    void SetTabIndex(int32_t tabIndex)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetTabIndex(tabIndex);
    }

    bool IsDefaultFocus() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsDefaultFocus() : false;
    }
    void SetIsDefaultFocus(bool isDefaultFocus)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetIsDefaultFocus(isDefaultFocus);
    }

    bool IsDefaultGroupFocus() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsDefaultGroupFocus() : false;
    }
    void SetIsDefaultGroupFocus(bool isDefaultGroupFocus)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetIsDefaultGroupFocus(isDefaultGroupFocus);
    }

    bool IsFocusOnTouch() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsFocusOnTouch() : false;
    }
    void SetIsFocusOnTouch(bool isFocusOnTouch);

    void SetIsDefaultHasFocused(bool isDefaultHasFocused)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetIsDefaultHasFocused(isDefaultHasFocused);
    }
    bool IsDefaultHasFocused() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsDefaultHasFocused() : false;
    }

    void SetIsDefaultGroupHasFocused(bool isDefaultGroupHasFocused)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetIsDefaultGroupHasFocused(isDefaultGroupHasFocused);
    }
    bool IsDefaultGroupHasFocused() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsDefaultGroupHasFocused() : false;
    }

    std::optional<std::string> GetInspectorKey() const;

    void SetScopeFocusAlgorithm(const ScopeFocusAlgorithm& focusAlgorithm)
    {
        focusAlgorithm_ = focusAlgorithm;
    }

protected:
    bool OnKeyEvent(const KeyEvent& keyEvent);
    bool OnKeyEventNode(const KeyEvent& keyEvent);
    bool OnKeyEventScope(const KeyEvent& keyEvent);

    bool CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const;
    bool RequestNextFocus(bool vertical, bool reverse, const RectF& rect);

    void OnFocus();
    void OnFocusNode();
    void OnFocusScope();
    void OnBlur();
    void OnBlurNode();
    void OnBlurScope();

    void HandleFocus()
    {
        // Need update: void RenderNode::MoveWhenOutOfViewPort(bool hasEffect)
        OnFocus();
    }

private:
    bool CalculatePosition();

    OnFocusFunc onFocusInternal_;
    OnBlurFunc onBlurInternal_;
    OnKeyEventFunc onKeyEventInternal_;
    OnPreFocusFunc onPreFocusCallback_;

    RefPtr<FocusCallbackEvents> focusCallbackEvents_;

    RefPtr<TouchEventImpl> focusOnTouchListener_;

    WeakPtr<EventHub> eventHub_;

    std::list<RefPtr<FocusHub>> focusNodes_;
    std::list<RefPtr<FocusHub>>::iterator itLastFocusNode_ { focusNodes_.end() };
    WeakPtr<FocusHub> lastWeakFocusNode_ { nullptr };

    bool focusable_ { true };
    bool parentFocusable_ { true };
    bool currentFocus_ { false };
    bool isFirstFocusInPage_ { true };
    bool show_ { true };

    FocusType focusType_ = FocusType::DISABLE;
    RectF rectFromOrigin_;
    ScopeFocusAlgorithm focusAlgorithm_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H
