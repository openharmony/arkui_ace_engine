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

type PropertyInfo = string;

/**
  * The IPropertySubscriber interface describes an instance that can subscribes
  * to various changes of app state.
  * It must have a gloabbly unique id
*/
interface IPropertySubscriber {

  // globally unique id
  id__(): number;

  /**
   *  inform the subscribed property
   * that the subscriber is about to be deleted
   * hence , unsubscribe
   */
  aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}

/**
 * The ISinglePropertyChangeSubscriber<T> describes an 
 * instance that subscribes to a source that manages a single app state property.
 * That instances expects to receive hasChanged() events with the new property value.
 * This property is of type T.
 */
interface ISinglePropertyChangeSubscriber<T> extends IPropertySubscriber {
  
  /**
   * get informed after the property has changed.
   */
  hasChanged(newValue: T): void;
}

/**
 * The IMultiPropertiesChangeSubscriber<T> describes an 
 * instance that subscribes to a source that manages multiple app state properties.
 * That instances expects to receive propertyHasChanged() events with the changed property name 
 * as a parameter.
 */
interface IMultiPropertiesChangeSubscriber extends IPropertySubscriber {
  // get informed that given property has changed.
  // Note: a Property's PropertyInfo can be undefined.
  propertyHasChanged(info?: PropertyInfo): void;
}

/**
 * The IMultiPropertiesReadSubscriber<T> describes an 
 * instance that subscribes to a source that manages multiple app state properties.
 * That instances expects to receive propertyRead() events with the read property name 
 * as a parameter. These events will typically only fire if read access recording 
 * has been explicitely enabled
 * 
 * Not a public / sdk interface
 */
 interface IMultiPropertiesReadSubscriber extends IPropertySubscriber {
  // get informed that given property has been read (get access).
  // Note: a Property's PropertyInfo can be undefined.
  propertyRead(info?: PropertyInfo): void;
}

/**
 * ViewPU implements IViewPropertiesChangeSubscriber<T>/
 * The ViewPU expects to receive viewPropertyHasChanged() events with the changed property name 
 * and a Set of dependent elementIds / nodeIds as a parameters.
 * 
 * Not a public / sdk interface
* 
*/
interface IViewPropertiesChangeSubscriber extends IPropertySubscriber {
  // ViewPU get informed when View variable has changed
  // informs the elmtIds that need update upon variable change
  viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void ;
}
