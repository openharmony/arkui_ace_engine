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

import { ExtendableComponent } from './extendableComponent';
import { 
    IProviderDecoratedVariable,
    IProvideDecoratedVariable,
    ProvideDecoratedVariable,
    ProviderDecoratedVariable,
    LocalStorage,
    uiUtils
} from '../stateManagement';
import { finalizerRegisterWithCleaner } from '@koalaui/common';

export class InteropExtendableComponent extends ExtendableComponent {
    dynamicComponent: ESValue;
    originComponent?: WeakRef<ExtendableComponent>;
    private onActiveChange: ESValue = ESValue.wrap((active: boolean): void => {
        this.__setActive__Internal(active);
    });
    constructor(dynamicComponent: ESValue) {
        super();
        this.dynamicComponent = dynamicComponent;
        const prev = ExtendableComponent.current;
        if (prev) {
            this.originComponent = new WeakRef<ExtendableComponent>(prev! as ExtendableComponent);
        }
        this.dynamicComponent.invokeMethod('addActiveChangeListenerForInterop', this.onActiveChange);
        const parent = this.dynamicComponent;
        const listener = this.onActiveChange;
        finalizerRegisterWithCleaner(this, () => {
            parent.invokeMethod('removeActiveChangeListenerForInterop', listener);
        });
    }

    public __setActive__Internal(active: boolean): void {
        this.__propagateToChild__Internal(active, false);
    }

    /** @memo */ build(): void {}

    override __findProvidedVarV2__Internal<T>(providedPropName: string): IProviderDecoratedVariable<T> | undefined {
        const createStaticProvider = (value: Object, viewV2: Object): ProviderDecoratedVariable<Object> => {
            const result = new ProviderDecoratedVariable<Object>(ExtendableComponent.current as ExtendableComponent, providedPropName, providedPropName, value);
            result.viewV2 = viewV2;
            return result;
        }
        const provider = ESValue.getGlobal().getProperty('findDynamicProvider').invoke(this.dynamicComponent, ESValue.wrap(providedPropName), createStaticProvider).unwrap();
        if (provider == undefined) {
            return undefined;
        }
        return provider as IProviderDecoratedVariable<T>;
    }

    override __findProvider__Internal<T>(providedPropName: string): IProviderDecoratedVariable<T> | undefined {
        const result = this.__findProvidedVarV2__Internal(providedPropName);
        if (result == undefined) {
            return undefined;
        }
        return result as IProviderDecoratedVariable<T>;
    }

    override __findProvide__Internal<T>(providedPropName: string): IProvideDecoratedVariable<T> | undefined {
        const value = this.dynamicComponent.invokeMethod('findProvidePU__', ESValue.wrap(providedPropName));
        if (value.unwrap() == undefined) {
            return undefined;
        }
        const getProxy = value.invokeMethod('getProxy').unwrap();
        if (getProxy === undefined && ExtendableComponent.current) {
            const provideVar = new ProvideDecoratedVariable<T>(ExtendableComponent.current as ExtendableComponent, providedPropName, providedPropName, uiUtils.makeV1Observed(value.invokeMethod('get').unwrap()) as T, false);
            provideVar.setProxy(value);
            value.invokeMethod('setProxy', ESValue.wrap(provideVar));
            const setProxyValue = ((newVal: T): void => {
                value.invokeMethod('set', ESValue.wrap(newVal));
            });
            provideVar.setProxyValue = setProxyValue;
            const global = ESValue.getGlobal();
            const setSource = ((newVal: T): void => {
                provideVar.set(newVal);
            });
            const fireChange = (): void => {
                provideVar.fireChange();
            }
            global.getProperty('updateNotifyCallback').invoke(value, ESValue.wrap(fireChange));
            const notifyProxy = (): void => {
                value.invokeMethod('syncPeerHasChanged');
            };
            provideVar.addWatch(notifyProxy);
            global.getProperty('updateSetValueCallback').invoke(value, ESValue.wrap(setSource));
            return provideVar;
        }
        else {
            return getProxy as IProvideDecoratedVariable<T>;
        }
    }

    public get __localStorage__Internal(): LocalStorage {
        const dynamicLocalStorage_ = this.dynamicComponent.getProperty('localStorage_');
        const proxy = dynamicLocalStorage_.invokeMethod('getProxy');
        if (proxy.isNull() || proxy.isUndefined()) {
            const staticLocalStorage_ = new LocalStorage();
            staticLocalStorage_.setProxy(dynamicLocalStorage_);
            dynamicLocalStorage_.invokeMethod('setProxy', ESValue.wrap(staticLocalStorage_));
            return staticLocalStorage_;
        }
        return proxy.unwrap() as LocalStorage;
    }

    override __addProvide__Internal<T>(providedPropName: string, store: IProvideDecoratedVariable<T>, allowOverride?: boolean): void {}

    override __isViewActive__Internal(): boolean {
        return this.dynamicComponent.invokeMethod('isViewActive').unwrap() as boolean;
    }
}

export function updateInteropExtendableComponent(dynamicComponent: Object): void {
    ExtendableComponent.current = new InteropExtendableComponent(ESValue.wrap(dynamicComponent));
}

export function resetInteropExtendableComponent(): void {
    const dynamicComponent = ExtendableComponent.current;
    ExtendableComponent.current = (dynamicComponent as InteropExtendableComponent).originComponent?.deref();
}

export function registerUpdateInteropExtendableComponent(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerUpdateInteropExtendableComponent');
    registerCallback.invoke(updateInteropExtendableComponent);
}

export function registerResetInteropExtendableComponent(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerResetInteropExtendableComponent');
    registerCallback.invoke(resetInteropExtendableComponent);
}



export function createInteropView(staticComponent: ExtendableComponent): ESValue {
    const createState = ESValue.getGlobal().getProperty('createStateVariable');
    const findProvidePU = (providedPropName: string): Object | null => {
        let provide = staticComponent.__findProvide__Internal<Object>(providedPropName);
        if (!provide) {
            return null;
        }
        let state = provide as ProvideDecoratedVariable<Object>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: Object): void => {
                state.set(value);
            });
            const fireChange = (): void => {
                state.fireChange();
            }
            const proxy = createState.invoke(state, ESValue.wrap(state!.get()), ESValue.wrap(setSource), ESValue.wrap(fireChange));
            state.setProxy(proxy);
            const setProxyValue = ((value: Object): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyProxy = (): void => {
                proxy.invokeMethod('syncPeerHasChanged');
            };
            state.addWatch(notifyProxy);
        }
        return state.getProxy()!.unwrap()! as Object;
    };
    const createDummyViewV2 = ESValue.getGlobal().getProperty('createDummyViewV2');
    const findProvider = (varName: string) => {
        const result = (
            staticComponent.__findProvidedVarV2__Internal<Object>(varName) ||
            staticComponent.__findProvider__Internal<Object>(varName)
        ) as ProviderDecoratedVariable<Object> | undefined;
        if (result == undefined) {
            return undefined;
        }
        const value = result.get();
        if (result.viewV2 === undefined) {
            const dummyViewV2 = createDummyViewV2.invoke(result, varName, value).unwrap() as Object;
            result.viewV2 = dummyViewV2;
        }
        return [result.viewV2, varName];
    };
    const findLocalStorageInterop = (): Object => {
        const staticLocalStorage_ = staticComponent.__localStorage__Internal;
        if (staticLocalStorage_.getProxy() === undefined) {
            staticLocalStorage_.setProxy();
        }
        return staticLocalStorage_.getProxy()!.unwrap()! as Object;
    };

    return ESValue.getGlobal().getProperty('createViewInterop').invoke(findProvidePU, findProvider, findLocalStorageInterop);
}