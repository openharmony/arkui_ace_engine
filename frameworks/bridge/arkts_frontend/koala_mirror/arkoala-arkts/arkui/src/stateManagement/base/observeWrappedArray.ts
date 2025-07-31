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
import { ObserveSingleton } from './observeSingleton';
import { FactoryInternal } from './iFactoryInternal';
import { ObserveWrappedBase } from './observeWrappedBase';
import { UIUtils } from '../utils';
final class CONSTANT {
    public static readonly OB_ARRAY_ANY_KEY = '__OB_ANY_INDEX';
    public static readonly OB_LENGTH = '__OB_LENGTH';
}

export class WrappedArray<T> extends Array<T> implements IObservedObject, ObserveWrappedBase, ISubscribedWatches {
    public store_: Array<T>;
    private meta_: IMutableKeyedStateMeta;
    // support for @Watch
    // each IObservedObject manages a set of @Wtch subscribers
    // when a object property changes need to call execureOnSubscribingWatches
    // compare interface
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    // IObservedObject interface
    private ____V1RenderId: RenderIdType = 0;

    constructor(src: Array<T>) {
        super();
        this.store_ = src;
        this.meta_ = FactoryInternal.mkMutableKeyedStateMeta('WrappedArray');
    }

    public getRaw(): Object {
        return this.store_;
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

    public shouldAddRef(): boolean {
        return ObserveSingleton.instance.shouldAddRef(this.____V1RenderId);
    }

    override get length(): number {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return this.store_.length;
    }

    override set length(newLen: number) {
        const len = this.store_.length;
        if (len !== newLen) {
            this.store_.length;
            if (this.store_.length !== len) {
                // the Array implementation actually changed the length!
                this.meta_.fireChange(CONSTANT.OB_LENGTH);
                this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

                // exec all subscribing @Watch
                this.executeOnSubscribingWatches('length');
            }
        }
    }

    // [index] operator
    public override $_get(index: number): T {
        return this.$_get(index.toInt());
    }

    // [] operator
    public override $_set(i: number, val: T): void {
        this.$_set(i.toInt(), val);
    }

    // [] operator
    public override $_get(idx: int): T {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
            this.meta_.addRef(String(idx as Object | undefined | null));
        }
        return UIUtils.makeObserved(this.store_[idx]);
    }

    // [] operator
    public override $_set(idx: int, val: T): void {
        const orig = this.store_[idx];
        this.store_[idx] = val;
        if (orig !== this.store_[idx]) {
            this.meta_.fireChange(String(idx as Object | undefined | null));
            this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

            // exec all subscribing @Watch functions
            this.executeOnSubscribingWatches(String(idx as Object | undefined | null));
        }
    }

    /**
     * Creates a new instance of WrappedArray.
     *
     * @param arrayLength amount of elements.
     * @param initialValue initial value of elements.
     */
    public static create<T>(arrayLength: number, initialValue: T): WrappedArray<T> {
        let other = new Array<T>(arrayLength.toInt());
        other.fill(initialValue);
        return new WrappedArray<T>(other);
    }

    /**
     * Extends Array with new elements to specified length.
     *
     * @param arrayLength amount of new added elements.
     * @param initialValue initial value of new elements.
     */
    public override extendTo(arrayLength: number, initialValue: T): void {
        this.store_.extendTo(arrayLength, initialValue);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);
        this.executeOnSubscribingWatches('extendTo');
    }

    /**
     * Shrinks Array to specified length.
     *
     * @param arrayLength length at which to shrink.
     */
    public override shrinkTo(arrayLength: number): void {
        this.store_.shrinkTo(arrayLength);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);
        this.executeOnSubscribingWatches('shrinkTo');
    }

    /**
     * Creates a new instance of an WrappedArray with Array of the specified length inside
     *
     * @param arrayLength The length of the array to be created (optional).
     * @returns A new Array instance with the specified length
     */
    public static $_invoke<T>(arrayLength?: number): WrappedArray<T> {
        if (arrayLength) {
            return new WrappedArray<T>(new Array<T>(arrayLength));
        } else {
            return new WrappedArray<T>(new Array<T>());
        }
    }

    /**
     * Creates a new WrappedArray with `Array` instance inside from `Object[]` primitive array.
     *
     * @param arr an iterable object to convert to an array.
     * @returns `Array` intance constructed from `Object[]` primitive array.
     */
    public static from<T>(iterable: ArrayLike<T> | Iterable<T>): WrappedArray<T> {
        return new WrappedArray<T>(Array.from<T, T>(iterable, (x: T, k: number): T => x));
    }

    /**
     * Creates a new WrappedArray with `Array` instance inside from `Object[]` primitive array.
     *
     * @param iterable an iterable object to convert to an array.
     * @param mapfn a mapping function to call on every element of the array.
     * Every value to be added to the array is first passed through this function, and `mapfn`'s return value
     * is added to the array instead.
     * @returns `Array` intance constructed from `Object[]` primitive array and given function.
     */
    public static from<T, U>(iterable: ArrayLike<T> | Iterable<T>, mapfn: (v: T, k: number) => U): WrappedArray<U> {
        return new WrappedArray<U>(Array.from<T, U>(iterable, mapfn));
    }

    public static from<T, U>(values: T[], mapfn: (v: T, k: number) => U): WrappedArray<U> {
        return new WrappedArray<U>(Array.from<T, U>(values, mapfn));
    }

    /**
     * Creates a new `Array` instance from `Object[]` primitive array.
     *
     * @param arr primitive array.
     * @returns `Array` intance constructed from `Object[]` primitive array.
     */
    public static from<T>(arr: T[]): WrappedArray<T> {
        return new WrappedArray<T>(Array.from<T>(arr));
    }

    /**
     * Reorders elements of `this` using comparator function.
     *
     * @param comparator function that defines the sort order.
     * @note Mutating method
     */
    public sort(comparator?: (a: T, b: T) => number): this {
        this.store_.sort(comparator);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('sort');

        return this;
    }

    /**
     * Removes the first element from an array and returns that removed element.
     * This method changes the length of the array.
     *
     * @returns shifted element, i.e. that was at index zero
     */
    public override shift(): T | undefined {
        const ret = this.store_.shift();
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('shift');

        return ret;
    }

    /**
     * Removes the last element from an array and returns that element.
     * This method changes the length of the array.
     *
     * @returns removed element
     */
    public override pop(): T | undefined {
        const ret = this.store_.pop();
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('pop');

        return ret;
    }

    /**
     * Adds the specified elements to the end of an array and returns the new length of the array.
     *
     * @returns new length
     */
    public override push(...val: T[]): number {
        const ret = this.store_.push(...val);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('push');

        return ret;
    }

    /**
     * Adds the specified elements to the end of an array and returns the new length of the array.
     *
     * @returns new length
     */
    public override pushECMA(...val: T[]): number {
        const ret = this.store_.pushECMA(...val);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('pushECMA');

        return ret;
    }

    /**
     * Changes the contents of an array by removing or replacing existing elements
     * and/or adding new elements in place.
     *
     * @param start index
     * @param delete number of items after start index
     * @returns an Array with deleted elements
     */
    public override splice(start: number, deleteIdx: Number | undefined, ...items: T[]): Array<T> {
        const ret = this.store_.splice(start, deleteIdx, ...items);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('splice');
        return ret;
    }

    /**
     * Changes the contents of an array by removing or replacing existing elements
     * and/or adding new elements in place.
     *
     * @param start index
     * @param delete number of items after start index
     * @returns an Array with deleted elements
     */
    public override splice(start: int, deleteIdx: int, ...items: T[]): Array<T> {
        const ret = this.store_.splice(start, deleteIdx, ...items);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('splice');

        return ret;
    }

    /**
     * Changes the contents of an array by removing or replacing existing elements
     * and/or adding new elements in place.
     *
     * @param start index
     * @returns an Array with deleted elements from start to the last element of the current instance
     */
    public override splice(start: number): Array<T> {
        const ret = this.store_.splice(start);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('splice');

        return ret;
    }

    /**
     * Changes the contents of an array by removing or replacing existing elements
     * and/or adding new elements in place.
     *
     * @param start index
     * @returns an Array with deleted elements from start to the last element of the current instance
     */
    public override splice(start: int): Array<T> {
        const ret = this.store_.splice(start);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('splice');

        return ret;
    }

    /**
     * Creates a new WrappedArray with regular Array inside
     * from a variable number of arguments,
     * regardless of number or type of the arguments.
     *
     * @param values an initilizer
     * @returns a newly created Array
     */
    public static of<T>(...values: T[]): WrappedArray<T> {
        const rawArray = Array.of(...values);
        return new WrappedArray<T>(rawArray);
    }

    /**
     * Adds the specified elements to the beginning of an Array
     * and returns the new length of the Array.
     *
     * @param values data to be added
     * @returns new length of the Array
     */
    public override unshift(...values: T[]): number {
        const ret = this.store_.unshift(...values);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('unshift');

        return ret;
    }

    /**
     * Returns an iterator over all indices
     */
    public override keys(): IterableIterator<Number> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.keys();
    }

    /**
     * Returns an iterator over all values
     */
    public override $_iterator(): IterableIterator<T> {
        // NOTE! addRef for OB_LENGTH similarly to V2!
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return this.store_.values();
    }

    /**
     * Returns the elements of an array that meet the condition specified in a callback function.
     *
     * @param predicate A function that accepts up to three arguments. The filter method calls the predicate function one time for each element in the array.
     * @returns New `Array` instance constructed from `this` with elements filtered using test function `predicate`.
     */
    public override filter(predicate: (value: T, index: number, array: Array<T>) => boolean): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.filter(predicate);
    }

    /**
     * Creates a new Array with all sub-array elements concatenated
     * into it recursively up to the specified depth.
     *
     * @param depth
     * @returns a flattened Array with respect to depth (not WrappedArray !)
     */
    public override flat<U>(depth: number): Array<U> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.flat<U>(depth);
    }

    /**
     * Creates a new Array with all sub-array elements concatenated
     * into it recursively up to the specified depth.
     *
     * @param depth
     * @returns a flattened Array with respect to depth
     */
    public override flat<U>(depth: int): Array<U> {
        return this.store_.flat<U>(depth);
    }

    /**
     * Creates a new Array with all sub-array elements concatenated
     *
     * @returns a flattened Array
     */
    public override flat<U>(): Array<U> {
        return this.flat<U>(1);
    }

    /**
     * Applies flat and than map
     *
     * @param fn a function to apply
     * @return new Array after map and than flat
     */
    public override flatMap<U>(fn: (v: T, k: number, arr: Array<T>) => U): Array<U> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.flatMap(fn);
    }

    /**
     * Takes an integer value and returns the item at that index,
     * allowing for positive and negative integers. Negative integers count back
     * from the last item in the array.
     *
     * @param index Zero-based index of the array element to be returned.
     * Negative index counts back from the end of the array — if `index` < 0, index + `array.length()` is accessed.
     * @returns The element in the array matching the given index.
     * Returns undefined if `index` < `-length()` or `index` >= `length()`.
     */
    public override at(index: number): T | undefined {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
            this.meta_.addRef(String(index as Object | undefined | null));
        }
        return this.store_.at(index);
    }

    /**
     * Takes an integer value and returns the item at that index,
     * allowing for positive and negative integers. Negative integers count back
     * from the last item in the array.
     *
     * @param index Zero-based index of the array element to be returned.
     * Negative index counts back from the end of the array — if `index` < 0, index + `array.length()` is accessed.
     * @returns The element in the array matching the given index.
     * Returns undefined if `index` < `-length()` or `index` >= `length()`.
     */
    public override at(index: int): T | undefined {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
            this.meta_.addRef(String(index as Object | undefined | null));
        }
        return this.store_.at(index);
    }

    /**
     * Makes a shallow copy of the Array part to another location in the same Array and returns it without modifying its length.
     *
     * @param target index at which to copy the sequence
     * @param start index at which to start copying elements from
     * @param end index at which to end copying elements from
     * @returns this array after transformation
     */
    public override copyWithin(target: number, start: number, end?: Number): this {
        this.store_.copyWithin(target, start, end);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);
        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('copyWithin');

        return this;
    }

    /**
     * Makes a shallow copy of the Array part to another location in the same Array and returns it without modifying its length.
     *
     * @param target index at which to copy the sequence
     * @param start index at which to start copying elements from
     * @param end index at which to end copying elements from
     * @returns this array after transformation
     */
    public copyWithin(target: int, start: int, end: int): this {
        this.store_.copyWithin(target, start, end);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('copyWithin');

        return this;
    }

    /**
     * Makes a shallow copy of the Array part to another location in the same Array and returns it without modifying its length.
     *
     * @param target index at which to copy the sequence
     * @param start index at which to start copying elements from
     * @returns this array after transformation
     */
    public override copyWithin(target: int, start: int): this {
        this.store_.copyWithin(target, start);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('copyWithin');

        return this;
    }

    /**
     * Makes a shallow copy of the Array part to another location in the same Array and returns it without modifying its length.
     *
     * @param target index at which to copy the sequence
     * @returns this array after transformation
     */
    public override copyWithin(target: int): this {
        this.store_.copyWithin(target);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('copyWithin');

        return this;
    }

    /**
     * Changes all elements in the Array to a static value, from a start index to an end index
     *
     * @param value to fill the array with
     * @param start index at which to start filling
     * @param end index at which to end filling, but not including
     * @returns this array after transformation
     */
    public override fill(value: T, start?: Number, end?: Number): this {
        this.store_.fill(value, start, end);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('fill');

        return this;
    }

    /**
     * Changes all elements in the Array to a static value, from a start index to an end index
     *
     * @param value to fill the array with
     * @param start index at which to start filling
     * @param end index at which to end filling, but not including
     * @returns this array after transformation
     */
    public override fill(value: T, start: int, end: int): this {
        this.store_.fill(value, start, end);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('fill');

        return this;
    }

    /**
     * Returns the value of the first element in the array where predicate is true, and undefined
     * otherwise.
     *
     * @param predicate find calls predicate once for each element of the array, in ascending
     * order, until it finds one where predicate returns true. If such an element is found, find
     * immediately returns that element value. Otherwise, find returns undefined.
     * @returns the value of the first element in the array or undefined
     */
    public override find(predicate: (value: T, index: number, array: Array<T>) => boolean): T | undefined {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.find(predicate);
    }

    /**
     * Returns the index of the first element in the array where predicate is true, and -1
     * otherwise.
     *
     * @param predicate find calls predicate once for each element of the array, in ascending
     * order, until it finds one where predicate returns true. If such an element is found,
     * findIndex immediately returns that element index. Otherwise, findIndex returns -1.
     * @returns found element index or -1 otherwise
     */
    public override findIndex(predicate: (value: T, index: number, array: Array<T>) => boolean): number {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.findIndex(predicate);
    }

    /**
     * Iterates the array in reverse order and returns the value of the first element
     * that satisfies the provided testing function
     *
     * @param predicate testing function
     * @returns found element or undefined otherwise
     */
    public override findLast(predicate: (elem: T, index: number, array: Array<T>) => boolean): T | undefined {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.findLast(predicate);
    }

    /**
     * Determines whether all the members of an array satisfy the specified test.
     *
     * @param predicate A function that accepts up to three arguments. The every method calls
     * the predicate function for each element in the array until the predicate returns a value
     * which is coercible to the Boolean value false, or until the end of the array.
     * @returns `true` if `predicate` returns a `true` value for every array element. Otherwise, `false`.
     */
    public override every(predicate: (value: T, index: number, array: Array<T>) => boolean): boolean {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.every(predicate);
    }

    /**
     * Determines whether the specified callback function returns true for any element of an array.
     *
     * @param predicate A function that accepts up to three arguments. The some method calls
     * the predicate function for each element in the array until the predicate returns a value
     * which is coercible to the Boolean value true, or until the end of the array.
     * @returns `true` if `predicate` returns a `true` value for at least one array element. Otherwise, `false`.
     */
    public override some(predicate: (value: T, index: number, array: Array<T>) => boolean): boolean {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.some(predicate);
    }

    /**
     * Iterates the array in reverse order and returns the index of
     * the first element that satisfies the provided testing function.
     * If no elements satisfy the testing function, -1 is returned.
     *
     * @param predicate testing function
     * @returns index of first element satisfying to predicate, -1 if no such element
     */
    public override findLastIndex(predicate: (element: T, index: number, array: Array<T>) => boolean): number {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.findLastIndex(predicate);
    }

    /**
     * Calls the specified callback function for all the elements in an array. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduce method calls the callbackfn function one time for each element in the array.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduce(callbackfn: (previousValue: T, currentValue: T, index: number, array: Array<T>) => T): T {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.reduce(callbackfn);
    }

    /**
     * Calls the specified callback function for all the elements in an array. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduce method calls the callbackfn function one time for each element in the array.
     * @param initialValue If initialValue is specified, it is used as the initial value to start the accumulation. The first call to the callbackfn function provides this value as an argument instead of an array value.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduce<U = T>(
        callbackfn: (previousValue: U, currentValue: T, index: number, array: Array<T>) => U,
        initialValue: U
    ): U {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.reduce<U>(callbackfn, initialValue);
    }

    /**
     * Calls the specified callback function for all the elements in an array, in descending order. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduceRight method calls the callbackfn function one time for each element in the array.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduceRight(
        callbackfn: (previousValue: T, currentValue: T, index: number, array: Array<T>) => T
    ): T {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.reduceRight(callbackfn);
    }

    /**
     * Calls the specified callback function for all the elements in an array, in descending order. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduceRight method calls the callbackfn function one time for each element in the array.
     * @param initialValue If initialValue is specified, it is used as the initial value to start the accumulation. The first call to the callbackfn function provides this value as an argument instead of an array value.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduceRight<U>(
        callbackfn: (previousValue: U, currentValue: T, index: number, array: Array<T>) => U,
        initialValue: U
    ): U {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.reduceRight(callbackfn, initialValue);
    }

    /**
     * Performs the specified action for each element in an array.
     *
     * @param callbackfn A function that accepts up to three arguments. forEach calls the callbackfn function one time for each element in the array.
     */
    public override forEach(callbackfn: (value: T, index: number, array: Array<T>) => void): void {
        // same V2, forEach triggers this addRef!
        const shouldAddRef = this.shouldAddRef();
        if (shouldAddRef) {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        // Similar to V2!
        const observedCb = (value: T, index: number, array: Array<T>) => {
            if (shouldAddRef) {
                this.meta_.addRef(String(index as Object | undefined | null));
            }
            callbackfn(value, index, array);
        };
        return this.store_.forEach(observedCb);
    }

    /**
     * Creates a new `Array` object and populates it with elements of `this` instance of `Array` class
     * selected from `start` to `end` (`end` not included) where `start` and `end` represent the index of items in that array.
     *
     * @param start zero-based index at which to start extraction
     * @param end zero-based index at which to end extraction. `slice()` extracts up to but not including end.
     * @returns `Array` instance, constructed from extracted elements of `this` instance.
     */
    public override slice(start?: Number, end?: Number): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.slice(start, end);
    }

    /**
     * Creates a new `Array` object and populates it with elements of `this` instance of `Array` class
     * selected from `start` to `end` (`end` not included) where `start` and `end` represent the index of items in that array.
     *
     * @param start zero-based index at which to start extraction
     * @param end zero-based index at which to end extraction. `slice()` extracts up to but not including end.
     * @returns `Array` instance, constructed from extracted elements of `this` instance.
     */
    public override slice(start: int, end: int): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.slice(start, end);
    }

    /**
     * Creates a new `Array` object and populates it with elements of `this` instance of `Array` class
     * selected from `start` to `Int.MAX_VALUE`, which means 'to the end of an array'.
     *
     * @param start zero-based index at which to start extraction
     * @returns `Array` instance, constructed from extracted elements of `this` instance.
     */
    public override slice(start: int): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.slice(start);
    }

    /**
     * Returns the last index at which a given element can be found in the array,
     * or -1 if it is not present. The array is searched backwards, starting at fromIndex.
     *
     * @param searchElement element to locate in the array.
     * @param fromIndex zero-based index at which to start searching backwards.
     * Negative index counts back from the end of the array — if `fromIndex` < 0, `fromIndex` + `length()` is used.
     * If `fromIndex` < `-length()`, the array is not searched and -1 is returned.
     * If `fromIndex` >= `length()` then `array.length - 1` is used, causing the entire array to be searched.
     * If `fromIndex` is undefined then `fromIndex = 0`.
     * If `fromIndex` is ommited then `fromIndex = length()-1`.
     * @returns The last index of the element in the array; -1 if not found.
     */
    public override lastIndexOf(searchElement: T, fromIndex: int): int {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.lastIndexOf(searchElement, fromIndex);
    }

    /**
     * Returns the last index at which a given element can be found in the array,
     * or -1 if it is not present. The array is searched backwards, starting at fromIndex.
     *
     * @param searchElement element to locate in the array.
     * @param fromIndex zero-based index at which to start searching backwards.
     * Negative index counts back from the end of the array — if `fromIndex` < 0, `fromIndex` + `length()` is used.
     * If `fromIndex` < `-length()`, the array is not searched and -1 is returned.
     * If `fromIndex` >= `length()` then `array.length - 1` is used, causing the entire array to be searched.
     * If `fromIndex` is undefined then `fromIndex = 0`.
     * If `fromIndex` is ommited then `fromIndex = length()-1`.
     * @returns The last index of the element in the array; -1 if not found.
     */
    public override lastIndexOf(searchElement: T, fromIndex: number | undefined): number {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.lastIndexOf(searchElement, fromIndex);
    }

    /**
     * Creates and returns a new string by concatenating all of the elements in an `Array`,
     * separated by a specified separator string.
     * If the array has only one item, then that item will be returned without using the separator.
     *
     * @param sep specifies a separator
     * @returns A string with all array elements joined. If `length()` is 0, the empty string is returned.
     */
    public override join(sep?: String): string {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.join(sep);
    }

    /**
     * Returns a string representing the specified array and its elements.
     *
     * @returns string representation
     */
    public override toString(): string {
        return this.join(',');
    }

    /**
     * Returns a locale string representing the specified array and its elements.
     *
     * @param locales
     * @param options
     * @returns string representation
     */
    public override toLocaleString(locales: Object, options: Object): string {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toLocaleString(locales, options);
    }

    /**
     * Returns a locale string representing the specified array and its elements.
     *
     * @param options
     * @returns string representation
     */
    public override toLocaleString(locales: Object): string {
        return this.toLocaleString(new Object(), new Object());
    }

    /**
     * Returns a locale string representing the specified array and its elements.
     *
     * @returns string representation
     */
    public override toLocaleString(): string {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toLocaleString();
    }

    /**
     * Copying version of the splice() method.
     *
     * @param start index
     * @param delete number of items after start index
     * @returns a new Array with some elements removed and/or replaced at a given index.
     */
    public override toSpliced(start?: Number, deleteIdx?: Number): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toSpliced(start, deleteIdx);
    }

    /**
     * Copying version of the splice() method.
     *
     * @param start index
     * @returns a new Array with some elements removed and/or replaced at a given index.
     */
    public override toSpliced(start: int): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toSpliced(start);
    }

    /**
     * Checks whether an Array includes a certain value among its entries,
     * returning true or false as appropriate.
     *
     * @param val value to search
     * @param fromIndex start index
     * @returns true if val is in Array
     */
    public override includes(val: T, fromIndex?: Number): boolean {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.includes(val, fromIndex);
    }

    /**
     * Returns the first index at which a given element
     * can be found in the array, or -1 if it is not present.
     *
     * @param val value to search
     * @param fromIndex index to search from
     * @returns index of val, -1 otherwise
     */
    public override indexOf(val: T, fromIndex: int): int {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.indexOf(val, fromIndex);
    }

    /**
     * Returns the first index at which a given element
     * can be found in the array, or -1 if it is not present.
     *
     * @param val value to search
     * @param fromIndex index to search from
     * @returns index of val, -1 otherwise
     */
    public override indexOf(val: T, fromIndex?: Number): number {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.indexOf(val, fromIndex);
    }

    /**
     * Copying version of the sort() method.
     * It returns a new array with the elements sorted in ascending order.
     *
     * @returns sorted copy of hte current instance using default comparator
     */
    public override toSorted(): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toSorted();
    }

    /**
     * Copying version of the sort() method.
     * It returns a new array with the elements sorted in ascending order.
     *
     * @param comparator function to compare to elements of the Array
     * @returns sorted copy of the current instance comparator
     */
    public override toSorted(comparator: (a: T, b: T) => number): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toSorted(comparator);
    }

    /**
     * Modifies `this` instance of `Array` class and populates
     * it with same elements ordered towards the direction opposite to that previously stated.
     *
     * @note Mutating method
     */
    public override reverse(): this {
        this.store_.reverse();
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('reverse');

        return this; // WrappedArray
    }

    /**
     * Copying version of the reverse() method.
     * It returns a new array with the elements in reversed order.
     *
     * @returns reversed copy of the current Array
     */
    public override toReversed(): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.toReversed();
    }

    /**
     * Copying version of using the bracket notation to change the value of a given index.
     * It returns a new Array with the element at the given index replaced with the given value.
     *
     * @param index to replace
     * @param value new value
     * @returns a new Array with the element at the given index replaced with the given value
     */
    public override with(index: number, value: T): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.with(index, value);
    }

    /**
     * Copying version of using the bracket notation to change the value of a given index.
     * It returns a new Array with the element at the given index replaced with the given value.
     *
     * @param index to replace
     * @param value new value
     * @returns a new Array with the element at the given index replaced with the given value
     */
    public override with(index: int, value: T): Array<T> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.with(index, value);
    }

    /**
     * Returns an iterator over all values
     */
    public override values(): IterableIterator<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return this.store_.values();
    }

    /**
     * Returns an iterable of key, value pairs for every entry in the array
     */
    public override entries(): IterableIterator<[number, T]> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.entries();
    }

    /**
     * Calls a defined callback function on each element of an array, and returns an array that contains the results.
     *
     * @param callbackfn A function that accepts up to three arguments. The map method calls the callbackfn function one time for each element in the array.
     * @returns `Array` instance, constructed from `this` and given function.
     */
    public override map<U>(callbackfn: (value: T, index: number, array: Array<T>) => U): Array<U> {
        if (this.shouldAddRef()) {
            this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        }
        return this.store_.map<U>(callbackfn);
    }
}
