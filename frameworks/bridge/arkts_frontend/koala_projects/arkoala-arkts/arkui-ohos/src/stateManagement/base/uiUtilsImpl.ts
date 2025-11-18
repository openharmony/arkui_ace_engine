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

import { StateMgmtTool, InterfaceProxyHandler } from '#stateMgmtTool';
import { NullableObject } from './types';
import { WrappedArray } from './observeWrappedArray';
import { WrappedDate } from './observeWrappedDate';
import { WrappedSet } from './observeWrappedSet';
import { WrappedMap } from './observeWrappedMap';
import { ObserveWrappedBase } from './observeWrappedBase';
import { Binding, MutableBinding } from '../utils';
import { getRawObject, isDynamicObject } from '#generated';

const ArrayTypeName = Type.from<Array<Any>>().getName();
const SetTypeName = Type.from<Set<Any>>().getName();
const MapTypeName = Type.from<Map<Any, Any>>().getName();
const DateTypeName = Type.from<Date>().getName();

export class UIUtilsImpl {
    private static observedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();
    private static deepObservedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();

    public static set<T extends Object>(obj: Object, wrapObject: T, allowDeep: boolean): T {
        allowDeep
            ? UIUtilsImpl.deepObservedMap.set(obj, wrapObject)
            : UIUtilsImpl.observedMap.set(obj, wrapObject);
        return wrapObject;
    }

    public static getObservedProxy<T extends Object>(obj: T, allowDeep: boolean): T | undefined {
        if (obj && UIUtilsImpl.isProxied(obj)) {
            return obj;
        }
        return allowDeep
            ? UIUtilsImpl.deepObservedMap.get(obj) as T | undefined
            : UIUtilsImpl.observedMap.get(obj) as T | undefined;
    }

    public static getObserved<T extends Object>(obj: T, allowDeep: boolean): T | undefined {
        return allowDeep
            ? UIUtilsImpl.deepObservedMap.get(obj) as T | undefined
            : UIUtilsImpl.observedMap.get(obj) as T | undefined;
    }

    public static isProxied<T extends Object>(value: T): boolean {
        const handler = StateMgmtTool.tryGetHandler(value);
        return !!(handler && StateMgmtTool.isInterfaceProxyHandler(handler));
    }

    public static makeObservedProxyNoCheck<T extends Object>(source: T, allowDeep: boolean, isAPI: boolean = false): T {
        if (!isAPI) {
            return StateMgmtTool.createProxy<T>(source, allowDeep, isAPI);
        }
        const observed = UIUtilsImpl.getObservedProxy(source, allowDeep);
        if (observed !== undefined) {
            return observed as T;
        }
        return UIUtilsImpl.set(source, StateMgmtTool.createProxy<T>(source, allowDeep, isAPI), allowDeep);
    }

    public static makeObservedArray<T>(source: Array<T>, allowDeep: boolean, isAPI: boolean = false): Array<T> {
        if (!isAPI) {
            return new WrappedArray<T>(source, allowDeep, isAPI);
        }
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedArray<T>(source, allowDeep, isAPI), allowDeep);
    }

    public static makeObservedDate(source: Date, allowDeep: boolean, isAPI: boolean = false): Date {
        if (!isAPI) {
            return new WrappedDate(source, allowDeep);
        }
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedDate(source, allowDeep), allowDeep);
    }

    public static makeObservedMap<K, V>(source: Map<K, V>, allowDeep: boolean, isAPI: boolean = false): Map<K, V> {
        if (!isAPI) {
            return new WrappedMap<K, V>(source, allowDeep, isAPI);
        }
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedMap<K, V>(source, allowDeep, isAPI), allowDeep);
    }

    public static makeObservedSet<T>(source: Set<T>, allowDeep: boolean, isAPI: boolean = false): Set<T> {
        if (!isAPI) {
            return new WrappedSet<T>(source, allowDeep);
        }
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedSet<T>(source, allowDeep), allowDeep);
    }

    // allowDeep is used to mark whether it need to use deep observation
    // normally for V1 it should be false
    // for API and V2, it should be set to true manually
    public makeObservedEntrance<T>(value: T, allowDeep: boolean = false, isAPI: boolean = false): T {
        if (!allowDeep) {
            return this.makeV1Observed(value);
        } else if (!isAPI) {
            return this.autoProxyObject(value);
        } else {
            return this.makeObserved(value);
        }
    }

    private static makeObservedWrappedBaseMap: Map<string, (value: object, allowDeep: boolean, isAPI: boolean) => object> = 
        new Map<string, (value: object, allowDeep: boolean, isAPI: boolean) => object>([
            [ArrayTypeName, (value: object, allowDeep: boolean, isAPI: boolean) => UIUtilsImpl.makeObservedArray(value as Array<Any>, allowDeep, isAPI)],
            [DateTypeName, (value: object, allowDeep: boolean, isAPI: boolean) => UIUtilsImpl.makeObservedDate(value as Date, allowDeep, isAPI)],
            [MapTypeName, (value: object, allowDeep: boolean, isAPI: boolean) => UIUtilsImpl.makeObservedMap(value as Map<Any, Any>, allowDeep, isAPI)],
            [SetTypeName, (value: object, allowDeep: boolean, isAPI: boolean) => UIUtilsImpl.makeObservedSet(value as Set<Any>, allowDeep, isAPI)],
        ]);

    public makeV1Observed<T>(value: T): T {
        if (!value || typeof value !== 'object') {
            return value as T;
        }
        const isProxy = StateMgmtTool.isObjectLiteral(value);
        if (value instanceof ObserveWrappedBase || !(UIUtilsImpl.checkIsBuitInType(value) || isProxy)) {
            return value as T;
        }
        const valueTypeName = Type.of(value).getName();
        const makeObservedWrappedBase: ((value: object, allowDeep: boolean, isAPI: boolean) => object) | undefined = 
            UIUtilsImpl.makeObservedWrappedBaseMap.get(valueTypeName);
        if (makeObservedWrappedBase) {
            return makeObservedWrappedBase!(value as object, false, false) as T;
        }
        if (isProxy) {
            return UIUtilsImpl.makeObservedProxyNoCheck(value as Object, false, false) as T;
        }
        return value;
    }

    public autoProxyObject<T>(value: T): T {
        if (!value || typeof value !== 'object') {
            return value as T;
        }
        if (isDynamicObject(value)) {
            value = getRawObject(value);
        }
        if (value instanceof ObserveWrappedBase || !(UIUtilsImpl.checkIsBuitInType(value))) {
            return value as T;
        }
        const valueTypeName = Type.of(value).getName();
        const makeObservedWrappedBase: ((value: object, allowDeep: boolean, isAPI: boolean) => object) | undefined = 
            UIUtilsImpl.makeObservedWrappedBaseMap.get(valueTypeName);
        if (makeObservedWrappedBase) {
            return makeObservedWrappedBase!(value as object, true, false) as T;
        }
        return value;
    }

    public makeObserved<T>(value: T): T {
        if (!value || typeof value !== 'object') {
            return value as T;
        }
        if (isDynamicObject(value)) {
            value = getRawObject(value);
        }
        const isProxy = StateMgmtTool.isObjectLiteral(value);
        if (value instanceof ObserveWrappedBase || !(UIUtilsImpl.checkIsBuitInType(value) || isProxy)) {
            return value as T;
        }
        const valueTypeName = Type.of(value).getName();
        const makeObservedWrappedBase: ((value: object, allowDeep: boolean, isAPI: boolean) => object) | undefined = 
            UIUtilsImpl.makeObservedWrappedBaseMap.get(valueTypeName);
        if (makeObservedWrappedBase) {
            return makeObservedWrappedBase!(value as object, true, true) as T;
        }
        if (isProxy) {
            return UIUtilsImpl.makeObservedProxyNoCheck(value as Object, true, true) as T;
        }
        return value;
    }

    public static checkIsBuitInType<T>(value: T): boolean {
        return value instanceof Array || value instanceof Map || value instanceof Set || value instanceof Date;
    }

    public getTarget<T>(source: T): T {
        if (!source || typeof source !== 'object') {
            return source;
        }
        if (UIUtilsImpl.isProxied(source!)) {
            const handler = StateMgmtTool.tryGetHandler(source as Object);
            return (handler as InterfaceProxyHandler).target as T;
        }
        if (
            source instanceof WrappedArray ||
            source instanceof WrappedMap ||
            source instanceof WrappedDate ||
            source instanceof WrappedSet
        ) {
            return (source as ObserveWrappedBase).getRaw()! as T;
        }
        return source;
    }

    public makeBindingReadonly<T>(getter: () => T): Binding<T> {
        return new Binding<T>(getter);
    }
    public makeBindingMutable<T>(getter: () => T, setter: (newValue: T) => void): MutableBinding<T> {
        return new MutableBinding<T>(getter, setter);
    }

    public builtinContainersAddRefAnyKey(value: Any): void {
        if (value instanceof WrappedArray) {
            value.keys();
        } else if (value instanceof WrappedMap) {
            value.keys();
        } else if (value instanceof WrappedSet) {
            value.keys();
        }
    }

    public builtinContainersAddRefLength(value: Any): void {
        if (value instanceof WrappedArray) {
            value.length;
        } else if (value instanceof WrappedMap) {
            value.size;
        } else if (value instanceof WrappedSet) {
            value.size;
        }
    }
}

export const uiUtils: UIUtilsImpl = new UIUtilsImpl();
