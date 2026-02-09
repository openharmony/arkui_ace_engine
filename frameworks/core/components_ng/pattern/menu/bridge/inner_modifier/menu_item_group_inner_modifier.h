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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_GROUP_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_GROUP_INNER_MODIFIER_H

#include "interfaces/inner_api/ace_kit/include/ui/base/geometry/dimension.h"

namespace OHOS::Ace {
class AceType;
template<class T>
class RefPtr;
namespace NG {
class FrameNode;
class UINode;
struct ArkUIMenuItemGroupInnerModifier {
    void (*menuItemGroupAddHeader)(const RefPtr<FrameNode>& node, const RefPtr<NG::UINode>& header);
    void (*menuItemGroupAddHeaderContent)(const RefPtr<FrameNode>& node, const RefPtr<NG::FrameNode>& headerContent);
    void (*menuItemGroupUpdateStrokeWidth)(const RefPtr<FrameNode>& node, const Dimension& value);
    RefPtr<FrameNode> (*menuItemGroupAddHeaderGetOrCreateFrameNode)();
};

namespace InnerModifier {
const ArkUIMenuItemGroupInnerModifier* GetMenuItemGroupInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_ITEM_GROUP_INNER_MODIFIER_H