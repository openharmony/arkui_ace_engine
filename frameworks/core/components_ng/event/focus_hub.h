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
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/event/touch_event.h"
#include "core/event/key_event.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {

class FrameNode;
class FocusHub;
class EventHub;
class FocusView;
class FocusManager;

using TabIndexNodeList = std::list<std::pair<int32_t, WeakPtr<FocusHub>>>;
constexpr int32_t DEFAULT_TAB_FOCUSED_INDEX = -2;
constexpr int32_t NONE_TAB_FOCUSED_INDEX = -1;
constexpr int32_t MASK_FOCUS_STEP_FORWARD = 0x10;
constexpr int32_t MASK_FOCUS_STEP_TAB = 0x5;

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
    PROJECT_AREA = 2,
};
enum class FocusStep : int32_t {
    NONE = 0x0,
    LEFT = 0x1,
    UP = 0x2,
    RIGHT = 0x11,
    DOWN = 0x12,
    LEFT_END = 0x3,
    UP_END = 0x4,
    RIGHT_END = 0X13,
    DOWN_END = 0x14,
    SHIFT_TAB = 0x5,
    TAB = 0x15,
};
enum class RequestFocusResult : int32_t {
    DEFAULT = 0,
    NON_FOCUSABLE = 1,
    NON_FOCUSABLE_ANCESTOR = 2,
    NON_EXIST = 3,
    NON_FOCUSABLE_BY_TAB = 4,
};
enum class SwitchingStartReason : int32_t {
    DEFAULT = 0,
    WINDOW_FOCUS = 1,
    REQUEST_FOCUS = 2,
    LOST_FOCUS_TO_VIEW_ROOT = 3,
    REMOVE_SELF = 4,
    REMOVE_CHILD = 5,
};
enum class SwitchingEndReason : int32_t {
    DEFAULT = 0,
    FOCUS_GUARD_DESTROY = 1,
    DEPENDENCE_SELF = 2,
    NO_FOCUSABLE_CHILD = 3,
    NODE_FOCUS = 4,
};
enum class SwitchingUpdateReason : int32_t {
    DEFAULT = 0,
    SWITCH_FOCUS = 1,
    ON_FOCUS_NODE = 2,
};

using GetNextFocusNodeFunc = std::function<void(FocusStep, const WeakPtr<FocusHub>&, WeakPtr<FocusHub>&)>;

enum class FocusStyleType : int32_t {
    NONE = -1,
    INNER_BORDER = 0,
    OUTER_BORDER = 1,
    CUSTOM_BORDER = 2,
    CUSTOM_REGION = 3,
    FORCE_BORDER = 4,
    FORCE_NONE = 5,
};

enum class OnKeyEventType : int32_t {
    DEFAULT = 0,
    CONTEXT_MENU = 1,
};

enum class FocusDependence : int32_t {
    CHILD = 0,
    SELF = 1,
    AUTO = 2,
};

enum class FocusPriority : int32_t {
    AUTO = 0,
    PRIOR = 2000,
    PREVIOUS = 3000,
};

class ACE_EXPORT FocusPaintParam : public virtual AceType {
    DECLARE_ACE_TYPE(FocusPaintParam, AceType)

public:
    FocusPaintParam() = default;
    ~FocusPaintParam() override = default;

    bool HasPaintRect() const
    {
        return paintRect.has_value();
    }
    const RoundRect& GetPaintRect() const
    {
        return paintRect.value();
    }

    bool HasPaintColor() const
    {
        return paintColor.has_value();
    }
    const Color& GetPaintColor() const
    {
        return paintColor.value();
    }

    bool HasPaintWidth() const
    {
        return paintWidth.has_value();
    }
    const Dimension& GetPaintWidth() const
    {
        return paintWidth.value();
    }

    bool HasFocusPadding() const
    {
        return focusPadding.has_value();
    }
    const Dimension& GetFocusPadding() const
    {
        return focusPadding.value();
    }
    void SetPaintRect(const RoundRect& rect)
    {
        paintRect = rect;
    }
    void SetPaintColor(const Color& color)
    {
        paintColor = color;
    }
    void SetPaintWidth(const Dimension& width)
    {
        paintWidth = width;
    }
    void SetFocusPadding(const Dimension& padding)
    {
        focusPadding = padding;
    }

private:
    std::optional<RoundRect> paintRect;
    std::optional<Color> paintColor;
    std::optional<Dimension> paintWidth;
    std::optional<Dimension> focusPadding;
};

class ACE_EXPORT FocusPattern : public virtual AceType {
    DECLARE_ACE_TYPE(FocusPattern, AceType)

public:
    FocusPattern() = default;
    FocusPattern(FocusType focusType, bool focusable) : focusType_(focusType), focusable_(focusable) {}
    FocusPattern(FocusType focusType, bool focusable, FocusStyleType styleType)
        : focusType_(focusType), focusable_(focusable), styleType_(styleType)
    {}
    FocusPattern(FocusType focusType, bool focusable, FocusStyleType styleType, const FocusPaintParam& paintParams)
        : focusType_(focusType), focusable_(focusable), styleType_(styleType)
    {
        if (!paintParams_) {
            paintParams_ = std::make_unique<FocusPaintParam>();
        }
        if (paintParams.HasPaintRect()) {
            paintParams_->SetPaintRect(paintParams.GetPaintRect());
        }
        if (paintParams.HasPaintColor()) {
            paintParams_->SetPaintColor(paintParams.GetPaintColor());
        }
        if (paintParams.HasPaintWidth()) {
            paintParams_->SetPaintWidth(paintParams.GetPaintWidth());
        }
        if (paintParams.HasFocusPadding()) {
            paintParams_->SetFocusPadding(paintParams.GetFocusPadding());
        }
    }
    FocusPattern(const FocusPattern& focusPattern)
    {
        focusType_ = focusPattern.GetFocusType();
        focusable_ = focusPattern.GetFocusable();
        styleType_ = focusPattern.GetStyleType();
        if (focusPattern.GetFocusPaintParams()) {
            SetFocusPaintParams(*focusPattern.GetFocusPaintParams());
        }
        isFocusActiveWhenFocused_ = focusPattern.GetIsFocusActiveWhenFocused();
    }
    ~FocusPattern() override = default;

    FocusType GetFocusType() const
    {
        return focusType_;
    }
    void SetFocusType(FocusType type)
    {
        focusType_ = type;
    }

    bool GetFocusable() const
    {
        return focusable_;
    }
    void SetFocusable(bool focusable)
    {
        focusable_ = focusable;
    }

    FocusStyleType GetStyleType() const
    {
        return styleType_;
    }
    void SetStyleType(FocusStyleType styleType)
    {
        styleType_ = styleType;
    }

    const std::unique_ptr<FocusPaintParam>& GetFocusPaintParams() const
    {
        return paintParams_;
    }
    void SetFocusPaintParams(const FocusPaintParam& paintParams)
    {
        if (!paintParams_) {
            paintParams_ = std::make_unique<FocusPaintParam>();
        }
        if (paintParams.HasPaintRect()) {
            paintParams_->SetPaintRect(paintParams.GetPaintRect());
        }
        if (paintParams.HasPaintColor()) {
            paintParams_->SetPaintColor(paintParams.GetPaintColor());
        }
        if (paintParams.HasPaintWidth()) {
            paintParams_->SetPaintWidth(paintParams.GetPaintWidth());
        }
        if (paintParams.HasFocusPadding()) {
            paintParams_->SetFocusPadding(paintParams.GetFocusPadding());
        }
    }

    bool GetIsFocusActiveWhenFocused() const
    {
        return isFocusActiveWhenFocused_;
    }
    void SetIsFocusActiveWhenFocused(bool value)
    {
        isFocusActiveWhenFocused_ = value;
    }

private:
    FocusType focusType_ = FocusType::DISABLE;
    bool focusable_ = false;
    FocusStyleType styleType_ = FocusStyleType::NONE;
    std::unique_ptr<FocusPaintParam> paintParams_ = nullptr;
    bool isFocusActiveWhenFocused_ = false;
};

enum class ScopeFocusDirection {
    VERTICAL = 0,
    HORIZONTAL,
    UNIVERSAL,
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
    ScopeFocusAlgorithm(ScopeFocusDirection direction, bool isVertical, bool isLeftToRight, ScopeType scopeType)
        : direction(direction), isVertical(isVertical), isLeftToRight(isLeftToRight), scopeType(scopeType)
    {}
    ScopeFocusAlgorithm(ScopeFocusDirection direction, bool isVertical, bool isLeftToRight, ScopeType scopeType,
        GetNextFocusNodeFunc&& function)
        : direction(direction), isVertical(isVertical), isLeftToRight(isLeftToRight), scopeType(scopeType),
          getNextFocusNode(std::move(function))
    {}
    ~ScopeFocusAlgorithm() = default;

    // isVertical will be deleted
    ScopeFocusDirection direction { ScopeFocusDirection::VERTICAL };
    bool isVertical { true };
    bool isLeftToRight { true };
    ScopeType scopeType { ScopeType::OTHERS };
    GetNextFocusNodeFunc getNextFocusNode;
};

class ACE_EXPORT FocusCallbackEvents : public virtual AceType {
    DECLARE_ACE_TYPE(FocusCallbackEvents, AceType)
public:
    FocusCallbackEvents() = default;
    ~FocusCallbackEvents() override = default;

    OnFocusFunc onFocusCallback_;
    OnFocusFunc onJSFrameNodeFocusCallback_;
    OnBlurFunc onBlurCallback_;
    OnBlurFunc onJSFrameNodeBlurCallback_;
    OnKeyCallbackFunc onKeyEventCallback_;
    OnKeyCallbackFunc onJSFrameNodeKeyEventCallback_;
    OnKeyPreImeFunc onKeyPreImeCallback_;
    GestureEventFunc onClickEventCallback_;

    WeakPtr<FocusHub> defaultFocusNode_;

    std::optional<bool> isFocusOnTouch_;
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
    explicit FocusHub(const WeakPtr<EventHub>& eventHub, const FocusPattern& focusPattern)
    {
        eventHub_ = eventHub;
        focusable_ = focusPattern.GetFocusable();
        focusType_ = focusPattern.GetFocusType();
        focusStyleType_ = focusPattern.GetStyleType();
        if (focusPattern.GetFocusPaintParams()) {
            SetFocusPaintParamsPtr(focusPattern.GetFocusPaintParams());
        }
        isFocusActiveWhenFocused_ = focusPattern.GetIsFocusActiveWhenFocused();
    }
    ~FocusHub() override = default;

    static constexpr int32_t SCROLL_TO_HEAD = -1;
    static constexpr int32_t SCROLL_TO_TAIL = -2;

    void SetFocusStyleType(FocusStyleType type)
    {
        focusStyleType_ = type;
    }
    FocusStyleType GetFocusStyleType() const
    {
        return focusStyleType_;
    }

    BlurReason GetBlurReason() const
    {
        return blurReason_;
    }

    void SetFocusPaintParamsPtr(const std::unique_ptr<FocusPaintParam>& paramsPtr)
    {
        CHECK_NULL_VOID(paramsPtr);
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
        }
        if (paramsPtr->HasPaintRect()) {
            focusPaintParamsPtr_->SetPaintRect(paramsPtr->GetPaintRect());
        }
        if (paramsPtr->HasPaintColor()) {
            focusPaintParamsPtr_->SetPaintColor(paramsPtr->GetPaintColor());
        }
        if (paramsPtr->HasPaintWidth()) {
            focusPaintParamsPtr_->SetPaintWidth(paramsPtr->GetPaintWidth());
        }
        if (paramsPtr->HasFocusPadding()) {
            focusPaintParamsPtr_->SetFocusPadding(paramsPtr->GetFocusPadding());
        }
    }

    bool HasPaintRect() const
    {
        return focusPaintParamsPtr_ ? focusPaintParamsPtr_->HasPaintRect() : false;
    }
    RoundRect GetPaintRect() const
    {
        CHECK_NULL_RETURN(focusPaintParamsPtr_, RoundRect());
        return focusPaintParamsPtr_->GetPaintRect();
    }

    bool HasPaintColor() const
    {
        return focusPaintParamsPtr_ ? focusPaintParamsPtr_->HasPaintColor() : false;
    }
    const Color& GetPaintColor() const
    {
        CHECK_NULL_RETURN(focusPaintParamsPtr_, Color::TRANSPARENT);
        return focusPaintParamsPtr_->GetPaintColor();
    }

    bool HasPaintWidth() const
    {
        return focusPaintParamsPtr_ ? focusPaintParamsPtr_->HasPaintWidth() : false;
    }
    Dimension GetPaintWidth() const
    {
        CHECK_NULL_RETURN(focusPaintParamsPtr_, Dimension());
        return focusPaintParamsPtr_->GetPaintWidth();
    }

    bool HasFocusPadding() const
    {
        return focusPaintParamsPtr_ ? focusPaintParamsPtr_->HasFocusPadding() : false;
    }

    bool HasBackwardFocusMovement() const
    {
        return hasBackwardMovement_;
    }

    bool HasForwardFocusMovement() const
    {
        return hasForwardMovement_;
    }

    void ClearFocusMovementFlags()
    {
        hasBackwardMovement_ = false;
        hasForwardMovement_ = false;
    }

    bool HasBackwardFocusMovementInChildren();
    bool HasForwardFocusMovementInChildren();
    void ClearFocusMovementFlagsInChildren();
    void SetForceProcessOnKeyEventInternal(bool forceProcessOnKeyEventInternal)
    {
        forceProcessOnKeyEventInternal_ = forceProcessOnKeyEventInternal;
    }

    Dimension GetFocusPadding() const
    {
        CHECK_NULL_RETURN(focusPaintParamsPtr_, Dimension());
        return focusPaintParamsPtr_->GetFocusPadding();
    }
    void SetPaintRect(const RoundRect& rect)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
        }
        CHECK_NULL_VOID(focusPaintParamsPtr_);
        focusPaintParamsPtr_->SetPaintRect(rect);
    }
    void SetPaintColor(const Color& color)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
        }
        CHECK_NULL_VOID(focusPaintParamsPtr_);
        focusPaintParamsPtr_->SetPaintColor(color);
    }
    void SetPaintWidth(const Dimension& width)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
        }
        CHECK_NULL_VOID(focusPaintParamsPtr_);
        focusPaintParamsPtr_->SetPaintWidth(width);
    }
    void SetFocusPadding(const Dimension& padding)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
        }
        CHECK_NULL_VOID(focusPaintParamsPtr_);
        focusPaintParamsPtr_->SetFocusPadding(padding);
    }

    RefPtr<FocusManager> GetFocusManager() const;
    RefPtr<FrameNode> GetFrameNode() const;
    RefPtr<GeometryNode> GetGeometryNode() const;
    RefPtr<FocusHub> GetParentFocusHub() const;
    RefPtr<FocusHub> GetParentFocusHubWithBoundary() const;
    RefPtr<FocusHub> GetRootFocusHub();
    std::string GetFrameName() const;
    int32_t GetFrameId() const;

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool RequestFocusImmediately(bool isJudgeRootTree = false);
    void RequestFocus() const;
    void SwitchFocus(const RefPtr<FocusHub>& focusNode);
    void HandleLastFocusNodeInFocusWindow();

    static void LostFocusToViewRoot();

    bool IsViewRootScope();
    void LostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH);
    void LostSelfFocus();
    void RemoveSelf(BlurReason reason = BlurReason::FRAME_DESTROY);
    void RemoveChild(const RefPtr<FocusHub>& focusNode, BlurReason reason = BlurReason::FRAME_DESTROY);
    bool GoToNextFocusLinear(FocusStep step, const RectF& rect = RectF());
    bool TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect, FocusStep step = FocusStep::NONE);
    void InheritFocus()
    {
        OnFocusScope(true);
    }

    void CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes);
    bool GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx);
    bool HandleFocusByTabIndex(const KeyEvent& event);
    RefPtr<FocusHub> GetChildFocusNodeByType(FocusNodeType nodeType = FocusNodeType::DEFAULT);
    RefPtr<FocusHub> GetChildFocusNodeById(const std::string& id);
    bool TriggerFocusScroll();
    int32_t GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes) const;
    bool RequestFocusImmediatelyById(const std::string& id, bool isSyncRequest = false);
    RefPtr<FocusView> GetFirstChildFocusView();

    bool IsFocusableByTab();
    bool IsFocusableNodeByTab();
    bool IsFocusableScopeByTab();

    bool IsFocusableWholePath();
    bool IsSelfFocusableWholePath();
    bool IsOnRootTree() const;

    bool IsFocusable();
    bool IsFocusableNode();
    bool IsFocusableScope();

    bool IsSyncRequestFocusable();
    bool IsSyncRequestFocusableNode();
    bool IsSyncRequestFocusableScope();

    bool IsParentFocusable() const
    {
        return parentFocusable_;
    }
    void SetParentFocusable(bool parentFocusable);

    void SetFocusable(bool focusable, bool isExplicit = true);

    bool GetFocusable() const
    {
        return focusable_;
    }

    void SetShow(bool show);
    void SetEnabled(bool enabled);

    bool IsShow() const;

    bool IsEnabled() const;

    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }
    bool IsCurrentFocusWholePath();

    bool HasFocusedChild();

    void ClearUserOnFocus()
    {
        if (focusCallbackEvents_ && focusCallbackEvents_->onFocusCallback_) {
            focusCallbackEvents_->onFocusCallback_ = nullptr;
        }
    }

    void SetOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onFocusCallback_ = std::move(onFocusCallback);
    }
    OnFocusFunc GetOnFocusCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onFocusCallback_ : nullptr;
    }

    void ClearJSFrameNodeOnFocusCallback()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->onJSFrameNodeFocusCallback_ = nullptr;
        }
    }
    void SetJSFrameNodeOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onJSFrameNodeFocusCallback_ = std::move(onFocusCallback);
    }
    OnFocusFunc GetOnJSFrameNodeFocusCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onJSFrameNodeFocusCallback_ : nullptr;
    }

    void ClearUserOnBlur()
    {
        if (focusCallbackEvents_ && focusCallbackEvents_->onBlurCallback_) {
            focusCallbackEvents_->onBlurCallback_ = nullptr;
        }
    }

    void SetOnBlurCallback(OnBlurFunc&& onBlurCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onBlurCallback_ = std::move(onBlurCallback);
    }

    OnBlurFunc GetOnBlurCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onBlurCallback_ : nullptr;
    }

    void ClearJSFrameNodeOnBlurCallback()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->onJSFrameNodeBlurCallback_ = nullptr;
        }
    }
    void SetJSFrameNodeOnBlurCallback(OnBlurFunc&& onBlurCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onJSFrameNodeBlurCallback_ = std::move(onBlurCallback);
    }
    OnBlurFunc GetOnJSFrameNodeBlurCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onJSFrameNodeBlurCallback_ : nullptr;
    }

    void SetOnKeyCallback(OnKeyCallbackFunc&& onKeyCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onKeyEventCallback_ = std::move(onKeyCallback);
    }

    void ClearUserOnKey()
    {
        if (focusCallbackEvents_ && focusCallbackEvents_->onKeyEventCallback_) {
            focusCallbackEvents_->onKeyEventCallback_ = nullptr;
        }
    }

    OnKeyCallbackFunc GetOnKeyCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onKeyEventCallback_ : nullptr;
    }

    void SetOnKeyPreImeCallback(OnKeyPreImeFunc&& onKeyCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onKeyPreImeCallback_ = std::move(onKeyCallback);
    }

    void ClearOnKeyPreIme()
    {
        if (focusCallbackEvents_ && focusCallbackEvents_->onKeyPreImeCallback_) {
            focusCallbackEvents_->onKeyPreImeCallback_ = nullptr;
        }
    }

    OnKeyPreImeFunc GetOnKeyPreIme()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onKeyPreImeCallback_ : nullptr;
    }

    void ClearJSFrameNodeOnKeyCallback()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->onJSFrameNodeKeyEventCallback_ = nullptr;
        }
    }

    void SetJSFrameNodeOnKeyCallback(OnKeyCallbackFunc&& onKeyCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onJSFrameNodeKeyEventCallback_ = std::move(onKeyCallback);
    }
    
    OnKeyCallbackFunc GetOnJSFrameNodeKeyCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onJSFrameNodeKeyEventCallback_ : nullptr;
    }

    void SetOnClickCallback(GestureEventFunc&& onClickCallback)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->onClickEventCallback_ = std::move(onClickCallback);
    }
    GestureEventFunc GetOnClickCallback()
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->onClickEventCallback_ : nullptr;
    }

    void SetOnFocusInternal(OnFocusFunc&& onFocusInternal)
    {
        onFocusInternal_ = std::move(onFocusInternal);
    }
    void SetOnBlurInternal(OnBlurFunc&& onBlurInternal)
    {
        onBlurInternal_ = std::move(onBlurInternal);
    }
    void SetOnBlurReasonInternal(OnBlurReasonFunc&& onBlurReasonInternal)
    {
        onBlurReasonInternal_ = std::move(onBlurReasonInternal);
    }
    void SetOnPreFocusCallback(OnPreFocusFunc&& onPreFocusCallback)
    {
        onPreFocusCallback_ = std::move(onPreFocusCallback);
    }

    void SetOnClearFocusStateInternal(OnClearFocusStateFunc&& onClearFocusCallback)
    {
        onClearFocusStateCallback_ = std::move(onClearFocusCallback);
    }

    void SetOnPaintFocusStateInternal(OnPaintFocusStateFunc&& onPaintFocusCallback)
    {
        onPaintFocusStateCallback_ = std::move(onPaintFocusCallback);
    }

    void SetOnKeyEventInternal(OnKeyEventFunc&& onKeyEvent, OnKeyEventType type = OnKeyEventType::DEFAULT)
    {
        onKeyEventsInternal_[type] = std::move(onKeyEvent);
    }

    bool FindContextMenuOnKeyEvent(OnKeyEventType type)
    {
        return (onKeyEventsInternal_.find(type) != onKeyEventsInternal_.end());
    }

    bool ProcessOnKeyEventInternal(const KeyEvent& event)
    {
        bool result = false;
        for (const auto& onKeyEvent : onKeyEventsInternal_) {
            auto callback = onKeyEvent.second;
            if (callback && callback(event)) {
                result = true;
            }
        }
        return result;
    }

    void GetChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes);

    std::list<RefPtr<FocusHub>>::iterator FlushChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes);

    std::list<RefPtr<FocusHub>> GetChildren()
    {
        std::list<RefPtr<FocusHub>> focusNodes;
        GetChildrenFocusHub(focusNodes);
        return focusNodes;
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

    void DumpFocusTree(int32_t depth, bool hasJson = false);
    void DumpFocusNodeTree(int32_t depth);
    void DumpFocusScopeTree(int32_t depth);
    void DumpFocusUie();
    void DumpFocusUieInJson(std::unique_ptr<JsonValue>& json);

    bool OnClick(const KeyEvent& event);

    void SetFocusType(FocusType type)
    {
        if (focusType_ != type && type == FocusType::DISABLE) {
            RemoveSelf(BlurReason::FOCUS_SWITCH);
        }
        focusType_ = type;

        if (IsImplicitFocusableScope() && focusDepend_ == FocusDependence::CHILD) {
            focusDepend_ = FocusDependence::AUTO;
        }
    }
    FocusType GetFocusType() const
    {
        return focusType_;
    }

    int32_t GetTabIndex() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->tabIndex_ : 0;
    }
    void SetTabIndex(int32_t tabIndex)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->tabIndex_ = tabIndex;
    }

    bool IsDefaultFocus() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->isDefaultFocus_ : false;
    }

    void SetIsDefaultFocus(bool isDefaultFocus)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->isDefaultFocus_ = isDefaultFocus;
    }

    bool IsDefaultGroupFocus() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->isDefaultGroupFocus_ : false;
    }

    void SetIsDefaultGroupFocus(bool isDefaultGroupFocus)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->isDefaultGroupFocus_ = isDefaultGroupFocus;
    }

    WeakPtr<FocusHub> GetDefaultFocusNode() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->defaultFocusNode_ : nullptr;
    }

    void SetDefaultFocusNode(const WeakPtr<FocusHub>& node)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->defaultFocusNode_ = node;
    }

    std::optional<bool> IsFocusOnTouch() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->isFocusOnTouch_ : std::nullopt;
    }

    void SetIsFocusOnTouch(bool isFocusOnTouch);

    void SetIsDefaultHasFocused(bool isDefaultHasFocused)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->isDefaultHasFocused_ = isDefaultHasFocused;
    }

    bool IsDefaultHasFocused() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->isDefaultHasFocused_ : false;
    }

    void SetIsDefaultGroupHasFocused(bool isDefaultGroupHasFocused)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->isDefaultGroupHasFocused_ = isDefaultGroupHasFocused;
    }

    bool IsDefaultGroupHasFocused() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->isDefaultGroupHasFocused_ : false;
    }

    bool IsImplicitFocusableScope() const
    {
        return (focusType_ == FocusType::SCOPE) && focusable_ && implicitFocusable_;
    }

    std::optional<std::string> GetInspectorKey() const;

    bool PaintFocusState(bool isNeedStateStyles = true);
    bool PaintFocusStateToRenderContext();
    void GetPaintColorFromBox(Color& paintColor);
    void GetPaintWidthFromBox(Dimension& paintWidth);
    void GetPaintPaddingVp(Dimension& focusPaddingVp);
    bool PaintAllFocusState();
    bool PaintInnerFocusState(const RoundRect& paintRect, bool forceUpdate = false);
    void ClearFocusState(bool isNeedStateStyles = true);
    void ClearAllFocusState();
    void PrintOnKeyEventUserInfo(const KeyEvent& keyEvent, bool retCallback);

    void SetInnerFocusPaintRectCallback(const std::function<void(RoundRect&)>& callback)
    {
        getInnerFocusRectFunc_ = callback;
    }

    void SetLastWeakFocusNode(const WeakPtr<FocusHub>& focusHub)
    {
        lastWeakFocusNode_ = focusHub;
    }
    WeakPtr<FocusHub> GetLastWeakFocusNode() const
    {
        return lastWeakFocusNode_;
    }

    void SetIsFocusUnit(bool isFocusUnit)
    {
        isFocusUnit_ = isFocusUnit;
    }

    FocusDependence GetFocusDependence() const
    {
        return focusDepend_;
    }
    void SetFocusDependence(FocusDependence focusDepend)
    {
        focusDepend_ = focusDepend;
    }

    size_t GetFocusableCount()
    {
        size_t count = 0;
        auto children = GetChildren();
        for (const auto& child : children) {
            if (child->IsFocusable()) {
                count++;
            }
        }
        return count;
    }

    void SetIsFocusActiveWhenFocused(bool value)
    {
        isFocusActiveWhenFocused_ = value;
    }
    bool GetIsFocusActiveWhenFocused() const
    {
        return isFocusActiveWhenFocused_;
    }

    static inline bool IsFocusStepVertical(FocusStep step)
    {
        return (static_cast<uint32_t>(step) & 0x1) == 0;
    }

    static inline bool IsFocusStepForward(FocusStep step, bool isRtl = false)
    {
        bool isForward = (static_cast<uint32_t>(step) & MASK_FOCUS_STEP_FORWARD) != 0;
        if (isRtl && (step == FocusStep::RIGHT || step == FocusStep::LEFT)) {
            isForward = !isForward;
        }
        return isForward;
    }

    static inline bool IsFocusStepTab(FocusStep step)
    {
        return (static_cast<uint32_t>(step) & MASK_FOCUS_STEP_TAB) == MASK_FOCUS_STEP_TAB;
    }

    static inline FocusStep GetRealFocusStepByTab(FocusStep moveStep, bool isRtl = false)
    {
        if (isRtl) {
            return moveStep == FocusStep::TAB ? FocusStep::LEFT : FocusStep::RIGHT;
        } else {
            return moveStep == FocusStep::TAB ? FocusStep::RIGHT : FocusStep::LEFT;
        }
    }
    
    static double GetProjectAreaOnRect(const RectF& rect, const RectF& projectRect, FocusStep step);

    void SetFocusScopeId(const std::string& focusScopeId, bool isGroup, bool arrowKeyStepOut = true);
    void SetFocusScopePriority(const std::string& focusScopeId, const uint32_t focusPriority);
    void RemoveFocusScopeIdAndPriority();
    bool AcceptFocusOfPriorityChild();
    bool SetLastWeakFocusNodeToPreviousNode();
    void SetLastWeakFocusToPreviousInFocusView();
    bool GetIsFocusGroup() const
    {
        return isGroup_;
    }

    bool GetIsFocusScope() const
    {
        return isFocusScope_;
    }

    std::string GetFocusScopeId() const
    {
        return focusScopeId_;
    }

    FocusBox& GetFocusBox()
    {
        return box_;
    }

    FocusPriority GetFocusPriority() const
    {
        return focusPriority_;
    }

    static void ToJsonValue(
        const RefPtr<FocusHub>& hub, std::unique_ptr<JsonValue>& json, const InspectorFilter& filter);

    bool FocusToHeadOrTailChild(bool isHead);

    WeakPtr<FocusHub> GetUnfocusableParentFocusNode();

    bool IsNeedPaintFocusStateSelf();
protected:
    bool OnKeyEvent(const KeyEvent& keyEvent);
    bool OnKeyEventNode(const KeyEvent& keyEvent);
    bool OnKeyEventScope(const KeyEvent& keyEvent);
    bool RequestNextFocusOfKeyTab(const KeyEvent& keyEvent);
    bool OnKeyPreIme(KeyEventInfo& info, const KeyEvent& keyEvent);

    bool AcceptFocusOfSpecifyChild(FocusStep step);
    bool AcceptFocusOfLastFocus();
    bool AcceptFocusByRectOfLastFocus(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusNode(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusFlex(const RectF& rect);

    bool CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const;
    bool RequestNextFocus(FocusStep moveStep, const RectF& rect);
    bool RequestNextFocusByDefaultAlgorithm(FocusStep moveStep, const RectF& rect);
    bool RequestNextFocusByCustomAlgorithm(FocusStep moveStep, const RectF& rect);

    void OnFocus();
    void OnFocusNode();
    void OnFocusScope(bool currentHasFocused = false);
    void OnBlur();
    void OnBlurNode();
    void OnBlurScope();

    void HandleFocus()
    {
        // Need update: void RenderNode::MoveWhenOutOfViewPort(bool hasEffect)
        OnFocus();
    }

private:
    friend class FocusView;

    friend class FocusManager;
 
    bool CalculatePosition();

    void SetScopeFocusAlgorithm();

    void SetLastFocusNodeIndex(const RefPtr<FocusHub>& focusNode);

    void ScrollToLastFocusIndex() const;

    void CheckFocusStateStyle(bool onFocus);
    bool HasFocusStateStyle();

    bool IsNeedPaintFocusState();

    bool ScrollByOffset();
    bool ScrollByOffsetToParent(const RefPtr<FrameNode>& parentFrameNode) const;

    RefPtr<FocusHub> GetNearestNodeByProjectArea(const std::list<RefPtr<FocusHub>>& allNodes, FocusStep step);

    bool UpdateFocusView();

    bool IsFocusAbleChildOf(const RefPtr<FocusHub>& parentFocusHub);
    WeakPtr<FocusHub> GetChildPriorfocusNode(const std::string& focusScopeId);
    bool RequestFocusByPriorityInScope();
    bool IsInFocusGroup();
    bool IsNestingFocusGroup();
    void SetLastWeakFocusNodeWholeScope(const std::string &focusScopeId);

    void RaiseZIndex(); // Recover z-index in ClearFocusState

    bool RequestFocusImmediatelyInner(bool isJudgeRootTree = false);
    bool OnKeyEventNodeInternal(const KeyEvent& keyEvent);
    bool OnKeyEventNodeUser(KeyEventInfo& info, const KeyEvent& keyEvent);
    bool RequestNextFocusByKey(const KeyEvent& keyEvent);

    bool IsComponentDirectionRtl();

    void DumpFocusNodeTreeInJson(int32_t depth);
    void DumpFocusScopeTreeInJson(int32_t depth);

    bool SkipFocusMoveBeforeRemove();

    bool IsArrowKeyStepOut(FocusStep moveStep);

    OnFocusFunc onFocusInternal_;
    OnBlurFunc onBlurInternal_;
    OnBlurReasonFunc onBlurReasonInternal_;
    std::unordered_map<OnKeyEventType, OnKeyEventFunc> onKeyEventsInternal_;
    OnPreFocusFunc onPreFocusCallback_;
    OnClearFocusStateFunc onClearFocusStateCallback_;
    OnPaintFocusStateFunc onPaintFocusStateCallback_;

    RefPtr<FocusCallbackEvents> focusCallbackEvents_;

    RefPtr<TouchEventImpl> focusOnTouchListener_;

    WeakPtr<EventHub> eventHub_;

    WeakPtr<FocusHub> lastWeakFocusNode_ { nullptr };
    int32_t lastFocusNodeIndex_ { -1 };
    int32_t lastTabIndexNodeId_ { DEFAULT_TAB_FOCUSED_INDEX };

    bool focusable_ { true };
    bool isFocusableExplicit_ { false };
    bool implicitFocusable_ { false };
    bool parentFocusable_ { true };
    bool currentFocus_ { false };
    bool isFocusUnit_ { false };
    bool hasForwardMovement_ { false };
    bool hasBackwardMovement_ { false };
    bool isFocusActiveWhenFocused_ { false };
    bool isRaisedZIndex_ { false };
    bool forceProcessOnKeyEventInternal_ { false }; // extension use only

    FocusType focusType_ = FocusType::DISABLE;
    FocusStyleType focusStyleType_ = FocusStyleType::NONE;
    std::unique_ptr<FocusPaintParam> focusPaintParamsPtr_;
    std::function<void(RoundRect&)> getInnerFocusRectFunc_;
    FocusBox box_;

    RectF rectFromOrigin_;
    ScopeFocusAlgorithm focusAlgorithm_;
    BlurReason blurReason_ = BlurReason::FOCUS_SWITCH;
    FocusDependence focusDepend_ = FocusDependence::CHILD;

    std::string focusScopeId_;
    bool isFocusScope_ { false };
    bool isGroup_ { false };
    FocusPriority focusPriority_ = FocusPriority::AUTO;
    bool arrowKeyStepOut_ { true };
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H
