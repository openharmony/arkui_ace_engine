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
import { IMutableStateMeta, IMutableKeyedStateMeta } from '../decorator';
import { Dependent, MutableState } from '@koalaui/runtime';
import { ObserveSingleton } from './observeSingleton';
import { RenderIdType } from '../decorator';
import { StateMgmtTool } from '#stateMgmtTool';
import { StateUpdateLoop } from './stateUpdateLoop';
import { StateMgmtDFX } from '../tools/stateMgmtDFX';

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
}

/**
 * manage one meta MutableState
 * V2 equivalent: sym_ref entry for particular property called 'propName'
 * addRef(obj, propName) records dependency,
 * fireChange(obj, propName) marks all dependencies for this prop need update
 */
export class MutableStateMeta extends MutableStateMetaBase implements IMutableStateMeta, IBindingSource {
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

    constructor(info: string, metaDependency?: MutableState<int32>) {
        super(info);
        this.__metaDependency = metaDependency ?? StateMgmtTool.getGlobalStateManager().mutableState<int32>(0, true);
        this.bindingRefs_ = new Set<WeakRef<ITrackedDecoratorRef>>();
        this.weakThis = new WeakRef<IBindingSource>(this);
        this.metaValue = 0;
        this.hasFired = false;
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
                    ObserveSingleton.instance.addDirtyRef(trackedObject);
                } else {
                    this.clearBindingRefs(listener);
                }
            });
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
}

export class MutableKeyedStateMeta extends MutableStateMetaBase implements IMutableKeyedStateMeta {
    protected readonly __metaDependencies = new Map<string, MutableStateMeta>();

    constructor(info: string = '') {
        super(info);
    }

    public addRef(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (!metaDependency) {
            // incremental engine does not allow create mutableState while building tree
            metaDependency = new MutableStateMeta(
                key,
                StateMgmtTool.getGlobalStateManager().mutableState<int32>(0, true)
            );
            this.__metaDependencies.set(key, metaDependency);
        }
        metaDependency.addRef();
    }

    public fireChange(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (metaDependency) {
            metaDependency.fireChange();
        }
    }
}
