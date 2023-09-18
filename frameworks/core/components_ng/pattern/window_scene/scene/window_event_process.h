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

#ifndef OHOS_ACE_NG_WINDOW_SCENE_WINDOW_EVENT_PROCESS_H
#define OHOS_ACE_NG_WINDOW_SCENE_WINDOW_EVENT_PROCESS_H

#include "singleton.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "session/host/include/session.h"

namespace OHOS::Ace::NG {
class WindowEventProcess {
    DECLARE_DELAYED_SINGLETON(WindowEventProcess);
public:
    DISALLOW_COPY_AND_MOVE(WindowEventProcess);
    void ProcessWindowMouseEvent(int32_t nodeId, sptr<Rosen::Session> session,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void ProcessWindowDragEvent(int32_t nodeId, sptr<Rosen::Session> session,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void CleanWindowDragEvent();

private:
    void UpdateWindowMouseRecord(int32_t nodeId, sptr<Rosen::Session> session,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void CleanWindowMouseRecord();
    void ProcessEnterLeaveEvent(int32_t nodeId, sptr<Rosen::Session> session,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void DispatchPointerEvent(sptr<Rosen::Session> session,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
private:
    int32_t lastWindowNodeId_ { -1 };
    wptr<Rosen::Session> lastWeakSession_ { nullptr };
    std::shared_ptr<MMI::PointerEvent> lastPointEvent_ { nullptr };

    int32_t lastDragWindowNodeId_  { -1 };
    wptr<Rosen::Session> lastDragSession_ { nullptr };
    std::shared_ptr<MMI::PointerEvent> lastDragPointEvent_ { nullptr };
};
} // namespace OHOS::Ace::NG
#endif // OHOS_ACE_NG_WINDOW_SCENE_WINDOW_EVENT_PROCESS_H
