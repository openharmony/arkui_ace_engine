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
import { ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, Bindable, ArkCommonMethodComponent, Bindable_Boolean_serializer } from './common'
import { AttributeModifier, hookRefreshAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { CustomBuilder } from './builder'
import { ComponentContentBase } from '@arkui.ComponentContent'
import { RefreshModifier } from './../RefreshModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkRefreshPeer extends ArkCommonMethodPeer {
    attributeSet?: RefreshModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRefreshPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Refresh_construct(peerId, flags)
        const _peer  = new ArkRefreshPeer(_peerPtr, peerId, 'Refresh', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRefreshOptionsAttribute(value: RefreshOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RefreshOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RefreshInterface_setRefreshOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStateChangeAttribute(value: ((state: RefreshStatus) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRefreshingAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnRefreshing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRefreshOffsetAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setRefreshOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPullToRefreshAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setPullToRefresh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOffsetChangeAttribute(value: arkui_component_common_Callback<double, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnOffsetChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPullDownRatioAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setPullDownRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RefreshStatus {
    Inactive = 0,
    Drag = 1,
    OverDrag = 2,
    Refresh = 3,
    Done = 4,
    INACTIVE = 0,
    DRAG = 1,
    OVER_DRAG = 2,
    REFRESH = 3,
    DONE = 4
}
export interface RefreshOptions {
    refreshing: boolean | Bindable<boolean>;
    promptText?: arkui_component_units_ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContentBase;
}
export interface RefreshAttribute extends CommonMethod {
    setRefreshOptions(value: RefreshOptions): this {
        throw new Error('Unimplemented method setRefreshOptions')
    }
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        throw new Error('Unimplemented method onStateChange')
    }
    onRefreshing(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onRefreshing')
    }
    refreshOffset(value: double | undefined): this {
        throw new Error('Unimplemented method refreshOffset')
    }
    pullToRefresh(value: boolean | undefined): this {
        throw new Error('Unimplemented method pullToRefresh')
    }
    onOffsetChange(value: arkui_component_common_Callback<double, void> | undefined): this {
        throw new Error('Unimplemented method onOffsetChange')
    }
    pullDownRatio(value: double | undefined): this {
        throw new Error('Unimplemented method pullDownRatio')
    }
    attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRefreshComponent extends ArkCommonMethodComponent implements RefreshAttribute {
    getPeer(): ArkRefreshPeer {
        return (this.peer as ArkRefreshPeer)
    }
    public setRefreshOptions(value: RefreshOptions): this {
        if (this.checkPriority('setRefreshOptions')) {
            const value_casted = value as (RefreshOptions)
            this.getPeer()?.setRefreshOptionsAttribute(value_casted)
            this.applyOptionsFinish('RefreshAttribute');
            return this
        }
        return this
    }
    public onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        if (this.checkPriority('onStateChange')) {
            const value_casted = value as (((state: RefreshStatus) => void) | undefined)
            this.getPeer()?.setOnStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onRefreshing(value: (() => void) | undefined): this {
        if (this.checkPriority('onRefreshing')) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnRefreshingAttribute(value_casted)
            return this
        }
        return this
    }
    public refreshOffset(value: double | undefined): this {
        if (this.checkPriority('refreshOffset')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setRefreshOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public pullToRefresh(value: boolean | undefined): this {
        if (this.checkPriority('pullToRefresh')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPullToRefreshAttribute(value_casted)
            return this
        }
        return this
    }
    public onOffsetChange(value: arkui_component_common_Callback<double, void> | undefined): this {
        if (this.checkPriority('onOffsetChange')) {
            const value_casted = value as (arkui_component_common_Callback<double, void> | undefined)
            this.getPeer()?.setOnOffsetChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public pullDownRatio(value: double | undefined): this {
        if (this.checkPriority('pullDownRatio')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setPullDownRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRefreshAttributeModifier(this, value);
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
export function RefreshImpl(
    @memo @memo_skip
    style: ((attributes: RefreshAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRefreshComponent>((): ArkRefreshComponent => {
        return new ArkRefreshComponent()
    })
    NodeAttach<ArkRefreshPeer>((): ArkRefreshPeer => ArkRefreshPeer.create(receiver), (_: ArkRefreshPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class RefreshOptions_serializer {
    public static write(buffer: SerializerBase, value: RefreshOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRefreshing  = value.refreshing
        if (valueHolderForRefreshing instanceof boolean) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRefreshingForIdx0  = valueHolderForRefreshing as boolean
            valueSerializer.writeBoolean(valueHolderForRefreshingForIdx0)
        } else if (valueHolderForRefreshing instanceof Bindable) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRefreshingForIdx1  = valueHolderForRefreshing as Bindable<boolean>
            Bindable_Boolean_serializer.write(valueSerializer, valueHolderForRefreshingForIdx1)
        }
        const valueHolderForPromptText  = value.promptText
        if (valueHolderForPromptText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPromptTextTmpValue  = valueHolderForPromptText!
            if (valueHolderForPromptTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPromptTextTmpValueForIdx0  = valueHolderForPromptTextTmpValue as string
                valueSerializer.writeString(valueHolderForPromptTextTmpValueForIdx0)
            } else if (valueHolderForPromptTextTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPromptTextTmpValueForIdx1  = valueHolderForPromptTextTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPromptTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBuilder  = value.builder
        if (valueHolderForBuilder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBuilderTmpValue  = valueHolderForBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRefreshingContent  = value.refreshingContent
        if (valueHolderForRefreshingContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRefreshingContentTmpValue  = valueHolderForRefreshingContent!
            valueSerializer.holdAndWriteObject(valueHolderForRefreshingContentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RefreshOptions {
        let valueDeserializer : DeserializerBase = buffer
        const refreshingTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let refreshingTmpBuf : boolean | Bindable<boolean> | undefined
        if (refreshingTmpBufUnionSelector == (0).toByte()) {
            refreshingTmpBuf = valueDeserializer.readBoolean()
        } else if (refreshingTmpBufUnionSelector == (1).toByte()) {
            refreshingTmpBuf = Bindable_Boolean_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for refreshingTmpBuf has to be chosen through deserialisation.')
        }
        const refreshingTmpResult : boolean | Bindable<boolean> = (refreshingTmpBuf as boolean | Bindable<boolean>)
        const promptTextTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let promptTextTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((promptTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const promptTextTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let promptTextTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (promptTextTmpBufOptUnionSelector == (0).toByte()) {
                promptTextTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (promptTextTmpBufOptUnionSelector == (1).toByte()) {
                promptTextTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for promptTextTmpBufOpt has to be chosen through deserialisation.')
            }
            promptTextTmpBuf = (promptTextTmpBufOpt as string | arkui_component_units_Resource)
        }
        const promptTextTmpResult : arkui_component_units_ResourceStr | undefined = promptTextTmpBuf
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
        const refreshingContentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let refreshingContentTmpBuf : ComponentContentBase | undefined = undefined
        if ((refreshingContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            refreshingContentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const refreshingContentTmpResult : ComponentContentBase | undefined = refreshingContentTmpBuf
        let value : RefreshOptions = ({refreshing: refreshingTmpResult, promptText: promptTextTmpResult, builder: builderTmpResult, refreshingContent: refreshingContentTmpResult} as RefreshOptions)
        return value
    }
}
