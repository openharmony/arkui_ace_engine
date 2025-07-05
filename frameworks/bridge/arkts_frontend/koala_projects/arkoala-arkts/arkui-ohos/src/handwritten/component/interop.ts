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

import { ArkUIAniModule } from "arkui.ani"
import { KPointer } from '@koalaui/interop';
import { PeerNode } from '../PeerNode';
import { int32 } from '@koalaui/common';
import { NodeAttach } from '@koalaui/runtime';
import { ExtendableComponent } from './extendableComponent';
import { 
    StateDecoratedVariable, 
    ProvideDecoratedVariable, 
    PropDecoratedVariable,
    LinkDecoratedVariable, 
    ConsumeDecoratedVariable, 
    WatchFunc,
    UIUtils,
} from '../stateManagement';
import { IDecoratedV1Variable, WatchFuncType, WatchIdType } from '../stateManagement/decorator';

export class CompatiblePeerNode extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, view: ESValue, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
        this.view = view;
    }
    public view: ESValue;
    public static create(_peerPtr: KPointer, view: ESValue, flags: int32 = 0): CompatiblePeerNode {
        const peerId = PeerNode.nextId();
        const _peer = new CompatiblePeerNode(_peerPtr, peerId, view, 'ComponentRoot', flags);
        return _peer;
    }
} 

export interface CompatibleComponentInfo {
    name: string,
    component: ESValue
}


/** @memo */
export function compatibleComponent(
    init: () => CompatibleComponentInfo,
    update: (instance: ESValue) => void
): void {
    NodeAttach<CompatiblePeerNode>((): CompatiblePeerNode => {
        let global = ESValue.getGlobal();
        const ptr = ArkUIAniModule._CreateViewStackProcessor();
        openInterop(global);
        const result = init();
        const realComponent = result.component;
        const nodePtr = ArkUIAniModule._PopViewStackProcessor();
        ArkUIAniModule._DeleteViewStackProcessor(ptr);
        return CompatiblePeerNode.create(nodePtr, realComponent);
    }, (node: CompatiblePeerNode) => {
        update(node.view);
    });
}


function openInterop(global: ESValue): void {
    let openInterop = global.getProperty('openInterop');
    openInterop.invoke();
    registerCreateWatchFuncCallback();
    registerCreateStaticObservedCallback();
}

function closeInterop(global: ESValue): void {
    let closeInterop = global.getProperty('closeInterop');
    closeInterop.invoke();
}


export type CompatibleStateChangeCallback<T> = (value: T) => void;

type StateUnion<T> = StateDecoratedVariable<T> | ProvideDecoratedVariable<T> | PropDecoratedVariable<T>

export function bindCompatibleProvideCallback(staticComponent: ExtendableComponent,
    createState: ESValue, setCallback: ESValue, component?: ESValue): void {
    const callback = (providedPropName: string): Object | null => {
        let provide = staticComponent.findProvide<Object>(providedPropName);
        if ((provide === null)) {
            return provide;
        }
        let state = provide as ProvideDecoratedVariable<Object>;
        if (state.getProxy() === undefined) {
            let setSource = ((value: Object) => {
                state!.set(value);
            });
            let proxy = createState.invoke(ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            let setProxy = ((value: Object) => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxy;
            let notifyCallback = ((propertyName: string) => {
                proxy.invokeMethod('notifyPropertyHasChangedPU');
            });
            state.setNotifyCallback(notifyCallback);
        }
        return state.getProxy()!.unwrap()! as Object;
    }
    setCallback.invoke(callback, component);
    return;
}

export function getCompatibleState<T>(staticState: IDecoratedV1Variable<T>, createState: ESValue): ESValue {
    let source = staticState;

    let isLink = staticState instanceof LinkDecoratedVariable;
    let isConsume = staticState instanceof ConsumeDecoratedVariable;

    if (isLink) {
        source = (staticState as LinkDecoratedVariable<T>).getSource();
    } else if (isConsume) {
        source = (staticState as ConsumeDecoratedVariable<T>).getSource();
    }

    let isState = source instanceof StateDecoratedVariable;
    let isProvide = source instanceof ProvideDecoratedVariable;
    let isProp = source instanceof PropDecoratedVariable;

    if (isState) {
        let state = source as StateDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            let setSource = ((value: T) => {
                state.set(value);
            });
            let proxy = createState.invoke(ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            let setProxyValue = ((value: T) => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            let notifyCallback = ((propertyName: string) => {
                proxy.invokeMethod('notifyPropertyHasChangedPU');
            });
            state.setNotifyCallback(notifyCallback);
        }
        return state.getProxy()!;
    } else if (isProvide) {
        let state = source as ProvideDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            let setSource = ((value: T) => {
                state.set(value);
            });
            let proxy = createState.invoke(ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            let setProxyValue = ((value: T) => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            let notifyCallback = ((propertyName: string) => {
                proxy.invokeMethod('notifyPropertyHasChangedPU');
            });
            state.setNotifyCallback(notifyCallback);
        }
        return state.getProxy()!;
    } else if (isProp) {
        let state = source as PropDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            let setSource = ((value: T) => {
                state.set(value);
            });
            let proxy = createState.invoke(ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            let setProxyValue = ((value: T) => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            let notifyCallback = ((propertyName: string) => {
                proxy.invokeMethod('notifyPropertyHasChangedPU');
            });
            state.setNotifyCallback(notifyCallback);
        }
        return state.getProxy()!;
    }
    throw Error('Error getStateProxy.');
}

export function isDynamicObject<T>(value: T): boolean {
    return ESValue.wrap(value).isECMAObject();
}

export function getObservedObject<T>(value: T, staticState: StateUnion<T>): T {
    const callback = (): void => {
        staticState.fireChange();
    };
    let global = ESValue.getGlobal();
    let staticStateBindObservedObject = global.getProperty('staticStateBindObservedObject');
    return staticStateBindObservedObject.invoke(ESValue.wrap(value), ESValue.wrap(callback)).unwrap()! as Object as T;
}

export function registerCreateWatchFuncCallback(): void {
    const createWatchFuncCallback = (callback: WatchFuncType): WatchIdType => {
        const watchFunc = new WatchFunc(callback);
        return watchFunc.id();
    }
    let global = ESValue.getGlobal();
    let registerCallback = global.getProperty('registerCallbackForCreateWatchID');
    registerCallback.invoke(createWatchFuncCallback);
    return;
}

export function registerCreateStaticObservedCallback(): void {
    const makeObservedcallback = (value: Object): Object => {
        return UIUtils.makeObserved(value) as Object;
    }
    let global = ESValue.getGlobal();
    let registerCallback = global.getProperty('registerCallbackForMakeObserved');
    registerCallback.invoke(makeObservedcallback);
    return;
}