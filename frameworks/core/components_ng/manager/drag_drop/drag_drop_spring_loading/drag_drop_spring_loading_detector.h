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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_DETECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_DETECTOR_H

#include <string>

#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class DragDropSpringLoadingStateMachine;

struct SpringLoadingParams {
    Point movePoint = Point(0, 0);
    RefPtr<FrameNode> dragFrameNode = nullptr;
    uint64_t curTimeStamp = 0;
    std::string extraInfo = "";
    SpringLoadingParams(Point movePoint, RefPtr<FrameNode> dragFrameNode, uint64_t curTimeStamp, std::string extraInfo)
        : movePoint(movePoint), dragFrameNode(dragFrameNode), curTimeStamp(curTimeStamp), extraInfo(extraInfo)
    {}
    SpringLoadingParams() {};
};

class DragDropSpringLoadingDetector : public AceType {
    DECLARE_ACE_TYPE(DragDropSpringLoadingDetector, AceType);

public:
    DragDropSpringLoadingDetector();
    ~DragDropSpringLoadingDetector() override = default;

    void NotifyMove(const SpringLoadingParams& params);

    void NotifyIntercept(std::string_view extraInfo);

    const Point& GetPoint()
    {
        return preMovePoint_;
    }

    const RefPtr<FrameNode>& GetFrameNode()
    {
        return preTargetFrameNode_;
    }

private:
    bool IsMovementExceedThreshold(uint64_t curTimeStamp, Point curMovePoint);

    void Intercept(std::string extraInfo);

    void ResetState();

    Point preMovePoint_ = Point(0, 0);
    uint64_t preTimeStamp_ = 0;
    RefPtr<FrameNode> preTargetFrameNode_ = nullptr;
    RefPtr<DragDropSpringLoadingStateMachine> stateMachine_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_DETECTOR_H