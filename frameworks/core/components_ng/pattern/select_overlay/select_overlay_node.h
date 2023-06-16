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

private:
    void CreateToolBar();
    bool AddSystemDefaultOptions(float maxWidth, float& allocatedSize);
    void AddExtensionMenuOptions(const std::vector<MenuOptionsParam>& menuOptionItems, int32_t index);
    void GetDefaultButtonAndMenuWidth(float& maxWidth);

    void MoreAnimation();
    void BackAnimation();

    void SetAnimationStatus(bool toDoAnimation)
    {
        isDoingAnimation_ = toDoAnimation;
    }

    static RefPtr<FrameNode> CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info);

    /* Text selection menu node structure.
        -rootNode
            -selectOverlay
                -selectMenu_
                    -selectMenuInner_
                -backButton_
                -extensionMenu_
    */
    RefPtr<FrameNode> selectMenu_;
    RefPtr<FrameNode> selectMenuInner_;
    RefPtr<FrameNode> extensionMenu_;
    RefPtr<FrameNode> backButton_;

    std::string selectInfo_;

    // Marks whether it is currently in the animated state.
    bool isDoingAnimation_ = false;

    // Controls that only default menus can be converted to extended menus, and extended menus can be converted to
    // default menus.
    bool isExtensionMenu_ = false;

    // Label whether the menu default button needs to appear within the extended menu
    bool isShowInDefaultMenu_[7] = { true };

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H
