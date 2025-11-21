/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import {
    __memo_context_type as __memo_context_type,
    __memo_id_type as __memo_id_type,
} from 'arkui.incremental.runtime.state';
import { PeerNode } from 'arkui/PeerNode';
// import { AnimateParam, UIGestureEvent } from "./component";
export declare class ComponentBase {
    protected peer?: PeerNode | undefined;
    protected isFirstBuild: boolean;
    // protected gestureEvent: UIGestureEvent | undefined;
    setPeer(peer: PeerNode): void;
    // setGestureEvent(gestureEvent: UIGestureEvent): void;
    protected checkPriority(name: string): boolean;
    applyAttributesFinish(): void;
    applyAttributes(attrs: Object): void;
    // animationStart(param: AnimateParam): this;
    animationEnd(): this;
    __applyStyle<T extends ComponentBase, A>(
        __memo_context: __memo_context_type,
        __memo_id: __memo_id_type,
        func: (__memo_context: __memo_context_type, __memo_id: __memo_id_type, instance: T, arg: A) => T,
        arg: A
    ): T;
    __applyAnimatableExtend<T extends ComponentBase, A>(
        __memo_context: __memo_context_type,
        __memo_id: __memo_id_type,
        func: (__memo_context: __memo_context_type, __memo_id: __memo_id_type, instance: T, arg: A) => T,
        arg: A
    ): T;
}
