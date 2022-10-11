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

#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void BuildTitleAndSubtitle(
    const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (!navBarNode->GetTitle() && !navBarNode->GetSubtitle()) {
        return;
    }
    if (navBarNode->GetTitle() && navBarNode->HasTitleNodeOperation()) {
        if (navBarNode->GetTitleNodeOperationValue() != ChildNodeOperation::NONE) {
            if (navBarNode->GetTitleNodeOperationValue() == ChildNodeOperation::REPLACE) {
                navBarNode->RemoveChild(titleBarNode->GetTitle());
            }
            titleBarNode->SetTitle(navBarNode->GetTitle());
            titleBarNode->AddChild(titleBarNode->GetTitle());
        }
    }
    if (navBarNode->GetSubtitle() && navBarNode->HasSubtitleNodeOperation()) {
        if (navBarNode->GetSubtitleNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (navBarNode->GetSubtitleNodeOperationValue() == ChildNodeOperation::REPLACE) {
            navBarNode->RemoveChild(titleBarNode->GetSubtitle());
        }
        titleBarNode->SetSubtitle(navBarNode->GetSubtitle());
        titleBarNode->AddChild(titleBarNode->GetSubtitle());
    }
    titleBarNode->MarkModifyDone();
}

void BuildMenu(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (navBarNode->GetMenu() && navBarNode->HasMenuNodeOperation()) {
        if (navBarNode->GetMenuNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (navBarNode->GetMenuNodeOperationValue() == ChildNodeOperation::REPLACE) {
            navBarNode->RemoveChild(titleBarNode->GetMenu());
        }
        titleBarNode->SetMenu(navBarNode->GetMenu());
        titleBarNode->AddChild(titleBarNode->GetMenu());
    }
    titleBarNode->MarkModifyDone();
}

void BuildTitleBar(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode,
    RefPtr<NavBarLayoutProperty>& navBarLayoutProperty)
{
    if (!navBarNode->GetTitleBarNode()) {
        return;
    }
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (navBarLayoutProperty->HasHideBackButton()) {
        titleBarLayoutProperty->UpdateHideBackButton(navBarLayoutProperty->GetHideBackButtonValue());
    }
    do {
        if (!navBarNode->HasBackButtonNodeOperation() ||
            navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI ||
            navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::NONE) {
            break;
        }
        if (navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::REMOVE) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto textLayoutProperty = backButtonNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateVisibility(VisibleType::GONE);
            break;
        }
        // TODO: fix error for update condition when add or delete child
        if (titleBarNode->GetBackButton()) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto textLayoutProperty = backButtonNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            break;
        }
        titleBarNode->SetBackButton(navBarNode->GetBackButton());
        titleBarNode->AddChild(titleBarNode->GetBackButton());
    } while (false);
    titleBarLayoutProperty->UpdateTitleMode(navBarLayoutProperty->GetTitleModeValue());
    if (navBarLayoutProperty->HasHideTitleBar()) {
        titleBarLayoutProperty->UpdateHideTitleBar(navBarLayoutProperty->GetHideTitleBarValue());
    }
    BuildTitleAndSubtitle(navBarNode, titleBarNode);
    BuildMenu(navBarNode, titleBarNode);
}

void MountTitleBar(const RefPtr<NavBarNode>& hostNode)
{
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    if (!hostNode->GetTitle() && !hostNode->GetSubtitle() && !hostNode->GetMenu() &&
        navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    BuildTitleBar(hostNode, titleBarNode, navBarLayoutProperty);
}

void MountToolBar(const RefPtr<NavBarNode>& hostNode)
{
    if (hostNode->GetToolBarNode() && hostNode->HasToolBarNodeOperation()) {
        if (hostNode->GetToolBarNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (hostNode->GetToolBarNodeOperationValue() == ChildNodeOperation::REPLACE) {
            hostNode->RemoveChild(hostNode->GetPreToolBarNode());
        }
        hostNode->AddChild(hostNode->GetToolBarNode());
    }
}
} // namespace

bool NavBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto navigationLayoutAlgorithm =
        DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(navigationLayoutAlgorithm, false);
    // TODO: add scroll effect to title and subtitle
    lastScrollDistance_ = navigationLayoutAlgorithm->GetLastScrollDistance();
    return false;
}

void NavBarPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountTitleBar(hostNode);
    MountToolBar(hostNode);
}

void NavBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
}

} // namespace OHOS::Ace::NG