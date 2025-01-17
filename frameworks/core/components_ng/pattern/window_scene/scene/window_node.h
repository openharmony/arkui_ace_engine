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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_NODE_H

#include "wm/wm_common.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WindowNode : public FrameNode {
    DECLARE_ACE_TYPE(WindowNode, FrameNode);

public:
    WindowNode(const std::string& tag,
        int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false);
    WindowNode(const std::string& tag,
        int32_t nodeId, int32_t sessionId, const RefPtr<Pattern>& pattern, bool isRoot, int32_t screenId);
    ~WindowNode() override;

    static RefPtr<WindowNode> GetOrCreateWindowNode(const std::string& tag,
        int32_t nodeId, int32_t sessionId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void SetParent(const WeakPtr<UINode>& parent, bool needDetect = true) override;
    bool IsOutOfTouchTestRegion(const PointF& parentLocalPoint, const TouchEvent& touchEvent,
        std::vector<RectF>* regionList = nullptr) override;
    std::vector<RectF> GetResponseRegionList(const RectF& rect, int32_t sourceType) override;

private:
    RectF ConvertHotRect(const RectF& rect, int32_t sourceType);
    bool IsOutOfHotAreas(const std::vector<Rosen::Rect>& hotAreas, const PointF& parentLocalPoint);
    std::vector<RectF> ConvertHotRects(const std::vector<Rosen::Rect>& hotAreas);

    int32_t sessionId_ = 0;
    int32_t screenId_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_NODE_H
