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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
export class EnvironmentBackend {
    public static isAccessibilityEnabled(): boolean {
        return EnvironmentBackend.isAccessibilityEnabled_serialize()
    }
    public static getColorMode(): int32 {
        return EnvironmentBackend.getColorMode_serialize()
    }
    public static getFontScale(): float {
        return EnvironmentBackend.getFontScale_serialize()
    }
    public static getFontWeightScale(): float {
        return EnvironmentBackend.getFontWeightScale_serialize()
    }
    public static getLayoutDirection(): string {
        return EnvironmentBackend.getLayoutDirection_serialize()
    }
    public static getLanguageCode(): string {
        return EnvironmentBackend.getLanguageCode_serialize()
    }
    private static isAccessibilityEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_isAccessibilityEnabled()
        return retval
    }
    private static getColorMode_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_getColorMode()
        return retval
    }
    private static getFontScale_serialize(): float {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_getFontScale()
        return retval
    }
    private static getFontWeightScale_serialize(): float {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_getFontWeightScale()
        return retval
    }
    private static getLayoutDirection_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_getLayoutDirection()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static getLanguageCode_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._EnvironmentBackend_getLanguageCode()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
}
export class PersistentStorageBackend {
    public static get(key: string): string | undefined {
        const key_casted = key as (string)
        return PersistentStorageBackend.get_serialize(key_casted)
    }
    public static has(key: string): boolean {
        const key_casted = key as (string)
        return PersistentStorageBackend.has_serialize(key_casted)
    }
    public static remove(key: string): void {
        const key_casted = key as (string)
        PersistentStorageBackend.remove_serialize(key_casted)
        return
    }
    public static set(key: string, value: string): void {
        const key_casted = key as (string)
        const value_casted = value as (string)
        PersistentStorageBackend.set_serialize(key_casted, value_casted)
        return
    }
    public static clear(): void {
        PersistentStorageBackend.clear_serialize()
        return
    }
    private static get_serialize(key: string): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._PersistentStorageBackend_get(key)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : string | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private static has_serialize(key: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._PersistentStorageBackend_has(key)
        return retval
    }
    private static remove_serialize(key: string): void {
        ArkUIGeneratedNativeModule._PersistentStorageBackend_remove(key)
    }
    private static set_serialize(key: string, value: string): void {
        ArkUIGeneratedNativeModule._PersistentStorageBackend_set(key, value)
    }
    private static clear_serialize(): void {
        ArkUIGeneratedNativeModule._PersistentStorageBackend_clear()
    }
}
