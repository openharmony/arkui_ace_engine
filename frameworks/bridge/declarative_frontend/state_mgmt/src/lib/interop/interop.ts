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
    constructor(callback: (property: string) => void) {
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

    public notifyInterop: (property: string) => void;

    // @Observed no @Track   set to ObservedObject
    onTrackedObjectPropertyCompatModeHasChangedPU<T>(sourceObject: ObservedObject<T>, changedPropertyName: string): void {
        this.notifyInterop(changedPropertyName);
    }
    
    // @Observed has @Track
    onTrackedObjectPropertyHasChangedPU<T>(sourceObject: ObservedObject<T>, changedPropertyName: string): void {
        this.notifyInterop(changedPropertyName);
    }
}

type setValue<T> = (value: T) => void;
type WatchFuncType = (propertyName: string) => void;

function createStateVariable<T>(staticState: Object, value: T, setValueCallback: setValue<T>, notifyCallback: () => void): ObservedPropertyPU<T> {
    const proxy = new ObservedPropertyPU(value, undefined, 'proxy');
    proxy._setInteropValueForStaticState = setValueCallback;
    proxy._notifyInteropFireChange = notifyCallback;
    proxy.setProxy(staticState);
    return proxy;
}

function updateSetValueCallback(observedProperty, setValueCallback): void {
    observedProperty._setInteropValueForStaticState = setValueCallback;
}

function updateNotifyCallback(observedProperty, notifyCallback): void {
    observedProperty._notifyInteropFireChange = notifyCallback;
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

function staticStateBindObservedObject(
    value: Object,
    onPropertyChange: () => void,
    onTrackPropertyRead:(readPropName: string, isTracked: boolean) => void,
    onTrackPropertyChange: (readPropName: string) => void
): void {
    if (TrackedObject.isCompatibilityMode(value)) {
        const subscribeInterop = new SubscribeInterop((property: string) => {
            onPropertyChange()
        });
        ObservedObject.addOwningProperty(value, subscribeInterop);
        return;
    }
    const subscribeInterop = new SubscribeInterop(onTrackPropertyChange);
    const observedObject = new ObservedPropertyObjectPU<Object>(value, undefined, undefined);
    ObservedObject.addOwningProperty(value, subscribeInterop);
    ObservedObject.registerPropertyReadCb(value, (readObject: Object, readPropName: string, isTracked: boolean) => {
        onTrackPropertyRead(readPropName, isTracked)
    }, observedObject)
}

function __Interop_CreateStaticComponent_Internal(
    factory: () => Object,
    options?: () => Object,
    content?: () => void
): [() => void, number] {
    if (InteropExtractorModule.compatibleStaticComponent === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No compatibleStaticComponent Method For Create StaticComponent');
    }
    return InteropExtractorModule.compatibleStaticComponent(factory, options, content);
}

function __Interop_UpdateInteropExtendableComponent_Internal(dynamicComponent: Object): void {
    if (InteropExtractorModule.updateInteropExtendableComponent === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No updateInteropExtendableComponent method For update InteropExtendableComponent');
    }
    return InteropExtractorModule.updateInteropExtendableComponent(dynamicComponent);
}

function __Interop_ResetInteropExtendableComponent_Internal(): void {
    if (InteropExtractorModule.resetInteropExtendableComponent === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No resetInteropExtendableComponent method For reset InteropExtendableComponent');
    }
    return InteropExtractorModule.resetInteropExtendableComponent();
}

function __Interop_TransferCompatibleBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void {
    if(InteropExtractorModule.transferCompatibleBuilder === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No transferCompatibleBuilder method For Transfer CompatibleBuilder');
    }
    return InteropExtractorModule.transferCompatibleBuilder(builder);
}

function __Interop_transferCompatibleDynamicBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void {
    if(InteropExtractorModule.transferCompatibleDynamicBuilder === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No transferCompatibleDynamicBuilder method For Transfer Compatible Dynamic Builder');
    }
    return InteropExtractorModule.transferCompatibleDynamicBuilder(builder);
}

function __Interop_createCompatibleStaticState_Internal(value: Object): Object {
    if(InteropExtractorModule.createCompatibleStaticState === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No createCompatibleStaticState method For createCompatibleStaticState');
    }
    if (value instanceof SynchedPropertyTwoWayPU<Object>) {
        value = value.getRootSource();
    }
    return InteropExtractorModule.createCompatibleStaticState(value);
}

function __Interop_TransferCompatibleUpdatableBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void {
    if(InteropExtractorModule.transferCompatibleUpdatableBuilder === undefined) {
        // only happened in toolchain error, internal error
        throw new BusinessError(NOT_IMPLEMENT, 'No transferCompatibleUpdatableBuilder method For Transfer CompatibleUpdatableBuilder');
    }
    return InteropExtractorModule.transferCompatibleUpdatableBuilder(builder);
}

function createObservedObject(value: Object): Object {
    if (!ObservedObject.IsObservedObject(value)) {
        value = ObservedObject.createNew(value, null);
    }
    return value;
}

function invokeObserveFireChange(target: Object, key: string): void {
    ObserveV2.getObserve().fireChange(RefInfo.get(UIUtilsImpl.instance().getTarget(target)), key);
}