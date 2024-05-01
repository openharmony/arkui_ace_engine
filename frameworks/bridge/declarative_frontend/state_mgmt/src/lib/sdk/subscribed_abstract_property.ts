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


/**
 * 
 *   SubscribedAbstractProperty is base class of ObservedPropertyAbstract
 *   and includes these 3 functions that are part of the SDK.
 *
 *   SubscribedAbstractProperty<T> is the return type of 
 *   - AppStorage static functions Link(), Prop(), SetAndLink(), and SetAndProp()
 *   - LocalStorage methods link(), prop(), setAndLink(), and setAndProp()
 *
 *   'T' can be boolean, string, number or custom class.
 * 
 * Main functions
 *   @see get() reads the linked AppStorage/LocalStorage property value,
 *   @see set(newValue) write a new value to the synched AppStorage/LocalStorage property value
 *   @see aboutToBeDeleted() ends the sync relationship with the AppStorage/LocalStorage property
 *        The app must call this function before the SubscribedAbstractProperty<T> object 
 *        goes out of scope.
 * 
 * @since 7
*/

abstract class SubscribedAbstractProperty<T> {
     /** 
      * reads value of the sync'ed AppStorage/LocalStorage property.
      * 
      * @since 7
      *
      */
     public abstract get(): T;

     /**
      * Set new value, must be of type T, and must not be 'undefined' or 'null'.
      * Updates the value of value of the sync'ed AppStorage/LocalStorage property.
      * 
      * @param newValue 
      * 
      * @since 7
      */
     public abstract set(newValue: T): void;

     /**
      * An app needs to call this function before the instance of SubscribedAbstractProperty
      * goes out of scrope / is subject to garbage collection. Its purpose is to unregister the
      * variable from the tw0-way/one-way sync relationship that AppStorage/LocalStorage.link()/prop() 
      * and related functions create.
      * 
      * @since 7
      */
     public abstract aboutToBeDeleted(): void;


     /**
      * @return the property name if set or undefined
      * 
      * @since 7
      */
     public abstract info(): string;

     /**
      * @return the number of current subscribers
      * This info is useful because only a property with no subscribers is allowed 
      * to be deleted / let out of scope
      * 
      * @since 7
      */
     public abstract numberOfSubscrbers(): number;

     /**
      * Notify the property value would have changed.
      * The framework calls this function automatically upon @see set().
      * An application should NOT use this function!
      *
      * @since 7, depreciated, do NOT use!
      */
     protected abstract notifyHasChanged(newValue: T);

     /**
      * Notify the property value would have been read.
      * The framework calls this function automatically upon @see get()
      * if it needs this information (usually during initial render of a @Component)
      * An application should NOT use this function!
      *
      * @since 7, depreciated, do NOT use!
      */
     protected abstract notifyPropertyRead();


     /**
      * Create a new SubscribedAbstractProperty<T> and establish a two-way sync with this property.
      * We found that managing a 'chain' of SubscribedAbstractProperty<T> is hard to manage and in consequence
      * easily gets broken by one object being GC'ed. Therefore we have depreciated this method. Do not use it!
      * 
      * @since 7, depreciated.
      * 
      */
     public abstract createTwoWaySync(subscribeMe?: IPropertySubscriber, info?: string): SubscribedAbstractProperty<T>;

     /**
      * Create a new SubscribedAbstractProperty<T> and establish a one-way sync with this property.
      * We found that managing a 'chain' of SubscribedAbstractProperty<T> is hard to manage and in consequence
      * easily gets broken by one object being GC'ed. Therefore we have depreciated this method. Do not use it!
      * 
      * @since 7, depreciated.
      * 
      */
     public abstract createOneWaySync(subscribeMe?: IPropertySubscriber, info?: string): SubscribedAbstractProperty<T>;
}

/**
 *
 *  AbstractProperty can be understood as a handler or an alias
 *  to a property inside LocalStorage / AppStorage singleton
 *  allows to read the value with @see get and to change the
 *  value with @see set.
 *
 * Functions
 *   reads the referenced AppStorage/LocalStorage property value with given name @see get()
 *   write a new value to the AppStorage/LocalStorage property value @see set()
 *   returns the referenced AppStorage/LocalStorage property name @see info()
 *
 * Use ref or setAndRef to obtain a AbstractProperty.
 *
 * @since 12
 */
interface AbstractProperty<T> {
     /**
      * reads value of the referenced AppStorage/LocalStorage property.
      *
      * @returns { T } value of the referenced AppStorage/LocalStorage property.
      * @since 12
      */
     get(): T;

     /**
      * Set new value, must be of type T, can be 'undefined' or 'null'.
      * Updates the value of the referenced AppStorage/LocalStorage property.
      *
      * @param { T } newValue new value set to AppStorage/LocalStorage
      * @since 12
      */
     set(newValue: T): void;

     /**
      * returns the name of the referenced property
      *
      * @returns { string } name of the referenced property
      * @since 12
      */
     info(): string;
}
