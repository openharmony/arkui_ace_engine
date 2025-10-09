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

function createStateVariable<T>(value: T, setValueCallback: setValue<T>, notifyCallback: () => void): ObservedPropertyPU<T> {
    const proxy = new ObservedPropertyPU(value, undefined, 'proxy');
    proxy._setInteropValueForStaticState = setValueCallback;
    proxy._notifyInteropFireChange = notifyCallback;
    return proxy;
}

function updateSetValueCallback(observedProperty, setValueCallback): void {
    observedProperty._setInteropValueForStaticState = setValueCallback;
}

function updateNotifyCallback(observedProperty, notifyCallback): void {
    observedProperty._notifyInteropFireChange = notifyCallback;
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

function viewPUCreate(component: ViewPU): void {
    ViewPU.create(component);
}

function viewV2Create(component: ViewV2): void {
    ViewV2.create(component);
}

function getRawObjectForInterop(value: Object): Object {
    if ((Array.isArray(value) || value instanceof Set || value instanceof Date || value instanceof Map) &&
        ObservedObject.IsObservedObject(value)) {
        return ObservedObject.GetRawObject(value);
    }
    return value;
}

function staticStateBindObservedObject(value: Object, staticCallback: () => void): Object {
    if (!ObservedObject.IsObservedObject(value)) {
        value = ObservedObject.createNew(value, null);
    }
    const subscirbeInterop = new SubscribeInterop(staticCallback);
    ObservedObject.addOwningProperty(value, subscirbeInterop);
    return value;
}

function __Interop_CreateStaticComponent_Internal(
    factory: () => Object,
    options?: () => Object,
    content?: () => void
): [() => void, number] {
    if (InteropExtractorModule.compatibleStaticComponent === undefined) {
        throw new Error('Non Method For Create StaticComponent');
    }
    return InteropExtractorModule.compatibleStaticComponent(factory, options, content);
}

function __Interop_UpdateInteropExtendableComponent_Internal(dynamicComponent: Object): void {
    if (InteropExtractorModule.updateInteropExtendableComponent === undefined) {
        throw new Error('Non Method For update InteropExtendableComponent');
    }
    return InteropExtractorModule.updateInteropExtendableComponent(dynamicComponent);
}

function __Interop_ResetInteropExtendableComponent_Internal(): void {
    if (InteropExtractorModule.resetInteropExtendableComponent === undefined) {
        throw new Error('Non Method For reset InteropExtendableComponent');
    }
    return InteropExtractorModule.resetInteropExtendableComponent();
}

function __Interop_TransferCompatibleBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void {
    if(InteropExtractorModule.transferCompatibleBuilder === undefined) {
        throw new Error("Non Method For Transfer CompatibleBuilder");
    }
    return InteropExtractorModule.transferCompatibleBuilder(builder);
}

function __Interop_transferCompatibleDynamicBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void {
    if(InteropExtractorModule.transferCompatibleDynamicBuilder === undefined) {
        throw new Error("Non Method For Transfer Compatible Dynamic Builder");
    }
    return InteropExtractorModule.transferCompatibleDynamicBuilder(builder);
}