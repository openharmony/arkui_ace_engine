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

import { FileSelectorMode } from "./ArkWebInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class FileSelectorParamInternal {
    public static fromPtr(ptr: KPointer): FileSelectorParam {
        const obj : FileSelectorParam = new FileSelectorParam()
        obj.peer = new Finalizable(ptr, FileSelectorParam.getFinalizer())
        return obj
    }
}
export class FileSelectorParam implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_fileselectorparam(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FileSelectorParam.ctor_fileselectorparam()
        this.peer = new Finalizable(ctorPtr, FileSelectorParam.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FileSelectorParam_getFinalizer()
    }
    public getTitle(): string {
        return this.getTitle_serialize()
    }
    public getMode(): FileSelectorMode {
        return this.getMode_serialize()
    }
    public getAcceptType(): Array<string> {
        return this.getAcceptType_serialize()
    }
    public isCapture(): boolean {
        return this.isCapture_serialize()
    }
    private getTitle_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getTitle(this.peer!.ptr)
        return retval
    }
    private getMode_serialize(): FileSelectorMode {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getMode(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getAcceptType_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptType(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private isCapture_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_isCapture(this.peer!.ptr)
        return retval
    }
}
