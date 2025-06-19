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

import { Callback_PopInfo_Void } from "./SyntheticDeclarations"
import { PopInfo } from "./ArkNavigationInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class NavPathInfoInternal {
    public static fromPtr(ptr: KPointer): NavPathInfo {
        const obj : NavPathInfo = new NavPathInfo(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, NavPathInfo.getFinalizer())
        return obj
    }
}
export class NavPathInfo implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get name(): string {
        return this.getName()
    }
    set name(name: string) {
        this.setName(name)
    }
    get param(): object | undefined {
        throw new Error("Not implemented")
    }
    set param(param: object | undefined) {
        const param_NonNull  = (param as object)
        this.setParam(param_NonNull)
    }
    get onPop(): ((parameter: PopInfo) => void) | undefined {
        throw new Error("Not implemented")
    }
    set onPop(onPop: ((parameter: PopInfo) => void) | undefined) {
        const onPop_NonNull  = (onPop as ((parameter: PopInfo) => void))
        this.setOnPop(onPop_NonNull)
    }
    get isEntry(): boolean | undefined {
        return this.getIsEntry()
    }
    set isEntry(isEntry: boolean | undefined) {
        const isEntry_NonNull  = (isEntry as boolean)
        this.setIsEntry(isEntry_NonNull)
    }
    static ctor_navpathinfo(name: string, param: object, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Any", param)
        let onPop_type : int32 = RuntimeType.UNDEFINED
        onPop_type = runtimeType(onPop)
        thisSerializer.writeInt8(onPop_type as int32)
        if ((RuntimeType.UNDEFINED) != (onPop_type)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        let isEntry_type : int32 = RuntimeType.UNDEFINED
        isEntry_type = runtimeType(isEntry)
        thisSerializer.writeInt8(isEntry_type as int32)
        if ((RuntimeType.UNDEFINED) != (isEntry_type)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_ctor(name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(name?: string, param?: object, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean) {
        if (((name) !== (undefined)) || ((param) !== (undefined)) || ((onPop) !== (undefined)) || ((isEntry) !== (undefined)))
        {
            const ctorPtr : KPointer = NavPathInfo.ctor_navpathinfo((name)!, (param)!, (onPop)!, (isEntry)!)
            this.peer = new Finalizable(ctorPtr, NavPathInfo.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathInfo_getFinalizer()
    }
    private getName(): string {
        return this.getName_serialize()
    }
    private setName(name: string): void {
        const name_casted = name as (string)
        this.setName_serialize(name_casted)
        return
    }
    private getParam(): object {
        return this.getParam_serialize()
    }
    private setParam(param: object): void {
        const param_casted = param as (object)
        this.setParam_serialize(param_casted)
        return
    }
    private getOnPop(): ((parameter: PopInfo) => void) {
        return this.getOnPop_serialize()
    }
    private setOnPop(onPop: ((parameter: PopInfo) => void)): void {
        const onPop_casted = onPop as (((parameter: PopInfo) => void))
        this.setOnPop_serialize(onPop_casted)
        return
    }
    private getIsEntry(): boolean {
        return this.getIsEntry_serialize()
    }
    private setIsEntry(isEntry: boolean): void {
        const isEntry_casted = isEntry as (boolean)
        this.setIsEntry_serialize(isEntry_casted)
        return
    }
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setName(this.peer!.ptr, name)
    }
    private getParam_serialize(): object {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getParam(this.peer!.ptr)
        return retval
    }
    private setParam_serialize(param: object): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Any", param)
        ArkUIGeneratedNativeModule._NavPathInfo_setParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnPop_serialize(): ((parameter: PopInfo) => void) {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getOnPop(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnPop_serialize(onPop: ((parameter: PopInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onPop)
        ArkUIGeneratedNativeModule._NavPathInfo_setOnPop(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEntry_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        return retval
    }
    private setIsEntry_serialize(isEntry: boolean): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, isEntry ? 1 : 0)
    }
}
