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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
export class ComponentContentInternal {
    public static fromPtr(ptr: KPointer): ComponentContent {
        return new ComponentContent(ptr)
    }
}
export class ComponentContent implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ComponentContent.getFinalizer())
    }
    constructor() {
        this(ComponentContent.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ComponentContent_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(args)
        ArkUIGeneratedNativeModule._ComponentContent_update(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private reuse_serialize(param?: Object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8((param_type).toChar())
        if ((param_type) != (RuntimeType.UNDEFINED)) {
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
export class ComponentContent_serializer {
    public static write(buffer: SerializerBase, value: ComponentContent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ComponentContent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ComponentContentInternal.fromPtr(ptr)
    }
}
