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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, resourceFinalizerRegister, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookMenuItemGroupAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { CustomBuilder } from './builder'
import { MenuItemGroupModifier } from './../MenuItemGroupModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkMenuItemGroupPeer extends ArkCommonMethodPeer {
    attributeSet?: MenuItemGroupModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    header?: arkui_component_units_ResourceStr | CustomBuilder;
    footer?: arkui_component_units_ResourceStr | CustomBuilder;
}
export interface MenuItemGroupAttribute extends CommonMethod {
    setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        throw new Error('Unimplemented method setMenuItemGroupOptions')
    }
    attributeModifier(value: AttributeModifier<MenuItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkMenuItemGroupComponent extends ArkCommonMethodComponent implements MenuItemGroupAttribute {
    getPeer(): ArkMenuItemGroupPeer {
        return (this.peer as ArkMenuItemGroupPeer)
    }
    public setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        if (this.checkPriority('setMenuItemGroupOptions')) {
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
    @memo @memo_skip
    style: ((attributes: MenuItemGroupAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuItemGroupComponent>((): ArkMenuItemGroupComponent => {
        return new ArkMenuItemGroupComponent()
    })
    NodeAttach<ArkMenuItemGroupPeer>((): ArkMenuItemGroupPeer => ArkMenuItemGroupPeer.create(receiver), (_: ArkMenuItemGroupPeer): void => {
        style?.(receiver)
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
            if (valueHolderForHeaderTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeaderTmpValueForIdx0  = valueHolderForHeaderTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForHeaderTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForHeaderTmpValueForIdx0ForIdx0  = valueHolderForHeaderTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForHeaderTmpValueForIdx0ForIdx0)
                } else if (valueHolderForHeaderTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForHeaderTmpValueForIdx0ForIdx1  = valueHolderForHeaderTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeaderTmpValueForIdx0ForIdx1)
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
            if (valueHolderForFooterTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFooterTmpValueForIdx0  = valueHolderForFooterTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForFooterTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForFooterTmpValueForIdx0ForIdx0  = valueHolderForFooterTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForFooterTmpValueForIdx0ForIdx0)
                } else if (valueHolderForFooterTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForFooterTmpValueForIdx0ForIdx1  = valueHolderForFooterTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForFooterTmpValueForIdx0ForIdx1)
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
        const headerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let headerTmpBuf : arkui_component_units_ResourceStr | CustomBuilder | undefined = undefined
        if ((headerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const headerTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let headerTmpBufOpt : arkui_component_units_ResourceStr | CustomBuilder | undefined
            if (headerTmpBufOptUnionSelector == (0).toByte()) {
                const headerTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let headerTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (headerTmpBufOptBufUUnionSelector == (0).toByte()) {
                    headerTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (headerTmpBufOptBufUUnionSelector == (1).toByte()) {
                    headerTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for headerTmpBufOptBufU has to be chosen through deserialisation.')
                }
                headerTmpBufOpt = (headerTmpBufOptBufU as string | arkui_component_units_Resource)
            } else if (headerTmpBufOptUnionSelector == (1).toByte()) {
                const headerTmpBufOptBufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const headerTmpBufOptBufUBufCall : KPointer = valueDeserializer.readPointer()
                const headerTmpBufOptBufUBufCallSync : KPointer = valueDeserializer.readPointer()
                const headerTmpBufOptBufUClosure  = ():void => {
                    const headerTmpBufOptBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    headerTmpBufOptBufUBufArgsSerializer.writeInt32(headerTmpBufOptBufUBufResource.resourceId);
                    headerTmpBufOptBufUBufArgsSerializer.writePointer(headerTmpBufOptBufUBufCall);
                    headerTmpBufOptBufUBufArgsSerializer.writePointer(headerTmpBufOptBufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, -1834072896, headerTmpBufOptBufUBufArgsSerializer.asBuffer(), headerTmpBufOptBufUBufArgsSerializer.length());
                    headerTmpBufOptBufUBufArgsSerializer.release();
                    return;
                }
                resourceFinalizerRegister(headerTmpBufOptBufUClosure, headerTmpBufOptBufUBufResource)
                headerTmpBufOpt = headerTmpBufOptBufUClosure
            } else {
                throw new Error('One of the branches for headerTmpBufOpt has to be chosen through deserialisation.')
            }
            headerTmpBuf = (headerTmpBufOpt as arkui_component_units_ResourceStr | CustomBuilder)
        }
        const headerTmpResult : arkui_component_units_ResourceStr | CustomBuilder | undefined = headerTmpBuf
        const footerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let footerTmpBuf : arkui_component_units_ResourceStr | CustomBuilder | undefined = undefined
        if ((footerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const footerTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let footerTmpBufOpt : arkui_component_units_ResourceStr | CustomBuilder | undefined
            if (footerTmpBufOptUnionSelector == (0).toByte()) {
                const footerTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let footerTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (footerTmpBufOptBufUUnionSelector == (0).toByte()) {
                    footerTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (footerTmpBufOptBufUUnionSelector == (1).toByte()) {
                    footerTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for footerTmpBufOptBufU has to be chosen through deserialisation.')
                }
                footerTmpBufOpt = (footerTmpBufOptBufU as string | arkui_component_units_Resource)
            } else if (footerTmpBufOptUnionSelector == (1).toByte()) {
                const footerTmpBufOptBufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
                const footerTmpBufOptBufUBufCall : KPointer = valueDeserializer.readPointer()
                const footerTmpBufOptBufUBufCallSync : KPointer = valueDeserializer.readPointer()
                const footerTmpBufOptBufUClosure  = ():void => {
                    const footerTmpBufOptBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                    footerTmpBufOptBufUBufArgsSerializer.writeInt32(footerTmpBufOptBufUBufResource.resourceId);
                    footerTmpBufOptBufUBufArgsSerializer.writePointer(footerTmpBufOptBufUBufCall);
                    footerTmpBufOptBufUBufArgsSerializer.writePointer(footerTmpBufOptBufUBufCallSync);
                    InteropNativeModule._CallCallbackSync(10, -1834072896, footerTmpBufOptBufUBufArgsSerializer.asBuffer(), footerTmpBufOptBufUBufArgsSerializer.length());
                    footerTmpBufOptBufUBufArgsSerializer.release();
                    return;
                }
                resourceFinalizerRegister(footerTmpBufOptBufUClosure, footerTmpBufOptBufUBufResource)
                footerTmpBufOpt = footerTmpBufOptBufUClosure
            } else {
                throw new Error('One of the branches for footerTmpBufOpt has to be chosen through deserialisation.')
            }
            footerTmpBuf = (footerTmpBufOpt as arkui_component_units_ResourceStr | CustomBuilder)
        }
        const footerTmpResult : arkui_component_units_ResourceStr | CustomBuilder | undefined = footerTmpBuf
        let value : MenuItemGroupOptions = ({header: headerTmpResult, footer: footerTmpResult} as MenuItemGroupOptions)
        return value
    }
}
