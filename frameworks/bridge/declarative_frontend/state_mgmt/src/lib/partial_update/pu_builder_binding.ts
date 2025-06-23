/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 *
**/

/**
 * Generic Binding class to encapsulate read-only data binding.
 *
 * @template T - The type of the value to be bound.
*/
class Binding<T> {
    private getter_: () => T;

    /**
     * Constructs a new Binding instance.
     *
     * @param getter - A function that returns the current value of type T.
     */
    constructor(getter: () => T) {
        this.getter_ = getter;
    }

    /**
     * Gets the current value of the binding.
     *
     * @returns The current value of type T.
     */
    public get value(): T {
        return this.getter_();
    }
}

/**
 * Generic MutableBinding class to encapsulate both read and write operations.
 *
 * @template T - The type of the value to be bound.
 */
class MutableBinding<T> {
    private getter_: () => T;
    private setter_: (newValue: T) => void;

    /**
     * Constructs a new MutableBinding instance.
     *
     * @param getter - A function that returns the current value of type T.
     * @param setter - A function that sets a new value of type T.
     */
    constructor(getter: () => T, setter: (newValue: T) => void) {
        this.getter_ = getter;
        this.setter_ = setter;
    }

    /**
     * Sets a new value for the binding.
     *
     * @param newValue - The new value to be set of type T.
     */
    set value(newValue: T) {
        this.setter_(newValue);
    }

    /**
     * Gets the current value of the binding.
     *
     * @returns The current value of type T.
     */
    get value(): T {
        return this.getter_();
    }
}