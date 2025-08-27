/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { getObservableTarget } from "./observable"

/*
    When decorating variables of complex types,
    @Prop makes a deep copy, during which all types,
    except primitive types, Map, Set, Date, and Array, will be lost.
 */

export function propDeepCopy<T>(sourceObject: T): T {
    if (!sourceObject || typeof sourceObject !== 'object') {
        return sourceObject
    }

    const copiedObjects = new Map<Object, Object>()
    return recursiveDeepCopy(sourceObject) as T

    function recursiveDeepCopy(sourceObject: Object): Object {
        if (!sourceObject || typeof sourceObject !== 'object') {
            return sourceObject
        }

        const storedObject = copiedObjects.get(sourceObject)
        if (storedObject !== undefined) {
            return storedObject
        }

        const copy: any = copyDeepTrackable(sourceObject)

        const objectToCopyFrom = getObservableTarget(sourceObject)
        Object.keys(objectToCopyFrom)
            .forEach((key) => {
                const property = objectToCopyFrom[key as keyof Object]

                if (typeof property === "function") {
                    Reflect.set(copy, key, property)
                    copy[key] = copy[key].bind(copy)
                    return
                }
                Reflect.set(copy, key, recursiveDeepCopy(property));
            })

        return copy
    }

    function copyDeepTrackable<T>(sourceObject: T): T {
        if (sourceObject instanceof Set) {
            const copy = new Set<any>()
            Object.setPrototypeOf(copy, Object.getPrototypeOf(sourceObject))
            copiedObjects.set(sourceObject, copy)
            for (const setKey of sourceObject.keys()) {
                copy.add(recursiveDeepCopy(setKey))
            }
            return copy as T
        }
        if (sourceObject instanceof Map) {
            const copy = new Map<any, any>()
            Object.setPrototypeOf(copy, Object.getPrototypeOf(sourceObject))
            copiedObjects.set(sourceObject, copy)
            for (const mapKey of sourceObject.keys()) {
                copy.set(mapKey, recursiveDeepCopy(sourceObject.get(mapKey)))
            }
            return copy as T
        }
        if (sourceObject instanceof Date) {
            const copy = new Date()
            copy.setTime(sourceObject.getTime())
            Object.setPrototypeOf(copy, Object.getPrototypeOf(sourceObject))
            copiedObjects.set(sourceObject, copy)
            return copy as T
        }
        if (sourceObject instanceof Object) {
            const copy = Array.isArray(sourceObject) ? [] : {}
            Object.setPrototypeOf(copy, Object.getPrototypeOf(sourceObject))
            copiedObjects.set(sourceObject, copy)
            return copy as T
        }

        return sourceObject
    }
}
