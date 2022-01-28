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

class ContentStorage {
  private storage_: Map<string, ObservedPropertyAbstract<any>>;

  constructor() {
    this.storage_ = new Map<string, ObservedPropertyAbstract<any>>();
  }

  public has(propName: string): boolean {
    return this.storage_.has(propName);
  }

  public get<T>(key: string): T | undefined {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(key);
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

 public setOrCreate<T>(propName: string, newValue: T, linkUser?: IPropertySubscriber): void {
    var p: ObservedPropertyAbstract<T> = this.storage_.get(propName);
    if (p) {
      console.log(`ContentStorage.setOrCreate(${propName}, ${newValue}) update existing property`);
      p.set(newValue);
    } else {
      console.log(`ContentStorage.setOrCreate(${propName}, ${newValue}) create new entry and set value`);
      const newProp = (typeof newValue === "object") ?
      new ObservedPropertyObject<T>(newValue, linkUser, propName)
        : new ObservedPropertySimple<T>(newValue, linkUser, propName);
      this.storage_.set(propName, newProp);
    }
  }

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

  public keys(): IterableIterator<string> {
    return this.storage_.keys();
  }

  public size(): number {
    return this.storage_.size;
  }

  public aboutToBeDeleted(): boolean {
    return this.clear();
  }

  public numberOfSubscribersTo(propName: string): number | undefined {
    var p: ObservedPropertyAbstract<any> | undefined = this.storage_.get(propName);
    if (p) {
      return p.numberOfSubscrbers();
    }
    return undefined;
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

  public isMutable(key: string): boolean {
    return true;
  }

  public clear(): boolean {
    for (let propName of this.keys()) {
      var p: ObservedPropertyAbstract<any> = this.storage_.get(propName);
      if (p.numberOfSubscrbers()) {
       console.error(`ContentStorage.deleteAll: Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
        return false;
      }
    }
    for (let propName of this.keys()) {
      var p: ObservedPropertyAbstract<any> = this.storage_.get(propName);
      p.aboutToBeDeleted();
    }
    console.error(`ContentStorage.deleteAll: success`);
  }

  public link<T>(propName: string, linkUser?: IPropertySubscriber): ObservedPropertyAbstract<T> | undefined {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    return (p) ? p.createLink(linkUser, propName) : undefined
  }

  public setAndLink<T>(propName: string, defaultValue: T, linkUser?: IPropertySubscriber): ObservedPropertyAbstract<T> {
    var p: ObservedPropertyAbstract<T> | undefined = this.storage_.get(propName);
    if (!p) {
      this.setOrCreate(propName, defaultValue, linkUser);
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
        this.setOrCreate(propName, defaultValue, propUser);
      } else {
        return undefined;
      }
    }
    return this.prop(propName, propUser);
  }
}