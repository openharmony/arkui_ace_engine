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
import { default as uiEffect } from "@ohos.graphics.uiEffect"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class uiEffect_Filter_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.Filter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUiEffectFilterPtr(value))
    }
    public static read(buffer: DeserializerBase): uiEffect.Filter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUiEffectFilterPtr(ptr)
    }
}
export class uiEffect_VisualEffect_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.VisualEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUiEffectVisualEffectPtr(value))
    }
    public static read(buffer: DeserializerBase): uiEffect.VisualEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUiEffectVisualEffectPtr(ptr)
    }
}
export class uiEffect_BrightnessBlender_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.BrightnessBlender): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUiEffectBrightnessBlenderPtr(value))
    }
    public static read(buffer: DeserializerBase): uiEffect.BrightnessBlender {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUiEffectBrightnessBlenderPtr(ptr)
    }
}
