/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import { InteropNativeModule } from "@koalaui/interop"
import { ComponentBase } from "../ComponentBase"
import { TestComponentOptions } from "./TestComponent"
import { ArkCommonMethodPeer } from "../generated"
import { ArkUIGeneratedNativeModule } from "#components"
import { PeerNode } from "../PeerNode"
import { TEST_LOG_NUMBER } from "../Application"

export class TestComponentPeer extends ArkCommonMethodPeer {
    protected constructor(id: int32) {
        super(ArkUIGeneratedNativeModule._Stack_construct(0, 0), id)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): TestComponentPeer {
        const id = PeerNode.nextId()
        const peer  = new TestComponentPeer(id)
        component?.setPeer(peer)
        return peer
    }
    setTestComponentOptionsAttribute(option?: TestComponentOptions): void {
        if (option != undefined) {
            if (option.id != undefined) {
                this.setId(option.id as int32)
            }
            if (option.log != undefined) {
                this.logAttribute(option.log as string)
            }
            if (option.onChange != undefined) {
                this.onChangeAttribute(option.onChange as () => void)
            }
        }
    }
    onChangeCallback: (() => void) | undefined = undefined

    onChangeAttribute(callback: () => void): void {
        this.onChangeCallback = callback
    }
    logAttribute(message: string): void {
        if (true)
            InteropNativeModule._AppendGroupedLog(TEST_LOG_NUMBER, message + "\n")
        else
            console.log(message)
    }
}