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

#include "core/components_ng/pattern/navigation/navigation_layout_util.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"

namespace OHOS::Ace::NG {
bool NavigationLayoutUtil::CheckWhetherNeedToHideToolbar(
    const RefPtr<NavDestinationNodeBase>& nodeBase, const SizeF& navigationSize)
{
    // if current menu or toolBar is custom, no need to hide.
    if (nodeBase->GetPrevMenuIsCustomValue(false) || nodeBase->GetPrevToolBarIsCustom().value_or(false)) {
        return false;
    }

    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
    CHECK_NULL_RETURN(toolbarNode, false);
    if (!toolbarNode->HasValidContent()) {
        return true;
    }

    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    auto rotationLimitCount = theme->GetToolbarRotationLimitGridCount();

    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::NAVIGATION_TOOLBAR);
    columnInfo->GetParent()->BuildColumnWidth();

    auto currentColumns = columnInfo->GetParent()->GetColumns();
    float gridWidth = static_cast<float>(columnInfo->GetWidth(rotationLimitCount));
    float gutterWidth = columnInfo->GetParent()->GetGutterWidth().ConvertToPx();
    float hideLimitWidth = gridWidth + gutterWidth * 2;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (currentColumns >= static_cast<int32_t>(rotationLimitCount) &&
            GreatOrEqual(navigationSize.Width(), gridWidth)) {
            return true;
        }
    } else if (SystemProperties::GetDeviceType() == DeviceType::TABLET) {
        if (currentColumns > static_cast<int32_t>(rotationLimitCount) &&
            GreatNotEqual(navigationSize.Width(), hideLimitWidth)) {
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG
