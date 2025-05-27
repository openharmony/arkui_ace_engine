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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Boolean_Void } from "./navigation"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkNavRouterPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavRouterPeer {
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
    onStateChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavRouterAttribute_onStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavRouteMode): void {
        ArkUIGeneratedNativeModule._NavRouterAttribute_mode(this.peer.ptr, TypeChecker.NavRouteMode_ToNumeric(value))
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
    onStateChange(value: ((isVisible: boolean) => void)): this
    mode(value: NavRouteMode): this
    attributeModifier(value: AttributeModifier<NavRouterAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UINavRouterAttribute extends UICommonMethod {
    /** @memo */
    onStateChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    mode(value: NavRouteMode): this
    /** @memo */
    attributeModifier(value: AttributeModifier<NavRouterAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkNavRouterStyle extends ArkCommonMethodStyle implements NavRouterAttribute {
    onStateChange_value?: ((isVisible: boolean) => void)
    mode_value?: NavRouteMode
    public onStateChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public mode(value: NavRouteMode): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavRouterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkNavRouterComponent extends ArkCommonMethodComponent implements UINavRouterAttribute {
    getPeer(): ArkNavRouterPeer {
        return (this.peer as ArkNavRouterPeer)
    }
    /** @memo */
    public setNavRouterOptions(value?: RouteInfo): this {
        if (this.checkPriority("setNavRouterOptions")) {
            const value_type = runtimeType(value)
            this.getPeer()?.setNavRouterOptions0Attribute()
            return this
        }
        return this
    }
    /** @memo */
    public onStateChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: NavRouteMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavRouteMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<NavRouterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkNavRouter(
    /** @memo */
    style: ((attributes: UINavRouterAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value?: RouteInfo,
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
