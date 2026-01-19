/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

declare class SendableMap<K, V> {
    constructor(entries?: readonly (readonly [K, V])[] | null);
    [Symbol.iterator](): IterableIterator<[K, V]>
    set(key: K, value: V): this;
    keys(): IterableIterator<K>;
    values(): IterableIterator<V>;
};
declare class SendableSet<T> {
    constructor(values?: readonly T[] | null);
    [Symbol.iterator](): IterableIterator<T>;
    add(value: T): this;
    values(): IterableIterator<T>;
    delete(value: T): boolean;
};
declare class SendableArray<T> {
    constructor(...items: T[]);
    constructor(items: T[]);
    [Symbol.iterator](): IterableIterator<T>;
    entries(): IterableIterator<[number, T]>;
};

class SendableType {
    public static isArray<T extends object>(o: T): boolean {
        return o instanceof SendableArray;
    }
    public static isSet<T extends object>(o: T): boolean {
        return o instanceof SendableSet;
    }

    public static isMap<T extends object>(o: T): boolean {
        return o instanceof SendableMap;
    }

    public static isContainer<T extends object>(o: T): boolean {
        return o instanceof SendableMap || o instanceof SendableSet || o instanceof SendableArray;
    }
}