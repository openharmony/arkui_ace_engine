/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H

#include <cstdint>
#include <memory>

#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

enum class FrameNodeType {
    SELECTMENU,
    EXTENSIONMENU,
    BACKBUTTON
};

enum class FrameNodeStatus {
    VISIBLE,
    VISIBLETOGONE,
    GONE,
    GONETOVISIBLE
};

enum class FrameNodeTrigger {
    SHOW,
    SHOWN,
    HIDE,
    HIDDEN
};

class ACE_EXPORT SelectOverlayNode : public FrameNode {
    DECLARE_ACE_TYPE(SelectOverlayNode, FrameNode)
public:
    explicit SelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info);
    ~SelectOverlayNode() override = default;

    static RefPtr<FrameNode> CreateSelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info);
    RefPtr<FrameNode> CreateMoreSelectOverlayNode(const std::vector<MenuOptionsParam>& menuOptionItems, int32_t index);

    void UpdateToolBar(bool menuItemChanged);

    void SetSelectInfo(const std::string& selectInfo)
    {
        selectInfo_ = selectInfo;
    }

    const std::string& GetSelectInfo() const
    {
        return selectInfo_;
    }

    void ChangeToolBar(bool isUseExtensionMenu);

    void MoreOrBackAnimation(bool isMore);

    bool IsInSelectedOrSelectOverlayArea(const PointF& point);

    void SetClosedByGlobalEvent(bool closedByGlobalEvent);

    bool GetAnimationStatus()
    {
        return isDoingAnimation_;
    }

    bool GetIsExtensionMenu()
    {
        return isExtensionMenu_;
    }

    void ShowSelectOverlay(bool animation);

    void HideSelectOverlay(const std::function<void()>& callback);

private:
    void CreateToolBar();
    bool AddSystemDefaultOptions(float maxWidth, float& allocatedSize);
    void AddExtensionMenuOptions(const std::vector<MenuOptionsParam>& menuOptionItems, int32_t index);
    void GetDefaultButtonAndMenuWidth(float& maxWidth);

    void MoreAnimation();
    void BackAnimation();

    void DispatchVisibleState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchVisibleToGoneState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchGoneState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchGoneToVisibleState(FrameNodeType type, FrameNodeTrigger trigger);
    void ExecuteOverlayStatus(FrameNodeType type, FrameNodeTrigger trigger);
    void SetFrameNodeStatus(FrameNodeType type, FrameNodeStatus status);
    void SetFrameNodeVisibility(FrameNodeType type, VisibleType visibleType);
    void SetFrameNodeOpacity(FrameNodeType type, float opacity);
    void SetSelectMenuOpacity(float value);
    void SetExtensionMenuOpacity(float value);
    void SetBackButtonOpacity(float value);

    void SetAnimationStatus(bool toDoAnimation)
    {
        isDoingAnimation_ = toDoAnimation;
    }

    static RefPtr<FrameNode> CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info);

    using ExecuteStateFunc = void (SelectOverlayNode::*)(FrameNodeType type, FrameNodeTrigger trigger);

    /* Text selection menu node structure.
        -rootNode
            -selectOverlay
                -selectMenu_
                    -selectMenuInner_
                -backButton_
                -extensionMenu_
       Attention:
        If the user-defined selection menu is bound by bindSelectionMenu, there will be only the selectMenu_.
        Then, selectMenuInner_, backButton_, extensionMenu_ will be null.
        Text selection menu node structure whill be like bellow:
        -rootNode
            -selectOverlay(menuWrapper)
                -selectMenu_(menu)
                    -scroller
                        -customBuilderMenu
    */
    RefPtr<FrameNode> selectMenu_;
    RefPtr<FrameNode> selectMenuInner_;
    RefPtr<FrameNode> extensionMenu_;
    RefPtr<FrameNode> backButton_;

    FrameNodeStatus selectMenuStatus_ = FrameNodeStatus::VISIBLE;
    FrameNodeStatus extensionMenuStatus_ = FrameNodeStatus::GONE;
    FrameNodeStatus backButtonStatus_ = FrameNodeStatus::GONE;

    std::map<FrameNodeStatus, ExecuteStateFunc> stateFuncs_;

    std::string selectInfo_;

    // Marks whether it is currently in the animated state.
    bool isDoingAnimation_ = false;

    // Controls that only default menus can be converted to extended menus, and extended menus can be converted to
    // default menus.
    bool isExtensionMenu_ = false;

    // Label whether the menu default button needs to appear within the extended menu
    bool isShowInDefaultMenu_[7] = { false };

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H
