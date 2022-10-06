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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_VIEW_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/panel/sliding_panel_event_hub.h"
#include "core/components_ng/pattern/panel/sliding_panel_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SlidingPanelView {
public:
    static void Create();
    static void SetPanelType(PanelType type);
    static void SetPanelMode(PanelMode mode);
    static void SetHasDragBar(bool hasDragBar);
    static void SetMiniHeight(const Dimension& miniHeight);
    static void SetHalfHeight(const Dimension& halfHeight);
    static void SetFullHeight(const Dimension& fullHeight);
    static void SetBackgroundColor(Color backgroundColor);
    static void SetOnChange(ChangeEvent&& onChange);
    static void SetOnHeightChange(HeightChangeEvent&& onHeightChange);
    static void Pop();

private:
    static RefPtr<SlidingPanelNode> GetOrCreateSlidingPanelNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    static RefPtr<LinearLayoutProperty> GetLinearLayoutProperty();

    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelView);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_VIEW_H