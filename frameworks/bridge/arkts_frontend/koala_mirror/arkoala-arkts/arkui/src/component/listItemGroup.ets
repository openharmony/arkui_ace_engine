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
import { ListDividerOptions_serializer, ListDividerOptions } from "./list"
import { ChildrenMainSize_serializer, ArkCommonMethodPeer, CommonMethod, ChildrenMainSize, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkListItemGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItemGroup_construct(peerId, flags)
        const _peer  = new ArkListItemGroupPeer(_peerPtr, peerId, "ListItemGroup", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemGroupOptionsAttribute(options?: ListItemGroupOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ListItemGroupOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupInterface_setListItemGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ListDividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ListDividerOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChildrenMainSizeAttribute(value: ChildrenMainSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ChildrenMainSize_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupAttribute_setChildrenMainSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ListItemGroupStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemGroupOptions {
    header?: CustomBuilder;
    headerComponent?: ComponentContent;
    footer?: CustomBuilder;
    footerComponent?: ComponentContent;
    space?: number | string;
    style?: ListItemGroupStyle;
}
export interface ListItemGroupAttribute extends CommonMethod {
    divider(value: ListDividerOptions | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        throw new Error("Unimplemented method childrenMainSize")
    }
    attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkListItemGroupStyle extends ArkCommonMethodStyle implements ListItemGroupAttribute {
    divider_value?: ListDividerOptions | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    attributeModifier_value?: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    public divider(value: ListDividerOptions | undefined): this {
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ListItemGroupAttribute): void {
        super.apply(target)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.childrenMainSize_value !== undefined)
            target.childrenMainSize(this.childrenMainSize_value!)
    }
}

export class ArkListItemGroupComponent extends ArkCommonMethodComponent implements ListItemGroupAttribute {
    getPeer(): ArkListItemGroupPeer {
        return (this.peer as ArkListItemGroupPeer)
    }
    public setListItemGroupOptions(options?: ListItemGroupOptions): this {
        if (this.checkPriority("setListItemGroupOptions")) {
            const options_casted = options as (ListItemGroupOptions | undefined)
            this.getPeer()?.setListItemGroupOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize | undefined)
            this.getPeer()?.setChildrenMainSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withListItemGroupStyle(receiver: ListItemGroupAttribute, modifier: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkListItemGroupStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ListItemGroup")
// export function ListItemGroup(
//     options?: ListItemGroupOptions,
//     @memo
//     content_?: () => void,
// ): ListItemGroupAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ListItemGroup(
    @memo
    style: ((attributes: ListItemGroupAttribute) => void) | undefined,
    options?: ListItemGroupOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkListItemGroupComponent>((): ArkListItemGroupComponent => {
        return new ArkListItemGroupComponent()
    })
    NodeAttach<ArkListItemGroupPeer>((): ArkListItemGroupPeer => ArkListItemGroupPeer.create(receiver), (_: ArkListItemGroupPeer): void => {
        receiver.setListItemGroupOptions(options)
        style?.(receiver)
        withListItemGroupStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkListItemGroupSet extends ArkCommonMethodSet implements ListItemGroupAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _divider_flag?: boolean
    _divider0_value?: ListDividerOptions | undefined
    _childrenMainSize_flag?: boolean
    _childrenMainSize0_value?: ChildrenMainSize | undefined
    applyModifierPatch(component: ListItemGroupAttribute): void {
        if (this._divider_flag)
            component.divider((this._divider0_value as ListDividerOptions | undefined))
        if (this._childrenMainSize_flag)
            component.childrenMainSize((this._childrenMainSize0_value as ChildrenMainSize | undefined))
    }
    public divider(value: ListDividerOptions | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        this._childrenMainSize_flag = true
        this._childrenMainSize0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ListItemGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: ListItemGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_header  = value.header
        let value_header_type : int32 = RuntimeType.UNDEFINED
        value_header_type = runtimeType(value_header)
        valueSerializer.writeInt8((value_header_type).toChar())
        if ((value_header_type) != (RuntimeType.UNDEFINED)) {
            const value_header_value  = value_header!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_header_value))
        }
        const value_headerComponent  = value.headerComponent
        let value_headerComponent_type : int32 = RuntimeType.UNDEFINED
        value_headerComponent_type = runtimeType(value_headerComponent)
        valueSerializer.writeInt8((value_headerComponent_type).toChar())
        if ((value_headerComponent_type) != (RuntimeType.UNDEFINED)) {
            const value_headerComponent_value  = value_headerComponent!
            ComponentContent_serializer.write(valueSerializer, value_headerComponent_value)
        }
        const value_footer  = value.footer
        let value_footer_type : int32 = RuntimeType.UNDEFINED
        value_footer_type = runtimeType(value_footer)
        valueSerializer.writeInt8((value_footer_type).toChar())
        if ((value_footer_type) != (RuntimeType.UNDEFINED)) {
            const value_footer_value  = value_footer!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_footer_value))
        }
        const value_footerComponent  = value.footerComponent
        let value_footerComponent_type : int32 = RuntimeType.UNDEFINED
        value_footerComponent_type = runtimeType(value_footerComponent)
        valueSerializer.writeInt8((value_footerComponent_type).toChar())
        if ((value_footerComponent_type) != (RuntimeType.UNDEFINED)) {
            const value_footerComponent_value  = value_footerComponent!
            ComponentContent_serializer.write(valueSerializer, value_footerComponent_value)
        }
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_space_value_0  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_0)
            }
            else if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_space_value_1  = value_space_value as string
                valueSerializer.writeString(value_space_value_1)
            }
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as ListItemGroupStyle)
            valueSerializer.writeInt32(TypeChecker.ListItemGroupStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): ListItemGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const header_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let header_buf : CustomBuilder | undefined
        if ((header_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const header_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const header_buf__call : KPointer = valueDeserializer.readPointer()
            const header_buf__callSync : KPointer = valueDeserializer.readPointer()
            header_buf = ():void => { 
    const header_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    header_buf__argsSerializer.writeInt32(header_buf__resource.resourceId);
    header_buf__argsSerializer.writePointer(header_buf__call);
    header_buf__argsSerializer.writePointer(header_buf__callSync);
    InteropNativeModule._CallCallback(737226752, header_buf__argsSerializer.asBuffer(), header_buf__argsSerializer.length());
    header_buf__argsSerializer.release();
    return; }
        }
        const header_result : CustomBuilder | undefined = header_buf
        const headerComponent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let headerComponent_buf : ComponentContent | undefined
        if ((headerComponent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            headerComponent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const headerComponent_result : ComponentContent | undefined = headerComponent_buf
        const footer_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footer_buf : CustomBuilder | undefined
        if ((footer_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const footer_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const footer_buf__call : KPointer = valueDeserializer.readPointer()
            const footer_buf__callSync : KPointer = valueDeserializer.readPointer()
            footer_buf = ():void => { 
    const footer_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    footer_buf__argsSerializer.writeInt32(footer_buf__resource.resourceId);
    footer_buf__argsSerializer.writePointer(footer_buf__call);
    footer_buf__argsSerializer.writePointer(footer_buf__callSync);
    InteropNativeModule._CallCallback(737226752, footer_buf__argsSerializer.asBuffer(), footer_buf__argsSerializer.length());
    footer_buf__argsSerializer.release();
    return; }
        }
        const footer_result : CustomBuilder | undefined = footer_buf
        const footerComponent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footerComponent_buf : ComponentContent | undefined
        if ((footerComponent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            footerComponent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const footerComponent_result : ComponentContent | undefined = footerComponent_buf
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : number | string | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : number | string | undefined
            if (space_buf__selector == (0).toChar()) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (space_buf__selector == (1).toChar()) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for space_buf_ has to be chosen through deserialisation.")
            }
            space_buf = (space_buf_ as number | string)
        }
        const space_result : number | string | undefined = space_buf
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : ListItemGroupStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.ListItemGroupStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : ListItemGroupStyle | undefined = style_buf
        let value : ListItemGroupOptions = ({header: header_result, headerComponent: headerComponent_result, footer: footer_result, footerComponent: footerComponent_result, space: space_result, style: style_result} as ListItemGroupOptions)
        return value
    }
}
