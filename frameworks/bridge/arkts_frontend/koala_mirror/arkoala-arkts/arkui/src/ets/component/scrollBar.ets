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
import { Scroller, Scroller_serializer } from "./scroll"
import { BarState } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkScrollBarPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollBarPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ScrollBar_construct(peerId, flags)
        const _peer  = new ArkScrollBarPeer(_peerPtr, peerId, "ScrollBar", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScrollBarOptionsAttribute(value: ScrollBarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ScrollBarOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._ScrollBarInterface_setScrollBarOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNestedScrollAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollBarAttribute_setEnableNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ScrollBarDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1
}
export interface ScrollBarOptions {
    scroller: Scroller;
    direction?: ScrollBarDirection;
    state?: BarState;
}
export interface ScrollBarAttribute extends CommonMethod {
    enableNestedScroll(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableNestedScroll")
    }
    attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkScrollBarStyle extends ArkCommonMethodStyle implements ScrollBarAttribute {
    enableNestedScroll_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined
    public enableNestedScroll(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ScrollBarAttribute): void {
        super.apply(target)
        if (this.enableNestedScroll_value !== undefined)
            target.enableNestedScroll(this.enableNestedScroll_value!)
    }
}

export class ArkScrollBarComponent extends ArkCommonMethodComponent implements ScrollBarAttribute {
    getPeer(): ArkScrollBarPeer {
        return (this.peer as ArkScrollBarPeer)
    }
    public setScrollBarOptions(value: ScrollBarOptions): this {
        if (this.checkPriority("setScrollBarOptions")) {
            const value_casted = value as (ScrollBarOptions)
            this.getPeer()?.setScrollBarOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNestedScroll(value: boolean | undefined): this {
        if (this.checkPriority("enableNestedScroll")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withScrollBarStyle(receiver: ScrollBarAttribute, modifier: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkScrollBarStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ScrollBar")
// export function ScrollBar(
//     value: ScrollBarOptions,
//     @memo
//     content_?: () => void,
// ): ScrollBarAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ScrollBar(
    @memo
    style: ((attributes: ScrollBarAttribute) => void) | undefined,
    value: ScrollBarOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkScrollBarComponent>((): ArkScrollBarComponent => {
        return new ArkScrollBarComponent()
    })
    NodeAttach<ArkScrollBarPeer>((): ArkScrollBarPeer => ArkScrollBarPeer.create(receiver), (_: ArkScrollBarPeer): void => {
        receiver.setScrollBarOptions(value)
        style?.(receiver)
        withScrollBarStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkScrollBarSet extends ArkCommonMethodSet implements ScrollBarAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _enableNestedScroll_flag?: boolean
    _enableNestedScroll0_value?: boolean | undefined
    applyModifierPatch(component: ScrollBarAttribute): void {
        if (this._enableNestedScroll_flag)
            component.enableNestedScroll((this._enableNestedScroll0_value as boolean | undefined))
    }
    public enableNestedScroll(value: boolean | undefined): this {
        this._enableNestedScroll_flag = true
        this._enableNestedScroll0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ScrollBarOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_scroller  = value.scroller
        Scroller_serializer.write(valueSerializer, value_scroller)
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as ScrollBarDirection)
            valueSerializer.writeInt32(TypeChecker.ScrollBarDirection_ToNumeric(value_direction_value))
        }
        const value_state  = value.state
        let value_state_type : int32 = RuntimeType.UNDEFINED
        value_state_type = runtimeType(value_state)
        valueSerializer.writeInt8((value_state_type).toChar())
        if ((value_state_type) != (RuntimeType.UNDEFINED)) {
            const value_state_value  = (value_state as BarState)
            valueSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_state_value))
        }
    }
    public static read(buffer: DeserializerBase): ScrollBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scroller_result : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : ScrollBarDirection | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.ScrollBarDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : ScrollBarDirection | undefined = direction_buf
        const state_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let state_buf : BarState | undefined
        if ((state_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            state_buf = TypeChecker.BarState_FromNumeric(valueDeserializer.readInt32())
        }
        const state_result : BarState | undefined = state_buf
        let value : ScrollBarOptions = ({scroller: scroller_result, direction: direction_result, state: state_result} as ScrollBarOptions)
        return value
    }
}
