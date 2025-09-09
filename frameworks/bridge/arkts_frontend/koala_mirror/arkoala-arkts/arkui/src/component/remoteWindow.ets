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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRemoteWindowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRemoteWindowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RemoteWindow_construct(peerId, flags)
        const _peer  = new ArkRemoteWindowPeer(_peerPtr, peerId, "RemoteWindow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRemoteWindowOptionsAttribute(target: WindowAnimationTarget): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WindowAnimationTarget_serializer.write(thisSerializer, target)
        ArkUIGeneratedNativeModule._RemoteWindowInterface_setRemoteWindowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RRect {
    left: number;
    top: number;
    width: number;
    height: number;
    radius: number;
}
export interface WindowAnimationTarget {
    readonly bundleName: string;
    readonly abilityName: string;
    readonly windowBounds: RRect;
    readonly missionId: number;
}
export interface RemoteWindowAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRemoteWindowStyle extends ArkCommonMethodStyle implements RemoteWindowAttribute {
    attributeModifier_value?: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RemoteWindowAttribute): void {
        super.apply(target)
    }
}

export class ArkRemoteWindowComponent extends ArkCommonMethodComponent implements RemoteWindowAttribute {
    getPeer(): ArkRemoteWindowPeer {
        return (this.peer as ArkRemoteWindowPeer)
    }
    public setRemoteWindowOptions(target: WindowAnimationTarget): this {
        if (this.checkPriority("setRemoteWindowOptions")) {
            const target_casted = target as (WindowAnimationTarget)
            this.getPeer()?.setRemoteWindowOptionsAttribute(target_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRemoteWindowStyle(receiver: RemoteWindowAttribute, modifier: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRemoteWindowStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("RemoteWindow")
// export function RemoteWindow(
//     target: WindowAnimationTarget,
//     @memo
//     content_?: () => void,
// ): RemoteWindowAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function RemoteWindow(
    @memo
    style: ((attributes: RemoteWindowAttribute) => void) | undefined,
    target: WindowAnimationTarget,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRemoteWindowComponent>((): ArkRemoteWindowComponent => {
        return new ArkRemoteWindowComponent()
    })
    NodeAttach<ArkRemoteWindowPeer>((): ArkRemoteWindowPeer => ArkRemoteWindowPeer.create(receiver), (_: ArkRemoteWindowPeer): void => {
        receiver.setRemoteWindowOptions(target)
        style?.(receiver)
        withRemoteWindowStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRemoteWindowSet extends ArkCommonMethodSet implements RemoteWindowAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: RemoteWindowAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RRect_serializer {
    public static write(buffer: SerializerBase, value: RRect): void {
        let valueSerializer : SerializerBase = buffer
        const value_left  = value.left
        valueSerializer.writeNumber(value_left)
        const value_top  = value.top
        valueSerializer.writeNumber(value_top)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
        const value_radius  = value.radius
        valueSerializer.writeNumber(value_radius)
    }
    public static read(buffer: DeserializerBase): RRect {
        let valueDeserializer : DeserializerBase = buffer
        const left_result : number = (valueDeserializer.readNumber() as number)
        const top_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        const radius_result : number = (valueDeserializer.readNumber() as number)
        let value : RRect = ({left: left_result, top: top_result, width: width_result, height: height_result, radius: radius_result} as RRect)
        return value
    }
}
export class WindowAnimationTarget_serializer {
    public static write(buffer: SerializerBase, value: WindowAnimationTarget): void {
        let valueSerializer : SerializerBase = buffer
        const value_bundleName  = value.bundleName
        valueSerializer.writeString(value_bundleName)
        const value_abilityName  = value.abilityName
        valueSerializer.writeString(value_abilityName)
        const value_windowBounds  = value.windowBounds
        RRect_serializer.write(valueSerializer, value_windowBounds)
        const value_missionId  = value.missionId
        valueSerializer.writeNumber(value_missionId)
    }
    public static read(buffer: DeserializerBase): WindowAnimationTarget {
        let valueDeserializer : DeserializerBase = buffer
        const bundleName_result : string = (valueDeserializer.readString() as string)
        const abilityName_result : string = (valueDeserializer.readString() as string)
        const windowBounds_result : RRect = RRect_serializer.read(valueDeserializer)
        const missionId_result : number = (valueDeserializer.readNumber() as number)
        let value : WindowAnimationTarget = ({bundleName: bundleName_result, abilityName: abilityName_result, windowBounds: windowBounds_result, missionId: missionId_result} as WindowAnimationTarget)
        return value
    }
}
