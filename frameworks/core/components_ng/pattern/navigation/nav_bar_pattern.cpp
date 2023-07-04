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
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

void UpdateTitleFontSize(const RefPtr<NavBarNode>& hostNode, const Dimension& fontSize)
{
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto titleLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID_NOLOG(titleLayoutProperty);
    titleLayoutProperty->UpdateFontSize(fontSize);
    titleNode->MarkModifyDone();
}

void BuildTitle(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navBarNode->GetTitle());
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        UpdateTitleFontSize(navBarNode, theme->GetTitleFontSize());
    } else {
        UpdateTitleFontSize(navBarNode, theme->GetTitleFontSizeBig());
    }

    if (navBarNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navBarNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    titleBarNode->SetTitle(navBarNode->GetTitle());
    titleBarNode->AddChild(titleBarNode->GetTitle());
}

void BuildSubtitle(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navBarNode->GetSubtitle());
    if (navBarNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navBarNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    titleBarNode->SetSubtitle(navBarNode->GetSubtitle());
    titleBarNode->AddChild(titleBarNode->GetSubtitle());
}

void BuildMenu(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navBarNode->GetMenu());
    if (navBarNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }

    if (navBarNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetMenu());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    titleBarNode->SetMenu(navBarNode->GetMenu());
    titleBarNode->AddChild(titleBarNode->GetMenu());
}

void BuildTitleBar(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode,
    RefPtr<NavBarLayoutProperty>& navBarLayoutProperty)
{
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    do {
        if (!navBarNode->HasBackButtonNodeOperation() ||
            navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::NONE) {
            break;
        }
        if (navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::REMOVE) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
            CHECK_NULL_VOID(backButtonLayoutProperty);
            backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
            break;
        }
        titleBarNode->SetBackButton(navBarNode->GetBackButton());
        titleBarNode->AddChild(titleBarNode->GetBackButton());
        if (titleBarNode->GetBackButton() && !titleBarLayoutProperty->GetHideBackButtonValue(false)) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
            CHECK_NULL_VOID(backButtonLayoutProperty);
            backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            break;
        }
    } while (false);
    BuildTitle(navBarNode, titleBarNode);
    BuildSubtitle(navBarNode, titleBarNode);
    BuildMenu(navBarNode, titleBarNode);
}

void MountTitleBar(const RefPtr<NavBarNode>& hostNode)
{
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    if (!hostNode->GetTitle() && !hostNode->GetSubtitle() && !hostNode->GetMenu() && !hostNode->GetBackButton()) {
        return;
    }
    titleBarLayoutProperty->UpdateTitleMode(navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE));
    titleBarLayoutProperty->UpdateHideBackButton(navBarLayoutProperty->GetHideBackButtonValue(false));
    BuildTitleBar(hostNode, titleBarNode, navBarLayoutProperty);
    if (navBarLayoutProperty->GetHideTitleBar().value_or(false)) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    titleBarNode->MarkModifyDone();
}

void MountToolBar(const RefPtr<NavBarNode>& hostNode)
{
    CHECK_NULL_VOID_NOLOG(hostNode->GetToolBarNode());
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto toolBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(toolBarLayoutProperty);

    if (hostNode->GetToolBarNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        hostNode->RemoveChild(hostNode->GetPreToolBarNode());
        hostNode->AddChild(hostNode->GetToolBarNode());
    }

    if (navBarLayoutProperty->GetHideToolBar().value_or(false)) {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
}
} // namespace

void NavBarPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!panEvent_);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleOnDragStart(info.GetOffsetY());
    };

    auto actionUpdateTask = [weak = WeakClaim(this), this](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleOnDragUpdate(info.GetOffsetY());
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleOnDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleOnDragEnd();
    };

    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::VERTICAL };
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void NavBarPattern::HandleOnDragStart(float offset)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragStart(offset);
}

void NavBarPattern::HandleOnDragUpdate(float offset)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragUpdate(offset);
}

void NavBarPattern::HandleOnDragEnd()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragEnd();
}

void NavBarPattern::InitCoordinationEvent()
{
    auto scrollableNode = FindScrollableChild();
    scrollableNode_ = WeakClaim(AceType::RawPtr(scrollableNode));
    CHECK_NULL_VOID(scrollableNode);
    auto scrollablePattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto onScrollEvent = [weak = WeakClaim(this)](double offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnCoordScrollUpdate(static_cast<float>(offset));
    };
    coordinationEvent->SetOnScrollEvent(onScrollEvent);
    auto onScrollStartEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnCoordScrollStart();
    };
    coordinationEvent->SetOnScrollStartEvent(onScrollStartEvent);
    auto onScrollEndEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnCoordScrollEnd();
    };
    coordinationEvent->SetOnScrollEndEvent(onScrollEndEvent);
    scrollablePattern->SetCoordinationEvent(coordinationEvent);
    scrollablePattern->SetParentDraggedDown(true);
    scrollablePattern->SetCoordEventNeedSpringEffect(false);
    scrollablePattern->SetCoordEventNeedMoveUp(true);
}

void NavBarPattern::OnCoordScrollStart()
{
    offset_ = 0.0f;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragStart(offset_);
    auto scrollableNode = scrollableNode_.Upgrade();
    CHECK_NULL_VOID(scrollableNode);
    auto scrollablePattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);
    scrollablePattern->SetParentDraggedDown(titlePattern->IsTitleDraggedDown());
    springEffect_ = scrollablePattern->IsScrollableSpringEffect();
}

void NavBarPattern::OnCoordScrollUpdate(float offset)
{
    offset_ += offset;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragUpdate(offset_);

    auto scrollableNode = scrollableNode_.Upgrade();
    CHECK_NULL_VOID(scrollableNode);
    auto scrollablePattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);
    scrollablePattern->SetParentDraggedDown(titlePattern->IsTitleDraggedDown());
}

void NavBarPattern::OnCoordScrollEnd()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    titlePattern->ProcessTittleDragEnd();
    offset_ = 0.0f;
}

RefPtr<FrameNode> NavBarPattern::FindScrollableChild()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    std::queue<RefPtr<FrameNode>> frameNodeQueue;
    frameNodeQueue.push(host);
    while (!frameNodeQueue.empty()) {
        auto size = frameNodeQueue.size();
        while (size > 0) {
            auto node = frameNodeQueue.front();
            CHECK_NULL_RETURN(node, nullptr);
            if ((AceType::InstanceOf<ScrollablePattern>(node->GetPattern())) &&
                ((AceType::InstanceOf<ListPattern>(node->GetPattern())) ||
                    (AceType::InstanceOf<GridPattern>(node->GetPattern())))) {
                return node;
            }
            frameNodeQueue.pop();
            auto children = node->GetChildren();
            for (auto const& child : children) {
                auto childNode = DynamicCast<FrameNode>(child);
                if (childNode) {
                    frameNodeQueue.push(childNode);
                }
            }
            size--;
        }
    }
    return nullptr;
}

void NavBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountTitleBar(hostNode);
    MountToolBar(hostNode);
    auto gesture = hostNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    InitPanEvent(gesture);
    InitCoordinationEvent();
}

} // namespace OHOS::Ace::NG
