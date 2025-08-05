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

import { StateMgmtTool } from '#stateMgmtTool';
import { NullableObject } from './types';
import { WrappedArray } from './observeWrappedArray';
import { WrappedDate } from './observeWrappedDate';
import { WrappedSet } from './observeWrappedSet';
import { WrappedMap } from './observeWrappedMap';
import { ObserveWrappedBase } from './observeWrappedBase';
import { Binding, MutableBinding } from '../utils';

export class UIUtilsImpl {
    private static observedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();
    private static deepObservedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();

    public static set<T extends Object>(obj: Object, wrapObject: T, allowDeep: boolean): T {
        allowDeep ? UIUtilsImpl.deepObservedMap.set(obj, wrapObject) : UIUtilsImpl.observedMap.set(obj, wrapObject);
        return wrapObject;
    }

    public static getObservedProxy<T extends Object>(obj: T, allowDeep: boolean): T | undefined {
        if (obj && UIUtilsImpl.isProxied(obj)) {
            return obj;
        }
        return allowDeep
            ? (UIUtilsImpl.deepObservedMap.get(obj) as T | undefined)
            : (UIUtilsImpl.observedMap.get(obj) as T | undefined);
    }

    public static getObserved<T extends Object>(obj: T, allowDeep: boolean): T | undefined {
        return allowDeep
            ? (UIUtilsImpl.deepObservedMap.get(obj) as T | undefined)
            : (UIUtilsImpl.observedMap.get(obj) as T | undefined);
    }

    public static isProxied<T extends Object>(value: T): boolean {
        const handler = StateMgmtTool.tryGetHandler(value);
        return !!(handler && StateMgmtTool.isInterfaceProxyHandler(handler));
    }

    public static makeObservedProxyNoCheck<T extends Object>(source: T, allowDeep: boolean): T {
        const observed = UIUtilsImpl.getObservedProxy(source, allowDeep);
        if (observed !== undefined) {
            return observed as T;
        }
        return UIUtilsImpl.set(source, StateMgmtTool.createProxy<T>(source, allowDeep), allowDeep);
    }

    public static makeObservedArray<T>(source: Array<T>, allowDeep: boolean): Array<T> {
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedArray<T>(source, allowDeep), allowDeep);
    }

    public static makeObservedDate(source: Date, allowDeep: boolean): Date {
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedDate(source, allowDeep), allowDeep);
    }

    public static makeObservedMap<K, V>(source: Map<K, V>, allowDeep: boolean): Map<K, V> {
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedMap<K, V>(source, allowDeep), allowDeep);
    }

    public static makeObservedSet<T>(source: Set<T>, allowDeep: boolean): Set<T> {
        const observed = UIUtilsImpl.getObserved(source, allowDeep);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedSet<T>(source, allowDeep), allowDeep);
    }

    // allowDeep is used to mark whether it need to use deep observation
    // normally for V1 it should be false
    // for API and V2, it should be set to true manually
    public makeObserved<T>(value: T, allowDeep: boolean = false): T {
        if (!value || typeof value !== 'object') {
            return value as T;
        }
        if (value instanceof ObserveWrappedBase) {
            return value as T;
        }
        if (value instanceof Array && Type.of(value).getName() === 'escompat.Array') {
            return UIUtilsImpl.makeObservedArray(value, allowDeep) as T;
        }
        if (value instanceof Date && Type.of(value).getName() === 'escompat.Date') {
            return UIUtilsImpl.makeObservedDate(value, allowDeep) as T;
        }
        if (value instanceof Map && Type.of(value).getName() === 'escompat.Map') {
            return UIUtilsImpl.makeObservedMap(value, allowDeep) as T;
        }
        if (value instanceof Set && Type.of(value).getName() === 'escompat.Set') {
            return UIUtilsImpl.makeObservedSet(value, allowDeep) as T;
        }
        if (value && StateMgmtTool.isObjectLiteral(value)) {
            return UIUtilsImpl.makeObservedProxyNoCheck(value as Object, allowDeep) as T;
        }
        return value;
    }

    public getTarget<T>(source: T): T {
        if (!source || typeof source !== 'object') {
            return source;
        }
        if (UIUtilsImpl.isProxied(source!)) {
            return proxy.Proxy.tryGetTarget(source! as Object)! as Object as T;
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
}

export const uiUtils: UIUtilsImpl = new UIUtilsImpl();
