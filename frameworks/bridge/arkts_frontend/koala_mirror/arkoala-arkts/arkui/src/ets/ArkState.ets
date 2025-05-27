/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 *  AbstractProperty is an alias to the referenced storage property.
 */
export interface AbstractProperty<T> {
    /**
     * @returns the name of the referenced storage property
     */
    info(): string
    /**
     * @returns the value of the referenced storage property
     */
    get(): T
    /**
     * Updates the value of the referenced storage property.
     * @param newValue - new value for the referenced storage property
     */
    set(newValue: T): void
}

export interface TrackableProperty<T> extends AbstractProperty<T> {
    subscribe(listener: () => void): void
    unsubscribe(listener: () => void): void
    aboutToBeDeleted(): void
}

/**
 * Defines the subscribed abstract property.
 * @since 7
 * @systemapi
 */
export abstract class SubscribedAbstractProperty<T> implements TrackableProperty<T> {
    /**
     * Returns the property name,
     * e.g. let link = AppStorage.Link("foo") then link.info() == "foo"
     *
     * @returns { string } the property name if set or undefined
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    abstract info(): string

    /**
     * Called when data is obtained.
     * @since 7
     * @systemapi
     */
    abstract get(): T

    /**
     * Called when data is created.
     * @since 7
     * @systemapi
     */
    abstract set(newValue: T): void

    abstract subscribe(listener: () => void): void
    abstract unsubscribe(listener: () => void): void

    /**
     * An app needs to call this function before the instance of SubscribedAbstractProperty
     * goes out of scope / is subject to garbage collection. Its purpose is to unregister the
     * variable from the two-way/one-way sync relationship that AppStorage/LocalStorage.link()/prop()
     * and related functions create.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    abstract aboutToBeDeleted(): void
}
