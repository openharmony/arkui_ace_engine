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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { ColorMetrics_serializer } from "./../Graphics"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ColorMetrics } from "arkui.Graphics"
import { AttributeModifier, hookScrollBarAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Scroller, Scroller_serializer } from "./scroll"
import { BarState } from "./enums"
import { ScrollBarModifier } from "./../ScrollBarModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkScrollBarPeer extends ArkCommonMethodPeer {
    attributeSet?: ScrollBarModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    setScrollBarColorAttribute(value: ColorMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ColorMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollBarAttribute_setScrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setScrollBarOptions(value: ScrollBarOptions): this {
        throw new Error("Unimplemented method setScrollBarOptions")
    }
    enableNestedScroll(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableNestedScroll")
    }
    scrollBarColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method scrollBarColor")
    }
    attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkScrollBarStyle extends ArkCommonMethodStyle implements ScrollBarAttribute {
    enableNestedScroll_value?: boolean | undefined
    scrollBarColor_value?: ColorMetrics | undefined
    attributeModifier_value?: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined
    setScrollBarOptions(value: ScrollBarOptions): this {
        return this
    }
    enableNestedScroll(value: boolean | undefined): this {
        return this
    }
    scrollBarColor(value: ColorMetrics | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkScrollBarComponent extends ArkCommonMethodComponent implements ScrollBarAttribute {
    getPeer(): ArkScrollBarPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkScrollBarPeer)
    }
    public setScrollBarOptions(value: ScrollBarOptions): this {
        if (this.checkPriority("setScrollBarOptions")) {
            const value_casted = value as (ScrollBarOptions)
            this.getPeer()?.setScrollBarOptionsAttribute(value_casted)
            this.applyOptionsFinish('ScrollBarAttribute');
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
    public scrollBarColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setScrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookScrollBarAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ScrollBarImpl(
    @memo
    style: ((attributes: ScrollBarAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkScrollBarComponent>((): ArkScrollBarComponent => {
        return new ArkScrollBarComponent()
    })
    NodeAttach<ArkScrollBarPeer>((): ArkScrollBarPeer => ArkScrollBarPeer.create(receiver), (peer: ArkScrollBarPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
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
            valueSerializer.writeInt32(valueHolderForDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForState  = value.state
        if (valueHolderForState !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStateTmpValue  = (valueHolderForState as BarState)
            valueSerializer.writeInt32(valueHolderForStateTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scrollerTmpResult : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : ScrollBarDirection | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = ScrollBarDirection.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : ScrollBarDirection | undefined = directionTmpBuf
        const stateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateTmpBuf : BarState | undefined = undefined
        if ((stateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stateTmpBuf = BarState.fromValue(valueDeserializer.readInt32())
        }
        const stateTmpResult : BarState | undefined = stateTmpBuf
        let value : ScrollBarOptions = ({scroller: scrollerTmpResult, direction: directionTmpResult, state: stateTmpResult} as ScrollBarOptions)
        return value
    }
}
