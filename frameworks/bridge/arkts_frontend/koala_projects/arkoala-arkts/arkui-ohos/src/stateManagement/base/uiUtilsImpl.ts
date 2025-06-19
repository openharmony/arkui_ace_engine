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

export class UIUtilsImpl {
    private static observedMap: WeakMap<Object, Object> = new WeakMap<Object, Object>();

    public static set<T extends Object>(obj: Object, wrapObject: T): T {
        UIUtilsImpl.observedMap.set(obj, wrapObject);
        return wrapObject;
    }

    public static getObservedProxy<T extends Object>(obj: T): T | undefined {
        if (UIUtilsImpl.isProxied(obj)) {
            return obj;
        }
        return UIUtilsImpl.observedMap.get(obj) as (T | undefined);
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

    public makeObserved<T extends Object>(value: T): T {
        if (StateMgmtTool.isIObservedObject(value)) {
            return value as T;
        }
        if (StateMgmtTool.isObjectLiteral(value)) {
            return UIUtilsImpl.makeObservedProxyNoCheck(value);
        }
        return value;
    }
}

export const uiUtils: UIUtilsImpl = new UIUtilsImpl();