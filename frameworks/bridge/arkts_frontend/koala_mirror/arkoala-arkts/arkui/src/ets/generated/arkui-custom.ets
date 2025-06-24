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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { ResourceStr, ResourceColor } from "./units"
import { Frame_serializer, Frame } from "./arkui.Graphics"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Color } from "./enums"
export class FocusController {
    public static requestFocus(key: string): void {
        const key_casted = key as (string)
        FocusController.requestFocus_serialize(key_casted)
        return
    }
    private static requestFocus_serialize(key: string): void {
        ArkUIGeneratedNativeModule._FocusController_requestFocus(key)
    }
}
export class LazyForEachOps {
    public static Sync(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const node_casted = node as (KPointer)
        const totalCount_casted = totalCount as (int32)
        const creator_casted = creator as (Callback_CreateItem)
        const updater_casted = updater as (Callback_RangeUpdate)
        LazyForEachOps.Sync_serialize(node_casted, totalCount_casted, creator_casted, updater_casted)
        return
    }
    private static Sync_serialize(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(creator)
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_Sync(node, totalCount, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class RestrictedWorkerInternal {
    public static fromPtr(ptr: KPointer): RestrictedWorker {
        return new RestrictedWorker(ptr)
    }
}
export class RestrictedWorker implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onexit(): RestrictedWorker_onexit_Callback | undefined {
        return this.getOnexit()
    }
    set onexit(onexit: RestrictedWorker_onexit_Callback | undefined) {
        const onexit_NonNull  = (onexit as RestrictedWorker_onexit_Callback)
        this.setOnexit(onexit_NonNull)
    }
    get onerror(): RestrictedWorker_onerror_Callback | undefined {
        return this.getOnerror()
    }
    set onerror(onerror: RestrictedWorker_onerror_Callback | undefined) {
        const onerror_NonNull  = (onerror as RestrictedWorker_onerror_Callback)
        this.setOnerror(onerror_NonNull)
    }
    get onmessage(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessage()
    }
    set onmessage(onmessage: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessage_NonNull  = (onmessage as RestrictedWorker_onmessage_Callback)
        this.setOnmessage(onmessage_NonNull)
    }
    get onmessageerror(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessageerror()
    }
    set onmessageerror(onmessageerror: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessageerror_NonNull  = (onmessageerror as RestrictedWorker_onmessage_Callback)
        this.setOnmessageerror(onmessageerror_NonNull)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RestrictedWorker.getFinalizer())
    }
    static ctor(scriptURL: string, options?: WorkerOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            WorkerOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_ctor(scriptURL, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scriptURL: string, options?: WorkerOptions) {
        this(RestrictedWorker.ctor((scriptURL)!, options))
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RestrictedWorker_getFinalizer()
    }
    public postMessage(message: Object, transfer?: Array<NativeBuffer> | PostMessageOptions | undefined): void {
        const message_type = runtimeType(message)
        const transfer_type = runtimeType(transfer)
        if (((RuntimeType.OBJECT) == (transfer_type)) && (TypeChecker.isArray_Buffer(transfer))) {
            const message_casted = message as (Object)
            const transfer_casted = transfer as (Array<NativeBuffer>)
            this.postMessage0_serialize(message_casted, transfer_casted)
            return
        }
        if ((RuntimeType.OBJECT == transfer_type) || (RuntimeType.UNDEFINED == transfer_type)) {
            const message_casted = message as (Object)
            const options_casted = transfer as (PostMessageOptions | undefined)
            this.postMessage1_serialize(message_casted, options_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public postMessageWithSharedSendable(message: Object, transfer?: Array<NativeBuffer>): void {
        const message_casted = message as (Object)
        const transfer_casted = transfer as (Array<NativeBuffer> | undefined)
        this.postMessageWithSharedSendable_serialize(message_casted, transfer_casted)
        return
    }
    public on(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.on_serialize(Type_casted, listener_casted)
        return
    }
    public once(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.once_serialize(Type_casted, listener_casted)
        return
    }
    public off(Type: string, listener?: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener | undefined)
        this.off_serialize(Type_casted, listener_casted)
        return
    }
    public terminate(): void {
        this.terminate_serialize()
        return
    }
    public addEventListener(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.addEventListener_serialize(Type_casted, listener_casted)
        return
    }
    public dispatchEvent(event: Event): boolean {
        const event_casted = event as (Event)
        return this.dispatchEvent_serialize(event_casted)
    }
    public removeEventListener(Type: string, callback_?: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const callback__casted = callback_ as (WorkerEventListener | undefined)
        this.removeEventListener_serialize(Type_casted, callback__casted)
        return
    }
    public removeAllListener(): void {
        this.removeAllListener_serialize()
        return
    }
    public registerGlobalCallObject(instanceName: string, globalCallObject: Object): void {
        const instanceName_casted = instanceName as (string)
        const globalCallObject_casted = globalCallObject as (Object)
        this.registerGlobalCallObject_serialize(instanceName_casted, globalCallObject_casted)
        return
    }
    public unregisterGlobalCallObject(instanceName?: string): void {
        const instanceName_casted = instanceName as (string | undefined)
        this.unregisterGlobalCallObject_serialize(instanceName_casted)
        return
    }
    private getOnexit(): RestrictedWorker_onexit_Callback | undefined {
        return this.getOnexit_serialize()
    }
    private setOnexit(onexit: RestrictedWorker_onexit_Callback): void {
        const onexit_casted = onexit as (RestrictedWorker_onexit_Callback)
        this.setOnexit_serialize(onexit_casted)
        return
    }
    private getOnerror(): RestrictedWorker_onerror_Callback | undefined {
        return this.getOnerror_serialize()
    }
    private setOnerror(onerror: RestrictedWorker_onerror_Callback): void {
        const onerror_casted = onerror as (RestrictedWorker_onerror_Callback)
        this.setOnerror_serialize(onerror_casted)
        return
    }
    private getOnmessage(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessage_serialize()
    }
    private setOnmessage(onmessage: RestrictedWorker_onmessage_Callback): void {
        const onmessage_casted = onmessage as (RestrictedWorker_onmessage_Callback)
        this.setOnmessage_serialize(onmessage_casted)
        return
    }
    private getOnmessageerror(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessageerror_serialize()
    }
    private setOnmessageerror(onmessageerror: RestrictedWorker_onmessage_Callback): void {
        const onmessageerror_casted = onmessageerror as (RestrictedWorker_onmessage_Callback)
        this.setOnmessageerror_serialize(onmessageerror_casted)
        return
    }
    private postMessage0_serialize(message: Object, transfer: Array<NativeBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        thisSerializer.writeInt32(transfer.length as int32)
        for (let i = 0; i < transfer.length; i++) {
            const transfer_element : NativeBuffer = transfer[i]
            thisSerializer.writeBuffer(transfer_element)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessage1_serialize(message: Object, options?: PostMessageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            PostMessageOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<NativeBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        let transfer_type : int32 = RuntimeType.UNDEFINED
        transfer_type = runtimeType(transfer)
        thisSerializer.writeInt8(transfer_type)
        if ((RuntimeType.UNDEFINED) != (transfer_type)) {
            const transfer_value  = transfer!
            thisSerializer.writeInt32(transfer_value.length as int32)
            for (let i = 0; i < transfer_value.length; i++) {
                const transfer_value_element : NativeBuffer = transfer_value[i]
                thisSerializer.writeBuffer(transfer_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessageWithSharedSendable(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private on_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_on(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private once_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_once(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private off_serialize(Type: string, listener?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let listener_type : int32 = RuntimeType.UNDEFINED
        listener_type = runtimeType(listener)
        thisSerializer.writeInt8(listener_type)
        if ((RuntimeType.UNDEFINED) != (listener_type)) {
            const listener_value  = listener!
            WorkerEventListener_serializer.write(thisSerializer, listener_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_off(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private terminate_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_terminate(this.peer!.ptr)
    }
    private addEventListener_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_addEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private dispatchEvent_serialize(event: Event): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Event_serializer.write(thisSerializer, event)
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_dispatchEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeEventListener_serialize(Type: string, callback_?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            WorkerEventListener_serializer.write(thisSerializer, callback__value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_removeEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeAllListener_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_removeAllListener(this.peer!.ptr)
    }
    private registerGlobalCallObject_serialize(instanceName: string, globalCallObject: Object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(globalCallObject)
        ArkUIGeneratedNativeModule._RestrictedWorker_registerGlobalCallObject(this.peer!.ptr, instanceName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private unregisterGlobalCallObject_serialize(instanceName?: string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let instanceName_type : int32 = RuntimeType.UNDEFINED
        instanceName_type = runtimeType(instanceName)
        thisSerializer.writeInt8(instanceName_type)
        if ((RuntimeType.UNDEFINED) != (instanceName_type)) {
            const instanceName_value  = instanceName!
            thisSerializer.writeString(instanceName_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_unregisterGlobalCallObject(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnexit_serialize(): RestrictedWorker_onexit_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnexit(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : RestrictedWorker_onexit_Callback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (code: number):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    buffer__argsSerializer.writeNumber(code);
    InteropNativeModule._CallCallback(-2095497263, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onexit_Callback | undefined = buffer
        return returnResult
    }
    private setOnexit_serialize(onexit: RestrictedWorker_onexit_Callback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onexit)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnexit(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnerror_serialize(): RestrictedWorker_onerror_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : RestrictedWorker_onerror_Callback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (ev: ErrorEvent):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    ErrorEvent_serializer.write(buffer__argsSerializer, ev);
    InteropNativeModule._CallCallback(-1213708823, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onerror_Callback | undefined = buffer
        return returnResult
    }
    private setOnerror_serialize(onerror: RestrictedWorker_onerror_Callback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onerror)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessage_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessage(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : RestrictedWorker_onmessage_Callback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    MessageEvents_serializer.write(buffer__argsSerializer, event);
    InteropNativeModule._CallCallback(1614214490, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessage_serialize(onmessage: RestrictedWorker_onmessage_Callback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onmessage)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessageerror_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessageerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : RestrictedWorker_onmessage_Callback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    MessageEvents_serializer.write(buffer__argsSerializer, event);
    InteropNativeModule._CallCallback(1614214490, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessageerror_serialize(onmessageerror: RestrictedWorker_onmessage_Callback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onmessageerror)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessageerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class SceneInternal {
    public static fromPtr(ptr: KPointer): Scene {
        return new Scene(ptr)
    }
}
export class Scene implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Scene.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scene_ctor()
        return retval
    }
    constructor() {
        this(Scene.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Scene_getFinalizer()
    }
    public static load(uri?: ResourceStr): Promise<Scene> {
        const uri_casted = uri as (ResourceStr | undefined)
        return Scene.load_serialize(uri_casted)
    }
    public destroy(): void {
        this.destroy_serialize()
        return
    }
    private static load_serialize(uri?: ResourceStr): Promise<Scene> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let uri_type : int32 = RuntimeType.UNDEFINED
        uri_type = runtimeType(uri)
        thisSerializer.writeInt8(uri_type)
        if ((RuntimeType.UNDEFINED) != (uri_type)) {
            const uri_value  = uri!
            let uri_value_type : int32 = RuntimeType.UNDEFINED
            uri_value_type = runtimeType(uri_value)
            if (RuntimeType.STRING == uri_value_type) {
                thisSerializer.writeInt8(0)
                const uri_value_0  = uri_value as string
                thisSerializer.writeString(uri_value_0)
            }
            else if (RuntimeType.OBJECT == uri_value_type) {
                thisSerializer.writeInt8(1)
                const uri_value_1  = uri_value as Resource
                Resource_serializer.write(thisSerializer, uri_value_1)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<Scene>()[0]
        ArkUIGeneratedNativeModule._Scene_load(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private destroy_serialize(): void {
        ArkUIGeneratedNativeModule._Scene_destroy(this.peer!.ptr)
    }
}
export class StateStylesOps {
    public static onStateStyleChange(node: KPointer, stateStyleChange: Callback_StateStylesChange): void {
        const node_casted = node as (KPointer)
        const stateStyleChange_casted = stateStyleChange as (Callback_StateStylesChange)
        StateStylesOps.onStateStyleChange_serialize(node_casted, stateStyleChange_casted)
        return
    }
    private static onStateStyleChange_serialize(node: KPointer, stateStyleChange: Callback_StateStylesChange): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(stateStyleChange)
        ArkUIGeneratedNativeModule._StateStylesOps_onStateStyleChange(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class SystemOps {
    public static StartFrame(): KPointer {
        return SystemOps.StartFrame_serialize()
    }
    public static EndFrame(root: KPointer): void {
        const root_casted = root as (KPointer)
        SystemOps.EndFrame_serialize(root_casted)
        return
    }
    public static syncInstanceId(instanceId: int32): void {
        const instanceId_casted = instanceId as (int32)
        SystemOps.syncInstanceId_serialize(instanceId_casted)
        return
    }
    public static restoreInstanceId(): void {
        SystemOps.restoreInstanceId_serialize()
        return
    }
    public static getResourceId(bundleName: string, moduleName: string, params: Array<string>): int32 {
        const bundleName_casted = bundleName as (string)
        const moduleName_casted = moduleName as (string)
        const params_casted = params as (Array<string>)
        return SystemOps.getResourceId_serialize(bundleName_casted, moduleName_casted, params_casted)
    }
    public static resourceManagerReset(): void {
        SystemOps.resourceManagerReset_serialize()
        return
    }
    public static setFrameCallback(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void {
        const onFrameCallback_casted = onFrameCallback as (((value0: number) => void))
        const onIdleCallback_casted = onIdleCallback as (((value0: number) => void))
        const delayTime_casted = delayTime as (number)
        SystemOps.setFrameCallback_serialize(onFrameCallback_casted, onIdleCallback_casted, delayTime_casted)
        return
    }
    private static StartFrame_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SystemOps_StartFrame()
        return retval
    }
    private static EndFrame_serialize(root: KPointer): void {
        ArkUIGeneratedNativeModule._SystemOps_EndFrame(root)
    }
    private static syncInstanceId_serialize(instanceId: int32): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(instanceId)
    }
    private static restoreInstanceId_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId()
    }
    private static getResourceId_serialize(bundleName: string, moduleName: string, params: Array<string>): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(params.length as int32)
        for (let i = 0; i < params.length; i++) {
            const params_element : string = params[i]
            thisSerializer.writeString(params_element)
        }
        const retval  = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleName, moduleName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static resourceManagerReset_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_resourceManagerReset()
    }
    private static setFrameCallback_serialize(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onFrameCallback)
        thisSerializer.holdAndWriteCallback(onIdleCallback)
        ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(), thisSerializer.length(), delayTime)
        thisSerializer.release()
    }
}
export class UIContextAtomicServiceBar {
    public static getBarRect(): Frame {
        return UIContextAtomicServiceBar.getBarRect_serialize()
    }
    private static getBarRect_serialize(): Frame {
        const retval  = ArkUIGeneratedNativeModule._UIContextAtomicServiceBar_getBarRect()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Frame = Frame_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export type Callback_RangeUpdate = (start: int32, end: int32) => void;
export type Callback_CreateItem = (index: int32) => KPointer;
export interface CustomColors {
    brand?: ResourceColor;
    warning?: ResourceColor;
    alert?: ResourceColor;
    confirm?: ResourceColor;
    fontPrimary?: ResourceColor;
    fontSecondary?: ResourceColor;
    fontTertiary?: ResourceColor;
    fontFourth?: ResourceColor;
    fontEmphasize?: ResourceColor;
    fontOnPrimary?: ResourceColor;
    fontOnSecondary?: ResourceColor;
    fontOnTertiary?: ResourceColor;
    fontOnFourth?: ResourceColor;
    iconPrimary?: ResourceColor;
    iconSecondary?: ResourceColor;
    iconTertiary?: ResourceColor;
    iconFourth?: ResourceColor;
    iconEmphasize?: ResourceColor;
    iconSubEmphasize?: ResourceColor;
    iconOnPrimary?: ResourceColor;
    iconOnSecondary?: ResourceColor;
    iconOnTertiary?: ResourceColor;
    iconOnFourth?: ResourceColor;
    backgroundPrimary?: ResourceColor;
    backgroundSecondary?: ResourceColor;
    backgroundTertiary?: ResourceColor;
    backgroundFourth?: ResourceColor;
    backgroundEmphasize?: ResourceColor;
    compForegroundPrimary?: ResourceColor;
    compBackgroundPrimary?: ResourceColor;
    compBackgroundPrimaryTran?: ResourceColor;
    compBackgroundPrimaryContrary?: ResourceColor;
    compBackgroundGray?: ResourceColor;
    compBackgroundSecondary?: ResourceColor;
    compBackgroundTertiary?: ResourceColor;
    compBackgroundEmphasize?: ResourceColor;
    compBackgroundNeutral?: ResourceColor;
    compEmphasizeSecondary?: ResourceColor;
    compEmphasizeTertiary?: ResourceColor;
    compDivider?: ResourceColor;
    compCommonContrary?: ResourceColor;
    compBackgroundFocus?: ResourceColor;
    compFocusedPrimary?: ResourceColor;
    compFocusedSecondary?: ResourceColor;
    compFocusedTertiary?: ResourceColor;
    interactiveHover?: ResourceColor;
    interactivePressed?: ResourceColor;
    interactiveFocus?: ResourceColor;
    interactiveActive?: ResourceColor;
    interactiveSelect?: ResourceColor;
    interactiveClick?: ResourceColor;
}
export interface WorkerOptions {
    type?: string;
    name?: string;
    shared?: boolean;
}
export interface Event {
    readonly type: string;
    readonly timeStamp: int64;
}
export interface ErrorEvent extends Event {
    readonly message: string;
    readonly filename: string;
    readonly lineno: number;
    readonly colno: number;
    readonly error: Object;
}
export interface MessageEvents extends Event {
    readonly data: object;
}
export type WorkerEventListener = (event: Event) => Promise<void>;
export interface PostMessageOptions {
    transfer?: Array<Object>;
}
export type RestrictedWorker_onexit_Callback = (code: number) => void;
export type RestrictedWorker_onerror_Callback = (ev: ErrorEvent) => void;
export type RestrictedWorker_onmessage_Callback = (event: MessageEvents) => void;
export type Callback_StateStylesChange = (currentState: int32) => void;
export class Scene_serializer {
    public static write(buffer: SerializerBase, value: Scene): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Scene {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SceneInternal.fromPtr(ptr)
    }
}
export class WorkerEventListener_serializer {
    public static write(buffer: SerializerBase, value: WorkerEventListener): void {
    }
    public static read(buffer: DeserializerBase): WorkerEventListener {
        throw new Error("Interface with functions is not supported")
    }
}
export class ErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: ErrorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_filename  = value.filename
        valueSerializer.writeString(value_filename)
        const value_lineno  = value.lineno
        valueSerializer.writeNumber(value_lineno)
        const value_colno  = value.colno
        valueSerializer.writeNumber(value_colno)
        const value_error  = value.error
        valueSerializer.holdAndWriteObject(value_error)
    }
    public static read(buffer: DeserializerBase): ErrorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        const message_result : string = (valueDeserializer.readString() as string)
        const filename_result : string = (valueDeserializer.readString() as string)
        const lineno_result : number = (valueDeserializer.readNumber() as number)
        const colno_result : number = (valueDeserializer.readNumber() as number)
        const error_result : Object = (valueDeserializer.readObject() as object)
        let value : ErrorEvent = ({type: type_result, timeStamp: timeStamp_result, message: message_result, filename: filename_result, lineno: lineno_result, colno: colno_result, error: error_result} as ErrorEvent)
        return value
    }
}
export class Event_serializer {
    public static write(buffer: SerializerBase, value: Event): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
    }
    public static read(buffer: DeserializerBase): Event {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        let value : Event = ({type: type_result, timeStamp: timeStamp_result} as Event)
        return value
    }
}
export class MessageEvents_serializer {
    public static write(buffer: SerializerBase, value: MessageEvents): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
        const value_data  = value.data
        valueSerializer.holdAndWriteObject(value_data)
    }
    public static read(buffer: DeserializerBase): MessageEvents {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        const data_result : object = (valueDeserializer.readObject() as object)
        let value : MessageEvents = ({type: type_result, timeStamp: timeStamp_result, data: data_result} as MessageEvents)
        return value
    }
}
export class PostMessageOptions_serializer {
    public static write(buffer: SerializerBase, value: PostMessageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_transfer  = value.transfer
        let value_transfer_type : int32 = RuntimeType.UNDEFINED
        value_transfer_type = runtimeType(value_transfer)
        valueSerializer.writeInt8(value_transfer_type)
        if ((RuntimeType.UNDEFINED) != (value_transfer_type)) {
            const value_transfer_value  = value_transfer!
            valueSerializer.writeInt32(value_transfer_value.length as int32)
            for (let i = 0; i < value_transfer_value.length; i++) {
                const value_transfer_value_element : Object = value_transfer_value[i]
                valueSerializer.holdAndWriteObject(value_transfer_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): PostMessageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const transfer_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let transfer_buf : Array<Object> | undefined
        if ((RuntimeType.UNDEFINED) != (transfer_buf_runtimeType))
        {
            const transfer_buf__length : int32 = valueDeserializer.readInt32()
            let transfer_buf_ : Array<Object> = new Array<Object>(transfer_buf__length)
            for (let transfer_buf__i = 0; transfer_buf__i < transfer_buf__length; transfer_buf__i++) {
                transfer_buf_[transfer_buf__i] = (valueDeserializer.readObject() as object)
            }
            transfer_buf = transfer_buf_
        }
        const transfer_result : Array<Object> | undefined = transfer_buf
        let value : PostMessageOptions = ({transfer: transfer_result} as PostMessageOptions)
        return value
    }
}
export class WorkerOptions_serializer {
    public static write(buffer: SerializerBase, value: WorkerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8(value_type_type)
        if ((RuntimeType.UNDEFINED) != (value_type_type)) {
            const value_type_value  = value_type!
            valueSerializer.writeString(value_type_value)
        }
        const value_name  = value.name
        let value_name_type : int32 = RuntimeType.UNDEFINED
        value_name_type = runtimeType(value_name)
        valueSerializer.writeInt8(value_name_type)
        if ((RuntimeType.UNDEFINED) != (value_name_type)) {
            const value_name_value  = value_name!
            valueSerializer.writeString(value_name_value)
        }
        const value_shared  = value.shared
        let value_shared_type : int32 = RuntimeType.UNDEFINED
        value_shared_type = runtimeType(value_shared)
        valueSerializer.writeInt8(value_shared_type)
        if ((RuntimeType.UNDEFINED) != (value_shared_type)) {
            const value_shared_value  = value_shared!
            valueSerializer.writeBoolean(value_shared_value)
        }
    }
    public static read(buffer: DeserializerBase): WorkerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const type_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let type_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (type_buf_runtimeType))
        {
            type_buf = (valueDeserializer.readString() as string)
        }
        const type_result : string | undefined = type_buf
        const name_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let name_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (name_buf_runtimeType))
        {
            name_buf = (valueDeserializer.readString() as string)
        }
        const name_result : string | undefined = name_buf
        const shared_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let shared_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (shared_buf_runtimeType))
        {
            shared_buf = valueDeserializer.readBoolean()
        }
        const shared_result : boolean | undefined = shared_buf
        let value : WorkerOptions = ({type: type_result, name: name_result, shared: shared_result} as WorkerOptions)
        return value
    }
}
export class RestrictedWorker_serializer {
    public static write(buffer: SerializerBase, value: RestrictedWorker): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RestrictedWorker {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RestrictedWorkerInternal.fromPtr(ptr)
    }
}
