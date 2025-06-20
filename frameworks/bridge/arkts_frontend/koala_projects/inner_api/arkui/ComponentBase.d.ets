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

import { PeerNode } from 'arkui.PeerNode';
// import { AnimateParam, UIGestureEvent } from "arkui.component"

export declare class ComponentBase {
    protected peer?: PeerNode;
    protected isFirstBuild: boolean;
    /** @memo */
    public __applyStyle<T extends ComponentBase, A>(
        /** @memo */
        func: (instance: T, arg: A) => T, // should be ...args: A[], but that doesn't currently compile
        arg: A
    ): T;
    /** @memo */
    public __applyAnimatableExtend<T extends ComponentBase, A>(
        /** @memo */
        func: (instance: T, arg: A) => T,
        arg: A
    ): T;
}
