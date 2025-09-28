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
import { MultiAppMode, ModuleMetadata, ApplicationInfo } from "bundleManager.ApplicationInfo"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class MultiAppMode_serializer {
    public static write(buffer: SerializerBase, value: MultiAppMode): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toMultiAppModePtr(value))
    }
    public static read(buffer: DeserializerBase): MultiAppMode {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromMultiAppModePtr(ptr)
    }
}
export class ModuleMetadata_serializer {
    public static write(buffer: SerializerBase, value: ModuleMetadata): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toModuleMetadataPtr(value))
    }
    public static read(buffer: DeserializerBase): ModuleMetadata {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromModuleMetadataPtr(ptr)
    }
}
export class ApplicationInfo_serializer {
    public static write(buffer: SerializerBase, value: ApplicationInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toApplicationInfoPtr(value))
    }
    public static read(buffer: DeserializerBase): ApplicationInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromApplicationInfoPtr(ptr)
    }
}
