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
 */

import { IMutableKeyedStateMeta, IObservedObject, ISubscribedWatches, RenderIdType, WatchIdType } from '../decorator';
import { SubscribedWatches } from '../decoratorImpl/decoratorWatch';
import { FactoryInternal } from './iFactoryInternal';
import { ObserveSingleton } from './observeSingleton';
import { ObserveWrappedBase } from './observeWrappedBase';
import { UIUtils } from '../utils';
final class CONSTANT {
    public static readonly OB_MAP_ANY_PROPERTY = '__OB_SET_ANY_PROPERTY';
    public static readonly OB_LENGTH = '__OB_LENGTH';
}

export class WrappedMap<K, V> extends Map<K, V> implements IObservedObject, ObserveWrappedBase, ISubscribedWatches {
    public store_: Map<K, V>;
    // Use public access to enable unit testing.
    protected meta_: IMutableKeyedStateMeta;
    // support for @Watch
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    // IObservedObject interface
    private ____V1RenderId: RenderIdType = 0;

    /**
     * Constructs a Map from another Map
     * @param map another map
     */
    constructor(map: Map<K, V>) {
        // Create without parameters to avoid call back to WrappedMap before "this" is fully constructed!
        super();

        this.store_ = map;
        this.meta_ = FactoryInternal.mkMutableKeyedStateMeta('WrappedMap');
    }

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches.removeWatchSubscriber(watchId);
    }
    public executeOnSubscribingWatches(propertyName: string): void {
        this.subscribedWatches.executeOnSubscribingWatches(propertyName);
    }

    public getRaw(): Object {
        return this.store_;
    }

    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    // helper
    public shouldAddRef(): boolean {
        return ObserveSingleton.instance.shouldAddRef(this.____V1RenderId);
    }

    public override toString(): String {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        }
        return this.store_.toString();
    }

    /**
     * Puts a pair of key and value into the Map
     *
     * @param key the key to put into the Map
     * @param val the value to put into the Map
     */
    public override set(key: K, val: V): this {
        if (!this.store_.has(key)) {
            this.store_.set(key, val);
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.executeOnSubscribingWatches('set');
        } else if (this.store_.get(key) !== val) {
            this.store_.set(key, val);
            this.meta_.fireChange(String(key as Object | undefined | null));
            this.executeOnSubscribingWatches('set');
        }
        this.meta_.fireChange(CONSTANT.OB_MAP_ANY_PROPERTY);
        return this;
    }

    /**
     * Checks if a key is in the Map
     *
     * @param key the key to find in the Map
     * @returns true if the value is in the Map
     */
    public override has(key: K): boolean {
        const ret = this.store_.has(key);
        if (this.shouldAddRef()) {
            if (ret) {
                this.meta_.addRef(String(key as Object | undefined | null));
            } else {
                this.meta_.addRef(CONSTANT.OB_LENGTH);
            }
        }
        return ret;
    }

    /**
     * Returns number of Entries with unique keys in the Map
     * @returns number of Entries with unique keys in the Map
     */
    public override get size(): number {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.size;
    }

    /**
     * Removes an Entry with specified key from the Map
     * @param key the key to remove
     */
    public override delete(key: K): boolean {
        if (this.store_.has(key)) {
            const ret: boolean = this.store_.delete(key);
            this.meta_.fireChange(String(key as Object | undefined | null));
            this.meta_.fireChange(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.executeOnSubscribingWatches('delete');
            return ret;
        } else {
            return false;
        }
    }

    /**
     * Deletes all elements from the Map
     */
    public override clear(): void {
        if (this.store_.size > 0) {
            this.store_.forEach((_, prop) => {
                this.meta_.fireChange(String(prop as Object | undefined | null));
            });
            this.store_.clear();
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.meta_.fireChange(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.executeOnSubscribingWatches('clear');
        }
    }

    /**
     * Returns a value assosiated with key if present
     *
     * @param key the key to find in the Map
     * @returns value if assosiated with key presents.
     */
    public override get(key: K): V | undefined {
        if (this.shouldAddRef()) {
            if (this.store_.has(key)) {
                this.meta_.addRef(String(key as Object | undefined | null));
            } else {
                this.meta_.addRef(CONSTANT.OB_LENGTH);
            }
        }
        return UIUtils.makeObserved(this.store_.get(key));
    }

    /**
     * Returns a value assosiated with key if present, or a default value otherwise
     *
     * @param key the key to find in the Map
     * @param def a value to return if key is not in the Map
     * @returns value if key presents, def otherwise
     */
    public override get(key: K, def: V): V {
        if (this.shouldAddRef()) {
            if (this.store_.has(key)) {
                this.meta_.addRef(String(key as Object | undefined | null));
            } else {
                this.meta_.addRef(CONSTANT.OB_LENGTH);
            }
        }
        return this.store_.get(key, def);
    }

    /**
     * Returns elements from the Map as an keys Iterator
     *
     * @returns iterator with map keys
     */
    public override keys(): IterableIterator<K> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.keys();
    }

    /**
     * Returns elements from the Map as an values Iterator
     *
     * @returns iterator with map values
     */
    public override values(): IterableIterator<V> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.values();
    }

    public override $_iterator(): IterableIterator<[K, V]> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.entries();
    }

    /**
     * Returns elements from the Map as an array of Entries
     *
     * @returns an array of Entries
     */
    public override entries(): IterableIterator<[K, V]> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.entries();
    }

    /**
     * Executes a provided function once per each key/value pair in the Map, in insertion order
     *
     * @param callbackfn to apply
     */
    public override forEach(callbackfn: (v: V, k: K, map: Map<K, V>) => void): void {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.forEach(callbackfn);
    }
}
