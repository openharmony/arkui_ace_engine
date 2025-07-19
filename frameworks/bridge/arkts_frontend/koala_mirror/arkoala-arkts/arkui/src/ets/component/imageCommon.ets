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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    private getImageAnalyzerSupportTypes_serialize(): Array<ImageAnalyzerType> {
        const retval  = ArkUIGeneratedNativeModule._ImageAnalyzerController_getImageAnalyzerSupportTypes(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = TypeChecker.ImageAnalyzerType_FromNumeric(retvalDeserializer.readInt32())
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
    aiController?: ImageAnalyzerController;
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
        const value_types  = value.types
        let value_types_type : int32 = RuntimeType.UNDEFINED
        value_types_type = runtimeType(value_types)
        valueSerializer.writeInt8((value_types_type).toChar())
        if ((value_types_type) != (RuntimeType.UNDEFINED)) {
            const value_types_value  = value_types!
            valueSerializer.writeInt32((value_types_value.length).toInt())
            for (let value_types_value_counter_i = 0; value_types_value_counter_i < value_types_value.length; value_types_value_counter_i++) {
                const value_types_value_element : ImageAnalyzerType = value_types_value[value_types_value_counter_i]
                valueSerializer.writeInt32(TypeChecker.ImageAnalyzerType_ToNumeric(value_types_value_element))
            }
        }
        const value_aiController  = value.aiController
        let value_aiController_type : int32 = RuntimeType.UNDEFINED
        value_aiController_type = runtimeType(value_aiController)
        valueSerializer.writeInt8((value_aiController_type).toChar())
        if ((value_aiController_type) != (RuntimeType.UNDEFINED)) {
            const value_aiController_value  = value_aiController!
            ImageAnalyzerController_serializer.write(valueSerializer, value_aiController_value)
        }
    }
    public static read(buffer: DeserializerBase): ImageAIOptions {
        let valueDeserializer : DeserializerBase = buffer
        const types_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let types_buf : Array<ImageAnalyzerType> | undefined
        if ((types_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const types_buf__length : int32 = valueDeserializer.readInt32()
            let types_buf_ : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(types_buf__length)
            for (let types_buf__i = 0; types_buf__i < types_buf__length; types_buf__i++) {
                types_buf_[types_buf__i] = TypeChecker.ImageAnalyzerType_FromNumeric(valueDeserializer.readInt32())
            }
            types_buf = types_buf_
        }
        const types_result : Array<ImageAnalyzerType> | undefined = types_buf
        const aiController_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let aiController_buf : ImageAnalyzerController | undefined
        if ((aiController_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            aiController_buf = (ImageAnalyzerController_serializer.read(valueDeserializer) as ImageAnalyzerController)
        }
        const aiController_result : ImageAnalyzerController | undefined = aiController_buf
        let value : ImageAIOptions = ({types: types_result, aiController: aiController_result} as ImageAIOptions)
        return value
    }
}
export class ImageAnalyzerConfig_serializer {
    public static write(buffer: SerializerBase, value: ImageAnalyzerConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_types  = value.types
        valueSerializer.writeInt32((value_types.length).toInt())
        for (let value_types_counter_i = 0; value_types_counter_i < value_types.length; value_types_counter_i++) {
            const value_types_element : ImageAnalyzerType = value_types[value_types_counter_i]
            valueSerializer.writeInt32(TypeChecker.ImageAnalyzerType_ToNumeric(value_types_element))
        }
    }
    public static read(buffer: DeserializerBase): ImageAnalyzerConfig {
        let valueDeserializer : DeserializerBase = buffer
        const types_buf_length : int32 = valueDeserializer.readInt32()
        let types_buf : Array<ImageAnalyzerType> = new Array<ImageAnalyzerType>(types_buf_length)
        for (let types_buf_i = 0; types_buf_i < types_buf_length; types_buf_i++) {
            types_buf[types_buf_i] = TypeChecker.ImageAnalyzerType_FromNumeric(valueDeserializer.readInt32())
        }
        const types_result : Array<ImageAnalyzerType> = types_buf
        let value : ImageAnalyzerConfig = ({types: types_result} as ImageAnalyzerConfig)
        return value
    }
}
