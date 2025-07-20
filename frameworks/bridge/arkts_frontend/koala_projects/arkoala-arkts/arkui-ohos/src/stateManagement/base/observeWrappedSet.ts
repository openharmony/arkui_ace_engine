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

final class CONSTANT {
    public static readonly OB_SET_ANY_PROPERTY = '__OB_ANY_INDEX';
    public static readonly OB_LENGTH = '__OB_LENGTH';
}

export class WrappedSet<K> extends Set<K> implements IObservedObject, ObserveWrappedBase, ISubscribedWatches {
    public store_: Set<K>;
    // Use public access to enable unit testing.
    public meta_: IMutableKeyedStateMeta;
    // support for @Watch
    // each IObservedObject manages a set of @Watch subscribers
    // when a object property changes need to call executeOnSubscribingWatches
    // compare interface
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    // IObservedObject interface
    private ____V1RenderId: RenderIdType = 0;

    /**
     * Constructs a Set from another Set
     * @param set another Set
     */
    constructor(set: Set<K>) {
        super();

        this.store_ = set;
        this.meta_ = FactoryInternal.mkMutableKeyedStateMeta('WrappedSet');
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

    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    public getRaw(): Object {
        return this.store_;
    }

    public shouldAddRef(): boolean {
        return ObserveSingleton.instance.shouldAddRef(this.____V1RenderId);
    }

    public toString(): String {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        }
        return this.store_.toString();
    }

    /**
     * Puts a value into the Set
     *
     * @param val the value to put into the Set
     * @returns this
     */
    public add(val: K): this {
        if (!this.store_.has(val)) {
            this.store_.add(val);
            this.meta_.fireChange(String(val as Object | undefined | null));
            this.meta_.fireChange(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.executeOnSubscribingWatches('add');
        }
        return this;
    }

    /**
     * Checks if a value is in the Set
     *
     * @param val the value to find in the Set
     * @returns true if the value is in the Set
     */
    public has(val: K): boolean {
        const has = this.store_.has(val);
        if (this.shouldAddRef()) {
            if (has) {
                this.meta_.addRef(String(val as Object | undefined | null));
            } else {
                this.meta_.addRef(CONSTANT.OB_LENGTH);
            }
        }
        return has;
    }

    /**
     * Returns number of unique elements in the Set
     *
     * @returns number of unique elements in the Set
     */
    public get size(): number {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.size;
    }

    /**
     * Removes a value from the Set
     *
     * @param val the value to remove
     */
    public delete(val: K): boolean {
        if (this.store_.has(val)) {
            const res = this.store_.delete(val);
            this.meta_.fireChange(String(val as Object | undefined | null));
            this.meta_.fireChange(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.executeOnSubscribingWatches('delete');
            return res;
        } else {
            return false;
        }
    }

    /**
     * Deletes all elements from the Set
     */
    public clear(): void {
        if (this.store_.size > 0) {
            this.store_.forEach((_, val) => {
                this.meta_.fireChange(String(val as Object | undefined | null));
            });
            this.store_.clear();
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.meta_.fireChange(CONSTANT.OB_SET_ANY_PROPERTY);
            this.executeOnSubscribingWatches('clear');
        }
    }

    /**
     * Despite name, returns elements from the Set
     * @returns an iterable of the values in the set
     */
    public keys(): IterableIterator<K> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.keys();
    }

    /**
     * Returns elements from the Set
     *
     * @returns an iterable of the values in the set
     */
    public values(): IterableIterator<K> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.values();
    }

    public $_iterator(): IterableIterator<K> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.$_iterator();
    }

    /**
     * @returns an iterable of [v,v] pairs for every value `v` in the set.
     */
    public entries(): IterableIterator<[K, K]> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.entries();
    }

    /**
     * Executes a provided function once per each value in the Set object, in insertion order
     *
     * @param callbackfn to apply
     */
    public forEach(callbackfn: (k: K, v: K, set: Set<K>) => void): void {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        this.store_.forEach(callbackfn);
    }
}
