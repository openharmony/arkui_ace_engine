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

#include "core/common/force_split/force_split_utils.h"

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension APP_ICON_SIZE = 64.0_vp;
constexpr char BG_COLOR_SYS_RES_NAME[] = "sys.color.ohos_id_color_sub_background";
const std::vector<std::string> PRIMARY_PAGE_PREFIX = {"main", "home", "index", "root"};
const std::vector<std::string> TRANS_PAGE_PREFIX = {"guide", "load", "splash", "login"};
constexpr int32_t PRIMARY_DESTINATION_CHILD_NODE_DEPTH_THRESHOLD = 50;
constexpr int32_t PRIMARY_DESTINATION_CHILD_NODE_COUNT_THRESHOLD = 100;
}

RefPtr<FrameNode> ForceSplitUtils::CreatePlaceHolderContent(const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);
    auto id = windowManager->GetAppIconId();
    auto pixelMap = themeConstants->GetPixelMap(id);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    CalcSize imageCalcSize((CalcLength(APP_ICON_SIZE)), CalcLength(APP_ICON_SIZE));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(PixelMap::CreatePixelMap(&pixelMap)));
    imageNode->MountToParent(stackNode);
    imageNode->MarkModifyDone();

    return stackNode;
}

RefPtr<NavDestinationGroupNode> ForceSplitUtils::CreatePlaceHolderNavDestination(const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto navManager = context->GetNavigationManager();
    CHECK_NULL_RETURN(navManager, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeHolder = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    CHECK_NULL_RETURN(placeHolder, nullptr);

    auto eventHub = placeHolder->GetOrCreateEventHub<EventHub>();
    eventHub->SetEnabled(false);
    auto pattern = placeHolder->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetName("__placeHolder_NavDestination__");
    auto focusHub = pattern->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusable(false);
    placeHolder->SetNavDestinationType(NavDestinationType::PLACE_HOLDER);
    auto property = placeHolder->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    property->UpdateHideTitleBar(true);
    property->UpdateIsAnimatedTitleBar(false);
    property->UpdateHideToolBar(true);
    property->UpdateIsAnimatedToolBar(false);
    property->UpdateVisibility(VisibleType::INVISIBLE);

    auto phContext = placeHolder->GetRenderContext();
    CHECK_NULL_RETURN(phContext, nullptr);
    Color bgColor;
    if (navManager->GetSystemColor(BG_COLOR_SYS_RES_NAME, bgColor)) {
        phContext->UpdateBackgroundColor(bgColor);
    }

    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_RETURN(contentNode, nullptr);
    auto phContent = CreatePlaceHolderContent(context);
    CHECK_NULL_RETURN(phContent, nullptr);
    phContent->MountToParent(contentNode);

    placeHolder->AddChild(contentNode);
    placeHolder->SetContentNode(contentNode);

    return placeHolder;
}

bool ForceSplitUtils::IsNavDestinationHomePage(const RefPtr<NavDestinationGroupNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    if (node->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        return false;
    }

    auto context = node->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto navManager = context->GetNavigationManager();
    CHECK_NULL_RETURN(navManager, false);
    auto pattern = node->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const auto& expectedHomeName = navManager->GetHomePageName();
    std::string name = pattern->GetName();
    if (!expectedHomeName.empty() && expectedHomeName == name) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] with expectedName", name.c_str());
        return true;
    }
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (auto it = TRANS_PAGE_PREFIX.begin(); it != TRANS_PAGE_PREFIX.end(); it++) {
        std::string prefix = *it;
        if (name.find(prefix) != std::string::npos) {
            return false;
        }
    }
    for (auto it = PRIMARY_PAGE_PREFIX.begin(); it != PRIMARY_PAGE_PREFIX.end(); it++) {
        std::string prefix = *it;
        if (name.find(prefix) != std::string::npos) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] with primary page prefix", name.c_str());
            return true;
        }
    }
    int32_t count = 0;
    int32_t depth = 0;
    node->GetPageNodeCountAndDepth(&count, &depth);
    if (count > PRIMARY_DESTINATION_CHILD_NODE_COUNT_THRESHOLD &&
        depth > PRIMARY_DESTINATION_CHILD_NODE_DEPTH_THRESHOLD) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] for node count:%{public}d and depth:%{public}d",
            name.c_str(), count, depth);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG

