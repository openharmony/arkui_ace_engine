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
import { IBindingSource, ITrackedDecoratorRef, MonitorTarget } from './mutableStateMeta';
import { StateMgmtTool } from '#stateMgmtTool';
import { NullableObject } from './types';
import { MonitorFunctionDecorator, MonitorValueInternal } from '../decoratorImpl/decoratorMonitor';
import { ComputedDecoratedVariable } from '../decoratorImpl/decoratorComputed';
import { PersistenceV2Impl } from '../storage/persistenceV2';
import { GlobalStateManager } from '@koalaui/runtime';

type TaskType<T> = () => T;

enum NotifyMutableStateMode {
    normal = 0,
    delayMutation = 1,
    noMutation = 2,
}

export class ObserveSingleton implements IObserve {
    public static readonly instance: ObserveSingleton = new ObserveSingleton();
    public static readonly InvalidRenderId: RenderIdType | undefined = undefined;
    public static readonly RenderingPause: int = -1;
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
    private monitorPathRefsChanged_ =
        new Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>();
    private computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private monitorPathRefsDelayed_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private computedPropRefsDelayed_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private queuedMutableStateChanges_ = new Set<WeakRef<IBindingSource>>();
    private persistencePropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private syncMonitorsPropRefsChanged_ =
        new Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>();
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
            GlobalStateManager.instance.currentScope?.id ?? ObserveSingleton.InvalidRenderId;
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

    /*
        ID range layout used by addDirtyRef routing. Each tracked-ref class
        owns a contiguous slice; the ranges are pairwise disjoint and
        ordered, so a single greater-than-or-equal cascade picks the
        correct bucket. Defined in their owning files:

        ComputedDecoratedVariable.MIN_COMPUTED_ID         = 0x10000000  (decoratorComputed.ts)
        MonitorFunctionDecorator.MIN_MONITOR_ID           = 0x20000000  (decoratorMonitor.ts)
        MonitorFunctionDecorator.MIN_SYNC_MONITOR_ID      = 0x25000000  (decoratorMonitor.ts)
        PersistenceV2Impl.MIN_PERSISTENCE_ID              = 0x30000000  (persistenceV2.ts)
    */

    public addDirtyRef(trackedRef: ITrackedDecoratorRef, triggeredBy?: MonitorTarget): void {
        if (trackedRef.id >= PersistenceV2Impl.MIN_PERSISTENCE_ID) {
            this.persistencePropRefsChanged_.add(trackedRef.weakThis);
        } else if (trackedRef.id >= MonitorFunctionDecorator.MIN_SYNC_MONITOR_ID) {
            this.recordMonitorSource(
                this.syncMonitorsPropRefsChanged_, trackedRef.weakThis, triggeredBy);
        } else if (trackedRef.id >= MonitorFunctionDecorator.MIN_MONITOR_ID) {
            this.recordMonitorSource(
                this.monitorPathRefsChanged_, trackedRef.weakThis, triggeredBy);
        } else if (trackedRef.id >= ComputedDecoratedVariable.MIN_COMPUTED_ID) {
            this.computedPropRefsChanged_.add(trackedRef.weakThis);
        }
    }

    // Coalesce repeat addDirtyRef for the same monitor into one drain entry
    // keyed by weakThis identity, while preserving every triggering source so
    // the wildcard LSV check (`sources.includes(this.before)`) can detect a
    // transit-dep change even when several different metas of the same monitor
    // batched into one drain pass with non-shared targets.
    //
    // Storage is Array rather than Set to avoid the per-monitor Set header
    // allocation in the common single-source case (typical N is 1–3 per
    // drain). Manual dedup via includes() before push keeps the array small
    // — bounded by the number of distinct target objects that triggered the
    // monitor in the current drain pass.
    private recordMonitorSource(
        map: Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>,
        weakThis: WeakRef<ITrackedDecoratorRef>,
        triggeredBy: MonitorTarget,
    ): void {
        let sources = map.get(weakThis);
        if (!sources) {
            sources = new Array<MonitorTarget>();
            map.set(weakThis, sources);
        }
        // Skip pushing `undefined` — legacy no-arg fireChange() callers route
        // here with triggeredBy=undefined, and admitting undefined would let
        // the wildcard LSV check (`sources.includes(this.before)`) trip
        // whenever this.before is undefined (uninitialized field, broken
        // path), causing phantom callbacks. Same rationale as the empty-Array
        // injection in unFreezeDelayedMonitorPaths below: keep the monitor
        // queued for re-eval but force the dirty check to fall through to
        // the regular `before !== now` branch.
        if (triggeredBy !== undefined && !sources.includes(triggeredBy)) {
            sources.push(triggeredBy);
        }
    }

    /**
     * Sync-monitor batch nesting depth. While > 0, calls to
     * updateDirtySyncMonitorPaths() defer the drain so a logically-single
     * mutation (e.g. WrappedArray.push, which fires both OB_LENGTH and
     * OB_ARRAY_ANY_KEY) coalesces into ONE sync callback per monitor instead
     * of one per fireChange. The drain runs when the outermost batch ends.
     */
    private syncMonitorBatchDepth_: int = 0;

    public beginSyncMonitorBatch(): void {
        this.syncMonitorBatchDepth_++;
    }

    public endSyncMonitorBatch(): void {
        if (--this.syncMonitorBatchDepth_ === 0) {
            this.drainSyncMonitorPaths();
        }
    }

    /**
     * Process synchronous monitor paths that have been marked as dirty.
     *
     * Synchronous monitors (those with id >= MIN_SYNC_MONITOR_ID) need to be
     * processed immediately when their dependencies change, unlike regular monitors
     * which are processed during the next updateDirty() cycle.
     *
     * Called from MutableStateMeta.fireChange() to ensure real-time tracking
     * for synchronous monitors. Defers while inside a sync-monitor batch.
     */
    public updateDirtySyncMonitorPaths(): void {
        if (this.syncMonitorBatchDepth_ > 0) {
            return;
        }
        this.drainSyncMonitorPaths();
    }

    private drainSyncMonitorPaths(): void {
        // Swap-before-drain: re-entrant fires from within a sync monitor
        // callback land in a fresh map, so the in-flight drain doesn't
        // double-visit refs from the current pass.
        const pending = this.syncMonitorsPropRefsChanged_;
        this.syncMonitorsPropRefsChanged_ =
            new Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>();
        const monitorsToRun = this.notifyDirtyMonitorPaths(pending);
        if (monitorsToRun && monitorsToRun.size > 0) {
            monitorsToRun.forEach((monitor: MonitorFunctionDecorator) => {
                monitor.runMonitorFunction();
            });
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
                this.monitorPathRefsChanged_ =
                    new Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>();
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

    public updateDirtyComputedAndMonitorWhenUnfreeze(): void {
        do {
            while (this.computedPropRefsChanged_.size > 0) {
                const computedProps = this.computedPropRefsChanged_;
                this.computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                this.updateDirtyComputedProps(computedProps);
            }
            if (this.monitorPathRefsChanged_.size > 0) {
                const monitors = this.monitorPathRefsChanged_;
                this.monitorPathRefsChanged_ =
                    new Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>();
                let monitorsToRun: Set<MonitorFunctionDecorator> = this.notifyDirtyMonitorPaths(monitors);
                if (monitorsToRun && monitorsToRun.size > 0) {
                    monitorsToRun.forEach((monitor: MonitorFunctionDecorator) => {
                        monitor.runMonitorFunction();
                    });
                }
            }
        } while (
            this.monitorPathRefsChanged_.size + this.computedPropRefsChanged_.size > 0
        )
    }

    private updateDirtyComputedProps(computedProps: Set<WeakRef<ITrackedDecoratorRef>>): void {
        computedProps.forEach((computedPropWeak: WeakRef<ITrackedDecoratorRef>) => {
            let computedPropRef = computedPropWeak.deref();
            if (!computedPropRef) {
                return;
            }
            // Cast to the concrete @Computed class (mirrors how the monitor
            // drain casts to MonitorFunctionDecorator) — this is the only
            // call site that needs isFreeze/fireChange on a tracked ref, so
            // a one-purpose interface earns its keep less than the symmetry.
            const computed = computedPropRef as ComputedDecoratedVariable<Any>;
            if (computed.isFreeze()) {
                this.computedPropRefsDelayed_.add(computedPropWeak);
            } else {
                computedPropRef!.clearReverseBindings();
                computed.fireChange();
            }
        });
    }

    private notifyDirtyMonitorPaths(
        monitorPaths: Map<WeakRef<ITrackedDecoratorRef>, Array<MonitorTarget>>
    ): Set<MonitorFunctionDecorator> {
        let monitors: Set<MonitorFunctionDecorator> = new Set<MonitorFunctionDecorator>();
        monitorPaths.forEach((
            sources: Array<MonitorTarget>,
            monitorPathRef: WeakRef<ITrackedDecoratorRef>
        ) => {
            let monitorPath = monitorPathRef.deref();
            if (monitorPath) {
                let monitor: MonitorFunctionDecorator = (monitorPath as MonitorValueInternal).monitor;
                if (monitor.isFreeze()) {
                    this.monitorPathRefsDelayed_.add(monitorPathRef);
                } else if (monitor.notifyChangesForPath(monitorPath, sources)) {
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
            // No source info is preserved across freeze, so the wildcard
            // transit-dep check (`sources.includes(this.before)` in
            // MonitorValueInternal.readValue) has no input to make a decision.
            // Inject an EMPTY source array so the check inevitably falls
            // through to the regular `before !== now` branch. Adding a
            // placeholder value (e.g. undefined) would spuriously trip the
            // transit-dep branch when a wildcard monitor's LSV happens to
            // equal the placeholder.
            this.monitorPathRefsChanged_.set(weak, new Array<MonitorTarget>());
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
