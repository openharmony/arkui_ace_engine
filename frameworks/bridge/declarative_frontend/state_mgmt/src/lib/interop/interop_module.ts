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
    static getInteropObservedObject<T extends Object>(newValue: T, owningProperty: ObservedPropertyAbstractPU<T>): T {
        const isStaBuiltin =
          globalThis.Panda.STValue.isSTArray(newValue) ||
          globalThis.Panda.STValue.isSTSet(newValue) ||
          globalThis.Panda.STValue.isSTMap(newValue) ||
          newValue instanceof Date;
        if (
          isStaBuiltin &&
          !('addWatchSubscriber' in newValue) &&
          typeof InteropExtractorModule.makeObserved !== undefined &&
          typeof InteropExtractorModule.makeObserved === 'function'
        ) {
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

    static getV2InteropObservedObject<T extends Object>(newValue: T, owningProperty: object, propertyKey: string, watchKeyPrefix: string): T {
        const isStaBuiltin =
          globalThis.Panda.STValue.isSTArray(newValue) ||
          globalThis.Panda.STValue.isSTSet(newValue) ||
          globalThis.Panda.STValue.isSTMap(newValue) ||
          newValue instanceof Date;
        if (
          isStaBuiltin &&
          !('addWatchSubscriber' in newValue) &&
          typeof InteropExtractorModule.makeObserved !== undefined &&
          typeof InteropExtractorModule.makeObserved === 'function'
        ) {
          newValue = InteropExtractorModule.makeObserved(newValue) as T;
        }
        if ('addWatchSubscriber' in newValue && typeof (newValue as any).addWatchSubscriber === 'function') {
            const callback = () => {
                ObserveV2.getObserve().fireChange(owningProperty, propertyKey);
            };
            if (typeof InteropExtractorModule.createWatchFunc !== undefined && typeof InteropExtractorModule.createWatchFunc === 'function') {
                const watchStoreKey = `${watchKeyPrefix}${propertyKey}`;
                owningProperty[watchStoreKey] = InteropExtractorModule.createWatchFunc(callback, newValue);
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
    static transferCompatibleDynamicBuilder1?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder2?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder3?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder4?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder5?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder6?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder7?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder8?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder9?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static transferCompatibleDynamicBuilder10?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static createCompatibleStaticState?: (value: Object) => Object;
    static transferCompatibleUpdatableBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
    static localStorageSetProxy?: (storage: Object, proxy: Object) => void;
    static isCloneableObject?: (obj: Object) => boolean;
    static cloneCloneableObject?: (obj: Object) => Object | null | undefined;
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

function registerTransferCompatibleDynamicBuilderCallback1(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder1 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback2(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder2 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback3(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder3 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback4(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder4 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback5(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder5 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback6(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder6 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback7(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder7 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback8(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder8 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback9(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder9 = callback;
}

function registerTransferCompatibleDynamicBuilderCallback10(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleDynamicBuilder10 = callback;
}

function registerCreateCompatibleStaticState(callback: (value: Object) => Object): void {
    InteropExtractorModule.createCompatibleStaticState = callback;
}

function registerTransferCompatibleUpdatableBuilderCallback(callback: (builder: (...args: any[]) => void) => (...args: any[]) => void): void {
    InteropExtractorModule.transferCompatibleUpdatableBuilder = callback;
}

function registerLocalStorageSetProxy(callback: (storage: Object, proxy: Object) => void): void {
     InteropExtractorModule.localStorageSetProxy = callback;
}

function __Interop_RegisterIsCloneableObject_internal_(callback: (obj: Object) => boolean): void {
    InteropExtractorModule.isCloneableObject = callback;
}

function __Interop_RegisterCloneCloneableObject_internal_(callback: (obj: Object) => Object | null | undefined): void {
    InteropExtractorModule.cloneCloneableObject = callback;
}
