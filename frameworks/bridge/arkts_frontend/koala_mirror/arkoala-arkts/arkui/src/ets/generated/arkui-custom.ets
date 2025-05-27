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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ResourceStr, Font, ResourceColor } from "./units"
import { Resource } from "./resource"
import { AnimateParam, SheetOptions } from "./common"
import { Callback_Void } from "./ability_component"
import { TextPickerDialogOptions } from "./text_picker"
import { FrameNode, FrameNodeInternal } from "./arkui-framenode"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class BaseContextInternal {
    public static fromPtr(ptr: KPointer): BaseContext {
        const obj : BaseContext = new BaseContext()
        obj.peer = new Finalizable(ptr, BaseContext.getFinalizer())
        return obj
    }
}
export class BaseContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get stageMode(): boolean {
        return this.getStageMode()
    }
    set stageMode(stageMode: boolean) {
        this.setStageMode(stageMode)
    }
    static ctor_basecontext(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseContext_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = BaseContext.ctor_basecontext()
        this.peer = new Finalizable(ctorPtr, BaseContext.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseContext_getFinalizer()
    }
    private getStageMode(): boolean {
        return this.getStageMode_serialize()
    }
    private setStageMode(stageMode: boolean): void {
        const stageMode_casted = stageMode as (boolean)
        this.setStageMode_serialize(stageMode_casted)
        return
    }
    private getStageMode_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._BaseContext_getStageMode(this.peer!.ptr)
        return retval
    }
    private setStageMode_serialize(stageMode: boolean): void {
        ArkUIGeneratedNativeModule._BaseContext_setStageMode(this.peer!.ptr, stageMode ? 1 : 0)
    }
}
export class UnifiedDataInternal {
    public static fromPtr(ptr: KPointer): UnifiedData {
        const obj : UnifiedData = new UnifiedData()
        obj.peer = new Finalizable(ptr, UnifiedData.getFinalizer())
        return obj
    }
}
export class UnifiedData implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_unifieddata(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UnifiedData_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UnifiedData.ctor_unifieddata()
        this.peer = new Finalizable(ctorPtr, UnifiedData.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UnifiedData_getFinalizer()
    }
    public hasType(UnifiedData_type: string): boolean {
        const UnifiedData_type_casted = UnifiedData_type as (string)
        return this.hasType_serialize(UnifiedData_type_casted)
    }
    public getTypes(): Array<string> {
        return this.getTypes_serialize()
    }
    private hasType_serialize(UnifiedData_type: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._UnifiedData_hasType(this.peer!.ptr, UnifiedData_type)
        return retval
    }
    private getTypes_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._UnifiedData_getTypes(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
}
export class LazyForEachOps {
    public static NeedMoreElements(node: KPointer, mark: KPointer, direction: int32): KPointer {
        const node_casted = node as (KPointer)
        const mark_casted = mark as (KPointer)
        const direction_casted = direction as (int32)
        return LazyForEachOps.NeedMoreElements_serialize(node_casted, mark_casted, direction_casted)
    }
    public static OnRangeUpdate(node: KPointer, totalCount: int32, updater: Callback_RangeUpdate): void {
        const node_casted = node as (KPointer)
        const totalCount_casted = totalCount as (int32)
        const updater_casted = updater as (Callback_RangeUpdate)
        LazyForEachOps.OnRangeUpdate_serialize(node_casted, totalCount_casted, updater_casted)
        return
    }
    public static SetCurrentIndex(node: KPointer, index: int32): void {
        const node_casted = node as (KPointer)
        const index_casted = index as (int32)
        LazyForEachOps.SetCurrentIndex_serialize(node_casted, index_casted)
        return
    }
    public static Prepare(node: KPointer, itemCount: int32, offset: int32): void {
        const node_casted = node as (KPointer)
        const itemCount_casted = itemCount as (int32)
        const offset_casted = offset as (int32)
        LazyForEachOps.Prepare_serialize(node_casted, itemCount_casted, offset_casted)
        return
    }
    public static NotifyChange(node: KPointer, startIndex: int32, endIndex: int32, count: int32): void {
        const node_casted = node as (KPointer)
        const startIndex_casted = startIndex as (int32)
        const endIndex_casted = endIndex as (int32)
        const count_casted = count as (int32)
        LazyForEachOps.NotifyChange_serialize(node_casted, startIndex_casted, endIndex_casted, count_casted)
        return
    }
    private static NeedMoreElements_serialize(node: KPointer, mark: KPointer, direction: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LazyForEachOps_NeedMoreElements(node, mark, direction)
        return retval
    }
    private static OnRangeUpdate_serialize(node: KPointer, totalCount: int32, updater: Callback_RangeUpdate): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_OnRangeUpdate(node, totalCount, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetCurrentIndex_serialize(node: KPointer, index: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_SetCurrentIndex(node, index)
    }
    private static Prepare_serialize(node: KPointer, itemCount: int32, offset: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_Prepare(node, itemCount, offset)
    }
    private static NotifyChange_serialize(node: KPointer, startIndex: int32, endIndex: int32, count: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_NotifyChange(node, startIndex, endIndex, count)
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(params.length as int32)
        for (let i = 0; i < params.length; i++) {
            const params_element : string = params[i]
            thisSerializer.writeString(params_element)
        }
        const retval  = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleName, moduleName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
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
export class ComponentContentInternal {
    public static fromPtr(ptr: KPointer): ComponentContent {
        const obj : ComponentContent = new ComponentContent()
        obj.peer = new Finalizable(ptr, ComponentContent.getFinalizer())
        return obj
    }
}
export class ComponentContent implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_componentcontent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ComponentContent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ComponentContent.ctor_componentcontent()
        this.peer = new Finalizable(ctorPtr, ComponentContent.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ComponentContent_getFinalizer()
    }
    public update(args: Object): void {
        const args_casted = args as (Object)
        this.update_serialize(args_casted)
        return
    }
    public reuse(param?: Object): void {
        const param_casted = param as (Object | undefined)
        this.reuse_serialize(param_casted)
        return
    }
    public recycle(): void {
        this.recycle_serialize()
        return
    }
    public dispose(): void {
        this.dispose_serialize()
        return
    }
    public updateConfiguration(): void {
        this.updateConfiguration_serialize()
        return
    }
    private update_serialize(args: Object): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(args)
        ArkUIGeneratedNativeModule._ComponentContent_update(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private reuse_serialize(param?: Object): void {
        const thisSerializer : Serializer = Serializer.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8(param_type)
        if ((RuntimeType.UNDEFINED) != (param_type)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        ArkUIGeneratedNativeModule._ComponentContent_reuse(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private recycle_serialize(): void {
        ArkUIGeneratedNativeModule._ComponentContent_recycle(this.peer!.ptr)
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._ComponentContent_dispose(this.peer!.ptr)
    }
    private updateConfiguration_serialize(): void {
        ArkUIGeneratedNativeModule._ComponentContent_updateConfiguration(this.peer!.ptr)
    }
}
export class SceneInternal {
    public static fromPtr(ptr: KPointer): Scene {
        const obj : Scene = new Scene()
        obj.peer = new Finalizable(ptr, Scene.getFinalizer())
        return obj
    }
}
export class Scene implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scene(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scene_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = Scene.ctor_scene()
        this.peer = new Finalizable(ctorPtr, Scene.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Scene_getFinalizer()
    }
    public static load(uri?: ResourceStr): Scene {
        const uri_casted = uri as (ResourceStr | undefined)
        return Scene.load_serialize(uri_casted)
    }
    public destroy(): void {
        this.destroy_serialize()
        return
    }
    private static load_serialize(uri?: ResourceStr): Scene {
        const thisSerializer : Serializer = Serializer.hold()
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
                thisSerializer.writeResource(uri_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._Scene_load(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Scene = SceneInternal.fromPtr(retval)
        return obj
    }
    private destroy_serialize(): void {
        ArkUIGeneratedNativeModule._Scene_destroy(this.peer!.ptr)
    }
}
export interface WorkerEventListener {
    invoke(event: Event): void
}
export class WorkerEventListenerInternal implements MaterializedBase,WorkerEventListener {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_workereventlistener(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WorkerEventListener_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WorkerEventListenerInternal.ctor_workereventlistener()
        this.peer = new Finalizable(ctorPtr, WorkerEventListenerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WorkerEventListener_getFinalizer()
    }
    public invoke(event: Event): void {
        const event_casted = event as (Event)
        this.invoke_serialize(event_casted)
        return
    }
    private invoke_serialize(event: Event): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEvent(event)
        ArkUIGeneratedNativeModule._WorkerEventListener_invoke(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): WorkerEventListenerInternal {
        const obj : WorkerEventListenerInternal = new WorkerEventListenerInternal()
        obj.peer = new Finalizable(ptr, WorkerEventListenerInternal.getFinalizer())
        return obj
    }
}
export class RestrictedWorkerInternal {
    public static fromPtr(ptr: KPointer): RestrictedWorker {
        const obj : RestrictedWorker = new RestrictedWorker(undefined, undefined)
        obj.peer = new Finalizable(ptr, RestrictedWorker.getFinalizer())
        return obj
    }
}
export class RestrictedWorker implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onexit(): RestrictedWorker_onexit_Callback | undefined {
        throw new Error("Not implemented")
    }
    set onexit(onexit: RestrictedWorker_onexit_Callback | undefined) {
        const onexit_NonNull  = (onexit as RestrictedWorker_onexit_Callback)
        this.setOnexit(onexit_NonNull)
    }
    get onerror(): RestrictedWorker_onerror_Callback | undefined {
        throw new Error("Not implemented")
    }
    set onerror(onerror: RestrictedWorker_onerror_Callback | undefined) {
        const onerror_NonNull  = (onerror as RestrictedWorker_onerror_Callback)
        this.setOnerror(onerror_NonNull)
    }
    get onmessage(): RestrictedWorker_onmessage_Callback | undefined {
        throw new Error("Not implemented")
    }
    set onmessage(onmessage: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessage_NonNull  = (onmessage as RestrictedWorker_onmessage_Callback)
        this.setOnmessage(onmessage_NonNull)
    }
    get onmessageerror(): RestrictedWorker_onmessage_Callback | undefined {
        throw new Error("Not implemented")
    }
    set onmessageerror(onmessageerror: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessageerror_NonNull  = (onmessageerror as RestrictedWorker_onmessage_Callback)
        this.setOnmessageerror(onmessageerror_NonNull)
    }
    static ctor_restrictedworker(scriptURL: string, options?: WorkerOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeWorkerOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_ctor(scriptURL, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scriptURL?: string, options?: WorkerOptions) {
        if (((scriptURL) !== (undefined)) || ((options) !== (undefined)))
        {
            const ctorPtr : KPointer = RestrictedWorker.ctor_restrictedworker((scriptURL)!, options)
            this.peer = new Finalizable(ctorPtr, RestrictedWorker.getFinalizer())
        }
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
        const thisSerializer : Serializer = Serializer.hold()
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(message)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writePostMessageOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<NativeBuffer>): void {
        const thisSerializer : Serializer = Serializer.hold()
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
        ArkUIGeneratedNativeModule._RestrictedWorker_on(this.peer!.ptr, Type, toPeerPtr(listener))
    }
    private once_serialize(Type: string, listener: WorkerEventListener): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_once(this.peer!.ptr, Type, toPeerPtr(listener))
    }
    private off_serialize(Type: string, listener?: WorkerEventListener): void {
        const thisSerializer : Serializer = Serializer.hold()
        let listener_type : int32 = RuntimeType.UNDEFINED
        listener_type = runtimeType(listener)
        thisSerializer.writeInt8(listener_type)
        if ((RuntimeType.UNDEFINED) != (listener_type)) {
            const listener_value  = listener!
            thisSerializer.writeWorkerEventListener(listener_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_off(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private terminate_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_terminate(this.peer!.ptr)
    }
    private addEventListener_serialize(Type: string, listener: WorkerEventListener): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_addEventListener(this.peer!.ptr, Type, toPeerPtr(listener))
    }
    private dispatchEvent_serialize(event: Event): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEvent(event)
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_dispatchEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeEventListener_serialize(Type: string, callback_?: WorkerEventListener): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.writeWorkerEventListener(callback__value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_removeEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeAllListener_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_removeAllListener(this.peer!.ptr)
    }
    private registerGlobalCallObject_serialize(instanceName: string, globalCallObject: Object): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(globalCallObject)
        ArkUIGeneratedNativeModule._RestrictedWorker_registerGlobalCallObject(this.peer!.ptr, instanceName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private unregisterGlobalCallObject_serialize(instanceName?: string): void {
        const thisSerializer : Serializer = Serializer.hold()
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnexit_serialize(onexit: RestrictedWorker_onexit_Callback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onexit)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnexit(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnerror_serialize(): RestrictedWorker_onerror_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnerror(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnerror_serialize(onerror: RestrictedWorker_onerror_Callback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onerror)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessage_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessage(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnmessage_serialize(onmessage: RestrictedWorker_onmessage_Callback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onmessage)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessageerror_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessageerror(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnmessageerror_serialize(onmessageerror: RestrictedWorker_onmessage_Callback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onmessageerror)
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessageerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class UIContextInternal {
    public static fromPtr(ptr: KPointer): UIContext {
        const obj : UIContext = new UIContext()
        obj.peer = new Finalizable(ptr, UIContext.getFinalizer())
        return obj
    }
}
export class UIContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uicontext(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIContext_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UIContext.ctor_uicontext()
        this.peer = new Finalizable(ctorPtr, UIContext.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIContext_getFinalizer()
    }
    public getFont(): Font {
        return this.getFont_serialize()
    }
    public getFilteredInspectorTree(filters?: Array<string>): string {
        const filters_casted = filters as (Array<string> | undefined)
        return this.getFilteredInspectorTree_serialize(filters_casted)
    }
    public getFilteredInspectorTreeById(id: string, depth: number, filters?: Array<string>): string {
        const id_casted = id as (string)
        const depth_casted = depth as (number)
        const filters_casted = filters as (Array<string> | undefined)
        return this.getFilteredInspectorTreeById_serialize(id_casted, depth_casted, filters_casted)
    }
    public animateTo(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        this.animateTo_serialize(value_casted, event_casted)
        return
    }
    public showTextPickerDialog(options: TextPickerDialogOptions): void {
        const options_casted = options as (TextPickerDialogOptions)
        this.showTextPickerDialog_serialize(options_casted)
        return
    }
    public runScopedTask(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this.runScopedTask_serialize(callback__casted)
        return
    }
    public animateToImmediately(param: AnimateParam, event: (() => void)): void {
        const param_casted = param as (AnimateParam)
        const event_casted = event as ((() => void))
        this.animateToImmediately_serialize(param_casted, event_casted)
        return
    }
    public getFrameNodeById(id: string): FrameNode | undefined {
        const id_casted = id as (string)
        return this.getFrameNodeById_serialize(id_casted)
    }
    public getAttachedFrameNodeById(id: string): FrameNode | undefined {
        const id_casted = id as (string)
        return this.getAttachedFrameNodeById_serialize(id_casted)
    }
    public getFrameNodeByUniqueId(id: number): FrameNode | undefined {
        const id_casted = id as (number)
        return this.getFrameNodeByUniqueId_serialize(id_casted)
    }
    public vp2px(value: number): number {
        const value_casted = value as (number)
        return this.vp2px_serialize(value_casted)
    }
    public px2vp(value: number): number {
        const value_casted = value as (number)
        return this.px2vp_serialize(value_casted)
    }
    public fp2px(value: number): number {
        const value_casted = value as (number)
        return this.fp2px_serialize(value_casted)
    }
    public px2fp(value: number): number {
        const value_casted = value as (number)
        return this.px2fp_serialize(value_casted)
    }
    public lpx2px(value: number): number {
        const value_casted = value as (number)
        return this.lpx2px_serialize(value_casted)
    }
    public px2lpx(value: number): number {
        const value_casted = value as (number)
        return this.px2lpx_serialize(value_casted)
    }
    public getHostContext(): Context | undefined {
        return this.getHostContext_serialize()
    }
    public setDynamicDimming(id: string, value: number): void {
        const id_casted = id as (string)
        const value_casted = value as (number)
        this.setDynamicDimming_serialize(id_casted, value_casted)
        return
    }
    public getWindowName(): string | undefined {
        return this.getWindowName_serialize()
    }
    public openBindSheet<T extends Object>(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: number): void {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        const sheetOptions_casted = sheetOptions as (SheetOptions | undefined)
        const targetId_casted = targetId as (number | undefined)
        this.openBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, targetId_casted)
        return
    }
    public updateBindSheet<T extends Object>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): void {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        const sheetOptions_casted = sheetOptions as (SheetOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        this.updateBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, partialUpdate_casted)
        return
    }
    public closeBindSheet<T extends Object>(bindSheetContent: ComponentContent): void {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        this.closeBindSheet_serialize(bindSheetContent_casted)
        return
    }
    public clearResourceCache(): void {
        this.clearResourceCache_serialize()
        return
    }
    public isFollowingSystemFontScale(): boolean {
        return this.isFollowingSystemFontScale_serialize()
    }
    public getMaxFontScale(): number {
        return this.getMaxFontScale_serialize()
    }
    private getFont_serialize(): Font {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFont(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : Font = retvalDeserializer.readFont()
        return returnResult
    }
    private getFilteredInspectorTree_serialize(filters?: Array<string>): string {
        const thisSerializer : Serializer = Serializer.hold()
        let filters_type : int32 = RuntimeType.UNDEFINED
        filters_type = runtimeType(filters)
        thisSerializer.writeInt8(filters_type)
        if ((RuntimeType.UNDEFINED) != (filters_type)) {
            const filters_value  = filters!
            thisSerializer.writeInt32(filters_value.length as int32)
            for (let i = 0; i < filters_value.length; i++) {
                const filters_value_element : string = filters_value[i]
                thisSerializer.writeString(filters_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFilteredInspectorTree(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getFilteredInspectorTreeById_serialize(id: string, depth: number, filters?: Array<string>): string {
        const thisSerializer : Serializer = Serializer.hold()
        let filters_type : int32 = RuntimeType.UNDEFINED
        filters_type = runtimeType(filters)
        thisSerializer.writeInt8(filters_type)
        if ((RuntimeType.UNDEFINED) != (filters_type)) {
            const filters_value  = filters!
            thisSerializer.writeInt32(filters_value.length as int32)
            for (let i = 0; i < filters_value.length; i++) {
                const filters_value_element : string = filters_value[i]
                thisSerializer.writeString(filters_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFilteredInspectorTreeById(this.peer!.ptr, id, depth, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private animateTo_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._UIContext_animateTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private showTextPickerDialog_serialize(options: TextPickerDialogOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextPickerDialogOptions(options)
        ArkUIGeneratedNativeModule._UIContext_showTextPickerDialog(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private runScopedTask_serialize(callback_: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIContext_runScopedTask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private animateToImmediately_serialize(param: AnimateParam, event: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(param)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._UIContext_animateToImmediately(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFrameNodeById_serialize(id: string): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFrameNodeById(this.peer!.ptr, id)
        throw new Error("Object deserialization is not implemented.")
    }
    private getAttachedFrameNodeById_serialize(id: string): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getAttachedFrameNodeById(this.peer!.ptr, id)
        throw new Error("Object deserialization is not implemented.")
    }
    private getFrameNodeByUniqueId_serialize(id: number): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFrameNodeByUniqueId(this.peer!.ptr, id)
        throw new Error("Object deserialization is not implemented.")
    }
    private vp2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_vp2px(this.peer!.ptr, value)
        return retval
    }
    private px2vp_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2vp(this.peer!.ptr, value)
        return retval
    }
    private fp2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_fp2px(this.peer!.ptr, value)
        return retval
    }
    private px2fp_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2fp(this.peer!.ptr, value)
        return retval
    }
    private lpx2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_lpx2px(this.peer!.ptr, value)
        return retval
    }
    private px2lpx_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2lpx(this.peer!.ptr, value)
        return retval
    }
    private getHostContext_serialize(): Context | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getHostContext(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDynamicDimming_serialize(id: string, value: number): void {
        ArkUIGeneratedNativeModule._UIContext_setDynamicDimming(this.peer!.ptr, id, value)
    }
    private getWindowName_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getWindowName(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private openBindSheet_serialize<T extends Object>(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let sheetOptions_type : int32 = RuntimeType.UNDEFINED
        sheetOptions_type = runtimeType(sheetOptions)
        thisSerializer.writeInt8(sheetOptions_type)
        if ((RuntimeType.UNDEFINED) != (sheetOptions_type)) {
            const sheetOptions_value  = sheetOptions!
            thisSerializer.writeSheetOptions(sheetOptions_value)
        }
        let targetId_type : int32 = RuntimeType.UNDEFINED
        targetId_type = runtimeType(targetId)
        thisSerializer.writeInt8(targetId_type)
        if ((RuntimeType.UNDEFINED) != (targetId_type)) {
            const targetId_value  = targetId!
            thisSerializer.writeNumber(targetId_value)
        }
        ArkUIGeneratedNativeModule._UIContext_openBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private updateBindSheet_serialize<T extends Object>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSheetOptions(sheetOptions)
        let partialUpdate_type : int32 = RuntimeType.UNDEFINED
        partialUpdate_type = runtimeType(partialUpdate)
        thisSerializer.writeInt8(partialUpdate_type)
        if ((RuntimeType.UNDEFINED) != (partialUpdate_type)) {
            const partialUpdate_value  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdate_value)
        }
        ArkUIGeneratedNativeModule._UIContext_updateBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeBindSheet_serialize<T extends Object>(bindSheetContent: ComponentContent): void {
        ArkUIGeneratedNativeModule._UIContext_closeBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent))
    }
    private clearResourceCache_serialize(): void {
        ArkUIGeneratedNativeModule._UIContext_clearResourceCache(this.peer!.ptr)
    }
    private isFollowingSystemFontScale_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._UIContext_isFollowingSystemFontScale(this.peer!.ptr)
        return retval
    }
    private getMaxFontScale_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getMaxFontScale(this.peer!.ptr)
        return retval
    }
}
export type Context_getGroupDir_Callback = (result: string) => void;
export enum PointerStyle {
    DEFAULT = 0,
    EAST = 1,
    WEST = 2,
    SOUTH = 3,
    NORTH = 4,
    WEST_EAST = 5,
    NORTH_SOUTH = 6,
    NORTH_EAST = 7,
    NORTH_WEST = 8,
    SOUTH_EAST = 9,
    SOUTH_WEST = 10,
    NORTH_EAST_SOUTH_WEST = 11,
    NORTH_WEST_SOUTH_EAST = 12,
    CROSS = 13,
    CURSOR_COPY = 14,
    CURSOR_FORBID = 15,
    COLOR_SUCKER = 16,
    HAND_GRABBING = 17,
    HAND_OPEN = 18,
    HAND_POINTING = 19,
    HELP = 20,
    MOVE = 21,
    RESIZE_LEFT_RIGHT = 22,
    RESIZE_UP_DOWN = 23,
    SCREENSHOT_CHOOSE = 24,
    SCREENSHOT_CURSOR = 25,
    TEXT_CURSOR = 26,
    ZOOM_IN = 27,
    ZOOM_OUT = 28,
    MIDDLE_BTN_EAST = 29,
    MIDDLE_BTN_WEST = 30,
    MIDDLE_BTN_SOUTH = 31,
    MIDDLE_BTN_NORTH = 32,
    MIDDLE_BTN_NORTH_SOUTH = 33,
    MIDDLE_BTN_NORTH_EAST = 34,
    MIDDLE_BTN_NORTH_WEST = 35,
    MIDDLE_BTN_SOUTH_EAST = 36,
    MIDDLE_BTN_SOUTH_WEST = 37,
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,
    HORIZONTAL_TEXT_CURSOR = 39,
    CURSOR_CROSS = 40,
    CURSOR_CIRCLE = 41,
    LOADING = 42,
    RUNNING = 43
}
export type Callback_RangeUpdate = (index: int32, mark: KPointer, end: int32) => void;
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
export interface CustomTheme {
    colors?: CustomColors;
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
export interface PostMessageOptions {
    transfer?: Array<Object>;
}
export type RestrictedWorker_onexit_Callback = (code: number) => void;
export type RestrictedWorker_onerror_Callback = (ev: ErrorEvent) => void;
export type RestrictedWorker_onmessage_Callback = (event: MessageEvents) => void;
export interface SystemBarStyle {
    statusBarContentColor?: string;
}
export class ContextInternal {
    public static fromPtr(ptr: KPointer): Context {
        const obj : Context = new Context()
        obj.peer = new Finalizable(ptr, Context.getFinalizer())
        return obj
    }
}
export class Context extends BaseContext implements MaterializedBase {
    get cacheDir(): string {
        return this.getCacheDir()
    }
    set cacheDir(cacheDir: string) {
        this.setCacheDir(cacheDir)
    }
    get tempDir(): string {
        return this.getTempDir()
    }
    set tempDir(tempDir: string) {
        this.setTempDir(tempDir)
    }
    get filesDir(): string {
        return this.getFilesDir()
    }
    set filesDir(filesDir: string) {
        this.setFilesDir(filesDir)
    }
    get databaseDir(): string {
        return this.getDatabaseDir()
    }
    set databaseDir(databaseDir: string) {
        this.setDatabaseDir(databaseDir)
    }
    get preferencesDir(): string {
        return this.getPreferencesDir()
    }
    set preferencesDir(preferencesDir: string) {
        this.setPreferencesDir(preferencesDir)
    }
    get bundleCodeDir(): string {
        return this.getBundleCodeDir()
    }
    set bundleCodeDir(bundleCodeDir: string) {
        this.setBundleCodeDir(bundleCodeDir)
    }
    get distributedFilesDir(): string {
        return this.getDistributedFilesDir()
    }
    set distributedFilesDir(distributedFilesDir: string) {
        this.setDistributedFilesDir(distributedFilesDir)
    }
    get resourceDir(): string {
        return this.getResourceDir()
    }
    set resourceDir(resourceDir: string) {
        this.setResourceDir(resourceDir)
    }
    get cloudFileDir(): string {
        return this.getCloudFileDir()
    }
    set cloudFileDir(cloudFileDir: string) {
        this.setCloudFileDir(cloudFileDir)
    }
    static ctor_context(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Context_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = Context.ctor_context()
        this.peer = new Finalizable(ctorPtr, Context.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Context_getFinalizer()
    }
    public createBundleContext(bundleName: string): Context {
        const bundleName_casted = bundleName as (string)
        return this.createBundleContext_serialize(bundleName_casted)
    }
    public createModuleContext(bundleName: string, moduleName?: string): Context {
        const bundleName_type = runtimeType(bundleName)
        const moduleName_type = runtimeType(moduleName)
        const moduleName_casted = bundleName as (string)
        return this.createModuleContext0_serialize(moduleName_casted)
    }
    public getGroupDir(dataGroupID: string, callback_?: Context_getGroupDir_Callback): string | undefined {
        const dataGroupID_type = runtimeType(dataGroupID)
        const callback__type = runtimeType(callback_)
        const dataGroupID_casted = dataGroupID as (string)
        return this.getGroupDir1_serialize(dataGroupID_casted)
    }
    private getCacheDir(): string {
        return this.getCacheDir_serialize()
    }
    private setCacheDir(cacheDir: string): void {
        const cacheDir_casted = cacheDir as (string)
        this.setCacheDir_serialize(cacheDir_casted)
        return
    }
    private getTempDir(): string {
        return this.getTempDir_serialize()
    }
    private setTempDir(tempDir: string): void {
        const tempDir_casted = tempDir as (string)
        this.setTempDir_serialize(tempDir_casted)
        return
    }
    private getFilesDir(): string {
        return this.getFilesDir_serialize()
    }
    private setFilesDir(filesDir: string): void {
        const filesDir_casted = filesDir as (string)
        this.setFilesDir_serialize(filesDir_casted)
        return
    }
    private getDatabaseDir(): string {
        return this.getDatabaseDir_serialize()
    }
    private setDatabaseDir(databaseDir: string): void {
        const databaseDir_casted = databaseDir as (string)
        this.setDatabaseDir_serialize(databaseDir_casted)
        return
    }
    private getPreferencesDir(): string {
        return this.getPreferencesDir_serialize()
    }
    private setPreferencesDir(preferencesDir: string): void {
        const preferencesDir_casted = preferencesDir as (string)
        this.setPreferencesDir_serialize(preferencesDir_casted)
        return
    }
    private getBundleCodeDir(): string {
        return this.getBundleCodeDir_serialize()
    }
    private setBundleCodeDir(bundleCodeDir: string): void {
        const bundleCodeDir_casted = bundleCodeDir as (string)
        this.setBundleCodeDir_serialize(bundleCodeDir_casted)
        return
    }
    private getDistributedFilesDir(): string {
        return this.getDistributedFilesDir_serialize()
    }
    private setDistributedFilesDir(distributedFilesDir: string): void {
        const distributedFilesDir_casted = distributedFilesDir as (string)
        this.setDistributedFilesDir_serialize(distributedFilesDir_casted)
        return
    }
    private getResourceDir(): string {
        return this.getResourceDir_serialize()
    }
    private setResourceDir(resourceDir: string): void {
        const resourceDir_casted = resourceDir as (string)
        this.setResourceDir_serialize(resourceDir_casted)
        return
    }
    private getCloudFileDir(): string {
        return this.getCloudFileDir_serialize()
    }
    private setCloudFileDir(cloudFileDir: string): void {
        const cloudFileDir_casted = cloudFileDir as (string)
        this.setCloudFileDir_serialize(cloudFileDir_casted)
        return
    }
    private createBundleContext_serialize(bundleName: string): Context {
        const retval  = ArkUIGeneratedNativeModule._Context_createBundleContext(this.peer!.ptr, bundleName)
        const obj : Context = ContextInternal.fromPtr(retval)
        return obj
    }
    private createModuleContext0_serialize(moduleName: string): Context {
        const retval  = ArkUIGeneratedNativeModule._Context_createModuleContext0(this.peer!.ptr, moduleName)
        const obj : Context = ContextInternal.fromPtr(retval)
        return obj
    }
    private createModuleContext1_serialize(bundleName: string, moduleName: string): Context {
        const retval  = ArkUIGeneratedNativeModule._Context_createModuleContext1(this.peer!.ptr, bundleName, moduleName)
        const obj : Context = ContextInternal.fromPtr(retval)
        return obj
    }
    private getGroupDir0_serialize(dataGroupID: string, callback_: Context_getGroupDir_Callback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._Context_getGroupDir0(this.peer!.ptr, dataGroupID, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getGroupDir1_serialize(dataGroupID: string): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getGroupDir1(this.peer!.ptr, dataGroupID)
        return retval
    }
    private getCacheDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getCacheDir(this.peer!.ptr)
        return retval
    }
    private setCacheDir_serialize(cacheDir: string): void {
        ArkUIGeneratedNativeModule._Context_setCacheDir(this.peer!.ptr, cacheDir)
    }
    private getTempDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getTempDir(this.peer!.ptr)
        return retval
    }
    private setTempDir_serialize(tempDir: string): void {
        ArkUIGeneratedNativeModule._Context_setTempDir(this.peer!.ptr, tempDir)
    }
    private getFilesDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getFilesDir(this.peer!.ptr)
        return retval
    }
    private setFilesDir_serialize(filesDir: string): void {
        ArkUIGeneratedNativeModule._Context_setFilesDir(this.peer!.ptr, filesDir)
    }
    private getDatabaseDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getDatabaseDir(this.peer!.ptr)
        return retval
    }
    private setDatabaseDir_serialize(databaseDir: string): void {
        ArkUIGeneratedNativeModule._Context_setDatabaseDir(this.peer!.ptr, databaseDir)
    }
    private getPreferencesDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getPreferencesDir(this.peer!.ptr)
        return retval
    }
    private setPreferencesDir_serialize(preferencesDir: string): void {
        ArkUIGeneratedNativeModule._Context_setPreferencesDir(this.peer!.ptr, preferencesDir)
    }
    private getBundleCodeDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getBundleCodeDir(this.peer!.ptr)
        return retval
    }
    private setBundleCodeDir_serialize(bundleCodeDir: string): void {
        ArkUIGeneratedNativeModule._Context_setBundleCodeDir(this.peer!.ptr, bundleCodeDir)
    }
    private getDistributedFilesDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getDistributedFilesDir(this.peer!.ptr)
        return retval
    }
    private setDistributedFilesDir_serialize(distributedFilesDir: string): void {
        ArkUIGeneratedNativeModule._Context_setDistributedFilesDir(this.peer!.ptr, distributedFilesDir)
    }
    private getResourceDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getResourceDir(this.peer!.ptr)
        return retval
    }
    private setResourceDir_serialize(resourceDir: string): void {
        ArkUIGeneratedNativeModule._Context_setResourceDir(this.peer!.ptr, resourceDir)
    }
    private getCloudFileDir_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._Context_getCloudFileDir(this.peer!.ptr)
        return retval
    }
    private setCloudFileDir_serialize(cloudFileDir: string): void {
        ArkUIGeneratedNativeModule._Context_setCloudFileDir(this.peer!.ptr, cloudFileDir)
    }
}
