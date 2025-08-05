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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Scroller, Scroller_serializer } from "./scroll"
import { BarState } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkScrollBarPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollBarPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ScrollBar_construct(peerId, flags)
        const _peer  = new ArkScrollBarPeer(_peerPtr, peerId, 'ScrollBar', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ScrollBarModifier extends CommonMethodModifier implements ScrollBarAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _enableNestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNestedScroll_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkScrollBarPeer): void {
        super.applyModifierPatch(peer)
        if (this._enableNestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNestedScrollAttribute((this._enableNestedScroll_0_0value as boolean | undefined));
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNestedScrollAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ScrollBarModifier): void {
        super.mergeModifier(modifier)
        if (modifier._enableNestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNestedScroll(modifier._enableNestedScroll_0_0value);
                    break;
                }
                default: {
                    this.enableNestedScroll((undefined as boolean | undefined));
                }
            }
        }
    }
    enableNestedScroll(value: boolean | undefined): this {
        if (((this._enableNestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNestedScroll_0_0value) !== (value)))
        {
            this._enableNestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNestedScroll_0_0value = value
        } else
        {
            this._enableNestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ScrollBarOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScroller  = value.scroller
        Scroller_serializer.write(valueSerializer, valueHolderForScroller)
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as ScrollBarDirection)
            valueSerializer.writeInt32(TypeChecker.ScrollBarDirection_ToNumeric(valueHolderForDirectionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForState  = value.state
        if (valueHolderForState !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStateTmpValue  = (valueHolderForState as BarState)
            valueSerializer.writeInt32(TypeChecker.BarState_ToNumeric(valueHolderForStateTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scrollerTmpResult : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : ScrollBarDirection | undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = TypeChecker.ScrollBarDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const directionTmpResult : ScrollBarDirection | undefined = directionTmpBuf
        const stateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateTmpBuf : BarState | undefined
        if ((stateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stateTmpBuf = TypeChecker.BarState_FromNumeric(valueDeserializer.readInt32())
        }
        const stateTmpResult : BarState | undefined = stateTmpBuf
        let value : ScrollBarOptions = ({scroller: scrollerTmpResult, direction: directionTmpResult, state: stateTmpResult} as ScrollBarOptions)
        return value
    }
}
