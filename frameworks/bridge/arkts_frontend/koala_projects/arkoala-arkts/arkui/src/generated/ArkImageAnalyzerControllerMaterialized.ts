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

import { ImageAnalyzerType } from "./ArkImageCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ImageAnalyzerControllerInternal {
    public static fromPtr(ptr: KPointer): ImageAnalyzerController {
        const obj : ImageAnalyzerController = new ImageAnalyzerController()
        obj.peer = new Finalizable(ptr, ImageAnalyzerController.getFinalizer())
        return obj
    }
}
export class ImageAnalyzerController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_imageanalyzercontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ImageAnalyzerController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ImageAnalyzerController.ctor_imageanalyzercontroller()
        this.peer = new Finalizable(ctorPtr, ImageAnalyzerController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageAnalyzerController_getFinalizer()
    }
    public getImageAnalyzerSupportTypes(): Array<ImageAnalyzerType> {
        return this.getImageAnalyzerSupportTypes_serialize()
    }
    private getImageAnalyzerSupportTypes_serialize(): Array<ImageAnalyzerType> {
        const retval  = ArkUIGeneratedNativeModule._ImageAnalyzerController_getImageAnalyzerSupportTypes(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readInt32() as ImageAnalyzerType)
        }
        const returnResult : Array<ImageAnalyzerType> = buffer
        return returnResult
    }
}
