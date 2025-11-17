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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookMenuItemGroupAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ResourceStr } from "./units"
import { Resource } from "global.resource"
import { CustomBuilder } from "./builder"
import { MenuItemGroupModifier } from "./../MenuItemGroupModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
import { ModifierStateManager } from '../CommonModifier';
export class ArkMenuItemGroupPeer extends ArkCommonMethodPeer {
    attributeSet?: MenuItemGroupModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MenuItemGroup_construct(peerId, flags)
        const _peer  = new ArkMenuItemGroupPeer(_peerPtr, peerId, 'MenuItemGroup', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuItemGroupOptionsAttribute(value?: MenuItemGroupOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            MenuItemGroupOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
    setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        throw new Error("Unimplemented method setMenuItemGroupOptions")
    }
    attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMenuItemGroupStyle extends ArkCommonMethodStyle implements MenuItemGroupAttribute {
    attributeModifier_value?: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkMenuItemGroupComponent extends ArkCommonMethodComponent implements MenuItemGroupAttribute {
    getPeer(): ArkMenuItemGroupPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkMenuItemGroupPeer)
    }
    public setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        if (this.checkPriority("setMenuItemGroupOptions")) {
            const value_casted = value as (MenuItemGroupOptions | undefined)
            this.getPeer()?.setMenuItemGroupOptionsAttribute(value_casted)
            this.applyOptionsFinish('MenuItemGroupAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookMenuItemGroupAttributeModifier(this, value);
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
export function MenuItemGroupImpl(
    @memo
    style: ((attributes: MenuItemGroupAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuItemGroupComponent>((): ArkMenuItemGroupComponent => {
        return new ArkMenuItemGroupComponent()
    })
    NodeAttach<ArkMenuItemGroupPeer>((): ArkMenuItemGroupPeer => ArkMenuItemGroupPeer.create(receiver), (peer: ArkMenuItemGroupPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class MenuItemGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuItemGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHeader  = value.header
        if (valueHolderForHeader !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeaderTmpValue  = valueHolderForHeader!
            if (valueHolderForHeaderTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeaderTmpValueForIdx0  = valueHolderForHeaderTmpValue as ResourceStr
                if (valueHolderForHeaderTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForHeaderTmpValueForIdx0ForIdx0  = valueHolderForHeaderTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForHeaderTmpValueForIdx0ForIdx0)
                } else if (valueHolderForHeaderTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForHeaderTmpValueForIdx0ForIdx1  = valueHolderForHeaderTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForHeaderTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForHeaderTmpValue instanceof CustomBuilder) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeaderTmpValueForIdx1  = valueHolderForHeaderTmpValue as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForHeaderTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFooter  = value.footer
        if (valueHolderForFooter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFooterTmpValue  = valueHolderForFooter!
            if (valueHolderForFooterTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFooterTmpValueForIdx0  = valueHolderForFooterTmpValue as ResourceStr
                if (valueHolderForFooterTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForFooterTmpValueForIdx0ForIdx0  = valueHolderForFooterTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForFooterTmpValueForIdx0ForIdx0)
                } else if (valueHolderForFooterTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForFooterTmpValueForIdx0ForIdx1  = valueHolderForFooterTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForFooterTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForFooterTmpValue instanceof CustomBuilder) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFooterTmpValueForIdx1  = valueHolderForFooterTmpValue as CustomBuilder
                valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForFooterTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MenuItemGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const headerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let headerTmpBuf : ResourceStr | CustomBuilder | undefined = undefined
        if ((headerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const headerTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let headerTmpBuf_ : ResourceStr | CustomBuilder | undefined
            if (headerTmpBuf_UnionSelector == (0).toChar()) {
                const headerTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let headerTmpBuf_BufU : string | Resource | undefined
                if (headerTmpBuf_BufUUnionSelector == (0).toChar()) {
                    headerTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (headerTmpBuf_BufUUnionSelector == (1).toChar()) {
                    headerTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for headerTmpBuf_BufU has to be chosen through deserialisation.")
                }
                headerTmpBuf_ = (headerTmpBuf_BufU as string | Resource)
            } else if (headerTmpBuf_UnionSelector == (1).toChar()) {
                const headerTmpBuf_BufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const headerTmpBuf_BufUBufCall : KPointer = valueDeserializer.readPointer()
                const headerTmpBuf_BufUBufCallSync : KPointer = valueDeserializer.readPointer()
                headerTmpBuf_ = ():void => {
                    const headerTmpBuf_BufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    headerTmpBuf_BufUBufArgsSerializer.writeInt32(headerTmpBuf_BufUBufResource.resourceId);
                    headerTmpBuf_BufUBufArgsSerializer.writePointer(headerTmpBuf_BufUBufCall);
                    headerTmpBuf_BufUBufArgsSerializer.writePointer(headerTmpBuf_BufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, 737226752, headerTmpBuf_BufUBufArgsSerializer.asBuffer(), headerTmpBuf_BufUBufArgsSerializer.length());
                    headerTmpBuf_BufUBufArgsSerializer.release();
                    return;
                }
            } else {
                throw new Error("One of the branches for headerTmpBuf_ has to be chosen through deserialisation.")
            }
            headerTmpBuf = (headerTmpBuf_ as ResourceStr | CustomBuilder)
        }
        const headerTmpResult : ResourceStr | CustomBuilder | undefined = headerTmpBuf
        const footerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footerTmpBuf : ResourceStr | CustomBuilder | undefined = undefined
        if ((footerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const footerTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let footerTmpBuf_ : ResourceStr | CustomBuilder | undefined
            if (footerTmpBuf_UnionSelector == (0).toChar()) {
                const footerTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let footerTmpBuf_BufU : string | Resource | undefined
                if (footerTmpBuf_BufUUnionSelector == (0).toChar()) {
                    footerTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (footerTmpBuf_BufUUnionSelector == (1).toChar()) {
                    footerTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for footerTmpBuf_BufU has to be chosen through deserialisation.")
                }
                footerTmpBuf_ = (footerTmpBuf_BufU as string | Resource)
            } else if (footerTmpBuf_UnionSelector == (1).toChar()) {
                const footerTmpBuf_BufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const footerTmpBuf_BufUBufCall : KPointer = valueDeserializer.readPointer()
                const footerTmpBuf_BufUBufCallSync : KPointer = valueDeserializer.readPointer()
                footerTmpBuf_ = ():void => {
                    const footerTmpBuf_BufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    footerTmpBuf_BufUBufArgsSerializer.writeInt32(footerTmpBuf_BufUBufResource.resourceId);
                    footerTmpBuf_BufUBufArgsSerializer.writePointer(footerTmpBuf_BufUBufCall);
                    footerTmpBuf_BufUBufArgsSerializer.writePointer(footerTmpBuf_BufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, 737226752, footerTmpBuf_BufUBufArgsSerializer.asBuffer(), footerTmpBuf_BufUBufArgsSerializer.length());
                    footerTmpBuf_BufUBufArgsSerializer.release();
                    return;
                }
            } else {
                throw new Error("One of the branches for footerTmpBuf_ has to be chosen through deserialisation.")
            }
            footerTmpBuf = (footerTmpBuf_ as ResourceStr | CustomBuilder)
        }
        const footerTmpResult : ResourceStr | CustomBuilder | undefined = footerTmpBuf
        let value : MenuItemGroupOptions = ({header: headerTmpResult, footer: footerTmpResult} as MenuItemGroupOptions)
        return value
    }
}
