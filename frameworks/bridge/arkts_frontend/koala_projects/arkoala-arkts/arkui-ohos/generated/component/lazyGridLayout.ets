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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { LengthMetrics_serializer } from "./../Graphics"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { extractors, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { LengthMetrics, LengthUnit } from "arkui.Graphics"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { LazyGridLayoutModifier } from "./../LazyGridLayoutModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LazyVGridLayoutModifier } from "./../LazyVGridLayoutModifier"
export class ArkLazyGridLayoutAttributePeer extends ArkCommonMethodPeer {
    attributeSet?: LazyGridLayoutModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): object {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_construct(peerId, flags)
        const _peer  = new ArkLazyGridLayoutAttributePeer(_peerPtr, peerId, 'LazyGridLayoutAttribute', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowsGapAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkLazyVGridLayoutPeer extends ArkLazyGridLayoutAttributePeer {
    attributeSet?: LazyVGridLayoutModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyVGridLayoutPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LazyVGridLayout_construct(peerId, flags)
        const _peer  = new ArkLazyVGridLayoutPeer(_peerPtr, peerId, 'LazyVGridLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyVGridLayoutOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._LazyVGridLayoutInterface_setLazyVGridLayoutOptions(this.peer.ptr)
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyVGridLayoutAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface LazyGridLayoutAttribute extends CommonMethod {
    rowsGap(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method rowsGap")
    }
    columnsGap(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method columnsGap")
    }
    attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkLazyGridLayoutStyle extends ArkCommonMethodStyle implements LazyGridLayoutAttribute {
    rowsGap(value: LengthMetrics | undefined): this {
        return this
    }
    columnsGap(value: LengthMetrics | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface LazyVGridLayoutAttribute extends LazyGridLayoutAttribute {
    setLazyVGridLayoutOptions(): this {
        throw new Error("Unimplemented method setLazyVGridLayoutOptions")
    }
    columnsTemplate(value: string | undefined): this {
        throw new Error("Unimplemented method columnsTemplate")
    }
    attributeModifier(value: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkLazyVGridLayoutStyle extends ArkLazyGridLayoutStyle implements LazyVGridLayoutAttribute {
    columnsTemplate_value?: string | undefined
    attributeModifier_value?: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined
    setLazyVGridLayoutOptions(): this {
        return this
    }
    columnsTemplate(value: string | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkLazyGridLayoutAttributeComponent extends ArkCommonMethodComponent implements LazyGridLayoutAttribute {
    getPeer(): ArkLazyGridLayoutAttributePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkLazyGridLayoutAttributePeer)
    }
    public rowsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setRowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setColumnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkLazyVGridLayoutComponent extends ArkLazyGridLayoutAttributeComponent implements LazyVGridLayoutAttribute {
    getPeer(): ArkLazyVGridLayoutPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkLazyVGridLayoutPeer)
    }
    public setLazyVGridLayoutOptions(): this {
        if (this.checkPriority("setLazyVGridLayoutOptions")) {
            this.getPeer()?.setLazyVGridLayoutOptionsAttribute()
            return this
        }
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setColumnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function LazyVGridLayoutImpl(
    @memo
    style: ((attributes: LazyVGridLayoutAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyVGridLayoutComponent>((): ArkLazyVGridLayoutComponent => {
        return new ArkLazyVGridLayoutComponent()
    })
    NodeAttach<ArkLazyVGridLayoutPeer>((): ArkLazyVGridLayoutPeer => ArkLazyVGridLayoutPeer.create(receiver), (peer: ArkLazyVGridLayoutPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

