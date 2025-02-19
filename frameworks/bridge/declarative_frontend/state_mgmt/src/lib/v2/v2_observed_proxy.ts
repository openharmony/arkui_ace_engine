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

/**
 * Common Proxy handler for objects and dates for both decorators and makeObserved
 */
class ObjectProxyHandler {

    private static readonly OB_DATE = '__date__';

    private isMakeObserved_: boolean;

    constructor(isMakeObserved: boolean = false) {
        this.isMakeObserved_ = isMakeObserved;
    }

    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    private getTarget(obj: any): any {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }

    private static readonly dateSetFunctions = new Set(['setFullYear', 'setMonth', 'setDate', 'setHours', 'setMinutes',
        'setSeconds', 'setMilliseconds', 'setTime', 'setUTCFullYear', 'setUTCMonth', 'setUTCDate', 'setUTCHours',
        'setUTCMinutes', 'setUTCSeconds', 'setUTCMilliseconds']);

    get(target: any, key: string | symbol, receiver: any): any {

        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args): any => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }

        stateMgmtConsole.debug(`ObjectProxyHandler get key '${key}'`);
        const conditionalTarget = this.getTarget(target);

        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        // do not addref for function type, it will make such huge unnecessary dependency collection
        // for some common function attributes, e.g. toString etc.
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret)[RefInfo.MAKE_OBSERVED_PROXY] : ret;
        }

        if (target instanceof Date) {
            if (ObjectProxyHandler.dateSetFunctions.has(key)) {
                return function (...args): any {
                    // execute original function with given arguments
                    let result = ret.call(this, ...args);
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObjectProxyHandler.OB_DATE);
                    return result;
                    // bind 'this' to target inside the function
                }.bind(target);
            } else {
                ObserveV2.getObserve().addRef(conditionalTarget, ObjectProxyHandler.OB_DATE);
            }
            return ret.bind(target);
        }

        // function
        return ret.bind(receiver);
    }

    set(target: any, key: string | symbol, value: any): boolean {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }

        if (target[key] === value) {
            return true;
        }
        target[key] = value;
        ObserveV2.getObserve().fireChange(this.getTarget(target), key.toString());
        return true;
    }
};

/**
 * Common Proxy handler for Arrays for both decorators and makeObserved
 */
class ArrayProxyHandler {

    private isMakeObserved_: boolean;

    constructor(isMakeObserved: boolean = false) {
        this.isMakeObserved_ = isMakeObserved;
    }

    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    private getTarget(obj: any): any {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }

    // shrinkTo and extendTo is collection.Array api.
    private static readonly arrayLengthChangingFunctions = new Set(['push', 'pop', 'shift', 'splice', 'unshift', 'shrinkTo', 'extendTo']);
    private static readonly arrayMutatingFunctions = new Set(['copyWithin', 'fill', 'reverse', 'sort']);

    get(target: Array<any>, key: string | symbol, receiver: Array<any>): any {

        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args): any => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }

        stateMgmtConsole.debug(`ArrayProxyHandler get key '${key}'`);
        const conditionalTarget = this.getTarget(target);

        if (key === 'length') {
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return target[key];
        }

        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret)[RefInfo.MAKE_OBSERVED_PROXY] : ret;
        }

        if (ArrayProxyHandler.arrayMutatingFunctions.has(key)) {
            return function (...args): any {
                ret.call(target, ...args);
                ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                // returning the 'receiver(proxied object)' ensures that when chain calls also 2nd function call
                // operates on the proxied object.
                return receiver;
            };
        } else if (ArrayProxyHandler.arrayLengthChangingFunctions.has(key)) {
            return function (...args): any {
                const result = ret.call(target, ...args);
                ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                return result;
            };
        } else if (!SendableType.isArray(target)) {
            return ret.bind(receiver);
        } else if (key === 'forEach') {
            // to make ForEach Component and its Item can addref
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return function (callbackFn: (value: any, index: number, array: Array<any>) => void): any {
                const result = ret.call(target, (value: any, index: number, array: Array<any>) => {
                    // Collections.Array will report BusinessError: The foreach cannot be bound if call "receiver".
                    // because the passed parameter is not the instance of the container class.
                    // so we must call "target" here to deal with the collections situations.
                    // But we also need to addref for each index.
                    ObserveV2.getObserve().addRef(conditionalTarget, index.toString());
                    callbackFn(typeof value === 'object' ? RefInfo.get(value)[RefInfo.MAKE_OBSERVED_PROXY] : value, index, receiver);
                });
                return result;
            };
        } else {
            return ret.bind(target); // SendableArray can't be bound -> functions not observed
        }
    }

    set(target: Array<any>, key: string | symbol, value: any): boolean {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }

        if (target[key] === value) {
            return true;
        }

        const originalLength = target.length;
        target[key] = value;
        const arrayLenChanged = target.length !== originalLength;
        ObserveV2.getObserve().fireChange(this.getTarget(target), arrayLenChanged ? ObserveV2.OB_LENGTH : key.toString());
        return true;
    }
};

/**
 * Common Proxy handler for Maps and Sets for both decorators and makeObserved
 */
class SetMapProxyHandler {

    private static readonly OB_MAP_SET_ANY_PROPERTY = '___ob_map_set';

    private isMakeObserved_: boolean;

    constructor(isMakeObserved: boolean = false) {
        this.isMakeObserved_ = isMakeObserved;
    }

    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    private getTarget(obj: any): any {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }

    get(target: any, key: string | symbol, receiver: any): any {
        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().addRef(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args): any => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }

        stateMgmtConsole.debug(`SetMapProxyHandler get key '${key}'`);
        const conditionalTarget = this.getTarget(target);

        if (key === 'size') {
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return target[key];
        }

        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret)[RefInfo.MAKE_OBSERVED_PROXY] : ret;
        }

        if (key === 'has') {
            return (prop): boolean => {
                const ret = target.has(prop);
                if (ret) {
                    ObserveV2.getObserve().addRef(conditionalTarget, prop);
                } else {
                    ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                }
                return ret;
            };
        }
        if (key === 'delete') {
            return (prop): boolean => {
                if (target.has(prop)) {
                    const res: boolean = target.delete(prop)
                    ObserveV2.getObserve().fireChange(conditionalTarget, prop);
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    return res;
                } else {
                    return false;
                }
            };
        }
        if (key === 'clear') {
            return (): void => {
                if (target.size > 0) {
                    target.forEach((_, prop) => {
                        ObserveV2.getObserve().fireChange(conditionalTarget, prop.toString(), true);
                    });
                    target.clear();
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                }
            };
        }
        if (key === 'keys' || key === 'values' || key === 'entries') {
            return (): any => {
                ObserveV2.getObserve().addRef(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return target[key]();
            };
        }

        if (target instanceof Set || (this.isMakeObserved_ && SendableType.isSet(target))) {
            if (key === 'add') {
                return (val): any => {
                    if (target.has(val)) {
                        return receiver;
                    }
                    target.add(val);
                    ObserveV2.getObserve().fireChange(conditionalTarget, val);
                    ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    return receiver;
                };
            }

            if (key === 'forEach') {
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return function (callbackFn: (value: any, value2: any, set: Set<any>) => void): any {
                    // need to execute it target because it is the internal function for build-in type, and proxy does not have such slot.
                    // if necessary, addref for each item in Set and also wrap proxy for makeObserved if it is Object.
                    // currently, just execute it in target because there is no Component need to iterate Set, only Array
                    const result = ret.call(target, callbackFn);
                    return result;
                };
            }
            // Bind to receiver ==> functions are observed
            return (typeof ret === 'function') ? ret.bind(receiver) : ret;
        }

        if (target instanceof Map || (this.isMakeObserved_ && SendableType.isMap(target))) {
            if (key === 'get') {
                return (prop): any => {
                    if (target.has(prop)) {
                        ObserveV2.getObserve().addRef(conditionalTarget, prop);
                    } else {
                        ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                    }
                    let item = target.get(prop);
                    return (typeof item === 'object' && this.isMakeObserved_) ? RefInfo.get(item)[RefInfo.MAKE_OBSERVED_PROXY] : item;
                };
            }
            if (key === 'set') {
                return (prop, val): any => {
                    if (!target.has(prop)) {
                        target.set(prop, val);
                        ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    } else if (target.get(prop) !== val) {
                        target.set(prop, val);
                        ObserveV2.getObserve().fireChange(conditionalTarget, prop);
                    }
                    ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                    return receiver;
                };
            }
            if (key === 'forEach') {
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return function (callbackFn: (value: any, key: any, map: Map<any, any>) => void): any {
                    // need to execute it target because it is the internal function for build-in type, and proxy does not have such slot.
                    // if necessary, addref for each item in Map and also wrap proxy for makeObserved if it is Object.
                    // currently, just execute it in target because there is no Component need to iterate Map, only Array
                    const result = ret.call(target, callbackFn);
                    return result;
                };
            }
        }
        // Bind to receiver ==> functions are observed
        return (typeof ret === 'function') ? ret.bind(receiver) : ret;
    }

    set(target: any, key: string | symbol, value: any): boolean {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }

        if (target[key] === value) {
            return true;
        }
        target[key] = value;
        ObserveV2.getObserve().fireChange(this.getTarget(target), key.toString());
        return true;
    }
};