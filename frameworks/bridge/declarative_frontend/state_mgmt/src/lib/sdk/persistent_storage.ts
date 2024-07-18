/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

/**
 * file version
 *
 * To indicate the file formate
 *
 */
enum ObjectVersion {
  NewVersion,
  CompatibleVersion,
  Default,
}

/**
 * MapInfo
 *
 * Helper class to persist Map in Persistent storage
 *
 */
type MapItem<K, V> = { key: K, value: V };
class MapInfo<K, V> {
  static readonly replacer: string = '_____map_replacer__';
  static readonly replacerCompatible: string = 'ace_engine_state_mgmt_map_replacer';
  public keys: K[];
  public values: V[];

  constructor(
    public mapReplacer: string,
    public keyToValue: MapItem<K, V>[]
  ) { }

  // Check if the given object is of type MapInfo
  static isObject<K, V>(obj: unknown): ObjectVersion {
    const typedObject = obj as MapInfo<K, V>;
    if ('mapReplacer' in typedObject && typedObject.mapReplacer === MapInfo.replacer) {
      return ObjectVersion.NewVersion;
    }
    if ('mapReplacer' in typedObject && typedObject.mapReplacer === MapInfo.replacerCompatible) {
      return ObjectVersion.CompatibleVersion;
    }
    return ObjectVersion.Default;
  }

  // Convert Map to Object
  static toObject<K, V>(map: Map<K, V>): MapInfo<K, V> {
    let mapItems: MapItem<K, V>[] = [];
    map.forEach((val: V, key: K) => {
      mapItems.push({ key: key, value: val })
    })
    return new MapInfo(MapInfo.replacer, mapItems);
  }

  // Convert Object to Map
  static toMap<K, V>(obj: MapInfo<K, V>): Map<K, V> {
    return new Map<K, V>(obj.keyToValue.map((item: MapItem<K, V>) => [item.key, item.value]));
  }

  static toMapCompatible<K, V>(obj: MapInfo<K, V>): Map<K, V> {
    return new Map<K, V>(obj.keys.map((key, i) => [key, obj.values[i]]));
  }
}

/**
 * SetInfo
 *
 * Helper class to persist Set in Persistent storage
 *
 */
class SetInfo<V> {
  static readonly replacer: string = '_____set_replacer__';
  static readonly replacerCompatible: string = "ace_engine_state_mgmt_set_replacer";

  constructor(
    public setReplacer: string,
    public values: V[]
  ) { }

  // Check if the given object is of type SetInfo
  static isObject<V>(obj: unknown): obj is SetInfo<V> {
    const typedObject = obj as SetInfo<V>;
    if ('setReplacer' in typedObject &&
      (typedObject.setReplacer === SetInfo.replacer || typedObject.setReplacer === SetInfo.replacerCompatible)) {
      return true;
    }
    return false;
  }

  // Convert Set to Object
  static toObject<V>(set: Set<V>): SetInfo<V> {
    const values: V[] = Array.from(set.values());
    return new SetInfo(SetInfo.replacer, values);
  }

  // Convert Object to Set
  static toSet<V>(obj: SetInfo<V>): Set<V> {
    return new Set<V>(obj.values);
  }
}

/**
 * DateInfo
 *
 * Helper class to persist Date in Persistent storage
 *
 */
class DateInfo {
  static readonly replacer: string = '_____date_replacer__';
  static readonly replacerCompatible: string = "ace_engine_state_mgmt_date_replacer";

  constructor(
    public dateReplacer: string,
    public date: string
  ) { }

  // Check if the given object is of type DateInfo
  static isObject(obj: unknown): obj is DateInfo {
    const typedObject = obj as DateInfo;
    if ('dateReplacer' in typedObject &&
      (typedObject.dateReplacer === DateInfo.replacer || typedObject.dateReplacer === DateInfo.replacerCompatible)) {
      return true;
    }
    return false;
  }

  // Convert Date to Object
  static toObject(date: Date): DateInfo {
    return new DateInfo(DateInfo.replacer, date.toISOString());
  }

  // Convert Object to Date
  static toDate(obj: DateInfo): Date {
    return new Date(obj.date);
  }
}

/**
 * PersistentStorage
 *
 * Keeps current values of select AppStorage property properties persisted to file.
 *
 * since 9
 */

class PersistentStorage implements IMultiPropertiesChangeSubscriber {
  private static storage_: IStorage;
  private static instance_: PersistentStorage = undefined;

  private id_: number;
  private links_: Map<string, SubscribedAbstractProperty<any>>;

  /**
   *
   * @param storage method to be used by the framework to set the backend
   * this is to be done during startup
   *
   * internal function, not part of the SDK
   *
   */
  public static configureBackend(storage: IStorage): void {
    PersistentStorage.storage_ = storage;
  }

  /**
   * private, use static functions!
   */
  private static getOrCreate(): PersistentStorage {
    if (PersistentStorage.instance_) {
      // already initialized
      return PersistentStorage.instance_;
    }

    PersistentStorage.instance_ = new PersistentStorage();
    return PersistentStorage.instance_;
  }

  /**
   *
   * internal function, not part of the SDK
   */
  public static aboutToBeDeleted(): void {
    if (!PersistentStorage.instance_) {
      return;
    }

    PersistentStorage.getOrCreate().aboutToBeDeleted();
    PersistentStorage.instance_ = undefined;
  }


  /**
   * Add property 'key' to AppStorage properties whose current value will be
   * persistent.
   * If AppStorage does not include this property it will be added and initializes
   * with given value
   *
   * @since 10
   *
   * @param key property name
   * @param defaultValue If AppStorage does not include this property it will be initialized with this value
   *
   */
  public static persistProp<T>(key: string, defaultValue: T): void {
    PersistentStorage.getOrCreate().persistProp(key, defaultValue);
  }

  /**
   * @see persistProp
   * @deprecated
   */
  public static PersistProp<T>(key: string, defaultValue: T): void {
    PersistentStorage.getOrCreate().persistProp(key, defaultValue);
  }


  /**
   * Reverse of @see persistProp
   * @param key no longer persist the property named key
   *
   * @since 10
   */
  public static deleteProp(key: string): void {
    PersistentStorage.getOrCreate().deleteProp(key);
  }

  /**
   * @see deleteProp
   * @deprecated
   */
  public static DeleteProp(key: string): void {
    PersistentStorage.getOrCreate().deleteProp(key);
  }

  /**
   * Persist given AppStorage properties with given names.
   * If a property does not exist in AppStorage, add it and initialize it with given value
   * works as @see persistProp for multiple properties.
   *
   * @param properties
   *
   * @since 10
   *
   */
  public static persistProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    PersistentStorage.getOrCreate().persistProps(properties);
  }

  /**
   * @see persistProps
   * @deprecated
   */
  public static PersistProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    PersistentStorage.getOrCreate().persistProps(properties);
  }

  /**
   * Inform persisted AppStorage property names
   * @returns array of AppStorage keys
   *
   * @since 10
   */
  public static keys(): Array<string> {
    let result = [];
    const it = PersistentStorage.getOrCreate().keys();
    let val = it.next();

    while (!val.done) {
      result.push(val.value);
      val = it.next();
    }

    return result;
  }

  /**
   * @see keys
   * @deprecated
   */
  public static Keys(): Array<string> {
    return PersistentStorage.keys();
  }

/**
  * This methid offers a way to force writing the property value with given
  * key to persistent storage.
  * In the general case this is unnecessary as the framework observed changes
  * and triggers writing to disk by itself. For nested objects (e.g. array of
  * objects) however changes of a property of a property as not observed. This
  * is the case where the application needs to signal to the framework.
  *
  * @param key property that has changed
  *
  * @since 10
  *
  */
  public static notifyHasChanged(propName: string) {
  stateMgmtConsole.debug(`PersistentStorage: force writing '${propName}'-
      '${PersistentStorage.getOrCreate().links_.get(propName)}' to storage`);
  PersistentStorage.getOrCreate().writeToPersistentStorage(propName,
    PersistentStorage.getOrCreate().links_.get(propName).get());
  }

 /**
  * @see notifyHasChanged
  * @deprecated
  */
  public static NotifyHasChanged(propName: string) {
    stateMgmtConsole.debug(`PersistentStorage: force writing '${propName}'-
        '${PersistentStorage.getOrCreate().links_.get(propName)}' to storage`);
    PersistentStorage.getOrCreate().writeToPersistentStorage(propName,
      PersistentStorage.getOrCreate().links_.get(propName).get());
  }

  /**
   * all following methods are framework internal
   */

  private constructor() {
    this.links_ = new Map<string, SubscribedAbstractProperty<any>>();
    this.id_ = SubscriberManager.MakeId();
    SubscriberManager.Add(this);
  }

  private keys(): IterableIterator<string> {
    return this.links_.keys();
  }

  private persistProp<T>(propName: string, defaultValue: T): void {
    if (this.persistProp1(propName, defaultValue)) {
      // persist new prop
      stateMgmtConsole.debug(`PersistentStorage: writing '${propName}' - '${this.links_.get(propName)}' to storage`);
      this.writeToPersistentStorage(propName, this.links_.get(propName).get());
    }
  }


  // helper function to persist a property
  // does everything except writing prop to disk
  private persistProp1<T>(propName: string, defaultValue: T): boolean {
    stateMgmtConsole.debug(`PersistentStorage: persistProp1 ${propName} ${defaultValue}`);
    if (defaultValue == null && !Utils.isApiVersionEQAbove(12)) {
      stateMgmtConsole.error(`PersistentStorage: persistProp for ${propName} called with 'null' or 'undefined' default value!`);
      return false;
    }

    if (this.links_.get(propName)) {
      stateMgmtConsole.warn(`PersistentStorage: persistProp: ${propName} is already persisted`);
      return false;
    }

    let link = AppStorage.link(propName, this);
    if (link) {
      stateMgmtConsole.debug(`PersistentStorage: persistProp ${propName} in AppStorage, using that`);
      this.links_.set(propName, link);
    } else {
      let returnValue: T;
      if (!PersistentStorage.storage_.has(propName)) {
        stateMgmtConsole.debug(`PersistentStorage: no entry for ${propName}, will initialize with default value`);
        returnValue = defaultValue;
      }
      else {
        returnValue = this.readFromPersistentStorage(propName);
      }
      link = AppStorage.setAndLink(propName, returnValue, this);
      if (link === undefined) {
        stateMgmtConsole.debug(`PersistentStorage: failed to set and link app storage property ${propName}`);
        return false;
      }
      this.links_.set(propName, link);
      stateMgmtConsole.debug(`PersistentStorage: created new persistent prop for ${propName}`);
    }
    return true;
  }

  private persistProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    properties.forEach(property => this.persistProp1(property.key, property.defaultValue));
    this.write();
  }

  private deleteProp(propName: string): void {
    let link = this.links_.get(propName);
    if (link) {
      link.aboutToBeDeleted();
      this.links_.delete(propName);
      PersistentStorage.storage_.delete(propName);
      stateMgmtConsole.debug(`PersistentStorage: deleteProp: no longer persisting '${propName}'.`);
    } else {
      stateMgmtConsole.warn(`PersistentStorage: '${propName}' is not a persisted property warning.`);
    }
  }

  private write(): void {
    this.links_.forEach((link, propName, map) => {
      stateMgmtConsole.debug(`PersistentStorage: writing ${propName} to storage`);
      this.writeToPersistentStorage(propName, link.get());
    });
  }

  // helper function to write to the persistent storage
  // any additional check and formatting can to be done here
  private writeToPersistentStorage<T>(propName: string, value: T): void {
    if (value instanceof Map) {
      value = MapInfo.toObject(value) as unknown as T;
    } else if (value instanceof Set) {
      value = SetInfo.toObject(value) as unknown as T;
    } else if (value instanceof Date) {
      value = DateInfo.toObject(value) as unknown as T;
    }

    PersistentStorage.storage_.set(propName, value);
  }

  // helper function to read from the persistent storage
  // any additional check and formatting can to be done here
  private readFromPersistentStorage<T>(propName: string): T {
    let newValue: T = PersistentStorage.storage_.get(propName);
    if (newValue instanceof Object) {
      if (MapInfo.isObject(newValue) === ObjectVersion.NewVersion) {
        newValue = MapInfo.toMap(newValue as unknown as MapInfo<any, any>) as unknown as T;
      } else if (MapInfo.isObject(newValue) === ObjectVersion.CompatibleVersion) {
        newValue = MapInfo.toMapCompatible(newValue as unknown as MapInfo<any, any>) as unknown as T;
      } else if (SetInfo.isObject(newValue)) {
        newValue = SetInfo.toSet(newValue) as unknown as T;
      } else if (DateInfo.isObject(newValue)) {
        newValue = DateInfo.toDate(newValue) as unknown as T;
      }
    }

    return newValue;
  }

  // FU code path method
  public propertyHasChanged(info?: PropertyInfo): void {
    stateMgmtConsole.debug('PersistentStorage: property changed');
    this.write();
  }

  // PU code path method
  public syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<any>) {
    stateMgmtConsole.debug(`PersistentStorage: sync peer ${eventSource.info()} has changed`);
    this.write();
  }

  // public required by the interface, use the static method instead!
  public aboutToBeDeleted(): void {
    stateMgmtConsole.debug('PersistentStorage: about to be deleted');
    this.links_.forEach((val, key, map) => {
      stateMgmtConsole.debug(`PersistentStorage: removing ${key}`);
      val.aboutToBeDeleted();
    });

    this.links_.clear();
    SubscriberManager.Delete(this.id__());
    PersistentStorage.storage_.clear();
  }

  public id__(): number {
    return this.id_;
  }
};

