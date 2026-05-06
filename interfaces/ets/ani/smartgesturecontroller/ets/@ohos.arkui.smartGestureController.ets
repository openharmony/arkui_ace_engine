/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { SmartGestureAction, OperateIntention } from 'arkui.component.enums'

export default namespace smartGestureController {
    loadLibrary("smartGestureController_ani");

    export interface SmartGestureProposalRaw {
        action: SmartGestureAction;
        operateIntention?: OperateIntention;
        nodePtr?: long;
        pageCount?: int;
        distance?: double;
    }

    class SmartGestureProposalRawInner implements SmartGestureProposalRaw {
        action: SmartGestureAction = SmartGestureAction.NONE;
        operateIntention?: OperateIntention;
        nodePtr?: long;
        pageCount?: int;
        distance?: double;
    }

    export interface SmartGestureHandlingResolutionRaw {
        isConsumed: boolean;
        selectedProposal?: SmartGestureProposalRaw;
    }

    class SmartGestureHandlingResolutionRawInner implements SmartGestureHandlingResolutionRaw {
        isConsumed: boolean = false;
        selectedProposal?: SmartGestureProposalRaw;
    }

    export type SmartGestureMonitorRawCallback =
        (proposal: SmartGestureProposalRaw) => SmartGestureHandlingResolutionRaw;

    export native function enableSmartTapAndSlideGestures(enabled: boolean): void;
    export native function registerMonitor(callback: SmartGestureMonitorRawCallback): void;
    export native function unregisterMonitor(callback: SmartGestureMonitorRawCallback): void;
    export native function clearMonitors(): void;
    export native function requestSelected(id: string): void;
    export native function clearSelected(): void;
}
