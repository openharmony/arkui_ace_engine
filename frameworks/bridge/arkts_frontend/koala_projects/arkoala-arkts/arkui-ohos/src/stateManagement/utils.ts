/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

import { uiUtils } from './base/uiUtilsImpl';
import { MonitorFunctionDecorator } from './decoratorImpl/decoratorMonitor';
import { ExtendableComponent } from '../component/extendableComponent';
import { BusinessError } from '@ohos.base';
import { canBeObserved as canBeObservedImpl } from './tools/stateMgmtDFX';
import { CustomComponentV2, CustomComponentLifecycle } from '@component/customComponent';
import {
  IMonitor,
  IMonitorDecoratedVariable,
  IMonitorPathInfo,
  IVariableOwner,
  IMutableKeyedStateMeta,
  IObservedObject,
  ISubscribedWatches,
  RenderIdType,
  WatchIdType,
  STATE_MGMT_FACTORY,
  IMutableStateMeta
} from './decorator';
import { SubscribedWatches } from './decoratorImpl/decoratorWatch';
import { FactoryInternal } from './base/iFactoryInternal';
import { ObservedBuiltIn } from './base/observeWrappedBase';

final class CONSTANT {
    public static readonly OB_ARRAY_ANY_KEY = '__OB_ANY_INDEX';
    public static readonly OB_SET_ANY_PROPERTY = '__OB_ANY_PROPERTY';
    public static readonly OB_MAP_ANY_PROPERTY = '__OB_ANY_PROPERTY';
    public static readonly OB_LENGTH = '__OB_LENGTH';
}

export interface ElementInfo {
    elementName: string;
    elementId: int;
}

export interface DecoratorInfo {
    decoratorName: string;
    stateVariableName: string;
    owningComponentOrClassName: string;
    owningComponentId: int;
    dependentInfo: Array<ElementInfo>;
}

export interface ObservedResult {
    isObserved: boolean;
    reason: string;
    decoratorInfo: Array<DecoratorInfo>;
}

export class UIUtils {
    static makeObserved<T extends object | null | undefined>(source: T): T {
        return uiUtils.makeObserved(source, true) as T;
    }
    static makeObserved<T extends object | null | undefined>(source: T, allowDeep: boolean): T {
        return uiUtils.makeObserved(source, allowDeep) as T;
    }
    static getTarget<T extends Object>(source: T): T {
        return uiUtils.getTarget(source) as T;
    }
    static makeBinding<T>(getter: () => T): Binding<T> {
        return uiUtils.makeBindingReadonly(getter);
    }
    static makeBinding<T>(getter: () => T, setter: (newValue: T) => void): MutableBinding<T> {
        return uiUtils.makeBindingMutable(getter, setter);
    }

    /**
     * Check if an object can be observed by the state management framework.
     * This is the public API for DFX debugging purposes.
     *
     * @param obj The object to check
     * @returns ObservedResult containing observation status and related information
     */
    static canBeObserved(obj: Object): ObservedResult {
        return canBeObservedImpl(obj);
    }

    private static readonly DEFAULT_PATH: string = 'MONITOR_';
    private static readonly DEFAULT_INDEX = 0;
    private static currentIndex_ = UIUtils.DEFAULT_INDEX;

    static addMonitor(valueCallback: (() => Any) | Array<() => Any>, monitorCallback: (m: IMonitor) => void, options?: MonitorOptions): IMonitorDecoratedVariable {
        if (options?.owner && !(options?.owner instanceof CustomComponentV2)) {
            const errorCode: Int = 130000;
            const errorMessage: string = 'options.owner is not a component decorated with @ComponentV2 which is not supported by UIUtils.addMonitor.';
            throw new BusinessError(errorCode, new Error(errorMessage));
        }

        const callbackArray = UIUtils.unionToArray(valueCallback);
        const pathArray = UIUtils.pathToArray(options?.path);
        const pathLambda = UIUtils.generatePathLambda(callbackArray, pathArray);

        return new MonitorFunctionDecorator(pathLambda, monitorCallback, options?.owner, options?.isSynchronous);
    }

    static clearMonitor(monitor: IMonitorDecoratedVariable): void {
        (monitor as MonitorFunctionDecorator).unbindAllInternalValues();
    }

    /**
     * Get lifecycle instance of IVariableOwner
     *
     * @param {IVariableOwner} source - Variable owner instance
     * @returns lifecycle instance
     */
    static getLifecycle<T extends IVariableOwner>(customComponent: T): CustomComponentLifecycle {
        return customComponent.__getLifecycle__Internal();
    }

      /**
   * Get the custom component context.
   *
   * @param { T } customComponent - custom component instance
   * @returns { CustomComponentContext } The lifecycle that the custom component belongs to.
   * @static
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0 static
   */
  static getCustomComponentContext<T extends IVariableOwner>(customComponent: T): CustomComponentContext {
    return customComponent.__getCustomComponentContext__Internal();
  }

    private static pathToArray(path?: string | string[]): string[] {
        if (!path) {
            return [];
        }

        return UIUtils.unionToArray(path);
    }

    private static unionToArray<T>(input: T | T[]): T[] {
        if (Array.isArray(input)) {
            return input as T[];
        } else {
            return [input as T];
        }
    }

    private static createPathInfo(callback: () => Any, path?: string): IMonitorPathInfo {
        return {
            path: path ?? '',
            valueCallback: callback
        };
    }

    private static generatePathLambda(callbacks: (() => Any)[], paths?: string[]): IMonitorPathInfo[] {
        return callbacks.map((callback: () => Any, index: int): IMonitorPathInfo => {
            const currentPath: string = !paths || index >= paths.length
                ? `${UIUtils.DEFAULT_PATH}${UIUtils.currentIndex_++}`
                : paths[index];

            return UIUtils.createPathInfo(callback, currentPath);
        });
    }
}

export interface MonitorBaseOptions {
    isSynchronous?: boolean;
    owner?: IVariableOwner;
}

export interface MonitorOptions {
    isSynchronous?: boolean;
    owner?: IVariableOwner;
    path?: string | string[];
}

/**
 * Generic Binding class to encapsulate read-only data binding.
 *
 * @template T - The type of the value to be bound.
*/
export class Binding<T> {
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

    get getter(): () => T {
        return this.getter_;
    }
}

/**
 * Generic MutableBinding class to encapsulate both read and write operations.
 *
 * @template T - The type of the value to be bound.
 */
export class MutableBinding<T> {
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

    get getter(): () => T {
        return this.getter_;
    }

    get setter(): (newValue: T) => void {
        return this.setter_;
    }
}

/**
 * CustomComponentContext is a state management tool for operating the observed data.
 *
 * @interface
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0 static
 */
export interface CustomComponentContext {
/**
 * Register active and inactive callback.
 *
 * @param { ActiveAndInactiveCallbackType } [active] - active function callback.
 * @param { ActiveAndInactiveCallbackType } [inactive] - inactive function callback.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0 static
 */
registerActiveAndInactiveCallback(active?: ActiveAndInactiveCallbackType,
  inactive?: ActiveAndInactiveCallbackType): void;
}

 /**
 * Defines active and inactive function callback.
 *
 * @typedef { function }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0 static
 */
export type ActiveAndInactiveCallbackType = () => void;

export class ObservedArray<T> extends Array<T> implements IObservedObject, ObservedBuiltIn, ISubscribedWatches {
    @JSONStringifyIgnore
    private meta_: IMutableKeyedStateMeta = FactoryInternal.mkMutableKeyedStateMeta(
        'One-layer Observation' + 'ObservedArray', this);
    // support for @Watch
    // each IObservedObject manages a set of @Wtch subscribers
    // when a object property changes need to call execureOnSubscribingWatches
    // compare interface
    @JSONStringifyIgnore
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();

    constructor() {
        super();
    }

    constructor(first: T, ...d: T[]) {
        super(first, ...d);
    }

    constructor(arrayLen: int, initializer: (index: int) => T) {
        super(arrayLen, initializer);
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

    public setV1RenderId(renderId: RenderIdType): void {}

    override get length(): int {
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.length;
    }

    override set length(newLen: int) {
        const len = super.length;
        if (len !== newLen) {
            super.length = newLen;
            // the Array implementation actually changed the length!
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

            // exec all subscribing @Watch
            this.executeOnSubscribingWatches('length');
        }
    }

    // [] operator
    public override $_get(idx: int): T {
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        this.meta_.addRef(String(idx as Object | undefined | null));
        return super.$_get(idx);
    }

    // [] operator
    public override $_set(idx: int, val: T): void {
        const orig = super.$_get(idx);
        super.$_set(idx, val);
        if (orig !== super.$_get(idx)) {
            this.meta_.fireChange(String(idx as Object | undefined | null));
            this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

            // exec all subscribing @Watch functions
            this.executeOnSubscribingWatches(String(idx as Object | undefined | null));
        }
    }

    /**
     * Extends Array with new elements to specified length.
     *
     * @param arrayLength amount of new added elements.
     * @param initialValue initial value of new elements.
     */
    public override extendTo(arrayLength: int, initialValue: T): void {
        super.extendTo(arrayLength, initialValue);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);
        this.executeOnSubscribingWatches('extendTo');
    }

    /**
     * Shrinks Array to specified length.
     *
     * @param arrayLength length at which to shrink.
     */
    public override shrinkTo(arrayLength: int): void {
        super.shrinkTo(arrayLength);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);
        this.executeOnSubscribingWatches('shrinkTo');
    }

    /**
     * Reorders elements of `this` using comparator function.
     *
     * @param comparator function that defines the sort order.
     * @note Mutating method
     */
    public override sort(comparator?: (a: T, b: T) => int): this {
        super.sort(comparator);
        // We do not need to fire length change
        // the length does not change here, closing fireChange on CONSTANT.OB_LENGTH
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
        const ret = super.shift();
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
        const ret = super.pop();
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
    public override pushArray(...val: T[]): int {
        const ret = super.push(...val);
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
    public override pushOne(val: T): int {
        const ret = super.push(val);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('push');

        return ret;
    }

    public push(...val: T[]): int {
        return this.pushArray(...val);
    }

    overload push { push, pushOne, pushArray }

    /**
     * Changes the contents of an array by removing or replacing existing elements
     * and/or adding new elements in place.
     *
     * @param start index
     * @param delete number of items after start index
     * @returns an Array with deleted elements
     */
    public override splice(start: int, deleteIdx: int | undefined, ...items: T[]): Array<T> {
        const ret = super.splice(start, deleteIdx, ...items);
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
        const ret = super.splice(start);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('splice');

        return ret;
    }

    /**
     * Adds the specified elements to the beginning of an Array
     * and returns the new length of the Array.
     *
     * @param values data to be added
     * @returns new length of the Array
     */
    public override unshift(...values: T[]): int {
        const ret = super.unshift(...values);
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('unshift');

        return ret;
    }

    /**
     * Returns an iterator over all indices
     */
    public override keys(): IterableIterator<int> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.keys();
    }

    /**
     * Returns an iterator over all values
     */
    public override $_iterator(): IterableIterator<T> {
        // NOTE! addRef for OB_LENGTH similarly to V2!
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.values();
    }

    /**
     * Returns the elements of an array that meet the condition specified in a callback function.
     *
     * @param predicate A function that accepts up to three arguments. The filter method calls the predicate function one time for each element in the array.
     * @returns New `Array` instance constructed from `this` with elements filtered using test function `predicate`.
     */
    public override filter(predicate: (value: T, index: int, array: Array<T>) => boolean): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.filter(predicate);
    }

    /**
     * Creates a new Array with all sub-array elements concatenated
     * into it recursively up to the specified depth.
     *
     * @param depth
     * @returns a flattened Array with respect to depth
     */
    public override flat<U>(depth: int): Array<U> {
        return super.flat<U>(depth);
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
    public override flatMap<U>(fn: (v: T, k: int, arr: Array<T>) => U | ReadonlyArray<U>): Array<U> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.flatMap(fn);
    }

    /**
     * Takes an integer value and returns the item at that index,
     * allowing for positive and negative integers. Negative integers count back
     * from the last item in the array.
     *
     * @param index Zero-based index of the array element to be returned.
     * Negative index counts back from the end of the array — if `index` < 0, index + `array.length()` is accessed.
     * @returns The element in the array matching the given index.
     * Throw range error if `index` < `-length()` or `index` >= `length()`.
     */
    public override at(index: int): T {
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        this.meta_.addRef(String(index as Object | undefined | null));
        return super.at(index);
    }

    /**
     * Makes a shallow copy of the Array part to another location in the same Array and returns it without modifying its length.
     *
     * @param target index at which to copy the sequence
     * @param start index at which to start copying elements from
     * @param end index at which to end copying elements from
     * @returns this array after transformation
     */
    public override copyWithin(target: int, start: int, end?: int): this {
        super.copyWithin(target, start, end);
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
        super.copyWithin(target, start);
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
        super.copyWithin(target);
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
    public override fill(value: T, start?: int, end?: int): this {
        super.fill(value, start, end);
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
    public override find(predicate: (value: T, index: int, array: Array<T>) => boolean): T | undefined {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.find(predicate);
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
    public override findIndex(predicate: (value: T, index: int, array: Array<T>) => boolean): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.findIndex(predicate);
    }

    /**
     * Iterates the array in reverse order and returns the value of the first element
     * that satisfies the provided testing function
     *
     * @param predicate testing function
     * @returns found element or undefined otherwise
     */
    public override findLast(predicate: (elem: T, index: int, array: Array<T>) => boolean): T | undefined {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.findLast(predicate);
    }

    /**
     * Determines whether all the members of an array satisfy the specified test.
     *
     * @param predicate A function that accepts up to three arguments. The every method calls
     * the predicate function for each element in the array until the predicate returns a value
     * which is coercible to the Boolean value false, or until the end of the array.
     * @returns `true` if `predicate` returns a `true` value for every array element. Otherwise, `false`.
     */
    public override every(predicate: (value: T, index: int, array: Array<T>) => boolean): boolean {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.every(predicate);
    }

    /**
     * Determines whether the specified callback function returns true for any element of an array.
     *
     * @param predicate A function that accepts up to three arguments. The some method calls
     * the predicate function for each element in the array until the predicate returns a value
     * which is coercible to the Boolean value true, or until the end of the array.
     * @returns `true` if `predicate` returns a `true` value for at least one array element. Otherwise, `false`.
     */
    public override some(predicate: (value: T, index: int, array: Array<T>) => boolean): boolean {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.some(predicate);
    }

    /**
     * Iterates the array in reverse order and returns the index of
     * the first element that satisfies the provided testing function.
     * If no elements satisfy the testing function, -1 is returned.
     *
     * @param predicate testing function
     * @returns index of first element satisfying to predicate, -1 if no such element
     */
    public override findLastIndex(predicate: (element: T, index: int, array: Array<T>) => boolean): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.findLastIndex(predicate);
    }

    /**
     * Calls the specified callback function for all the elements in an array. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduce method calls the callbackfn function one time for each element in the array.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduce(callbackfn: (previousValue: T, currentValue: T, index: int, array: Array<T>) => T): T {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.reduce(callbackfn);
    }

    /**
     * Calls the specified callback function for all the elements in an array. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduce method calls the callbackfn function one time for each element in the array.
     * @param initialValue If initialValue is specified, it is used as the initial value to start the accumulation. The first call to the callbackfn function provides this value as an argument instead of an array value.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduce<U = T>(
        callbackfn: (previousValue: U, currentValue: T, index: int, array: Array<T>) => U,
        initialValue: U
    ): U {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.reduce<U>(callbackfn, initialValue);
    }

    /**
     * Calls the specified callback function for all the elements in an array, in descending order. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduceRight method calls the callbackfn function one time for each element in the array.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduceRight(
        callbackfn: (previousValue: T, currentValue: T, index: int, array: Array<T>) => T
    ): T {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.reduceRight(callbackfn);
    }

    /**
     * Calls the specified callback function for all the elements in an array, in descending order. The return value of the callback function is the accumulated result, and is provided as an argument in the next call to the callback function.
     *
     * @param callbackfn A function that accepts up to four arguments. The reduceRight method calls the callbackfn function one time for each element in the array.
     * @param initialValue If initialValue is specified, it is used as the initial value to start the accumulation. The first call to the callbackfn function provides this value as an argument instead of an array value.
     * @returns a result after applying callbackfn over all elements of the Array
     */
    public override reduceRight<U>(
        callbackfn: (previousValue: U, currentValue: T, index: int, array: Array<T>) => U,
        initialValue: U
    ): U {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.reduceRight(callbackfn, initialValue);
    }

    /**
     * Performs the specified action for each element in an array.
     *
     * @param callbackfn A function that accepts up to three arguments. forEach calls the callbackfn function one time for each element in the array.
     */
    public override forEach(callbackfn: (value: T, index: int, array: Array<T>) => void): void {
        // same V2, forEach triggers this addRef!
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        // Similar to V2!
        const observedCb = (value: T, index: int, array: Array<T>) => {
            this.meta_.addRef(String(index as Object | undefined | null));
            callbackfn(value, index, array);
        };
        return super.forEach(observedCb);
    }

    /**
     * Creates a new `Array` object and populates it with elements of `this` instance of `Array` class
     * selected from `start` to `end` (`end` not included) where `start` and `end` represent the index of items in that array.
     *
     * @param start zero-based index at which to start extraction
     * @param end zero-based index at which to end extraction. `slice()` extracts up to but not including end.
     * @returns `Array` instance, constructed from extracted elements of `this` instance.
     */
    public override slice(start?: int, end?: int): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.slice(start, end);
    }

    /**
     * Creates a new `Array` object and populates it with elements of `this` instance of `Array` class
     * selected from `start` to `Int.MAX_VALUE`, which means 'to the end of an array'.
     *
     * @param start zero-based index at which to start extraction
     * @returns `Array` instance, constructed from extracted elements of `this` instance.
     */
    public override slice(start: int): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.slice(start);
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
    public override lastIndexOf(searchElement: T, fromIndex?: int): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.lastIndexOf(searchElement, fromIndex);
    }

    public override lastIndexOf(searchElement: T): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.lastIndexOf(searchElement);
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
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.join(sep);
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
    public override toLocaleString(locales?: Intl.LocalesArgument, options?: object): string {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toLocaleString(locales, options);
    }

    /**
     * Copying version of the splice() method.
     *
     * @param start index
     * @param delete number of items after start index
     * @returns a new Array with some elements removed and/or replaced at a given index.
     */
    public override toSpliced(start?: int, deleteIdx?: int): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toSpliced(start, deleteIdx);
    }

    public override toSpliced(start: int, delete: int, ...items: FixedArray<T>): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toSpliced(start, delete, ...items);
    }

    /**
     * Copying version of the splice() method.
     *
     * @param start index
     * @returns a new Array with some elements removed and/or replaced at a given index.
     */
    public override toSpliced(start: int): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toSpliced(start);
    }

    /**
     * Checks whether an Array includes a certain value among its entries,
     * returning true or false as appropriate.
     *
     * @param val value to search
     * @param fromIndex start index
     * @returns true if val is in Array
     */
    public override includes(val: T, fromIndex?: int): boolean {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.includes(val, fromIndex);
    }

    /**
     * Returns the first index at which a given element
     * can be found in the array, or -1 if it is not present.
     *
     * @param val value to search
     * @param fromIndex index to search from
     * @returns index of val, -1 otherwise
     */
    public override indexOf(val: T, fromIndex?: int): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.indexOf(val, fromIndex);
    }

    public override indexOf(val: T): int {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.indexOf(val);
    }

    /**
     * Copying version of the sort() method.
     * It returns a new array with the elements sorted in ascending order.
     *
     * @returns sorted copy of hte current instance using default comparator
     */
    public override toSorted(): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toSorted();
    }

    /**
     * Copying version of the sort() method.
     * It returns a new array with the elements sorted in ascending order.
     *
     * @param comparator function to compare to elements of the Array
     * @returns sorted copy of the current instance comparator
     */
    public override toSorted(comparator: (a: T, b: T) => int): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toSorted(comparator);
    }

    /**
     * Modifies `this` instance of `Array` class and populates
     * it with same elements ordered towards the direction opposite to that previously stated.
     *
     * @note Mutating method
     */
    public override reverse(): this {
        super.reverse();
        this.meta_.fireChange(CONSTANT.OB_LENGTH);
        this.meta_.fireChange(CONSTANT.OB_ARRAY_ANY_KEY);

        // exec all subscribing @Watch
        this.executeOnSubscribingWatches('reverse');

        return this; // ObservedArray
    }

    /**
     * Copying version of the reverse() method.
     * It returns a new array with the elements in reversed order.
     *
     * @returns reversed copy of the current Array
     */
    public override toReversed(): Array<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.toReversed();
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
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.with(index, value);
    }

    /**
     * Returns an iterator over all values
     */
    public override values(): IterableIterator<T> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.values();
    }

    /**
     * Returns an iterable of key, value pairs for every entry in the array
     */
    public override entries(): IterableIterator<[int, T]> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.entries();
    }

    /**
     * Calls a defined callback function on each element of an array, and returns an array that contains the results.
     *
     * @param callbackfn A function that accepts up to three arguments. The map method calls the callbackfn function one time for each element in the array.
     * @returns `Array` instance, constructed from `this` and given function.
     */
    public override map<U>(callbackfn: (value: T, index: int, array: Array<T>) => U): Array<U> {
        this.meta_.addRef(CONSTANT.OB_ARRAY_ANY_KEY);
        return super.map<U>(callbackfn);
    }
}

export class ObservedSet<K> extends Set<K> implements IObservedObject, ObservedBuiltIn, ISubscribedWatches {
    // Use public access to enable unit testing.
    @JSONStringifyIgnore
    private meta_: IMutableKeyedStateMeta = FactoryInternal.mkMutableKeyedStateMeta(
        'One-layer Observation' + 'ObservedSet', this);
    // support for @Watch
    // each IObservedObject manages a set of @Watch subscribers
    // when a object property changes need to call executeOnSubscribingWatches
    // compare interface
    @JSONStringifyIgnore
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    /**
     * Constructs a Set from another Set
     * @param set another Set
     */
    constructor() {
        super();
    }

    constructor(bucketsCount: int) {
        super(bucketsCount);
    }

    constructor(set: Set<K>) {
        super(set);
    }

    constructor(values: K[]) {
        super(values);
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

    public setV1RenderId(renderId: RenderIdType): void {}

    public override toString(): String {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        return super.toString();
    }

    /**
     * Puts a value into the Set
     *
     * @param val the value to put into the Set
     * @returns this
     */
    public override add(val: K): this {
        if (!super.has(val)) {
            super.add(val);
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
    public override has(val: K): boolean {
        const has = super.has(val);
        if (has) {
            this.meta_.addRef(String(val as Object | undefined | null));
        } else {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return has;
    }

    /**
     * Returns number of unique elements in the Set
     *
     * @returns number of unique elements in the Set
     */
    public override get size(): int {
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.size;
    }

    /**
     * Removes a value from the Set
     *
     * @param val the value to remove
     */
    public override delete(val: K): boolean {
        if (super.has(val)) {
            const res = super.delete(val);
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
    public override clear(): void {
        if (super.size > 0) {
            super.forEach((_, val) => {
                this.meta_.fireChange(String(val as Object | undefined | null));
            });
            super.clear();
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.meta_.fireChange(CONSTANT.OB_SET_ANY_PROPERTY);
            this.executeOnSubscribingWatches('clear');
        }
    }

    /**
     * Despite name, returns elements from the Set
     * @returns an iterable of the values in the set
     */
    public override keys(): IterableIterator<K> {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.keys();
    }

    /**
     * Returns elements from the Set
     *
     * @returns an iterable of the values in the set
     */
    public override values(): IterableIterator<K> {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.values();
    }

    public override $_iterator(): IterableIterator<K> {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.$_iterator();
    }

    /**
     * @returns an iterable of [v,v] pairs for every value `v` in the set.
     */
    public override entries(): IterableIterator<[K, K]> {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.entries();
    }

    /**
     * Executes a provided function once per each value in the Set object, in insertion order
     *
     * @param callbackfn to apply
     */
    public override forEach(callbackfn: (k: K, v: K, set: Set<K>) => void): void {
        this.meta_.addRef(CONSTANT.OB_SET_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        super.forEach(callbackfn);
    }
}

export class ObservedMap<K, V> extends Map<K, V> implements IObservedObject, ObservedBuiltIn, ISubscribedWatches {
    // Use public access to enable unit testing.
    @JSONStringifyIgnore
    private meta_: IMutableKeyedStateMeta = FactoryInternal.mkMutableKeyedStateMeta(
        'One-layer Observation' + 'ObservedMap', this);
    // support for @Watch
    @JSONStringifyIgnore
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    /**
     * Constructs a Map from another Map
     * @param map another map
     */
    constructor() {
        super();
    }

    constructor(initialCapacity: int) {
        super(initialCapacity);
    }

    constructor(entries: [K, V][]) {
        super(entries);
    }

    constructor(map: Map<K, V>) {
        super(map);
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

    public setV1RenderId(renderId: RenderIdType): void {}

    public override toString(): String {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        return super.toString();
    }

    /**
     * Puts a pair of key and value into the Map
     *
     * @param key the key to put into the Map
     * @param val the value to put into the Map
     */
    public override set(key: K, val: V): this {
        if (!this.meta_) {
            this.meta_ = FactoryInternal.mkMutableKeyedStateMeta(
                'One-layer Observation' + 'ObservedMap', this);
            this.subscribedWatches = new SubscribedWatches();
        }
        if (!super.has(key)) {
            super.set(key, val);
            this.meta_.fireChange(CONSTANT.OB_LENGTH);
            this.executeOnSubscribingWatches('set');
        } else if (super.get(key) !== val) {
            super.set(key, val);
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
        const ret = super.has(key);
        if (ret) {
            this.meta_.addRef(String(key as Object | undefined | null));
        } else {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return ret;
    }

    /**
     * Returns number of Entries with unique keys in the Map
     * @returns number of Entries with unique keys in the Map
     */
    public override get size(): int {
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.size;
    }

    /**
     * Removes an Entry with specified key from the Map
     * @param key the key to remove
     */
    public override delete(key: K): boolean {
        if (super.has(key)) {
            const ret: boolean = super.delete(key);
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
        if (super.size > 0) {
            super.forEach((_, prop) => {
                this.meta_.fireChange(String(prop as Object | undefined | null));
            });
            super.clear();
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
        if (super.has(key)) {
            this.meta_.addRef(String(key as Object | undefined | null));
        } else {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        const value = super.get(key);
        return value;
    }

    /**
     * Returns a value assosiated with key if present, or a default value otherwise
     *
     * @param key the key to find in the Map
     * @param def a value to return if key is not in the Map
     * @returns value if key presents, def otherwise
     */
    public override get(key: K, def: V): V {
        if (super.has(key)) {
            this.meta_.addRef(String(key as Object | undefined | null));
        } else {
            this.meta_.addRef(CONSTANT.OB_LENGTH);
        }
        return super.get(key, def);
    }

    /**
     * Returns elements from the Map as an keys Iterator
     *
     * @returns iterator with map keys
     */
    public override keys(): IterableIterator<K> {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.keys();
    }

    /**
     * Returns elements from the Map as an values Iterator
     *
     * @returns iterator with map values
     */
    public override values(): IterableIterator<V> {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.values();
    }

    public override $_iterator(): IterableIterator<[K, V]> {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.entries();
    }

    /**
     * Returns elements from the Map as an array of Entries
     *
     * @returns an array of Entries
     */
    public override entries(): IterableIterator<[K, V]> {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.entries();
    }

    /**
     * Executes a provided function once per each key/value pair in the Map, in insertion order
     *
     * @param callbackfn to apply
     */
    public override forEach(callbackfn: (v: V, k: K, map: Map<K, V>) => void): void {
        this.meta_.addRef(CONSTANT.OB_MAP_ANY_PROPERTY);
        this.meta_.addRef(CONSTANT.OB_LENGTH);
        return super.forEach(callbackfn);
    }
}

export class ObservedDate extends Date implements IObservedObject, ObservedBuiltIn, ISubscribedWatches {
    @JSONStringifyIgnore
    private meta_: IMutableStateMeta = STATE_MGMT_FACTORY.makeMutableStateMeta(this,
        'One-layer Observation' +'ObservedDate');
    // support for @Watch
    // each IObservedObject manages a set of @Wtch subscribers
    // when a object property changes need to call execureOnSubscribingWatches
    // compare interface
    @JSONStringifyIgnore
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    /**
     * Constructs a Date from another Date
     * @param date another Date
     */
    constructor() {
        super();
    }

    constructor(value: long | string | Date) {
        super(value);
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

    public setV1RenderId(renderId: RenderIdType): void {}

    /**
     * The `isDateValid()` method checks if constructed date is maximum of ±100,000,000
     * (one hundred million) days relative to January 1, 1970 UTC
     * (that is, April 20, 271821 BCE ~ September 13, 275760 CE) can be represented
     * by the standard Date object (equivalent to ±8,640,000,000,000,000 milliseconds).
     */
    public override isDateValid(): boolean {
        this.conditionalAddRef();
        return super.isDateValid();
    }

    /**
     * The `valueOf()` method returns the primitive value of a `Date` object.
     *
     * @see ECMA-262, 21.4.4.44
     * @returns The number of milliseconds between 1 January 1970 00:00:00 UTC and the given date.
     * @throws InvalidDate - Throws if Date object is invalid (@link{isDateValid} is `false`).
     */
    public override valueOf(): long {
        this.conditionalAddRef();
        return super.valueOf();
    }

    /**
     * Gets a string with a language-sensitive representation of the time portion of the date.
     *
     * @returns a language-sensitive representation of the time portion of the date.
     */
    public override toLocaleTimeString(): string {
        this.conditionalAddRef();
        return super.toLocaleTimeString();
    }

    public override toLocaleTimeString(locales?: Intl.LocalesArgument, options?: Intl.DateTimeFormatOptions): string {
        this.conditionalAddRef();
        return super.toLocaleTimeString(locales, options);
    }

    public override toLocaleString(locales?: Intl.LocalesArgument, options?: object): string {
        this.conditionalAddRef();
        return super.toLocaleString(locales, options);
    }

    /**
     * Gets a string with a language-sensitive representation
     * of the date portion of the specified date in the user agent's timezone.
     *
     * @returns a string with a language-sensitive representation
     * of the date portion of the specified date in the user agent's timezone.
     */
    public override toLocaleDateString(): string {
        this.conditionalAddRef();
        return super.toLocaleDateString();
    }

    public override toLocaleDateString(locales?: Intl.LocalesArgument, options?: Intl.DateTimeFormatOptions): string {
        this.conditionalAddRef();
        return super.toLocaleDateString(locales, options);
    }

    /**
     * The `getDate()` method returns the day of the month for the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.2
     * @returns An integer number, between 1 and 31, representing the day of the month for the given date according to local time.
     */
    public override getDate(): int {
        this.conditionalAddRef();
        return super.getDate();
    }

    /**
     * Changes the day of the month of a given Date instance, based on local time.
     *
     * @param value new day.
     */
    public override setDate(value: int): long {
        const result = super.setDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setDate');
        return result;
    }

    /**
     * Returns the day of the month (from 1 to 31) in the specified date according to universal time.
     *
     * @returns An integer number, between 1 and 31, representing the day of the month for the given date according to local time.
     */
    public override getUTCDate(): int {
        this.conditionalAddRef();
        return super.getUTCDate();
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDate(value: int): long {
        const result = super.setUTCDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDate');
        return result;
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDay(value: int): long {
        const result = super.setUTCDay(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDay');
        return result;
    }

    /**
     * Returns the day of the week for the specified date according to local time,
     * where 0 represents Sunday. For the day of the month, see @link{getDayOfMonth}.
     *
     * @see ECMA-262, 21.4.4.3
     * @returns An integer number, between 0 and 6, corresponding to the day of the week
     * for the given date, according to local time: 0 for Sunday, 1 for Monday, 2 for Tuesday, and so on.
     */
    public override getDay(): int {
        this.conditionalAddRef();
        return super.getDay();
    }

    /**
     * Returns the day of the week in the specified date according to universal time, where 0 represents Sunday.
     *
     * @returns An integer number, between 0 and 6, corresponding to the day of the week
     * for the given date, according to local time: 0 for Sunday, 1 for Monday, 2 for Tuesday, and so on.
     */
    public override getUTCDay(): int {
        this.conditionalAddRef();
        return super.getUTCDay();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.4
     * @note This function is an alias to @link{getFullYear} and left for compatibility with ECMA-262.
     * @returns year
     */
    public override getYear(): int {
        this.conditionalAddRef();
        return super.getYear();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @returns A year of the specified date according to local time.
     * @description The value returned by `getUTCFullYear()` is an absolute number.
     * For dates between the years 1000 and 9999, `getUTCFullYear()` returns a four-digit number,
     * for example, 1995. Use this function to make sure a year is compliant with years after 2000.
     * @returns year
     */
    public override getUTCFullYear(): int {
        this.conditionalAddRef();
        return super.getUTCFullYear();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.4
     * @returns A number corresponding to the year of the given date, according to local time.
     * @description The value returned by `getFullYear()` is an absolute number.
     * For dates between the years 1000 and 9999, `getFullYear()` returns a four-digit number,
     * for example, 1995. Use this function to make sure a year is compliant with years after 2000.
     * @example
     * ```ets
     * const today = new Date();
     * const year = today.getYearFull();
     * ```
     */
    public override getFullYear(): int {
        this.conditionalAddRef();
        return super.getFullYear();
    }

    /**
     * Sets the full year for a specified date according to universal time.
     *
     * @param value new year
     */
    public override setUTCFullYear(value: int): long {
        const result = super.setUTCFullYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to universal time.
     *
     * @param value new year
     */
    public override setUTCFullYear(value: int, month: int): long {
        const result = super.setUTCFullYear(value, month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to universal time.
     *
     * @param value new year
     */
    public override setUTCFullYear(value: int, month: int, date: int): long {
        const result = super.setUTCFullYear(value, month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCFullYear');
        return result;
    }

    /**
     * This function is an alias to @link{setFullYear} and left for compatibility with ECMA-262.
     *
     * @param value new year
     */
    public override setYear(value: int): void {
        super.setYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setYear');
    }

    /**
     * Sets the full year for a specified date according to local time.
     *
     * @param value new year
     */
    public override setFullYear(value: int): long {
        const result = super.setFullYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to local time.
     *
     * @param value new year
     */
    public override setFullYear(value: int, month: int): long {
        const result = super.setFullYear(value, month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to local time.
     *
     * @param value new year
     */
    public override setFullYear(value: int, month: int, date: int): long {
        const result = super.setFullYear(value, month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setFullYear');
        return result;
    }

    /**
     * Returns the hour for the specified date, according to local time.
     *
     * @see ECMA-262, 21.4.4.5
     * @returns An integer number, between 0 and 23, representing the hour for the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const hours = today.getHour();
     * ```
     */
    public override getHours(): int {
        this.conditionalAddRef();
        return super.getHours();
    }

    /**
     * Returns the hours in the specified date according to universal time.
     *
     * @returns An integer number, between 0 and 23, representing the hour for the given date according to UTC time.
     */
    public override getUTCHours(): int {
        this.conditionalAddRef();
        return super.getUTCHours();
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: int): long {
        const result = super.setHours(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
        return result;
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: int, min: int): long {
        const result = super.setHours(value, min);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
        return result;
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: int, min: int, sec: int): long {
        const result = super.setHours(value, min, sec);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
        return result;
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: int, min: int, sec: int, ms: int): long {
        const result = super.setHours(value, min, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
        return result;
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: int): long {
        const result = super.setUTCHours(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCHours');
        return result;
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: int, min: int): long {
        const result = super.setUTCHours(value, min);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCHours');
        return result;
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: int, min: int, sec: int): long {
        const result = super.setUTCHours(value, min, sec);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCHours');
        return result;
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: int, min: int, sec: int, ms: int): long {
        const result = super.setUTCHours(value, min, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCHours');
        return result;
    }

    /**
     * Returns the milliseconds in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.6
     * @returns A number between 0 and 999 representing the milliseconds for the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const milliseconds = today.getMilliseconds();
     * ```
     */
    public override getMilliseconds(): int {
        this.conditionalAddRef();
        return super.getMilliseconds();
    }

    /**
     * Returns the milliseconds portion of the time object's value according to universal time.
     *
     * @returns the milliseconds portion of the time object's value according to universal time.
     */
    public override getUTCMilliseconds(): int {
        this.conditionalAddRef();
        return super.getUTCMilliseconds();
    }

    /**
     * Sets the milliseconds for a specified date according to local time.
     *
     * @param value new ms
     */
    public override setMilliseconds(value: int): long {
        const result = super.setMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMilliseconds');
        return result;
    }

    /**
     * Sets the milliseconds for a specified date according to universal time.
     *
     * @param value new ms
     */
    public override setUTCMilliseconds(value: int): long {
        const result = super.setUTCMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMilliseconds');
        return result;
    }

    /**
     * Returns the seconds in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.9
     * @returns An integer number, between 0 and 59, representing the seconds in the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const seconds = today.getSeconds();
     * ```
     */
    public override getSeconds(): int {
        this.conditionalAddRef();
        return super.getSeconds();
    }

    /**
     * Returns the seconds in the specified date according to universal time.
     *
     * @returns the seconds in the specified date according to universal time.
     */
    public override getUTCSeconds(): int {
        this.conditionalAddRef();
        return super.getUTCSeconds();
    }

    /**
     * Sets the seconds for a specified date according to local time.
     *
     * @param value new seconds
     */
    public override setSeconds(value: int): long {
        const result = super.setSeconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setSeconds');
        return result;
    }

    /**
     * Sets the seconds for a specified date according to local time.
     *
     * @param value new seconds
     */
    public override setSeconds(value: int, ms: int): long {
        const result = super.setSeconds(value, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setSeconds');
        return result;
    }

    /**
     * Sets the seconds for a specified date according to universal time.
     *
     * @param value new seconds
     */
    public override setUTCSeconds(value: int): long {
        const result = super.setUTCSeconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCSeconds');
        return result;
    }

    /**
     * Sets the seconds for a specified date according to universal time.
     *
     * @param value new seconds
     */
    public override setUTCSeconds(value: int, ms: int): long {
        const result = super.setUTCSeconds(value, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCSeconds');
        return result;
    }

    /**
     * Returns the minutes in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.7
     * @returns An integer number, between 0 and 59, representing the minutes in the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const minutes = today.getMinutes();
     * ```
     */
    public override getMinutes(): int {
        this.conditionalAddRef();
        return super.getMinutes();
    }

    /**
     * Sets the minutes for a specified date according to universal time.
     *
     * @param value new minutes
     */
    public override setUTCMinutes(value: int): long {
        const result = super.setUTCMinutes(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Sets the minutes for a specified date according to universal time.
     *
     * @param value new minutes
     */
    public override setUTCMinutes(value: int, sec: int): long {
        const result = super.setUTCMinutes(value, sec);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Sets the minutes for a specified date according to universal time.
     *
     * @param value new minutes
     */
    public override setUTCMinutes(value: int, sec: int, ms: int): long {
        const result = super.setUTCMinutes(value, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Returns the minutes in the specified date according to universal time.
     *
     * @returns the minutes in the specified date according to universal time.
     */
    public override getUTCMinutes(): int {
        this.conditionalAddRef();
        return super.getUTCMinutes();
    }

    /**
     * Sets the minutes for a specified date according to local time.
     *
     * @param value new minutes
     */
    public override setMinutes(value: int): long {
        const result = super.setMinutes(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Sets the minutes for a specified date according to local time.
     *
     * @param value new minutes
     */
    public override setMinutes(value: int, sec: int): long {
        const result = super.setMinutes(value, sec);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Sets the minutes for a specified date according to local time.
     *
     * @param value new minutes
     */
    public override setMinutes(value: int, sec: int, ms: int): long {
        const result = super.setMinutes(value, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Returns the month in the specified date according to local time,
     * as a zero-based value (where zero indicates the first month of the year).
     *
     * @see ECMA-262, 21.4.4.8
     * @returns  An integer number, between 0 and 11, representing the month in the given date according to local time.
     * 0 corresponds to January, 1 to February, and so on.
     * @example
     * ```ets
     * const today = new Date();
     * const month = today.getMonth();
     * ```
     */
    public override getMonth(): int {
        this.conditionalAddRef();
        return super.getMonth();
    }

    /**
     * Returns the month of the specified date according to universal time, as a zero-based value (where zero indicates the first month of the year).
     *
     * @returns  An integer number, between 0 and 11, representing the month in the given date according to UTC time.
     * 0 corresponds to January, 1 to February, and so on.
     */
    public override getUTCMonth(): int {
        this.conditionalAddRef();
        return super.getUTCMonth();
    }

    /**
     * Sets the month for a specified date according to the currently set year.
     *
     * @param month new month
     */
    public override setMonth(month: int): long {
        const result = super.setMonth(month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMonth');
        return result;
    }

    /**
     * Sets the month for a specified date according to the currently set year.
     *
     * @param month new month
     */
    public override setMonth(month: int, date: int): long {
        const result = super.setMonth(month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMonth');
        return result;
    }

    /**
     * Sets the month for a specified date according to universal time.
     *
     * @param month new month
     */
    public override setUTCMonth(month: int): long {
        const result = super.setUTCMonth(month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMonth');
        return result;
    }

    /**
     * Sets the month for a specified date according to universal time.
     *
     * @param month new month
     */
    public override setUTCMonth(month: int, date: int): long {
        const result = super.setUTCMonth(month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMonth');
        return result;
    }

    /**
     * Returns the number of milliseconds since the epoch,
     * which is defined as the midnight at the beginning of January 1, 1970, UTC.
     *
     * @see ECMA-262, 21.4.4.10
     * @returns A number representing the milliseconds elapsed between 1 January 1970 00:00:00 UTC and the given date.
     */
    public override getTime(): long {
        this.conditionalAddRef();
        return super.getTime();
    }

    /**
     * Sets the number of milliseconds since the epoch,
     * which is defined as the midnight at the beginning of January 1, 1970, UTC.
     *
     * @param value new ms
     * @see ECMA-262, 21.4.4.10
     * @returns A number representing the milliseconds elapsed between 1 January 1970 00:00:00 UTC and the given date.
     */
    public override setTime(value: long): long {
        const result = super.setTime(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setTime');
        return result;
    }

    /**
     * Returns the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     *
     * @returns the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     */
    public override getTimezoneOffset(): long {
        this.conditionalAddRef();
        return super.getTimezoneOffset();
    }

    /**
     * Sets the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     *
     * @param value new timezone offset
     */
    public override setTimezoneOffset(value: int): long {
        const result = super.setTimezoneOffset(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setTime');
        return result;
    }

    /**
     * Returns a string in simplified extended ISO format (ISO 8601),
     * which is always 24 or 27 characters long (YYYY-MM-DDTHH:mm:ss.sssZ or
     * ±YYYYYY-MM-DDTHH:mm:ss.sssZ, respectively). The timezone is always zero UTC offset,
     * as denoted by the suffix Z.
     *
     * @see ECMA-262, 21.4.4.36
     * @returns A string representing the given date in the ISO 8601 format according to universal time.
     * It's the same format as the one required to be recognized by @link{parse()}.
     * @example
     * ```ets
     * const today = new Date();
     * console.println(today.toISOString()); // Returns 2023-02-05T14:48:00.000Z
     * ```
     */
    public override toISOString(): string {
        this.conditionalAddRef();
        return super.toISOString();
    }

    /**
     * Returns a string representation of the Date object.
     *
     * @returns JSON representation of the current instance
     */
    public override toJSON(): string {
        this.conditionalAddRef();
        return super.toJSON() ?? '';
    }

    /**
     * Returns the time portion of a `Date` object interpreted in the local timezone in English.
     *
     * @see ECMA-262, 21.4.4.42
     * @returns A string representing the time portion of the given date in human-readable form in English.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toTimeString()); // 13:12:57 GMT
     * ```
     */
    public override toTimeString(): string {
        this.conditionalAddRef();
        return super.toTimeString();
    }

    /**
     * Returns the date portion of a `Date` object interpreted in the local timezone in English.
     *
     * @see ECMA-262, 21.4.4.35
     * @returns A string representing the date portion of the given Date object in human-readable form in English.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toDateString()); // Sat Oct 27 1979
     * ```
     */
    public override toDateString(): string {
        this.conditionalAddRef();
        return super.toDateString();
    }

    /**
     * Returns a string representing the specified `Date` object interpreted in the local timezone.
     *
     * @see ECMA-262, 21.4.4.41
     * @returns A string representing the given date.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toString()); // Sat Oct 27 1979 13:12:57 GMT
     * ```
     */
    public override toString(): string {
        this.conditionalAddRef();
        return super.toString();
    }

    /**
     * Returns a string representing the specified `Date` object interpreted in UTC.
     *
     * @see ECMA-262, 21.4.4.41
     * @returns A string representing the given date.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toUTCString()); // Sat Oct 27 1979 13:12:57 GMT
     * ```
     */
    public override toUTCString(): string {
        this.conditionalAddRef();
        return super.toUTCString();
    }

    // shorthand function because
    // Date can suffice with one meta
    // (IMutableStateMeta)
    private conditionalAddRef(): void {
        this.meta_.addRef();
    }
}
