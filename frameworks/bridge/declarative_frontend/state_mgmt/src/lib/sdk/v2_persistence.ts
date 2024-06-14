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
  Serialisation = 'serialisation',
  Unknown = 'unknown'
};

type PersistErrorType = PersistError.Quota | PersistError.Serialisation | PersistError.Unknown;
type PersistErrorCallback = ((key: string, reason: PersistErrorType, message: string) => void) | undefined;

class AppStorageV2Impl {
  public static defaultValueErrorMessage: string = 'The default creator should be function when first connect';

  private static instance_: AppStorageV2Impl | undefined = undefined;

  private memorizedValues_: Map<string, any>;

  constructor() {
    this.memorizedValues_ = new Map<string, any>();
  }

  public static instance(): AppStorageV2Impl {
    if (AppStorageV2Impl.instance_) {
      return AppStorageV2Impl.instance_;
    }
    AppStorageV2Impl.instance_ = new AppStorageV2Impl();
    return AppStorageV2Impl.instance_;
  }

  public connect<T extends object>(key: string, defaultCreator?: () => T): T | undefined {
    if (!this.memorizedValues_.has(key)) {
      if (typeof defaultCreator !== 'function') {
        stateMgmtConsole.error(AppStorageV2Impl.defaultValueErrorMessage);
        return undefined;
      }
      const defaultValue: T = defaultCreator();
      this.memorizedValues_.set(key, defaultValue);
      return defaultValue;
    }

    return this.memorizedValues_.get(key);
  }

  public remove(key: string): boolean {
    return this.removeFromMemory(key);
  }

  public getMemoryKeys(): Array<string> {
    return Array.from(this.memorizedValues_.keys());
  }

  private removeFromMemory(key: string): boolean {
    return this.memorizedValues_.delete(key);
  }
}

class PersistenceV2Impl {
  public static readonly MIN_PERSISTENCE_ID = 0x1010000000000;
  public static nextPersistId_ = PersistenceV2Impl.MIN_PERSISTENCE_ID;

  private static readonly KEYS_ARR_: string = '___keys_arr';
  private static storage_: IStorage;
  private static instance_: PersistenceV2Impl = undefined;

  // the map is used to store the persisted value in memory, can reuse when re-connect if the key exists
  private map_: Map<string, any>;
  private keysArr_: Set<string>;
  private cb_: PersistErrorCallback = undefined;
  private idToKey_: Map<number, string>;

  constructor() {
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

  public connect<T extends object>(key: string, defaultCreator?: () => T): T | undefined {
    if (key === PersistenceV2Impl.KEYS_ARR_) {
      this.errorHelper(key, PersistError.Quota, `The key '${key}' cannot be used`);
      return undefined;
    }

    // In memory
    if (this.map_.has(key)) {
      return this.map_.get(key);
    }

    if (!PersistenceV2Impl.storage_) {
      this.errorHelper(key, PersistError.Unknown, `The storage is null`);
      return undefined;
    }

    if (typeof defaultCreator !== 'function') {
      this.errorHelper(key, PersistError.Quota, AppStorageV2Impl.defaultValueErrorMessage);
      return undefined;
    }

    const observedValue: T = defaultCreator();

    if (this.isNotClassObject(observedValue)) {
      this.errorHelper(key, PersistError.Quota, `Not support! only the class object can be serialized`);
      return undefined;
    }

    const id: number = ++PersistenceV2Impl.nextPersistId_;
    this.idToKey_.set(id, key);

    // Not in memory, but in disk
    if (PersistenceV2Impl.storage_.has(key)) {
      let newObservedValue: T;

      try {
        const json: string = PersistenceV2Impl.storage_.get(key);

        // Adding ref for persistence
        ObserveV2.getObserve().startRecordDependencies(this, id);
        newObservedValue = JSONCoder.parseTo(observedValue, json) as T;
        ObserveV2.getObserve().stopRecordDependencies();
      } catch (err) {
        if (this.cb_ && typeof this.cb_ === 'function') {
          this.cb_(key, PersistError.Serialisation, err);
          return undefined;
        }

        throw err;
      }

      this.map_.set(key, newObservedValue);
      this.storeKeyToPersistenceV2(key);

      return newObservedValue;
    }

    // Neither in memory or in disk
    ObserveV2.getObserve().startRecordDependencies(this, id);
    // Map is a proxy object. When it is connected for the first time, map.has is used to add dependencies,
    // and map.set is used to trigger writing to disk.
    const hasKey: boolean = this.map_.has(key);
    ObserveV2.getObserve().stopRecordDependencies();

    // Writing to persistence by ref
    if (!hasKey) {
      this.map_.set(key, observedValue);
      this.storeKeyToPersistenceV2(key);
    }
    return observedValue;
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
      throw err;
    }
    return Array.from(this.keysArr_);
  }

  public remove(key: string): boolean {
    this.map_.delete(key);
    return this.removeFromPersistenceV2(key);
  }

  public save<T>(key: string): void {
    const value: T = this.map_.get(key);
    if (value) {
      try {
        PersistenceV2Impl.storage_.set(key, JSONCoder.stringify(value));
      } catch (err) {
        if (this.cb_ && typeof this.cb_ === 'function') {
          this.cb_(key, PersistError.Serialisation, err);
          return;
        }
        throw err;
      }
    }
  }

  public notifyOnError(cb: PersistErrorCallback): void {
    this.cb_ = cb;
  }

  public onChangeObserved(persistKeys: Array<number>): void {
    this.writeAllChangedToFile(persistKeys);
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

          PersistenceV2Impl.storage_.set(key, json);
        }
      } catch (err) {
        if (this.cb_ && typeof this.cb_ === 'function') {
          this.cb_(key, PersistError.Serialisation, err);
          continue;
        }

        throw err;
      }
    }
  }

  private isNotClassObject(value: object): boolean {
    return Array.isArray(value) || value instanceof Set || value instanceof Map || value instanceof Date ||
      value instanceof Boolean || value instanceof Number || value instanceof BigInt || value instanceof String ||
      value instanceof Symbol || value === undefined || value === null;
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
      if (this.cb_ && typeof this.cb_ === 'function') {
        this.cb_(key, PersistError.Unknown, `fail to store the key '${key}'`);
        return;
      }
      throw err;
    }
  }

  private removeFromPersistenceV2(key: string): boolean {
    try {
      if (PersistenceV2Impl.storage_.has(key)) {
        PersistenceV2Impl.storage_.delete(key);

        // The first call to remove
        if (!this.keysArr_.has(key)) {
          this.keysArr_ = this.getKeysArrFromStorage();
        }

        this.keysArr_.delete(key);
        this.storeKeysArrToStorage(this.keysArr_);
        return true;
      }
      return false;
    } catch (err) {
      if (this.cb_ && typeof this.cb_ === 'function') {
        this.cb_(key, PersistError.Unknown, `fail to remove the key '${key}'`);
        return;
      }
      throw err;
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
    } else {
      stateMgmtConsole.error(message);
    }
  }
}
