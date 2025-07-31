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

export class UIUtilsImpl {
    private static observedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();

    public static set<T extends Object>(obj: Object, wrapObject: T): T {
        UIUtilsImpl.observedMap.set(obj, wrapObject);
        return wrapObject;
    }

    public static getObservedProxy<T extends Object>(obj: T): T | undefined {
        if (obj && UIUtilsImpl.isProxied(obj)) {
            return obj;
        }
        return UIUtilsImpl.observedMap.get(obj) as T | undefined;
    }

    public static getObserved<T extends Object>(obj: T): T | undefined {
        return UIUtilsImpl.observedMap.get(obj) as T | undefined;
    }

    public static isProxied<T extends Object>(value: T): boolean {
        const handler = StateMgmtTool.tryGetHandler(value);
        return !!(handler && StateMgmtTool.isInterfaceProxyHandler(handler));
    }

    public static makeObservedProxyNoCheck<T extends Object>(source: T): T {
        const observed = UIUtilsImpl.getObservedProxy(source);
        if (observed !== undefined) {
            return observed as T;
        }
        return UIUtilsImpl.set(source, StateMgmtTool.createProxy<T>(source));
    }

    public static makeObservedArray<T>(source: Array<T>): Array<T> {
        const observed = UIUtilsImpl.getObserved(source);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedArray<T>(source));
    }

    public static makeObservedDate(source: Date): Date {
        const observed = UIUtilsImpl.getObserved(source);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedDate(source));
    }

    public static makeObservedMap<K, V>(source: Map<K, V>): Map<K, V> {
        const observed = UIUtilsImpl.getObserved(source);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedMap<K, V>(source));
    }

    public static makeObservedSet<T>(source: Set<T>): Set<T> {
        const observed = UIUtilsImpl.getObserved(source);
        if (observed) {
            return observed;
        }
        return UIUtilsImpl.set(source, new WrappedSet<T>(source));
    }

    public makeObserved<T>(value: T): T {
        if (value instanceof ObserveWrappedBase) {
            return value as T;
        }
        if (value instanceof Array && Type.of(value).getName() === 'escompat.Array') {
            return UIUtilsImpl.makeObservedArray(value) as T;
        }
        if (value instanceof Date && Type.of(value).getName() === 'escompat.Date') {
            return UIUtilsImpl.makeObservedDate(value) as T;
        }
        if (value instanceof Map && Type.of(value).getName() === 'escompat.Map') {
            return UIUtilsImpl.makeObservedMap(value) as T;
        }
        if (value instanceof Set && Type.of(value).getName() === 'escompat.Set') {
            return UIUtilsImpl.makeObservedSet(value) as T;
        }
        if (value && StateMgmtTool.isObjectLiteral(value)) {
            return UIUtilsImpl.makeObservedProxyNoCheck(value as Object) as T;
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
}

export const uiUtils: UIUtilsImpl = new UIUtilsImpl();
