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
import { ResourceStr } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { CustomBuilder } from "./builder"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMenuItemGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MenuItemGroup_construct(peerId, flags)
        const _peer  = new ArkMenuItemGroupPeer(_peerPtr, peerId, "MenuItemGroup", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuItemGroupOptionsAttribute(value?: MenuItemGroupOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            MenuItemGroupOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemGroupInterface_setMenuItemGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MenuItemGroupOptions {
    header?: ResourceStr | CustomBuilder;
    footer?: ResourceStr | CustomBuilder;
}
export interface MenuItemGroupAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMenuItemGroupStyle extends ArkCommonMethodStyle implements MenuItemGroupAttribute {
    attributeModifier_value?: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: MenuItemGroupAttribute): void {
        super.apply(target)
    }
}

export class ArkMenuItemGroupComponent extends ArkCommonMethodComponent implements MenuItemGroupAttribute {
    getPeer(): ArkMenuItemGroupPeer {
        return (this.peer as ArkMenuItemGroupPeer)
    }
    public setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        if (this.checkPriority("setMenuItemGroupOptions")) {
            const value_casted = value as (MenuItemGroupOptions | undefined)
            this.getPeer()?.setMenuItemGroupOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withMenuItemGroupStyle(receiver: MenuItemGroupAttribute, modifier: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkMenuItemGroupStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("MenuItemGroup")
// export function MenuItemGroup(
//     value?: MenuItemGroupOptions,
//     @memo
//     content_?: () => void,
// ): MenuItemGroupAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function MenuItemGroup(
    @memo
    style: ((attributes: MenuItemGroupAttribute) => void) | undefined,
    value?: MenuItemGroupOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuItemGroupComponent>((): ArkMenuItemGroupComponent => {
        return new ArkMenuItemGroupComponent()
    })
    NodeAttach<ArkMenuItemGroupPeer>((): ArkMenuItemGroupPeer => ArkMenuItemGroupPeer.create(receiver), (_: ArkMenuItemGroupPeer): void => {
        receiver.setMenuItemGroupOptions(value)
        style?.(receiver)
        withMenuItemGroupStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkMenuItemGroupSet extends ArkCommonMethodSet implements MenuItemGroupAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: MenuItemGroupAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class MenuItemGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuItemGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_header  = value.header
        let value_header_type : int32 = RuntimeType.UNDEFINED
        value_header_type = runtimeType(value_header)
        valueSerializer.writeInt8((value_header_type).toChar())
        if ((value_header_type) != (RuntimeType.UNDEFINED)) {
            const value_header_value  = value_header!
            let value_header_value_type : int32 = RuntimeType.UNDEFINED
            value_header_value_type = runtimeType(value_header_value)
            if ((RuntimeType.STRING == value_header_value_type) || (RuntimeType.OBJECT == value_header_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_header_value_0  = value_header_value as ResourceStr
                let value_header_value_0_type : int32 = RuntimeType.UNDEFINED
                value_header_value_0_type = runtimeType(value_header_value_0)
                if (RuntimeType.STRING == value_header_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_header_value_0_0  = value_header_value_0 as string
                    valueSerializer.writeString(value_header_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_header_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_header_value_0_1  = value_header_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_header_value_0_1)
                }
            }
            else if (RuntimeType.FUNCTION == value_header_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_header_value_1  = value_header_value as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_header_value_1))
            }
        }
        const value_footer  = value.footer
        let value_footer_type : int32 = RuntimeType.UNDEFINED
        value_footer_type = runtimeType(value_footer)
        valueSerializer.writeInt8((value_footer_type).toChar())
        if ((value_footer_type) != (RuntimeType.UNDEFINED)) {
            const value_footer_value  = value_footer!
            let value_footer_value_type : int32 = RuntimeType.UNDEFINED
            value_footer_value_type = runtimeType(value_footer_value)
            if ((RuntimeType.STRING == value_footer_value_type) || (RuntimeType.OBJECT == value_footer_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_footer_value_0  = value_footer_value as ResourceStr
                let value_footer_value_0_type : int32 = RuntimeType.UNDEFINED
                value_footer_value_0_type = runtimeType(value_footer_value_0)
                if (RuntimeType.STRING == value_footer_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_footer_value_0_0  = value_footer_value_0 as string
                    valueSerializer.writeString(value_footer_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_footer_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_footer_value_0_1  = value_footer_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_footer_value_0_1)
                }
            }
            else if (RuntimeType.FUNCTION == value_footer_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_footer_value_1  = value_footer_value as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_footer_value_1))
            }
        }
    }
    public static read(buffer: DeserializerBase): MenuItemGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const header_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let header_buf : ResourceStr | CustomBuilder | undefined
        if ((header_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const header_buf__selector : int32 = valueDeserializer.readInt8()
            let header_buf_ : ResourceStr | CustomBuilder | undefined
            if (header_buf__selector == (0).toChar()) {
                const header_buf__u_selector : int32 = valueDeserializer.readInt8()
                let header_buf__u : string | Resource | undefined
                if (header_buf__u_selector == (0).toChar()) {
                    header_buf__u = (valueDeserializer.readString() as string)
                }
                else if (header_buf__u_selector == (1).toChar()) {
                    header_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for header_buf__u has to be chosen through deserialisation.")
                }
                header_buf_ = (header_buf__u as string | Resource)
            }
            else if (header_buf__selector == (1).toChar()) {
                const header_buf__u_resource : CallbackResource = valueDeserializer.readCallbackResource()
                const header_buf__u_call : KPointer = valueDeserializer.readPointer()
                const header_buf__u_callSync : KPointer = valueDeserializer.readPointer()
                header_buf_ = ():void => { 
    const header_buf__u_argsSerializer : SerializerBase = SerializerBase.hold();
    header_buf__u_argsSerializer.writeInt32(header_buf__u_resource.resourceId);
    header_buf__u_argsSerializer.writePointer(header_buf__u_call);
    header_buf__u_argsSerializer.writePointer(header_buf__u_callSync);
    InteropNativeModule._CallCallback(737226752, header_buf__u_argsSerializer.asBuffer(), header_buf__u_argsSerializer.length());
    header_buf__u_argsSerializer.release();
    return; }
            }
            else {
                throw new Error("One of the branches for header_buf_ has to be chosen through deserialisation.")
            }
            header_buf = (header_buf_ as ResourceStr | CustomBuilder)
        }
        const header_result : ResourceStr | CustomBuilder | undefined = header_buf
        const footer_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footer_buf : ResourceStr | CustomBuilder | undefined
        if ((footer_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const footer_buf__selector : int32 = valueDeserializer.readInt8()
            let footer_buf_ : ResourceStr | CustomBuilder | undefined
            if (footer_buf__selector == (0).toChar()) {
                const footer_buf__u_selector : int32 = valueDeserializer.readInt8()
                let footer_buf__u : string | Resource | undefined
                if (footer_buf__u_selector == (0).toChar()) {
                    footer_buf__u = (valueDeserializer.readString() as string)
                }
                else if (footer_buf__u_selector == (1).toChar()) {
                    footer_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for footer_buf__u has to be chosen through deserialisation.")
                }
                footer_buf_ = (footer_buf__u as string | Resource)
            }
            else if (footer_buf__selector == (1).toChar()) {
                const footer_buf__u_resource : CallbackResource = valueDeserializer.readCallbackResource()
                const footer_buf__u_call : KPointer = valueDeserializer.readPointer()
                const footer_buf__u_callSync : KPointer = valueDeserializer.readPointer()
                footer_buf_ = ():void => { 
    const footer_buf__u_argsSerializer : SerializerBase = SerializerBase.hold();
    footer_buf__u_argsSerializer.writeInt32(footer_buf__u_resource.resourceId);
    footer_buf__u_argsSerializer.writePointer(footer_buf__u_call);
    footer_buf__u_argsSerializer.writePointer(footer_buf__u_callSync);
    InteropNativeModule._CallCallback(737226752, footer_buf__u_argsSerializer.asBuffer(), footer_buf__u_argsSerializer.length());
    footer_buf__u_argsSerializer.release();
    return; }
            }
            else {
                throw new Error("One of the branches for footer_buf_ has to be chosen through deserialisation.")
            }
            footer_buf = (footer_buf_ as ResourceStr | CustomBuilder)
        }
        const footer_result : ResourceStr | CustomBuilder | undefined = footer_buf
        let value : MenuItemGroupOptions = ({header: header_result, footer: footer_result} as MenuItemGroupOptions)
        return value
    }
}
