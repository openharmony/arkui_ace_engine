/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT TabContentNode : public FrameNode {
    DECLARE_ACE_TYPE(TabContentNode, FrameNode);

public:
    TabContentNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~TabContentNode() = default;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void OnAttachToMainTree(bool recursive) override;
    void OnDetachFromMainTree(bool recursive, PipelineContext* context = nullptr) override;

    void OnOffscreenProcess(bool recursive) override;

    static RefPtr<TabContentNode> GetOrCreateTabContentNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void ResetTabBarItemId()
    {
        tabBarItemId_.reset();
    }

    bool HasTabBarItemId() const
    {
        return tabBarItemId_.has_value();
    }

    int32_t GetTabBarItemId()
    {
        if (!tabBarItemId_.has_value()) {
            tabBarItemId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return tabBarItemId_.value();
    }

    void UpdataTabBarItem();

private:
    void ProcessTabBarItem();
    Axis GetTabBarAxis() const;
    std::string ConvertFlexAlignToString(FlexAlign verticalAlign) const;
    std::string ConvertLayoutModeToString(LayoutMode layoutMode) const;
    Dimension GetDefaultFontSize() const;

    std::optional<int32_t> tabBarItemId_;
    ACE_DISALLOW_COPY_AND_MOVE(TabContentNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H
