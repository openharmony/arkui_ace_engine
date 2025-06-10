/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { ArkoalaControl } from "./Declarations"

// This is a workaround for ArkTS compiler bug.
type lambda = (args: Object) => void

export class ArkoalaControlImpl implements ArkoalaControl {
    private listeners: Map<string, Array<(args: Object) => void>> = new Map()

    constructor() {}

    sendMessage(topic: string, event: Object): void {
        const handlers = this.listeners.get(topic)
        if (handlers) {
            for (let i = 0; i < handlers.length; i++) {
                handlers[i](event)
            }
        }
    }
    addListener(topic: string, handler: (args: Object) => void): void {
        let listeners = this.listeners.get(topic)
        if (!listeners) {
            listeners = new Array<lambda>()
            this.listeners.set(topic, listeners)
        }
        listeners.push(handler)
    }
}
