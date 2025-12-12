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
#include "ui/base/utils/utils.h"

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension APP_ICON_SIZE = 64.0_vp;
constexpr Dimension APP_ICON_BORDER_RADIUS = 18.0_vp;
constexpr char BG_COLOR_SYS_RES_NAME[] = "sys.color.ohos_id_color_sub_background";
const std::vector<std::string> HOME_NAME_KEYWORDS = {"main", "home", "index", "root"};
const std::vector<std::string> EXCLUDE_NAME_KEYWORDS = {"guide", "load", "splash", "login", "privacy"};
constexpr int32_t HOME_PAGE_CHILD_NODE_DEPTH_THRESHOLD = 30;
constexpr int32_t HOME_PAGE_CHILD_NODE_COUNT_THRESHOLD = 100;
constexpr char NAV_BAR_HOME_PAGE_NAME[] = "navBar";
constexpr char HOME_PAGE_KEY[] = "homePage";
constexpr char RELATED_PAGE_KEY[] = "relatedPage";
constexpr char ENABLE_ARKUI_HOOK_KEY[] = "enableArkUIHook";
constexpr char HOME_NAVIGATION_ID_KEY[] = "homeNavigationId";
constexpr char ENABLE_HOOK_KEY[] = "enableHook";
constexpr char NAVIGATION_OPTIONS_KEY[] = "navigationOptions";
constexpr char NAVIGATION_OPTIONS_ID_KEY[] = "id";
constexpr char NAVIGATION_OPTIONS_DEPTH_KEY[] = "depth";
constexpr char NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY[] = "disablePlaceholder";
constexpr char NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY[] = "disableDivider";
constexpr char FULL_SCREEN_PAGES_KEY[] = "fullScreenPages";

std::string FullScreenPageToString(const std::set<std::string>& fullScreenPages)
{
    std::string str("[");
    int32_t idx = 0;
    for (const auto& page : fullScreenPages) {
        if (idx != 0) {
            str.append(", ");
        }
        str.append(page);
        idx++;
    }
    str.append("]");
    return str;
}

class PlaceholderPattern : public StackPattern {
    DECLARE_ACE_TYPE(PlaceholderPattern, StackPattern);
public:
    PlaceholderPattern() = default;
    ~PlaceholderPattern() override = default;

    void OnColorConfigurationUpdate() override;
    void OnAttachToMainTree() override;
    void RefreshBackgroundColor();
};

void PlaceholderPattern::OnColorConfigurationUpdate()
{
    RefreshBackgroundColor();
}

void PlaceholderPattern::OnAttachToMainTree()
{
    StackPattern::OnAttachToMainTree();
    RefreshBackgroundColor();
}

void PlaceholderPattern::RefreshBackgroundColor()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto navManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navManager);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Color bgColor;
    if (navManager->GetSystemColor(BG_COLOR_SYS_RES_NAME, bgColor)) {
        renderContext->UpdateBackgroundColor(bgColor);
    }
}
}

RefPtr<FrameNode> ForceSplitUtils::CreatePlaceHolderContent(const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PlaceholderPattern>(); });
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
        .edges = SAFE_AREA_EDGE_ALL };
    stackLayoutProperty->UpdateSafeAreaExpandOpts(opts);

    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);
    auto id = forceSplitMgr->GetAppIconId();
    auto pixelMap = themeConstants->GetPixelMap(id);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    CalcSize imageCalcSize((CalcLength(APP_ICON_SIZE)), CalcLength(APP_ICON_SIZE));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(PixelMap::CreatePixelMap(&pixelMap)));
    auto imageRenderContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageRenderContext, nullptr);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(APP_ICON_BORDER_RADIUS);
    borderRadius.multiValued = false;
    imageRenderContext->UpdateBorderRadius(borderRadius);
    auto paintProperty = imageNode->GetPaintPropertyPtr<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    paintProperty->UpdateNeedBorderRadius(true);
    paintProperty->UpdateBorderRadius(borderRadius);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(imagePattern, nullptr);
    imagePattern->SetNeedBorderRadius(true);

    imageNode->MountToParent(stackNode);
    imageNode->MarkModifyDone();

    return stackNode;
}

RefPtr<NavDestinationGroupNode> ForceSplitUtils::CreateNavDestinationProxyNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto proxyNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    CHECK_NULL_RETURN(proxyNode, nullptr);
    proxyNode->SetNavDestinationType(NavDestinationType::PROXY);
    auto pattern = proxyNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetName("__NavDestination_proxy__");
    auto eventHub = proxyNode->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(false);
    }
    auto focusHub = proxyNode->GetOrCreateFocusHub();
    if (focusHub) {
        focusHub->SetFocusable(false);
    }
    auto property = proxyNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    property->UpdateHideTitleBar(true);
    property->UpdateIsAnimatedTitleBar(false);
    property->UpdateHideToolBar(true);
    property->UpdateIsAnimatedToolBar(false);
    property->UpdateVisibility(VisibleType::INVISIBLE);
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_RETURN(contentNode, nullptr);
    proxyNode->AddChild(contentNode);
    proxyNode->SetContentNode(contentNode);
    return proxyNode;
}

bool ForceSplitUtils::IsHomePageNavBar(const RefPtr<NavBarNode>& navBar)
{
    CHECK_NULL_RETURN(navBar, false);
    auto context = navBar->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto manager = context->GetForceSplitManager();
    CHECK_NULL_RETURN(manager, false);
    const auto& expectedHomeName = manager->GetHomePageName();
    if (!expectedHomeName.empty()) {
        if (expectedHomeName == NAV_BAR_HOME_PAGE_NAME) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find navBar homePage with expectedName");
            return true;
        }
        return false;
    }

    int32_t count = 0;
    int32_t depth = 0;
    navBar->GetPageNodeCountAndDepth(&count, &depth);
    if (count > HOME_PAGE_CHILD_NODE_COUNT_THRESHOLD &&
        depth > HOME_PAGE_CHILD_NODE_DEPTH_THRESHOLD) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find NavBar as homePage for node count:%{public}d and depth:%{public}d",
            count, depth);
        return true;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "NavBar Not HomePage, count: %{public}d, depth: %{public}d", count, depth);
    return false;
}

bool ForceSplitUtils::IsHomePageNavDestination(const RefPtr<NavDestinationGroupNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    if (node->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        return false;
    }

    auto context = node->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    auto pattern = node->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const auto& expectedHomeName = forceSplitMgr->GetHomePageName();
    std::string name = pattern->GetName();
    if (!expectedHomeName.empty()) {
        if (expectedHomeName == name) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] with expectedName", name.c_str());
            return true;
        }
        return false;
    }
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (auto it = EXCLUDE_NAME_KEYWORDS.begin(); it != EXCLUDE_NAME_KEYWORDS.end(); it++) {
        std::string keyword = *it;
        if (name.find(keyword) != std::string::npos) {
            return false;
        }
    }
    for (auto it = HOME_NAME_KEYWORDS.begin(); it != HOME_NAME_KEYWORDS.end(); it++) {
        std::string keyword = *it;
        if (name.find(keyword) != std::string::npos) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] with primary page keyword", name.c_str());
            return true;
        }
    }
    int32_t count = 0;
    int32_t depth = 0;
    node->GetPageNodeCountAndDepth(&count, &depth);
    if (count > HOME_PAGE_CHILD_NODE_COUNT_THRESHOLD &&
        depth > HOME_PAGE_CHILD_NODE_DEPTH_THRESHOLD) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find homePage[%{public}s] for node count:%{public}d and depth:%{public}d",
            name.c_str(), count, depth);
        return true;
    }
    return false;
}

RefPtr<FrameNode> ForceSplitUtils::CreatePlaceHolderNode()
{
    int32_t phId = ElementRegister::GetInstance()->MakeUniqueId();
    auto phNode = FrameNode::GetOrCreateFrameNode(
        V2::SPLIT_PLACEHOLDER_CONTENT_ETS_TAG, phId, []() { return AceType::MakeRefPtr<Pattern>(); });
    CHECK_NULL_RETURN(phNode, nullptr);
    auto context = phNode->GetContextRefPtr();
    CHECK_NULL_RETURN(context, nullptr);
    auto property = phNode->GetLayoutProperty();
    CHECK_NULL_RETURN(property, nullptr);
    property->UpdateVisibility(VisibleType::INVISIBLE);
    property->UpdateAlignment(Alignment::TOP_LEFT);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
        .edges = SAFE_AREA_EDGE_ALL };
    property->UpdateSafeAreaExpandOpts(opts);
    auto eventHub = phNode->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(false);
    }
    auto focusHub = phNode->GetOrCreateFocusHub();
    if (focusHub) {
        focusHub->SetFocusable(false);
    }
    auto phContent = ForceSplitUtils::CreatePlaceHolderContent(context);
    if (phContent) {
        phContent->MountToParent(phNode);
    } else {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "failed to create PlaceHolder content");
    }
    return phNode;
}

bool ForceSplitUtils::ParseNavigationOptions(
    const std::unique_ptr<JsonValue>& navigationOptions, ForceSplitConfig& config)
{
    if (!navigationOptions || !navigationOptions->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, navigationOptions is an invalid json object!");
        return false;
    }
    if (navigationOptions->Contains(NAVIGATION_OPTIONS_ID_KEY)) {
        auto idJson = navigationOptions->GetValue(NAVIGATION_OPTIONS_ID_KEY);
        if (!idJson->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, navigationOptions.id is not string!");
            return false;
        }
        auto idStr = idJson->GetString();
        if (!idStr.empty()) {
            config.navigationId = idStr;
        }
    }
    if (navigationOptions->Contains(NAVIGATION_OPTIONS_DEPTH_KEY)) {
        auto depthJson = navigationOptions->GetValue(NAVIGATION_OPTIONS_DEPTH_KEY);
        if (!depthJson->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, navigationOptions.depth is not number!");
            return false;
        }
        config.navigationDepth = navigationOptions->GetInt(NAVIGATION_OPTIONS_DEPTH_KEY);
    }
    if (navigationOptions->Contains(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY)) {
        auto disablePlaceholderJson = navigationOptions->GetValue(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY);
        if (!disablePlaceholderJson->IsBool()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, navigationOptions.disablePlaceholder is not bool!");
            return false;
        }
        config.navigationDisablePlaceholder = disablePlaceholderJson->GetBool();
    }
    if (navigationOptions->Contains(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY)) {
        auto disableDividerJson = navigationOptions->GetValue(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY);
        if (!disableDividerJson->IsBool()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, navigationOptions.disableDivider is not bool!");
            return false;
        }
        config.navigationDisableDivider = disableDividerJson->GetBool();
    }
    return true;
}

bool ForceSplitUtils::ParseFullScreenPages(const std::unique_ptr<JsonValue>& fullScreenPages, ForceSplitConfig& config)
{
    if (!fullScreenPages || !fullScreenPages->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, fullScreenPages is an invalid json array!");
        return false;
    }
    std::set<std::string> pageSet;
    int32_t itemSize = fullScreenPages->GetArraySize();
    for (int32_t idx = 0; idx < itemSize; ++idx) {
        auto item = fullScreenPages->GetArrayItem(idx);
        if (!item || !item->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, fullScreenPages item is not a string!");
            continue;
        }
        auto page = item->GetString();
        if (!page.empty()) {
            pageSet.insert(page);
        }
    }
    std::swap(config.fullScreenPages, pageSet);
    return true;
}

bool ForceSplitUtils::ParseSystemForceSplitConfig(const std::string& configJsonStr, ForceSplitConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "parse system forceSplit config: %{public}s", configJsonStr.c_str());
    auto configJson = JsonUtil::ParseJsonString(configJsonStr);
    if (!configJson) {
        return false;
    }
    if (!configJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, arkUIOptions is an invalid json object!");
        return false;
    }
    config.isArkUIHookEnabled = configJson->GetBool(ENABLE_HOOK_KEY, false);
    if (configJson->Contains(NAVIGATION_OPTIONS_KEY)) {
        if (!ParseNavigationOptions(configJson->GetValue(NAVIGATION_OPTIONS_KEY), config)) {
            return false;
        }
    }
    if (configJson->Contains(FULL_SCREEN_PAGES_KEY)) {
        if (!ParseFullScreenPages(configJson->GetValue(FULL_SCREEN_PAGES_KEY), config)) {
            return false;
        }
    }
    return true;
}

bool ForceSplitUtils::ParseAppForceSplitConfig(
    bool isRouter, const std::string& configJsonStr, ForceSplitConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "parse app forceSplit config: %{public}s", configJsonStr.c_str());
    if (configJsonStr.empty()) {
        return true;
    }
    auto configJson = JsonUtil::ParseJsonString(configJsonStr);
    if (!configJson) {
        return false;
    }
    if (!configJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is an invalid json object!",
            isRouter ? "routerSplitOptions" : "navigationSplitOptions");
        return false;
    }
    config.isArkUIHookEnabled = configJson->GetBool(ENABLE_ARKUI_HOOK_KEY, false);
    if (configJson->Contains(HOME_PAGE_KEY)) {
        auto homePageJson = configJson->GetValue(HOME_PAGE_KEY);
        if (!homePageJson->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not string!", HOME_PAGE_KEY);
            return false;
        }
        auto homePageStr = homePageJson->GetString();
        if (!homePageStr.empty()) {
            config.homePage = homePageStr;
        }
    }
    if (configJson->Contains(RELATED_PAGE_KEY)) {
        auto relatedPageJson = configJson->GetValue(RELATED_PAGE_KEY);
        if (!relatedPageJson->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not string!", RELATED_PAGE_KEY);
            return false;
        }
        auto relatedPageStr = relatedPageJson->GetString();
        if (!relatedPageStr.empty()) {
            config.relatedPage = relatedPageStr;
        }
    }
    if (configJson->Contains(FULL_SCREEN_PAGES_KEY)) {
        if (!ParseFullScreenPages(configJson->GetValue(FULL_SCREEN_PAGES_KEY), config)) {
            return false;
        }
    }
    if (isRouter) {
        return true;
    }
    if (configJson->Contains(HOME_NAVIGATION_ID_KEY)) {
        auto idJson = configJson->GetValue(HOME_NAVIGATION_ID_KEY);
        if (!idJson->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not string!", HOME_NAVIGATION_ID_KEY);
            return false;
        }
        auto idStr = idJson->GetString();
        if (!idStr.empty()) {
            config.navigationId = idStr;
        }
    }
    if (configJson->Contains(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY)) {
        auto disablePlaceholderJson = configJson->GetValue(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY);
        if (!disablePlaceholderJson->IsBool()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not bool!",
                NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY);
            return false;
        }
        config.navigationDisablePlaceholder = disablePlaceholderJson->GetBool();
    }
    if (configJson->Contains(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY)) {
        auto disableDividerJson = configJson->GetValue(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY);
        if (!disableDividerJson->IsBool()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not bool!",
                NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY);
            return false;
        }
        config.navigationDisableDivider = disableDividerJson->GetBool();
    }
    return true;
}

void ForceSplitUtils::LogSystemForceSplitConfig(
    bool isRouter, const std::string& homePage, const ForceSplitConfig& config)
{
    TAG_LOGI(
        AceLogTag::ACE_NAVIGATION,
        "system ForceSplitConfig: isRouter:%{public}d, homePage:%{public}s, "
        "fullScreenPages:%{public}s, enableHook:%{public}d, navId:%{public}s,"
        "navDepth:%{public}s, disablePlaceholder:%{public}d, disableDivider:%{public}d",
        isRouter, homePage.c_str(), FullScreenPageToString(config.fullScreenPages).c_str(), config.isArkUIHookEnabled,
        (config.navigationId.has_value() ? config.navigationId.value().c_str() : "NA"),
        (config.navigationDepth.has_value() ? std::to_string(config.navigationDepth.value()).c_str() : "NA"),
        config.navigationDisablePlaceholder, config.navigationDisableDivider);
}

void ForceSplitUtils::LogAppForceSplitConfig(bool isRouter, const ForceSplitConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "app ForceSplitConfig: isRouter:%{public}d, homePage:%{public}s, relatedPage:%{public}s, "
        "fullScreenPages:%{public}s, enableArkUIHook:%{public}d, navId:%{public}s,"
        "disablePlaceholder:%{public}d, disableDivider:%{public}d",
        isRouter, config.homePage.c_str(), config.relatedPage.c_str(),
        FullScreenPageToString(config.fullScreenPages).c_str(), config.isArkUIHookEnabled,
        (config.navigationId.has_value() ? config.navigationId.value().c_str() : "NA"),
        config.navigationDisablePlaceholder, config.navigationDisableDivider);
}
} // namespace OHOS::Ace::NG

