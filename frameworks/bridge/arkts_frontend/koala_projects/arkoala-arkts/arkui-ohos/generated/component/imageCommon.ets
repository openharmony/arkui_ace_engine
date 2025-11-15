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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
export class ImageAnalyzerControllerInternal {
    public static fromPtr(ptr: KPointer): ImageAnalyzerController {
        return new ImageAnalyzerController(ptr)
    }
}
export class ImageAnalyzerController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ImageAnalyzerController.getFinalizer())
    }
    constructor() {
        this(ImageAnalyzerController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ImageAnalyzerController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageAnalyzerController_getFinalizer()
    }
    public getImageAnalyzerSupportTypes(): Array<ImageAnalyzerType> {
        return this.getImageAnalyzerSupportTypes_serialize()
    }
    getImageAnalyzerSupportTypes_serialize(): Array<ImageAnalyzerType> {
        const retval  = ArkUIGeneratedNativeModule._ImageAnalyzerController_getImageAnalyzerSupportTypes(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = ImageAnalyzerType.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult : Array<ImageAnalyzerType> = buffer
        return returnResult
    }
}
export enum ImageAnalyzerType {
    SUBJECT = 0,
    TEXT = 1,
    OBJECT_LOOKUP = 2
}
export interface ImageAnalyzerConfig {
    types: Array<ImageAnalyzerType>;
}
export interface ImageAIOptions {
    types?: Array<ImageAnalyzerType>;
    aiController?: ImageAnalyzerController | ESValue;
}
export class ImageAnalyzerController_serializer {
    public static write(buffer: SerializerBase, value: ImageAnalyzerController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ImageAnalyzerController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ImageAnalyzerControllerInternal.fromPtr(ptr)
    }
}
export class ImageAIOptions_serializer {
    public static write(buffer: SerializerBase, value: ImageAIOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTypes  = value.types
        if (valueHolderForTypes !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypesTmpValue  = valueHolderForTypes!
            valueSerializer.writeInt32((valueHolderForTypesTmpValue.length).toInt())
            for (let valueHolderForTypesTmpValueCounterI = 0; valueHolderForTypesTmpValueCounterI < valueHolderForTypesTmpValue.length; valueHolderForTypesTmpValueCounterI++) {
                const valueHolderForTypesTmpValueTmpElement : ImageAnalyzerType = valueHolderForTypesTmpValue[valueHolderForTypesTmpValueCounterI]
                valueSerializer.writeInt32(valueHolderForTypesTmpValueTmpElement.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAiController  = value.aiController
        if (valueHolderForAiController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAiControllerTmpValue  = valueHolderForAiController!
            if (valueHolderForAiControllerTmpValue instanceof ImageAnalyzerController) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAiControllerTmpValueForIdx0  = valueHolderForAiControllerTmpValue as ImageAnalyzerController
                ImageAnalyzerController_serializer.write(valueSerializer, valueHolderForAiControllerTmpValueForIdx0)
            } else if (valueHolderForAiControllerTmpValue instanceof object) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAiControllerTmpValueForIdx1  = valueHolderForAiControllerTmpValue as object
                valueSerializer.holdAndWriteObject(valueHolderForAiControllerTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageAIOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typesTmpBuf : Array<ImageAnalyzerType> | undefined = undefined
        if ((typesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const typesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let typesTmpBuf_ : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(typesTmpBuf_Length)
            for (let typesTmpBuf_BufCounterI = 0; typesTmpBuf_BufCounterI < typesTmpBuf_Length; typesTmpBuf_BufCounterI++) {
                typesTmpBuf_[typesTmpBuf_BufCounterI] = ImageAnalyzerType.fromValue(valueDeserializer.readInt32())
            }
            typesTmpBuf = typesTmpBuf_
        }
        const typesTmpResult : Array<ImageAnalyzerType> | undefined = typesTmpBuf
        const aiControllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let aiControllerTmpBuf : ImageAnalyzerController | ESValue | undefined = undefined
        if ((aiControllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const aiControllerTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let aiControllerTmpBuf_ : ImageAnalyzerController | ESValue | undefined
            if (aiControllerTmpBuf_UnionSelector == (0).toChar()) {
                aiControllerTmpBuf_ = (ImageAnalyzerController_serializer.read(valueDeserializer) as ImageAnalyzerController)
            } else if (aiControllerTmpBuf_UnionSelector == (1).toChar()) {
                aiControllerTmpBuf_ = (valueDeserializer.readObject() as ESValue)
            } else {
                throw new Error("One of the branches for aiControllerTmpBuf_ has to be chosen through deserialisation.")
            }
            aiControllerTmpBuf = (aiControllerTmpBuf_ as ImageAnalyzerController | ESValue)
        }
        const aiControllerTmpResult : ImageAnalyzerController | ESValue | undefined = aiControllerTmpBuf
        let value : ImageAIOptions = ({types: typesTmpResult, aiController: aiControllerTmpResult} as ImageAIOptions)
        return value
    }
}
export class ImageAnalyzerConfig_serializer {
    public static write(buffer: SerializerBase, value: ImageAnalyzerConfig): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTypes  = value.types
        valueSerializer.writeInt32((valueHolderForTypes.length).toInt())
        for (let valueHolderForTypesCounterI = 0; valueHolderForTypesCounterI < valueHolderForTypes.length; valueHolderForTypesCounterI++) {
            const valueHolderForTypesTmpElement : ImageAnalyzerType = valueHolderForTypes[valueHolderForTypesCounterI]
            valueSerializer.writeInt32(valueHolderForTypesTmpElement.valueOf())
        }
    }
    public static read(buffer: DeserializerBase): ImageAnalyzerConfig {
        let valueDeserializer : DeserializerBase = buffer
        const typesTmpBufLength : int32 = valueDeserializer.readInt32()
        let typesTmpBuf : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(typesTmpBufLength)
        for (let typesTmpBufBufCounterI = 0; typesTmpBufBufCounterI < typesTmpBufLength; typesTmpBufBufCounterI++) {
            typesTmpBuf[typesTmpBufBufCounterI] = ImageAnalyzerType.fromValue(valueDeserializer.readInt32())
        }
        const typesTmpResult : Array<ImageAnalyzerType> = typesTmpBuf
        let value : ImageAnalyzerConfig = ({types: typesTmpResult} as ImageAnalyzerConfig)
        return value
    }
}
