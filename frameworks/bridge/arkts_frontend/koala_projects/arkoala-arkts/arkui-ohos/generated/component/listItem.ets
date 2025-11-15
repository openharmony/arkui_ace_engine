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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, extractors, hookListItemAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ComponentContent } from "arkui.ComponentContent"
import { Length } from "./units"
import { Resource } from "global.resource"
import { ListItemModifier } from "./../ListItemModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent_serializer } from "./../ComponentContent"
import { Resource_serializer } from "./../framework/resource"
import { ModifierStateManager } from '../CommonModifier';
export class ArkListItemPeer extends ArkCommonMethodPeer {
    attributeSet?: ListItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItem_construct(peerId, flags)
        const _peer  = new ArkListItemPeer(_peerPtr, peerId, 'ListItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemOptionsAttribute(value?: ListItemOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ListItemOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemInterface_setListItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwipeActionAttribute(value: SwipeActionOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SwipeActionOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSwipeAction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: ((isSelected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SwipeEdgeEffect {
    SPRING = 0,
    Spring = 0,
    NONE = 1,
    None = 1
}
export enum SwipeActionState {
    COLLAPSED = 0,
    EXPANDED = 1,
    ACTIONING = 2
}
export interface SwipeActionItem {
    builder?: CustomBuilder;
    builderComponent?: ComponentContent;
    actionAreaDistance?: Length;
    onAction?: (() => void);
    onEnterActionArea?: (() => void);
    onExitActionArea?: (() => void);
    onStateChange?: ((state: SwipeActionState) => void);
}
export interface SwipeActionOptions {
    start?: CustomBuilder | SwipeActionItem;
    end?: CustomBuilder | SwipeActionItem;
    edgeEffect?: SwipeEdgeEffect;
    onOffsetChange?: ((offset: double) => void);
}
export enum ListItemStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemOptions {
    style?: ListItemStyle;
}
export interface ListItemAttribute extends CommonMethod {
    setListItemOptions(value?: ListItemOptions): this {
        throw new Error("Unimplemented method setListItemOptions")
    }
    selectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectable")
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        throw new Error("Unimplemented method swipeAction")
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkListItemStyle extends ArkCommonMethodStyle implements ListItemAttribute {
    selectable_value?: boolean | undefined
    selected_value?: boolean | Bindable<boolean> | undefined
    swipeAction_value?: SwipeActionOptions | undefined
    onSelect_value?: ((isSelected: boolean) => void) | undefined
    attributeModifier_value?: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined
    setListItemOptions(value?: ListItemOptions): this {
        return this
    }
    selectable(value: boolean | undefined): this {
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        return this
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkListItemComponent extends ArkCommonMethodComponent implements ListItemAttribute {
    getPeer(): ArkListItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkListItemPeer)
    }
    public setListItemOptions(value?: ListItemOptions): this {
        if (this.checkPriority("setListItemOptions")) {
            const value_casted = value as (ListItemOptions | undefined)
            this.getPeer()?.setListItemOptionsAttribute(value_casted)
            this.applyOptionsFinish('ListItemAttribute');
            return this
        }
        return this
    }
    public selectable(value: boolean | undefined): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        if (this.checkPriority("swipeAction")) {
            const value_casted = value as (SwipeActionOptions | undefined)
            this.getPeer()?.setSwipeActionAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((isSelected: boolean) => void) | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookListItemAttributeModifier(this, value);
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
export class ListItemOptions_serializer {
    public static write(buffer: SerializerBase, value: ListItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as ListItemStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ListItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : ListItemStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = ListItemStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : ListItemStyle | undefined = styleTmpBuf
        let value : ListItemOptions = ({style: styleTmpResult} as ListItemOptions)
        return value
    }
}
export class SwipeActionItem_serializer {
    public static write(buffer: SerializerBase, value: SwipeActionItem): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBuilder  = value.builder
        if (valueHolderForBuilder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBuilderTmpValue  = valueHolderForBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBuilderComponent  = value.builderComponent
        if (valueHolderForBuilderComponent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBuilderComponentTmpValue  = valueHolderForBuilderComponent!
            ComponentContent_serializer.write(valueSerializer, valueHolderForBuilderComponentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForActionAreaDistance  = value.actionAreaDistance
        if (valueHolderForActionAreaDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActionAreaDistanceTmpValue  = valueHolderForActionAreaDistance!
            if (valueHolderForActionAreaDistanceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForActionAreaDistanceTmpValueForIdx0  = valueHolderForActionAreaDistanceTmpValue as string
                valueSerializer.writeString(valueHolderForActionAreaDistanceTmpValueForIdx0)
            } else if (valueHolderForActionAreaDistanceTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForActionAreaDistanceTmpValueForIdx1  = valueHolderForActionAreaDistanceTmpValue as double
                valueSerializer.writeFloat64(valueHolderForActionAreaDistanceTmpValueForIdx1)
            } else if (valueHolderForActionAreaDistanceTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForActionAreaDistanceTmpValueForIdx2  = valueHolderForActionAreaDistanceTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForActionAreaDistanceTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnAction  = value.onAction
        if (valueHolderForOnAction !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnActionTmpValue  = valueHolderForOnAction!
            valueSerializer.holdAndWriteCallback(valueHolderForOnActionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnEnterActionArea  = value.onEnterActionArea
        if (valueHolderForOnEnterActionArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnEnterActionAreaTmpValue  = valueHolderForOnEnterActionArea!
            valueSerializer.holdAndWriteCallback(valueHolderForOnEnterActionAreaTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnExitActionArea  = value.onExitActionArea
        if (valueHolderForOnExitActionArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnExitActionAreaTmpValue  = valueHolderForOnExitActionArea!
            valueSerializer.holdAndWriteCallback(valueHolderForOnExitActionAreaTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnStateChange  = value.onStateChange
        if (valueHolderForOnStateChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnStateChangeTmpValue  = valueHolderForOnStateChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnStateChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SwipeActionItem {
        let valueDeserializer : DeserializerBase = buffer
        const builderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builderTmpBuf : CustomBuilder | undefined = undefined
        if ((builderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const builderTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const builderTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const builderTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            builderTmpBuf = ():void => {
                const builderTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                builderTmpBuf_BufArgsSerializer.writeInt32(builderTmpBuf_BufResource.resourceId);
                builderTmpBuf_BufArgsSerializer.writePointer(builderTmpBuf_BufCall);
                builderTmpBuf_BufArgsSerializer.writePointer(builderTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, 737226752, builderTmpBuf_BufArgsSerializer.asBuffer(), builderTmpBuf_BufArgsSerializer.length());
                builderTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const builderTmpResult : CustomBuilder | undefined = builderTmpBuf
        const builderComponentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builderComponentTmpBuf : ComponentContent | undefined = undefined
        if ((builderComponentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            builderComponentTmpBuf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const builderComponentTmpResult : ComponentContent | undefined = builderComponentTmpBuf
        const actionAreaDistanceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let actionAreaDistanceTmpBuf : Length | undefined = undefined
        if ((actionAreaDistanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const actionAreaDistanceTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let actionAreaDistanceTmpBuf_ : string | double | Resource | undefined
            if (actionAreaDistanceTmpBuf_UnionSelector == (0).toChar()) {
                actionAreaDistanceTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (actionAreaDistanceTmpBuf_UnionSelector == (1).toChar()) {
                actionAreaDistanceTmpBuf_ = valueDeserializer.readFloat64()
            } else if (actionAreaDistanceTmpBuf_UnionSelector == (2).toChar()) {
                actionAreaDistanceTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for actionAreaDistanceTmpBuf_ has to be chosen through deserialisation.")
            }
            actionAreaDistanceTmpBuf = (actionAreaDistanceTmpBuf_ as string | double | Resource)
        }
        const actionAreaDistanceTmpResult : Length | undefined = actionAreaDistanceTmpBuf
        const onActionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onActionTmpBuf : (() => void) | undefined = undefined
        if ((onActionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onActionTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onActionTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onActionTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onActionTmpBuf = ():void => {
                const onActionTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onActionTmpBuf_BufArgsSerializer.writeInt32(onActionTmpBuf_BufResource.resourceId);
                onActionTmpBuf_BufArgsSerializer.writePointer(onActionTmpBuf_BufCall);
                onActionTmpBuf_BufArgsSerializer.writePointer(onActionTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onActionTmpBuf_BufArgsSerializer.asBuffer(), onActionTmpBuf_BufArgsSerializer.length());
                onActionTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onActionTmpResult : (() => void) | undefined = onActionTmpBuf
        const onEnterActionAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onEnterActionAreaTmpBuf : (() => void) | undefined = undefined
        if ((onEnterActionAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterActionAreaTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterActionAreaTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onEnterActionAreaTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onEnterActionAreaTmpBuf = ():void => {
                const onEnterActionAreaTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterActionAreaTmpBuf_BufArgsSerializer.writeInt32(onEnterActionAreaTmpBuf_BufResource.resourceId);
                onEnterActionAreaTmpBuf_BufArgsSerializer.writePointer(onEnterActionAreaTmpBuf_BufCall);
                onEnterActionAreaTmpBuf_BufArgsSerializer.writePointer(onEnterActionAreaTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onEnterActionAreaTmpBuf_BufArgsSerializer.asBuffer(), onEnterActionAreaTmpBuf_BufArgsSerializer.length());
                onEnterActionAreaTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onEnterActionAreaTmpResult : (() => void) | undefined = onEnterActionAreaTmpBuf
        const onExitActionAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onExitActionAreaTmpBuf : (() => void) | undefined = undefined
        if ((onExitActionAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onExitActionAreaTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onExitActionAreaTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onExitActionAreaTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onExitActionAreaTmpBuf = ():void => {
                const onExitActionAreaTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onExitActionAreaTmpBuf_BufArgsSerializer.writeInt32(onExitActionAreaTmpBuf_BufResource.resourceId);
                onExitActionAreaTmpBuf_BufArgsSerializer.writePointer(onExitActionAreaTmpBuf_BufCall);
                onExitActionAreaTmpBuf_BufArgsSerializer.writePointer(onExitActionAreaTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onExitActionAreaTmpBuf_BufArgsSerializer.asBuffer(), onExitActionAreaTmpBuf_BufArgsSerializer.length());
                onExitActionAreaTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onExitActionAreaTmpResult : (() => void) | undefined = onExitActionAreaTmpBuf
        const onStateChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onStateChangeTmpBuf : ((state: SwipeActionState) => void) | undefined = undefined
        if ((onStateChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onStateChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onStateChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onStateChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onStateChangeTmpBuf = (state: SwipeActionState):void => {
                const onStateChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onStateChangeTmpBuf_BufArgsSerializer.writeInt32(onStateChangeTmpBuf_BufResource.resourceId);
                onStateChangeTmpBuf_BufArgsSerializer.writePointer(onStateChangeTmpBuf_BufCall);
                onStateChangeTmpBuf_BufArgsSerializer.writePointer(onStateChangeTmpBuf_BufCallSync);
                onStateChangeTmpBuf_BufArgsSerializer.writeInt32(state.valueOf());
                InteropNativeModule._CallCallbackSync(10, -301561698, onStateChangeTmpBuf_BufArgsSerializer.asBuffer(), onStateChangeTmpBuf_BufArgsSerializer.length());
                onStateChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onStateChangeTmpResult : ((state: SwipeActionState) => void) | undefined = onStateChangeTmpBuf
        let value : SwipeActionItem = ({builder: builderTmpResult, builderComponent: builderComponentTmpResult, actionAreaDistance: actionAreaDistanceTmpResult, onAction: onActionTmpResult, onEnterActionArea: onEnterActionAreaTmpResult, onExitActionArea: onExitActionAreaTmpResult, onStateChange: onStateChangeTmpResult} as SwipeActionItem)
        return value
    }
}
export class SwipeActionOptions_serializer {
    public static write(buffer: SerializerBase, value: SwipeActionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            if (valueHolderForStartTmpValue instanceof CustomBuilder) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartTmpValueForIdx0  = valueHolderForStartTmpValue as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForStartTmpValueForIdx0))
            } else if (valueHolderForStartTmpValue instanceof SwipeActionItem) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartTmpValueForIdx1  = valueHolderForStartTmpValue as SwipeActionItem
                SwipeActionItem_serializer.write(valueSerializer, valueHolderForStartTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            if (valueHolderForEndTmpValue instanceof CustomBuilder) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndTmpValueForIdx0  = valueHolderForEndTmpValue as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForEndTmpValueForIdx0))
            } else if (valueHolderForEndTmpValue instanceof SwipeActionItem) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndTmpValueForIdx1  = valueHolderForEndTmpValue as SwipeActionItem
                SwipeActionItem_serializer.write(valueSerializer, valueHolderForEndTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEdgeEffect  = value.edgeEffect
        if (valueHolderForEdgeEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEdgeEffectTmpValue  = (valueHolderForEdgeEffect as SwipeEdgeEffect)
            valueSerializer.writeInt32(valueHolderForEdgeEffectTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnOffsetChange  = value.onOffsetChange
        if (valueHolderForOnOffsetChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnOffsetChangeTmpValue  = valueHolderForOnOffsetChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnOffsetChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SwipeActionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : CustomBuilder | SwipeActionItem | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBuf_ : CustomBuilder | SwipeActionItem | undefined
            if (startTmpBuf_UnionSelector == (0).toChar()) {
                const startTmpBuf_BufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const startTmpBuf_BufUBufCall : KPointer = valueDeserializer.readPointer()
                const startTmpBuf_BufUBufCallSync : KPointer = valueDeserializer.readPointer()
                startTmpBuf_ = ():void => {
                    const startTmpBuf_BufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    startTmpBuf_BufUBufArgsSerializer.writeInt32(startTmpBuf_BufUBufResource.resourceId);
                    startTmpBuf_BufUBufArgsSerializer.writePointer(startTmpBuf_BufUBufCall);
                    startTmpBuf_BufUBufArgsSerializer.writePointer(startTmpBuf_BufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, 737226752, startTmpBuf_BufUBufArgsSerializer.asBuffer(), startTmpBuf_BufUBufArgsSerializer.length());
                    startTmpBuf_BufUBufArgsSerializer.release();
                    return;
                }
            } else if (startTmpBuf_UnionSelector == (1).toChar()) {
                startTmpBuf_ = SwipeActionItem_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startTmpBuf_ has to be chosen through deserialisation.")
            }
            startTmpBuf = (startTmpBuf_ as CustomBuilder | SwipeActionItem)
        }
        const startTmpResult : CustomBuilder | SwipeActionItem | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : CustomBuilder | SwipeActionItem | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBuf_ : CustomBuilder | SwipeActionItem | undefined
            if (endTmpBuf_UnionSelector == (0).toChar()) {
                const endTmpBuf_BufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const endTmpBuf_BufUBufCall : KPointer = valueDeserializer.readPointer()
                const endTmpBuf_BufUBufCallSync : KPointer = valueDeserializer.readPointer()
                endTmpBuf_ = ():void => {
                    const endTmpBuf_BufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    endTmpBuf_BufUBufArgsSerializer.writeInt32(endTmpBuf_BufUBufResource.resourceId);
                    endTmpBuf_BufUBufArgsSerializer.writePointer(endTmpBuf_BufUBufCall);
                    endTmpBuf_BufUBufArgsSerializer.writePointer(endTmpBuf_BufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, 737226752, endTmpBuf_BufUBufArgsSerializer.asBuffer(), endTmpBuf_BufUBufArgsSerializer.length());
                    endTmpBuf_BufUBufArgsSerializer.release();
                    return;
                }
            } else if (endTmpBuf_UnionSelector == (1).toChar()) {
                endTmpBuf_ = SwipeActionItem_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endTmpBuf_ has to be chosen through deserialisation.")
            }
            endTmpBuf = (endTmpBuf_ as CustomBuilder | SwipeActionItem)
        }
        const endTmpResult : CustomBuilder | SwipeActionItem | undefined = endTmpBuf
        const edgeEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let edgeEffectTmpBuf : SwipeEdgeEffect | undefined = undefined
        if ((edgeEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            edgeEffectTmpBuf = SwipeEdgeEffect.fromValue(valueDeserializer.readInt32())
        }
        const edgeEffectTmpResult : SwipeEdgeEffect | undefined = edgeEffectTmpBuf
        const onOffsetChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onOffsetChangeTmpBuf : ((offset: double) => void) | undefined = undefined
        if ((onOffsetChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onOffsetChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onOffsetChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onOffsetChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onOffsetChangeTmpBuf = (offset: double):void => {
                const onOffsetChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onOffsetChangeTmpBuf_BufArgsSerializer.writeInt32(onOffsetChangeTmpBuf_BufResource.resourceId);
                onOffsetChangeTmpBuf_BufArgsSerializer.writePointer(onOffsetChangeTmpBuf_BufCall);
                onOffsetChangeTmpBuf_BufArgsSerializer.writePointer(onOffsetChangeTmpBuf_BufCallSync);
                onOffsetChangeTmpBuf_BufArgsSerializer.writeFloat64(offset);
                InteropNativeModule._CallCallbackSync(10, -949162837, onOffsetChangeTmpBuf_BufArgsSerializer.asBuffer(), onOffsetChangeTmpBuf_BufArgsSerializer.length());
                onOffsetChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onOffsetChangeTmpResult : ((offset: double) => void) | undefined = onOffsetChangeTmpBuf
        let value : SwipeActionOptions = ({start: startTmpResult, end: endTmpResult, edgeEffect: edgeEffectTmpResult, onOffsetChange: onOffsetChangeTmpResult} as SwipeActionOptions)
        return value
    }
}
