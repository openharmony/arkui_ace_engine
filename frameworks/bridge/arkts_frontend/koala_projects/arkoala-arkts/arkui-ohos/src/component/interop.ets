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

import { ArkUIAniModule } from 'arkui.ani'
import { KPointer } from '@koalaui/interop';
import { PeerNode, findPeerNode } from '../PeerNode';
import { int32 } from '@koalaui/common';
import { __context, __id, GlobalStateManager, IncrementalNode, memoEntry, memoEntry1, mutableState, MutableState, NodeAttach } from '@koalaui/runtime';
import { StateContext } from 'arkui.incremental.runtime.state';
import { ExtendableComponent } from './extendableComponent';
import { 
    StateDecoratedVariable, 
    ProvideDecoratedVariable, 
    PropDecoratedVariable,
    PropRefDecoratedVariable,
    LinkDecoratedVariable, 
    ConsumeDecoratedVariable, 
    InteropWatchFunc,
    uiUtils,
    IObservedObject,
    OBSERVE,
    LocalStorage
} from '../stateManagement';
import { ObserveSingleton } from "arkui/stateManagement/base/observeSingleton";
import { IDecoratedV1Variable, WatchFuncType, WatchIdType } from '../stateManagement/decorator';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { DetachedRootEntryImpl, UIContextImpl } from 'arkui/base/UIContextImpl';
import { CustomComponent, CustomDelegate, BaseCustomComponent } from './customComponent';
import { setNeedCreate } from '../ArkComponentRoot';
import { StateMgmtTool } from '#stateMgmtTool';
import { ArkContentSlotPeer } from './contentSlot';
import { ArkCustomComponentRootPeer } from "#generated";
import {
    registerUpdateInteropExtendableComponent,
    registerResetInteropExtendableComponent,
    createInteropView
} from './interopExtendableComponent';
import { ThemeColorMode } from "arkui/component/common"
import { ArkThemeNativeHelper } from "arkui/theme/ArkThemeNativeHelper"
import { ArkThemeScopeManager } from "arkui/theme/ArkThemeScopeManager"

import { StateManagerImpl } from '@koalaui/runtime';
import { MutableStateMeta } from '../stateManagement/base/mutableStateMeta';
import { NavPathInfo, NavPathStackInternal, NavigationOptions, NavigationInterception } from "../component/navigation";

export class CompatiblePeerNode extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, view: ESValue, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
        this.view = view;
        this.view.setProperty('isCompFreezeAllowed_', ESValue.wrap(true));
    }
    public view: ESValue;
    public static create(_peerPtr: KPointer, view: ESValue, flags: int32 = 0): CompatiblePeerNode {
        const peerId = PeerNode.nextId();
        const _peer = new CompatiblePeerNode(_peerPtr, peerId, view, 'ComponentRoot', flags);
        return _peer;
    }
    private staticParent?: ExtendableComponent;
    private onActiveChange: (active: boolean, isReuse: boolean) => void = (active: boolean, isReuse: boolean): void => {
        this.setActive(active);
    };
    public setStaticParent(parent?: ExtendableComponent): void {
        this.staticParent = parent;
        this.staticParent?.__addActiveChangeListenerForInterop__Internal(this.onActiveChange);
    }
    public setActive(active: boolean): void {
        this.view.invokeMethod('setActiveInternal', ESValue.wrap(active));
    }
    public dispose(): void {
        this.staticParent?.__removeActiveChangeListenerForInterop__Internal(this.onActiveChange);
        this.staticParent = undefined;
        super.dispose();
    }
}

export interface CompatibleComponentInfo {
    name: string,
    component: ESValue
}


/** @memo */
export function compatibleComponent(
    init: (parent: ESValue) => CompatibleComponentInfo,
    update: (instance: ESValue) => void,
    component?: ExtendableComponent
): void {
    NodeAttach<CompatiblePeerNode>((): CompatiblePeerNode => {
        let global = ESValue.getGlobal();
        let staticComponent = component;
        const ptr = ArkUIAniModule._CreateViewStackProcessor();
        if (staticComponent === undefined) {
            staticComponent = (ExtendableComponent.current) as (ExtendableComponent | undefined);
        }
        let current = (GlobalStateManager.instance as StateManagerImpl).current;
        (GlobalStateManager.instance as StateManagerImpl).current = undefined;
        const viewInterop = staticComponent ? createInteropView(staticComponent) : ESValue.instantiateEmptyObject();
        const result = init(viewInterop);
        (GlobalStateManager.instance as StateManagerImpl).current = current;
        const dynamicComponent = result.component;
        const nodePtr = ArkUIAniModule._PopViewStackProcessor();
        ArkUIAniModule._DeleteViewStackProcessor(ptr);
        const node = CompatiblePeerNode.create(nodePtr, dynamicComponent);
        node.setStaticParent(staticComponent);
        return node;
    }, (node: CompatiblePeerNode) => {
        ArkThemeScopeManager.getInstance().applyWithThemeForCompatibleComponent(node.view);
        update(node.view);
        ArkThemeScopeManager.getInstance().popWithThemeForCompatibleComponent();
    });
}

export function compatibleStaticComponent<T extends BaseCustomComponent<T_Options>, T_Options>(
    factory: () => T,
    options?: () => T_Options,
    content?: () => void
): [() => void, number] {
    const instantiateImpl = /** @memo */ (): void => {
        BaseCustomComponent._invokeImpl(undefined, factory, options, undefined, content);
    };

    const uiContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
    let manager = uiContext.stateMgr;
    if (manager === undefined) {
        manager = GlobalStateManager.instance;
    }

    ArkThemeScopeManager.getInstance().applyColorModeFromThemeScope();
    
    const node = manager.updatableNode(new IncrementalNode(), (context: StateContext) => {
        const frozen = manager.frozen;
        manager.frozen = true;
        ArkUIAniModule._Common_Sync_InstanceId(uiContext.getInstanceId());
        let r = OBSERVE.renderingComponent;
        OBSERVE.renderingComponent = ObserveSingleton.RenderingComponentV1;
        const needCreate = setNeedCreate(true);
        memoEntry<void>(context, 0, instantiateImpl);
        setNeedCreate(needCreate);
        OBSERVE.renderingComponent = r;
        ArkUIAniModule._Common_Restore_InstanceId();
        manager.frozen = frozen;
    });

    const inc = node.value;
    const peerNode = findPeerNode(inc);
    if (peerNode === undefined) {
        node.dispose();
        return [() => {}, 0];
    }
    const staticComponent = (peerNode as ArkCustomComponentRootPeer).getComponent();
    uiContext.getDetachedRootEntryManager().detachedRoots_.set(peerNode.peer.ptr, new DetachedRootEntryImpl<IncrementalNode>(node));
    ArkThemeScopeManager.getInstance().restoreColorMode()
    return [
        () => {
            ArkThemeScopeManager.getInstance().executeReload(node);
            (staticComponent as CustomDelegate<T, T_Options>).__updateStruct(options ? options() : undefined);
            }, 
            peerNode.getPeerPtr() as number,
        ];
}

function openInterop(): void {
    const global = ESValue.getGlobal();
    if (!global) {
        throw Error('cannot find ArkTS1.1 global.');
    }
    const openInterop = global.getProperty('openInterop');
    openInterop.invoke();
    registerCreateWatchFuncCallback();
    registerCreateStaticObservedCallback();
    registerCompatibleStaticComponentCallback();
    registerMakeBuilderParameterStaticProxy();
    registerUpdateInteropExtendableComponent();
    registerResetInteropExtendableComponent();
    registerTransferCompatibleBuilderCallback();
    registertransferCompatibleDynamicBuilderCallback();
    registerCreateCompatibleStaticState();
    registerTransferCompatibleUpdatableBuilderCallback();
    registerNavPathStackCallback();
    registerLocalStorageSetProxy();
}

function closeInterop(): void {
    const global = ESValue.getGlobal();
    const closeInterop = global.getProperty('closeInterop');
    closeInterop.invoke();
}


export type CompatibleStateChangeCallback<T> = (value: T) => void;

type StateUnion<T> = StateDecoratedVariable<T> | ProvideDecoratedVariable<T> | PropDecoratedVariable<T> | PropRefDecoratedVariable<T>;

export function getCompatibleState<T>(staticState: IDecoratedV1Variable<T>): ESValue {
    const global = ESValue.getGlobal();
    const createState = global.getProperty('createStateVariable');
    let source = staticState;

    const isLink = staticState instanceof LinkDecoratedVariable;
    const isConsume = staticState instanceof ConsumeDecoratedVariable;

    if (isLink) {
        source = (staticState as LinkDecoratedVariable<T>).getSource();
    } else if (isConsume) {
        source = (staticState as ConsumeDecoratedVariable<T>).getSource();
    }

    const isState = source instanceof StateDecoratedVariable;
    const isProvide = source instanceof ProvideDecoratedVariable;
    const isProp = source instanceof PropDecoratedVariable;
    const isPropRef = source instanceof PropRefDecoratedVariable;

    if (isState) {
        let state = source as StateDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: T): void => {
                state.set(value);
            });
            const fireChange = (): void => {
                state.fireChange();
            }
            const proxy = createState.invoke(ESValue.wrap(state), ESValue.wrap(state!.get()), ESValue.wrap(setSource), ESValue.wrap(fireChange));
            state.setProxy(proxy);
            const setProxyValue = ((value: T): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyProxy = (): void => {
                proxy.invokeMethod('syncPeerHasChanged');
            };
            state.addWatch(notifyProxy);
        }
        return state.getProxy()!;
    } else if (isProvide) {
        let state = source as ProvideDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: T): void => {
                state.set(value);
            });
            const fireChange = (): void => {
                state.fireChange();
            }
            const proxy = createState.invoke(ESValue.wrap(state), ESValue.wrap(state!.get()), ESValue.wrap(setSource), ESValue.wrap(fireChange));
            state.setProxy(proxy);
            const setProxyValue = ((value: T): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyProxy = (): void => {
                proxy.invokeMethod('syncPeerHasChanged');
            };
            state.addWatch(notifyProxy);
        }
        return state.getProxy()!;
    } else if (isProp) {
        let state = source as PropDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: T): void => {
                state.set(value);
            });
            const fireChange = (): void => {
                state.fireChange();
            }
            const proxy = createState.invoke(ESValue.wrap(state), ESValue.wrap(state!.get()), ESValue.wrap(setSource), ESValue.wrap(fireChange));
            state.setProxy(proxy);
            const setProxyValue = ((value: T): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyProxy = (): void => {
                proxy.invokeMethod('syncPeerHasChanged');
            };
            state.addWatch(notifyProxy);
        }
        return state.getProxy()!;
    } else if (isPropRef) {
        let state = source as PropRefDecoratedVariable<T>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: T): void => {
                state.set(value);
            });
            const fireChange = (): void => {
                state.fireChange();
            }
            const proxy = createState.invoke(ESValue.wrap(state), ESValue.wrap(state!.get()), ESValue.wrap(setSource), ESValue.wrap(fireChange));
            state.setProxy(proxy);
            const setProxyValue = ((value: T): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyProxy = (): void => {
                proxy.invokeMethod('syncPeerHasChanged');
            };
            state.addWatch(notifyProxy);
        }
        return state.getProxy()!;
    }
    throw Error('Error getStateProxy.');
}

export function isDynamicObject<T>(value: T): boolean {
    if (value instanceof ESValue) {
        return false;
    }
    return ESValue.wrap(value).isECMAObject();
}

export function getRawObject<T>(value: T): T {
    const global = ESValue.getGlobal();
    const getRawObjectForInterop = global.getProperty('getRawObjectForInterop');
    return getRawObjectForInterop.invoke(ESValue.wrap(value)).unwrap()! as Object as T;
}

export function getObservedObject<T>(value: T): T {
    const global = ESValue.getGlobal();
    const createObservedObject = global.getProperty('createObservedObject');
    return createObservedObject.invoke(ESValue.wrap(value)).unwrap()! as Object as T;
}

export function registerCreateWatchFuncCallback(): void {
    const createWatchFuncCallback = (callback: WatchFuncType, value: Object): InteropWatchFunc => {
        const watchFunc = new InteropWatchFunc(callback);
        const watchFuncId = watchFunc.id();
        (value as IObservedObject).addWatchSubscriber(watchFuncId);
        return watchFunc;
    }
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerCallbackForCreateWatchID');
    registerCallback.invoke(createWatchFuncCallback);
}

export function registerCreateStaticObservedCallback(): void {
    const makeObservedcallback = (value: Object): Object => {
        return uiUtils.makeV1Observed(value) as Object;
    }
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerCallbackForMakeObserved');
    registerCallback.invoke(makeObservedcallback);
}

export function registerCompatibleStaticComponentCallback(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerCompatibleStaticComponentCallback');
    registerCallback.invoke(compatibleStaticComponent);
}

export function registerMakeBuilderParameterStaticProxy(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerMakeBuilderParameterStaticProxy');
    registerCallback.invoke(makeBuilderParameterStaticProxy);
}

export function registerTransferCompatibleBuilderCallback(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerTransferCompatibleBuilderCallback');
    const callback = (builder: Any) => { return transferCompatibleBuilder(builder).unwrap()!};
    registerCallback.invoke(callback);
}

export function registerTransferCompatibleUpdatableBuilderCallback(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerTransferCompatibleUpdatableBuilderCallback');
    const callback = (builder: (args: Any) => void) => { return transferCompatibleUpdatableBuilder(builder).unwrap()!};
    registerCallback.invoke(callback);
}

type ESValueOrUndefined  = ESValue | undefined;

/** @memo */
export function compatibleWrappedBuilder(builder: Any, ...args: FixedArray<ESValue>): void {
    compatibleWrappedBuilderInternal(builder, ...args);
}

/** @memo */
export function compatibleWrappedBuilderInternal(builder: Any, ...args: FixedArray<ESValueOrUndefined>): void {
    compatibleComponent((() => {
        const global = ESValue.getGlobal();
        const viewStackProcessor = global.getProperty('ViewStackProcessor');
        const createId = viewStackProcessor.getProperty('AllocateNewElmetIdForNextComponent');
        const elmtId = createId.invoke();

        let component: ESValue;
        let createCompatibleNode: ESValue;
        let current = (GlobalStateManager.instance as StateManagerImpl).current;
        (GlobalStateManager.instance as StateManagerImpl).current = undefined;
        switch (args.length) {
            case 0:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFuncVoid');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId);
                break;
            case 1:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0]);
                break;
            case 2:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc2');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0], args[1]);
                break;
            case 3:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc3');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0], 
                    args[1], args[2]);
                break;
            case 4:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc4');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0], 
                    args[1], args[2], args[3]);
                break;
            case 5:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc5');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0], 
                    args[1], args[2], args[3], args[4]);
                break;
            case 6:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc6');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0],
                    args[1], args[2], args[3], args[4], args[5]);
                break;
            case 7:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc7');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0],
                    args[1], args[2], args[3], args[4], args[5], args[6]);
                break;
            case 8:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc8');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0],
                    args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                break;
            case 9:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc9');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0],
                    args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
                break;
            case 10:
                createCompatibleNode = global.getProperty('createCompatibleNodeWithFunc10');
                component = createCompatibleNode.invoke(ESValue.wrap(builder), elmtId, args[0],
                    args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
                break;
            default:
                throw Error('Error arguments in Legacy Builder Function');
        }
        const viewPUCreate = global.getProperty('viewPUCreate');
        viewPUCreate.invoke(component);
        (GlobalStateManager.instance as StateManagerImpl).current = current;
        return {
            component: component,
            name: 'compatibleWrappedBuilder',
        };
    }), ((instance: ESValue) => {
        if (args.length !== 1) {
            return;
        }
        const param = args[0] as ESValue;
        if (param.typeOf() !== 'object') {
            return;
        }
        const stateParam = instance.getProperty('arg1') as ESValue;
        const rawValue = param.unwrap()!;
        const global = ESValue.getGlobal();
        const invokeObserveFireChange = global.getProperty('invokeObserveFireChange');
        if (isDynamicObject(rawValue)) {
            const isDynamicBuilderProxy = global.getProperty('isDynamicBuilderProxy').invoke(param).unwrap() as boolean;
            if (isDynamicBuilderProxy) {
                const getBuilderParamProxyEntries = global.getProperty('getBuilderParamProxyEntries');
                const entries = getBuilderParamProxyEntries.invoke(param).unwrap()! as Array<Any>;
                entries.forEach((entry)=>{
                    entry = entry as Array<Any>;
                    stateParam.setProperty(ESValue.wrap(entry[0]), ESValue.wrap(entry[1]));
                    invokeObserveFireChange.invoke(stateParam, ESValue.wrap(entry[0]));
                })
            } else {
                let it = param.keys();
                while (true) {
                    const result = it.next();
                    if (result.done) {
                        break;
                    }
                    stateParam.setProperty(result.value as ESValue, param.getProperty(result.value as ESValue));
                }
            }
        } else {
            const target = (reflect.Value.of(rawValue) as ClassValue).getFieldByName('@target').getData() as Object;
            const keys = Object.keys(target);
            if (rawValue instanceof IObservedObject) {
                const PREFIX = '__backing_';
                keys.forEach((key)=>{
                    if(key.startsWith(PREFIX)){
                        const value = (reflect.Value.of(target) as ClassValue).getFieldByName(key).getData() as Object;
                        stateParam.setProperty(key.slice(PREFIX.length), value);
                        invokeObserveFireChange.invoke(stateParam, ESValue.wrap(key.slice(PREFIX.length)));
                    }
                })
            } else {
                keys.forEach((key)=>{
                    const value = (reflect.Value.of(target) as ClassValue).getFieldByName(key).getData() as Object;
                    stateParam.setProperty(key, value);
                    invokeObserveFireChange.invoke(stateParam, ESValue.wrap(key));
                })
            }
        }
        const runPendingJobs = global.getProperty('runPendingJobs');
        runPendingJobs.invoke();
    }));
}

export function transferCompatibleBuilder<T extends Function>(
    /** @memo */
    builder: T
): ESValue {
    const staticBuilderFunc = (...params: FixedArray<Any>): number => {
        /** @memo */
        const func = () => {
            builder.unsafeCall(...[__context(), __id(), ...params]);
        };

        const uiContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        let manager = uiContext.stateMgr;
        if (manager === undefined) {
            manager = GlobalStateManager.instance;
        }
        const node = manager.updatableNode(ArkContentSlotPeer.create(undefined) as PeerNode, (context: StateContext) => {
            const frozen = manager.frozen;
            manager.frozen = true;
            ArkUIAniModule._Common_Sync_InstanceId(uiContext.getInstanceId());
            let r = OBSERVE.renderingComponent;
            OBSERVE.renderingComponent = ObserveSingleton.RenderingComponentV1;
            memoEntry<void>(context, 0, func);
            OBSERVE.renderingComponent = r;
            ArkUIAniModule._Common_Restore_InstanceId();
            manager.frozen = frozen;
        });

        const ptr = node.value.peer.ptr;
        uiContext.getDetachedRootEntryManager().detachedRoots_.set(ptr, new DetachedRootEntryImpl<PeerNode>(node));
        return ptr as number;
    }
    const createDynamicBuilder = ESValue.getGlobal().getProperty('createDynamicBuilder');
    const dynamicBuilder = createDynamicBuilder.invoke(ESValue.wrap(staticBuilderFunc));
    return dynamicBuilder;
}


export function transferCompatibleUpdatableBuilder<T extends Object>(
    /** @memo */
    builder: (args: T) => void
): ESValue {
    const staticBuilderFunc = (args: T): [number, ()=>void] => {
        let state: MutableState<int32> | undefined;
        if (isDynamicObject(args)) {
            state = updateDynamicObjectForInterop(args);
        } else {
            const objType = Type.of(args);
            let handler = objType instanceof ClassType && (objType as ClassType).getName().endsWith('@Proxy')
            ? (proxy.Proxy.tryGetHandler(args) as InteropBuilderLiteralProxyHandler<T>) // a very slow call so need to judge proxy first
            : undefined;
            if (handler) {
                state = handler!.state;
            }
        }
        const uiContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        let manager = uiContext.stateMgr;
        if (manager === undefined) {
            manager = GlobalStateManager.instance;
        }
        const node = manager.updatableNode(ArkContentSlotPeer.create(undefined) as PeerNode, (context: StateContext) => {
            const frozen = manager.frozen;
            manager.frozen = true;
            ArkUIAniModule._Common_Sync_InstanceId(uiContext.getInstanceId());
            let r = OBSERVE.renderingComponent;
            OBSERVE.renderingComponent = ObserveSingleton.RenderingComponentV1;
            memoEntry1<T, void>(context, 0, builder, args);
            OBSERVE.renderingComponent = r;
            ArkUIAniModule._Common_Restore_InstanceId();
            manager.frozen = frozen;
        });
        const ptr = node.value.peer.ptr;
        uiContext.getDetachedRootEntryManager().detachedRoots_.set(ptr, new DetachedRootEntryImpl<PeerNode>(node));
        return [ptr as number, ()=>{ if (state) { state.value++; } }];
    }
    const createDynamicUpdatableBuilder = ESValue.getGlobal().getProperty('createDynamicUpdatableBuilder');
    const dynamicBuilder = createDynamicUpdatableBuilder.invoke(ESValue.wrap(staticBuilderFunc));
    return dynamicBuilder;
}

/**
 * Creates a proxy for static object literal in the ArkTS 1.1 context
 * to intercept property getter operations.
 */
function makeBuilderParameterStaticProxy<T extends Object>(name: string, value: T, sourceGetter: Any): T {
    const result = proxy.Proxy.create(value, new InteropBuilderLiteralProxyHandler<T>(sourceGetter));
    return result;
}

/**
 * Empowers the proxy object of a dynamic object with ArkTS 1.2's dependency addition capability
 * through hook functions, thereby enabling it to refresh the 1.2 UI.
 */
function updateDynamicObjectForInterop(args: Any): MutableState<int32> | undefined {
    let state: MutableState<int32> = StateMgmtTool.getGlobalStateManager().mutableState<int32>(0, true);
    const startHookFunc = ESValue.getGlobal().getProperty('startStaticHook');
    const result = startHookFunc.invoke(ESValue.wrap(args), ESValue.wrap(()=>{ state.value })).unwrap();
    if (result === undefined) {
        return undefined;
    }
    return state;
}

class InteropBuilderLiteralProxyHandler<T extends Object> extends proxy.DefaultProxyHandler<T> {
    source: ESValue;
    state: MutableState<int32>;
    constructor(source: Any) {
        this.source = ESValue.wrap(source)
        this.state = StateMgmtTool.getGlobalStateManager().mutableState<int32>(0, true);
    }

    override get(target: T, name: string): Any {
        const propertyGetter: ESValue = this.source.getPropertySafe(name);
        if (propertyGetter === ESValue.Undefined) {
            return super.get(target, name);
        }
        this.state.value;
        return propertyGetter.invoke().unwrap();
    }
}

function registertransferCompatibleDynamicBuilderCallback(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerTransferCompatibleDynamicBuilderCallback');
    registerCallback.invoke(transferCompatibleDynamicBuilder);
}

// -------------------- code below for navigation interop --------------------
function parseInfoFromJsonElement(infoElement: jsonx.JsonElement): NavPathInfo | undefined {
    let name: string | undefined = infoElement.tryGetString('name');
    if (name === undefined) {
        return undefined;
    }
    let paramObj: Object | undefined = infoElement.tryGetElement('param');
    let isEntry: boolean | undefined = infoElement.tryGetBoolean('isEntry');
    return new NavPathInfo(name, paramObj, undefined, isEntry);
} 

function parseNumberArrayFromJson(jsonArray: string): Array<int32> {
    let array = new Array<int32>();
    let elementArray = JSON.parseJsonElement(jsonArray).tryAsArray();
    if (elementArray === undefined) {
        return array;
    }
    for (let index = 0; index < elementArray.length; index ++) {
        let value = elementArray[index].tryAsInteger();
        if (value) {
            array.push(value.toInt());
        }
    }
    return array;
}

function pushPathCallback(stack: KPointer, info: string, optionParam?: boolean | NavigationOptions): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    let navPathInfo = parseInfoFromJsonElement(JSON.parseJsonElement(info));
    if (navPathInfo === undefined) {
        return;
    }
    // for override
    if (optionParam === undefined) {
        navStack.pushPath(navPathInfo, true);
    } else if (typeof optionParam === 'boolean') {
        navStack.pushPath(navPathInfo, optionParam as boolean);
    } else {
        navStack.pushPath(navPathInfo, optionParam as NavigationOptions);
    }
}

function pushDestinationCallback(stack: KPointer, info: string, optionParam?: boolean | NavigationOptions): Promise<void> {
    let promise = new Promise<void>((resolve, reject) => {});
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return promise;
    }
    let navPathInfo = parseInfoFromJsonElement(JSON.parseJsonElement(info));
    if (navPathInfo === undefined) {
        return promise;
    }
    // for override
    if (optionParam === undefined) {
        promise = navStack.pushDestination(navPathInfo, true);
    } else if (typeof optionParam === 'boolean') {
        navStack.pushDestination(navPathInfo, optionParam as boolean);
    } else {
        navStack.pushDestination(navPathInfo, optionParam as NavigationOptions);
    }
    return promise;
}

function pushPathByNameCallback(stack: KPointer, name: string, param: string, animated?: boolean): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    let paramObj: Object = JSON.parseJsonElement(param) as Object;
    navStack.pushPathByName(name, paramObj, animated);
}

function pushDestinationByNameCallback(stack: KPointer, name: string, param: string, animated?: boolean): Promise<void> {
    let promise = new Promise<void>((resolve, reject) => {});
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return promise;
    }
    let paramObj: Object = JSON.parseJsonElement(param) as Object;
    promise = navStack.pushDestinationByName(name, paramObj, animated);
    return promise;
}

function replacePathCallback(stack: KPointer, info: string, optionParam?: boolean | NavigationOptions): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    let navPathInfo = parseInfoFromJsonElement(JSON.parseJsonElement(info));
    if (navPathInfo === undefined) {
        return;
    }
    // for override
    if (optionParam === undefined) {
        navStack.replacePath(navPathInfo, true);
    } else if (typeof optionParam === 'boolean') {
        navStack.replacePath(navPathInfo, optionParam as boolean);
    } else {
        navStack.replacePath(navPathInfo, optionParam as NavigationOptions);
    }
}

function replaceDestinationCallback(stack: KPointer, info: string, optionParam?: NavigationOptions): Promise<void> {
    let promise = new Promise<void>((resolve, reject) => {});
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return promise;
    }
    let navPathInfo = parseInfoFromJsonElement(JSON.parseJsonElement(info));
    if (navPathInfo === undefined) {
        return promise;
    }
    // no override
    promise = navStack.replaceDestination(navPathInfo, optionParam);
    return promise;
}

function replacePathByNameCallback(stack: KPointer, name: string, param: string, animated?: boolean): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    let paramObj: Object = JSON.parseJsonElement(param) as Object;
    navStack.replacePathByName(name, paramObj, animated);
}

function removeByIndexesCallback(stack: KPointer, indexes: string): number {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return 0;
    }
    // return navStack.removeByIndexes(parseNumberArrayFromJson(indexes));
    return -1;
}

function removeByNameCallback(stack: KPointer, name: string): number {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return -1;
    }
    return navStack.removeByName(name);
}

function removeByNavDestinationIdCallback(stack: KPointer, navDestinationId: string): boolean {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return false;
    }
    return navStack.removeByNavDestinationId(navDestinationId);
}

function popCallback(stack: KPointer, animated?: boolean): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return 'undefined';
    }
    return JSON.stringify(navStack.pop(animated));
}

function popToNameCallback(stack: KPointer, name: string): number {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return -1;
    }
    return navStack.popToName(name);
}

function popToIndexCallback(stack: KPointer, index: number): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    navStack.popToIndex(index.toInt());
}

function moveToTopCallback(stack: KPointer, name: string): number {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return -1;
    }
    return navStack.moveToTop(name);
}

function moveIndexToTopCallback(stack: KPointer, index: number): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    navStack.moveIndexToTop(index.toInt());
}

function clearCallback(stack: KPointer, animated?: boolean): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    navStack.clear(animated);
}

function getAllPathNameCallback(stack: KPointer): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return "[]";
    }
    return JSON.stringify(navStack.getAllPathName());
}

function getParamByIndexCallback(stack: KPointer, index: number): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return "[]";
    }
    return JSON.stringify(navStack.getParamByIndex(index.toInt()));
}

function getParamByNameCallback(stack: KPointer, name: string): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return "[]";
    }
    return JSON.stringify(navStack.getParamByName(name));
}

function getIndexByNameCallback(stack: KPointer, name: string): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return "[]";
    }
    return JSON.stringify(navStack.getIndexByName(name));
}

function getParentCallback(stack: KPointer): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return "undefined";
    }
    return JSON.stringify(navStack.getParent());
}

function sizeCallback(stack: KPointer): number {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return 0;
    }
    return navStack.size();
}

function disableAnimationCallback(stack: KPointer, disable: boolean): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    navStack.disableAnimation(disable);
}

function setInterceptionCallback(stack: KPointer, interception: NavigationInterception): void {
    // not impl yet
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    navStack.setInterception(interception);
}

function getPathStackCallback(stack: KPointer): string {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return '[]';
    }
    return JSON.stringify(navStack.getPathStack());
}

function setPathStackCallback(stack: KPointer, pathStack: string, animated?: boolean): void {
    let navStack = NavPathStackInternal.fromPtr(stack);
    if (navStack === undefined) {
        return;
    }
    // navStack.setPathStack()
}

function registerNavPathStackCallback(): void {
    const global = ESValue.getGlobal();

    const registeNavPushPathCallback = global.getProperty('registeNavPushPathCallback');
    registeNavPushPathCallback.invoke(pushPathCallback);

    const registeNavPushDestinationCallback = global.getProperty('registeNavPushDestinationCallback');
    registeNavPushDestinationCallback.invoke(pushDestinationCallback);

    const registeNavPushPathByNameCallback = global.getProperty('registeNavPushPathByNameCallback');
    registeNavPushPathByNameCallback.invoke(pushPathByNameCallback);

    const registeNavPushDestinationByNameCallback = global.getProperty('registeNavPushDestinationByNameCallback');
    registeNavPushDestinationByNameCallback.invoke(pushDestinationByNameCallback);

    const registeNavReplacePathCallback = global.getProperty('registeNavReplacePathCallback');
    registeNavReplacePathCallback.invoke(replacePathCallback);

    const registeNavReplaceDestinationCallback = global.getProperty('registeNavReplaceDestinationCallback');
    registeNavReplaceDestinationCallback.invoke(replaceDestinationCallback);

    const registeNavReplacePathByNameCallback = global.getProperty('registeNavReplacePathByNameCallback');
    registeNavReplacePathByNameCallback.invoke(replacePathByNameCallback);

    const registeNavRemoveByIndexesCallback = global.getProperty('registeNavRemoveByIndexesCallback');
    registeNavRemoveByIndexesCallback.invoke(removeByIndexesCallback);

    const registeNavRemoveByNameCallback = global.getProperty('registeNavRemoveByNameCallback');
    registeNavRemoveByNameCallback.invoke(removeByNameCallback);

    const registeNavRemoveByNavDestinationIdCallback = global.getProperty('registeNavRemoveByNavDestinationIdCallback');
    registeNavRemoveByNavDestinationIdCallback.invoke(removeByNavDestinationIdCallback);

    const registeNavPopCallback = global.getProperty('registeNavPopCallback');
    registeNavPopCallback.invoke(popCallback);

    const registeNavPopToNameCallback = global.getProperty('registeNavPopToNameCallback');
    registeNavPopToNameCallback.invoke(popToNameCallback);

    const registeNavPopToIndexCallback = global.getProperty('registeNavPopToIndexCallback');
    registeNavPopToIndexCallback.invoke(popToIndexCallback);

    const registeNavMoveToTopCallback = global.getProperty('registeNavMoveToTopCallback');
    registeNavMoveToTopCallback.invoke(moveToTopCallback);

    const registeNavMoveIndexToTopCallback = global.getProperty('registeNavMoveIndexToTopCallback');
    registeNavMoveIndexToTopCallback.invoke(moveIndexToTopCallback);

    const registeNavClearCallback = global.getProperty('registeNavClearCallback');
    registeNavClearCallback.invoke(clearCallback);

    const registeNavGetAllPathNameCallback = global.getProperty('registeNavGetAllPathNameCallback');
    registeNavGetAllPathNameCallback.invoke(getAllPathNameCallback);

    const registeNavGetParamByIndexCallback = global.getProperty('registeNavGetParamByIndexCallback');
    registeNavGetParamByIndexCallback.invoke(getParamByIndexCallback);

    const registeNavGetParamByNameCallback = global.getProperty('registeNavGetParamByNameCallback');
    registeNavGetParamByNameCallback.invoke(getParamByNameCallback);

    const registeNavGetIndexByNameCallback = global.getProperty('registeNavGetIndexByNameCallback');
    registeNavGetIndexByNameCallback.invoke(getIndexByNameCallback);

    const registeNavGetParentCallback = global.getProperty('registeNavGetParentCallback');
    registeNavGetParentCallback.invoke(getParentCallback);

    const registeNavSizeCallback = global.getProperty('registeNavSizeCallback');
    registeNavSizeCallback.invoke(sizeCallback);

    const registeNavDisableAnimationCallback = global.getProperty('registeNavDisableAnimationCallback');
    registeNavDisableAnimationCallback.invoke(disableAnimationCallback);

    const registeNavSetInterceptionCallback = global.getProperty('registeNavSetInterceptionCallback');
    registeNavSetInterceptionCallback.invoke(setInterceptionCallback);

    const registeNavGetPathStackCallback = global.getProperty('registeNavGetPathStackCallback');
    registeNavGetPathStackCallback.invoke(getPathStackCallback);

    const registeNavSetPathStackCallback = global.getProperty('registeNavSetPathStackCallback');
    registeNavSetPathStackCallback.invoke(setPathStackCallback);
}
// -------------------- code above for navigation interop --------------------

function transferCompatibleDynamicBuilder(builder: (...args: FixedArray<Any>) => void):
/** @memo */
(...args: FixedArray<Any>) => void {
    return (
        /** @memo */
        (...args: FixedArray<Any>) => {
            let argsESValue: FixedArray<ESValueOrUndefined> = new ESValueOrUndefined[args.length]; 
            for (let i = 0; i < args.length; i++) {
                if (args[i] instanceof ESValue) {
                    argsESValue[i] = args[i] as ESValue;
                } else {
                    argsESValue[i] = ESValue.wrap(args[i]);
                }
            }
            compatibleWrappedBuilderInternal(builder, ...argsESValue);
        }
    )
}

export function registerCreateCompatibleStaticState(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerCreateCompatibleStaticState');
    registerCallback.invoke(createCompatibleStaticState);
}

function createCompatibleStaticState<T>(dynamicValue: Object): ProvideDecoratedVariable<T> {
    const value = ESValue.wrap(dynamicValue);
    const getProxy = value.invokeMethod('getProxy').unwrap();
    if (getProxy === undefined) {
        const stateVar = new ProvideDecoratedVariable<T>(
          ExtendableComponent.current as ExtendableComponent,
          "proxy",
          "proxy",
          uiUtils.makeV1Observed(value.invokeMethod("get").unwrap()) as T,
          false
        );
        stateVar.setProxy(value);
        value.invokeMethod('setProxy', ESValue.wrap(stateVar));
        const setProxyValue = ((newVal: T): void => {
            value.invokeMethod('set', ESValue.wrap(newVal));
        });
        stateVar.setProxyValue = setProxyValue;
        const global = ESValue.getGlobal();
        const setSource = ((newVal: T): void => {
            stateVar.set(newVal);
        });
        const fireChange = (): void => {
            stateVar.fireChange();
        }
        global.getProperty('updateNotifyCallback').invoke(value, ESValue.wrap(fireChange));
        const notifyProxy = (): void => {
            value.invokeMethod('syncPeerHasChanged');
        };
        stateVar.addWatch(notifyProxy);
        global.getProperty('updateSetValueCallback').invoke(value, ESValue.wrap(setSource));
        return stateVar;
    }
    else {
        return getProxy as ProvideDecoratedVariable<T>;
    }
}

export function enableCompatibleObservedV2ForStatic<T>(
    value: T
): T {
    let method = ESValue.getGlobal().getProperty('enableCompatibleObservedV2ForStatic');
    let createStaticState = () => {
        return StateMgmtTool.getGlobalStateManager().mutableState<int32>(0, true);
    }
    let recordStaticState = (value: MutableState<int32>) => {
        value.value
    }
    let updateStaticState = (value: MutableState<int32>) => {   
        value.value++
        ESValue.getGlobal().getProperty('runPendingJobs').invoke();
    }
    method.invoke(ESValue.wrap(value), ESValue.wrap(createStaticState),
        ESValue.wrap(recordStaticState), ESValue.wrap(updateStaticState))
    return value;
}

export function enableCompatibleObservedV2ForDynamic<T>(
    value: T
): T {
    if (value instanceof IObservedObject) {
        addCompatibleWatchFuncForDynamic(value as IObservedObject)
    }
    return value;
}

function createDynamicCompatibleStateMeta(): [()=> void,()=> void] {
    let createFunc = ESValue.getGlobal().getProperty('createCompatibleStateMetaForStaticObservedV2');
    if (createFunc  ==  ESValue.Undefined) {
        throw Error('fail to find compatible func for create dynamic state meta');
    }
    let result = createFunc.invoke();
    let addRef = () => {
        result.getPropertySafe(0).invoke();
    }
    let fireChange = () => {
        result.getPropertySafe(1).invoke();
    }
    return [addRef, fireChange];
}

function addCompatibleWatchFuncForDynamic(value: IObservedObject): void {
    let values = Object.values(value);
    for(let i =0; i < values.length; i++){
        let attr = values[i];
        if (attr instanceof MutableStateMeta) {
            let result = createDynamicCompatibleStateMeta();
            (attr as MutableStateMeta).registerDynamicHookFunc(result[0], result[1]);
        } else if (attr instanceof IObservedObject) {
            addCompatibleWatchFuncForDynamic(attr as IObservedObject);
        }
    }
}

export function staticStateBindObservedObject<T>(
    value: T,
    onPropertyChange?: () => void,
    onTrackPropertyRead?: (readPropName: string, isTracked: boolean) => void,
    onTrackPropertyChange?: (readPropName: string) => void
): T {
    let global = ESValue.getGlobal();
    let staticStateBindObservedObject = global.getProperty('staticStateBindObservedObject');
    return staticStateBindObservedObject.invoke(
        ESValue.wrap(value),
        ESValue.wrap(onPropertyChange),
        ESValue.wrap(onTrackPropertyRead),
        ESValue.wrap(onTrackPropertyChange)) as Object as T;
}

function registerLocalStorageSetProxy(): void {
    const global = ESValue.getGlobal();
    const registerCallback = global.getProperty('registerLocalStorageSetProxy');
    registerCallback.invoke(localStorageSetProxy);
}

function localStorageSetProxy(storage: LocalStorage, proxy: Object): void {
    storage.setProxy(ESValue.wrap(proxy));
}