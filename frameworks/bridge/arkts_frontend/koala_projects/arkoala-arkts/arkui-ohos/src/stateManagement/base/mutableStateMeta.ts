/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from '@koalaui/common';
import { ArkUIAniModule } from 'arkui.ani';
import {
    IMutableStateMeta, IMutableKeyedStateMeta, IObservedObject,
} from '../decorator';
import { Dependent, MutableState, GlobalStateManager, IncrementalNode } from '@koalaui/runtime';
import { ObserveSingleton } from './observeSingleton';
import { RenderIdType } from '../decorator';
import { StateUpdateLoop } from './stateUpdateLoop';
import { ObservedObjectRegistry, StateMgmtDFX } from '../tools/stateMgmtDFX';
import { ElementInfo } from '../utils';

class MutableStateMetaBase {
    public readonly info_: string;

    constructor(info: string) {
        this.info_ = info;
    }
}

export interface IBindingSource {
    clearBindingRefs(listener: WeakRef<ITrackedDecoratorRef>): void;
    changeMutableState(): void;
    readonly weakThis: WeakRef<IBindingSource>;
}

export interface ITrackedDecoratorRef {
    id: RenderIdType;
    weakThis: WeakRef<ITrackedDecoratorRef>;
    reverseBindings: Set<WeakRef<IBindingSource>>;
    clearReverseBindings(): void;
    getDFXInfo(): ElementInfo;
}

// The wildcard LSV target sentinel: the object stored in MutableStateMeta.target_
// (and accumulated in ObserveSingleton's per-monitor sources Array). The wildcard
// LSV identity check (`sources.includes(this.before)`) is the only consumer; a
// non-matching value falls through to `before !== now`. Concrete callers pass
// the IObservedObject that owns the meta, or for IBindingSource owners
// (BackingValue, PropRefDecoratedVariable) `this` itself — a user lambda will
// never return one of those, so they're safe anti-targets. Typed as Object so
// any class instance qualifies without forcing each owner to formally implement
// IBindingSource just to be a target.
export type MonitorTarget = Object | undefined;

/**
 * manage one meta MutableState
 * V2 equivalent: sym_ref entry for particular property called 'propName'
 * addRef(obj, propName) records dependency,
 * fireChange(obj, propName) marks all dependencies for this prop need update
 */
export class MutableStateMeta extends MutableStateMetaBase implements IMutableStateMeta, IBindingSource {
    public static registry: FinalizationRegistry<WeakRef<MutableState<int32>>> = new FinalizationRegistry<WeakRef<MutableState<int32>>>(
        (weak: WeakRef<MutableState<int32>>) => {
            const state = weak.deref();
            state?.dispose();
        }
    );
    // meta MutableState to record dependencies in addRef
    // and mutate in fireChange
    protected __metaDependency: MutableState<int32>;
    private bindingRefs_: Set<WeakRef<ITrackedDecoratorRef>>;
    weakThis: WeakRef<IBindingSource>;
    metaValue: int32;
    enableDynamicCompatible: boolean = false;
    dynamicAddRefFunc?: () => void;
    dynamicFireChangeFunc?: () => void;
    private hasFired: boolean;
    // Per-meta wildcard LSV target (the IObservedObject / IBindingSource that
    // owns this meta). Captured at construction so fireChange() doesn't need
    // a per-call target argument. Undefined when the meta is created without
    // an owner (legacy field-initializer pattern); recordMonitorSource skips
    // undefined sources, so the wildcard LSV check still falls through to
    // `before !== now` correctly.
    private readonly target_?: MonitorTarget;

    constructor(info: string, target?: MonitorTarget, metaDependency?: MutableState<int32>) {
        super(info);
        this.__metaDependency = metaDependency ?? GlobalStateManager.instance.mutableState<int32>(0, true);
        this.bindingRefs_ = new Set<WeakRef<ITrackedDecoratorRef>>();
        this.weakThis = new WeakRef<IBindingSource>(this);
        this.metaValue = 0;
        this.hasFired = false;
        this.target_ = target;
        MutableStateMeta.registry.register(this, new WeakRef<MutableState<int32>>(this.__metaDependency));
    }

    public registerDynamicHookFunc(addRef: () => void, fireChange: () => void) {
        this.enableDynamicCompatible = true;
        this.dynamicAddRefFunc = addRef;
        this.dynamicFireChangeFunc = fireChange;
    }

    public addRef(): void {
        const renderingComponent = ObserveSingleton.instance.renderingComponent;
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`MutableStateMeta addRef ${renderingComponent} ${ObserveSingleton.instance.renderingId}`);
        if (renderingComponent <= ObserveSingleton.RenderingComponent && !this.enableDynamicCompatible) {
            return;
        }
        // >= RenderingMonitor means Monitor/Computed/PersistentStorage
        if (
            renderingComponent >= ObserveSingleton.RenderingMonitor
        ) {
            this.bindingRefs_.add(ObserveSingleton.instance.renderingComponentRef!.weakThis);
            ObserveSingleton.instance.renderingComponentRef!.reverseBindings.add(this.weakThis);
        } else {
            this.__metaDependency!.value;
        }
        if (this.hasFired) {
            this.hasFired = false;
        }
        if (this.enableDynamicCompatible) {
            this.dynamicAddRefFunc?.();
        }
    }

    public fireChange(): void {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`MutableStateMeta fireChange ${this.hasFired} ${this.shouldFireChange()} ${StateUpdateLoop.canRequestFrame}`);
        if (ObserveSingleton.instance.renderingComponent === ObserveSingleton.RenderingComputed) {
            throw new Error('Attempt to modify state variables from @Computed function');
        }
        if (this.bindingRefs_.size > 0) {
            this.bindingRefs_.forEach((listener: WeakRef<ITrackedDecoratorRef>) => {
                let trackedObject = listener.deref();
                if (trackedObject) {
                    // we have dependent object to execute: Computed, Monitor...
                    // Collect id of items to run
                    ObserveSingleton.instance.addDirtyRef(trackedObject, this.target_);
                } else {
                    this.clearBindingRefs(listener);
                }
            });
            ObserveSingleton.instance.updateDirtySyncMonitorPaths();
        }
        if (!this.hasFired && this.shouldFireChange()) {
            ObserveSingleton.instance.changeMutableState(this);
            this.hasFired = true;
            if (StateUpdateLoop.canRequestFrame) {
                ArkUIAniModule._CustomNode_RequestFrame();
                StateUpdateLoop.canRequestFrame = false;
            }
        }
        if (this.enableDynamicCompatible) {
            this.dynamicFireChangeFunc?.();
        }
    }

    public changeMutableState(): void {
        this.__metaDependency!.value = ++this.metaValue;
    }

    clearBindingRefs(listener: WeakRef<ITrackedDecoratorRef>): void {
        this.bindingRefs_.delete(listener);
    }

    shouldFireChange(): boolean {
        const dependency = this.__metaDependency as Object as Dependent;
        return dependency.hasDependencies();
    }
    getDependentNodeInfo(): Set<IncrementalNode> | undefined {
        return this.__metaDependency.getDependentInfo();
    }
    getMonitorAndComputedInfo(elementInfo: Array<ElementInfo>): Array<ElementInfo> {
        if (this.bindingRefs_.size > 0) {
            this.bindingRefs_.forEach((listener: WeakRef<ITrackedDecoratorRef>) => {
                let trackedObject = listener.deref();
                if (trackedObject) {
                    elementInfo.push(trackedObject.getDFXInfo());
                }
            });
        }
        return elementInfo;
    }
}

export class MutableKeyedStateMeta extends MutableStateMetaBase implements IMutableKeyedStateMeta {
    protected readonly __metaDependencies = new Map<string, MutableStateMeta>();
    private observed: IObservedObject | undefined = undefined;
    constructor(info: string = '', observed?: IObservedObject) {
        super(info);
        if (observed) {
            this.observed = observed;
            const observedInfo = ObservedObjectRegistry.getOrRegister(observed!);
            let resolvedKey: string = ''
            if (info.startsWith('__metaBuiltInV1_')) {
                resolvedKey = '__metaBuiltInV1Key_';
            } else if (info.startsWith('__metaBuiltInV2_')) {
                resolvedKey = '__metaBuiltInV2Key_';
            } else if (info.startsWith('__metaBuiltInMakeObserved_')) {
                resolvedKey = '__metaMakeObservedKey_';
            } else if (info.startsWith('__metaInterfaceMakeObserved_')) {
                resolvedKey = '__metaInterfaceMakeObservedKey_';
            }
            observedInfo.setType(resolvedKey);
        }
    }

    public addRef(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (!metaDependency) {
            // Pass `this.observed` as the wildcard LSV target so per-key
            // fireChange routes through addDirtyRef with the owning
            // IObservedObject as the trigger, without needing a per-call
            // target argument. incremental engine does not allow create
            // mutableState while building tree.
            metaDependency = new MutableStateMeta(
                key,
                this.observed,
                GlobalStateManager.instance.mutableState<int32>(0, true)
            );
            if (this.observed) {
                const observedObject = this.observed as IObservedObject;
                const info = ObservedObjectRegistry.getOrRegister(observedObject!); // type has been set in ctor
                info.registerMutableStateMeta(metaDependency);
            }
            this.__metaDependencies.set(key, metaDependency);
        }
        metaDependency.addRef();
    }

    public fireChange(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (metaDependency) {
            // The per-key sub-meta has its own constructor-stored target
            // (this.observed) baked in via addRef, so MutableStateMeta.fireChange
            // resolves the wildcard target without an explicit per-call arg.
            metaDependency.fireChange();
        }
    }

    // Fire several keys as one logical mutation. The sync-monitor drain is
    // deferred via beginSyncMonitorBatch / endSyncMonitorBatch so a wildcard
    // monitor bound to multiple of the keys (e.g. OB_LENGTH and
    // OB_ARRAY_ANY_KEY for an array push) fires its callback ONCE per
    // mutation, not once per key. Each key still goes through the per-key
    // fireChange, so non-overlapping bindings still see their own
    // notification.
    public fireChangeBatch(keys: ReadonlyArray<string>): void {
        ObserveSingleton.instance.beginSyncMonitorBatch();
        try {
            keys.forEach((key: string) => this.fireChange(key));
        } finally {
            ObserveSingleton.instance.endSyncMonitorBatch();
        }
    }
}
