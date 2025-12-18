/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

const enum PersistError {
  Quota = 'quota',
  Serialization = 'serialization',
  Unknown = 'unknown'
};

type PersistErrorType = PersistError.Quota | PersistError.Serialization | PersistError.Unknown;
type PersistErrorCallback = ((key: string, reason: PersistErrorType, message: string) => void) | undefined;
type StorageDefaultCreator<T> = () => T;

interface TypeConstructorWithArgs<T> {
  new(...args: any): T;
}

type CollectionType<S> =
  | Array<S>
  | Map<string | number, S>
  | Set<S>
  | SendableArray<S>
  | SendableMap<string | number, S>
  | SendableSet<S>

interface ConnectOptions<T extends object> {
  // (Mandatory) Specified type.
  type: TypeConstructorWithArgs<T>;
  // (Optional) Input key. If no key is specified, the name of the type is used as the key.
  key?: string;
  // Default constructor. You are advised to set this parameter.
  defaultCreator?: StorageDefaultCreator<T>;
  // (Optional) Encryption parameter.
  areaMode?: number;
}

interface ConnectOptionsCollections<T extends CollectionType<S>, S extends object> extends ConnectOptions<T> {
  // Default constructor. You are advised to set this parameter.
  defaultCreator: StorageDefaultCreator<T>;
  // Default constructor for collection items. You are advised to set this parameter whenever using collection of application defined class (S) .
  defaultSubCreator: StorageDefaultCreator<S>;
}

const enum AreaMode {
  EL1 = 0,
  EL2 = 1,
  EL3 = 2,
  EL4 = 3,
  EL5 = 4
}

const enum MapType {
  NOT_IN_MAP = -1,
  MODULE_MAP = 0,
  GLOBAL_MAP = 1
}

class StorageHelper {
  protected static readonly INVALID_DEFAULT_VALUE: string = 'The default creator should be function when first connect';
  protected static readonly DELETE_NOT_EXIST_KEY: string = 'The key to be deleted does not exist';
  protected static readonly INVALID_TYPE: string = 'The type should have function constructor signature when use storage';
  protected static readonly EMPTY_STRING_KEY: string = 'Cannot use empty string as the key';
  protected static readonly INVALID_LENGTH_KEY: string = 'Cannot use the key! The length of key should be 2 to 255';
  protected static readonly INVALID_CHARACTER_KEY: string = 'Cannot use the key! The value of key can only consist of letters, digits and underscores';
  protected static readonly NULL_OR_UNDEFINED_KEY: string = `The parameter cannot be null or undefined`;

  // sotre old type name to check the type matches or not
  protected oldTypeValues_: Map<string, string>;

  constructor() {
    this.oldTypeValues_ = new Map<string, string>();
  }

  protected getConnectedKey<T>(
    type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>
  ): string | undefined {
    if (keyOrDefaultCreator === null || keyOrDefaultCreator === undefined) {
      stateMgmtConsole.applicationWarn(StorageHelper.NULL_OR_UNDEFINED_KEY + ', try to use the type name as key');
    }

    if (typeof keyOrDefaultCreator === 'string') {
      return keyOrDefaultCreator;
    }

    return this.getTypeName(type);
  }

  protected getKeyOrTypeName<T>(keyOrType: string | TypeConstructorWithArgs<T>): string | undefined {
    if (typeof keyOrType === 'function') {
      keyOrType = this.getTypeName(keyOrType);
    }
    return keyOrType;
  }

  protected throwIfTypeNameMismatch<T>(type: TypeConstructorWithArgs<T>, oldType?: string, key?: string): void {
    if (this.getTypeName(type) !== oldType) {
      throw new Error(`The type mismatches when use the key '${key}' in storage`);
    }
  }

  protected throwIfNotInstanceOf<T>(value: T, type: TypeConstructorWithArgs<T>, key: string): void {
    if (typeof type !== 'function') {
      throw new Error(StorageHelper.INVALID_TYPE);
    }

    if (!(value instanceof type)) {
      throw new Error(`The type mismatches when use the key '${key}' in storage`);
    }
  }

  protected getTypeName<T>(type: TypeConstructorWithArgs<T>): string | undefined {
    if (typeof type !== 'function') {
      throw new Error(StorageHelper.INVALID_TYPE);
    }

    let name: string | undefined = type.name;
    while (name === undefined) {
      type = Object.getPrototypeOf(type);
      if (!type) {
        break;
      }
      name = type.name;
    }
    return name;
  }

  protected isKeyValid(key: string | null | undefined): boolean {
    if (typeof key !== 'string') {
      throw new Error(StorageHelper.INVALID_TYPE);
    }

    // The key string is empty
    if (key === '') {
      stateMgmtConsole.applicationError(StorageHelper.EMPTY_STRING_KEY);
      return false;
    }

    const len: number = key.length;
    // The key string length should shorter than 1024
    if (len >= 1024) {
      stateMgmtConsole.applicationError(StorageHelper.INVALID_LENGTH_KEY);
      return false;
    }

    if (len < 2 || len > 255) {
      stateMgmtConsole.applicationWarn(StorageHelper.INVALID_LENGTH_KEY);
    }

    if (!/^[0-9a-zA-Z_]+$/.test(key)) {
      stateMgmtConsole.applicationWarn(StorageHelper.INVALID_CHARACTER_KEY);
    }

    return true;
  }
}

class AppStorageV2Impl extends StorageHelper {
  private static instance_: AppStorageV2Impl = undefined;

  private memorizedValues_: Map<string, any>;

  constructor() {
    super();
    this.memorizedValues_ = new Map<string, any>();
  }

  public static instance(): AppStorageV2Impl {
    if (AppStorageV2Impl.instance_) {
      return AppStorageV2Impl.instance_;
    }
    AppStorageV2Impl.instance_ = new AppStorageV2Impl();
    return AppStorageV2Impl.instance_;
  }

  public connect<T extends object>(type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultCreator?: StorageDefaultCreator<T>
  ): T | undefined {
    const key = this.getConnectedKey(type, keyOrDefaultCreator);

    if (!this.isKeyValid(key)) {
      return undefined;
    }

    if (typeof keyOrDefaultCreator === 'function') {
      defaultCreator = keyOrDefaultCreator;
    }

    if (!this.memorizedValues_.has(key)) {
      if (typeof defaultCreator !== 'function') {
        throw new Error(AppStorageV2Impl.INVALID_DEFAULT_VALUE);
      }

      const defaultValue: T = defaultCreator();

      this.throwIfNotInstanceOf(defaultValue, type, key);

      this.memorizedValues_.set(key, defaultValue);
      this.oldTypeValues_.set(key, this.getTypeName(type));
      return defaultValue;
    }

    this.throwIfTypeNameMismatch(type, this.oldTypeValues_.get(key), key);

    const existedValue: T = this.memorizedValues_.get(key);
    return existedValue;
  }

  public remove<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    if (keyOrType === null || keyOrType === undefined) {
      stateMgmtConsole.applicationWarn(AppStorageV2Impl.NULL_OR_UNDEFINED_KEY);
      return;
    }

    const key: string = this.getKeyOrTypeName(keyOrType);

    if (!this.isKeyValid(key)) {
      return;
    }

    this.removeFromMemory(key);
  }

  public getMemoryKeys(): Array<string> {
    return Array.from(this.memorizedValues_.keys());
  }

  protected removeFromMemory(key: string): void {
    const isDeleted: boolean = this.memorizedValues_.delete(key);

    if (!isDeleted) {
      stateMgmtConsole.applicationWarn(AppStorageV2Impl.DELETE_NOT_EXIST_KEY);
    } else {
      this.oldTypeValues_.delete(key);
    }
  }

  public hasKey(key: string): boolean {
    return this.memorizedValues_.has(key);
  }

  public getValue(key: string): object {
      const obj = this.memorizedValues_.get(key);
      return obj;
  }

  public removeByInterop<T>(keyOrType: string | TypeConstructorWithArgs<T>): boolean {
    if (keyOrType === null || keyOrType === undefined) {
      stateMgmtConsole.applicationWarn(AppStorageV2Impl.NULL_OR_UNDEFINED_KEY);
      return false;
    }

    const key: string = this.getKeyOrTypeName(keyOrType);
    if (!this.isKeyValid(key)) {
      return false;
    }

    const isDeleted: boolean = this.memorizedValues_.delete(key);
    if (!isDeleted) {
      stateMgmtConsole.applicationWarn(AppStorageV2Impl.DELETE_NOT_EXIST_KEY);
      return false;
    } else {
      this.oldTypeValues_.delete(key);
      return true
    }
  }
}

class PersistenceV2Impl extends StorageHelper {
  public static readonly MIN_PERSISTENCE_ID = 0x1020000000000;
  public static nextPersistId_ = PersistenceV2Impl.MIN_PERSISTENCE_ID;

  protected static readonly NOT_SUPPORT_TYPE_MESSAGE_: string = 'Not support! Can only use the class object in Persistence';
  protected static readonly NOT_SUPPORT_AREAMODE_MESSAGE_: string = 'AreaMode Value Error! value range can only in EL1-EL5';
  protected static readonly KEYS_DUPLICATE_: string = 'ERROR, Duplicate key used when connect';
  protected static readonly KEYS_ARR_: string = '___keys_arr';
  // not supported by globalConnect() and connect()
  protected static readonly NOT_SUPPORT_TYPES_: Array<any> =
    [WeakSet, WeakMap, Boolean, Number, String, Symbol, BigInt, RegExp, Function, Promise, ArrayBuffer];
  protected static storage_: IStorage;
  protected static instance_: PersistenceV2Impl = undefined;

  // the map is used to store the persisted value in memory, can reuse when re-connect if the key exists
  protected map_: Map<string, any>;
  protected globalMap_: Map<string, any>;
  protected globalMapAreaMode_: Map<string, number>;
  protected keysArr_: Set<string>;
  protected globalKeysArr_: Array<Set<string>>;
  protected cb_: PersistErrorCallback = undefined;
  protected idToKey_: Map<number, string>;

  constructor() {
    super();
    this.map_ = new Proxy(new Map<string, any>(), new SetMapProxyHandler());
    this.globalMap_ = new Proxy(new Map<string, any>(), new SetMapProxyHandler());
    this.globalMapAreaMode_ = new Map<string, number>();
    this.keysArr_ = new Set<string>();
    this.globalKeysArr_ = [new Set(), new Set(), new Set(), new Set(), new Set()];
    this.idToKey_ = new Map<number, string>();
  }

  public static instance(): PersistenceV2Impl {
    if (PersistenceV2Impl.instance_) {
      return PersistenceV2Impl.instance_;
    }
    PersistenceV2Impl.instance_ = new PersistenceV2Impl();
    return PersistenceV2Impl.instance_;
  }

  public static configureBackend(storage: IStorage): void {
    PersistenceV2Impl.storage_ = storage;
  }

  public connect<T extends object>(
    type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultCreator?: StorageDefaultCreator<T>
  ): T | undefined;
  public connect<T extends CollectionType<S>, S extends object>(
    type: TypeConstructorWithArgs<T>,
    key: string,
    defaultCreator: StorageDefaultCreator<T>,
    defaultSubCreator: StorageDefaultCreator<S>
  ): T | undefined;
  public connect<T extends CollectionType<S>, S extends object>(
    type: TypeConstructorWithArgs<T>,
    defaultCreator: StorageDefaultCreator<T>,
    defaultSubCreator: StorageDefaultCreator<S>
  ): T | undefined;

  public connect<T extends object, S extends object>(
    type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultORSubCreator?: StorageDefaultCreator<T> | StorageDefaultCreator<S>,
    defaultSubCreator?: StorageDefaultCreator<S>
  ): T | undefined {
    this.throwIfTypeIsNotSupported(type);

    const key = this.getRightKey(type, keyOrDefaultCreator);
    if (!this.isKeyValid(key)) {
      return undefined;
    }

    if (typeof keyOrDefaultCreator === 'function') {
      [defaultORSubCreator, defaultSubCreator] = [keyOrDefaultCreator, defaultORSubCreator as StorageDefaultCreator<S>];
    }

    // In memory
    if (this.globalMap_.has(key)) {
      throw new Error(PersistenceV2Impl.KEYS_DUPLICATE_);
    }

    if (this.map_.has(key)) {
      const existedValue: T = this.map_.get(key);
      this.throwIfTypeNameMismatch(type, this.oldTypeValues_.get(key), key);
      return existedValue;
    }

    let observedValue: T | undefined = this.getConnectDefaultValue(
      key, type, defaultORSubCreator as StorageDefaultCreator<T>
    );
    if (!observedValue) {
      return undefined;
    }

    const id: number = ++PersistenceV2Impl.nextPersistId_;
    this.idToKey_.set(id, key);

    // Not in memory, but in disk
    if (PersistenceV2Impl.storage_.has(key)) {
      let [value, error] = this.getValueFromDisk(key, id, observedValue, type, defaultSubCreator);
      if (!error) {
          // No error, return valid  object
          return value;
      } else {
          // Default object partially restored, create new clean default object
          this.disconnectValue(key);
          observedValue = this.getConnectDefaultValue(key, type, defaultORSubCreator as StorageDefaultCreator<T>);
      }
    }

    // Neither in memory or in disk
    return this.setValueToDisk(key, id, observedValue, type);
  }

  public globalConnect<T extends object>(
    connectOptions : ConnectOptions<T>) : T | undefined;
  public globalConnect<T extends CollectionType<S>, S extends object>(
    connectOptions : ConnectOptionsCollections<T, S>) : T | undefined;

  public globalConnect<T extends object, S extends object>(
    connectOptions : ConnectOptions<T> | ConnectOptionsCollections<T extends CollectionType<S> ? T : never, S>
  ) : T | undefined {
    const type = connectOptions.type as TypeConstructorWithArgs<any>;
    this.throwIfTypeIsNotSupported(type);

    const key: string | undefined = this.getRightGlobalKey(type, connectOptions.key);
    if (!this.isKeyValid(key)) {
      return undefined;
    }

    // In memory, do duplicate key check
    if (this.map_.has(key)) {
      throw new Error(PersistenceV2Impl.KEYS_DUPLICATE_);
    }
    // In memory, return if globalMap_ exist
    if (this.globalMap_.has(key)) {
      const existedValue: T = this.globalMap_.get(key);
      this.throwIfTypeNameMismatch(type, this.oldTypeValues_.get(key), key);
      return existedValue;
    }

    let observedValue: T | undefined =
      this.getConnectDefaultValue(key, type, connectOptions.defaultCreator);

    if (!observedValue) {
      return undefined;
    }

    const id: number = ++PersistenceV2Impl.nextPersistId_;
    this.idToKey_.set(id, key);

    // Not in memory, but in disk
    const areaMode: number = this.getAreaMode(connectOptions.areaMode);
    this.globalMapAreaMode_.set(key, areaMode);
    if (PersistenceV2Impl.storage_.has(key, areaMode)) {
      let defaultSubCreator;
      if ('defaultSubCreator' in connectOptions) {
          defaultSubCreator = (connectOptions as ConnectOptionsCollections<CollectionType<S>, S>).defaultSubCreator;
      } else {
          defaultSubCreator = undefined;
      }
      let [value, error] = this.getValueFromDisk(
        key, id, observedValue,
        type,
        defaultSubCreator,
        areaMode
      );
      if (!error) {
          // No error, return valid  object
          return value;
      } else {
          // Create new clean default object
          this.disconnectValue(key);
          observedValue = this.getConnectDefaultValue(key, type, connectOptions.defaultCreator);
      }
    }

    // Neither in memory or in disk
    return this.setValueToDisk(key, id, observedValue, type, areaMode);
  }

  public keys(): Array<string> {
    const allKeys: Set<string> = new Set<string>();
    try {
      // add module path key
      if (!this.keysArr_.size) {
        this.keysArr_ = this.getKeysArrFromStorage();
      }
      for (const key of this.keysArr_) {
        allKeys.add(key);
      }
      // add global path key
      for (let i = 0; i < this.globalKeysArr_.length; i++) {
        if (!this.globalKeysArr_[i].size) {
          this.globalKeysArr_[i] = this.getKeysArrFromStorage(i);
        }
        for (const key of this.globalKeysArr_[i]) {
          allKeys.add(key);
        }
      }
    } catch (err) {
      if (this.cb_ && typeof this.cb_ === 'function') {
        this.cb_('', PersistError.Unknown, `fail to get all persisted keys`);
        return;
      }
      throw new Error(err);
    }

    return Array.from(allKeys);
  }

  public remove<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    if (keyOrType === null || keyOrType === undefined) {
      stateMgmtConsole.applicationWarn(PersistenceV2Impl.NULL_OR_UNDEFINED_KEY);
      return;
    }

    if (typeof keyOrType !== 'string')
      this.throwIfTypeIsNotSupported(keyOrType);

    const key: string = this.getKeyOrTypeName(keyOrType);

    if (!this.isKeyValid(key)) {
      return;
    }

    this.disconnectValue(key);
  }

  public save<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    if (keyOrType === null || keyOrType === undefined) {
      stateMgmtConsole.applicationWarn(PersistenceV2Impl.NULL_OR_UNDEFINED_KEY);
      return;
    }

    if (typeof keyOrType !== 'string')
      this.throwIfTypeIsNotSupported(keyOrType);

    const key: string = this.getKeyOrTypeName(keyOrType);

    if (!this.isKeyValid(key)) {
      return;
    }

    if (this.globalMap_.has(key)) {
      // find in global path
      const areaMode = this.globalMapAreaMode_.get(key);
      try {
        const data = this.globalMap_.get(key);
        const stringified = DataCoder.stringify(data);
        PersistenceV2Impl.storage_.set(key, stringified, areaMode);
      } catch (err) {
        this.errorHelper(key, PersistError.Serialization, err);
      }
    } else if (this.map_.has(key)) {
      // find in module path
      try {
        const data = this.map_.get(key);
        const stringified = DataCoder.stringify(data);
        PersistenceV2Impl.storage_.set(key, stringified);
      } catch (err) {
        this.errorHelper(key, PersistError.Serialization, err);
      }
    } else {
      stateMgmtConsole.applicationWarn(`Cannot save the key '${key}'! The key is disconnected`);
    }
  }

  public notifyOnError(cb: PersistErrorCallback): void {
    this.cb_ = cb;
  }

  public onChangeObserved(persistKeys: Array<number>): void {
    this.writeAllChangedToFile(persistKeys);
  }

  protected connectNewValue(key: string, newValue: any, typeName: string, areaMode?: number | undefined): void {
    if (typeof areaMode === 'number') {
      this.globalMap_.set(key, newValue);
    } else {
      this.map_.set(key, newValue);
    }
    this.oldTypeValues_.set(key, typeName);

    this.storeKeyToPersistenceV2(key, areaMode);
  }

  protected disconnectValue(key: string): void {
    const keyType: MapType = this.getKeyMapType(key);
    let areaMode: number | undefined = undefined;
    if (keyType === MapType.GLOBAL_MAP) {
      this.globalMap_.delete(key);
      areaMode = this.globalMapAreaMode_.get(key);
      this.globalMapAreaMode_.delete(key);
    } else if (keyType === MapType.MODULE_MAP) {
      this.map_.delete(key);
    }

    this.oldTypeValues_.delete(key);
    this.removeFromPersistenceV2(key, areaMode);
  }

  protected throwIfTypeIsNotSupported<T>(type: TypeConstructorWithArgs<T>) {
    if (typeof type !== 'function') {
      throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
    }

    if (PersistenceV2Impl.NOT_SUPPORT_TYPES_.includes(type as any)) {
      throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
    }
  }

  protected throwIfNotSupported(value: object) {
    const classes = PersistenceV2Impl.NOT_SUPPORT_TYPES_;
    if (classes.some(clazz => (value instanceof clazz))) {
      throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
    }
  }

  protected getRightKey<T extends object>(
    type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>
  ) {
    const key = this.getConnectedKey(type, keyOrDefaultCreator);

    if (key === undefined) {
      throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
    }

    if (key === PersistenceV2Impl.KEYS_ARR_) {
      this.errorHelper(key, PersistError.Quota, `The key '${key}' cannot be used`);
      return undefined;
    }

    return key;
  }

  protected getRightGlobalKey<T extends object>(type: TypeConstructorWithArgs<T>, key?: string): string {
    if (key === undefined || key === null) {
      stateMgmtConsole.applicationWarn(StorageHelper.NULL_OR_UNDEFINED_KEY + ', try to use the type name as key');
      key = this.getTypeName(type);
      if (key === undefined) {
        throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
      }
    }

    if (key === PersistenceV2Impl.KEYS_ARR_) {
      this.errorHelper(key, PersistError.Quota, `The key '${key}' cannot be used`);
      return undefined;
    }
    return key;
  }

  protected getAreaMode(areaMode: number | undefined): number {
    if (typeof areaMode === 'undefined') {
      return AreaMode.EL2;
    }
    else if (areaMode >= AreaMode.EL1 && areaMode <= AreaMode.EL5) {
      return areaMode;
    } else {
      throw new Error(PersistenceV2Impl.NOT_SUPPORT_AREAMODE_MESSAGE_);
    }
  }

  protected getKeyMapType(key: string): MapType {
    if (this.globalMap_.has(key)) {
      return MapType.GLOBAL_MAP;
    } else if (this.map_.has(key)) {
      return MapType.MODULE_MAP;
    } else {
      return MapType.NOT_IN_MAP;
    }
  }

  protected getConnectDefaultValue<T extends object>(
    key: string, type: TypeConstructorWithArgs<T>,
    defaultCreator?: StorageDefaultCreator<T>
  ): T | undefined {
    if (!PersistenceV2Impl.storage_) {
      this.errorHelper(key, PersistError.Unknown, `The storage is null`);
      return undefined;
    }

    if (typeof defaultCreator !== 'function') {
      throw new Error(PersistenceV2Impl.INVALID_DEFAULT_VALUE);
    }

    const observedValue: T = defaultCreator();

    this.throwIfNotInstanceOf(observedValue, type, key);

    this.throwIfNotSupported(observedValue);

    return observedValue;
  }

  protected getValueFromDisk<T extends object, S extends object>(
    key: string, id: number, observedValue: T,
    type: TypeConstructorWithArgs<T>,
    defaultSubCreator?: StorageDefaultCreator<S>,
    areaMode?: number
  ): [T | undefined, boolean] {
    let newObservedValue: T;
    let json: string = "";

    try {
      json = PersistenceV2Impl.storage_.get(key, areaMode);
    } catch (err) {
      this.errorHelper(key, PersistError.Unknown, err);
      return [undefined, true];
    }

    try {
      if (json.startsWith(DataCoder.FORMAT_TAG)) {
        const parsedValue = DataCoder.parse(json) as T;
        // Adding ref for persistence
        ObserveV2.getObserve().startRecordDependencies(this, id);
        newObservedValue = DataCoder.restoreTo(observedValue, parsedValue, defaultSubCreator) as T;
        ObserveV2.getObserve().stopRecordDependencies();
      } else {
        // Adding ref for persistence
        ObserveV2.getObserve().startRecordDependencies(this, id);
        newObservedValue = JSONCoder.parseTo(observedValue, json) as T;
        ObserveV2.getObserve().stopRecordDependencies();
      }
    } catch (err) {
      ObserveV2.getObserve().stopRecordDependencies();
      this.errorHelper(key, PersistError.Serialization, err);
      return [undefined, true];
    }

    this.throwIfNotInstanceOf(newObservedValue, type, key);

    this.connectNewValue(key, newObservedValue, this.getTypeName(type), areaMode);
    return [newObservedValue, false];
  }

  protected setValueToDisk<T extends object>(key: string, id: number, observedValue: T,
    type: TypeConstructorWithArgs<T>, areaMode?: number | undefined
  ): T | undefined {
    ObserveV2.getObserve().startRecordDependencies(this, id);
    // Map is a proxy object. When it is connected for the first time, map.has is used to add dependencies,
    // and map.set is used to trigger writing to disk.
    const keyType: MapType = this.getKeyMapType(key);
    ObserveV2.getObserve().stopRecordDependencies();

    // Writing to persistence by ref
    if (keyType === MapType.NOT_IN_MAP) {
      if (typeof areaMode === 'number') {
        this.connectNewValue(key, observedValue, this.getTypeName(type), areaMode);
      } else {
        this.connectNewValue(key, observedValue, this.getTypeName(type));
      }
    }
    return observedValue;
  }

  protected writeAllChangedToFile(persistKeys: Array<number>): void {
    for (let i = 0; i < persistKeys.length; ++i) {
      const id: number = persistKeys[i];
      const key: string = this.idToKey_.get(id);

      try {
        const keyType: MapType = this.getKeyMapType(key);

        if (keyType !== MapType.NOT_IN_MAP) {
          const value: object = keyType === MapType.GLOBAL_MAP ? this.globalMap_.get(key) : this.map_.get(key);

          ObserveV2.getObserve().startRecordDependencies(this, id);
          const json = DataCoder.stringify(value);
          ObserveV2.getObserve().stopRecordDependencies();

          if (keyType === MapType.GLOBAL_MAP) {
            const areaMode = this.globalMapAreaMode_.get(key);
            PersistenceV2Impl.storage_.set(key, json, areaMode);
          } else {
            PersistenceV2Impl.storage_.set(key, json);
          }
        }
      } catch (err) {
        if (this.cb_ && typeof this.cb_ === 'function') {
          this.cb_(key, PersistError.Serialization, err);
          continue;
        }

        stateMgmtConsole.applicationError(`For '${key}' key: ` + err);
      }
    }
  }

  protected storeKeyToPersistenceV2(key: string, areaMode?: number | undefined): void {
    try {
      if (typeof areaMode === 'number') {
        if (this.globalKeysArr_[areaMode].has(key)) {
          return;
        }

        // Initializing the keys arr in memory
        if (!this.globalKeysArr_[areaMode].size) {
          this.globalKeysArr_[areaMode] = this.getKeysArrFromStorage(areaMode);
        }

        this.globalKeysArr_[areaMode].add(key);

        // Updating the keys arr in disk
        this.storeKeysArrToStorage(this.globalKeysArr_[areaMode], areaMode);
      } else {
        if (this.keysArr_.has(key)) {
          return;
        }

        // Initializing the keys arr in memory
        if (!this.keysArr_.size) {
          this.keysArr_ = this.getKeysArrFromStorage();
        }

        this.keysArr_.add(key);

        // Updating the keys arr in disk
        this.storeKeysArrToStorage(this.keysArr_);
      }
    } catch (err) {
      this.errorHelper(key, PersistError.Unknown, `fail to store the key '${key}'`);
    }
  }

  protected removeForModulePath(key: string): void {
    PersistenceV2Impl.storage_.delete(key);
    // The first call for module path
    if (!this.keysArr_.has(key)) {
      this.keysArr_ = this.getKeysArrFromStorage();
    }

    this.keysArr_.delete(key);
    this.storeKeysArrToStorage(this.keysArr_);
  }

  protected getRemoveFlagForGlobalPath(key: string): boolean {
    let removeFlag = false;
    // first call for global path
    for (let i = 0; i < this.globalKeysArr_.length; i++) {
      if (PersistenceV2Impl.storage_.has(key, i)) {
        removeFlag = true;
        PersistenceV2Impl.storage_.delete(key, i);
        this.globalKeysArr_[i] = this.getKeysArrFromStorage(i);
        this.globalKeysArr_[i].delete(key);
        this.storeKeysArrToStorage(this.globalKeysArr_[i], i);
      }
    }
    return removeFlag;
  }

  protected removeFromPersistenceV2(key: string, areaMode: number | undefined): void {
    try {
      // check for global path
      if (typeof areaMode === 'number') {
        PersistenceV2Impl.storage_.delete(key, areaMode);
        this.globalKeysArr_[areaMode].delete(key);
        this.storeKeysArrToStorage(this.globalKeysArr_[areaMode], areaMode);
      } else {
        let removeFlag: boolean = false;
        // check for module path
        if (PersistenceV2Impl.storage_.has(key)) {
          removeFlag = true;
          this.removeForModulePath(key);
        } else {
          removeFlag = this.getRemoveFlagForGlobalPath(key);
        }
        if (!removeFlag) {
          stateMgmtConsole.applicationWarn(PersistenceV2Impl.DELETE_NOT_EXIST_KEY + `keys:${key}`);
        }
      }
    } catch (err) {
      this.errorHelper(key, PersistError.Unknown, `fail to remove the key '${key}'`);
    }
  }

  protected getKeysArrFromStorage(areaMode?: number | undefined): Set<string> {
    if (typeof areaMode === 'number' && !PersistenceV2Impl.storage_.has(PersistenceV2Impl.KEYS_ARR_, areaMode)) {
      return this.globalKeysArr_[areaMode];
    }
    else if (typeof areaMode === 'undefined' && !PersistenceV2Impl.storage_.has(PersistenceV2Impl.KEYS_ARR_)) {
      return this.keysArr_;
    }
    const jsonKeysArr: string = PersistenceV2Impl.storage_.get(PersistenceV2Impl.KEYS_ARR_, areaMode);
    return new Set(JSON.parse(jsonKeysArr));
  }

  protected storeKeysArrToStorage(keysArr: Set<string>, areaMode?: number | undefined): void {
    PersistenceV2Impl.storage_.set(PersistenceV2Impl.KEYS_ARR_, JSON.stringify(Array.from(keysArr)), areaMode);
  }

  protected errorHelper(key: string, reason: PersistError, message: string) {
    if (this.cb_ && typeof this.cb_ === 'function') {
      this.cb_(key, reason, message);
      return;
    }

    if (!key) {
      key = 'unknown';
    }
    throw new Error(`For '${key}' key: ` + message);
  }
}
