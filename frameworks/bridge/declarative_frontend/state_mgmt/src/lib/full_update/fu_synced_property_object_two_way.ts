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
 * SynchedPropertyObjectTwoWay
 * 
 * all definitions in this file are framework internal
 */
class SynchedPropertyObjectTwoWay<C extends Object>
  extends ObservedPropertyObjectAbstract<C>
  implements ISinglePropertyChangeSubscriber<C> {

  private linkedParentProperty_: ObservedPropertyObjectAbstract<C>;
  private changeNotificationIsOngoing_: boolean = false;

  constructor(linkSource: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);
    this.linkedParentProperty_ = linkSource;
    if (this.linkedParentProperty_) {
      // register to the parent property
      this.linkedParentProperty_.subscribeMe(this);
    }

    // register to the ObservedObject
    ObservedObject.addOwningProperty(this.getObject(), this);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    if (this.linkedParentProperty_) {
        // unregister from parent of this link
        this.linkedParentProperty_.unlinkSuscriber(this.id__());
    
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.getObject(), this);
    }
    super.aboutToBeDeleted();
  }

  private getObject(): C {
    this.notifyPropertyRead();
    return (this.linkedParentProperty_ ? this.linkedParentProperty_.get() : undefined);
  }

  private setObject(newValue: C): void {
    if (this.linkedParentProperty_) {
        this.linkedParentProperty_.set(newValue);
    }
  }

  // this object is subscriber to ObservedObject
  // will call this cb function when property has changed
  hasChanged(newValue: C): void {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWay[${this.id__()}, '${this.info() || 'unknown'}']: contained ObservedObject hasChanged'.`);
      this.notifyHasChanged(this.getObject());
    }
  }



  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWay[${this.id__()}, '${this.info() || 'unknown'}']: get`);
    return this.getObject();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.getObject() === newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWay[${this.id__()}, '${this.info() || 'unknown'}']: set to newValue: '${newValue}'.`);

    ObservedObject.removeOwningProperty(this.getObject(), this);

    // the purpose of the changeNotificationIsOngoing_ is to avoid 
    // circular notifications @Link -> source @State -> other but alos same @Link
    this.changeNotificationIsOngoing_ = true;
    this.setObject(newValue);
    ObservedObject.addOwningProperty(this.getObject(), this);
    this.notifyHasChanged(newValue);
    this.changeNotificationIsOngoing_ = false;
  }

  /**
 * These functions are meant for use in connection with the App Stoage and
 * business logic implementation.
 * the created Link and Prop will update when 'this' property value
 * changes.
 */
  public createLink(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<C> {
    return new SynchedPropertyObjectTwoWay(this, subscribeOwner, linkPropName);
  }
  public createProp(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<C> {
    throw new Error("Creating a 'Prop' property is unsupported for Object type property value.");
  }

}
