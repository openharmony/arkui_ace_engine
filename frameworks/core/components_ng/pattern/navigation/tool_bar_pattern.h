/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_PATTERN_H

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class NavToolbarPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(NavToolbarPattern, LinearLayoutPattern);

public:
    NavToolbarPattern() : LinearLayoutPattern(false) {};
    ~NavToolbarPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto toolbarLayoutAlgorithm = MakeRefPtr<ToolbarLayoutAlgorithm>();
        return toolbarLayoutAlgorithm;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_BOTTOM };
            host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }

        SetDefaultBackgroundColorIfNeeded(host);
    }

    void OnColorConfigurationUpdate() override;

    void SetToolbarOptions(NavigationToolbarOptions&& opt);

    RefPtr<FrameNode> GetDialogNode()
    {
        return dialogNode_;
    }

    void SetToolBarItemDialogNode(const RefPtr<FrameNode>& dialogNode)
    {
        dialogNode_ = dialogNode;
    }

private:
    void OnModifyDone() override;
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitDragEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleLongPressEvent(const GestureEvent& info);
    void HandleLongPressActionEnd();
    void ShowDialogWithNode(const RefPtr<BarItemNode>& barItemNode);

    void SetDefaultBackgroundColorIfNeeded(RefPtr<FrameNode>& host);
    void UpdateBackgroundStyle(RefPtr<FrameNode>& host);

    NavigationToolbarOptions options_;
    RefPtr<FrameNode> dialogNode_;
    std::optional<int32_t> moveIndex_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_PATTERN_H
