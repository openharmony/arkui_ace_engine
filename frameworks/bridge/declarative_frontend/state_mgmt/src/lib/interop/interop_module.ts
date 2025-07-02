/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class InteropExtractorModule { 
    static createObservedArrayForInterop<T extends Object>(rawObject: T, owningProperty: IPropertySubscriber): T {
        if (ObservedObject.IsObservedObject(rawObject)) {
            ObservedObject.addOwningProperty(rawObject, owningProperty);
            return rawObject;
        }
        const result = new Proxy(rawObject, new SubscribableArrayHandler(owningProperty));
        if (owningProperty) {
            result[SubscribableHandler.SUBSCRIBE] = owningProperty;
        }
        return result as T;
    }

    static getInteropObservedObject<T extends Object>(newValue: T, owningProperty: IPropertySubscriber): T {
        if (newValue instanceof Array) {
            return InteropExtractorModule.createObservedArrayForInterop(newValue, owningProperty);
        } else if (newValue instanceof Set || newValue instanceof Map || newValue instanceof Date) {
            return ObservedObject.createNew(newValue, owningProperty);
        } else {
            return newValue;
        }
    }

    static setStaticValueForInterop<T>(state: ObservedPropertyPU<T>, newValue: T): void {
        if (state._setInteropValueForStaticState !== undefined && 
            typeof state._setInteropValueForStaticState === 'function') {
            state._setInteropValueForStaticState(newValue);
        }
    }
}