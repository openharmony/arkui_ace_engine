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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_UTILS_H

#include <unordered_map>
#include <unordered_set>

#include "core/components_ng/base/frame_node.h"
#include "core/common/force_split/force_split_constants.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class NavDestinationGroupNode;
class NavBarNode;

struct ForceSplitConfig {
    std::string homePage;
    std::string relatedPage;
    bool isArkUIHookEnabled = false;
    bool navigationDisablePlaceholder = false;
    bool navigationDisableDivider = false;
    bool dialogSupportSplit = true;
    std::optional<std::string> navigationId;
    std::optional<int32_t> navigationDepth;
    std::unordered_set<std::string> fullScreenPages;
    std::optional<float> wideSplitRatio;
    std::optional<float> squareSplitRatio;
    std::optional<Color> splitDividerColorLight;
    std::optional<Color> splitDividerColorDark;
    ForceSplitBehaviorMode behaviorMode = ForceSplitBehaviorMode::NAVIGATION;
    // For ForceSplitBehaviorMode::NAVIGATION, from -> to
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs;
    // For ForceSplitBehaviorMode::DISPLACE
    std::unordered_set<std::string> transPages;
};

class ForceSplitUtils {
public:
    static RefPtr<FrameNode> CreatePlaceHolderContent(const RefPtr<PipelineContext>& context);
    static RefPtr<NavDestinationGroupNode> CreateNavDestinationProxyNode();
    static bool IsHomePageNavDestination(const RefPtr<NavDestinationGroupNode>& node);
    static bool IsHomePageNavBar(const RefPtr<NavBarNode>& navBar);
    static RefPtr<FrameNode> CreatePlaceHolderNode();
    static bool ParseSystemForceSplitConfig(const std::string& configJsonStr, ForceSplitConfig& config);
    static bool ParseAppForceSplitConfig(bool isRouter, const std::string& configJsonStr, ForceSplitConfig& config);
    static void LogSystemForceSplitConfig(bool isRouter, const std::string& homePage, const ForceSplitConfig& config);
    static void LogAppForceSplitConfig(bool isRouter, const ForceSplitConfig& config);
private:
    static bool ParseCommonConfig(const std::unique_ptr<JsonValue>& configJson, ForceSplitConfig& config);
    static bool ParseNavigationOptions(const std::unique_ptr<JsonValue>& navigationOptions, ForceSplitConfig& config);
    static bool ParseFullScreenPages(const std::unique_ptr<JsonValue>& fullScreenPages, ForceSplitConfig& config);
    static bool ParseSplitDividerColor(const std::unique_ptr<JsonValue>& splitDividerColor, ForceSplitConfig& config);
    static bool ParseSplitParam(
        const std::unique_ptr<JsonValue>& split, const std::string& splitType, std::optional<float>& splitRatio);
    static bool ParsePagePairs(const std::unique_ptr<JsonValue>& pagePairs, ForceSplitConfig& config);
    static bool ParseTransPages(const std::unique_ptr<JsonValue>& transPages, ForceSplitConfig& config);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_UTILS_H
