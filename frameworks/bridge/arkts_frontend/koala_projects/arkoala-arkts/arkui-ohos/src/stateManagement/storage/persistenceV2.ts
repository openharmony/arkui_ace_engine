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

import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { DecoratedVariableBase } from '../decoratorImpl/decoratorBase';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { IBindingSource, ITrackedDecoratorRef } from '../base/mutableStateMeta';
import { RenderIdType } from '../decorator';

import { StateMgmtTool } from '#stateMgmtTool';
import { uiUtils } from '../base/uiUtilsImpl';
import { IAniStorage, AniStorage, AreaMode } from './persistentStorage';
import contextConstant from '@ohos.app.ability.contextConstant';

export type StorageDefaultCreator<T> = () => T;

type StringOrUndefinedType = String | undefined
type FixedStringArrayType = FixedArray<StringOrUndefinedType>;

export type ToJSONType<T> = (value: T) => jsonx.JsonElement;
export type FromJSONType<T> = (element: jsonx.JsonElement) => T;

export function transferTypeName(typename: string): string {
    return typename.substring(typename.lastIndexOf('.') + 1);
}

export interface SerializableObject extends jsonx.JsonElementSerializable, jsonx.JsonElementDeserializable {}

export interface ConnectOptions<T extends object> {
    type: Type;
    key?: string;
    defaultCreator?: StorageDefaultCreator<T>;
    areaMode?: contextConstant.AreaMode;
    enableAutoSave?: boolean;
}

const Quota: string = 'quota';
const Serialization: string = 'serialization';
const Unknown: string = 'unknown';

type PersistenceErrorCallback = ((key: string, reason: string, message: string) => void) | undefined;

const enum MapType {
    NOT_IN_MAP = -1,
    MODULE_MAP = 0,
    GLOBAL_MAP = 1
}

interface IStorageKey {
    key: string;
}

interface IStorageAutoSave {
    autoSave: boolean;
}

export class PersistenceV2 {
    public static configureBackend(storage: IAniStorage): void {
        PersistenceV2Impl.instance().configureBackend(storage);
    }

    public static connect<T extends object>(
        ttype: Type,
        toJson: ToJSONType<T>,
        fromJson: FromJSONType<T>,
        defaultCreator?: StorageDefaultCreator<T>,
        enableAutoSave?: boolean
    ): T | undefined {
        return PersistenceV2Impl.instance().connect(ttype, transferTypeName(ttype.getName()), toJson, fromJson, defaultCreator, enableAutoSave);
    }

    public static connect<T extends object>(
        ttype: Type,
        key: string,
        toJson: ToJSONType<T>,
        fromJson: FromJSONType<T>,
        defaultCreator?: StorageDefaultCreator<T>,
        enableAutoSave?: boolean
    ): T | undefined {
        return PersistenceV2Impl.instance().connect(ttype, key, toJson, fromJson, defaultCreator, enableAutoSave);
    }

    public static connect<T extends SerializableObject>(
      ttype: Type,
      defaultCreator?: StorageDefaultCreator<T>,
      enableAutoSave?: boolean
    ): T | undefined {
      return PersistenceV2Impl.instance().connect<T>(ttype, transferTypeName(ttype.getName()), undefined, undefined, defaultCreator, enableAutoSave);
    }

    public static connect<T extends SerializableObject>(
      ttype: Type,
      key: string,
      defaultCreator?: StorageDefaultCreator<T>,
      enableAutoSave?: boolean
    ): T | undefined {
      return PersistenceV2Impl.instance().connect<T>(ttype, key, undefined, undefined, defaultCreator, enableAutoSave);
    }

    public static globalConnect<T extends object>(
        connectOptions: ConnectOptions<T>,
        toJson: ToJSONType<T>,
        fromJson: FromJSONType<T>): T | undefined {
        return PersistenceV2Impl.instance().globalConnect(connectOptions, toJson, fromJson);
    }

    public static globalConnect<T extends SerializableObject>(
        connectOptions: ConnectOptions<T>): T | undefined {
        return PersistenceV2Impl.instance().globalConnect(connectOptions, undefined, undefined);
    }

    public static keys(): Array<string> {
        return PersistenceV2Impl.instance().keys();
    }

    public static notifyOnError(callback: PersistenceErrorCallback | undefined): void {
        PersistenceV2Impl.instance().notifyOnError(callback);
    }

    public static remove(keyOrType: string | Type): void {
        PersistenceV2Impl.instance().remove(keyOrType);
        return;
    }

    public static save(keyOrType: string | Type): void {
        PersistenceV2Impl.instance().save(keyOrType);
        return;
    }
}

class StoragePropertyV2<T extends object>
    extends DecoratedVariableBase
    implements ITrackedDecoratorRef, IStorageKey, IStorageAutoSave {
    private backing_: IBackingValue<T> | T | undefined;
    public id: RenderIdType; // We keep ID only for sorting purposes, but sorting not really needed
    public weakThis: WeakRef<ITrackedDecoratorRef>;
    public reverseBindings: Set<WeakRef<IBindingSource>>;
    public key: string;
    public observable: boolean;
    public autoSave: boolean;

    constructor(key: string, initValue: T, autoSave: boolean) {
        super("", undefined, "");
        this.id = ++PersistenceV2Impl.nextPersistId_;
        this.weakThis = new WeakRef<ITrackedDecoratorRef>(this as ITrackedDecoratorRef);
        this.reverseBindings = new Set<WeakRef<IBindingSource>>;
        ObserveSingleton.instance.addToTrackedRegistry(this, this.reverseBindings);
        if (StateMgmtTool.isIObservedObject(initValue) || this.isObservedInterface(initValue)) {
            this.backing_ = FactoryInternal.mkDecoratorValue<T>("StoragePropertyV2", initValue);
            this.observable = true;
        } else {
            this.backing_ = initValue;
            this.observable = false;
        }
        this.key = key;
        this.autoSave = autoSave;
    }

    private isObservedInterface<T>(value: T): boolean {
        if (typeof value !== "object") {
            return false;
        }
        try {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            return handler !== undefined || handler !== null;
        } catch (err) {
            // Not proxied
        }
        return false;
    }

    constructor(key: string, autoSave: boolean) {
        super("", undefined, "");
        this.id = ++PersistenceV2Impl.nextPersistId_;
        this.weakThis = new WeakRef<ITrackedDecoratorRef>(this as ITrackedDecoratorRef);
        this.reverseBindings = new Set<WeakRef<IBindingSource>>;
        ObserveSingleton.instance.addToTrackedRegistry(this, this.reverseBindings);
        this.backing_ = undefined;
        this.key = key;
        this.autoSave = autoSave;
        this.observable = false;
    }

    clearReverseBindings(): void {
        this.reverseBindings.forEach((dep: WeakRef<IBindingSource>) => {
            let ref = dep!.deref()
            if (ref) {
                ref.clearBindingRefs(this.weakThis)
            } else {
                this.reverseBindings.delete(dep)
            }
        })
    }

    public get(): T | undefined {
        if (this.backing_ === undefined) {
            return undefined
        }
        if (this.observable) {
            return (this.backing_! as IBackingValue<T>).get(this.shouldAddRef());
        }
        return this.backing_ as T;
    }

    public set(newValue: T): void {
        if (this.backing_ !== undefined) {
            if (this.observable) {
                (this.backing_! as IBackingValue<T>).set(newValue);
            }
            else {
                this.backing_ = newValue;
            }
            return;
        }

        if (StateMgmtTool.isIObservedObject(newValue) || this.isObservedInterface(newValue)) {
            this.backing_ = FactoryInternal.mkDecoratorValue<T>("StoragePropertyV2", newValue);
            this.observable = true;
        } else {
            this.backing_ = newValue;
            this.observable = false;
        }
    }
}

export class StorageHelper {
    public static readonly INVALID_DEFAULT_VALUE_CREATOR: string = 'The default creator should be function when first connect';
    public static readonly DELETE_NOT_EXIST_KEY: string = 'The key to be deleted does not exist';
    public static readonly INVALID_TYPE: string = 'The type should have function constructor signature when use storage';
    public static readonly EMPTY_STRING_KEY: string = 'Cannot use empty string as the key';
    public static readonly INVALID_LENGTH_KEY: string = 'Cannot use the key! The length of key should be 2 to 255';
    public static readonly INVALID_CHARACTER_KEY: string = 'Cannot use the key! The value of key can only consist of letters, digits and underscores';
    public static readonly NULL_OR_UNDEFINED_KEY: string = `The parameter cannot be null or undefined`;
    public static readonly ERROR_NOT_IN_THE_STORE: string = `The parameter is not in the store`;
    public static readonly INVALID_DEFAULT_VALUE_PRIMITIVE: string = 'Can not store primitive data types';

    public static getKeyOrTypeNameWithChecks<T>(keyOrType: string | Type): string | undefined {
        if (typeof keyOrType === 'string') {
            const key = keyOrType as string;
            return StorageHelper.isKeyValid(key) ? key : undefined;
        }
        return transferTypeName((keyOrType as Type).getName());
    }

    public static checkTypeByType<T>(key: string, newType: Type, oldType: Type): void {
        if (!newType.assignableFrom(oldType)) {
            throw new Error(`The ** type mismatches when use the key '${key}' in storage`);
        }
    }

    public static checkTypeByName(key: string, ttype: Type, typeName: string): void {
        if (transferTypeName(ttype.getName()) !== typeName) {
            throw new Error(`The type mismatches when use the key '${key}' in storage, '${transferTypeName(ttype.getName())}' vs. '${typeName}'`);
        }
    }

    public static checkTypeByInstanceOf<T>(key: string, ttype: Type, obj: T): void {
        if (!ttype.assignableFrom(Type.of(obj))) {
            throw new Error(`The type mismatches when use the key '${key}' in storage`);
        }
    }

    public static isKeyValid(key: string): boolean {
        // The key string is empty
        if (key === '') {
            StateMgmtConsole.log(StorageHelper.EMPTY_STRING_KEY);
            return false;
        }

        const len: number = key.length;
        // The key string length should shorter than 1024, error
        if (len >= 1024) {
            StateMgmtConsole.log(StorageHelper.INVALID_LENGTH_KEY);
            return false;
        }

        // Warnings only
        if (len < 2 || len > 255) {
            StateMgmtConsole.log(StorageHelper.INVALID_LENGTH_KEY);
        }
        if (!(new RegExp("^[0-9a-zA-Z_]+$")).test(key)) {
            StateMgmtConsole.log(StorageHelper.INVALID_CHARACTER_KEY);
        }

        return true;
    }
}

export class PersistenceV2Impl {
    private static readonly NOT_SUPPORTED_TYPES_: Array<Type> =
        [
            Type.from<Array<object>>(),
            Type.from<Set<object>>(),
            Type.from<Map<object, object>>(),
            Type.from<WeakSet<object>>(),
            Type.from<WeakMap<object, object>>(),
            Type.from<Date>(),
            Type.from<Boolean>(),
            Type.from<Number>(),
            Type.from<String>(),
            Type.from<BigInt>(),
            Type.from<RegExp>(),
            Type.from<Function>(),
            Type.from<Promise<void>>(),
            Type.from<ArrayBuffer>()
        ];

    public static readonly MIN_PERSISTENCE_ID = 0x30000000;
    public static nextPersistId_ = PersistenceV2Impl.MIN_PERSISTENCE_ID;

    private storageBackend_: IAniStorage | undefined = undefined;
    private static instance_: PersistenceV2Impl | undefined = undefined;

    private static readonly NOT_SUPPORT_TYPE_MESSAGE_: string = 'Type is not supported! Can only use the class object in Persistence';
    private static readonly KEYS_DUPLICATE_: string = 'ERROR, Duplicate key used when connect';
    private static readonly NOT_SUPPORT_AREAMODE_MESSAGE_: string = 'AreaMode Value Error! value range can only in EL1-EL5';
    private static readonly KEYS_ARR_: string = '___keys_arr';
    private static readonly MAX_DATA_LENGTH_: number = 8000;

    private entriesMap_: Map<string, DecoratedVariableBase>;
    private globalEntriesMap_: Map<string, DecoratedVariableBase>;
    private globalMapAreaMode_: Map<string, AreaMode>;
    private keysSet_: Set<string>;
    private globalKeysArr_: Array<Set<string>>;
    private propertyWriters_: Map<string, () => void>;
    private errorCB_: PersistenceErrorCallback = undefined;
    private typeMap_: Map<string, Type>;
    private observationInProgress_: boolean = false;
    public static backendUpdateCountForTesting: int = 0;

    constructor() {
        super();
        this.entriesMap_ = new Map<string, DecoratedVariableBase>;
        this.globalEntriesMap_ = new Map<string, DecoratedVariableBase>;
        this.globalMapAreaMode_ = new Map<string, AreaMode>();
        this.keysSet_ = new Set<string>();
        this.globalKeysArr_ = [new Set<string>(), new Set<string>(), new Set<string>(), new Set<string>(), new Set<string>()];
        this.typeMap_ = new Map<string, Type>();
        this.propertyWriters_ = new Map<string, () => void>();
        this.storageBackend_ = new AniStorage();
    }

    public static instance(): PersistenceV2Impl {
        if (PersistenceV2Impl.instance_ !== undefined) {
            return PersistenceV2Impl.instance_!;
        }
        PersistenceV2Impl.instance_ = new PersistenceV2Impl();
        return PersistenceV2Impl.instance_!;
    }

    // Test helper
    public static instanceReset() {
        PersistenceV2Impl.instance_ = undefined;
    }

    // Test helper
    public static instanceExists(): boolean {
        return PersistenceV2Impl.instance_ !== undefined;
    }

    public configureBackend(storage: IAniStorage): void {
        this.storageBackend_ = storage;
    }

    public connect<T extends object | SerializableObject>(
        ttype: Type,
        key: string,
        toJson: ToJSONType<T> | undefined,
        fromJson: FromJSONType<T> | undefined,
        defaultCreator?: StorageDefaultCreator<T>,
        enableAutoSave?: boolean
    ): T | undefined {
        if (this.storageBackend_ === undefined) {
            this.errorHelper(key, Unknown, `The storage is null`);
            return undefined;
        }

        this.checkTypeIsValidClassObject(ttype);

        if (ttype.isPrimitive()) {
            throw new Error(StorageHelper.INVALID_DEFAULT_VALUE_CREATOR);
        }

        if (!this.isPersistentKeyValid(key)) {
            return undefined;
        }

        // In memory
        if (this.globalEntriesMap_.has(key)) {
            throw new Error(PersistenceV2Impl.KEYS_DUPLICATE_);
        }

        if (this.entriesMap_.has(key)) {
            StorageHelper.checkTypeByType(key, ttype, this.typeMap_.get(key)!);
            const existingValue = this.entriesMap_.get(key) as StoragePropertyV2<T>;
            return existingValue.get();
        }

        const saveCheck: boolean = (enableAutoSave !== undefined ? enableAutoSave : true) as boolean;

        // Not in memory (not connected), but exists on the disk
        if (this.storageBackend_!.has(key)) {
            return this.readValueFromDisk<T>(key, ttype, toJson, fromJson, defaultCreator, saveCheck);
        }

        // Key is neither in the memory nor in the storage/disk
        // Create default value and check correctness
        const storageProperty = this.createDefaultValue<T>(key, ttype, saveCheck, defaultCreator);
        if (!storageProperty) {
            return undefined;
        }

        let observedValue = storageProperty!.get();
        this.connectNewValue<T>(key, storageProperty, ttype, toJson);
        return observedValue;
    }

    public globalConnect<T extends object>(
        connectOptions: ConnectOptions<T>,
        toJson: ToJSONType<T> | undefined,
        fromJson: FromJSONType<T> | undefined): T | undefined {
        return this.doGlobalConnect(connectOptions, toJson, fromJson);
    }

    private doGlobalConnect<T extends object>(connectOptions: ConnectOptions<T>,
        toJson: ToJSONType<T> | undefined, fromJson: FromJSONType<T> | undefined): T | undefined {

        this.checkTypeIsValidClassObject(connectOptions.type);

        const key = this.getPersistentKeyOrTypeNameWithChecks(connectOptions);
        if (!key) {
            return undefined;
        }

        if (this.storageBackend_ === undefined) {
            this.errorHelper(key, Unknown, `The storage is null`);
            return undefined;
        }

        // In memory, do duplicate key check
        if (this.entriesMap_.has(key)) {
            throw new Error(PersistenceV2Impl.KEYS_DUPLICATE_);
        }

        // In memory, return if globalEntriesMap_ exist
        if (this.globalEntriesMap_.has(key)) {
            StorageHelper.checkTypeByType(key, connectOptions.type, this.typeMap_.get(key)!);
            const existingValue = this.globalEntriesMap_.get(key) as StoragePropertyV2<T>;
            return existingValue!.get() as T;
        }

        const saveCheck: boolean = (connectOptions.enableAutoSave !== undefined ? connectOptions.enableAutoSave : true) as boolean;

        // Not in memory, but on disk
        const areaMode: AreaMode = this.getAreaMode(connectOptions.areaMode);
        this.globalMapAreaMode_.set(key, areaMode);
        if (this.storageBackend_!.has(key, areaMode)) {
            return this.readValueFromDisk<T>(key, connectOptions.type, toJson, fromJson, connectOptions.defaultCreator, saveCheck, areaMode);
        }

        // Neither in memory or in disk, create new entry
        let storageProperty = this.createDefaultValue<T>(key, connectOptions.type, saveCheck, connectOptions.defaultCreator);
        if (!storageProperty) {
            return undefined;
        }
        let observedValue = storageProperty!.get();

        if (!observedValue) {
            return undefined;
        }

        this.connectNewValue<T>(key, storageProperty, connectOptions.type, toJson, true, areaMode);
        return observedValue;
    }

    public keys(): Array<string> {
        const allKeys: Set<string> = new Set<string>();
        try {
            // add module path key
            if (!this.keysSet_.size) {
                this.keysSet_ = this.getKeysFromStorage();
            }
            for (const key of this.keysSet_) {
                allKeys.add(key);
            }
            // add global path key
            for (let i = 0; i < this.globalKeysArr_.length; i++) {
                if (!this.globalKeysArr_[i].size) {
                    this.globalKeysArr_[i] = this.getKeysFromStorage(i as AreaMode);
                }
                for (const key of this.globalKeysArr_[i]) {
                    allKeys.add(key);
                }
            }
        } catch (err) {
            if (this.errorCB_) {
                this.errorCB_!('', Unknown, `fail to get all persisted keys`);
                return [];
            }
            throw err;
        }
        return Array.from(allKeys);
    }

    public remove(keyOrType: string | Type): boolean {
        let key = StorageHelper.getKeyOrTypeNameWithChecks(keyOrType);
        if (!key) {
            return false;
        }
        this.disconnectValue(key);
        return true;
    }

    public save(keyOrType: string | Type): boolean {
        let key = StorageHelper.getKeyOrTypeNameWithChecks(keyOrType);
        if (!key) {
            return false;
        }

        let obj = this.globalEntriesMap_.has(key)
            ? this.globalEntriesMap_.get(key)
            : (this.entriesMap_.has(key) ? this.entriesMap_.get(key) : undefined);

        if (obj === undefined) {
            StateMgmtConsole.log(`Cannot save the key '${key}'! The key is disconnected`);
            return false;
        }
        let status = true;
        try {
            let writer = this.propertyWriters_.get(key);
            if (writer) {
                writer();
            }
        } catch (err) {
            this.errorHelper(key, Serialization, JSON.stringify(err));
            status = false;
        }
        return status;
    }

    public notifyOnError(callback: PersistenceErrorCallback): void {
        this.errorCB_ = callback;
    }

    public onChangeObserved(persistRefs: Set<WeakRef<ITrackedDecoratorRef>>): void {
        this.writeAllChangedToDisk(persistRefs);
    }

    private startObservation<T extends object>(property: StoragePropertyV2<T>) {
        if (!property.observable) {
            return;
        }
        ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingPersistentStorage
        ObserveSingleton.instance.renderingComponentRef = property;
        this.observationInProgress_ = true;
    }

    private stopObservation() {
        if (!this.observationInProgress_) {
            return;
        }
        ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponent;
        ObserveSingleton.instance.renderingComponentRef = undefined;
        this.observationInProgress_ = false;
    }

    private propertyWriter<T extends object>(key: string, toJson: ToJSONType<T> | undefined) {
        const keyType: MapType = this.getKeyMapType(key!);
        if (keyType === MapType.NOT_IN_MAP) {
            return;
        }

        const property =
            (keyType === MapType.GLOBAL_MAP ? this.globalEntriesMap_.get(key!)! : this.entriesMap_.get(key!))
            as StoragePropertyV2<T>;

        const ttype = this.typeMap_.get(key!);

        this.startObservation(property);
        const jsonElement = PersistenceV2Impl.toJsonWithType(toJson, property!.get() as T);
        let jsonString = JSON.stringifyJsonElement(jsonElement);
        this.stopObservation();

        if (this.isOverSizeLimit(jsonString)) {
            StateMgmtConsole.log(
                `Cannot store the key '${key}'! The length of data must be less than ${PersistenceV2Impl.MAX_DATA_LENGTH_}`);
            return;
        }
        const areaMode = (keyType === MapType.GLOBAL_MAP) ? this.globalMapAreaMode_.get(key!) : undefined;
        // Write to backend
        this.storageBackend_!.set(key!, jsonString, areaMode);
        PersistenceV2Impl.backendUpdateCountForTesting++;
    }

    private connectNewValue<T extends object>(
        key: string,
        newValue: StoragePropertyV2<T>,
        ttype: Type,
        toJson: ToJSONType<T> | undefined,
        writeFlag: boolean = true,
        areaMode?: AreaMode): void {
        this.propertyWriters_.set(
            key,
            () => { this.propertyWriter<T>(key, toJson) } as() => void
        );

        if (areaMode !== undefined) {
            this.globalEntriesMap_.set(key, newValue);
        } else {
            this.entriesMap_.set(key, newValue);
        }
        this.typeMap_.set(key, ttype);

        if (writeFlag) {
            this.storeKeyToPersistenceV2(key, areaMode);
            // Schedule writing to back storage
            ObserveSingleton.instance.addDirtyRef(newValue)
        }
    }

    private disconnectValue(key: string): void {
        const keyType: MapType = this.getKeyMapType(key);
        let areaMode: AreaMode | undefined;
        if (keyType === MapType.GLOBAL_MAP) {
            this.globalEntriesMap_.delete(key);
            areaMode = this.globalMapAreaMode_.get(key);
            this.globalMapAreaMode_.delete(key);
        } else if (keyType === MapType.MODULE_MAP) {
            this.entriesMap_.delete(key);
        }

        this.typeMap_.delete(key);
        this.propertyWriters_.delete(key);
        this.removeFromPersistenceV2(key, areaMode);
    }

    private checkTypeIsValidClassObject(ttype: Type) {
        PersistenceV2Impl.NOT_SUPPORTED_TYPES_.forEach((wrong_ttype) => {
            if (wrong_ttype.equals(ttype)) {
                throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
            }
        })
    }

    private getAreaMode(areaMode?: contextConstant.AreaMode): AreaMode {
        if (areaMode === undefined) {
            return AreaMode.EL2;
        }
        switch (areaMode) {
            case contextConstant.AreaMode.EL1:
                return AreaMode.EL1;
            case contextConstant.AreaMode.EL2:
                return AreaMode.EL2;
            case contextConstant.AreaMode.EL3:
                return AreaMode.EL3;
            case contextConstant.AreaMode.EL4:
                return AreaMode.EL4;
            case contextConstant.AreaMode.EL5:
                return AreaMode.EL5;
            default:
                throw new Error(PersistenceV2Impl.NOT_SUPPORT_AREAMODE_MESSAGE_);
        }
    }

    private getKeyMapType(key: string): MapType {
        if (this.globalEntriesMap_.has(key)) {
            return MapType.GLOBAL_MAP;
        }
        if (this.entriesMap_.has(key)) {
            return MapType.MODULE_MAP;
        }
        return MapType.NOT_IN_MAP;
    }

    private createDefaultValue<T extends object>(key: string, ttype: Type, autoSave: boolean,
        defaultCreator?: StorageDefaultCreator<T>): StoragePropertyV2<T> | undefined {
        if (!defaultCreator) {
            this.errorHelper(key, Unknown, `Can not create default value for '${key}'`);
            return undefined;
        }
        const value: T = defaultCreator!();
        StorageHelper.checkTypeByInstanceOf(key, ttype, value);
        if (PersistenceV2Impl.isNotAValidClassObject(value)) {
            throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
        }

        return new StoragePropertyV2<T>(key, uiUtils.autoProxyObject(value), autoSave);
    }

    private static getTargetClassName<T extends object>(value: T): string {
        try {
            let maybeTarget = StateMgmtTool.tryGetTarget(value);
            let target = maybeTarget ? maybeTarget as T : value;
            return transferTypeName(Type.of(target).getName());
        } catch (err) {
            // not proxied
        }
        return transferTypeName(Type.of(value).getName());
    }

    private static fromJsonWithType<T extends object | SerializableObject>(
        key: string,
        fromJson: FromJSONType<T> | undefined,
        record: jsonx.JsonElement,
        valueToUpdate: SerializableObject | undefined = undefined)
        : [string, T | undefined] {
        let recordArray = record.asArray();
        let typeString = recordArray[0].asString();
        let value : T | undefined = undefined;
        if (fromJson !== undefined) {
            value = fromJson(recordArray[1])
         } else if (valueToUpdate !== undefined){
            StorageHelper.checkTypeByName(key, Type.of(valueToUpdate), typeString);
            valueToUpdate!.fromJSON(recordArray[1]);
            value = valueToUpdate! as T;
         }
        return [typeString, value];
    }

    private static toJsonWithType<T extends object | SerializableObject>(toJson: ToJSONType<T> | undefined, obj: T): jsonx.JsonElement {
        let topArray = new Array<jsonx.JsonElement>();
        let classname = PersistenceV2Impl.getTargetClassName(obj);
        let el = jsonx.JsonElement.createString(classname);
        topArray.push(el);
        topArray.push(toJson !== undefined? toJson(obj) : (obj as SerializableObject).toJSON());
        let ret = jsonx.JsonElement.createArray(topArray);
        return ret;
    }

    private readValueFromDisk<T extends object>(
        key: string,
        ttype: Type,
        toJson: ToJSONType<T> | undefined,
        fromJson: FromJSONType<T> | undefined,
        defaultCreator: StorageDefaultCreator<T> | undefined,
        enableAutoSave: boolean,
        areaMode?: AreaMode): T | undefined {
        try {
            const jsonString: string = this.storageBackend_!.get(key, areaMode)!;
            if (!jsonString) {
                this.errorHelper(key, Serialization, StorageHelper.ERROR_NOT_IN_THE_STORE);
                return undefined;
            }
            let property: StoragePropertyV2<T> | undefined;
            let newObservedValue: T | undefined;
            const jsonElement = JSON.parseJsonElement(jsonString);
            if (fromJson !== undefined) {
                property = new StoragePropertyV2<T>(key, enableAutoSave);
                const newValueTuple = PersistenceV2Impl.fromJsonWithType(key, fromJson, jsonElement);
                const typeName = newValueTuple[0]
                const newValue = newValueTuple[1];
                if (newValue === undefined) {
                    throw new Error("unable to deserialize object for the key: " + key);
                }
                // Exception if type mismatch
                StorageHelper.checkTypeByName(key, ttype, typeName);
                StorageHelper.checkTypeByInstanceOf(key, ttype, newValue);
                newObservedValue = uiUtils.autoProxyObject(newValue!);
                property.set(newObservedValue);
            } else {
                property = this.createDefaultValue<T>(key, ttype, enableAutoSave, defaultCreator);
                if ((property === undefined) || (property!.get() === undefined)) {
                    throw new Error("unable to create default value the key: " + key);
                }
                const newValueTuple = PersistenceV2Impl.fromJsonWithType(key, undefined, jsonElement, property!.get() as SerializableObject);
                newObservedValue = property!.get();
            }

            // Collect dependencies
            this.startObservation(property);
            PersistenceV2Impl.toJsonWithType(toJson, newObservedValue!);
            this.stopObservation();

            // Adds to one of the maps, do not store key on disk
            this.connectNewValue<T>(key, property, ttype, toJson, false, areaMode);
            return newObservedValue;
        } catch (err) {
            this.stopObservation();
            this.errorHelper(key, Serialization, JSON.stringify(err));
        }
        return undefined;
    }

    private writeAllChangedToDisk(refs: Set<WeakRef<ITrackedDecoratorRef>>): void {
        refs.forEach((item) => {
            let property = item.deref();
            if (property) {
                const key = (property as IStorageKey).key;
                const autoSave = (property as IStorageAutoSave).autoSave;

                try {
                    if (this.propertyWriters_.has(key!) && autoSave) {
                        this.propertyWriters_.get(key!)!();
                    }
                } catch (err) {
                    if (this.errorCB_) {
                        this.errorCB_!(key!, Serialization, JSON.stringify(err));
                    }
                    StateMgmtConsole.log(`Exception writing for '${key}' key: ` + err);
                }
            }
        })
    }

    private isOverSizeLimit(json: string): boolean {
        return json.length >= PersistenceV2Impl.MAX_DATA_LENGTH_;
    }

    private static isNotAValidClassObject(value: object): boolean {
        const wrongType =
            Type.of(value).isPrimitive() ||
            Array.isArray(value) ||
            value instanceof Array ||
            value instanceof Set ||
            value instanceof Map ||
            value instanceof WeakSet ||
            value instanceof WeakMap ||
            value instanceof Date ||
            value instanceof Boolean ||
            value instanceof Number ||
            value instanceof String ||
            value instanceof BigInt ||
            value instanceof RegExp ||
            value instanceof Function ||
            value instanceof Promise ||
            value instanceof ArrayBuffer;
        return wrongType;
    }

    private storeKeyToPersistenceV2(key: string, areaMode?: AreaMode): void {
        try {
            if (areaMode !== undefined) {
                if (this.globalKeysArr_[areaMode].has(key)) {
                    return;
                }
                // Initializing the keys arr in memory
                if (!this.globalKeysArr_[areaMode].size) {
                    this.globalKeysArr_[areaMode] = this.getKeysFromStorage(areaMode);
                }
                this.globalKeysArr_[areaMode].add(key);
                // Updating the keys arr in disk
                this.storeKeysToStorage(this.globalKeysArr_[areaMode], areaMode);
            } else {
                if (this.keysSet_.has(key)) {
                    return;
                }

                // Initializing the keys arr in memory
                if (!this.keysSet_.size) {
                    this.keysSet_ = this.getKeysFromStorage();
                }
                this.keysSet_.add(key);
                // Updating the keys arr in disk
                this.storeKeysToStorage(this.keysSet_);
            }
        } catch (err) {
            this.errorHelper(key, Unknown, `fail to store the key '${key}'`);
        }
    }

    private removeForModulePath(key: string): void {
        this.storageBackend_!.delete(key);
        // The first call for module path
        if (!this.keysSet_.has(key)) {
            this.keysSet_ = this.getKeysFromStorage();
        }
        this.keysSet_.delete(key);
        this.storeKeysToStorage(this.keysSet_);
    }

    private removeFlagForGlobalPath(key: string): boolean {
        let removeFlag = false;
        // first call for global path
        for (let i = 0; i < this.globalKeysArr_.length; i++) {
            if (this.storageBackend_!.has(key, i as AreaMode)) {
                removeFlag = true;
                this.storageBackend_!.delete(key, i as AreaMode);
                this.globalKeysArr_[i] = this.getKeysFromStorage(i as AreaMode);
                this.globalKeysArr_[i].delete(key);
                this.storeKeysToStorage(this.globalKeysArr_[i], i as AreaMode);
            }
        }
        return removeFlag;
    }

    private removeFromPersistenceV2(key: string, areaMode?: AreaMode): void {
        try {
            // check for global path
            if (areaMode !== undefined) {
                this.storageBackend_!.delete(key, areaMode);
                this.globalKeysArr_[areaMode].delete(key);
                this.storeKeysToStorage(this.globalKeysArr_[areaMode], areaMode);
            } else {
                let removeFlag: boolean = false;
                // check for module path
                if (this.storageBackend_!.has(key)) {
                    removeFlag = true;
                    this.removeForModulePath(key);
                } else {
                    removeFlag = this.removeFlagForGlobalPath(key);
                }
                if (!removeFlag) {
                    StateMgmtConsole.warn(StorageHelper.DELETE_NOT_EXIST_KEY + `keys:${key}`);
                }
            }
        } catch (err) {
            StateMgmtConsole.log("removeFromPersistenceV2 fails to remove " + err);
            this.errorHelper(key, Unknown, `fail to remove the key '${key}'`);
        }
    }

    private getKeysFromStorage(areaMode?: AreaMode): Set<string> {
        if (areaMode !== undefined && !this.storageBackend_!.has(PersistenceV2Impl.KEYS_ARR_, areaMode!)) {
            return this.globalKeysArr_[areaMode];
        }
        else if (areaMode === undefined && !this.storageBackend_!.has(PersistenceV2Impl.KEYS_ARR_)) {
            return this.keysSet_;
        }

        const jsonKeysArr: string | undefined = this.storageBackend_!.get(PersistenceV2Impl.KEYS_ARR_, areaMode);

        let returnSet = new Set<string>();
        if (jsonKeysArr === undefined) {
            return returnSet;
        }

        const arrayForTypeDetection: FixedArray<StringOrUndefinedType> = new StringOrUndefinedType[2];
        let keysArray = JSON.parse<FixedStringArrayType>(jsonKeysArr, Type.of(arrayForTypeDetection));
        if (keysArray === undefined) {
            return returnSet;
        }
        for (let idx = 0; idx < keysArray!.length; idx++) {
            returnSet.add(keysArray![idx] as string);
        }
        return returnSet;
    }

    private storeKeysToStorage(keysSet: Set<string>, areaMode?: AreaMode | undefined): void {
        let keysArray: FixedStringArrayType = new StringOrUndefinedType[keysSet.size];
        let idx: int = 0;
        keysSet.forEach((key) => { keysArray[idx++] = key; })
        this.storageBackend_!.set(PersistenceV2Impl.KEYS_ARR_, JSON.stringify(keysArray), areaMode);
    }

    private isPersistentKeyValid(key: string): string | undefined {
        if (key === PersistenceV2Impl.KEYS_ARR_) {
            this.errorHelper(key, Quota, `The key '${key}' cannot be used`);
            return undefined;
        }
        return StorageHelper.isKeyValid(key!) ? key : undefined;
    }

    private getPersistentKeyOrTypeNameWithChecks<T extends object>(options: ConnectOptions<T>): string | undefined {
        let key = options.key;
        if (!options.key) {
            StateMgmtConsole.log(StorageHelper.NULL_OR_UNDEFINED_KEY + ', try to use the type name as key');
            key = transferTypeName(options.type.getName());
        }

        if (key === undefined) {
            throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
        }
        return this.isPersistentKeyValid(key);
    }

    private errorHelper(key: string, reason: string, message: string) {
        if (this.errorCB_ !== undefined) {
            this.errorCB_!(key, reason, message);
            return;
        }
        if (!key) {
            key = 'unknown';
        }
        throw new Error(`For '${key}' key: ` + message);
    }
}
