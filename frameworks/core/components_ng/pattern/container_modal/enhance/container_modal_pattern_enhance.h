/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H

#include <functional>
#include <unordered_map>

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/base/inspector.h"

namespace OHOS::Ace::NG {
using ButtonsRectChangeListener = std::function<void(const RectF& containerModal, const RectF& buttonsRect)>;

class ACE_EXPORT ContainerModalPatternEnhance : public ContainerModalPattern {
    DECLARE_ACE_TYPE(ContainerModalPatternEnhance, ContainerModalPattern);

public:
    ContainerModalPatternEnhance() = default;
    ~ContainerModalPatternEnhance() override = default;
    void OnWindowForceUnfocused() override;
    void UpdateTitleInTargetPos(bool isShow, int32_t height);
    void ShowTitle(bool isShow, bool hasDeco = true, bool needUpdate = false) override;
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&) override;
    void EnableContainerModalGesture(bool isEnable) override;
    void CallContainerModalNative(const std::string& name, const std::string& value) override;
    void OnContainerModalEvent(const std::string& name, const std::string& value) override;
    void ClearTapGestureEvent(RefPtr<FrameNode>& containerTitleRow);
    RefPtr<FrameNode> GetOrCreateMenuList(const RefPtr<FrameNode>& targetNode);
    /* event */
    void SetTapGestureEvent(RefPtr<FrameNode>& gestureRow);
    RefPtr<FrameNode> ShowMaxMenu(const RefPtr<FrameNode>& targetNode);
    void OnMaxButtonClick(GestureEvent& info);
    void OnMinButtonClick(GestureEvent& info);
    void OnCloseButtonClick(GestureEvent& info);
    void OnMaxBtnInputEvent(MouseInfo& info);
    void OnMaxBtnHoverEvent(bool hover, WeakPtr<FrameNode>& maximizeBtn);
    void OnMenuItemClickGesture(bool isSplistLeft);
    static void OnMenuItemHoverEvent(RefPtr<FrameNode> item, bool isHover);
    static void OnMenuItemClickEvent(RefPtr<FrameNode> item, MouseInfo& info);
    void EnablePanEventOnNode(
        RefPtr<FrameNode>& node, bool isEnable, const std::string& rowName);
    void EnableTapGestureOnNode(
        RefPtr<FrameNode>& node, bool isEnable, const std::string& rowName);
    bool GetFloatingTitleVisible() override;
    bool GetCustomTitleVisible() override;
    bool GetControlButtonVisible() override;
    void OnColorConfigurationUpdate() override;

    void Init() override;
    void SetCloseButtonStatus(bool isEnabled) override;
    void InitButtonsLayoutProperty() override;
    CalcLength GetControlButtonRowWidth() override;
    bool GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons) override;
    bool GetContainerModalComponentRect(RectF& containerModal, RectF& buttons);
    void OnMaxButtonClick();
    void OnMinButtonClick();
    void OnCloseButtonClick();
    void AddPointLight();
    void CallMenuWidthChange(int32_t resId);
    int32_t AddButtonsRectChangeListener(ButtonsRectChangeListener&& listener);
    void RemoveButtonsRectChangeListener(int32_t id);

private:
    RefPtr<FrameNode> GetButtonRowByInspectorId()
    {
        return NG::Inspector::GetFrameNodeByKey("containerModalButtonRowId");
    }

    RefPtr<FrameNode> GetMaximizeButton()
    {
        return NG::Inspector::GetFrameNodeByKey("EnhanceMaximizeBtn");
    }

    RefPtr<FrameNode> GetMinimizeButton()
    {
        return NG::Inspector::GetFrameNodeByKey("EnhanceMinimizeBtn");
    }

    RefPtr<FrameNode> GetCloseButton()
    {
        return NG::Inspector::GetFrameNodeByKey("EnhanceCloseBtn");
    }
    RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex) override;
    void ChangeFloatingTitle(bool isFocus) override;
    void ChangeCustomTitle(bool isFocus) override;
    void ChangeControlButtons(bool isFocus) override;

    RefPtr<FrameNode> ShowMaxMenu(RefPtr<FrameNode>& container, const RefPtr<FrameNode>& targetNode);
    void ResetHoverTimer();
    Dimension GetMenuWidth();
    void CalculateMenuOffset(const RefPtr<FrameNode>& targetNode);
    void BuildMenuList();

    void SetColorConfigurationUpdate();
    void SetMaximizeIconIsRecover();
    void NotifyButtonsRectChange(const RectF& containerModal, const RectF& buttonsRect) override;

    VisibleType controlButtonVisibleBeforeAnim_;
    RefPtr<FrameNode> menuList_;
    OffsetF menuOffset_;
    float textWidth_ = 0.0f;
    bool isMenuPending_ = false;
    bool isForbidMenuEvent_ = false;
    bool enableSplit_ = true;
    CancelableCallback<void()> contextTimer_;
    bool enableContainerModalGesture_ = true;
    std::unordered_map<int32_t, ButtonsRectChangeListener> rectChangeListeners_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
