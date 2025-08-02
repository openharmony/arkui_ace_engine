/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "accessibility_system_ability_client.h"

#include "adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h"
#include "base/log/dump_log.h"
#include "core/accessibility/accessibility_utils.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {

namespace {
inline std::string BoolToString(bool tag)
{
    return tag ? "true" : "false";
}

inline std::string ChildrenToString(const std::vector<int64_t>& children, int32_t treeId)
{
    std::string ids;
    for (auto& child : children) {
        if (!ids.empty()) {
            ids.append(",");
        }
        int64_t childId = child;
        AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, childId);
        ids.append(std::to_string(childId));
    }
    return ids;
}

inline void DumpRectNG(const Accessibility::Rect& rect)
{
    DumpLog::GetInstance().AddDesc(
        "width: ", std::to_string(rect.GetRightBottomXScreenPostion() - rect.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc(
        "height: ", std::to_string(rect.GetRightBottomYScreenPostion() - rect.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("left: ", std::to_string(rect.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc("top: ", std::to_string(rect.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("right: ", std::to_string(rect.GetRightBottomXScreenPostion()));
    DumpLog::GetInstance().AddDesc("bottom: ", std::to_string(rect.GetRightBottomYScreenPostion()));
}

} // namespace

void AccessibilityElementInfoUtils::ToCommonInfo(
    const Accessibility::AccessibilityElementInfo& nodeInfo,
    int32_t treeId)
{
    int64_t elementId = nodeInfo.GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, elementId);
    DumpLog::GetInstance().AddDesc("ID: ", elementId);
    DumpLog::GetInstance().AddDesc("UniqueID: ", nodeInfo.GetUniqueId());
    int64_t parentId = nodeInfo.GetParentNodeId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, parentId);
    DumpLog::GetInstance().AddDesc("parent ID: ", parentId);
    DumpLog::GetInstance().AddDesc("child IDs: ", ChildrenToString(nodeInfo.GetChildIds(), treeId));
    DumpLog::GetInstance().AddDesc("component type: ", nodeInfo.GetComponentType());
    DumpLog::GetInstance().AddDesc("accessibilityCustomRole: " + nodeInfo.GetCustomComponentType());
    DumpLog::GetInstance().AddDesc("text: ", nodeInfo.GetContent());
    DumpLog::GetInstance().AddDesc("originText: ", nodeInfo.GetOriginalText());
    DumpLog::GetInstance().AddDesc("window id: " + std::to_string(nodeInfo.GetWindowId()));
    DumpRectNG(nodeInfo.GetRectInScreen());

    DumpLog::GetInstance().AddDesc("enabled: ", BoolToString(nodeInfo.IsEnabled()));
    DumpLog::GetInstance().AddDesc("focusable: ", BoolToString(nodeInfo.IsFocusable()));
    DumpLog::GetInstance().AddDesc("focused: ", BoolToString(nodeInfo.IsFocused()));
    DumpLog::GetInstance().AddDesc("visible: ", BoolToString(nodeInfo.IsVisible()));
    DumpLog::GetInstance().AddDesc("accessibility focused: ", BoolToString(nodeInfo.HasAccessibilityFocus()));
    DumpLog::GetInstance().AddDesc("accessibilityText: " + nodeInfo.GetAccessibilityText());
    DumpLog::GetInstance().AddDesc("accessibilityGroup: " + BoolToString(nodeInfo.GetAccessibilityGroup()));
    DumpLog::GetInstance().AddDesc("accessibilityLevel: " + nodeInfo.GetAccessibilityLevel());
    DumpLog::GetInstance().AddDesc("accessibilityDescription: " + nodeInfo.GetDescriptionInfo());
    DumpLog::GetInstance().AddDesc("hitTestBehavior: " + nodeInfo.GetHitTestBehavior());

    DumpLog::GetInstance().AddDesc("inspector key: ", nodeInfo.GetInspectorKey());
    DumpLog::GetInstance().AddDesc("bundle name: ", nodeInfo.GetBundleName());
    DumpLog::GetInstance().AddDesc("page id: " + std::to_string(nodeInfo.GetPageId()));
    DumpLog::GetInstance().AddDesc("page path: ", nodeInfo.GetPagePath());
    DumpLog::GetInstance().AddDesc("is valid element: ", BoolToString(nodeInfo.IsValidElement()));
    DumpLog::GetInstance().AddDesc("resource name: ", nodeInfo.GetComponentResourceId());

    DumpLog::GetInstance().AddDesc("clickable: ", BoolToString(nodeInfo.IsClickable()));
    DumpLog::GetInstance().AddDesc("long clickable: ", BoolToString(nodeInfo.IsLongClickable()));
    DumpLog::GetInstance().AddDesc("popup supported: ", BoolToString(nodeInfo.IsPopupSupported()));
    DumpLog::GetInstance().AddDesc("zindex: ", std::to_string(nodeInfo.GetZIndex()));
}
} // namespace OHOS::Ace::Framework
