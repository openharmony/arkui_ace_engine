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


function isStaticProxy<T extends Object>(obj: T): boolean {
    const prototype = obj?.constructor?.prototype;
    if (prototype === null || prototype === undefined) {
        return false;
    }
    return Object.prototype.hasOwnProperty.call(prototype, '_isStaticProxy') &&
            prototype._isStaticProxy === true;
}

class SubscribeInterop implements ISinglePropertyChangeSubscriber<Object>{
    private id_: number;
    constructor(callback: () => void) {
        this.notifyInterop = callback;
        this.id_ = SubscriberManager.MakeStateVariableId();
        SubscriberManager.Add(this);
    }
    
    public id__(): number {
        return this.id_;
    }

    public aboutToBeDeleted(owningView?: IPropertySubscriber): void {
        return;
    }

    public hasChanged(newValue: Object): void {
        return;
    }

    public notifyInterop: () => void;

    // @Observed no @Track   set to ObservedObject
    onTrackedObjectPropertyCompatModeHasChangedPU<T>(sourceObject: ObservedObject<T>, changedPropertyName: string): void {
        this.notifyInterop();
    }
    
    // @Observed has @Track
    onTrackedObjectPropertyHasChangedPU<T>(sourceObject: ObservedObject<T>, changedPropertyName: string): void {
        this.notifyInterop();
    }
}

type setValue<T> = (value: T) => void;
type WatchFuncType = (propertyName: string) => void;

function createStateVariable<T>(value: T, callback: setValue<T>): ObservedPropertyPU<T> {
    const proxy = new ObservedPropertyPU(value, undefined, 'proxy');
    proxy._setInteropValueForStaticState = callback;
    return proxy;
}

function resetViewPUFindProvideInterop(): void {
    ViewPU._resetFindProvide_ViewPU_Interop();
}

function setFindProvideInterop(callback: (providedPropName: string) => any, view?: ViewPU): void {
    if (view == null) {
        ViewPU._findProvide_ViewPU_Interop = callback;
    } else {
        view.findProvideInterop = callback;
    }
}

function setFindLocalStorageInterop(callback: () => any, view?: ViewPU): void {
    if (view == null) {
        ViewPU._findLocalStorage_ViewPU_Interop = callback;
    } else {
        view.findLocalStorageInterop = callback;
    }
}

function resetViewPUFindLocalStorageInterop(): void {
    ViewPU._resetFindLocalStorage_ViewPU_Interop();
}

function openInterop(): void {
    InteropConfigureStateMgmt.instance.openInterop();
}

function closeInterop(): void {
    InteropConfigureStateMgmt.instance.closeInterop();
}

function viewPUCreate(component: ViewPU): void {
    ViewPU.create(component);
}

function staticStateBindObservedObject(value: Object, staticCallback: () => void): Object {
    if (!ObservedObject.IsObservedObject(value)) {
        value = ObservedObject.createNew(value, null);
    }
    const subscirbeInterop = new SubscribeInterop(staticCallback);
    ObservedObject.addOwningProperty(value, subscirbeInterop);
    return value;
}

function registerCallbackForCreateWatchID(callback: () => any): void {
    InteropExtractorModule.createWatchFunc = callback;
}

function registerCallbackForMakeObserved(callback: (value: Object) => Object): void {
    InteropExtractorModule.makeObserved = callback;
}

/**
 * 
 * @param staticBuilder ArkTS1.2builder, return the pointer of PeerNode
 * @returns  Creates a dynamic builder function that wraps a static builder
 */
function createDynamicBuilder(
    staticBuilder: (...args: any[]) => number
): (...args: any[]) => void {
    let func = function (...args: any[]): void {
        this.observeComponentCreation2((elmtId: number, isInitialRender: boolean) => {
            if (isInitialRender) {
                let pointer = staticBuilder(...args);
                ViewStackProcessor.push(pointer);
            }
        }, {});
        ViewStackProcessor.pop();
    };
    return func;
}