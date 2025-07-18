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
import { CustomBuilder } from "./builder"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
import { Length } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkListItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItem_construct(peerId, flags)
        const _peer  = new ArkListItemPeer(_peerPtr, peerId, "ListItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemOptionsAttribute(value?: ListItemOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ListItemOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListItemInterface_setListItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwipeActionAttribute(value: SwipeActionOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SwipeActionOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setSwipeAction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: ((isSelected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._ListItemAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    onOffsetChange?: ((offset: number) => void);
}
export enum ListItemStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemOptions {
    style?: ListItemStyle;
}
export interface ListItemAttribute extends CommonMethod {
    selectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectable")
    }
    selected(value: boolean | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    swipeAction(value: SwipeActionOptions | undefined): this {
        throw new Error("Unimplemented method swipeAction")
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkListItemStyle extends ArkCommonMethodStyle implements ListItemAttribute {
    selectable_value?: boolean | undefined
    selected_value?: boolean | undefined
    swipeAction_value?: SwipeActionOptions | undefined
    onSelect_value?: ((isSelected: boolean) => void) | undefined
    attributeModifier_value?: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined
    public selectable(value: boolean | undefined): this {
        return this
    }
    public selected(value: boolean | undefined): this {
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ListItemAttribute): void {
        super.apply(target)
        if (this.selectable_value !== undefined)
            target.selectable(this.selectable_value!)
        if (this.selected_value !== undefined)
            target.selected(this.selected_value!)
        if (this.swipeAction_value !== undefined)
            target.swipeAction(this.swipeAction_value!)
        if (this.onSelect_value !== undefined)
            target.onSelect(this.onSelect_value!)
    }
}

export class ArkListItemComponent extends ArkCommonMethodComponent implements ListItemAttribute {
    getPeer(): ArkListItemPeer {
        return (this.peer as ArkListItemPeer)
    }
    public setListItemOptions(value?: ListItemOptions): this {
        if (this.checkPriority("setListItemOptions")) {
            const value_casted = value as (ListItemOptions | undefined)
            this.getPeer()?.setListItemOptionsAttribute(value_casted)
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
    public selected(value: boolean | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | undefined)
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
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withListItemStyle(receiver: ListItemAttribute, modifier: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkListItemStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ListItem")
// export function ListItem(
//     value?: ListItemOptions,
//     @memo
//     content_?: () => void,
// ): ListItemAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ListItem(
    @memo
    style: ((attributes: ListItemAttribute) => void) | undefined,
    value?: ListItemOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkListItemComponent>((): ArkListItemComponent => {
        return new ArkListItemComponent()
    })
    NodeAttach<ArkListItemPeer>((): ArkListItemPeer => ArkListItemPeer.create(receiver), (_: ArkListItemPeer): void => {
        receiver.setListItemOptions(value)
        style?.(receiver)
        withListItemStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkListItemSet extends ArkCommonMethodSet implements ListItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selectable_flag?: boolean
    _selectable0_value?: boolean | undefined
    _selected_flag?: boolean
    _selected0_value?: boolean | undefined
    _swipeAction_flag?: boolean
    _swipeAction0_value?: SwipeActionOptions | undefined
    _onSelect_flag?: boolean
    _onSelect0_value?: ((isSelected: boolean) => void) | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: boolean | undefined) => void)
    applyModifierPatch(component: ListItemAttribute): void {
        if (this._selectable_flag)
            component.selectable((this._selectable0_value as boolean | undefined))
        if (this._selected_flag)
            component.selected((this._selected0_value as boolean | undefined))
        if (this._swipeAction_flag)
            component.swipeAction((this._swipeAction0_value as SwipeActionOptions | undefined))
        if (this._onSelect_flag)
            component.onSelect((this._onSelect0_value as ((isSelected: boolean) => void) | undefined))
    }
    public selectable(value: boolean | undefined): this {
        this._selectable_flag = true
        this._selectable0_value = value
        return this
    }
    public selected(value: boolean | undefined): this {
        this._selected_flag = true
        this._selected0_value = value
        return this
    }
    public swipeAction(value: SwipeActionOptions | undefined): this {
        this._swipeAction_flag = true
        this._swipeAction0_value = value
        return this
    }
    public onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        this._onSelect_flag = true
        this._onSelect0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ListItemOptions_serializer {
    public static write(buffer: SerializerBase, value: ListItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as ListItemStyle)
            valueSerializer.writeInt32(TypeChecker.ListItemStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): ListItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : ListItemStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.ListItemStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : ListItemStyle | undefined = style_buf
        let value : ListItemOptions = ({style: style_result} as ListItemOptions)
        return value
    }
}
export class SwipeActionItem_serializer {
    public static write(buffer: SerializerBase, value: SwipeActionItem): void {
        let valueSerializer : SerializerBase = buffer
        const value_builder  = value.builder
        let value_builder_type : int32 = RuntimeType.UNDEFINED
        value_builder_type = runtimeType(value_builder)
        valueSerializer.writeInt8((value_builder_type).toChar())
        if ((value_builder_type) != (RuntimeType.UNDEFINED)) {
            const value_builder_value  = value_builder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder_value))
        }
        const value_builderComponent  = value.builderComponent
        let value_builderComponent_type : int32 = RuntimeType.UNDEFINED
        value_builderComponent_type = runtimeType(value_builderComponent)
        valueSerializer.writeInt8((value_builderComponent_type).toChar())
        if ((value_builderComponent_type) != (RuntimeType.UNDEFINED)) {
            const value_builderComponent_value  = value_builderComponent!
            ComponentContent_serializer.write(valueSerializer, value_builderComponent_value)
        }
        const value_actionAreaDistance  = value.actionAreaDistance
        let value_actionAreaDistance_type : int32 = RuntimeType.UNDEFINED
        value_actionAreaDistance_type = runtimeType(value_actionAreaDistance)
        valueSerializer.writeInt8((value_actionAreaDistance_type).toChar())
        if ((value_actionAreaDistance_type) != (RuntimeType.UNDEFINED)) {
            const value_actionAreaDistance_value  = value_actionAreaDistance!
            let value_actionAreaDistance_value_type : int32 = RuntimeType.UNDEFINED
            value_actionAreaDistance_value_type = runtimeType(value_actionAreaDistance_value)
            if (RuntimeType.STRING == value_actionAreaDistance_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_actionAreaDistance_value_0  = value_actionAreaDistance_value as string
                valueSerializer.writeString(value_actionAreaDistance_value_0)
            }
            else if (RuntimeType.NUMBER == value_actionAreaDistance_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_actionAreaDistance_value_1  = value_actionAreaDistance_value as number
                valueSerializer.writeNumber(value_actionAreaDistance_value_1)
            }
            else if (RuntimeType.OBJECT == value_actionAreaDistance_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_actionAreaDistance_value_2  = value_actionAreaDistance_value as Resource
                Resource_serializer.write(valueSerializer, value_actionAreaDistance_value_2)
            }
        }
        const value_onAction  = value.onAction
        let value_onAction_type : int32 = RuntimeType.UNDEFINED
        value_onAction_type = runtimeType(value_onAction)
        valueSerializer.writeInt8((value_onAction_type).toChar())
        if ((value_onAction_type) != (RuntimeType.UNDEFINED)) {
            const value_onAction_value  = value_onAction!
            valueSerializer.holdAndWriteCallback(value_onAction_value)
        }
        const value_onEnterActionArea  = value.onEnterActionArea
        let value_onEnterActionArea_type : int32 = RuntimeType.UNDEFINED
        value_onEnterActionArea_type = runtimeType(value_onEnterActionArea)
        valueSerializer.writeInt8((value_onEnterActionArea_type).toChar())
        if ((value_onEnterActionArea_type) != (RuntimeType.UNDEFINED)) {
            const value_onEnterActionArea_value  = value_onEnterActionArea!
            valueSerializer.holdAndWriteCallback(value_onEnterActionArea_value)
        }
        const value_onExitActionArea  = value.onExitActionArea
        let value_onExitActionArea_type : int32 = RuntimeType.UNDEFINED
        value_onExitActionArea_type = runtimeType(value_onExitActionArea)
        valueSerializer.writeInt8((value_onExitActionArea_type).toChar())
        if ((value_onExitActionArea_type) != (RuntimeType.UNDEFINED)) {
            const value_onExitActionArea_value  = value_onExitActionArea!
            valueSerializer.holdAndWriteCallback(value_onExitActionArea_value)
        }
        const value_onStateChange  = value.onStateChange
        let value_onStateChange_type : int32 = RuntimeType.UNDEFINED
        value_onStateChange_type = runtimeType(value_onStateChange)
        valueSerializer.writeInt8((value_onStateChange_type).toChar())
        if ((value_onStateChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onStateChange_value  = value_onStateChange!
            valueSerializer.holdAndWriteCallback(value_onStateChange_value)
        }
    }
    public static read(buffer: DeserializerBase): SwipeActionItem {
        let valueDeserializer : DeserializerBase = buffer
        const builder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builder_buf : CustomBuilder | undefined
        if ((builder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const builder_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const builder_buf__call : KPointer = valueDeserializer.readPointer()
            const builder_buf__callSync : KPointer = valueDeserializer.readPointer()
            builder_buf = ():void => { 
    const builder_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    builder_buf__argsSerializer.writeInt32(builder_buf__resource.resourceId);
    builder_buf__argsSerializer.writePointer(builder_buf__call);
    builder_buf__argsSerializer.writePointer(builder_buf__callSync);
    InteropNativeModule._CallCallback(737226752, builder_buf__argsSerializer.asBuffer(), builder_buf__argsSerializer.length());
    builder_buf__argsSerializer.release();
    return; }
        }
        const builder_result : CustomBuilder | undefined = builder_buf
        const builderComponent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builderComponent_buf : ComponentContent | undefined
        if ((builderComponent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            builderComponent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const builderComponent_result : ComponentContent | undefined = builderComponent_buf
        const actionAreaDistance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let actionAreaDistance_buf : Length | undefined
        if ((actionAreaDistance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const actionAreaDistance_buf__selector : int32 = valueDeserializer.readInt8()
            let actionAreaDistance_buf_ : string | number | Resource | undefined
            if (actionAreaDistance_buf__selector == (0).toChar()) {
                actionAreaDistance_buf_ = (valueDeserializer.readString() as string)
            }
            else if (actionAreaDistance_buf__selector == (1).toChar()) {
                actionAreaDistance_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (actionAreaDistance_buf__selector == (2).toChar()) {
                actionAreaDistance_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for actionAreaDistance_buf_ has to be chosen through deserialisation.")
            }
            actionAreaDistance_buf = (actionAreaDistance_buf_ as string | number | Resource)
        }
        const actionAreaDistance_result : Length | undefined = actionAreaDistance_buf
        const onAction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAction_buf : (() => void) | undefined
        if ((onAction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onAction_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAction_buf__call : KPointer = valueDeserializer.readPointer()
            const onAction_buf__callSync : KPointer = valueDeserializer.readPointer()
            onAction_buf = ():void => { 
    const onAction_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onAction_buf__argsSerializer.writeInt32(onAction_buf__resource.resourceId);
    onAction_buf__argsSerializer.writePointer(onAction_buf__call);
    onAction_buf__argsSerializer.writePointer(onAction_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onAction_buf__argsSerializer.asBuffer(), onAction_buf__argsSerializer.length());
    onAction_buf__argsSerializer.release();
    return; }
        }
        const onAction_result : (() => void) | undefined = onAction_buf
        const onEnterActionArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onEnterActionArea_buf : (() => void) | undefined
        if ((onEnterActionArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onEnterActionArea_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterActionArea_buf__call : KPointer = valueDeserializer.readPointer()
            const onEnterActionArea_buf__callSync : KPointer = valueDeserializer.readPointer()
            onEnterActionArea_buf = ():void => { 
    const onEnterActionArea_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onEnterActionArea_buf__argsSerializer.writeInt32(onEnterActionArea_buf__resource.resourceId);
    onEnterActionArea_buf__argsSerializer.writePointer(onEnterActionArea_buf__call);
    onEnterActionArea_buf__argsSerializer.writePointer(onEnterActionArea_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onEnterActionArea_buf__argsSerializer.asBuffer(), onEnterActionArea_buf__argsSerializer.length());
    onEnterActionArea_buf__argsSerializer.release();
    return; }
        }
        const onEnterActionArea_result : (() => void) | undefined = onEnterActionArea_buf
        const onExitActionArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onExitActionArea_buf : (() => void) | undefined
        if ((onExitActionArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onExitActionArea_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onExitActionArea_buf__call : KPointer = valueDeserializer.readPointer()
            const onExitActionArea_buf__callSync : KPointer = valueDeserializer.readPointer()
            onExitActionArea_buf = ():void => { 
    const onExitActionArea_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onExitActionArea_buf__argsSerializer.writeInt32(onExitActionArea_buf__resource.resourceId);
    onExitActionArea_buf__argsSerializer.writePointer(onExitActionArea_buf__call);
    onExitActionArea_buf__argsSerializer.writePointer(onExitActionArea_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onExitActionArea_buf__argsSerializer.asBuffer(), onExitActionArea_buf__argsSerializer.length());
    onExitActionArea_buf__argsSerializer.release();
    return; }
        }
        const onExitActionArea_result : (() => void) | undefined = onExitActionArea_buf
        const onStateChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onStateChange_buf : ((state: SwipeActionState) => void) | undefined
        if ((onStateChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onStateChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onStateChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onStateChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onStateChange_buf = (state: SwipeActionState):void => { 
    const onStateChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onStateChange_buf__argsSerializer.writeInt32(onStateChange_buf__resource.resourceId);
    onStateChange_buf__argsSerializer.writePointer(onStateChange_buf__call);
    onStateChange_buf__argsSerializer.writePointer(onStateChange_buf__callSync);
    onStateChange_buf__argsSerializer.writeInt32(TypeChecker.SwipeActionState_ToNumeric(state));
    InteropNativeModule._CallCallback(-301561698, onStateChange_buf__argsSerializer.asBuffer(), onStateChange_buf__argsSerializer.length());
    onStateChange_buf__argsSerializer.release();
    return; }
        }
        const onStateChange_result : ((state: SwipeActionState) => void) | undefined = onStateChange_buf
        let value : SwipeActionItem = ({builder: builder_result, builderComponent: builderComponent_result, actionAreaDistance: actionAreaDistance_result, onAction: onAction_result, onEnterActionArea: onEnterActionArea_result, onExitActionArea: onExitActionArea_result, onStateChange: onStateChange_result} as SwipeActionItem)
        return value
    }
}
export class SwipeActionOptions_serializer {
    public static write(buffer: SerializerBase, value: SwipeActionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            let value_start_value_type : int32 = RuntimeType.UNDEFINED
            value_start_value_type = runtimeType(value_start_value)
            if (RuntimeType.FUNCTION == value_start_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_start_value_0  = value_start_value as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_start_value_0))
            }
            else if (RuntimeType.OBJECT == value_start_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_start_value_1  = value_start_value as SwipeActionItem
                SwipeActionItem_serializer.write(valueSerializer, value_start_value_1)
            }
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            let value_end_value_type : int32 = RuntimeType.UNDEFINED
            value_end_value_type = runtimeType(value_end_value)
            if (RuntimeType.FUNCTION == value_end_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_end_value_0  = value_end_value as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_end_value_0))
            }
            else if (RuntimeType.OBJECT == value_end_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_end_value_1  = value_end_value as SwipeActionItem
                SwipeActionItem_serializer.write(valueSerializer, value_end_value_1)
            }
        }
        const value_edgeEffect  = value.edgeEffect
        let value_edgeEffect_type : int32 = RuntimeType.UNDEFINED
        value_edgeEffect_type = runtimeType(value_edgeEffect)
        valueSerializer.writeInt8((value_edgeEffect_type).toChar())
        if ((value_edgeEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_edgeEffect_value  = (value_edgeEffect as SwipeEdgeEffect)
            valueSerializer.writeInt32(TypeChecker.SwipeEdgeEffect_ToNumeric(value_edgeEffect_value))
        }
        const value_onOffsetChange  = value.onOffsetChange
        let value_onOffsetChange_type : int32 = RuntimeType.UNDEFINED
        value_onOffsetChange_type = runtimeType(value_onOffsetChange)
        valueSerializer.writeInt8((value_onOffsetChange_type).toChar())
        if ((value_onOffsetChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onOffsetChange_value  = value_onOffsetChange!
            valueSerializer.holdAndWriteCallback(value_onOffsetChange_value)
        }
    }
    public static read(buffer: DeserializerBase): SwipeActionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : CustomBuilder | SwipeActionItem | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const start_buf__selector : int32 = valueDeserializer.readInt8()
            let start_buf_ : CustomBuilder | SwipeActionItem | undefined
            if (start_buf__selector == (0).toChar()) {
                const start_buf__u_resource : CallbackResource = valueDeserializer.readCallbackResource()
                const start_buf__u_call : KPointer = valueDeserializer.readPointer()
                const start_buf__u_callSync : KPointer = valueDeserializer.readPointer()
                start_buf_ = ():void => { 
    const start_buf__u_argsSerializer : SerializerBase = SerializerBase.hold();
    start_buf__u_argsSerializer.writeInt32(start_buf__u_resource.resourceId);
    start_buf__u_argsSerializer.writePointer(start_buf__u_call);
    start_buf__u_argsSerializer.writePointer(start_buf__u_callSync);
    InteropNativeModule._CallCallback(737226752, start_buf__u_argsSerializer.asBuffer(), start_buf__u_argsSerializer.length());
    start_buf__u_argsSerializer.release();
    return; }
            }
            else if (start_buf__selector == (1).toChar()) {
                start_buf_ = SwipeActionItem_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for start_buf_ has to be chosen through deserialisation.")
            }
            start_buf = (start_buf_ as CustomBuilder | SwipeActionItem)
        }
        const start_result : CustomBuilder | SwipeActionItem | undefined = start_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : CustomBuilder | SwipeActionItem | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const end_buf__selector : int32 = valueDeserializer.readInt8()
            let end_buf_ : CustomBuilder | SwipeActionItem | undefined
            if (end_buf__selector == (0).toChar()) {
                const end_buf__u_resource : CallbackResource = valueDeserializer.readCallbackResource()
                const end_buf__u_call : KPointer = valueDeserializer.readPointer()
                const end_buf__u_callSync : KPointer = valueDeserializer.readPointer()
                end_buf_ = ():void => { 
    const end_buf__u_argsSerializer : SerializerBase = SerializerBase.hold();
    end_buf__u_argsSerializer.writeInt32(end_buf__u_resource.resourceId);
    end_buf__u_argsSerializer.writePointer(end_buf__u_call);
    end_buf__u_argsSerializer.writePointer(end_buf__u_callSync);
    InteropNativeModule._CallCallback(737226752, end_buf__u_argsSerializer.asBuffer(), end_buf__u_argsSerializer.length());
    end_buf__u_argsSerializer.release();
    return; }
            }
            else if (end_buf__selector == (1).toChar()) {
                end_buf_ = SwipeActionItem_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for end_buf_ has to be chosen through deserialisation.")
            }
            end_buf = (end_buf_ as CustomBuilder | SwipeActionItem)
        }
        const end_result : CustomBuilder | SwipeActionItem | undefined = end_buf
        const edgeEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let edgeEffect_buf : SwipeEdgeEffect | undefined
        if ((edgeEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            edgeEffect_buf = TypeChecker.SwipeEdgeEffect_FromNumeric(valueDeserializer.readInt32())
        }
        const edgeEffect_result : SwipeEdgeEffect | undefined = edgeEffect_buf
        const onOffsetChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onOffsetChange_buf : ((offset: number) => void) | undefined
        if ((onOffsetChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onOffsetChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onOffsetChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onOffsetChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onOffsetChange_buf = (offset: number):void => { 
    const onOffsetChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onOffsetChange_buf__argsSerializer.writeInt32(onOffsetChange_buf__resource.resourceId);
    onOffsetChange_buf__argsSerializer.writePointer(onOffsetChange_buf__call);
    onOffsetChange_buf__argsSerializer.writePointer(onOffsetChange_buf__callSync);
    onOffsetChange_buf__argsSerializer.writeNumber(offset);
    InteropNativeModule._CallCallback(36519084, onOffsetChange_buf__argsSerializer.asBuffer(), onOffsetChange_buf__argsSerializer.length());
    onOffsetChange_buf__argsSerializer.release();
    return; }
        }
        const onOffsetChange_result : ((offset: number) => void) | undefined = onOffsetChange_buf
        let value : SwipeActionOptions = ({start: start_result, end: end_result, edgeEffect: edgeEffect_result, onOffsetChange: onOffsetChange_result} as SwipeActionOptions)
        return value
    }
}
