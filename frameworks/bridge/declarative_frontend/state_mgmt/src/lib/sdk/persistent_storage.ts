/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 * PersistentStorage
 * 
 * Keeps current values of select AppStorage property properties persisted to file.
 * 
 * since 9
 */

class PersistentStorage implements IMultiPropertiesChangeSubscriber {
  private static Storage_: IStorage;
  private static Instance_: PersistentStorage = undefined;

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
  public static ConfigureBackend(storage: IStorage): void {
    PersistentStorage.Storage_ = storage;
  }

  /**
   * private, use static functions!
   */
  private static GetOrCreate(): PersistentStorage {
    if (PersistentStorage.Instance_) {
      // already initialized
      return PersistentStorage.Instance_;
    }

    PersistentStorage.Instance_ = new PersistentStorage();
    return PersistentStorage.Instance_;
  }

  /**
   * 
   * internal function, not part of the SDK
   */
  public static AboutToBeDeleted(): void {
    if (!PersistentStorage.Instance_) {
      return;
    }

    PersistentStorage.GetOrCreate().aboutToBeDeleted();
    PersistentStorage.Instance_ = undefined;
  }


  /**
   * Add property 'key' to AppStorage properties whose current value will be 
   * persistemt.
   * If AppStorage does not include this property it will be added and initializes 
   * with given value
   * 
   * @since 9
   * 
   * @param key property name
   * @param defaultValue If AppStorage does not include this property it will be initialized with this value
   * 
   */
  public static PersistProp<T>(key: string, defaultValue: T): void {
    PersistentStorage.GetOrCreate().persistProp(key, defaultValue);
  }

  /**
   * Reverse of @see PersistProp
   * @param key no longer persist the property named key
   * 
   * @since 9
   */
  public static DeleteProp(key: string): void {
    PersistentStorage.GetOrCreate().deleteProp(key);
  }

  /**
   * Persist given AppStorage properties with given names.
   * If a property does not exist in AppStorage, add it and initialize it with given value
   * works as @see PersistProp for multiple properties.
   * 
   * @param properties 
   * 
   * @since 9
   * 
   */
  public static PersistProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    PersistentStorage.GetOrCreate().persistProps(properties);
  }

  /**
   * Inform persisted AppStorage property names
   * @returns array of AppStorage keys
   * 
   * @since 9
   */
  public static Keys(): Array<string> {
    let result = [];
    const it = PersistentStorage.GetOrCreate().keys();
    let val = it.next();

    while (!val.done) {
      result.push(val.value);
      val = it.next();
    }

    return result;
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
  * @since 9
  * 
  */
 public static NotifyHasChanged(propName: string) {
  stateMgmtConsole.debug(`PersistentStorage: force writing '${propName}'-
      '${PersistentStorage.GetOrCreate().links_.get(propName)}' to storage`);
  PersistentStorage.Storage_.set(propName,
    PersistentStorage.GetOrCreate().links_.get(propName).get());
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
      PersistentStorage.Storage_.set(propName, this.links_.get(propName).get());
    }
  }


  // helper function to persist a property
  // does everything except writing prop to disk
  private persistProp1<T>(propName: string, defaultValue: T): boolean {
    if (defaultValue == null || defaultValue == undefined) {
      stateMgmtConsole.error(`PersistentStorage: persistProp for ${propName} called with 'null' or 'undefined' default value!`);
      return false;
    }

    if (this.links_.get(propName)) {
      stateMgmtConsole.warn(`PersistentStorage: persistProp: ${propName} is already persisted`);
      return false;
    }

    let link = AppStorage.Link(propName, this);
    if (link) {
      stateMgmtConsole.debug(`PersistentStorage: persistProp ${propName} in AppStorage, using that`);
      this.links_.set(propName, link);
    } else {
      let newValue: T = PersistentStorage.Storage_.get(propName);
      let returnValue: T;
      if (!newValue) {
        stateMgmtConsole.debug(`PersistentStorage: no entry for ${propName}, will initialize with default value`);
        returnValue = defaultValue;
      }
      else {
        returnValue = newValue;
      }
      link = AppStorage.SetAndLink(propName, returnValue, this);
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
      PersistentStorage.Storage_.delete(propName);
      stateMgmtConsole.debug(`PersistentStorage: deleteProp: no longer persisting '${propName}'.`);
    } else {
      stateMgmtConsole.warn(`PersistentStorage: '${propName}' is not a persisted property warning.`);
    }
  }

  private write(): void {
    this.links_.forEach((link, propName, map) => {
      stateMgmtConsole.debug(`PersistentStorage: writing ${propName} to storage`);
      PersistentStorage.Storage_.set(propName, link.get());
    });
  }

  public propertyHasChanged(info?: PropertyInfo): void {
    stateMgmtConsole.debug("PersistentStorage: property changed");
    this.write();
  }

  public syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<any>) {
    stateMgmtConsole.debug(`PersistentStorage: sync peer ${eventSource.info()} has changed`);
    this.write();
  }

  // public required by the interface, use the static method instead!
  public aboutToBeDeleted(): void {
    stateMgmtConsole.debug("PersistentStorage: about to be deleted");
    this.links_.forEach((val, key, map) => {
      stateMgmtConsole.debug(`PersistentStorage: removing ${key}`);
      val.aboutToBeDeleted();
    });

    this.links_.clear();
    SubscriberManager.Delete(this.id__());
    PersistentStorage.Storage_.clear();
  }

  public id__(): number {
    return this.id_;
  }
};

