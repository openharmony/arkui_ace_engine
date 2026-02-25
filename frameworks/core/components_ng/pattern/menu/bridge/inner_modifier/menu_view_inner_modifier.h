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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_VIEW_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_VIEW_INNER_MODIFIER_H

#include <cstdint>
#include <string>
#include <vector>

namespace OHOS::Ace {
struct SelectParam;
class AceType;
template<class T>
class RefPtr;
namespace NG {
enum class MenuHoverScaleStatus;
enum class MenuType;
struct MenuParam;
struct OptionParam;
struct PreparedInfoForDrag;
class FrameNode;
class UINode;

struct ArkUIMenuViewInnerModifier {
    RefPtr<FrameNode> (*createWithOptionParams)(std::vector<OptionParam>&& params, int32_t targetId,
        const std::string& targetTag, MenuType type, const MenuParam& menuParam);
    RefPtr<FrameNode> (*createWithCustomNode)(const RefPtr<UINode>& customNode, int32_t targetId,
        const std::string& targetTag, const MenuParam& menuParam, bool withWrapper,
        const RefPtr<UINode>& previewCustomNode);
    RefPtr<FrameNode> (*createWithSelectParams)(
        const std::vector<SelectParam>& params, int32_t targetId, const std::string& targetTag, bool autoWrapFlag);
    void (*removeMenuHoverScaleStatus)(int32_t targetId);
    void (*executeMenuDisappearAnimation)(const PreparedInfoForDrag& data);
    void (*updateMenuNodePosition)(const PreparedInfoForDrag& data);
    void (*updateMenuParam)(
        const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    void (*updateMenuProperties)(const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& menuNode,
        const MenuParam& menuParam, const MenuType& type);
    void (*getMenuPixelMap)(
        const RefPtr<FrameNode>& targetNode, const MenuParam& menuParam, const RefPtr<FrameNode>& wrapperNode);
    void (*setMenuHoverScaleStatus)(int32_t targetId, MenuHoverScaleStatus status);
    MenuHoverScaleStatus (*getMenuHoverScaleStatus)(int32_t targetId);
    void (*setMenuSystemMaterial)(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
};

namespace InnerModifier {
const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier();

} // namespace InnerModifier
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_VIEW_INNER_MODIFIER_H