/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

class DistributedStorage implements IMultiPropertiesChangeSubscriber {
  private storage_: IStorage;

  private id_: number;
  private links_: Map<string, ObservedPropertyAbstract<any>>;
  private aviliable_: boolean;
  private notifier_: (status: string) => void;

  public constructor(sessionId: string, notifier: (status: string) => void) {
    this.links_ = new Map<string, ObservedPropertyAbstract<any>>();
    this.id_ = SubscriberManager.Get().MakeId();
    SubscriberManager.Get().add(this);
    this.aviliable_ = false;
    this.notifier_ = notifier;
  }

  public keys(): Array<string> {
    let result = [];
    const it = this.links_.keys();
    let val = it.next();

    while (!val.done) {
      result.push(val.value);
      val = it.next();
    }

    return result;
  }


  public distributeProp<T>(propName: string, defaultValue: T): void {
    if (this.link(propName, defaultValue)) {
      console.debug(`DistributedStorage: writing '${propName}' - '${this.links_.get(propName)}' to storage`);
    }
  }

  public distributeProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    properties.forEach(property => this.link(property.key, property.defaultValue));
  }

  public link<T>(propName: string, defaultValue: T): boolean {
    if (defaultValue == null || defaultValue == undefined) {
      console.error(`DistributedStorage: linkProp for ${propName} called with 'null' or 'undefined' default value!`);
      return false;
    }
    if (this.links_.get(propName)) {
      console.warn(`DistributedStorage: linkProp: ${propName} is already exist`);
        return false;
    }
    let link = AppStorage.Link(propName, this);
    if (link) {
      console.debug(`DistributedStorage: linkProp ${propName} in AppStorage, using that`);
        this.links_.set(propName, link);
        this.setDistributedProp(propName, defaultValue);
    }
    else {
        let returnValue = defaultValue;
        if (this.aviliable_) {
            let newValue = this.getDistributedProp(propName);
            if (newValue == null) {
              console.debug(`DistributedStorage: no entry for ${propName}, will initialize with default value`);
                this.setDistributedProp(propName, defaultValue);
            }
            else {
                returnValue = newValue;
            }
        }
        link = AppStorage.SetAndLink(propName, returnValue, this);
        this.links_.set(propName, link);
        console.debug(`DistributedStorage: created new linkProp prop for ${propName}`);
    }
    return true;
  }

  public deleteProp(propName: string): void {
    let link = this.links_.get(propName);
    if (link) {
      link.aboutToBeDeleted();
      this.links_.delete(propName);
      if (this.aviliable_) {
        this.storage_.delete(propName);
      }
    } else {
      console.warn(`DistributedStorage: '${propName}' is not a distributed property warning.`);
    }
  }

  private write(key: string): void {
    let link = this.links_.get(key);
    if (link) {
      this.setDistributedProp(key, link.get());
    }
  }


  // public required by the interface, use the static method instead!
  public aboutToBeDeleted(): void {
    console.debug("DistributedStorage: about to be deleted");
    this.links_.forEach((val, key, map) => {
      console.debug(`DistributedStorage: removing ${key}`);
      val.aboutToBeDeleted();
    });

    this.links_.clear();
    SubscriberManager.Get().delete(this.id__());
  }

  public id__(): number {
    return this.id_;
  }

  public propertyHasChanged(info?: PropertyInfo): void {
    console.debug("DistributedStorage: property changed");
    this.write(info);
  }

  public onDataOnChange(propName: string): void {
    let link = this.links_.get(propName);
    let newValue = this.getDistributedProp(propName);
    if (link && newValue != null) {
        console.info(`DistributedStorage: dataOnChange[${propName}-${newValue}]`);
        link.set(newValue)
    }
  }

  public onConnected(status): void {
    console.info(`DistributedStorage onConnected: status = ${status}`);
    if (!this.aviliable_) {
        this.syncProp();
        this.aviliable_ = true;
    }
    if (this.notifier_ != null) {
        this.notifier_(status);
    }
  }

  private syncProp(): void {
    this.links_.forEach((val, key) => {
        let newValue = this.getDistributedProp(key);
        if (newValue == null) {
            this.setDistributedProp(key, val.get());
        } else {
            val.set(newValue);
        }
    });
  }

  private setDistributedProp(key, value): void {
    if (!this.aviliable_) {
      console.warn(`DistributedStorage is not aviliable`);
        return;
    }
    console.error(`DistributedStorage value is object ${key}-${JSON.stringify(value)}`);
    if (typeof value == 'object') {
        this.storage_.set(key, JSON.stringify(value));
        return;
    }
    this.storage_.set(key, value);
  }

  private getDistributedProp(key): any {
    let value = this.storage_.get(key);
    if (typeof value == 'string') {
        try {
            let returnValue = JSON.parse(value);
            return returnValue;
        }
        finally {
            return value;
        }
    }
    return value;
  }
};
