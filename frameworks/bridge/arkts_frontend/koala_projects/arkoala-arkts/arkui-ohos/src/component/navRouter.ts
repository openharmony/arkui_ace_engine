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
import { Callback_Boolean_Void } from "./navigation"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkNavRouterPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkNavRouterPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavRouter_construct(peerId, flags)
        const _peer  = new ArkNavRouterPeer(_peerPtr, peerId, "NavRouter", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavRouterOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._NavRouterInterface_setNavRouterOptions0(this.peer.ptr)
    }
    setNavRouterOptions1Attribute(value: RouteInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRouteInfo(value)
        ArkUIGeneratedNativeModule._NavRouterInterface_setNavRouterOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavRouterAttribute_onStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavRouteMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavRouteMode)
            thisSerializer.writeInt32(TypeChecker.NavRouteMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavRouterAttribute_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RouteInfo {
    name: string;
    param?: object;
}
export enum NavRouteMode {
    PUSH_WITH_RECREATE = 0,
    PUSH = 1,
    REPLACE = 2
}
export interface NavRouterAttribute extends CommonMethod {
    onStateChange(value: ((isVisible: boolean) => void) | undefined): this
    mode(value: NavRouteMode | undefined): this
}
export class ArkNavRouterStyle extends ArkCommonMethodStyle implements NavRouterAttribute {
    onStateChange_value?: ((isVisible: boolean) => void) | undefined
    mode_value?: NavRouteMode | undefined
    public onStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public mode(value: NavRouteMode | undefined): this {
        return this
        }
}
export class ArkNavRouterComponent extends ArkCommonMethodComponent implements NavRouterAttribute {
    getPeer(): ArkNavRouterPeer {
        return (this.peer as ArkNavRouterPeer)
    }
    public setNavRouterOptions(value?: RouteInfo): this {
        if (this.checkPriority("setNavRouterOptions")) {
            const value_type = runtimeType(value)
            this.getPeer()?.setNavRouterOptions0Attribute()
            return this
        }
        return this
    }
    public onStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavRouteMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavRouteMode | undefined)
            this.getPeer()?.modeAttribute(value_casted)
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
export function NavRouter(
    /** @memo */
    style: ((attributes: NavRouterAttribute) => void) | undefined,
    value?: RouteInfo,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkNavRouterComponent()
    })
    NodeAttach<ArkNavRouterPeer>((): ArkNavRouterPeer => ArkNavRouterPeer.create(receiver), (_: ArkNavRouterPeer) => {
        receiver.setNavRouterOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
