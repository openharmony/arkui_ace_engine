/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H

enum class MenuPreviewMode {
    NONE,
    IMAGE,
    CUSTOM,
};

enum class MenuBindingType {
    LONG_PRESS,
    RIGHT_CLICK,
};

namespace OHOS::Ace::NG {

enum class HitTestMode {
    /**
     *  Both self and children respond to the hit test for touch events,
     *  but block hit test of the other nodes which is masked by this node.
     */
    HTMDEFAULT = 0,

    /**
     * Self respond to the hit test for touch events,
     * but block hit test of children and other nodes which is masked by this node.
     */
    HTMBLOCK,

    /**
     * Self and child respond to the hit test for touch events,
     * and allow hit test of other nodes which is masked by this node.
     */
    HTMTRANSPARENT,

    /**
     * Self not respond to the hit test for touch events,
     * but children respond to the hit test for touch events.
     */
    HTMNONE,

    /**
     * Self and child respond to the hit test for touch events,
     * when self consumed allow hit test of other nodes which is masked by this node,
     * when child consumed block hit test of other nodes.
     */
    HTMTRANSPARENT_SELF,
};

enum class TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION,
    FORWARD
};

enum class HitTestResult {
    // The touch point is located outside the current component area;
    OUT_OF_REGION,
    // node consumption events and prevent bubbling;
    STOP_BUBBLING,
    // node process events and bubble;
    BUBBLING,
    // node process events and bubble;
    SELF_TRANSPARENT,
};

enum class DragFuncType {
    DRAG_ENTER,
    DRAG_LEAVE,
    DRAG_MOVE,
    DRAG_DROP,
    DRAG_END,
};

enum class EventTreeType {
    TOUCH = 0,
    POST_EVENT,
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H
