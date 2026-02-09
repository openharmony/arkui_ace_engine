/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_INNER_MODIFIER_H

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

enum class MenuPreviewMode;
namespace OHOS::Ace {
struct SelectParam;
class AnimationOption;
class Dimension;
class DimensionOffset;
enum class MenuAlignType;
enum class AvoidanceMode;
class AceType;
template<typename T>
class RefPtr;
template<typename T>
class WeakPtr;
enum class Placement;
class ResourceObject;
struct SelectParam;
enum class DividerMode;
class Color;
class Alignment;
namespace V2 {
struct ItemDivider;
}
namespace NG {
enum class MenuType;
struct MenuParam;
class MenuLayoutProperty;
class FrameNode;
class UINode;
enum class HideMenuType;
class MenuItemConfiguration;
class Pattern;
class FrameNode;
struct MenuPathParams;
enum class SubMenuExpandingMode;
enum class MenuType;
template<typename T>
class SizeT;
using SizeF = SizeT<float>;
template<typename T>
class OffsetT;
using OffsetF = OffsetT<float>;
using SelectMakeCallback = std::function<RefPtr<FrameNode>(const MenuItemConfiguration menuItemConfiguration)>;

struct ArkUIMenuInnerModifier {
    // MenuPattern
    bool (*isMenuPattern)(const RefPtr<NG::Pattern>& pattern);
    bool (*isContextMenu)(const RefPtr<FrameNode>& node);
    MenuPreviewMode (*getPreviewMode)(const RefPtr<FrameNode>& node);
    bool (*isSelectMenu)(const RefPtr<FrameNode>& node);
    void (*hideMenu)(const RefPtr<FrameNode>& node, const HideMenuType& reason);
    bool (*getDisappearAnimation)(const RefPtr<FrameNode>& node);
    std::string (*getTargetTag)(const RefPtr<FrameNode>& node);
    int32_t (*getTargetId)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getShowedSubMenu)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getFirstInnerMenu)(const RefPtr<FrameNode>& node);
    int32_t (*getSubMenuDepth)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getParentMenuItem)(const RefPtr<FrameNode>& node);
    void (*removeParentHoverStyle)(const RefPtr<FrameNode>& node);
    void (*setShowedSubMenu)(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& subMenu);
    bool (*isSubMenu)(const RefPtr<FrameNode>& node);
    bool (*isSelectOverlaySubMenu)(const RefPtr<FrameNode>& node);
    void (*setDisappearAnimation)(const RefPtr<FrameNode>& node, bool hasAnimation);
    bool (*isSelectOverlayCustomMenu)(const RefPtr<FrameNode>& node);
    bool (*isSelectOverlayRightClickMenu)(const RefPtr<FrameNode>& node);
    RefPtr<MenuLayoutProperty> (*getLayoutProperty)(const RefPtr<FrameNode>& node);
    void (*focusViewShow)(const RefPtr<FrameNode>& node, bool isTriggerByStep);
    void (*showStackMenuDisappearAnimation)(
        const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& subMenuNode, AnimationOption& option);
    void (*setSubMenuShow)(const RefPtr<FrameNode>& node, bool subMenuShowed);
    void (*setCustomNode)(const RefPtr<FrameNode>& node, WeakPtr<UINode> customNode);
    std::vector<RefPtr<FrameNode>>& (*getEmbeddedMenuItems)(const RefPtr<FrameNode>& node);
    bool (*getIsShowHoverImage)(const RefPtr<FrameNode>& node);
    float (*getPreviewBeforeAnimationScale)(const RefPtr<FrameNode>& node);
    float (*getPreviewAfterAnimationScale)(const RefPtr<FrameNode>& node);
    std::optional<Placement> (*getLastPlacement)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*duplicateMenuNode)(
        const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    void (*removeResObj)(const RefPtr<FrameNode>& node, const std::string& key);
    std::string (*getResCacheMapByKey)(const RefPtr<FrameNode>& node, const std::string& key);
    void (*addResCache)(const RefPtr<FrameNode>& node, const std::string& key, const std::string& value);
    void (*addResObj)(const RefPtr<FrameNode>& node, const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);
    std::optional<MenuPathParams> (*getMenuPathParams)(const RefPtr<FrameNode>& node);
    void (*setIsSelectMenu)(const RefPtr<FrameNode>& node, bool isSelectMenu);
    void (*setDisableMenuBgColorByUser)(const RefPtr<FrameNode>& node, bool ret);
    void (*updateSelectParam)(const RefPtr<FrameNode>& node, const std::vector<SelectParam>& params);
    const std::vector<RefPtr<FrameNode>>& (*getOptions)(const RefPtr<FrameNode>& node);
    void (*setSelectProperties)(const RefPtr<FrameNode>& node, const std::vector<SelectParam>& params);
    void (*setBuilderFunc)(const RefPtr<FrameNode>& node, SelectMakeCallback&& makeFunc);
    void (*resetBuilderFunc)(const RefPtr<FrameNode>& node);
    void (*updateSelectIndex)(const RefPtr<FrameNode>& node, int32_t index);
    void (*updateSelectOptionTextByIndex)(const RefPtr<FrameNode>& node, int32_t index, const std::string& text);
    void (*updateSelectOptionIconByIndex)(const RefPtr<FrameNode>& node, int32_t index, const std::string& icon);
    void (*setIsWidthModifiedBySelect)(const RefPtr<FrameNode>& node, bool isModified);
    void (*setHasOptionWidth)(const RefPtr<FrameNode>& node, bool hasOptionWidth);
    void (*setIsHeightModifiedBySelect)(const RefPtr<FrameNode>& node, bool isModified);
    void (*updateMenuItemDivider)(const RefPtr<FrameNode>& node);
    void (*addMenuItemNode)(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& menuItem);
    void (*hideAllEmbeddedMenuItems)(const RefPtr<FrameNode>& node, bool isNeedAnimation);
    void (*setMenuShow)(const RefPtr<FrameNode>& node);
    void (*showMenuDisappearAnimation)(const RefPtr<FrameNode>& node);
    const std::vector<RefPtr<FrameNode>>& (*getMenuItems)(const RefPtr<FrameNode>& node);
    void (*setSelectOverlayExtensionMenuShow)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getOrCreateMenuNode)(const std::string& nodeTag, int32_t nodeId, const std::string& patternTag,
        int32_t patternId, MenuType menuType);
    void (*setParentMenuItem)(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& parentMenuItem);

    // MenuPreviewPattern
    float (*getHoverImageAfterScaleWidth)(const RefPtr<FrameNode>& node);
    float (*getHoverImageAfterScaleHeight)(const RefPtr<FrameNode>& node);
    float (*getStackAfterScaleActualWidth)(const RefPtr<FrameNode>& node);
    float (*getStackAfterScaleActualHeight)(const RefPtr<FrameNode>& node);

    // MenuLayoutProperty
    void (*updateMenuOffset)(const RefPtr<FrameNode>& node, const OHOS::Ace::NG::OffsetF& value);
    void (*resetMenuPlacement)(const RefPtr<FrameNode>& node);
    std::optional<SubMenuExpandingMode> (*getExpandingMode)(const RefPtr<FrameNode>& node);
    void (*updateTargetSize)(const RefPtr<FrameNode>& node, const OHOS::Ace::NG::SizeF& value);
    void (*updateShowInSubWindow)(const RefPtr<FrameNode>& node, const bool& value);
    void (*updateShowDefaultSelectedIcon)(const RefPtr<FrameNode>& node, const bool& value);
    void (*resetShowDefaultSelectedIcon)(const RefPtr<FrameNode>& node);
    float (*getSelectModifiedHeightValue)(const RefPtr<FrameNode>& node, const float& value);
    std::optional<DividerMode> (*getItemDividerMode)(const RefPtr<FrameNode>& node);
    void (*updateSelectMenuModifiedWidth)(const RefPtr<FrameNode>& node, const float& value);
    void (*updateAlignType)(const RefPtr<FrameNode>& node, const MenuAlignType& value);
    void (*updateOffset)(const RefPtr<FrameNode>& node, const DimensionOffset& value);
    void (*updateSelectAvoidanceMode)(const RefPtr<FrameNode>& node, const AvoidanceMode& value);
    void (*updateSelectModifiedHeight)(const RefPtr<FrameNode>& node, const float& value);
    void (*updateItemDividerMode)(const RefPtr<FrameNode>& node, const DividerMode& value);
    void (*resetItemDividerMode)(const RefPtr<FrameNode>& node);
    void (*updateExpandingMode)(const RefPtr<FrameNode>& node, const SubMenuExpandingMode& value);
    void (*updateMenuWidth)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*updateAlignment)(const RefPtr<FrameNode>& node, const OHOS::Ace::Alignment& value);

    // MenuAccessibilityProperty
    void (*setAccessibilityIsShow)(const RefPtr<FrameNode>& node, bool isShow);

    // MenuModelNG
    void (*setWidth)(FrameNode* frameNode, const Dimension& width);
    void (*setExpandingMode)(FrameNode* frameNode, const SubMenuExpandingMode& expandingMode);
    void (*setItemDivider)(FrameNode* frameNode, const V2::ItemDivider& divider, const DividerMode& mode);
    RefPtr<FrameNode> (*createMenu)();
    RefPtr<FrameNode> (*menuCreateFrameNode)(int32_t innerMenuId, int32_t nodeId);
    void (*menuSetNeedDivider)(const RefPtr<FrameNode>& node);
    void (*menuOnModifyDone)(const RefPtr<FrameNode>& node);
};

namespace InnerModifier {
const ArkUIMenuInnerModifier* GetMenuInnerModifier();
} // namespace InnerModifier
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_INNER_MODIFIER_H