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

#include "core/components_ng/base/geometry_node.h"
#include "core/event/key_event.h"

namespace OHOS::Ace::NG {

class FrameNode;
class FocusHub;
class ClickInfo;
class EventHub;

using TabIndexNodeList = std::list<std::pair<int32_t, WeakPtr<FocusHub>>>;
constexpr int32_t DEFAULT_TAB_FOCUSED_INDEX = -2;
constexpr int32_t NONE_TAB_FOCUSED_INDEX = -1;
enum class FocusType : int32_t {
    DISABLE = 0,
    NODE = 1,
    SCOPE = 2,
};

class ACE_EXPORT FocusHub : public Referenced {
public:
    explicit FocusHub(const WeakPtr<EventHub>& eventHub, FocusType type = FocusType::DISABLE)
        : eventHub_(eventHub), focusType_(type)
    {}
    ~FocusHub() override = default;

    RefPtr<FrameNode> GetFrameNode() const;
    RefPtr<GeometryNode> GetGeometryNode() const;
    RefPtr<FocusHub> GetParentFocusHub() const;
    std::string GetFrameName() const;

    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool RequestFocusImmediately();
    void UpdateAccessibilityFocusInfo();
    void SwitchFocus(const RefPtr<FocusHub>& focusNode);

    void LostFocus();
    bool GoToNextFocus(bool reverse, const RectF& rect = RectF());
    bool TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect);

    bool AcceptFocusByRectOfLastFocus(const RectF& rect);

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

    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }

    void SetOnFocusCallback(OnFocusFunc&& onFocusCallback)
    {
        onFocusCallback_ = std::move(onFocusCallback);
    }
    void SetOnBlurCallback(OnBlurFunc&& onBlurCallback)
    {
        onBlurCallback_ = std::move(onBlurCallback);
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
    void SetOnKeyEventInternal(HandleKeyEventFunc&& onKeyEventInternal)
    {
        handleKeyEvent_ = std::move(onKeyEventInternal);
    }
    void SetOnKeyCallback(OnKeyCallbackFunc&& onKeyCallback)
    {
        onKeyEventCallback_ = std::move(onKeyCallback);
    }
    void SetOnClickCallback(std::function<void(const std::shared_ptr<ClickInfo>&)>&& onClickCallback)
    {
        onClickEventCallback_ = std::move(onClickCallback);
    }

    void FlushChildrenFocusHub();

    void GetChildren(std::list<RefPtr<FocusHub>>& children) const;

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
        OnFocus();
    }

private:
    bool CalculatePosition();

    WeakPtr<FocusHub> parent_;

    OnFocusFunc onFocusCallback_;
    OnFocusFunc onFocusInternal_;

    OnBlurFunc onBlurCallback_;
    OnBlurFunc onBlurInternal_;

    OnKeyCallbackFunc onKeyEventCallback_;
    HandleKeyEventFunc handleKeyEvent_;

    OnPreFocusFunc onPreFocusCallback_;

    std::function<void(std::shared_ptr<ClickInfo>&)> onClickEventCallback_;

    WeakPtr<EventHub> eventHub_;

    std::list<RefPtr<FocusHub>> focusNodes_;
    std::list<RefPtr<FocusHub>>::iterator itLastFocusNode_ { focusNodes_.end() };
    WeakPtr<FocusHub> lastWeakFocusNode_ { nullptr };

    bool focusable_ { true };
    bool parentFocusable_ { true };
    bool currentFocus_ { false };

    FocusType focusType_ = FocusType::DISABLE;
    RectF rectFromOrigin_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HUB_H
