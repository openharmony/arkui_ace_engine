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
        if ('addWatchSubscriber' in newValue && typeof (newValue as any).addWatchSubscriber === 'function') {
            const callback = () => {
                owningProperty.onTrackedObjectPropertyCompatModeHasChangedPU(null, '');
            };
            if (typeof InteropExtractorModule.createWatchFunc !== undefined && typeof InteropExtractorModule.createWatchFunc === 'function') {
                owningProperty.staticWatchFunc = InteropExtractorModule.createWatchFunc(callback, newValue);
            }
        }
        return newValue;
    }

    static setStaticValueForInterop<T>(state: ObservedPropertyPU<T> | SynchedPropertyOneWayPU<T>, newValue: T): void {
        if (state._setInteropValueForStaticState !== undefined &&
            typeof state._setInteropValueForStaticState === 'function') {
            state._setInteropValueForStaticState(newValue);
        }
    }

    static createWatchFunc?: (watchFuncCallback: WatchFuncType, newValue: Object) => any;
    static makeObserved?: (value: Object) => Object;
    static compatibleStaticComponent?: (
        factory: () => Object,
        options?: () => Object,
        content?: () => void
    ) => [() => void, number];
    static makeBuilderParameterStaticProxy?: (name: string, value: Object, sourceGetter: Object) => Object;
    static updateInteropExtendableComponent?: (dynamicComponent: any) => void;
    static resetInteropExtendableComponent?: ()=> void;
    static transferCompatibleBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static createCompatibleStaticState?: (value: Object) => Object;
    static transferCompatibleUpdatableBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
}

class StaticInteropHook {
    addRef?: () => void;
}

function registerCallbackForCreateWatchID(callback: () => any): void {
    InteropExtractorModule.createWatchFunc = callback;
}

function registerCallbackForMakeObserved(callback: (value: Object) => Object): void {
    InteropExtractorModule.makeObserved = callback;
}

function registerCompatibleStaticComponentCallback(
    callback: (
        factory: () => Object,
        options?: () => Object,
        content?: () => void
    ) => [() => void, number]
): void {
    InteropExtractorModule.compatibleStaticComponent = callback;
}

function registerMakeBuilderParameterStaticProxy(callback: (name: string, value: Object, sourceGetter: Object) => Object): void {
    InteropExtractorModule.makeBuilderParameterStaticProxy = callback;
}

function registerUpdateInteropExtendableComponent(callback: (dynamicComponent: Object) => void): void {
    InteropExtractorModule.updateInteropExtendableComponent = callback;
}

function registerResetInteropExtendableComponent(callback: () => void): void {
    InteropExtractorModule.resetInteropExtendableComponent = callback;
}

function registerTransferCompatibleBuilderCallback(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleBuilder = callback;
}

function registerTransferCompatibleDynamicBuilderCallback(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder = callback;
}

function registerCreateCompatibleStaticState(callback: (value: Object) => Object): void {
    InteropExtractorModule.createCompatibleStaticState = callback;
}

function registerTransferCompatibleUpdatableBuilderCallback(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleUpdatableBuilder = callback;
}