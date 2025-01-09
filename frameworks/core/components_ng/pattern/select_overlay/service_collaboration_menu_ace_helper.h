/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SERVICE_COLLABORATION_MENU_ACE_HELPER
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SERVICE_COLLABORATION_MENU_ACE_HELPER

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/pipeline/pipeline_base.h"
namespace OHOS::Ace::NG {

enum ServiceCollaborationCode {
    SEND_PHOTO_SUCCESS = 1001202000,
    REMOTE_CANCEL = 1001202001,
    PHOTO_SENDING = 1001202006,
    MULTI_PHOTO_SENDING_BACK = 1001202007,
    PROCES_PREPARE = 1001202010,
};

class FrameNode;
struct SelectOverlayInfo;
class ACE_FORCE_EXPORT ServiceCollaborationMenuAceHelper : public virtual AceType {
    DECLARE_ACE_TYPE(ServiceCollaborationMenuAceHelper, AceType);
public:
    void CreateText(const std::string& value, const RefPtr<FrameNode>& parent, const Color& color,
        bool needMargin, bool hasEndIncon);
    void CreateHeaderText(const std::string& value, const RefPtr<FrameNode>& row,
        const RefPtr<FrameNode>& menuItemGroupNode);
    void CreateEndIcon(uint32_t iconId, const RefPtr<FrameNode>& parent);
    void CreateStartIcon(uint32_t iconId, const RefPtr<FrameNode>& parent);
    uint32_t GetSymbolId(const std::string& abilityType);
    RefPtr<FrameNode> CreateMainMenuItem(
        const std::string& value, const std::string& iconType, const Color& color, bool needEndIcon);
    RefPtr<FrameNode> CreateMainMenuItem(
        const std::string& value, uint32_t iconId, const Color& color, bool needEndIcon);
    RefPtr<FrameNode> CreateDeviceMenuItem(const std::string& value, uint32_t iconId);
    void RemoveSubmenu(const RefPtr<FrameNode>& menuWrapper);
    void SubMenuDown(const RefPtr<FrameNode>& menuWrapper);
    RefPtr<FrameNode> CreateMenuItemGroupNode(uint32_t index, const std::string& deviceName);
    RefPtr<FrameNode> CreateMenuNode();
    RefPtr<FrameNode> CreateSubDeviceOutMenu(const RefPtr<FrameNode>& column, const RefPtr<FrameNode>& menuWrapper);
    void SubMeunMountToMainMenu(const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
        std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator);
    void AddHoverEventToMainMenu(const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
        std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator);
    void AddClickEventToMainMenu(const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
        std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator);
    

    bool subMenuIsHover_ = false;
    bool subMenuIsShow_ = false;
    bool mainMenuIsHover_ = false;
    uint32_t photoCount_ = 0;
private:
    static constexpr int32_t TEXT_RIGHT_MARGIN = 8;
    static constexpr int32_t TEXT_RIGHT_MARGIN_NO_ENDICON = 12;
    static constexpr int32_t TEXT_LEFT_MARGIN = 0;
    static constexpr int32_t HEADER_MIN_WIDTH = 64;
    static constexpr int32_t HEADER_MIN_HEIGHT = 24;
    static constexpr int32_t HEADER_MARGIN_TOP = 26;
    static constexpr int32_t HEADER_MARGIN_BOTTOM = 16;
    static constexpr int32_t HEADER_MARGIN_LEFT = 0;
    static constexpr int32_t HEADER_MARGIN_RIGHT = 0;
    static constexpr int32_t ENDICON_MARGIN_RIGHT = -16;
    static constexpr int32_t PANDDING_ZERO = 0;
    static constexpr int32_t BORDER_MARGIN_TOP = 4;
    static constexpr int32_t BORDER_WIDTH = 1;
    static constexpr int32_t MENUITEM_WIDTH = 224;
    static constexpr int32_t MENUITEM_HEIGHT = 60;
    static constexpr int32_t MENUITEM_MARGIN = 2;
    static constexpr int32_t ROW_PADDING = 2;
    static constexpr int32_t GROUP_MIN_WIDTH = 64;
    static constexpr int32_t GROUP_MARGIN = 12;
    static constexpr int32_t MAIN_MENUGROUP_INDEX = 5;
    static constexpr int32_t SUB_MENU_ID = -2;
    static constexpr int32_t INNER_MENU_ID = -3;
    static constexpr uint32_t ENDICON_COLOR = 0x33000000;
    static constexpr uint32_t BORDER_COLOR = 0x33000000;
    static constexpr uint32_t HEADER_COLOR = 0x99000000;
    static constexpr uint32_t INDEX_ONE = 1;
    static constexpr uint32_t INDEX_TWO = 2;
    static constexpr uint32_t INDEX_THREE = 3;
    static constexpr uint32_t HEADER_TEXT_MAX_LINE = 2;
    static constexpr int32_t HEADER_TEXT_FONT_SIZE = 14;
    static constexpr char SUN_MENU_TAG[33] = "SelectOverlayMenuByRightClickSub";
};

class ACE_FORCE_EXPORT ServiceCollaborationAceCallback : public virtual AceType {
    DECLARE_ACE_TYPE(ServiceCollaborationAceCallback, AceType);
public:
    RefPtr<FrameNode> CreateCustomPopUpNode(const std::string& value, const std::string& icon);
    void CreateText(const std::string& value, const RefPtr<FrameNode>& parent);
    void CreateEndIcon(const std::string& icon, const RefPtr<FrameNode>& parent);
    void CreateStartIcon(uint32_t iconId, const RefPtr<FrameNode>& parent);
    RefPtr<PopupParam> GetPopupParam(bool isShow, StateChangeFunc& stateChangeFunc);
    void RemovePopupNode();
    int32_t OnEvent(uint32_t code, uint32_t eventId, std::string &category, StateChangeFunc& onStateChange_);
    int32_t OnDataCallback(uint32_t code, uint32_t collaborationId,
        uint32_t dataLength, std::unique_ptr<char[]>& data);
    RefPtr<PixelMap> CreatePixelMap(void *buffer, uint32_t code, uint32_t dataLength);
    void AddMouseEventToEndIcon(const RefPtr<FrameNode>& iconNode);
    uint32_t GetSymbolId(const std::string& abilityType);
    void SetMenuHelper(RefPtr<ServiceCollaborationMenuAceHelper> menuHelper)
    {
        menuHelper_ = menuHelper;
    }

    void SetRichEditor(const std::shared_ptr<SelectOverlayInfo>& info)
    {
        info_ = info;
    }

    void SetAbility(const std::string& ability)
    {
        ability_ = ability;
    }

    OffsetF position_;
    RefPtr<FrameNode> row_;
    bool isTransmit_;
    RefPtr<ServiceCollaborationMenuAceHelper> menuHelper_;
    std::shared_ptr<SelectOverlayInfo> info_;
    std::string ability_;
    bool endIconIsHover_ = false;
    bool isMultiImage_ = false;

private:
    static constexpr int32_t TEXT_MAX_WIDTH = 500;
    static constexpr int32_t TEXT_MAX_HIGHT = 456;
    static constexpr int32_t TEXT_FONT_SIZE = 14;
    static constexpr int32_t TEXT_MARGIN_TOP = 14;
    static constexpr int32_t TEXT_MARGIN_BOTTOM = 12;
    static constexpr int32_t ENDICON_SIZE = 36;
    static constexpr int32_t ENDICON_MARGIN = 12;
    static constexpr int32_t ENDICON_MARGIN_FIVE = 5;
    static constexpr int32_t ENDICON_MARGIN_THREE = 3;
    static constexpr int32_t ENDICON_MARGIN_TOP = 13;
    static constexpr int32_t STARTICON_SIZE = 24;
    static constexpr int32_t STARTICON_MARGIN = 12;
    static constexpr int32_t TARGET_SPACE = 8;
    static constexpr int32_t ICON_BORDER_RADIUS = 18;
    static constexpr int32_t ICON_PADDING = 7;
    static constexpr uint32_t ICON_COLOR = 0x99000000;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SERVICE_COLLABORATION_MENU_ACE_HELPER