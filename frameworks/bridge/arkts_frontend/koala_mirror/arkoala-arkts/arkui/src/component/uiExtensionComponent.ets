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
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Want_serializer, Want } from "./../generated/ohos.app.ability.Want"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ErrorCallback, BusinessError } from "./../generated/ohos.base"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
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
        throw new Error("Improve")
    }
    off(type: string, callback_: ((value0: UIExtensionProxy) => void)): void {
        throw new Error("Improve")
    }
    private send_serialize(data: Map<string, Object>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((data.size).toInt())
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
        thisSerializer.writeInt32((data.size).toInt())
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
        thisSerializer.writeInt8((callback__type).toChar())
        if ((callback__type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((callback__type).toChar())
        if ((callback__type) != (RuntimeType.UNDEFINED)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            UIExtensionOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentInterface_setUIExtensionComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRemoteReadyAttribute(value: ((value0: UIExtensionProxy) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReceiveAttribute(value: ((value0: Map<string, Object>) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_setOnTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDrawReadyAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
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
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string, ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
    windowModeFollowStrategy?: WindowModeFollowStrategy;
}
export type ReceiveCallback = ((value0: Map<string, Object>) => void);
export interface UIExtensionComponentAttribute extends CommonMethod {
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        throw new Error("Unimplemented method onRemoteReady")
    }
    onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        throw new Error("Unimplemented method onReceive")
    }
    onError(value: ErrorCallback | undefined): this {
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
    onReceive_value?: ((value0: Map<string, Object>) => void) | undefined
    onError_value?: ErrorCallback | undefined
    onTerminated_value?: ((value0: TerminationInfo) => void) | undefined
    onDrawReady_value?: (() => void) | undefined
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
    public onDrawReady(value: (() => void) | undefined): this {
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
        if (this.onDrawReady_value !== undefined)
            target.onDrawReady(this.onDrawReady_value!)
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
            this.getPeer()?.setOnRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((value0: Map<string, Object>) => void) | undefined)
            this.getPeer()?.setOnReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("UIExtensionComponent")
// export function UIExtensionComponent(
//     want: Want, options?: UIExtensionOptions,
//     @memo
//     content_?: () => void,
// ): UIExtensionComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function UIExtensionComponent(
    @memo
    style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
    want: Want, options?: UIExtensionOptions,
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

export class ArkUIExtensionComponentSet extends ArkCommonMethodSet implements UIExtensionComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onRemoteReady_flag?: boolean
    _onRemoteReady0_value?: ((value0: UIExtensionProxy) => void) | undefined
    _onReceive_flag?: boolean
    _onReceive0_value?: ((value0: Map<string, Object>) => void) | undefined
    _onError_flag?: boolean
    _onError0_value?: ErrorCallback | undefined
    _onTerminated_flag?: boolean
    _onTerminated0_value?: ((value0: TerminationInfo) => void) | undefined
    _onDrawReady_flag?: boolean
    _onDrawReady0_value?: (() => void) | undefined
    applyModifierPatch(component: UIExtensionComponentAttribute): void {
        if (this._onRemoteReady_flag)
            component.onRemoteReady((this._onRemoteReady0_value as ((value0: UIExtensionProxy) => void) | undefined))
        if (this._onReceive_flag)
            component.onReceive((this._onReceive0_value as ((value0: Map<string, Object>) => void) | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as ErrorCallback | undefined))
        if (this._onTerminated_flag)
            component.onTerminated((this._onTerminated0_value as ((value0: TerminationInfo) => void) | undefined))
        if (this._onDrawReady_flag)
            component.onDrawReady((this._onDrawReady0_value as (() => void) | undefined))
    }
    public onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        this._onRemoteReady_flag = true
        this._onRemoteReady0_value = value
        return this
    }
    public onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        this._onReceive_flag = true
        this._onReceive0_value = value
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        this._onTerminated_flag = true
        this._onTerminated0_value = value
        return this
    }
    public onDrawReady(value: (() => void) | undefined): this {
        this._onDrawReady_flag = true
        this._onDrawReady0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt8((value_isTransferringCaller_type).toChar())
        if ((value_isTransferringCaller_type) != (RuntimeType.UNDEFINED)) {
            const value_isTransferringCaller_value  = value_isTransferringCaller!
            valueSerializer.writeBoolean(value_isTransferringCaller_value)
        }
        const value_placeholder  = value.placeholder
        let value_placeholder_type : int32 = RuntimeType.UNDEFINED
        value_placeholder_type = runtimeType(value_placeholder)
        valueSerializer.writeInt8((value_placeholder_type).toChar())
        if ((value_placeholder_type) != (RuntimeType.UNDEFINED)) {
            const value_placeholder_value  = value_placeholder!
            ComponentContent_serializer.write(valueSerializer, value_placeholder_value)
        }
        const value_areaChangePlaceholder  = value.areaChangePlaceholder
        let value_areaChangePlaceholder_type : int32 = RuntimeType.UNDEFINED
        value_areaChangePlaceholder_type = runtimeType(value_areaChangePlaceholder)
        valueSerializer.writeInt8((value_areaChangePlaceholder_type).toChar())
        if ((value_areaChangePlaceholder_type) != (RuntimeType.UNDEFINED)) {
            const value_areaChangePlaceholder_value  = value_areaChangePlaceholder!
            valueSerializer.writeInt32((value_areaChangePlaceholder_value.size).toInt())
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
        valueSerializer.writeInt8((value_dpiFollowStrategy_type).toChar())
        if ((value_dpiFollowStrategy_type) != (RuntimeType.UNDEFINED)) {
            const value_dpiFollowStrategy_value  = (value_dpiFollowStrategy as DpiFollowStrategy)
            valueSerializer.writeInt32(TypeChecker.DpiFollowStrategy_ToNumeric(value_dpiFollowStrategy_value))
        }
        const value_windowModeFollowStrategy  = value.windowModeFollowStrategy
        let value_windowModeFollowStrategy_type : int32 = RuntimeType.UNDEFINED
        value_windowModeFollowStrategy_type = runtimeType(value_windowModeFollowStrategy)
        valueSerializer.writeInt8((value_windowModeFollowStrategy_type).toChar())
        if ((value_windowModeFollowStrategy_type) != (RuntimeType.UNDEFINED)) {
            const value_windowModeFollowStrategy_value  = (value_windowModeFollowStrategy as WindowModeFollowStrategy)
            valueSerializer.writeInt32(TypeChecker.WindowModeFollowStrategy_ToNumeric(value_windowModeFollowStrategy_value))
        }
    }
    public static read(buffer: DeserializerBase): UIExtensionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isTransferringCaller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isTransferringCaller_buf : boolean | undefined
        if ((isTransferringCaller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isTransferringCaller_buf = valueDeserializer.readBoolean()
        }
        const isTransferringCaller_result : boolean | undefined = isTransferringCaller_buf
        const placeholder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholder_buf : ComponentContent | undefined
        if ((placeholder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            placeholder_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const placeholder_result : ComponentContent | undefined = placeholder_buf
        const areaChangePlaceholder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let areaChangePlaceholder_buf : Map<string, ComponentContent> | undefined
        if ((areaChangePlaceholder_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const dpiFollowStrategy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dpiFollowStrategy_buf : DpiFollowStrategy | undefined
        if ((dpiFollowStrategy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dpiFollowStrategy_buf = TypeChecker.DpiFollowStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const dpiFollowStrategy_result : DpiFollowStrategy | undefined = dpiFollowStrategy_buf
        const windowModeFollowStrategy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let windowModeFollowStrategy_buf : WindowModeFollowStrategy | undefined
        if ((windowModeFollowStrategy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            windowModeFollowStrategy_buf = TypeChecker.WindowModeFollowStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const windowModeFollowStrategy_result : WindowModeFollowStrategy | undefined = windowModeFollowStrategy_buf
        let value : UIExtensionOptions = ({isTransferringCaller: isTransferringCaller_result, placeholder: placeholder_result, areaChangePlaceholder: areaChangePlaceholder_result, dpiFollowStrategy: dpiFollowStrategy_result, windowModeFollowStrategy: windowModeFollowStrategy_result} as UIExtensionOptions)
        return value
    }
}
