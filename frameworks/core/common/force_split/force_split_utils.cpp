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
#include "core/components_ng/manager/force_split/force_split_manager.h"

#include <string>
#include <vector>
#include "ui/base/utils/utils.h"

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/common/force_split/force_split_constants.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"

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
constexpr char ENABLE_HOOK_KEY[] = "enableReducedContainerSize";
constexpr char HOME_NAVIGATION_ID_KEY[] = "homeNavigationId";
constexpr char HOME_NAVIGATION_DEPTH_KEY[] = "homeNavigationDepth";
constexpr char NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY[] = "navigationDisablePlaceholder";
constexpr char NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY[] = "navigationDisableDivider";
constexpr char FULL_SCREEN_PAGES_KEY[] = "fullScreenPages";
constexpr char DIALOG_SUPPORT_SPLIT_KEY[] = "dialogSupportSplit";
constexpr char SPLIT_DIVIDER_COLOR[] = "splitDividerColor";
constexpr char COLOR_LIGHT[] = "light";
constexpr char COLOR_DARK[] = "dark";
constexpr char WIDE_SPLIT_KEY[] = "wideSplit";
constexpr char SQUARE_SPLIT_KEY[] = "squareSplit";
constexpr char RATIO_KEY[] = "ratio";
constexpr char IS_DRAGGABLE_KEY[] = "isDraggable";
constexpr char BEHAVIOR_MODE_KEY[] = "mode";
constexpr char PAGE_PAIRS_KEY[] = "pagePairs";
constexpr char TRANS_PAGES_KEY[] = "transPages";
constexpr int DISPLACE_BEHAVIOR_MODE = 0;
constexpr int NAVIGATION_BEHAVIOR_MODE = 1;

std::string JoinStringSet(const std::unordered_set<std::string>& strSet)
{
    std::string str("[");
    int32_t idx = 0;
    for (const auto& item : strSet) {
        if (idx != 0) {
            str.append(", ");
        }
        str.append(item);
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

bool ForceSplitUtils::ParseFullScreenPages(const std::unique_ptr<JsonValue>& fullScreenPages, ForceSplitParam& config)
{
    if (!fullScreenPages || !fullScreenPages->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, fullScreenPages is an invalid json array!");
        return false;
    }
    std::unordered_set<std::string> pageSet;
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

bool ForceSplitUtils::ParseSplitDividerColor(const std::unique_ptr<JsonValue>& splitDividerColor,
    ForceSplitParam& config)
{
    if (!splitDividerColor || !splitDividerColor->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, splitDividerColor is an invalid json object!");
        return false;
    }
    if (splitDividerColor->Contains(COLOR_LIGHT)) {
        auto lightColorValue = splitDividerColor->GetValue(COLOR_LIGHT);
        if (!lightColorValue->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, splitDividerColor.light is not color!");
            return false;
        }
        config.splitDividerColorLight = Color::FromString(lightColorValue->GetString());
    }
    if (splitDividerColor->Contains(COLOR_DARK)) {
        auto darkColorValue = splitDividerColor->GetValue(COLOR_DARK);
        if (!darkColorValue->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, splitDividerColor.dark is not color!");
            return false;
        }
        config.splitDividerColorDark = Color::FromString(darkColorValue->GetString());
    }
    return true;
}

bool ForceSplitUtils::ParseSplitParam(const std::unique_ptr<JsonValue>& split, const std::string& splitType,
                                      std::optional<float>& splitRatio, bool& isDraggable)
{
    splitRatio = std::nullopt;
    if (!split || !split->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is an invalid json Object!", splitType.c_str());
        return false;
    }
    if (!split->Contains(RATIO_KEY) && !split->Contains(IS_DRAGGABLE_KEY)) {
        return true;
    }
    if (split->Contains(IS_DRAGGABLE_KEY)) {
        isDraggable = split->GetBool(IS_DRAGGABLE_KEY, false);
    }
    if (isDraggable) {
        return true;
    }
    auto ratioJson = split->GetValue(RATIO_KEY);
    if (!ratioJson || !ratioJson->IsString()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, %{public}s must be type of string!", RATIO_KEY);
        return false;
    }
    auto ratioStr = ratioJson->GetString();
    auto pos = ratioStr.find('|');
    if (pos == std::string::npos) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, Invalid %{public}s format value: %{public}s, expected format "
            "\"<integer number> | <integer number>\"", RATIO_KEY, ratioStr.c_str());
        return false;
    }
    auto primaryStr = ratioStr.substr(0, pos);
    auto secondaryStr = ratioStr.substr(pos + 1);
    auto primaryValue = StringUtils::StringToInt(primaryStr);
    auto secondaryValue = StringUtils::StringToInt(secondaryStr);
    if (primaryValue <= 0 || secondaryValue <= 0 || (primaryValue + secondaryValue <= 0)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, Invalid %{public}s value: %{public}s", RATIO_KEY, ratioStr.c_str());
        return false;
    }
    auto ratio = 1.0f * secondaryValue / (primaryValue + secondaryValue);
    if (ratio < MIN_SPLIT_RATIO || ratio > MAX_SPLIT_RATIO) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "%{public}s: %{public}f must belong to range[1/3, 2/3]", RATIO_KEY, ratio);
    }
    splitRatio = std::clamp(ratio, MIN_SPLIT_RATIO, MAX_SPLIT_RATIO);
    return true;
}

bool ForceSplitUtils::ParsePagePairs(const std::unique_ptr<JsonValue>& pagePairs, ForceSplitParam& config)
{
    if (!pagePairs || !pagePairs->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is an invalid json array!", PAGE_PAIRS_KEY);
        return false;
    }
    config.pagePairs.clear();
    std::unordered_set<std::string> fromToAnyPageSet;
    int32_t itemSize = pagePairs->GetArraySize();
    for (int32_t idx = 0; idx < itemSize; ++idx) {
        auto item = pagePairs->GetArrayItem(idx);
        if (!item || !item->IsObject()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s's item is not a object!", PAGE_PAIRS_KEY);
            continue;
        }
        if (!item->Contains("from") || !item->Contains("to")) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s's item must contain from & to", PAGE_PAIRS_KEY);
            continue;
        }
        auto fromJson = item->GetValue("from");
        auto toJson = item->GetValue("to");
        if (!fromJson || !fromJson->IsString() || !toJson || !toJson->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s's from & to must be type of string!",
                PAGE_PAIRS_KEY);
            continue;
        }
        auto from = fromJson->GetString();
        auto to = toJson->GetString();
        if (from.empty() || to.empty()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s's from & to can not be empty string!",
                PAGE_PAIRS_KEY);
            continue;
        }
        auto it = config.pagePairs.find(from);
        if (it == config.pagePairs.end()) {
            std::unordered_set<std::string> set;
            config.pagePairs.emplace(from, set);
        }
        if (to == "*") {
            config.pagePairs[from].clear();
            fromToAnyPageSet.emplace(from);
        } else if (fromToAnyPageSet.find(from) == fromToAnyPageSet.end()) {
            config.pagePairs[from].emplace(to);
        }
    }
    return true;
}

bool ForceSplitUtils::ParseTransPages(const std::unique_ptr<JsonValue>& transPages, ForceSplitParam& config)
{
    if (!transPages || !transPages->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, transPages is an invalid json array!");
        return false;
    }
    config.transPages.clear();
    int32_t itemSize = transPages->GetArraySize();
    for (int32_t idx = 0; idx < itemSize; ++idx) {
        auto item = transPages->GetArrayItem(idx);
        if (!item || !item->IsString()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, transPages item is not a string!");
            continue;
        }
        auto page = item->GetString();
        if (!page.empty()) {
            config.transPages.emplace(page);
        }
    }
    return true;
}

bool ForceSplitUtils::ParseCommonConfig(const std::unique_ptr<JsonValue>& configJson, ForceSplitParam& config)
{
    if (!configJson) {
        return false;
    }
    config.dialogSupportSplit = configJson->GetBool(DIALOG_SUPPORT_SPLIT_KEY, true);
    if (configJson->Contains(FULL_SCREEN_PAGES_KEY)) {
        if (!ParseFullScreenPages(configJson->GetValue(FULL_SCREEN_PAGES_KEY), config)) {
            return false;
        }
    }
    if (configJson->Contains(SPLIT_DIVIDER_COLOR)) {
        if (!ParseSplitDividerColor(configJson->GetValue(SPLIT_DIVIDER_COLOR), config)) {
            return false;
        }
    }
    if (configJson->Contains(WIDE_SPLIT_KEY)) {
        if (!ParseSplitParam(configJson->GetValue(WIDE_SPLIT_KEY), WIDE_SPLIT_KEY, config.wideSplitRatio,
                             config.wideSplitIsDraggable)) {
            return false;
        }
    }
    if (configJson->Contains(SQUARE_SPLIT_KEY)) {
        if (!ParseSplitParam(configJson->GetValue(SQUARE_SPLIT_KEY), SQUARE_SPLIT_KEY, config.squareSplitRatio,
                             config.squareSplitIsDraggable)) {
            return false;
        }
    }
    if (configJson->Contains(BEHAVIOR_MODE_KEY)) {
        auto modeJson = configJson->GetValue(BEHAVIOR_MODE_KEY);
        if (!modeJson || !modeJson->IsNumber()) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, %{public}s must be type of number!", BEHAVIOR_MODE_KEY);
            return false;
        }
        auto modeValue = modeJson->GetInt();
        if (modeValue != DISPLACE_BEHAVIOR_MODE && modeValue != NAVIGATION_BEHAVIOR_MODE) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "invalid behavior mode value: %{public}d", modeValue);
            return false;
        }
        config.behaviorMode = modeValue == DISPLACE_BEHAVIOR_MODE ?
            ForceSplitBehaviorMode::DISPLACE : ForceSplitBehaviorMode::NAVIGATION;
    }
    return ParseBehaviorModeConfig(configJson, config);
}

bool ForceSplitUtils::ParseBehaviorModeConfig(
    const std::unique_ptr<JsonValue>& configJson, ForceSplitParam& config)
{
    if (!configJson) {
        return false;
    }
    if (config.behaviorMode == ForceSplitBehaviorMode::NAVIGATION && configJson->Contains(PAGE_PAIRS_KEY)) {
        if (!ParsePagePairs(configJson->GetValue(PAGE_PAIRS_KEY), config)) {
            return false;
        }
    }
    if (config.behaviorMode == ForceSplitBehaviorMode::DISPLACE && configJson->Contains(TRANS_PAGES_KEY)) {
        if (!ParseTransPages(configJson->GetValue(TRANS_PAGES_KEY), config)) {
            return false;
        }
    }
    return true;
}

bool ForceSplitUtils::ParseForceSplitParam(
    bool isRouterSplit, const std::string& configJsonStr, ForceSplitParam& config)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "parse forceSplit config: %{public}s", configJsonStr.c_str());
    if (configJsonStr.empty()) {
        return true;
    }
    auto configJson = JsonUtil::ParseJsonString(configJsonStr);
    if (!configJson) {
        return false;
    }
    if (!configJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Error, ArkUIOption is an invalid json object!");
        return false;
    }
    config.isArkUIHookEnabled = configJson->GetBool(ENABLE_HOOK_KEY, false);
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
    if (!ParseCommonConfig(configJson, config)) {
        return false;
    }
    if (isRouterSplit) {
        return true;
    }
    return ParseNavigationOptions(configJson, config);
}

bool ForceSplitUtils::ParseNavigationOptions(
    const std::unique_ptr<JsonValue>& configJson, ForceSplitParam& config)
{
    if (!configJson) {
        return false;
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
    if (configJson->Contains(HOME_NAVIGATION_DEPTH_KEY)) {
        auto depthJson = configJson->GetValue(HOME_NAVIGATION_DEPTH_KEY);
        if (!depthJson->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Error, %{public}s is not number!", HOME_NAVIGATION_DEPTH_KEY);
            return false;
        }
        config.navigationDepth = configJson->GetInt(HOME_NAVIGATION_DEPTH_KEY);
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

void ForceSplitUtils::LogForceSplitParam(bool isRouterSplit, const ForceSplitParam& config)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "ForceSplitParam: isRouterSplit:%{public}d, homePage:%{public}s, relatedPage:%{public}s, "
        "fullScreenPages:%{public}s, enableArkUIHook:%{public}d, navId:%{public}s,"
        "navDepth:%{public}s, disablePlaceholder:%{public}d, disableDivider:%{public}d, "
        "dividerColorLight:%{public}s, dividerColorDark:%{public}s, "
        "wideSplit[ratio:%{public}s, isDraggable:%{public}d], squareSplit[ratio:%{public}s, isDraggable:%{public}d], "
        "behaviorMode:%{public}d, transPages:%{public}s",
        isRouterSplit, config.homePage.c_str(), config.relatedPage.c_str(),
        JoinStringSet(config.fullScreenPages).c_str(), config.isArkUIHookEnabled,
        (config.navigationId.has_value() ? config.navigationId.value().c_str() : "NA"),
        (config.navigationDepth.has_value() ? std::to_string(config.navigationDepth.value()).c_str() : "NA"),
        config.navigationDisablePlaceholder, config.navigationDisableDivider,
        (config.splitDividerColorLight.has_value() ?  config.splitDividerColorLight.value().ToString().c_str() : "NA"),
        (config.splitDividerColorDark.has_value() ?  config.splitDividerColorDark.value().ToString().c_str() : "NA"),
        (config.wideSplitRatio.has_value() ? std::to_string(config.wideSplitRatio.value()).c_str() : "NA"),
        config.wideSplitIsDraggable,
        (config.squareSplitRatio.has_value() ? std::to_string(config.squareSplitRatio.value()).c_str() : "NA"),
        config.squareSplitIsDraggable,
        static_cast<int32_t>(config.behaviorMode), JoinStringSet(config.transPages).c_str());
}
} // namespace OHOS::Ace::NG

