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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { AttributeModifier, hookListItemAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { CustomBuilder } from './builder'
import { ComponentContentBase } from '@arkui.ComponentContent'
import { Length, Resource as arkui_component_units_Resource } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { ListItemModifier } from './../ListItemModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkListItemPeer extends ArkCommonMethodPeer {
    attributeSet?: ListItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
            } else if (valueTmpValue instanceof Bindable) {
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
    Spring = 0,
    None = 1,
    SPRING = 0,
    NONE = 1
}
export enum SwipeActionState {
    COLLAPSED = 0,
    EXPANDED = 1,
    ACTIONING = 2
}
export interface SwipeActionItem {
    builder?: CustomBuilder;
    builderComponent?: ComponentContentBase;
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
    onOffsetChange?: ((progress: double) => void);
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
        throw new Error('Unimplemented method setListItemOptions')
    }
    selectable(value: boolean | undefined): this {
        throw new Error('Unimplemented method selectable')
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error('Unimplemented method selected')
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        throw new Error('Unimplemented method swipeAction')
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error('Unimplemented method onSelect')
    }
    attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkListItemComponent extends ArkCommonMethodComponent implements ListItemAttribute {
    getPeer(): ArkListItemPeer {
        return (this.peer as ArkListItemPeer)
    }
    public setListItemOptions(value?: ListItemOptions): this {
        if (this.checkPriority('setListItemOptions')) {
            const value_casted = value as (ListItemOptions | undefined)
            this.getPeer()?.setListItemOptionsAttribute(value_casted)
            this.applyOptionsFinish('ListItemAttribute');
            return this
        }
        return this
    }
    public selectable(value: boolean | undefined): this {
        if (this.checkPriority('selectable')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority('selected')) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        if (this.checkPriority('swipeAction')) {
            const value_casted = value as (SwipeActionOptions | undefined)
            this.getPeer()?.setSwipeActionAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        if (this.checkPriority('onSelect')) {
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
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
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
            valueSerializer.holdAndWriteObject(valueHolderForBuilderComponentTmpValue)
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
            } else if (valueHolderForActionAreaDistanceTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForActionAreaDistanceTmpValueForIdx2  = valueHolderForActionAreaDistanceTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForActionAreaDistanceTmpValueForIdx2)
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
        const builderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let builderTmpBuf : CustomBuilder | undefined = undefined
        if ((builderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const builderTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const builderTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const builderTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const builderTmpBufOptClosure  = ():void => {
                const builderTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                builderTmpBufOptBufArgsSerializer.writeInt32(builderTmpBufOptBufResource.resourceId);
                builderTmpBufOptBufArgsSerializer.writePointer(builderTmpBufOptBufCall);
                builderTmpBufOptBufArgsSerializer.writePointer(builderTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, builderTmpBufOptBufArgsSerializer.asBuffer(), builderTmpBufOptBufArgsSerializer.length());
                builderTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(builderTmpBufOptClosure, builderTmpBufOptBufResource)
            builderTmpBuf = builderTmpBufOptClosure
        }
        const builderTmpResult : CustomBuilder | undefined = builderTmpBuf
        const builderComponentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let builderComponentTmpBuf : ComponentContentBase | undefined = undefined
        if ((builderComponentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            builderComponentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const builderComponentTmpResult : ComponentContentBase | undefined = builderComponentTmpBuf
        const actionAreaDistanceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let actionAreaDistanceTmpBuf : Length | undefined = undefined
        if ((actionAreaDistanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const actionAreaDistanceTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let actionAreaDistanceTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (actionAreaDistanceTmpBufOptUnionSelector == (0).toByte()) {
                actionAreaDistanceTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (actionAreaDistanceTmpBufOptUnionSelector == (1).toByte()) {
                actionAreaDistanceTmpBufOpt = valueDeserializer.readFloat64()
            } else if (actionAreaDistanceTmpBufOptUnionSelector == (2).toByte()) {
                actionAreaDistanceTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for actionAreaDistanceTmpBufOpt has to be chosen through deserialisation.')
            }
            actionAreaDistanceTmpBuf = (actionAreaDistanceTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const actionAreaDistanceTmpResult : Length | undefined = actionAreaDistanceTmpBuf
        const onActionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onActionTmpBuf : (() => void) | undefined = undefined
        if ((onActionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onActionTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onActionTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onActionTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onActionTmpBufOptClosure  = ():void => {
                const onActionTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onActionTmpBufOptBufArgsSerializer.writeInt32(onActionTmpBufOptBufResource.resourceId);
                onActionTmpBufOptBufArgsSerializer.writePointer(onActionTmpBufOptBufCall);
                onActionTmpBufOptBufArgsSerializer.writePointer(onActionTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onActionTmpBufOptBufArgsSerializer.asBuffer(), onActionTmpBufOptBufArgsSerializer.length());
                onActionTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onActionTmpBufOptClosure, onActionTmpBufOptBufResource)
            onActionTmpBuf = onActionTmpBufOptClosure
        }
        const onActionTmpResult : (() => void) | undefined = onActionTmpBuf
        const onEnterActionAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onEnterActionAreaTmpBuf : (() => void) | undefined = undefined
        if ((onEnterActionAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterActionAreaTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterActionAreaTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onEnterActionAreaTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onEnterActionAreaTmpBufOptClosure  = ():void => {
                const onEnterActionAreaTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterActionAreaTmpBufOptBufArgsSerializer.writeInt32(onEnterActionAreaTmpBufOptBufResource.resourceId);
                onEnterActionAreaTmpBufOptBufArgsSerializer.writePointer(onEnterActionAreaTmpBufOptBufCall);
                onEnterActionAreaTmpBufOptBufArgsSerializer.writePointer(onEnterActionAreaTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onEnterActionAreaTmpBufOptBufArgsSerializer.asBuffer(), onEnterActionAreaTmpBufOptBufArgsSerializer.length());
                onEnterActionAreaTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onEnterActionAreaTmpBufOptClosure, onEnterActionAreaTmpBufOptBufResource)
            onEnterActionAreaTmpBuf = onEnterActionAreaTmpBufOptClosure
        }
        const onEnterActionAreaTmpResult : (() => void) | undefined = onEnterActionAreaTmpBuf
        const onExitActionAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onExitActionAreaTmpBuf : (() => void) | undefined = undefined
        if ((onExitActionAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onExitActionAreaTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onExitActionAreaTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onExitActionAreaTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onExitActionAreaTmpBufOptClosure  = ():void => {
                const onExitActionAreaTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onExitActionAreaTmpBufOptBufArgsSerializer.writeInt32(onExitActionAreaTmpBufOptBufResource.resourceId);
                onExitActionAreaTmpBufOptBufArgsSerializer.writePointer(onExitActionAreaTmpBufOptBufCall);
                onExitActionAreaTmpBufOptBufArgsSerializer.writePointer(onExitActionAreaTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onExitActionAreaTmpBufOptBufArgsSerializer.asBuffer(), onExitActionAreaTmpBufOptBufArgsSerializer.length());
                onExitActionAreaTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onExitActionAreaTmpBufOptClosure, onExitActionAreaTmpBufOptBufResource)
            onExitActionAreaTmpBuf = onExitActionAreaTmpBufOptClosure
        }
        const onExitActionAreaTmpResult : (() => void) | undefined = onExitActionAreaTmpBuf
        const onStateChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onStateChangeTmpBuf : ((state: SwipeActionState) => void) | undefined = undefined
        if ((onStateChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onStateChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onStateChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onStateChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onStateChangeTmpBufOptClosure  = (state: SwipeActionState):void => {
                const onStateChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onStateChangeTmpBufOptBufArgsSerializer.writeInt32(onStateChangeTmpBufOptBufResource.resourceId);
                onStateChangeTmpBufOptBufArgsSerializer.writePointer(onStateChangeTmpBufOptBufCall);
                onStateChangeTmpBufOptBufArgsSerializer.writePointer(onStateChangeTmpBufOptBufCallSync);
                onStateChangeTmpBufOptBufArgsSerializer.writeInt32(state.valueOf());
                InteropNativeModule._CallCallbackSync(10, 1650975710, onStateChangeTmpBufOptBufArgsSerializer.asBuffer(), onStateChangeTmpBufOptBufArgsSerializer.length());
                onStateChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onStateChangeTmpBufOptClosure, onStateChangeTmpBufOptBufResource)
            onStateChangeTmpBuf = onStateChangeTmpBufOptClosure
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
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : CustomBuilder | SwipeActionItem | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let startTmpBufOpt : CustomBuilder | SwipeActionItem | undefined
            if (startTmpBufOptUnionSelector == (0).toByte()) {
                const startTmpBufOptBufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const startTmpBufOptBufUBufCall : KPointer = valueDeserializer.readPointer()
                const startTmpBufOptBufUBufCallSync : KPointer = valueDeserializer.readPointer()
                const startTmpBufOptBufUClosure  = ():void => {
                    const startTmpBufOptBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    startTmpBufOptBufUBufArgsSerializer.writeInt32(startTmpBufOptBufUBufResource.resourceId);
                    startTmpBufOptBufUBufArgsSerializer.writePointer(startTmpBufOptBufUBufCall);
                    startTmpBufOptBufUBufArgsSerializer.writePointer(startTmpBufOptBufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, -1834072896, startTmpBufOptBufUBufArgsSerializer.asBuffer(), startTmpBufOptBufUBufArgsSerializer.length());
                    startTmpBufOptBufUBufArgsSerializer.release();
                    return;
                }
                resourceFinalizerRegister(startTmpBufOptBufUClosure, startTmpBufOptBufUBufResource)
                startTmpBufOpt = startTmpBufOptBufUClosure
            } else if (startTmpBufOptUnionSelector == (1).toByte()) {
                startTmpBufOpt = SwipeActionItem_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for startTmpBufOpt has to be chosen through deserialisation.')
            }
            startTmpBuf = (startTmpBufOpt as CustomBuilder | SwipeActionItem)
        }
        const startTmpResult : CustomBuilder | SwipeActionItem | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : CustomBuilder | SwipeActionItem | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let endTmpBufOpt : CustomBuilder | SwipeActionItem | undefined
            if (endTmpBufOptUnionSelector == (0).toByte()) {
                const endTmpBufOptBufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const endTmpBufOptBufUBufCall : KPointer = valueDeserializer.readPointer()
                const endTmpBufOptBufUBufCallSync : KPointer = valueDeserializer.readPointer()
                const endTmpBufOptBufUClosure  = ():void => {
                    const endTmpBufOptBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    endTmpBufOptBufUBufArgsSerializer.writeInt32(endTmpBufOptBufUBufResource.resourceId);
                    endTmpBufOptBufUBufArgsSerializer.writePointer(endTmpBufOptBufUBufCall);
                    endTmpBufOptBufUBufArgsSerializer.writePointer(endTmpBufOptBufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, -1834072896, endTmpBufOptBufUBufArgsSerializer.asBuffer(), endTmpBufOptBufUBufArgsSerializer.length());
                    endTmpBufOptBufUBufArgsSerializer.release();
                    return;
                }
                resourceFinalizerRegister(endTmpBufOptBufUClosure, endTmpBufOptBufUBufResource)
                endTmpBufOpt = endTmpBufOptBufUClosure
            } else if (endTmpBufOptUnionSelector == (1).toByte()) {
                endTmpBufOpt = SwipeActionItem_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for endTmpBufOpt has to be chosen through deserialisation.')
            }
            endTmpBuf = (endTmpBufOpt as CustomBuilder | SwipeActionItem)
        }
        const endTmpResult : CustomBuilder | SwipeActionItem | undefined = endTmpBuf
        const edgeEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let edgeEffectTmpBuf : SwipeEdgeEffect | undefined = undefined
        if ((edgeEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            edgeEffectTmpBuf = SwipeEdgeEffect.fromValue(valueDeserializer.readInt32())
        }
        const edgeEffectTmpResult : SwipeEdgeEffect | undefined = edgeEffectTmpBuf
        const onOffsetChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onOffsetChangeTmpBuf : ((progress: double) => void) | undefined = undefined
        if ((onOffsetChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onOffsetChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onOffsetChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onOffsetChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onOffsetChangeTmpBufOptClosure  = (progress: double):void => {
                const onOffsetChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onOffsetChangeTmpBufOptBufArgsSerializer.writeInt32(onOffsetChangeTmpBufOptBufResource.resourceId);
                onOffsetChangeTmpBufOptBufArgsSerializer.writePointer(onOffsetChangeTmpBufOptBufCall);
                onOffsetChangeTmpBufOptBufArgsSerializer.writePointer(onOffsetChangeTmpBufOptBufCallSync);
                onOffsetChangeTmpBufOptBufArgsSerializer.writeFloat64(progress);
                InteropNativeModule._CallCallbackSync(10, -1748561129, onOffsetChangeTmpBufOptBufArgsSerializer.asBuffer(), onOffsetChangeTmpBufOptBufArgsSerializer.length());
                onOffsetChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onOffsetChangeTmpBufOptClosure, onOffsetChangeTmpBufOptBufResource)
            onOffsetChangeTmpBuf = onOffsetChangeTmpBufOptClosure
        }
        const onOffsetChangeTmpResult : ((progress: double) => void) | undefined = onOffsetChangeTmpBuf
        let value : SwipeActionOptions = ({start: startTmpResult, end: endTmpResult, edgeEffect: edgeEffectTmpResult, onOffsetChange: onOffsetChangeTmpResult} as SwipeActionOptions)
        return value
    }
}
