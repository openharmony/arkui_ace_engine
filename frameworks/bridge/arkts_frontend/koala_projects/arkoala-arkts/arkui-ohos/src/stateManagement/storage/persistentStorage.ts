/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { IStorageProperty } from './storageBase';
import { AbstractProperty, OnChangeType } from './storageProperty';
import { AppStorage } from './appStorage';
import { ArkUIAniModule } from 'arkui.ani';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

export const enum AreaMode {
    EL1 = 0,
    EL2 = 1,
    EL3 = 2,
    EL4 = 3,
    EL5 = 4,
}

export interface IAniStorage {
    get(key: string, areaMode?: AreaMode): string | undefined;
    set(key: string, val: string, areaMode?: AreaMode): void;
    has(key: string, areaMode?: AreaMode): boolean;
    clear(): void;
    delete(key: string, areaMode?: AreaMode): void;
}

// class JsonElement{}
/**
 * Define toJson type function.
 *
 * @typedef { function } ToJSONType<T>
 * @param { T } value  toJson value
 * @returns { JsonElement } Json stringify element object
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20
 */
export type ToJSONType<T> = (value: T) => jsonx.JsonElement;

/**
 * Define fromJson type function.
 *
 * @typedef { function } FromJSONType<T>
 * @param { JsonElement } element  json element
 * @returns { T } deserialization result
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20
 */
export type FromJSONType<T> = (element: jsonx.JsonElement) => T;

interface PersistPropsOptions<T> {
    key: string;
    defaultValue: T;
    toJson?: ToJSONType<T>;
    fromJson?: FromJSONType<T>;
}

class TypedMap {
    private key2Type_ = new Map<string, Type>();
    private key2Value_ = new Map<string, IStorageProperty>();

    public add(key: string, ttype: Type, sp: IStorageProperty): boolean {
        const typeOpt = this.key2Type_.get(key);
        if (typeOpt !== undefined) {
            if (!typeOpt!.equals(ttype)) {
                return false;
            }
        }
        this.key2Type_.set(key, ttype);
        this.key2Value_.set(key, sp);
        return true;
    }

    public get(key: string, expectedTtype: Type): IStorageProperty | undefined {
        const typeOpt = this.key2Type_.get(key);
        if (typeOpt === undefined || !typeOpt!.equals(expectedTtype)) {
            return undefined;
        }
        return this.key2Value_.get(key);
    }

    public delete(key: string): boolean {
        const r1 = this.key2Type_.delete(key);
        const ref = this.key2Value_.get(key);
        if (ref !== undefined) {
            const regId = (ref as AbstractProperty<Any>).getMyTriggerFromSourceWatchId();
            AppStorage.__getStoragePropUnsafe(key)!.__unregister(regId);
        }
        const r2 = this.key2Value_.delete(key);
        return r1 && r2;
    }

    public keys(): Array<string> {
        return Array.from(this.key2Type_.keys());
    }
}

export class AniStorage implements IAniStorage {
    clear(): void { // No AreaMode parameter
        ArkUIAniModule._PersistentStorage_Clear();
    }
    delete(key: string, areaMode?: AreaMode): void {
        ArkUIAniModule._PersistentStorage_Delete(key, areaModeToInt(areaMode));
    }
    get(key: string, areaMode?: AreaMode): string | undefined {
        return ArkUIAniModule._PersistentStorage_Get(key, areaModeToInt(areaMode));
    }
    has(key: string, areaMode?: AreaMode): boolean {
        return ArkUIAniModule._PersistentStorage_Has(key, areaModeToInt(areaMode));
    }
    set(key: string, val: string, areaMode?: AreaMode): void {
        ArkUIAniModule._PersistentStorage_Set(key, val, areaModeToInt(areaMode));
    }
}

function areaModeToInt(areaMode?: AreaMode): Int {
    if (areaMode === undefined) {
        return -1;
    }
    switch(areaMode) {
        case AreaMode.EL1:
            return 0;
        case AreaMode.EL2:
            return 1;
        case AreaMode.EL3:
            return 2;
        case AreaMode.EL4:
            return 3;
        case AreaMode.EL5:
            return 4;
        default:
            // never getting here
            return -1;
    }
}

/**
 * Defines the PersistentStorage interface.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20
 */
class PersistentStorage {
    private static instance_: PersistentStorage | undefined = undefined;
    private readonly storage_: IAniStorage = new AniStorage();
    private map_: TypedMap = new TypedMap();
    private simpleTypeSet: Set<Type> = new Set<Type>([
        Type.from<int>(),
        Type.from<long>(),
        Type.from<float>(),
        Type.from<double>(),
        Type.from<number>(),
        Type.from<string>(),
        Type.from<boolean>(),
    ]);

    private static getOrCreate(): PersistentStorage {
        if (PersistentStorage.instance_) {
            // already initialized
            return PersistentStorage.instance_!;
        }

        PersistentStorage.instance_ = new PersistentStorage();
        return PersistentStorage.instance_!;
    }

    /**
     * Add property 'key' to AppStorage properties whose current value will be
     * persistent.
     * If AppStorage does not include this property it will be added and initializes
     * with given value
     *
     * @param { string } key - property name
     * @param { T } defaultValue - If AppStorage does not include this property it will be initialized with this value
     * @param { Type } ttype - type of this property.
     * @param { ToJSONType<T> } [toJson] - serialization function
     * @param { FromJSONType<T> } [fromJson] - deserialization function
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public static persistProp<T>(
        key: string,
        defaultValue: T,
        toJson?: ToJSONType<T>,
        fromJson?: FromJSONType<T>
    ): boolean {
        return PersistentStorage.getOrCreate().persistPropInternal(key, defaultValue, toJson, fromJson);
    }

    /**
     * Add property 'key' to AppStorage properties whose current value will be
     * persistent for a loop.
     * If AppStorage does not include this property it will be added and initializes
     * with given value
     *
     * @param { PersistPropsOptions } properties - see PersistPropsOptions
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public static persistProps(properties: PersistPropsOptions<Any>[]): void {
        properties.forEach((prop) => {
            PersistentStorage.persistProp(prop.key, prop.defaultValue, prop.toJson, prop.fromJson);
        });
    }

    private isSimpleOrEnumType(ttype: Type, isEnum: boolean): boolean {
        return this.simpleTypeSet.has(ttype) || isEnum;
    }

    private persistPropInternal<T>(
        key: string,
        defaultValue: T,
        toJson?: ToJSONType<T>,
        fromJson?: FromJSONType<T>
    ): boolean {
        const ttype = Type.of(defaultValue);
        let isSimpleType = false;
        if (!toJson && !fromJson && this.isSimpleOrEnumType(ttype, defaultValue instanceof BaseEnum)) {
            isSimpleType = true;
        }
        try {
            if (!isSimpleType && (!toJson || !fromJson)) {
                StateMgmtConsole.log(
                    `Object Types for key ${key} requires toJson and fromJson functions to be defined`
                );
                return false;
            }
            const apOpt = PersistentStorage.getOrCreate().map_.get(key, ttype);
            if (apOpt !== undefined) {
                // persisted property already
                StateMgmtConsole.log(`persistProp key ${key} persistedAlready`);
                return false;
            }

            // case 1: property exists in storage already and start to persist it
            if (AppStorage.has(key)) {
                const success = PersistentStorage.getOrCreate().__startToPersistStorageProperty<T>(key, ttype, isSimpleType, toJson);
                if (!success) {
                    StateMgmtConsole.log(`Failed to start persistence for existing key ${key}`);
                }
                return success;
            }

            // case 2: Read from disk, set in AppStorage and start persistence
            if (
                PersistentStorage.getOrCreate().__readFromDiskSetAndPersist<T>(
                    key,
                    ttype,
                    isSimpleType,
                    isSimpleType ? undefined : fromJson,
                    isSimpleType ? undefined : toJson
                )
            ) {
                return true;
            }

            // case 3: Create new property with default value and start persistence
            const success = PersistentStorage.getOrCreate().__createNewAndPersist(
                key,
                ttype,
                defaultValue,
                isSimpleType,
                isSimpleType ? undefined : toJson
            );
            if (!success) {
                StateMgmtConsole.log(`Failed to create and persist key ${key} with default value`);
            }
            return success;
        } catch (error) {
            StateMgmtConsole.log(`Unexpected error in persistProp for key ${key}: ${error}`);
            return false;
        }
    }

    /**
     * Reverse of @see persistProp
     *
     * @param { string } key - no longer persist the property named key
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public static deleteProp(key: string): void {
        PersistentStorage.getOrCreate().deletePropInternal(key);
    }

    private deletePropInternal(key: string): void {
        // Remove from AniStorage
        PersistentStorage.getOrCreate().storage_.delete(key);
        // Remove from TypedMap and need to unregister from AppStorage
        PersistentStorage.getOrCreate().map_.delete(key);
    }

    // Note: persistProps can not be supported because each
    // property has different T
    // framework can not recover T from Array<PersistPropsOptions<Any>>
    // must use separate persistProp calls instead

    /**
     * Inform persisted AppStorage property names
     *
     * @returns { Array<string> } array of AppStorage keys
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public static keys(): Array<string> {
        return PersistentStorage.getOrCreate().keysInternal();
    }

    private keysInternal(): Array<string> {
        return PersistentStorage.getOrCreate().map_.keys();
    }

    // case 1: neither on disk nor in storage
    // create with default value and start to persist
    private __createNewAndPersist<T>(key: string, ttype: Type, defaultValue: T, isSimpleType: boolean, toJson?: ToJSONType<T>): boolean {
        if (!AppStorage.setOrCreate<T>(key, defaultValue)) {
            StateMgmtConsole.log(`__createNewAndPersist return false`);
            return false;
        }
        return PersistentStorage.getOrCreate().__startToPersistStorageProperty<T>(key, ttype, isSimpleType, toJson);
    }

    // case 2: not in storage
    // try to read from disk (return false if not found)
    // create in storage with read value and start to persist
    private __readFromDiskSetAndPersist<T>(
        key: string,
        ttype: Type,
        isSimpleType: boolean,
        fromJson?: FromJSONType<T>,
        toJson?: ToJSONType<T>
    ): boolean {
        // Step 1: Read JSON string from storage
        const jsonString = PersistentStorage.getOrCreate().storage_.get(key);
        if (jsonString === undefined) {
            return false; // Not found on disk
        }

        try {
            if (isSimpleType && fromJson === undefined) {
                // Step 2: simple type just parse from disk
                const value = JSON.parse<T>(jsonString, ttype);

                // Step 3: Store the value in AppStorage
                AppStorage.setOrCreate(key, value);

                // Step 4: persist the property
                return PersistentStorage.getOrCreate().__startToPersistStorageProperty<T>(key, ttype, isSimpleType, toJson); // returns true on success
            } else {
                // Step 2: Parse JSON string into JsonElement
                const jsonElement = JSON.parseJsonElement(jsonString);

                // Step 3: Convert JsonElement to type T using fromJson
                if (fromJson === undefined) {
                    return false; // Cannot deserialize without fromJson
                }
                const value: T = fromJson(jsonElement);

                // Step 4: Store the value in AppStorage
                AppStorage.setOrCreate(key, value);

                // Step 5: persist the property
                return PersistentStorage.getOrCreate().__startToPersistStorageProperty<T>(key, ttype, isSimpleType, toJson); // returns true on success
            }
        } catch (error) {
            if (error instanceof jsonx.JsonError) {
                StateMgmtConsole.log(`JSON parsing error: ${error.message}`);
            } else {
                StateMgmtConsole.log(`Unexpected error: ${error}`);
            }
            return false; // Failure due to parsing or deserialization error
        }
    }

    // case 3 - used by case 1 and 2: property exists in storage (caller needs to verify)
    // start to persist it
    private __startToPersistStorageProperty<T>(key: string, ttype: Type, isSimpleType: boolean, toJson?: ToJSONType<T>): boolean {
        const ref = AppStorage.ref<T>(key) as AbstractProperty<T> | undefined; // Explicitly specify T
        if (ref === undefined) {
            StateMgmtConsole.log(`Failed to get AppStorage ref for key ${key}`);
            return false;
        }
        PersistentStorage.getOrCreate().map_.add(key, ttype, ref);
        const writeToDiskOnChange: OnChangeType<T> = (key1: string, newValue: T) => {
            if (key != key1) {
                StateMgmtConsole.log('persistProp callback will non-matching key. Ignoring. Internal error.');
                return;
            }
            try {
                if (isSimpleType && toJson === undefined) {
                    const jsonString = JSON.stringify(newValue);
                    PersistentStorage.getOrCreate().storage_.set(key, jsonString);
                } else {
                    if (!toJson) {
                        StateMgmtConsole.log(`Object Types for key ${key} requires toJson functions to be defined`);
                    }
                    const jsonElement = toJson!(newValue);
                    // convert JsonElement to jsonString
                    const jsonString = JSON.stringifyJsonElement(jsonElement);
                    PersistentStorage.getOrCreate().storage_.set(key, jsonString);
                }
            } catch (error) {
                if (error instanceof jsonx.JsonError) {
                    StateMgmtConsole.log(`JSON serialization error for key ${key}: ${error.message}`);
                } else {
                    StateMgmtConsole.log(`Unexpected error persisting key ${key}: ${error}`);
                }
            }
        };
        ref.onChange(writeToDiskOnChange);
        PersistentStorage.getOrCreate().map_.add(key, ttype, ref);
        return true;
    }
}
