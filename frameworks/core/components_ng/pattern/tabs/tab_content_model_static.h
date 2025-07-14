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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_STATIC_H

#include <functional>
#include <string>

#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"

namespace OHOS::Ace::NG {

using TabBarBuilderFunc = std::function<void()>;

class ACE_EXPORT TabContentModelStatic {
public:
    static void SetIndicator(FrameNode* frameNode, const std::optional<IndicatorStyle>& indicatorOpt);
    static void SetLabelStyle(FrameNode* frameNode, const std::optional<LabelStyle>& labelStyleOpt);
    static void SetSelectedMode(FrameNode* node, const std::optional<SelectedMode>& selectedMode);
    static void SetBoard(FrameNode* node, const std::optional<BoardStyle>& board);
    static void SetPadding(FrameNode* node, const std::optional<NG::PaddingProperty>& padding);
    static void SetUseLocalizedPadding(FrameNode* node, bool useLocalizedPadding);
    static void SetId(FrameNode* node, const std::optional<std::string>& id);
    static void SetTabBarStyle(FrameNode* node, TabBarStyle tabBarStyle);
    static void SetTabBar(FrameNode* node,
        const std::optional<std::string>& label, const std::optional<std::string>& icon, TabBarBuilderFunc&& builder);
    static void SetLayoutMode(FrameNode* node, const std::optional<LayoutMode>& layoutMode);
    static void SetVerticalAlign(FrameNode* node, const std::optional<FlexAlign>& verticalAlign);
    static void SetSymmetricExtensible(FrameNode* node, const std::optional<bool>& isExtensible);
    static void SetIconStyle(FrameNode* node, const std::optional<IconStyle>& iconStyle);
    static void SetOnWillShow(FrameNode* node, std::function<void()>&& onWillShow);
    static void SetOnWillHide(FrameNode* node, std::function<void()>&& onWillHide);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_STATIC_H