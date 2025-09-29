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

import { extractors } from "#handwritten"
import { default as drawing } from "@ohos.graphics.drawing"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class drawing_Canvas_serializer {
    public static write(buffer: SerializerBase, value: drawing.Canvas): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingCanvasPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Canvas {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingCanvasPtr(ptr)
    }
}
export class drawing_ColorFilter_serializer {
    public static write(buffer: SerializerBase, value: drawing.ColorFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingColorFilterPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ColorFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingColorFilterPtr(ptr)
    }
}
export class drawing_Lattice_serializer {
    public static write(buffer: SerializerBase, value: drawing.Lattice): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingLatticePtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Lattice {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingLatticePtr(ptr)
    }
}
