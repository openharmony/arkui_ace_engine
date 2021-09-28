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

class AppStorage {
  private static Instance_: AppStorage = undefined;

  // FIXME: Perhaps "GetInstance" would be better name for this
  // static Get(): AppStorage { return AppStorage.Instance_; }
  static GetOrCreate(): AppStorage {
    if (!AppStorage.Instance_) {
      AppStorage.Instance_ = new AppStorage();
    }
    return AppStorage.Instance_;
  }

  private storage_: Map<string, ObservedPropertyAbstract<any>>;

  static Link<T>(key: string): ObservedPropertyAbstract<T> {
    return AppStorage.GetOrCreate().link(key);
  }

  static SetAndLink<T>(key: string, defaultValue: T): ObservedPropertyAbstract<T> {
    return AppStorage.GetOrCreate().setAndLink(key, defaultValue);
  }

  static Prop<T>(key: string): ObservedPropertyAbstract<T> {
    return AppStorage.GetOrCreate().prop(key);
  }

  static SetAndProp<S>(key: string, defaultValue: S): ObservedPropertyAbstract<S> {
    return AppStorage.GetOrCreate().setAndProp(key, defaultValue);
  }

  static Has(key: string): boolean {
    return AppStorage.GetOrCreate().has(key);
  }

  static Get<T>(key: string): T | undefined {
    return AppStorage.GetOrCreate().get(key);
  }

  static Set<T>(key: string, newValue: T): boolean {
    return AppStorage.GetOrCreate().set(key, newValue);
  }

  // FIXME(cvetan): No mechanism to create "immutable" properties
  static SetOrCreate<T>(key: string, newValue: T): void {
    AppStorage.GetOrCreate().setOrCreate(key, newValue);
  }

  static Delete(key: string): boolean {
    return AppStorage.GetOrCreate().delete(key);
  }

  static Keys(): IterableIterator<string> {
    return AppStorage.GetOrCreate().keys();
  }

  static Size(): number {
    return AppStorage.GetOrCreate().size();
  }

  static Clear(): boolean {
    return AppStorage.GetOrCreate().clear();
  }

  static AboutToBeDeleted(): void {
    AppStorage.GetOrCreate().aboutToBeDeleted();
  }

  static NumberOfSubscribersTo(propName: string): number | undefined {
    return AppStorage.GetOrCreate().numberOfSubscrbersTo(propName);
  }

  static SubscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean {
    return AppStorage.GetOrCreate().subscribeToChangesOf(propName, subscriber);
  }

  static UnsubscribeFromChangesOf(propName: string, subscriberId: number): boolean {
    return AppStorage.GetOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
  }

  static IsMutable(key: string): boolean {
    // FIXME(cvetan): No mechanism for immutable/mutable properties
    return true;
    //   return AppStorage.GetOrCreate().isMutable(key);
  }

  constructor() {
    this.storage_ = new Map<string, ObservedPropertyAbstract<any>>();
  }

  /**
   * App should call this method to order close down app storage before
   * terminating itself.
   * Before deleting a prop from app storage all its subscribers need to
   * unsubscribe from the property.
   *
   * @returns true if all properties could be removed from app storage
   */
  public aboutToBeDeleted(): boolean {
    return this.clear();
  }

  public get<T>(propName: string): T | undefined {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    return (p) ? p.get() : undefined;
  }

  public set<T>(propName: string, newValue: T): boolean {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    if (p) {
      p.set(newValue);
      return true;
    } else {
      return false;
    }
  }

  public setOrCreate<T>(propName: string, newValue: T): void {
    var p: ObservedPropertyAbstract<T> = this.storage_.get(propName);
    if (p) {
      console.log(`AppStorage.setOrCreate(${propName}, ${newValue}) update existing property`);
      p.set(newValue);
    } else {
      console.log(`AppStorage.setOrCreate(${propName}, ${newValue}) create new entry and set value`);
      const newProp = (typeof newValue === "object") ?
        new ObservedPropertyObject<T>(newValue, undefined, propName)
        : new ObservedPropertySimple<T>(newValue, undefined, propName);
      this.storage_.set(propName, newProp);
    }
  }

  public has(propName: string): boolean {
    console.log(`AppStorage.has(${propName})`);
    return this.storage_.has(propName);
  }


  /**
   * Delete poperty from AppStorage
   * must only use with caution:
   * Before deleting a prop from app storage all its subscribers need to
   * unsubscribe from the property.
   * This method fails and returns false if given property still has subscribers
   * Another reason for failing is unkmown property.
   *
   * @param propName
   * @returns false if method failed
   */
  public delete(propName: string): boolean {
    var p: ObservedPropertyAbstract<any> | undefined = this.storage_.get(propName);
    if (p) {
      if (p.numberOfSubscrbers()) {
        console.error(`Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
        return false;
      }
      p.aboutToBeDeleted();
      this.storage_.delete(propName);
      return true;
    } else {
      console.warn(`Attempt to delete unknown property ${propName}.`);
      return false;
    }
  }

  /**
   * delete all properties from the AppStorage
   * precondition is that there are no subscribers anymore
   * method returns false and deletes no poperties if there is any property
   * that still has subscribers
   */
  protected clear(): boolean {
    for (let propName of this.keys()) {
      var p: ObservedPropertyAbstract<any> = this.storage_.get(propName);
      if (p.numberOfSubscrbers()) {
        console.error(`AppStorage.deleteAll: Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
        return false;
      }
    }
    for (let propName of this.keys()) {
      var p: ObservedPropertyAbstract<any> = this.storage_.get(propName);
      p.aboutToBeDeleted();
    }
    console.error(`AppStorage.deleteAll: success`);
  }

  public keys(): IterableIterator<string> {
    return this.storage_.keys();
  }

  public size(): number {
    return this.storage_.size;
  }

  public link<T>(propName: string, linkUser?: IPropertySubscriber): ObservedPropertyAbstract<T> | undefined {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    return (p) ? p.createLink(linkUser, propName) : undefined
  }

  public setAndLink<T>(propName: string, defaultValue: T, linkUser?: IPropertySubscriber): ObservedPropertyAbstract<T> {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    if (!p) {
      this.setOrCreate(propName, defaultValue);
    }
    return this.link(propName, linkUser);
  }

  public prop<S>(propName: string, propUser?: IPropertySubscriber): ObservedPropertyAbstract<S> | undefined {
    var p: ObservedPropertyAbstract<S> | undefined = this.storage_.get(propName);
    return (p) ? p.createProp(propUser, propName) : undefined
  }

  public setAndProp<S>(propName: string, defaultValue: S, propUser?: IPropertySubscriber): ObservedPropertyAbstract<S> {
    var p: ObservedPropertyAbstract<S> | undefined = this.storage_.get(propName);

    if (!p) {
      if (typeof defaultValue === "boolean" ||
        typeof defaultValue === "number" || typeof defaultValue === "string") {
        this.setOrCreate(propName, defaultValue);
      } else {
        return undefined;
      }
    }
    return this.prop(propName, propUser);
  }


  public subscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    if (p) {
      p.subscribeMe(subscriber);
      return true;
    }
    return false;
  }

  public unsubscribeFromChangesOf(propName: string, subscriberId: number): boolean {
    var p: ObservedPropertyAbstract<any> | undefined = this.storage_.get(propName);
    if (p) {
      p.unlinkSuscriber(subscriberId);
      return true;
    }
    return false;
  }

  /*
  return number of subscribers to this property
  mostly useful for unit testin
  */
  public numberOfSubscrbersTo(propName: string): number | undefined {
    var p: ObservedPropertyAbstract<any> | undefined = this.storage_.get(propName);
    if (p) {
      return p.numberOfSubscrbers();
    }
    return undefined;
  }
}
