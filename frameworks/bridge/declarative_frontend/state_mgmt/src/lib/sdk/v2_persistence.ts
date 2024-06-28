/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class StorageHepler {
  protected static readonly DEFAULT_VALUE_ERROR_MESSAGE: string = 'The default creator should be function when first connect';
  protected static readonly DELETE_NOT_EXIST_KET_WARN_MESSAGE: string = 'The key to be deleted does not exist';
  protected static readonly TYPE_INVALID: string = 'The type should be function when use storage';

  // sotre old type name to check the type matches or not
  protected oldTypeValues_: Map<string, string>;

  constructor() {
    this.oldTypeValues_ = new Map<string, string>();
  }

  protected getConnectedKey<T>(type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>): string | undefined {
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

  protected checkTypeByName<T>(key: string, type: TypeConstructorWithArgs<T>, oldType: string): void {
    if (this.getTypeName(type) !== oldType) {
      throw new Error(`The type mismatches when use the key '${key}' in storage`);
    }
  }

  protected checkTypeByInstanceOf<T>(key: string, type: TypeConstructorWithArgs<T>, ins: T): void {
    this.checkTypeIsFunc(type);

    if (!(ins instanceof type)) {
      throw new Error(`The type mismatches when use the key '${key}' in storage`);
    }
  }

  protected getTypeName<T>(type: TypeConstructorWithArgs<T>): string | undefined {
    this.checkTypeIsFunc(type);

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

  private checkTypeIsFunc<T>(type: TypeConstructorWithArgs<T>): void {
    if (typeof type !== 'function') {
      throw new Error(StorageHepler.TYPE_INVALID);
    }
  }
}

class AppStorageV2Impl extends StorageHepler {
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

  public connect<T extends object>(type: TypeConstructorWithArgs<T>, keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultCreator?: StorageDefaultCreator<T>): T | undefined {
    const key: string = this.getConnectedKey(type, keyOrDefaultCreator);

    if (key === undefined) {
      throw new Error(AppStorageV2Impl.TYPE_INVALID);
    }

    if (typeof keyOrDefaultCreator === 'function') {
      defaultCreator = keyOrDefaultCreator;
    }

    if (!this.memorizedValues_.has(key)) {
      if (typeof defaultCreator !== 'function') {
        throw new Error(AppStorageV2Impl.DEFAULT_VALUE_ERROR_MESSAGE);
      }

      const defaultValue: T = defaultCreator();

      this.checkTypeByInstanceOf(key, type, defaultValue);

      this.memorizedValues_.set(key, defaultValue);
      this.oldTypeValues_.set(key, this.getTypeName(type));
      return defaultValue;
    }

    this.checkTypeByName(key, type, this.oldTypeValues_.get(key));

    const existedValue: T = this.memorizedValues_.get(key);
    return existedValue;
  }

  public remove<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    const key: string = this.getKeyOrTypeName(keyOrType);

    if (typeof key !== 'string') {
      stateMgmtConsole.error(AppStorageV2Impl.TYPE_INVALID);
      return;
    }

    this.removeFromMemory(key);
  }

  public getMemoryKeys(): Array<string> {
    return Array.from(this.memorizedValues_.keys());
  }

  private removeFromMemory(key: string): void {
    const isDeleted: boolean = this.memorizedValues_.delete(key);

    if (!isDeleted) {
      stateMgmtConsole.warn(AppStorageV2Impl.DELETE_NOT_EXIST_KET_WARN_MESSAGE);
    } else {
      this.oldTypeValues_.delete(key);
    }
  }
}

class PersistenceV2Impl extends StorageHepler {
  public static readonly MIN_PERSISTENCE_ID = 0x1010000000000;
  public static nextPersistId_ = PersistenceV2Impl.MIN_PERSISTENCE_ID;

  protected static readonly NOT_SUPPROT_TYPE: string = 'Not support! Can only use the class object in Persistence';
  private static readonly KEYS_ARR_: string = '___keys_arr';
  private static storage_: IStorage;
  private static instance_: PersistenceV2Impl = undefined;

  // the map is used to store the persisted value in memory, can reuse when re-connect if the key exists
  private map_: Map<string, any>;
  private keysArr_: Set<string>;
  private cb_: PersistErrorCallback = undefined;
  private idToKey_: Map<number, string>;

  constructor() {
    super();
    this.map_ = new Proxy(new Map<string, any>(), ObserveV2.arraySetMapProxy);
    this.keysArr_ = new Set<string>();
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

  public connect<T extends object>(type: TypeConstructorWithArgs<T>, keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultCreator?: StorageDefaultCreator<T>): T | undefined {
    if (typeof type !== 'function') {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }

    const key: string | undefined = this.getRightKey(type, keyOrDefaultCreator);
    if (key === undefined) {
      return undefined;
    }

    if (typeof keyOrDefaultCreator === 'function') {
      defaultCreator = keyOrDefaultCreator;
    }

    // In memory
    if (this.map_.has(key)) {
      const existedValue: T = this.map_.get(key);
      this.checkTypeByName(key, type, this.oldTypeValues_.get(key));
      return existedValue;
    }

    const observedValue: T | undefined = this.getConnectDefaultValue(key, type, defaultCreator);
    if (!observedValue) {
      return undefined;
    }

    const id: number = ++PersistenceV2Impl.nextPersistId_;
    this.idToKey_.set(id, key);

    // Not in memory, but in disk
    if (PersistenceV2Impl.storage_.has(key)) {
      return this.getValueFromDisk(key, id, observedValue, type);
    }

    // Neither in memory or in disk
    return this.setValueToDisk(key, id, observedValue, type);
  }

  public keys(): Array<string> {
    try {
      if (!this.keysArr_.size) {
        this.keysArr_ = this.getKeysArrFromStorage();
      }
    } catch (err) {
      if (this.cb_ && typeof this.cb_ === 'function') {
        this.cb_('', PersistError.Unknown, `fail to get all persisted keys`);
        return;
      }
      throw new Error(err);
    }

    return Array.from(this.keysArr_);
  }

  public remove<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    this.checkTypeIsClassObject(keyOrType);

    const key: string = this.getKeyOrTypeName(keyOrType);

    if (typeof key !== 'string') {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }

    this.disconnectValue(key);
  }

  public save<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    this.checkTypeIsClassObject(keyOrType);

    const key: string = this.getKeyOrTypeName(keyOrType);

    if (typeof key !== 'string') {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }

    const value: T = this.map_.get(key);
    if (value) {
      try {
        PersistenceV2Impl.storage_.set(key, JSONCoder.stringify(value));
      } catch (err) {
        this.errorHelper(key, PersistError.Serialization, err);
      }
    }
  }

  public notifyOnError(cb: PersistErrorCallback): void {
    this.cb_ = cb;
  }

  public onChangeObserved(persistKeys: Array<number>): void {
    this.writeAllChangedToFile(persistKeys);
  }

  private connectNewValue(key: string, newValue: any, typeName: string): void {
    this.map_.set(key, newValue);
    this.oldTypeValues_.set(key, typeName);

    this.storeKeyToPersistenceV2(key);
  }

  private disconnectValue(key: string): void {
    this.map_.delete(key);
    this.oldTypeValues_.delete(key);

    this.removeFromPersistenceV2(key);
  }

  private checkTypeIsClassObject<T>(keyOrType: string | TypeConstructorWithArgs<T>) {
    if ((typeof keyOrType !== 'string' && typeof keyOrType !== 'function') ||
      [Array, Set, Map, Date, Boolean, Number, BigInt, String, Symbol].includes(keyOrType as any)) {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }
  }

  private getRightKey<T extends object>(type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>) {
    const key: string = this.getConnectedKey(type, keyOrDefaultCreator);

    if (key === undefined) {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }

    if (key === PersistenceV2Impl.KEYS_ARR_) {
      this.errorHelper(key, PersistError.Quota, `The key '${key}' cannot be used`);
      return undefined;
    }

    return key;
  }

  private getConnectDefaultValue<T extends object>(key: string, type: TypeConstructorWithArgs<T>,
    defaultCreator?: StorageDefaultCreator<T>): T | undefined {
    if (!PersistenceV2Impl.storage_) {
      this.errorHelper(key, PersistError.Unknown, `The storage is null`);
      return undefined;
    }

    if (typeof defaultCreator !== 'function') {
      throw new Error(PersistenceV2Impl.DEFAULT_VALUE_ERROR_MESSAGE);
    }

    const observedValue: T = defaultCreator();

    this.checkTypeByInstanceOf(key, type, observedValue);

    if (this.isNotClassObject(observedValue)) {
      throw new Error(PersistenceV2Impl.NOT_SUPPROT_TYPE);
    }

    return observedValue;
  }

  private getValueFromDisk<T extends object>(key: string, id: number, observedValue: T,
    type: TypeConstructorWithArgs<T>): T | undefined {
    let newObservedValue: T;

    try {
      const json: string = PersistenceV2Impl.storage_.get(key);

      // Adding ref for persistence
      ObserveV2.getObserve().startRecordDependencies(this, id);
      newObservedValue = JSONCoder.parseTo(observedValue, json) as T;
      ObserveV2.getObserve().stopRecordDependencies();
    } catch (err) {
      this.errorHelper(key, PersistError.Serialization, err);
    }

    this.checkTypeByInstanceOf(key, type, newObservedValue);

    this.connectNewValue(key, newObservedValue, this.getTypeName(type));
    return newObservedValue;
  }

  private setValueToDisk<T extends object>(key: string, id: number, observedValue: T,
    type: TypeConstructorWithArgs<T>): T | undefined {
    ObserveV2.getObserve().startRecordDependencies(this, id);
    // Map is a proxy object. When it is connected for the first time, map.has is used to add dependencies,
    // and map.set is used to trigger writing to disk.
    const hasKey: boolean = this.map_.has(key);
    ObserveV2.getObserve().stopRecordDependencies();

    // Writing to persistence by ref
    if (!hasKey) {
      this.connectNewValue(key, observedValue, this.getTypeName(type));
    }
    return observedValue;
  }

  private writeAllChangedToFile(persistKeys: Array<number>): void {
    for (let i = 0; i < persistKeys.length; ++i) {
      const id: number = persistKeys[i];
      const key: string = this.idToKey_.get(id);

      try {
        const hasKey: boolean = this.map_.has(key);

        if (hasKey) {
          const value: object = this.map_.get(key);

          ObserveV2.getObserve().startRecordDependencies(this, id);
          const json: string = JSONCoder.stringify(value);
          ObserveV2.getObserve().stopRecordDependencies();

          if (this.isOverSizeLimit(json)) {
            throw new Error(`Cannot store the value of key '${key}'! The data size must be less than 8 KB`);
          }

          PersistenceV2Impl.storage_.set(key, json);
        }
      } catch (err) {
        if (this.cb_ && typeof this.cb_ === 'function') {
          this.cb_(key, PersistError.Serialization, err);
          continue;
        }

        throw new Error(err);
      }
    }
  }

  private isOverSizeLimit(json: string): boolean {
    let len = 0;
    for (let i = 0; i < json.length; ++i) {
      const c = json.charCodeAt(i);
      // one-byte character
      if ((c >= 0x0001 && c <= 0x007e) || (c >= 0xff60 && c <= 0xff9f)) {
        ++len;
      } else {
        len += 2;
      }
    }

    return len / 1024 > 8;
  }

  private isNotClassObject(value: object): boolean {
    return Array.isArray(value) || value instanceof Set || value instanceof Map || value instanceof Date ||
      value instanceof Boolean || value instanceof Number || value instanceof BigInt || value instanceof String ||
      value instanceof Symbol;
  }

  private storeKeyToPersistenceV2(key: string) {
    try {
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
    } catch (err) {
      this.errorHelper(key, PersistError.Unknown, `fail to store the key '${key}'`);
    }
  }

  private removeFromPersistenceV2(key: string): void {
    try {
      if (!PersistenceV2Impl.storage_.has(key)) {
        stateMgmtConsole.warn(PersistenceV2Impl.DELETE_NOT_EXIST_KET_WARN_MESSAGE);
        return;
      }

      PersistenceV2Impl.storage_.delete(key);

      // The first call to remove
      if (!this.keysArr_.has(key)) {
        this.keysArr_ = this.getKeysArrFromStorage();
      }

      this.keysArr_.delete(key);
      this.storeKeysArrToStorage(this.keysArr_);
    } catch (err) {
      this.errorHelper(key, PersistError.Unknown, `fail to remove the key '${key}'`);
    }
  }

  private getKeysArrFromStorage(): Set<string> {
    if (!PersistenceV2Impl.storage_.has(PersistenceV2Impl.KEYS_ARR_)) {
      return this.keysArr_;
    }
    const jsonKeysArr: string = PersistenceV2Impl.storage_.get(PersistenceV2Impl.KEYS_ARR_);
    return new Set(JSON.parse(jsonKeysArr));
  }

  private storeKeysArrToStorage(keysArr: Set<string>) {
    PersistenceV2Impl.storage_.set(PersistenceV2Impl.KEYS_ARR_, JSON.stringify(Array.from(keysArr)));
  }

  private errorHelper(key: string, reason: PersistError, message: string) {
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
