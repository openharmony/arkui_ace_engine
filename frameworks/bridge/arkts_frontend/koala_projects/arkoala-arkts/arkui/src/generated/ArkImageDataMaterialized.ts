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

import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ImageDataInternal {
    public static fromPtr(ptr: KPointer): ImageData {
        const obj : ImageData = new ImageData(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ImageData.getFinalizer())
        return obj
    }
}
export class ImageData implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get data(): NativeBuffer {
        throw new Error("Not implemented")
    }
    get height(): number {
        return this.getHeight()
    }
    get width(): number {
        return this.getWidth()
    }
    static ctor_imagedata(width: number, height: number, data?: NativeBuffer): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let data_type : int32 = RuntimeType.UNDEFINED
        data_type = runtimeType(data)
        thisSerializer.writeInt8(data_type as int32)
        if ((RuntimeType.UNDEFINED) != (data_type)) {
            const data_value  = data!
            thisSerializer.writeBuffer(data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._ImageData_ctor(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(width?: number, height?: number, data?: NativeBuffer) {
        if (((width) !== (undefined)) || ((height) !== (undefined)) || ((data) !== (undefined)))
        {
            const ctorPtr : KPointer = ImageData.ctor_imagedata((width)!, (height)!, (data)!)
            this.peer = new Finalizable(ctorPtr, ImageData.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageData_getFinalizer()
    }
    private getData(): NativeBuffer {
        return this.getData_serialize()
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private getData_serialize(): NativeBuffer {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getData(this.peer!.ptr)
        return new Deserializer(retval, retval.length).readBuffer()
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getWidth(this.peer!.ptr)
        return retval
    }
}
