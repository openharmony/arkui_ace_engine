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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ErrorCallback, BusinessError, RecordData } from "@ohos.base"
import { extractors, AttributeModifier, hookUIExtensionComponentAttributeModifier, AttributeUpdater } from "#handwritten"
import { default as Want } from "@ohos.app.ability.Want"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ComponentContent } from "arkui.ComponentContent"
import { UIExtensionComponentModifier } from "./../UIExtensionComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface UIExtensionProxy {
    send(data: Record<string, RecordData>): void
    sendSync(data: Record<string, RecordData>): Record<string, RecordData>
    onAsyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void) | undefined): void
    offSyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void) | undefined): void
}
export class UIExtensionProxyInternal implements MaterializedBase,UIExtensionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UIExtensionProxyInternal.getFinalizer())
    }
    constructor() {
        this(UIExtensionProxyInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        return new UIExtensionProxyInternal(ptr)
    }
    public send(data: Record<string, RecordData>): void {
        const data_casted = data as (Record<string, RecordData>)
        ArkUIAniUiextensionProxyModal._Send_Data(this.peer!.ptr, data_casted)
        return
    }
    public sendSync(data: Record<string, RecordData>): Record<string, RecordData> {
        const data_casted = data as (Record<string, RecordData>)
        return ArkUIAniUiextensionProxyModal._Send_Data_Sync(this.peer!.ptr, data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void))
        this.onAsyncReceiverRegisterAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void))
        this.onSyncReceiverRegisterSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegisterAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegisterSyncReceiverRegister_serialize(callback__casted)
        return
    }
    onAsyncReceiverRegister(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("Improve")
    }
    onSyncReceiverRegister(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("Improve")
    }
    offAsyncReceiverRegister(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("Improve")
    }
    offSyncReceiverRegister(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("Improve")
    }
    send_serialize(data: Map<string, RecordData>): void {
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
    sendSync_serialize(data: Map<string, RecordData>): Map<string, RecordData> {
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
        let buffer : Map<string, RecordData> = new Map<string, RecordData>()
        // TODO: TS map resize
        for (let bufferIVar = 0; bufferIVar < bufferSizeVar; bufferIVar++) {
            const bufferKeyVar : string = (retvalDeserializer.readString() as string)
            const bufferValueVarTempBuf_runtimeType  = retvalDeserializer.readInt8().toInt()
            let bufferValueVarTempBuf : Object | null | undefined = undefined
            if ((bufferValueVarTempBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
                bufferValueVarTempBuf = (retvalDeserializer.readObject() as object)
            }
            const bufferValueVar : RecordData = bufferValueVarTempBuf
            buffer.set(bufferKeyVar, bufferValueVar)
        }
        const returnResult : Map<string, RecordData> = buffer
        return returnResult
    }
    onAsyncReceiverRegisterAsyncReceiverRegister_serialize(callback_: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegisterAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSyncReceiverRegisterSyncReceiverRegister_serialize(callback_: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegisterSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offAsyncReceiverRegisterAsyncReceiverRegister_serialize(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegisterAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offSyncReceiverRegisterSyncReceiverRegister_serialize(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegisterSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkUIExtensionComponentPeer extends ArkUIExtensionComponentPeerBase {
    attributeSet?: UIExtensionComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIExtensionComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIExtensionComponent_construct(peerId, flags)
        const _peer  = new ArkUIExtensionComponentPeer(_peerPtr, peerId, 'UIExtensionComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setOnRemoteReadyAttribute(value: ((value0: UIExtensionProxy) => void) | undefined): void {
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
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Record<string, ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
    windowModeFollowStrategy?: WindowModeFollowStrategy;
}
export type ReceiveCallback = ((value0: Record<string, RecordData>) => void);
export interface UIExtensionComponentAttribute extends CommonMethod {
    setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        throw new Error("Unimplemented method setUIExtensionComponentOptions")
    }
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        throw new Error("Unimplemented method onRemoteReady")
    }
    onReceive(value: ((value0: Record<string, RecordData>) => void) | undefined): this {
        throw new Error("Unimplemented method onReceive")
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onTerminated")
    }
    onDrawReady(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onDrawReady")
    }
    attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkUIExtensionComponentStyle extends ArkCommonMethodStyle implements UIExtensionComponentAttribute {
    onRemoteReady_value?: ((value0: UIExtensionProxy) => void) | undefined
    onReceive_value?: ((value0: Record<string, RecordData>) => void) | undefined
    onError_value?: ErrorCallback<BusinessError> | undefined
    onTerminated_value?: ((value0: TerminationInfo) => void) | undefined
    onDrawReady_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        return this
    }
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        return this
    }
    onReceive(value: ((value0: Record<string, RecordData>) => void) | undefined): this {
        return this
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        return this
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        return this
    }
    onDrawReady(value: (() => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkUIExtensionComponentComponent extends ArkCommonMethodComponent implements UIExtensionComponentAttribute {
    getPeer(): ArkUIExtensionComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkUIExtensionComponentPeer)
    }
    public setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        if (this.checkPriority("setUIExtensionComponentOptions")) {
            const want_casted = want as (Want)
            const options_casted = options as (UIExtensionOptions | undefined)
            this.getPeer()?.setUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            this.applyOptionsFinish('UIExtensionComponentAttribute');
            return this
        }
        return this
    }
    public onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((value0: UIExtensionProxy) => void) | undefined)
            this.getPeer()?.setOnRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((value0: Record<string, RecordData>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((value0: Record<string, RecordData>) => void) | undefined)
            this.getPeer()?.setOnReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback<BusinessError> | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback<BusinessError> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((value0: TerminationInfo) => void) | undefined)
            this.getPeer()?.setOnTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onDrawReady(value: (() => void) | undefined): this {
        if (this.checkPriority("onDrawReady")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnDrawReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookUIExtensionComponentAttributeModifier(this, value);
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
    @memo
    style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkUIExtensionComponentComponent>((): ArkUIExtensionComponentComponent => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (peer: ArkUIExtensionComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
            valueSerializer.holdAndWriteObject(valueHolderForPlaceholderTmpValue)
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
                valueSerializer.holdAndWriteObject(valueHolderForAreaChangePlaceholderTmpValueValueVar)
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
        const isTransferringCallerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isTransferringCallerTmpBuf : boolean | undefined = undefined
        if ((isTransferringCallerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isTransferringCallerTmpBuf = valueDeserializer.readBoolean()
        }
        const isTransferringCallerTmpResult : boolean | undefined = isTransferringCallerTmpBuf
        // const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholderTmpBuf : ComponentContent | undefined = undefined
        // if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        //     placeholderTmpBuf = (valueDeserializer.readObject() as ComponentContent)
        // }
        const placeholderTmpResult : ComponentContent | undefined = undefined
        // const areaChangePlaceholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        // let areaChangePlaceholderTmpBuf : Map<string, ComponentContent> | undefined = undefined
        // if ((areaChangePlaceholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        //     const areaChangePlaceholderTmpBuf_SizeVar : int32 = valueDeserializer.readInt32()
        //     let areaChangePlaceholderTmpBuf_ : Map<string, ComponentContent> = new Map<string, ComponentContent>()
        //     // TODO: TS map resize
        //     for (let areaChangePlaceholderTmpBuf_IVar = 0; areaChangePlaceholderTmpBuf_IVar < areaChangePlaceholderTmpBuf_SizeVar; areaChangePlaceholderTmpBuf_IVar++) {
        //         const areaChangePlaceholderTmpBuf_KeyVar : string = (valueDeserializer.readString() as string)
        //         const areaChangePlaceholderTmpBuf_ValueVar : ComponentContent = (valueDeserializer.readObject() as ComponentContent)
        //         areaChangePlaceholderTmpBuf_.set(areaChangePlaceholderTmpBuf_KeyVar, areaChangePlaceholderTmpBuf_ValueVar)
        //     }
        //     areaChangePlaceholderTmpBuf = areaChangePlaceholderTmpBuf_
        // }
        const areaChangePlaceholderTmpResult : Map<string, ComponentContent> | undefined = undefined
        const dpiFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dpiFollowStrategyTmpBuf : DpiFollowStrategy | undefined = undefined
        if ((dpiFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dpiFollowStrategyTmpBuf = DpiFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const dpiFollowStrategyTmpResult : DpiFollowStrategy | undefined = dpiFollowStrategyTmpBuf
        const windowModeFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let windowModeFollowStrategyTmpBuf : WindowModeFollowStrategy | undefined = undefined
        if ((windowModeFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            windowModeFollowStrategyTmpBuf = WindowModeFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const windowModeFollowStrategyTmpResult : WindowModeFollowStrategy | undefined = windowModeFollowStrategyTmpBuf
        let value : UIExtensionOptions = ({isTransferringCaller: isTransferringCallerTmpResult, placeholder: placeholderTmpResult, areaChangePlaceholder: areaChangePlaceholderTmpResult, dpiFollowStrategy: dpiFollowStrategyTmpResult, windowModeFollowStrategy: windowModeFollowStrategyTmpResult} as UIExtensionOptions)
        return value
    }
}
