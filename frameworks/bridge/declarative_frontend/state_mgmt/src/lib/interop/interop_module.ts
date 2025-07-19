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
    static getInteropObservedObject<T extends Object>(newValue: T, owningProperty: ObservedPropertyPU<T>): T {
        if ((newValue instanceof Array || newValue instanceof Set || newValue instanceof Map || newValue instanceof Date) &&
            !('addWatchSubscriber' in newValue) && (typeof InteropExtractorModule.makeObserved !== undefined && typeof InteropExtractorModule.makeObserved === 'function')) {
            newValue = InteropExtractorModule.makeObserved(newValue) as T;
        }
        if ('addWatchSubscriber' in newValue && typeof newValue.addWatchSubscriber === 'function') {
            const callback = () => {
                owningProperty.onTrackedObjectPropertyCompatModeHasChangedPU(null, '');
            };
            if (typeof InteropExtractorModule.createWatchFunc !== undefined && typeof InteropExtractorModule.createWatchFunc === 'function') {
                owningProperty.staticWatchId = InteropExtractorModule.createWatchFunc(callback, newValue);
            }
        }
        return newValue;
    }

    static setStaticValueForInterop<T>(state: ObservedPropertyPU<T>, newValue: T): void {
        if (state._setInteropValueForStaticState !== undefined &&
            typeof state._setInteropValueForStaticState === 'function') {
            state._setInteropValueForStaticState(newValue);
        }
    }

    static createWatchFunc?: (watchFuncCallback: WatchFuncType, newValue: Object) => any;
    static makeObserved?: (value: Object) => Object;
}