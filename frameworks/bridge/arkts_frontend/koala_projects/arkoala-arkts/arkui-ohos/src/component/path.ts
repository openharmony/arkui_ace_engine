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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkPathPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkPathPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Path_construct(peerId, flags)
        const _peer  = new ArkPathPeer(_peerPtr, peerId, "Path", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPathOptionsAttribute(options?: PathOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writePathOptions(options_value)
        }
        ArkUIGeneratedNativeModule._PathInterface_setPathOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    commandsAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._PathAttribute_commands(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PathOptions {
    width?: number | string;
    height?: number | string;
    commands?: string;
}
export type PathInterface = (options?: PathOptions) => PathAttribute;
export interface PathAttribute extends CommonShapeMethod {
    commands(value: string | undefined): this
}
export class ArkPathStyle extends ArkCommonShapeMethodStyle implements PathAttribute {
    commands_value?: string | undefined
    public commands(value: string | undefined): this {
        return this
        }
}
export class ArkPathComponent extends ArkCommonShapeMethodComponent implements PathAttribute {
    getPeer(): ArkPathPeer {
        return (this.peer as ArkPathPeer)
    }
    public setPathOptions(options?: PathOptions): this {
        if (this.checkPriority("setPathOptions")) {
            const options_casted = options as (PathOptions | undefined)
            this.getPeer()?.setPathOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public commands(value: string | undefined): this {
        if (this.checkPriority("commands")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.commandsAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Path(
    /** @memo */
    style: ((attributes: PathAttribute) => void) | undefined,
    options?: PathOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkPathComponent()
    })
    NodeAttach<ArkPathPeer>((): ArkPathPeer => ArkPathPeer.create(receiver), (_: ArkPathPeer) => {
        receiver.setPathOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
