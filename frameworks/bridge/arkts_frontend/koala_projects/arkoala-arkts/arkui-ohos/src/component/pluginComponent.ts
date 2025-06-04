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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VoidCallback } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkPluginComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkPluginComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PluginComponent_construct(peerId, flags)
        const _peer  = new ArkPluginComponentPeer(_peerPtr, peerId, "PluginComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPluginComponentOptionsAttribute(options: PluginComponentOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePluginComponentOptions(options)
        ArkUIGeneratedNativeModule._PluginComponentInterface_setPluginComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PluginComponentAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: PluginErrorCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PluginComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PluginComponentTemplate {
    source: string;
    bundleName: string;
}
export interface PluginComponentOptions {
    template: PluginComponentTemplate;
    data: Object | undefined | null;
}
export interface PluginErrorData {
    errcode: number;
    msg: string;
}
export type PluginErrorCallback = (info: PluginErrorData) => void;
export type PluginComponentInterface = (options: PluginComponentOptions) => PluginComponentAttribute;
export interface PluginComponentAttribute extends CommonMethod {
    onComplete(value: VoidCallback | undefined): this
    onError(value: PluginErrorCallback | undefined): this
}
export class ArkPluginComponentStyle extends ArkCommonMethodStyle implements PluginComponentAttribute {
    onComplete_value?: VoidCallback | undefined
    onError_value?: PluginErrorCallback | undefined
    public onComplete(value: VoidCallback | undefined): this {
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        return this
        }
}
export class ArkPluginComponentComponent extends ArkCommonMethodComponent implements PluginComponentAttribute {
    getPeer(): ArkPluginComponentPeer {
        return (this.peer as ArkPluginComponentPeer)
    }
    public setPluginComponentOptions(options: PluginComponentOptions): this {
        if (this.checkPriority("setPluginComponentOptions")) {
            const options_casted = options as (PluginComponentOptions)
            this.getPeer()?.setPluginComponentOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public onComplete(value: VoidCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (PluginErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
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
export function PluginComponent(
    /** @memo */
    style: ((attributes: PluginComponentAttribute) => void) | undefined,
    options: PluginComponentOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkPluginComponentComponent()
    })
    NodeAttach<ArkPluginComponentPeer>((): ArkPluginComponentPeer => ArkPluginComponentPeer.create(receiver), (_: ArkPluginComponentPeer) => {
        receiver.setPluginComponentOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
