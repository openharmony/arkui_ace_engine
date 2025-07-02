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
    constructor(callback: () => void) {
        this.notifyInterop = callback;
    }
    
    public id__(): number {
        return 0;
    }

    public aboutToBeDeleted(owningView?: IPropertySubscriber): void {
        return;
    }

    public hasChanged(newValue: Object): void {
        return;
    }

    public notifyInterop: () => void
    
    public syncPeerHasChanged<T>(eventSource : ObservedPropertyAbstractPU<T>) : void {
        this.notifyInterop();
    }
}

type setValue<T> = (value: T) => void;

function createStateVariable<T>(value: T, callback: setValue<T>, notifyCallback: () => void): ObservedPropertyPU<T> {
    const proxy = new ObservedPropertyPU(value, undefined, 'proxy');
    proxy._setInteropValueForStaticState = callback;
    const subscirbe_Interop = new SubscribeInterop(notifyCallback);
    proxy.addSubscriber(subscirbe_Interop);
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

function openInterop(): void {
    InteropConfigureStateMgmt.instance.openInterop();
}

function closeInterop(): void {
    InteropConfigureStateMgmt.instance.closeInterop();
}

function viewPUCreate(component: ViewPU): void {
    ViewPU.create(component);
}

function createObservedObject(value: Object): Object {
    return ObservedObject.createNew(value, null);
}