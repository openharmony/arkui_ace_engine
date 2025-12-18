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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { RecordData, Callback as ohos_base_Callback, ErrorCallback, BusinessError } from '@ohos.base'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent } from './common'
import { extractors, AttributeModifier, hookUIExtensionComponentAttributeModifier, AttributeUpdater } from '#handwritten'
import { VoidCallback } from './units'
import { default as Want } from '@ohos.app.ability.Want'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ComponentContent } from '@arkui.ComponentContent'
import { UIExtensionComponentModifier } from './../UIExtensionComponentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { ComponentContent_serializer } from './../framework/ComponentContent'
export interface UIExtensionProxy {
    send(data: Record<string, RecordData>): void
    sendSync(data: Record<string, RecordData>): Record<string, RecordData>
    onAsyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy>): void
    onSyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy>): void
    offAsyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy> | undefined): void
    offSyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy> | undefined): void
}
export class UIExtensionProxyInternal implements MaterializedBase,UIExtensionProxy {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UIExtensionProxyInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, UIExtensionProxyInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        return new UIExtensionProxyInternal(MaterializedBaseTag.NOP, ptr)
    }
    public send(data: Record<string, RecordData>): void {
        const data_casted = data as (Record<string, RecordData>)
        this.send_serialize(data_casted)
        return
    }
    public sendSync(data: Record<string, RecordData>): Record<string, RecordData> {
        const data_casted = data as (Record<string, RecordData>)
        return this.sendSync_serialize(data_casted)
    }
    public onAsyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy>): void {
        const callback__casted = callback_ as (ohos_base_Callback<UIExtensionProxy>)
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ohos_base_Callback<UIExtensionProxy>): void {
        const callback__casted = callback_ as (ohos_base_Callback<UIExtensionProxy>)
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ohos_base_Callback<UIExtensionProxy>): void {
        const callback__casted = callback_ as (ohos_base_Callback<UIExtensionProxy> | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ohos_base_Callback<UIExtensionProxy>): void {
        const callback__casted = callback_ as (ohos_base_Callback<UIExtensionProxy> | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    private send_serialize(data: Record<string, RecordData>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((data.size).toInt())
        for (const pair of data) {
            const dataKeyVar = pair[0]
            const dataValueVar = pair[1]
            thisSerializer.writeString(dataKeyVar)
            if (dataValueVar !== undefined && dataValueVar !== null) {
                thisSerializer.writeInt8(RuntimeType.OBJECT)
                const dataValueVarTmpValue  = dataValueVar!
                thisSerializer.holdAndWriteObject(dataValueVarTmpValue)
            } else {
                thisSerializer.writeInt8(RuntimeType.UNDEFINED)
            }
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Record<string, RecordData>): Record<string, RecordData> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((data.size).toInt())
        for (const pair of data) {
            const dataKeyVar = pair[0]
            const dataValueVar = pair[1]
            thisSerializer.writeString(dataKeyVar)
            if (dataValueVar !== undefined && dataValueVar !== null) {
                thisSerializer.writeInt8(RuntimeType.OBJECT)
                const dataValueVarTmpValue  = dataValueVar!
                thisSerializer.holdAndWriteObject(dataValueVarTmpValue)
            } else {
                thisSerializer.writeInt8(RuntimeType.UNDEFINED)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferSizeVar : int32 = retvalDeserializer.readInt32()
        let buffer : Record<string, RecordData> = new Record<string, RecordData>()
        // TODO: TS map resize
        for (let bufferIVar = 0; bufferIVar < bufferSizeVar; bufferIVar++) {
            const bufferKeyVar : string = (retvalDeserializer.readString() as string)
            const bufferValueVarTempBuf_runtimeType  = retvalDeserializer.readInt8()!.toInt()
            let bufferValueVarTempBuf : Object | null | undefined = undefined
            if ((bufferValueVarTempBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
                bufferValueVarTempBuf = (retvalDeserializer.readObject() as object)
            }
            const bufferValueVar : RecordData = bufferValueVarTempBuf
            buffer.set(bufferKeyVar, bufferValueVar)
        }
        const returnResult : Record<string, RecordData> = buffer
        return returnResult
    }
    private onAsyncReceiverRegister_serialize(callback_: ohos_base_Callback<UIExtensionProxy>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSyncReceiverRegister_serialize(callback_: ohos_base_Callback<UIExtensionProxy>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ohos_base_Callback<UIExtensionProxy>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ohos_base_Callback<UIExtensionProxy>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkUIExtensionComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: UIExtensionComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIExtensionComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIExtensionComponent_construct(peerId, flags)
        const _peer  = new ArkUIExtensionComponentPeer(_peerPtr, peerId, 'UIExtensionComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUIExtensionComponentOptionsAttribute(want: Want, options?: UIExtensionOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            UIExtensionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentInterface_setUIExtensionComponentOptions(this.peer.ptr, extractors.toWantPtr(want), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRemoteReadyAttribute(value: ohos_base_Callback<UIExtensionProxy> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReceiveAttribute(value: ReceiveCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ErrorCallback<BusinessError<void>> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTerminatedAttribute(value: ohos_base_Callback<TerminationInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDrawReadyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnDrawReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export enum WindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}
export interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent<undefined>;
    areaChangePlaceholder?: Record<string, ComponentContent<undefined>>;
    dpiFollowStrategy?: DpiFollowStrategy;
    windowModeFollowStrategy?: WindowModeFollowStrategy;
}
export type ReceiveCallback = ohos_base_Callback<Record<string, RecordData>>;
export interface UIExtensionComponentAttribute extends CommonMethod {
    setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        throw new Error('Unimplemented method setUIExtensionComponentOptions')
    }
    onRemoteReady(value: ohos_base_Callback<UIExtensionProxy> | undefined): this {
        throw new Error('Unimplemented method onRemoteReady')
    }
    onReceive(value: ReceiveCallback | undefined): this {
        throw new Error('Unimplemented method onReceive')
    }
    onError(value: ErrorCallback<BusinessError<void>> | undefined): this {
        throw new Error('Unimplemented method onError')
    }
    onTerminated(value: ohos_base_Callback<TerminationInfo> | undefined): this {
        throw new Error('Unimplemented method onTerminated')
    }
    onDrawReady(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onDrawReady')
    }
    attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkUIExtensionComponentComponent extends ArkCommonMethodComponent implements UIExtensionComponentAttribute {
    getPeer(): ArkUIExtensionComponentPeer {
        return (this.peer as ArkUIExtensionComponentPeer)
    }
    public setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        if (this.checkPriority('setUIExtensionComponentOptions')) {
            const want_casted = want as (Want)
            const options_casted = options as (UIExtensionOptions | undefined)
            this.getPeer()?.setUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            this.applyOptionsFinish('UIExtensionComponentAttribute');
            return this
        }
        return this
    }
    public onRemoteReady(value: ohos_base_Callback<UIExtensionProxy> | undefined): this {
        if (this.checkPriority('onRemoteReady')) {
            const value_casted = value as (ohos_base_Callback<UIExtensionProxy> | undefined)
            this.getPeer()?.setOnRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ReceiveCallback | undefined): this {
        if (this.checkPriority('onReceive')) {
            const value_casted = value as (ReceiveCallback | undefined)
            this.getPeer()?.setOnReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback<BusinessError<void>> | undefined): this {
        if (this.checkPriority('onError')) {
            const value_casted = value as (ErrorCallback<BusinessError<void>> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ohos_base_Callback<TerminationInfo> | undefined): this {
        if (this.checkPriority('onTerminated')) {
            const value_casted = value as (ohos_base_Callback<TerminationInfo> | undefined)
            this.getPeer()?.setOnTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onDrawReady(value: VoidCallback | undefined): this {
        if (this.checkPriority('onDrawReady')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnDrawReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookUIExtensionComponentAttributeModifier(this, value);
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
export function UIExtensionComponentImpl(
    @memo @memo_skip
    style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkUIExtensionComponentComponent>((): ArkUIExtensionComponentComponent => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (_: ArkUIExtensionComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class UIExtensionProxy_serializer {
    public static write(buffer: SerializerBase, value: UIExtensionProxy): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): UIExtensionProxy {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return UIExtensionProxyInternal.fromPtr(ptr)
    }
}
export class UIExtensionOptions_serializer {
    public static write(buffer: SerializerBase, value: UIExtensionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIsTransferringCaller  = value.isTransferringCaller
        if (valueHolderForIsTransferringCaller !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsTransferringCallerTmpValue  = valueHolderForIsTransferringCaller!
            valueSerializer.writeBoolean(valueHolderForIsTransferringCallerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPlaceholder  = value.placeholder
        if (valueHolderForPlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlaceholderTmpValue  = valueHolderForPlaceholder!
            ComponentContent_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAreaChangePlaceholder  = value.areaChangePlaceholder
        if (valueHolderForAreaChangePlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAreaChangePlaceholderTmpValue  = valueHolderForAreaChangePlaceholder!
            valueSerializer.writeInt32((valueHolderForAreaChangePlaceholderTmpValue.size).toInt())
            for (const pair of valueHolderForAreaChangePlaceholderTmpValue) {
                const valueHolderForAreaChangePlaceholderTmpValueKeyVar = pair[0]
                const valueHolderForAreaChangePlaceholderTmpValueValueVar = pair[1]
                valueSerializer.writeString(valueHolderForAreaChangePlaceholderTmpValueKeyVar)
                ComponentContent_serializer.write(valueSerializer, valueHolderForAreaChangePlaceholderTmpValueValueVar)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDpiFollowStrategy  = value.dpiFollowStrategy
        if (valueHolderForDpiFollowStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDpiFollowStrategyTmpValue  = (valueHolderForDpiFollowStrategy as DpiFollowStrategy)
            valueSerializer.writeInt32(valueHolderForDpiFollowStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWindowModeFollowStrategy  = value.windowModeFollowStrategy
        if (valueHolderForWindowModeFollowStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWindowModeFollowStrategyTmpValue  = (valueHolderForWindowModeFollowStrategy as WindowModeFollowStrategy)
            valueSerializer.writeInt32(valueHolderForWindowModeFollowStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): UIExtensionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isTransferringCallerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isTransferringCallerTmpBuf : boolean | undefined = undefined
        if ((isTransferringCallerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isTransferringCallerTmpBuf = valueDeserializer.readBoolean()
        }
        const isTransferringCallerTmpResult : boolean | undefined = isTransferringCallerTmpBuf
        const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let placeholderTmpBuf : ComponentContent<undefined> | undefined = undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            placeholderTmpBuf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const placeholderTmpResult : ComponentContent<undefined> | undefined = placeholderTmpBuf
        const areaChangePlaceholderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let areaChangePlaceholderTmpBuf : Record<string, ComponentContent<undefined>> | undefined = undefined
        if ((areaChangePlaceholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const areaChangePlaceholderTmpBufOptSizeVar : int32 = valueDeserializer.readInt32()
            let areaChangePlaceholderTmpBufOpt : Record<string, ComponentContent<undefined>> = new Record<string, ComponentContent<undefined>>()
            // TODO: TS map resize
            for (let areaChangePlaceholderTmpBufOptIVar = 0; areaChangePlaceholderTmpBufOptIVar < areaChangePlaceholderTmpBufOptSizeVar; areaChangePlaceholderTmpBufOptIVar++) {
                const areaChangePlaceholderTmpBufOptKeyVar : string = (valueDeserializer.readString() as string)
                const areaChangePlaceholderTmpBufOptValueVar : ComponentContent<undefined> = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
                areaChangePlaceholderTmpBufOpt.set(areaChangePlaceholderTmpBufOptKeyVar, areaChangePlaceholderTmpBufOptValueVar)
            }
            areaChangePlaceholderTmpBuf = areaChangePlaceholderTmpBufOpt
        }
        const areaChangePlaceholderTmpResult : Record<string, ComponentContent<undefined>> | undefined = areaChangePlaceholderTmpBuf
        const dpiFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dpiFollowStrategyTmpBuf : DpiFollowStrategy | undefined = undefined
        if ((dpiFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dpiFollowStrategyTmpBuf = DpiFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const dpiFollowStrategyTmpResult : DpiFollowStrategy | undefined = dpiFollowStrategyTmpBuf
        const windowModeFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let windowModeFollowStrategyTmpBuf : WindowModeFollowStrategy | undefined = undefined
        if ((windowModeFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            windowModeFollowStrategyTmpBuf = WindowModeFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const windowModeFollowStrategyTmpResult : WindowModeFollowStrategy | undefined = windowModeFollowStrategyTmpBuf
        let value : UIExtensionOptions = ({isTransferringCaller: isTransferringCallerTmpResult, placeholder: placeholderTmpResult, areaChangePlaceholder: areaChangePlaceholderTmpResult, dpiFollowStrategy: dpiFollowStrategyTmpResult, windowModeFollowStrategy: windowModeFollowStrategyTmpResult} as UIExtensionOptions)
        return value
    }
}
