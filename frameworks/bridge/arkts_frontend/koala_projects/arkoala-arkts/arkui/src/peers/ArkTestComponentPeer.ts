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
import { InteropNativeModule, KPointer } from "@koalaui/interop"
import { ComponentBase } from "../ComponentBase"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "../generated/peers/ArkCommonPeer"
import { PeerNode } from "../PeerNode"
import { TestComponentOptions } from "../ArkTestComponent"

export class ArkTestComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTestComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Blank_construct(peerId, flags)
        const _peer  = new ArkTestComponentPeer(_peerPtr, peerId, "Blank", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTestComponentOptionsAttribute(option?: TestComponentOptions): void {
        if (option !== undefined) {
            this.setId(option!.id! as int32)
        }
    }
    onChangeCallback: Function0<void> | undefined = undefined
    onChangeAttribute(callback: Function0<void>): void {
        this.onChangeCallback = callback
    }
    logAttribute(message: string): void {
        InteropNativeModule._AppendGroupedLog(0, message + "\n")
    }
}
export interface ArkTestComponentAttributes extends ArkCommonMethodAttributes {
    onChange?: Function0<void>
}
