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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_INNER_MODIFIER_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace OHOS::Ace {
struct SelectParam;
class AceType;
class Color;
class Dimension;
template<typename T>
class RefPtr;
template<typename T>
class WeakPtr;
class ResourceObject;
class ImageSourceInfo;
enum class FontStyle;
enum class FontWeight;
enum class VisibleType;
namespace NG {
class FrameNode;
class Pattern;
class UINode;
class MenuLayoutProperty;
enum class SubMenuExpandingMode;
struct SelectDivider;
template<typename T>
class OffsetT;
template<typename T>
class PointT;
template<typename T>
class RectT;
struct OptionParam;
struct MenuParam;
class CalcLength;
template<typename T>
struct PaddingPropertyT;
using PaddingProperty = PaddingPropertyT<CalcLength>;
using OffsetF = OffsetT<float>;
using PointF = PointT<float>;
using RectF = RectT<float>;

struct ArkUIMenuItemInnerModifier {
    bool (*hasHideTask)(const RefPtr<FrameNode>& node);
    bool (*isAtomicNode)(const RefPtr<FrameNode>& node);
    bool (*isEnableMatchParent)(const RefPtr<FrameNode>& node);
    bool (*isEnableChildrenMatchParent)(const RefPtr<FrameNode>& node);
    bool (*isEnableFix)(const RefPtr<FrameNode>& node);
    bool (*markIsSelected)(const RefPtr<FrameNode>& node, bool isSelected);
    void (*setSelectedInt)(const RefPtr<FrameNode>& node, int32_t selected);
    void (*setSelectedBool)(const RefPtr<FrameNode>& node, bool isSelected);
    bool (*isSelected)(const RefPtr<FrameNode>& node);
    void (*setSubSelectMenuBuilder)(
        const RefPtr<FrameNode>& node, const std::function<RefPtr<UINode>()>& subBuilderFunc);
    std::function<RefPtr<UINode>()>& (*getSubSelectMenuBuilder)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*findTouchedEmbeddedMenuItem)(const RefPtr<UINode>& frameNode, PointF position);
    bool (*isDisabled)(const RefPtr<FrameNode>& frameNode);
    bool (*isStackSubmenuHeader)(const RefPtr<FrameNode>& frameNode);
    void (*notifyPressStatus)(const RefPtr<FrameNode>& frameNode, bool isPress);
    RefPtr<FrameNode> (*getMenu)(const RefPtr<FrameNode>& node, bool needTopMenu);
    bool (*setIsSubMenuShowed)(const RefPtr<FrameNode>& node, bool isSubMenuShowed);
    bool (*isInHoverRegions)(const RefPtr<FrameNode>& node, double x, double y);
    bool (*isSubMenuShowed)(const RefPtr<FrameNode>& node);
    void (*checkHideSubMenu)(
        const RefPtr<FrameNode>& node, std::function<void()> callback, const PointF& mousePoint, const RectF& menuZone);
    void (*cancelHideSubMenuTask)(const RefPtr<FrameNode>& node, const PointF& mousePoint);
    void (*setFontSize)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*setFontColor)(const RefPtr<FrameNode>& node, const Color& color, bool isNeedRecord);
    void (*setBgColor)(const RefPtr<FrameNode>& node, const Color& color);
    Color (*getBgColor)(const RefPtr<FrameNode>& node);
    void (*updateNextNodeDivider)(const RefPtr<FrameNode>& node, bool needDivider);
    bool (*isMenuItemPattern)(const RefPtr<Pattern>& pattern);
    bool (*hasMenuItemPattern)(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getTopDivider)(const RefPtr<FrameNode>& node);
    void (*hideEmbedded)(const RefPtr<FrameNode>& node, bool isNeedAnimation);
    SubMenuExpandingMode (*getExpandingMode)(const RefPtr<FrameNode>& node);
    void (*addHoverRegions)(
        const RefPtr<FrameNode>& node, const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint);
    void (*setIsWidthModifiedBySelect)(const RefPtr<FrameNode>& node, bool isModified);
    std::string (*getText)(const RefPtr<FrameNode>& node);
    void (*setItalicFontStyle)(const RefPtr<FrameNode>& node, const Ace::FontStyle& value);
    void (*setFontWeight)(const RefPtr<FrameNode>& node, const FontWeight& value);
    void (*setFontFamily)(const RefPtr<FrameNode>& node, const std::vector<std::string>& value);
    void (*setOptionFontColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*setShowDefaultSelectedIcon)(const RefPtr<FrameNode>& node, bool show);
    void (*setTextNode)(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& text);
    void (*setBlockClick)(const RefPtr<FrameNode>& node, bool blockClick);
    void (*setPasteButton)(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& pasteButton);
    RefPtr<FrameNode> (*getTextNode)(const RefPtr<FrameNode>& node);
    std::function<void(WeakPtr<NG::FrameNode>)>& (*getOptionTextModifier)(const RefPtr<FrameNode>& node);
    std::function<void(WeakPtr<NG::FrameNode>)>& (*getSelectedOptionTextModifier)(const RefPtr<FrameNode>& node);
    void (*setOptionTextModifier)(
        const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& optionApply);
    void (*resetSelectTextProps)(const RefPtr<FrameNode>& node);
    void (*applyOptionThemeStyles)(const RefPtr<FrameNode>& node);
    void (*setSelectedOptionTextModifier)(
        const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& optionSelectedApply);
    void (*applySelectedThemeStyles)(const RefPtr<FrameNode>& node);
    void (*setCheckMarkVisibleType)(const RefPtr<FrameNode>& node, VisibleType type);
    std::string (*inspectorGetFont)(const RefPtr<FrameNode>& node);
    Color (*getFontColor)(const RefPtr<FrameNode>& node);
    std::string (*getIcon)(const RefPtr<FrameNode>& node);
    void (*updateCheckMarkColor)(const RefPtr<FrameNode>& node, const Color& color);
    RefPtr<FrameNode> (*getBottomDivider)(const RefPtr<FrameNode>& node);
    void (*setHasOptionWidth)(const RefPtr<FrameNode>& node, bool hasOptionWidth);
    RefPtr<FrameNode> (*getOrCreateFrameNode)(const std::string& tag, int32_t nodeId, bool isOptionPattern, int index);
    void (*setSubBuilder)(const RefPtr<FrameNode>& node, const std::function<void()>& subBuilderFunc);
    void (*addResObj)(const RefPtr<FrameNode>& node, const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);
    void (*removeResObj)(const RefPtr<FrameNode>& node, const std::string& key);
    std::string (*getResCacheMapByKey)(const RefPtr<FrameNode>& node, const std::string& key);
    void (*addResCache)(const RefPtr<FrameNode>& node, const std::string& key, const std::string& value);
    bool (*hasMenuItemEventHub)(const RefPtr<FrameNode>& node);
    void (*setSelectOverlayMenuOnClick)(const RefPtr<FrameNode>& node, const std::function<void()>& onClickFunc);
    void (*setEnabled)(const RefPtr<FrameNode>& node, bool enabled);
    void (*setCurrentUIState)(const RefPtr<FrameNode>& node, uint64_t state, bool flag);
    void (*setOnSelect)(const RefPtr<FrameNode>& node, const std::function<void(int32_t)>& onSelect);
    void (*updateSelectModifiedWidth)(const RefPtr<FrameNode>& node, const float& value);
    void (*updateOptionBgColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*updateOptionFontColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*updateSelectedOptionBgColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*updateSelectedOptionFontColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*updateNeedDivider)(const RefPtr<FrameNode>& node, bool needDivider);
    float (*getSelectModifiedWidthValue)(const RefPtr<FrameNode>& node, const float& value);
    bool (*hasDivider)(const RefPtr<FrameNode>& node);
    SelectDivider (*getDividerValue)(const RefPtr<FrameNode>& node);
    void (*updateDivider)(const RefPtr<FrameNode>& node, const SelectDivider& divider);
    void (*setIdealWidthForWeb)(const RefPtr<FrameNode>& node, int32_t width);
    void (*updateStartMargin)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*updateEndMargin)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*updateDividerColor)(const RefPtr<FrameNode>& node, const Color& color);
    void (*updateStartIcon)(const RefPtr<FrameNode>& node, const ImageSourceInfo& value);
    void (*updateEndIcon)(const RefPtr<FrameNode>& node, const ImageSourceInfo& value);
    void (*updateContent)(const RefPtr<FrameNode>& node, const std::string& value);
    void (*updateLabel)(const RefPtr<FrameNode>& node, const std::string& value);
    void (*setStartSymbol)(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol);
    void (*setEndSymbol)(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol);
    void (*setSelectSymbol)(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol);
    RefPtr<FrameNode> (*createWithParam)(OptionParam&& param, const MenuParam& menuParam);
    RefPtr<FrameNode> (*createWithOnClickEventSet)(bool isClickSet);
    void (*menuItemUpdatePadding)(const RefPtr<FrameNode>& node, const PaddingProperty& value);
    void (*menuItemUpdateStrokeWidth)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*menuItemUpdateStartMargin)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*menuItemUpdateEndMargin)(const RefPtr<FrameNode>& node, const Dimension& value);
    void (*menuItemUpdateDividerColor)(const RefPtr<FrameNode>& node, const Color& value);
    RefPtr<FrameNode> (*menuItemCreateFrameNode)();
    void (*menuItemApplyTheme)();
};

namespace InnerModifier {
const ArkUIMenuItemInnerModifier* GetMenuItemInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_INNER_MODIFIER_H