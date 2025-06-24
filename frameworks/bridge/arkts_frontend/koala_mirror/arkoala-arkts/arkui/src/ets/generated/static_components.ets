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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, SerializerBase, DeserializerBase, NativeBuffer } from "@koalaui/interop"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { GeometryInfo, Measurable, Layoutable, SizeResult } from "./common"
import { ConstraintSizeOptions } from "./units"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier, AttributeUpdater } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Root_construct(peerId, flags)
        const _peer  = new ArkRootPeer(_peerPtr, peerId, "Root", flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkComponentRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkComponentRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ComponentRoot_construct(peerId, flags)
        const _peer  = new ArkComponentRootPeer(_peerPtr, peerId, "ComponentRoot", flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomLayoutRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCustomLayoutRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CustomLayoutRoot_construct(peerId, flags)
        const _peer  = new ArkCustomLayoutRootPeer(_peerPtr, peerId, "CustomLayoutRoot", flags)
        component?.setPeer(_peer)
        return _peer
    }
    subscribeOnMeasureSizeAttribute(value: Callback_onMeasureSize_SizeResult): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_subscribeOnMeasureSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    subscribeOnPlaceChildrenAttribute(value: Callback_onPlaceChildren_Void): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_subscribeOnPlaceChildren(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface Root {
    attributeModifier(value: AttributeModifier<Root> | undefined): this
}
export class ArkRootStyle implements Root {
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: Root): void {
    }
}
export interface ComponentRoot {
    attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this
}
export class ArkComponentRootStyle implements ComponentRoot {
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ComponentRoot): void {
    }
}
export type Callback_onMeasureSize_SizeResult = (selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions) => SizeResult;
export type Callback_onPlaceChildren_Void = (selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) => void;
export interface CustomLayoutRoot {
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this
    attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this
}
export class ArkCustomLayoutRootStyle implements CustomLayoutRoot {
    subscribeOnMeasureSize_value?: Callback_onMeasureSize_SizeResult
    subscribeOnPlaceChildren_value?: Callback_onPlaceChildren_Void
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: CustomLayoutRoot): void {
        if (this.subscribeOnMeasureSize_value !== undefined)
            target.subscribeOnMeasureSize(this.subscribeOnMeasureSize_value!)
        if (this.subscribeOnPlaceChildren_value !== undefined)
            target.subscribeOnPlaceChildren(this.subscribeOnPlaceChildren_value!)
    }
}
export class ArkRootComponent extends ComponentBase implements Root {
    getPeer(): ArkRootPeer {
        return (this.peer as ArkRootPeer)
    }
    _modifier?: AttributeModifier<Root> | undefined
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRootStyle(receiver: Root, modifier: AttributeModifier<Root> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRootStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<Root>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<Root>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkComponentRootComponent extends ComponentBase implements ComponentRoot {
    getPeer(): ArkComponentRootPeer {
        return (this.peer as ArkComponentRootPeer)
    }
    _modifier?: AttributeModifier<ComponentRoot> | undefined
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withComponentRootStyle(receiver: ComponentRoot, modifier: AttributeModifier<ComponentRoot> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkComponentRootStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<ComponentRoot>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<ComponentRoot>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkCustomLayoutRootComponent extends ComponentBase implements CustomLayoutRoot {
    getPeer(): ArkCustomLayoutRootPeer {
        return (this.peer as ArkCustomLayoutRootPeer)
    }
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        if (this.checkPriority("subscribeOnMeasureSize")) {
            const value_casted = value as (Callback_onMeasureSize_SizeResult)
            this.getPeer()?.subscribeOnMeasureSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        if (this.checkPriority("subscribeOnPlaceChildren")) {
            const value_casted = value as (Callback_onPlaceChildren_Void)
            this.getPeer()?.subscribeOnPlaceChildrenAttribute(value_casted)
            return this
        }
        return this
    }
    _modifier?: AttributeModifier<CustomLayoutRoot> | undefined
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCustomLayoutRootStyle(receiver: CustomLayoutRoot, modifier: AttributeModifier<CustomLayoutRoot> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCustomLayoutRootStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CustomLayoutRoot>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CustomLayoutRoot>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
