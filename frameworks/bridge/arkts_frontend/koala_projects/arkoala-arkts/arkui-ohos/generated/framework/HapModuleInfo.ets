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
import { DataItem, Dependency, HapModuleInfo, PreloadItem, RouterItem } from "bundleManager.HapModuleInfo"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class DataItem_serializer {
    public static write(buffer: SerializerBase, value: DataItem): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDataItemPtr(value))
    }
    public static read(buffer: DeserializerBase): DataItem {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDataItemPtr(ptr)
    }
}
export class Dependency_serializer {
    public static write(buffer: SerializerBase, value: Dependency): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDependencyPtr(value))
    }
    public static read(buffer: DeserializerBase): Dependency {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDependencyPtr(ptr)
    }
}
export class HapModuleInfo_serializer {
    public static write(buffer: SerializerBase, value: HapModuleInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toHapModuleInfoPtr(value))
    }
    public static read(buffer: DeserializerBase): HapModuleInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromHapModuleInfoPtr(ptr)
    }
}
export class PreloadItem_serializer {
    public static write(buffer: SerializerBase, value: PreloadItem): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toPreloadItemPtr(value))
    }
    public static read(buffer: DeserializerBase): PreloadItem {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromPreloadItemPtr(ptr)
    }
}
export class RouterItem_serializer {
    public static write(buffer: SerializerBase, value: RouterItem): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toRouterItemPtr(value))
    }
    public static read(buffer: DeserializerBase): RouterItem {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromRouterItemPtr(ptr)
    }
}
