/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H

#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {

enum class MenuHoverScaleStatus {
    DISABLE = 0,
    NONE,
    READY,
    HOVER,
    INTERRUPT,
    MENU_SHOW,
};

class ACE_EXPORT MenuView {
struct OptionValueInfo {
    bool optionsHasIcon = false;

    std::string content;
    bool isPasteOption = false;
    bool isAIMenuOption = false;
};

public:
    static void BindImageNodeToMenu(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& wrapperNode,
        const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam, const RefPtr<UINode>& previewCustomNode);

    // create menu with menuItems
    static RefPtr<FrameNode> Create(std::vector<OptionParam>&& params, int32_t targetId,
        const std::string& targetTag = "", MenuType type = MenuType::MENU, const MenuParam& menuParam = MenuParam());

    // create menu with custom node from a builder
    static RefPtr<FrameNode> Create(const RefPtr<UINode>& customNode, int32_t targetId,
        const std::string& targetTag = "", const MenuParam& menuParam = MenuParam(), bool withWrapper = true,
        const RefPtr<UINode>& previewCustomNode = nullptr);

    // create select's popup menu
    static RefPtr<FrameNode> Create(const std::vector<SelectParam>& params, int32_t targetId,
        const std::string& targetTag, bool autoWrapFlag = false);

    static void ShowPixelMapAnimation(const RefPtr<FrameNode>& menuNode);
    static void GetMenuPixelMap(
        const RefPtr<FrameNode>& targetNode, const MenuParam& menuParam, const RefPtr<FrameNode>& wrapperNode);
    static void UpdateMenuParam(
        const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    static void UpdateMenuProperties(const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& menuNode,
        const MenuParam& menuParam, const MenuType& type);

    static void CalcHoverScaleInfo(const RefPtr<FrameNode>& menuNode);
    static RefPtr<FrameNode> CreateIcon(const std::string& icon, const RefPtr<FrameNode>& parent,
        const RefPtr<FrameNode>& child = nullptr);
    static RefPtr<FrameNode> CreateText(const std::string& value, const RefPtr<FrameNode>& parent,
        bool autoWrapFlag = false, bool isAIMenuOption = false);
    static void CreatePasteButton(bool optionsHasIcon, const RefPtr<FrameNode>& option, const RefPtr<FrameNode>& row,
        const std::function<void()>& onClickFunc, const std::string& icon = "");
    static RefPtr<FrameNode> CreateSelectOption(const SelectParam& param, int32_t index, bool autoWrapFlag = false);
    static RefPtr<FrameNode> CreateSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol,
        const RefPtr<FrameNode>& parent, const RefPtr<FrameNode>& child = nullptr,
        const std::optional<Dimension>& symbolUserDefinedIdealFontSize = std::nullopt);
    static void UpdateMenuNodePosition(const PreparedInfoForDrag& data);
    static void ExecuteMenuDisappearAnimation(const PreparedInfoForDrag& data);
    static void SetHasCustomOutline(
        const RefPtr<FrameNode>& menuWrapperNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    static void RegisterAccessibilityChildActionNotify(const RefPtr<FrameNode>& menuNode);
    static void TouchEventGenerator(const RefPtr<FrameNode>& actionNode, TouchEvent& event);
    static void TouchPointGenerator(const RefPtr<FrameNode>& actionNode, TouchPoint& point);
    static void ShowMenuTargetScaleToOrigin(
        const RefPtr<MenuWrapperPattern>& wrapperPattern, const RefPtr<MenuPreviewPattern>& previewPattern);
    static void UpdateHoverImagePreivewPosition(const RefPtr<MenuPreviewPattern>& previewPattern);
    static void ShowHoverImageForInterruption(const RefPtr<FrameNode>& hoverImageStackNode,
        const RefPtr<FrameNode>& previewNode, const RefPtr<RenderContext>& imageContext,
        const RefPtr<MenuWrapperPattern>& wrapperPattern);
    static bool CheckHoverImageFinishForInterruption(const RefPtr<MenuWrapperPattern>& wrapperPattern,
        const RefPtr<MenuPreviewPattern>& previewPattern, const RefPtr<FrameNode>& hoverImageStackNode);
    static void SetMenuHoverScaleStatus(int32_t targetId, MenuHoverScaleStatus status);
    static void RemoveMenuHoverScaleStatus(int32_t targetId);
    static MenuHoverScaleStatus GetMenuHoverScaleStatus(int32_t targetId);

private:
    static void UpdateMenuPaintProperty(
        const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam, const MenuType& isContextMenu);
    static void UpdateMenuBackgroundEffect(const RefPtr<FrameNode>& menuNode);
    static void UpdateMenuBorderEffect(
        const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& wrapperNode, const MenuParam& menuParam);
    static void UpdateMenuBackgroundStyle(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    static void NeedAgingUpdateNode(const RefPtr<FrameNode>& optionNode);
    static void ContextMenuChildMountProc(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& wrapperNode,
        const RefPtr<FrameNode>& previewNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    static void CustomPreviewParentNodeCreate(const RefPtr<FrameNode>& stackNode, const RefPtr<FrameNode>& posNode,
        const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& previewNode);
    static RefPtr<FrameNode> Create(int32_t index);
    static RefPtr<FrameNode> CreateMenuOption(const OptionValueInfo& value,
        const std::function<void()>& onClickFunc, int32_t index, const std::string& icon = "");
    static RefPtr<FrameNode> CreateMenuOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index);
    static void CreateOption(const OptionValueInfo& value, const std::string& icon,
        const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option, const std::function<void()>& onClickFunc);
    static void CreateOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index,
        const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option);
    static void MountOptionToColumn(std::vector<OptionParam>& params, const RefPtr<FrameNode>& menuNode,
        const MenuParam& menuParam, RefPtr<FrameNode> column);
    static void UpdateMenuBackgroundStyleSub(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    static void UpdateMenuNodeByAnimation(const RefPtr<FrameNode>& menuNode, const PreparedInfoForDrag& data);
    static void UpdateMenuPositionTop(MarginProperty& menuNodeMargin,
        std::map<AlignDirection, AlignRule>& menuNodeAlignRules, AlignRule& alignMap, float biasMenuTop,
        float biasMenuBottom);
    static void UpdateMenuPositionLeft(MarginProperty& menuNodeMargin,
        std::map<AlignDirection, AlignRule>& menuNodeAlignRules, AlignRule& alignMap, float biasMenuLeft,
        float biasMenuRight);
    static void UpdateMenuNodePositionTop(MarginProperty& menuNodeMargin,
        std::map<AlignDirection, AlignRule>& menuNodeAlignRules, const PreparedInfoForDrag& data, float biasMenuLeft,
        std::map<std::string, AlignRule>& alignMap);
    static void UpdateMenuNodePositionLeft(MarginProperty& menuNodeMargin,
        std::map<AlignDirection, AlignRule>& menuNodeAlignRules, const PreparedInfoForDrag& data, float biasMenuLeft,
        std::map<std::string, AlignRule>& alignMap);
    static void UpdateMenuOutlineWithArrow(
        const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& wrapperNode, const MenuParam& menuParam);
    static void ReloadMenuParam(const MenuParam& menuParam);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H
