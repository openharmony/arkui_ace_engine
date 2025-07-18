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
import { TypeChecker } from '#components';
import { StateMgmtTool } from '#stateMgmtTool';
import { NullableObject } from './types';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { MonitorFunctionDecorator, MonitorValueInternal } from '../decoratorImpl/decoratorMonitor';
import { ComputedDecoratedVariable, IComputedDecoratorRef } from '../decoratorImpl/decoratorComputed';

export class ObserveSingleton implements IObserve {
    public static readonly instance: ObserveSingleton = new ObserveSingleton();
    public static readonly InvalidRenderId: RenderIdType | undefined = undefined;
    public static readonly RenderingComponent: number = 0;
    public static readonly RenderingComponentV1: number = 1;
    public static readonly RenderingComponentV2: number = 2;
    public static readonly RenderingMonitor: number = 3;
    public static readonly RenderingComputed: number = 4;

    public _renderingComponent: number = ObserveSingleton.RenderingComponent;
    public renderingComponentRef?: ITrackedDecoratorRef;
    private monitorPathRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
    private finalizationRegistry = new FinalizationRegistry<WeakRef<ITrackedDecoratorRef>>(this.finalizeComputedAndMonitorPath);
    private reverseBindingRefsToSet_ = new Map<WeakRef<ITrackedDecoratorRef>, Set<WeakRef<IBindingSource>>>();

    get renderingComponent(): number {
        return this._renderingComponent;
    }
    set renderingComponent(value: number) {
        this._renderingComponent = value;
    }

    get renderingId(): RenderIdType | undefined {
        const id =
            StateMgmtTool.getGlobalStateManager().currentScopeId ?? ObserveSingleton.InvalidRenderId
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

    public shouldAddRef(iObjectsRenderId: RenderIdType | undefined): boolean {
        return (
            this.renderingComponent >= ObserveSingleton.RenderingComponentV2 ||
            (this.renderingComponent === ObserveSingleton.RenderingComponentV1 && iObjectsRenderId === this.renderingId)
        );
    }

    public addDirtyRef(trackedRef: ITrackedDecoratorRef): void {
        if (trackedRef.id >= MonitorFunctionDecorator.MIN_MONITOR_ID) {
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
            })
            this.reverseBindingRefsToSet_.delete(ref);
        }
    }

    public updateDirty(): void {
        do {
            while(this.computedPropRefsChanged_.size > 0) {
                const computedProps = this.computedPropRefsChanged_;
                this.computedPropRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                this.updateDirtyComputedProps(computedProps);
            }
            if (this.monitorPathRefsChanged_.size > 0) {
                const monitors = this.monitorPathRefsChanged_;
                this.monitorPathRefsChanged_ = new Set<WeakRef<ITrackedDecoratorRef>>();
                let monitorsToRun: Set<MonitorFunctionDecorator> = this.notifyDirtyMonitorPaths(monitors);
                if (monitorsToRun && monitorsToRun.size > 0) {
                    monitorsToRun.forEach((monitor: MonitorFunctionDecorator) => { monitor.runMonitorFunction(); });
                }
            }
        } while(this.monitorPathRefsChanged_.size + this.computedPropRefsChanged_.size > 0);
    }

    private updateDirtyComputedProps(computedProps: Set<WeakRef<ITrackedDecoratorRef>>): void {
        computedProps.forEach((computedPropWeak: WeakRef<ITrackedDecoratorRef>) => {
            let computedPropRef = computedPropWeak.deref();
            computedPropRef?.clearReverseBindings();
            if (computedPropRef) {
                (computedPropRef as IComputedDecoratorRef).fireChange();
            }
        })
    }

    private notifyDirtyMonitorPaths(monitorPaths: Set<WeakRef<ITrackedDecoratorRef>>): Set<MonitorFunctionDecorator> {
        let monitors: Set<MonitorFunctionDecorator> = new Set<MonitorFunctionDecorator>();
        monitorPaths.forEach((monitorPathRef: WeakRef<ITrackedDecoratorRef>) => {
            let monitorPath = monitorPathRef.deref();
            if (monitorPath) {
                let monitor: MonitorFunctionDecorator = (monitorPath as MonitorValueInternal).monitor;
                if (monitor.notifyChangesForPath(monitorPath)) {
                    monitors.add(monitor);
                }
            }
        });
        return monitors;
    }
}
