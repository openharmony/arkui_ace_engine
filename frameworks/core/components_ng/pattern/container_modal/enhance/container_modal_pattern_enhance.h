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

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalPatternEnhance : public ContainerModalPattern {
    DECLARE_ACE_TYPE(ContainerModalPatternEnhance, ContainerModalPattern);

public:
    ContainerModalPatternEnhance() = default;
    ~ContainerModalPatternEnhance() override = default;
    void OnWindowFocused() override;
    void OnWindowUnfocused() override;
    void OnWindowForceUnfocused() override;
    void UpdateTitleInTargetPos(bool isShow, int32_t height);
    void ShowTitle(bool isShow, bool hasDeco = true, bool needUpdate = false) override;
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&) override;
    RefPtr<FrameNode> GetOrCreateMenuList(const RefPtr<FrameNode>& targetNode);
    /* event */
    void SetTapGestureEvent(RefPtr<FrameNode>& gestureRow);
    RefPtr<FrameNode> ShowMaxMenu(const RefPtr<FrameNode>& targetNode);
    void OnMaxButtonClick(GestureEvent& info);
    void OnMinButtonClick(GestureEvent& info);
    void OnCloseButtonClick(GestureEvent& info);
    void OnMaxBtnGestureEvent(RefPtr<FrameNode>& maximizeBtn);
    void OnMaxBtnInputEvent(MouseInfo& info);
    void OnMaxBtnHoverEvent(bool hover, WeakPtr<FrameNode>& maximizeBtn);
    void OnMenuItemClickGesture(bool isSplistLeft);
    static void OnMenuItemHoverEvent(RefPtr<FrameNode> item, bool isHover);
    static void OnMenuItemClickEvent(RefPtr<FrameNode> item, MouseInfo& info);

private:
    RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex) override;
    void ChangeFloatingTitle(bool isFocus) override;
    void ChangeCustomTitle(bool isFocus) override;
    void ChangeControlButtons(bool isFocus) override;
    void AddPointLight();
    void SetPointLight(RefPtr<FrameNode>& containerTitleRow, RefPtr<FrameNode>& maximizeBtn,
        RefPtr<FrameNode>& minimizeBtn, RefPtr<FrameNode>& closeBtn);
    void UpdateLightColor();
    void UpdateLightIntensity();
    RefPtr<FrameNode> ShowMaxMenu(RefPtr<FrameNode>& container, const RefPtr<FrameNode>& targetNode);
    void ResetHoverTimer();
    Dimension GetMenuWidth();
    void CalculateMenuOffset(const RefPtr<FrameNode>& targetNode);

    VisibleType controlButtonVisibleBeforeAnim_;
    RefPtr<RenderContext> closeBtnRenderContext_;
    bool isTitleRowHovered_;
    RefPtr<FrameNode> menuList_;
    OffsetF menuOffset_;
    float textWidth_ = 0.0f;
    bool isMenuPending_ = false;
    bool isForbidMenuEvent_ = false;
    bool enableSplit_ = true;
    CancelableCallback<void()> contextTimer_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_ENHANCE_H
