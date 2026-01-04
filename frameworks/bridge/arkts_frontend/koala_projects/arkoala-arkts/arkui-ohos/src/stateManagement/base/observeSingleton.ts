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

import { IObserve, OBSERVE } from '../decorator';
import { IObservedObject, RenderIdType } from '../decorator';
import { IBindingSource, ITrackedDecoratorRef } from './mutableStateMeta';
import { StateMgmtTool } from '#stateMgmtTool';
import { NullableObject } from './types';
import { MonitorFunctionDecorator, MonitorValueInternal } from '../decoratorImpl/decoratorMonitor';
import { ComputedDecoratedVariable, IComputedDecoratorRef } from '../decoratorImpl/decoratorComputed';
import { PersistenceV2Impl } from '../storage/persistenceV2';

type TaskType<T> = () => T;

enum NotifyMutableStateMode {
    normal = 0,
    delayMutation = 1,
    noMutation = 2,
}

export class ObserveSingleton implements IObserve {
    public static readonly instance: ObserveSingleton = new ObserveSingleton();
    public static readonly InvalidRenderId: RenderIdType | undefined = undefined;
    public static readonly RenderingComponent: int = 0;
    public static readonly RenderingComponentV1: int = 1;
    public static readonly RenderingComponentV2: int = 2;
    public static readonly RenderingMonitor: int = 3;
    public static readonly RenderingComputed: int = 4;
    public static readonly RenderingPersistentStorage: int = 5;
    // if add new to ths RenderingXXX, remember to change judgement when addRef

    public _renderingComponent: int = ObserveSingleton.RenderingComponent;
    private mutateMutableStateMode_: NotifyMutableStateMode = NotifyMutableStateMode.normal;
    public renderingComponentRef?: ITrackedDecoratorRef;
    private monitorPathRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private monitorPathRefsDelayed_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private computedPropRefsDelayed_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private queuedMutableStateChanges_ = new Set<WeakRef<IBindingSource>>();
    private persistencePropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private finalizationRegistry = new FinalizationRegistry<WeakRef<ITrackedDecoratorRef>>(
        this.finalizeComputedAndMonitorPath
    );
    private reverseBindingRefsToSet_ = new Map<WeakRef<ITrackedDecoratorRef>, Set<WeakRef<IBindingSource>>>();

    get renderingComponent(): int {
        return this._renderingComponent;
    }
    set renderingComponent(value: int) {
        this._renderingComponent = value;
    }

    get renderingId(): RenderIdType | undefined {
        const id =
            StateMgmtTool.getGlobalStateManager().currentScope?.id ?? ObserveSingleton.InvalidRenderId;
        return id;
    }
    set renderingId(value: RenderIdType | undefined) {
        this._renderingId = value;
    }
    public _renderingId: RenderIdType | undefined = ObserveSingleton.InvalidRenderId;

    constructor() {}

    public castToIObservedObject<T>(obj: T): IObservedObject | undefined {
        return obj && typeof obj === 'object' && StateMgmtTool.isIObservedObject(obj as Object)
            ? (obj as Object as IObservedObject)
            : undefined;
    }

    public setV1RenderId(value: NullableObject): void {
        if (
            this.renderingComponent === ObserveSingleton.RenderingComponentV1 &&
            this.renderingId !== ObserveSingleton.InvalidRenderId &&
            value &&
            typeof value === 'object'
        ) {
            if (StateMgmtTool.isIObservedObject(value as Object)) {
                (value as Object as IObservedObject).setV1RenderId(this.renderingId!);
            } else {
                this.trySetRenderIdOnInterface(value as object);
            }
        }
    }

    private trySetRenderIdOnInterface(obj: object): void {
        const handler = StateMgmtTool.tryGetHandler(obj);
        if (handler && StateMgmtTool.isInterfaceProxyHandler(handler)) {
            (handler as Object as IObservedObject).setV1RenderId(this.renderingId!);
        }
    }

    public isObservedInterface(value: NullableObject): boolean {
        if (value === undefined || value === null || typeof value !== 'object') {
            return false;
        }
        const handler = StateMgmtTool.tryGetHandler(value as Object);
        return handler !== undefined && StateMgmtTool.isInterfaceProxyHandler(handler);
    }

    public shouldAddRef(iObjectsRenderId: RenderIdType): boolean {
        return (
            this.renderingComponent >= ObserveSingleton.RenderingComponentV2 ||
            (this.renderingComponent === ObserveSingleton.RenderingComponentV1 && iObjectsRenderId === this.renderingId)
        );
    }

    public addDirtyRef(trackedRef: ITrackedDecoratorRef): void {
        if (trackedRef.id >= PersistenceV2Impl.MIN_PERSISTENCE_ID) {
            this.persistencePropRefsChanged_.add(trackedRef.weakThis);
        } else if (trackedRef.id >= MonitorFunctionDecorator.MIN_SYNC_MONITOR_ID) {
            const currentMonitor = (trackedRef as MonitorValueInternal).monitor;
            currentMonitor.notifyChangesForPath(trackedRef);
            currentMonitor.runMonitorFunction();
        } else if (trackedRef.id >= MonitorFunctionDecorator.MIN_MONITOR_ID) {
            this.monitorPathRefsChanged_.add(trackedRef.weakThis);
        } else if (trackedRef.id >= ComputedDecoratedVariable.MIN_COMPUTED_ID) {
            this.computedPropRefsChanged_.add(trackedRef.weakThis);
        }
    }

    public addToTrackedRegistry(ref: ITrackedDecoratorRef, reverseSet: Set<WeakRef<IBindingSource>>): void {
        this.reverseBindingRefsToSet_.set(ref.weakThis, reverseSet);
        this.finalizationRegistry.register(ref, ref.weakThis);
    }

    public finalizeComputedAndMonitorPath(ref: WeakRef<ITrackedDecoratorRef>): void {
        const bindingSources = this.reverseBindingRefsToSet_.get(ref);
        if (bindingSources) {
            bindingSources.forEach((binding: WeakRef<IBindingSource>) => {
                binding.deref()?.clearBindingRefs(ref);
            });
            this.reverseBindingRefsToSet_.delete(ref);
        }
    }

    public updateDirty(): void {
        do {
            while (this.computedPropRefsChanged_.size > 0) {
                const computedProps = this.computedPropRefsChanged_;
                this.computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                this.updateDirtyComputedProps(computedProps);
            }
            if (this.persistencePropRefsChanged_.size) {
                const persistenceProps = this.persistencePropRefsChanged_;
                this.persistencePropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                PersistenceV2Impl.instance().onChangeObserved(persistenceProps);
            }
            if (this.monitorPathRefsChanged_.size > 0) {
                const monitors = this.monitorPathRefsChanged_;
                this.monitorPathRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                let monitorsToRun: Set<MonitorFunctionDecorator> = this.notifyDirtyMonitorPaths(monitors);
                if (monitorsToRun && monitorsToRun.size > 0) {
                    monitorsToRun.forEach((monitor: MonitorFunctionDecorator) => {
                        monitor.runMonitorFunction();
                    });
                }
            }
        } while (
            this.monitorPathRefsChanged_.size +
                this.computedPropRefsChanged_.size +
                this.persistencePropRefsChanged_.size >
            0
        );
    }

    private updateDirtyComputedProps(computedProps: Set<WeakRef<ITrackedDecoratorRef>>): void {
        computedProps.forEach((computedPropWeak: WeakRef<ITrackedDecoratorRef>) => {
            let computedPropRef = computedPropWeak.deref();
            if (!computedPropRef) {
                return;
            }
            const computed = computedPropRef as IComputedDecoratorRef;
            if (computed.isFreeze()) {
                this.computedPropRefsDelayed_.add(computedPropWeak);
            } else {
                computedPropRef!.clearReverseBindings();
                computed.fireChange();
            }
        });
    }

    private notifyDirtyMonitorPaths(monitorPaths: Set<WeakRef<ITrackedDecoratorRef>>): Set<MonitorFunctionDecorator> {
        let monitors: Set<MonitorFunctionDecorator> = new Set<MonitorFunctionDecorator>();
        monitorPaths.forEach((monitorPathRef: WeakRef<ITrackedDecoratorRef>) => {
            let monitorPath = monitorPathRef.deref();
            if (monitorPath) {
                let monitor: MonitorFunctionDecorator = (monitorPath as MonitorValueInternal).monitor;
                if (monitor.isFreeze()) {
                    this.monitorPathRefsDelayed_.add(monitorPathRef);
                } else if (monitor.notifyChangesForPath(monitorPath)) {
                    monitors.add(monitor);
                }
            }
        });
        return monitors;
    }

    public unFreezeDelayedComputedProps(): void {
        this.computedPropRefsDelayed_.forEach((weak) => {
            this.computedPropRefsChanged_.add(weak);
        });
        this.computedPropRefsDelayed_.clear();
    }

    public clearDelayedComputedWhenReuse(): void {
        this.computedPropRefsChanged_.clear();
    }

    public clearDelayedMonitorWhenReuse(): void {
        this.monitorPathRefsDelayed_.clear();
    }

    public unFreezeDelayedMonitorPaths(): void {
        this.monitorPathRefsDelayed_.forEach((weak) => {
            this.monitorPathRefsChanged_.add(weak);
        });
        this.monitorPathRefsDelayed_.clear();
    }
    /* Execute given task
     * apply state changes to incremental engine immediately that occur while executing the task
     * this is the regular operation mode, therefore the function is rather redundant and given
     * just for the case where normal mode needs to be nested inside delayed mode
     * @param task
     * @returns
     */
    public applyTaskImmediateMutableStateChange<T>(task: TaskType<T>): T {
        const temp = this.mutateMutableStateMode_;
        this.mutateMutableStateMode_ = NotifyMutableStateMode.normal;
        const result: T = task();
        this.mutateMutableStateMode_ = temp;
        return result;
    }

    /**
     * Execute given task
     * while executing do not notify any state changes to incremental engine
     * state changes still trigger dependent @Computed to update and @Monitor
     * function to execute
     *
     * @param task
     * @returns
     */
    public applyTaskNoMutableStateChange<T>(task: TaskType<T>): T {
        const temp = this.mutateMutableStateMode_;
        this.mutateMutableStateMode_ = NotifyMutableStateMode.noMutation;
        const result: T = task();
        this.mutateMutableStateMode_ = temp;
        return result;
    }

    /**
     * Execute given task
     * queue any state changes to incremental engine that occur while executing the task
     * state changes still trigger normally dependent @Computed to update and @Monitor
     * function to execute
     * queued state changes get notified to incremental engine when instructed to do so
     * by calling @see delayedNotify
     *
     * @param task
     * @returns
     */
    public applyTaskDelayMutableStateChange<T>(task: TaskType<T>): T {
        if (ObserveSingleton.instance.renderingComponent === ObserveSingleton.RenderingComponent) {
            return task();
        }
        const temp = this.mutateMutableStateMode_;
        this.mutateMutableStateMode_ = NotifyMutableStateMode.delayMutation;
        const result: T = task();
        this.mutateMutableStateMode_ = temp;
        return result;
    }

    /**
     * Notify any state changes to incremental engine that have been queued up by
     * executing tasks with @see applyDelayNotify
     * The function mutates each MutableState just once even if executing tasks
     * added it to the queue several times.
     * The order of mutation is non deterministic.
     * @returns number of distinct MutableState objects that have been touched
     */
    public makeDelayedMutableStateChanges(): number {
        const count = this.queuedMutableStateChanges_.size;
        if (count > 0) {
            this.queuedMutableStateChanges_.forEach((mutableStateMetaWeak) => {
                const mutableStateMeta = mutableStateMetaWeak.deref();
                if (mutableStateMeta) {
                    mutableStateMeta!.changeMutableState();
                }
            });
            this.queuedMutableStateChanges_.clear();
        }
        return count;
    }

    public changeMutableState(mutableStateMeta: IBindingSource): void {
        switch (this.mutateMutableStateMode_) {
            case NotifyMutableStateMode.normal:
                mutableStateMeta.changeMutableState();
                break;
            case NotifyMutableStateMode.delayMutation:
                this.queuedMutableStateChanges_.add(mutableStateMeta.weakThis);
                break;
            case NotifyMutableStateMode.noMutation:
                // do nothing
                break;
            default:
                break;
        }
    }
}
