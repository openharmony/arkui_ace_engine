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

using GetNextFocusNodeFunc = std::function<void(FocusStep, const WeakPtr<FocusHub>&, WeakPtr<FocusHub>&)>;

enum class FocusStyleType : int32_t {
    NONE = -1,
    INNER_BORDER = 0,
    OUTER_BORDER = 1,
    CUSTOM_BORDER = 2,
    CUSTOM_REGION = 3,
};

enum class OnKeyEventType : int32_t {
    DEFAULT = 0,
    CONTEXT_MENU = 1,
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

private:
    FocusType focusType_ = FocusType::DISABLE;
    bool focusable_ = false;
    FocusStyleType styleType_ = FocusStyleType::NONE;
    std::unique_ptr<FocusPaintParam> paintParams_ = nullptr;
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
    FocusCallbackEvents() = default;
    ~FocusCallbackEvents() override = default;

    void ClearOnFocusCallback()
    {
        if (onFocusCallback_) {
            onFocusCallback_ = nullptr;
        }
    }

    void SetOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        onFocusCallback_ = std::move(onFocusCallback);
    }

    const OnFocusFunc& GetOnFocusCallback()
    {
        return onFocusCallback_;
    }

    void ClearOnBlurCallback()
    {
        if (onBlurCallback_) {
            onBlurCallback_ = nullptr;
        }
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

    void ClearOnKeyEventCallback()
    {
        if (onKeyEventCallback_) {
            onKeyEventCallback_ = nullptr;
        }
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

    WeakPtr<FocusHub> GetDefaultFocusNode() const
    {
        return defaultFocusNode_;
    }

    void SetDefaultFocusNode(const WeakPtr<FocusHub>& node)
    {
        defaultFocusNode_ = node;
    }

    std::optional<bool> IsFocusOnTouch() const
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
    {
        MarkRootFocusNeedUpdate();
    }
    ~FocusHub() override = default;

    void SetFocusStyleType(FocusStyleType type)
    {
        focusStyleType_ = type;
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
    Dimension GetFocusPadding() const
    {
        CHECK_NULL_RETURN(focusPaintParamsPtr_, Dimension());
        return focusPaintParamsPtr_->GetFocusPadding();
    }
    void SetPaintRect(const RoundRect& rect)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::unique_ptr<FocusPaintParam>();
        }
        focusPaintParamsPtr_->SetPaintRect(rect);
    }
    void SetPaintColor(const Color& color)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::unique_ptr<FocusPaintParam>();
        }
        focusPaintParamsPtr_->SetPaintColor(color);
    }
    void SetPaintWidth(const Dimension& width)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::unique_ptr<FocusPaintParam>();
        }
        focusPaintParamsPtr_->SetPaintWidth(width);
    }
    void SetFocusPadding(const Dimension& padding)
    {
        if (!focusPaintParamsPtr_) {
            focusPaintParamsPtr_ = std::unique_ptr<FocusPaintParam>();
        }
        focusPaintParamsPtr_->SetFocusPadding(padding);
    }

    RefPtr<FrameNode> GetFrameNode() const;
    RefPtr<GeometryNode> GetGeometryNode() const;
    RefPtr<FocusHub> GetParentFocusHub() const;
    std::string GetFrameName() const;
    int32_t GetFrameId() const;

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool RequestFocusImmediately(bool isWholePathFocusable = false);
    void RequestFocus() const;
    void RequestFocusWithDefaultFocusFirstly() const;
    void UpdateAccessibilityFocusInfo();
    void SwitchFocus(const RefPtr<FocusHub>& focusNode);

    void LostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH);
    void LostSelfFocus();
    void RemoveSelf();
    void RemoveChild(const RefPtr<FocusHub>& focusNode);
    bool GoToNextFocusLinear(FocusStep step, const RectF& rect = RectF());
    bool TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect, FocusStep step = FocusStep::NONE);

    void CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes);
    bool GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx);
    bool HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusHub>& mainFocusHub);
    RefPtr<FocusHub> GetChildFocusNodeByType(FocusNodeType nodeType = FocusNodeType::DEFAULT);
    RefPtr<FocusHub> GetChildFocusNodeById(const std::string& id);
    void HandleParentScroll() const;
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
        LOGD("Set node: %{public}s/%{public}d parentFocusable from %{public}d to %{public}d", GetFrameName().c_str(),
            GetFrameId(), parentFocusable_, parentFocusable);
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

    bool IsShow() const;

    bool IsEnabled() const;

    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }
    bool IsCurrentFocusWholePath();

    void MarkRootFocusNeedUpdate();

    void ClearUserOnFocus()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->ClearOnFocusCallback();
        }
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

    void ClearUserOnBlur()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->ClearOnBlurCallback();
        }
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

    void ClearUserOnKey()
    {
        if (focusCallbackEvents_) {
            focusCallbackEvents_->ClearOnKeyEventCallback();
        }
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

    std::list<RefPtr<FocusHub>>::iterator FlushChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes);

    std::list<RefPtr<FocusHub>> GetChildren()
    {
        std::list<RefPtr<FocusHub>> focusNodes;
        FlushChildrenFocusHub(focusNodes);
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
    void SetIsDefaultFocus(bool isDefaultFocus);

    bool IsDefaultGroupFocus() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsDefaultGroupFocus() : false;
    }
    void SetIsDefaultGroupFocus(bool isDefaultGroupFocus);

    WeakPtr<FocusHub> GetDefaultFocusNode() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->GetDefaultFocusNode() : nullptr;
    }
    void SetDefaultFocusNode(const WeakPtr<FocusHub>& node)
    {
        if (!focusCallbackEvents_) {
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
        }
        focusCallbackEvents_->SetDefaultFocusNode(node);
    }

    std::optional<bool> IsFocusOnTouch() const
    {
        return focusCallbackEvents_ ? focusCallbackEvents_->IsFocusOnTouch() : std::nullopt;
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

    bool PaintFocusState(bool isNeedStateStyles = true);
    bool PaintAllFocusState();
    bool PaintInnerFocusState(const RoundRect& paintRect);
    void ClearFocusState(bool isNeedStateStyles = true);
    void ClearAllFocusState();

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

    static inline bool IsFocusStepVertical(FocusStep step)
    {
        return (static_cast<uint32_t>(step) & 0x1) == 0;
    }

    static inline bool IsFocusStepForward(FocusStep step)
    {
        return (static_cast<uint32_t>(step) & MASK_FOCUS_STEP_FORWARD) != 0;
    }

    static inline bool IsFocusStepTab(FocusStep step)
    {
        return (static_cast<uint32_t>(step) & MASK_FOCUS_STEP_TAB) == MASK_FOCUS_STEP_TAB;
    }

    static double GetProjectAreaOnRect(const RectF& rect, const RectF& projectRect, FocusStep step);

protected:
    bool OnKeyEvent(const KeyEvent& keyEvent);
    bool OnKeyEventNode(const KeyEvent& keyEvent);
    bool OnKeyEventScope(const KeyEvent& keyEvent);

    bool AcceptFocusOfSpecifyChild(FocusStep step);
    bool AcceptFocusOfLastFocus();
    bool AcceptFocusByRectOfLastFocus(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusNode(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusScope(const RectF& rect);
    bool AcceptFocusByRectOfLastFocusFlex(const RectF& rect);

    bool CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const;
    bool RequestNextFocus(FocusStep moveStep, const RectF& rect);
    bool FocusToHeadOrTailChild(bool isHead);

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

    void SetScopeFocusAlgorithm();

    void SetLastFocusNodeIndex(const RefPtr<FocusHub>& focusNode);

    void ScrollToLastFocusIndex() const;

    void CheckFocusStateStyle(bool onFocus);

    bool IsNeedPaintFocusState();

    RefPtr<FocusHub> GetNearestNodeByProjectArea(const std::list<RefPtr<FocusHub>>& allNodes, FocusStep step);

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

    bool focusable_ { true };
    bool parentFocusable_ { true };
    bool currentFocus_ { false };
    bool isFirstFocusInPage_ { true };

    FocusType focusType_ = FocusType::DISABLE;
    FocusStyleType focusStyleType_ = FocusStyleType::NONE;
    std::unique_ptr<FocusPaintParam> focusPaintParamsPtr_;
    std::function<void(RoundRect&)> getInnerFocusRectFunc_;

    RectF rectFromOrigin_;
    ScopeFocusAlgorithm focusAlgorithm_;
    BlurReason blurReason_ = BlurReason::FOCUS_SWITCH;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H
