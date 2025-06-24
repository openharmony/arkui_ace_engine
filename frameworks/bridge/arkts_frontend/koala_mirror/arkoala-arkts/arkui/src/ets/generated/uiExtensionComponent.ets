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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Want_serializer, Want } from "./ohos.app.ability.Want"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ErrorCallback, BusinessError } from "./ohos.base"
import { TerminationInfo } from "./embeddedComponent"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { ComponentContent, ComponentContent_serializer } from "./arkui.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface UIExtensionProxy {
    send(data: Map<string, Object>): void
    sendSync(data: Map<string, Object>): Map<string, Object>
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_ctor()
        return retval
    }
    constructor() {
        this(UIExtensionProxyInternal.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public send(data: Map<string, Object>): void {
        const data_casted = data as (Map<string, Object>)
        this.send_serialize(data_casted)
        return
    }
    public sendSync(data: Map<string, Object>): Map<string, Object> {
        const data_casted = data as (Map<string, Object>)
        return this.sendSync_serialize(data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void))
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void))
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((value0: UIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    on(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    private send_serialize(data: Map<string, Object>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.holdAndWriteObject(data_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Map<string, Object>): Map<string, Object> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.holdAndWriteObject(data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_size : int32 = retvalDeserializer.readInt32()
        let buffer : Map<string, Object> = new Map<string, Object>()
        // TODO: TS map resize
        for (let buffer_i = 0; buffer_i < buffer_size; buffer_i++) {
            const buffer_key : string = (retvalDeserializer.readString() as string)
            const buffer_value : Object = (retvalDeserializer.readObject() as object)
            buffer.set(buffer_key, buffer_value)
        }
        const returnResult : Map<string, Object> = buffer
        return returnResult
    }
    private onAsyncReceiverRegister_serialize(callback_: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSyncReceiverRegister_serialize(callback_: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ((value0: UIExtensionProxy) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        return new UIExtensionProxyInternal(ptr)
    }
}
export class ArkUIExtensionComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIExtensionComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIExtensionComponent_construct(peerId, flags)
        const _peer  = new ArkUIExtensionComponentPeer(_peerPtr, peerId, "UIExtensionComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUIExtensionComponentOptionsAttribute(want: Want, options?: UIExtensionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Want_serializer.write(thisSerializer, want)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            UIExtensionOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentInterface_setUIExtensionComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRemoteReadyAttribute(value: ((value0: UIExtensionProxy) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReceiveAttribute(value: ((value0: Map<string, Object>) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string, ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
}
export type ReceiveCallback = ((value0: Map<string, Object>) => void);
export interface UIExtensionComponentAttribute extends CommonMethod {
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this
    onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this
    onError(value: ErrorCallback | undefined): this
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this
    attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkUIExtensionComponentStyle extends ArkCommonMethodStyle implements UIExtensionComponentAttribute {
    onRemoteReady_value?: ((value0: UIExtensionProxy) => void) | undefined
    onReceive_value?: ((value0: Map<string, Object>) => void) | undefined
    onError_value?: ErrorCallback | undefined
    onTerminated_value?: ((value0: TerminationInfo) => void) | undefined
    attributeModifier_value?: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        return this
    }
    public onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: UIExtensionComponentAttribute): void {
        super.apply(target)
        if (this.onRemoteReady_value !== undefined)
            target.onRemoteReady(this.onRemoteReady_value!)
        if (this.onReceive_value !== undefined)
            target.onReceive(this.onReceive_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
        if (this.onTerminated_value !== undefined)
            target.onTerminated(this.onTerminated_value!)
    }
}

export class ArkUIExtensionComponentComponent extends ArkCommonMethodComponent implements UIExtensionComponentAttribute {
    getPeer(): ArkUIExtensionComponentPeer {
        return (this.peer as ArkUIExtensionComponentPeer)
    }
    public setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        if (this.checkPriority("setUIExtensionComponentOptions")) {
            const want_casted = want as (Want)
            const options_casted = options as (UIExtensionOptions | undefined)
            this.getPeer()?.setUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            return this
        }
        return this
    }
    public onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((value0: UIExtensionProxy) => void) | undefined)
            this.getPeer()?.onRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((value0: Map<string, Object>) => void) | undefined)
            this.getPeer()?.onReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((value0: TerminationInfo) => void) | undefined)
            this.getPeer()?.onTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withUIExtensionComponentStyle(receiver: UIExtensionComponentAttribute, modifier: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkUIExtensionComponentStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("UIExtensionComponentImpl")
export function UIExtensionComponent(
    want: Want, options?: UIExtensionOptions | undefined,
    @memo
    content_?: () => void,
): UIExtensionComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function UIExtensionComponentImpl(
    @memo
    style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
    want: Want, options?: UIExtensionOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkUIExtensionComponentComponent>((): ArkUIExtensionComponentComponent => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (_: ArkUIExtensionComponentPeer): void => {
        receiver.setUIExtensionComponentOptions(want,options)
        style?.(receiver)
        withUIExtensionComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
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
        const value_isTransferringCaller  = value.isTransferringCaller
        let value_isTransferringCaller_type : int32 = RuntimeType.UNDEFINED
        value_isTransferringCaller_type = runtimeType(value_isTransferringCaller)
        valueSerializer.writeInt8(value_isTransferringCaller_type)
        if ((RuntimeType.UNDEFINED) != (value_isTransferringCaller_type)) {
            const value_isTransferringCaller_value  = value_isTransferringCaller!
            valueSerializer.writeBoolean(value_isTransferringCaller_value)
        }
        const value_placeholder  = value.placeholder
        let value_placeholder_type : int32 = RuntimeType.UNDEFINED
        value_placeholder_type = runtimeType(value_placeholder)
        valueSerializer.writeInt8(value_placeholder_type)
        if ((RuntimeType.UNDEFINED) != (value_placeholder_type)) {
            const value_placeholder_value  = value_placeholder!
            ComponentContent_serializer.write(valueSerializer, value_placeholder_value)
        }
        const value_areaChangePlaceholder  = value.areaChangePlaceholder
        let value_areaChangePlaceholder_type : int32 = RuntimeType.UNDEFINED
        value_areaChangePlaceholder_type = runtimeType(value_areaChangePlaceholder)
        valueSerializer.writeInt8(value_areaChangePlaceholder_type)
        if ((RuntimeType.UNDEFINED) != (value_areaChangePlaceholder_type)) {
            const value_areaChangePlaceholder_value  = value_areaChangePlaceholder!
            valueSerializer.writeInt32(value_areaChangePlaceholder_value.size as int32 as int32)
            for (const pair of value_areaChangePlaceholder_value) {
                const value_areaChangePlaceholder_value_key = pair[0]
                const value_areaChangePlaceholder_value_value = pair[1]
                valueSerializer.writeString(value_areaChangePlaceholder_value_key)
                ComponentContent_serializer.write(valueSerializer, value_areaChangePlaceholder_value_value)
            }
        }
        const value_dpiFollowStrategy  = value.dpiFollowStrategy
        let value_dpiFollowStrategy_type : int32 = RuntimeType.UNDEFINED
        value_dpiFollowStrategy_type = runtimeType(value_dpiFollowStrategy)
        valueSerializer.writeInt8(value_dpiFollowStrategy_type)
        if ((RuntimeType.UNDEFINED) != (value_dpiFollowStrategy_type)) {
            const value_dpiFollowStrategy_value  = (value_dpiFollowStrategy as DpiFollowStrategy)
            valueSerializer.writeInt32(TypeChecker.DpiFollowStrategy_ToNumeric(value_dpiFollowStrategy_value))
        }
    }
    public static read(buffer: DeserializerBase): UIExtensionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isTransferringCaller_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let isTransferringCaller_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (isTransferringCaller_buf_runtimeType))
        {
            isTransferringCaller_buf = valueDeserializer.readBoolean()
        }
        const isTransferringCaller_result : boolean | undefined = isTransferringCaller_buf
        const placeholder_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let placeholder_buf : ComponentContent | undefined
        if ((RuntimeType.UNDEFINED) != (placeholder_buf_runtimeType))
        {
            placeholder_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const placeholder_result : ComponentContent | undefined = placeholder_buf
        const areaChangePlaceholder_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let areaChangePlaceholder_buf : Map<string, ComponentContent> | undefined
        if ((RuntimeType.UNDEFINED) != (areaChangePlaceholder_buf_runtimeType))
        {
            const areaChangePlaceholder_buf__size : int32 = valueDeserializer.readInt32()
            let areaChangePlaceholder_buf_ : Map<string, ComponentContent> = new Map<string, ComponentContent>()
            // TODO: TS map resize
            for (let areaChangePlaceholder_buf__i = 0; areaChangePlaceholder_buf__i < areaChangePlaceholder_buf__size; areaChangePlaceholder_buf__i++) {
                const areaChangePlaceholder_buf__key : string = (valueDeserializer.readString() as string)
                const areaChangePlaceholder_buf__value : ComponentContent = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
                areaChangePlaceholder_buf_.set(areaChangePlaceholder_buf__key, areaChangePlaceholder_buf__value)
            }
            areaChangePlaceholder_buf = areaChangePlaceholder_buf_
        }
        const areaChangePlaceholder_result : Map<string, ComponentContent> | undefined = areaChangePlaceholder_buf
        const dpiFollowStrategy_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dpiFollowStrategy_buf : DpiFollowStrategy | undefined
        if ((RuntimeType.UNDEFINED) != (dpiFollowStrategy_buf_runtimeType))
        {
            dpiFollowStrategy_buf = TypeChecker.DpiFollowStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const dpiFollowStrategy_result : DpiFollowStrategy | undefined = dpiFollowStrategy_buf
        let value : UIExtensionOptions = ({isTransferringCaller: isTransferringCaller_result, placeholder: placeholder_result, areaChangePlaceholder: areaChangePlaceholder_result, dpiFollowStrategy: dpiFollowStrategy_result} as UIExtensionOptions)
        return value
    }
}
