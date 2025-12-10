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
import { ListDividerOptions_serializer, ListDividerOptions } from './list'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { ChildrenMainSize, AttributeModifier, hookListItemGroupChildrenMainSizeImpl, hookListItemGroupAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { CustomBuilder } from './builder'
import { ComponentContentBase } from '@arkui.ComponentContent'
import { ListItemGroupModifier } from './../ListItemGroupModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkListItemGroupPeer extends ArkCommonMethodPeer {
    attributeSet?: ListItemGroupModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItemGroup_construct(peerId, flags)
        const _peer  = new ArkListItemGroupPeer(_peerPtr, peerId, 'ListItemGroup', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemGroupOptionsAttribute(options?: ListItemGroupOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ListItemGroupOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemGroupInterface_setListItemGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ListDividerOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ListDividerOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListItemGroupAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ListItemGroupStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemGroupOptions {
    header?: CustomBuilder;
    headerComponent?: ComponentContentBase;
    footer?: CustomBuilder;
    footerComponent?: ComponentContentBase;
    space?: double | string;
    style?: ListItemGroupStyle;
}
export interface ListItemGroupAttribute extends CommonMethod {
    setListItemGroupOptions(options?: ListItemGroupOptions): this {
        throw new Error('Unimplemented method setListItemGroupOptions')
    }
    divider(value: ListDividerOptions | null | undefined): this {
        throw new Error('Unimplemented method divider')
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        throw new Error('Unimplemented method childrenMainSize')
    }
    attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkListItemGroupComponent extends ArkCommonMethodComponent implements ListItemGroupAttribute {
    getPeer(): ArkListItemGroupPeer {
        return (this.peer as ArkListItemGroupPeer)
    }
    public setListItemGroupOptions(options?: ListItemGroupOptions): this {
        if (this.checkPriority('setListItemGroupOptions')) {
            const options_casted = options as (ListItemGroupOptions | undefined)
            this.getPeer()?.setListItemGroupOptionsAttribute(options_casted)
            this.applyOptionsFinish('ListItemGroupAttribute');
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | null | undefined): this {
        if (this.checkPriority('divider')) {
            const value_casted = value as (ListDividerOptions | null | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority('childrenMainSize')) {
            hookListItemGroupChildrenMainSizeImpl(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookListItemGroupAttributeModifier(this, value);
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
export function ListItemGroupImpl(
    @memo @memo_skip
    style: ((attributes: ListItemGroupAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkListItemGroupComponent>((): ArkListItemGroupComponent => {
        return new ArkListItemGroupComponent()
    })
    NodeAttach<ArkListItemGroupPeer>((): ArkListItemGroupPeer => ArkListItemGroupPeer.create(receiver), (_: ArkListItemGroupPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ListItemGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: ListItemGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHeader  = value.header
        if (valueHolderForHeader !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeaderTmpValue  = valueHolderForHeader!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForHeaderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeaderComponent  = value.headerComponent
        if (valueHolderForHeaderComponent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeaderComponentTmpValue  = valueHolderForHeaderComponent!
            valueSerializer.holdAndWriteObject(valueHolderForHeaderComponentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFooter  = value.footer
        if (valueHolderForFooter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFooterTmpValue  = valueHolderForFooter!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForFooterTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFooterComponent  = value.footerComponent
        if (valueHolderForFooterComponent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFooterComponentTmpValue  = valueHolderForFooterComponent!
            valueSerializer.holdAndWriteObject(valueHolderForFooterComponentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as ListItemGroupStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ListItemGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const headerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let headerTmpBuf : CustomBuilder | undefined = undefined
        if ((headerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const headerTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const headerTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const headerTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const headerTmpBufOptClosure  = ():void => {
                const headerTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                headerTmpBufOptBufArgsSerializer.writeInt32(headerTmpBufOptBufResource.resourceId);
                headerTmpBufOptBufArgsSerializer.writePointer(headerTmpBufOptBufCall);
                headerTmpBufOptBufArgsSerializer.writePointer(headerTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, headerTmpBufOptBufArgsSerializer.asBuffer(), headerTmpBufOptBufArgsSerializer.length());
                headerTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(headerTmpBufOptClosure, headerTmpBufOptBufResource)
            headerTmpBuf = headerTmpBufOptClosure
        }
        const headerTmpResult : CustomBuilder | undefined = headerTmpBuf
        const headerComponentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let headerComponentTmpBuf : ComponentContentBase | undefined = undefined
        if ((headerComponentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            headerComponentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const headerComponentTmpResult : ComponentContentBase | undefined = headerComponentTmpBuf
        const footerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let footerTmpBuf : CustomBuilder | undefined = undefined
        if ((footerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const footerTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const footerTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const footerTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const footerTmpBufOptClosure  = ():void => {
                const footerTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                footerTmpBufOptBufArgsSerializer.writeInt32(footerTmpBufOptBufResource.resourceId);
                footerTmpBufOptBufArgsSerializer.writePointer(footerTmpBufOptBufCall);
                footerTmpBufOptBufArgsSerializer.writePointer(footerTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, footerTmpBufOptBufArgsSerializer.asBuffer(), footerTmpBufOptBufArgsSerializer.length());
                footerTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(footerTmpBufOptClosure, footerTmpBufOptBufResource)
            footerTmpBuf = footerTmpBufOptClosure
        }
        const footerTmpResult : CustomBuilder | undefined = footerTmpBuf
        const footerComponentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let footerComponentTmpBuf : ComponentContentBase | undefined = undefined
        if ((footerComponentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            footerComponentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const footerComponentTmpResult : ComponentContentBase | undefined = footerComponentTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let spaceTmpBuf : double | string | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBufOpt : double | string | undefined
            if (spaceTmpBufOptUnionSelector == (0).toByte()) {
                spaceTmpBufOpt = valueDeserializer.readFloat64()
            } else if (spaceTmpBufOptUnionSelector == (1).toByte()) {
                spaceTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for spaceTmpBufOpt has to be chosen through deserialisation.')
            }
            spaceTmpBuf = (spaceTmpBufOpt as double | string)
        }
        const spaceTmpResult : double | string | undefined = spaceTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : ListItemGroupStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = ListItemGroupStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : ListItemGroupStyle | undefined = styleTmpBuf
        let value : ListItemGroupOptions = ({header: headerTmpResult, headerComponent: headerComponentTmpResult, footer: footerTmpResult, footerComponent: footerComponentTmpResult, space: spaceTmpResult, style: styleTmpResult} as ListItemGroupOptions)
        return value
    }
}
