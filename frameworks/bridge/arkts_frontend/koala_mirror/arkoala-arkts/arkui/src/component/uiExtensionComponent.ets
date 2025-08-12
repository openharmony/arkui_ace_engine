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
import { Want_serializer, Want } from "./../generated/ohos.app.ability.Want"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ErrorCallback, BusinessError } from "./../generated/ohos.base"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
            const dataKeyVar = pair[0]
            const dataValueVar = pair[1]
            thisSerializer.writeString(dataKeyVar)
            thisSerializer.holdAndWriteObject(dataValueVar)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Map<string, Object>): Map<string, Object> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((data.size).toInt())
        for (const pair of data) {
            const dataKeyVar = pair[0]
            const dataValueVar = pair[1]
            thisSerializer.writeString(dataKeyVar)
            thisSerializer.holdAndWriteObject(dataValueVar)
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferSizeVar : int32 = retvalDeserializer.readInt32()
        let buffer : Map<string, Object> = new Map<string, Object>()
        // TODO: TS map resize
        for (let bufferIVar = 0; bufferIVar < bufferSizeVar; bufferIVar++) {
            const bufferKeyVar : string = (retvalDeserializer.readString() as string)
            const bufferValueVar : Object = (retvalDeserializer.readObject() as object)
            buffer.set(bufferKeyVar, bufferValueVar)
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
    private offSyncReceiverRegister_serialize(callback_?: ((value0: UIExtensionProxy) => void)): void {
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
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Want_serializer.write(thisSerializer, want)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            UIExtensionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentInterface_setUIExtensionComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    setOnReceiveAttribute(value: ((value0: Map<string, Object>) => void) | undefined): void {
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
    setOnErrorAttribute(value: ErrorCallback | undefined): void {
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
    setOnTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
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
    setOnDrawReadyAttribute(value: (() => void) | undefined): void {
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class UIExtensionComponentModifier extends CommonMethodModifier implements UIExtensionComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onRemoteReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRemoteReady_0_0value?: ((value0: UIExtensionProxy) => void) | undefined
    _onReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReceive_0_0value?: ((value0: Map<string, Object>) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ErrorCallback | undefined
    _onTerminated_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTerminated_0_0value?: ((value0: TerminationInfo) => void) | undefined
    _onDrawReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDrawReady_0_0value?: (() => void) | undefined
    applyModifierPatch(peer: ArkUIExtensionComponentPeer): void {
        super.applyModifierPatch(peer)
        if (this._onRemoteReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRemoteReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRemoteReadyAttribute((this._onRemoteReady_0_0value as ((value0: UIExtensionProxy) => void) | undefined));
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRemoteReadyAttribute((undefined as ((value0: UIExtensionProxy) => void) | undefined));
                }
            }
        }
        if (this._onReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReceiveAttribute((this._onReceive_0_0value as ((value0: Map<string, Object>) => void) | undefined));
                    this._onReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReceiveAttribute((undefined as ((value0: Map<string, Object>) => void) | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ErrorCallback | undefined));
                }
            }
        }
        if (this._onTerminated_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTerminated_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTerminatedAttribute((this._onTerminated_0_0value as ((value0: TerminationInfo) => void) | undefined));
                    this._onTerminated_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTerminated_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTerminated_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTerminatedAttribute((undefined as ((value0: TerminationInfo) => void) | undefined));
                }
            }
        }
        if (this._onDrawReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDrawReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDrawReadyAttribute((this._onDrawReady_0_0value as (() => void) | undefined));
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDrawReadyAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: UIExtensionComponentModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onRemoteReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRemoteReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRemoteReady(modifier._onRemoteReady_0_0value);
                    break;
                }
                default: {
                    this.onRemoteReady((undefined as ((value0: UIExtensionProxy) => void) | undefined));
                }
            }
        }
        if (modifier._onReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReceive(modifier._onReceive_0_0value);
                    break;
                }
                default: {
                    this.onReceive((undefined as ((value0: Map<string, Object>) => void) | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ErrorCallback | undefined));
                }
            }
        }
        if (modifier._onTerminated_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTerminated_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTerminated(modifier._onTerminated_0_0value);
                    break;
                }
                default: {
                    this.onTerminated((undefined as ((value0: TerminationInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onDrawReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDrawReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDrawReady(modifier._onDrawReady_0_0value);
                    break;
                }
                default: {
                    this.onDrawReady((undefined as (() => void) | undefined));
                }
            }
        }
    }
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        if (((this._onRemoteReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRemoteReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRemoteReady_0_0value = value
        } else
        {
            this._onRemoteReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReceive(value: ((value0: Map<string, Object>) => void) | undefined): this {
        if (((this._onReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReceive_0_0value = value
        } else
        {
            this._onReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (((this._onTerminated_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTerminated_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTerminated_0_0value = value
        } else
        {
            this._onTerminated_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDrawReady(value: (() => void) | undefined): this {
        if (((this._onDrawReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDrawReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDrawReady_0_0value = value
        } else
        {
            this._onDrawReady_0_flag = AttributeUpdaterFlag.SKIP
        }
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
            valueSerializer.writeInt32(TypeChecker.DpiFollowStrategy_ToNumeric(valueHolderForDpiFollowStrategyTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWindowModeFollowStrategy  = value.windowModeFollowStrategy
        if (valueHolderForWindowModeFollowStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWindowModeFollowStrategyTmpValue  = (valueHolderForWindowModeFollowStrategy as WindowModeFollowStrategy)
            valueSerializer.writeInt32(TypeChecker.WindowModeFollowStrategy_ToNumeric(valueHolderForWindowModeFollowStrategyTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): UIExtensionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isTransferringCallerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isTransferringCallerTmpBuf : boolean | undefined
        if ((isTransferringCallerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isTransferringCallerTmpBuf = valueDeserializer.readBoolean()
        }
        const isTransferringCallerTmpResult : boolean | undefined = isTransferringCallerTmpBuf
        const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholderTmpBuf : ComponentContent | undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            placeholderTmpBuf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const placeholderTmpResult : ComponentContent | undefined = placeholderTmpBuf
        const areaChangePlaceholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let areaChangePlaceholderTmpBuf : Map<string, ComponentContent> | undefined
        if ((areaChangePlaceholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const areaChangePlaceholderTmpBuf_SizeVar : int32 = valueDeserializer.readInt32()
            let areaChangePlaceholderTmpBuf_ : Map<string, ComponentContent> = new Map<string, ComponentContent>()
            // TODO: TS map resize
            for (let areaChangePlaceholderTmpBuf_IVar = 0; areaChangePlaceholderTmpBuf_IVar < areaChangePlaceholderTmpBuf_SizeVar; areaChangePlaceholderTmpBuf_IVar++) {
                const areaChangePlaceholderTmpBuf_KeyVar : string = (valueDeserializer.readString() as string)
                const areaChangePlaceholderTmpBuf_ValueVar : ComponentContent = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
                areaChangePlaceholderTmpBuf_.set(areaChangePlaceholderTmpBuf_KeyVar, areaChangePlaceholderTmpBuf_ValueVar)
            }
            areaChangePlaceholderTmpBuf = areaChangePlaceholderTmpBuf_
        }
        const areaChangePlaceholderTmpResult : Map<string, ComponentContent> | undefined = areaChangePlaceholderTmpBuf
        const dpiFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dpiFollowStrategyTmpBuf : DpiFollowStrategy | undefined
        if ((dpiFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dpiFollowStrategyTmpBuf = TypeChecker.DpiFollowStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const dpiFollowStrategyTmpResult : DpiFollowStrategy | undefined = dpiFollowStrategyTmpBuf
        const windowModeFollowStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let windowModeFollowStrategyTmpBuf : WindowModeFollowStrategy | undefined
        if ((windowModeFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            windowModeFollowStrategyTmpBuf = TypeChecker.WindowModeFollowStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const windowModeFollowStrategyTmpResult : WindowModeFollowStrategy | undefined = windowModeFollowStrategyTmpBuf
        let value : UIExtensionOptions = ({isTransferringCaller: isTransferringCallerTmpResult, placeholder: placeholderTmpResult, areaChangePlaceholder: areaChangePlaceholderTmpResult, dpiFollowStrategy: dpiFollowStrategyTmpResult, windowModeFollowStrategy: windowModeFollowStrategyTmpResult} as UIExtensionOptions)
        return value
    }
}
