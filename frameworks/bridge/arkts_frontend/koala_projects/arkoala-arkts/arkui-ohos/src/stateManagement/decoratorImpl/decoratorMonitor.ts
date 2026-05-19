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
import { ObserveSingleton } from '../base/observeSingleton';
import { IBindingSource, MonitorTarget } from '../base/mutableStateMeta';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { ITrackedDecoratorRef } from '../base/mutableStateMeta';
import {
    RenderIdType, IMonitorValue, IMonitorDecoratedVariable, IMonitor, IMonitorPathInfo,
    IVariableOwner, IDecoratorBaseRegistry,
} from '../decorator';
import { ElementInfo } from '../utils';
import { ObserveWrappedKeyedMeta } from '../base/observeWrappedBase';
import { IObservedAnyProp } from '../decorator';

export class MonitorFunctionDecorator implements IMonitorDecoratedVariable, IMonitor, IDecoratorBaseRegistry {
    public static readonly MIN_MONITOR_ID: RenderIdType = 0x20000000;
    public static readonly MIN_SYNC_MONITOR_ID: RenderIdType = 0x25000000;
    public static nextWatchId_ = MonitorFunctionDecorator.MIN_MONITOR_ID;
    public static nextSyncWatchId_ = MonitorFunctionDecorator.MIN_SYNC_MONITOR_ID;
    public readonly decorator: string;
    private readonly monitorFunction_: (m: IMonitor) => void;
    private readonly values_: MonitorValueInternal[] = new Array<MonitorValueInternal>();
    private readonly owningComponent_?: IVariableOwner;
    public readonly functionName_?: string;

    constructor(pathLambda: IMonitorPathInfo[], monitorFunction: (m: IMonitor) => void, owningView?: IVariableOwner, isSynchronous?: boolean,
            functionName?: string) {
        this.monitorFunction_ = monitorFunction;
        this.owningComponent_ = owningView;
        this.functionName_ = functionName;
        const isSync = isSynchronous ?? false;

        pathLambda.forEach((info: IMonitorPathInfo) => {
            this.values_.push(new MonitorValueInternal(info.path, info.valueCallback, this, isSync, info.enableWildcard));
        });
        this.decorator = '@Monitor';
        this.readInitialMonitorValues();
        this.registerToOwningView();
    }

    public isFreeze(): boolean {
        return !!(this.owningComponent_ && !this.owningComponent_!.__isViewActive__Internal());
    }

    // Wildcard monitor values do not represent a single property change —
    // the wildcard binding fans out to multiple metas, so before/now/path
    // on a wildcard MonitorValueInternal don't correspond to a single
    // observable read. Return undefined for them; only non-wildcard dirty
    // values are surfaced to the user.
    public value<T>(path?: string): IMonitorValue<T> | undefined {
        if (path) {
            for (let monitorValue of this.values_) {
                if (monitorValue.dirty && !monitorValue.enableWildcard && monitorValue.path === path) {
                    return new MonitorValuePublic<T>(monitorValue);
                }
            }
        } else {
            for (let monitorValue of this.values_) {
                if (monitorValue.dirty && !monitorValue.enableWildcard) {
                    return new MonitorValuePublic<T>(monitorValue);
                }
            }
        }
        return undefined;
    }

    public notifyChangesForPath(
        monitorPath: ITrackedDecoratorRef,
        sources: Array<MonitorTarget> | undefined
    ): boolean {
        return this.recordDependenciesForMonitorValue(
            false, monitorPath as MonitorValueInternal, sources);
    }

    public runMonitorFunction(): void {
        if (this.values_.some(value => value.dirty === true)) {
            try {
                this.monitorFunction_(this);
            } catch (e) {
                StateMgmtConsole.log(`Error caught while executing @Monitor function: '${e}'`);
            } finally {
                this.values_.forEach((monitorValue: MonitorValueInternal) => {
                    monitorValue.reset();
                });
            }
        }
    }

    public get dirty(): string[] {
        let ret = new Array<string>();
        this.values_.forEach((monitorValue: MonitorValueInternal) => {
            if (monitorValue.dirty) {
                ret.push(monitorValue.path);
            }
        });
        return ret;
    }

    private readInitialMonitorValues(): void {
        this.values_.forEach((monitorValue: MonitorValueInternal) => {
            this.recordDependenciesForMonitorValue(true, monitorValue, undefined);
        });
    }

    /**
     * Reads monitor value
     * @param isFirstRun true to clear previous bindings, and read value for first time
     * @param monitorValue
     * @param sources every distinct target that triggered a fire for this monitor
     *               in the current drain pass. The wildcard LSV check
     *               (`sources.includes(this.before)`) needs the full list so a
     *               transit-dep change isn't lost when the drain batches multiple
     *               metas with different targets. Array (not Set) keeps the
     *               common single-source case allocation-free aside from the array
     *               header; recordMonitorSource dedupes via includes() before push
     *               so the array stays small.
     * @returns true if value is dirty
     */
    private recordDependenciesForMonitorValue(
        isFirstRun: boolean,
        monitorValue: MonitorValueInternal,
        sources: Array<MonitorTarget> | undefined,
        isReuse: boolean = false
    ): boolean {
        if (!isFirstRun) {
            monitorValue.clearReverseBindings();
        }
        let renderingComponentBefore = ObserveSingleton.instance.renderingComponent;
        let renderingComponentRefBefore = ObserveSingleton.instance.renderingComponentRef;
        ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingMonitor;
        ObserveSingleton.instance.renderingComponentRef = monitorValue;

        let dirty = isReuse ?
            monitorValue.readValueWhenReuse() :
            monitorValue.readValue(isFirstRun, sources);

        if (monitorValue.enableWildcard) {
            if (monitorValue.now instanceof ObserveWrappedKeyedMeta) {
                (monitorValue.now as ObserveWrappedKeyedMeta).addRefAnyKey();
            } else if (monitorValue.now instanceof IObservedAnyProp) {
                (monitorValue.now as IObservedAnyProp).addRefAnyProp();
            }
        }
        ObserveSingleton.instance.renderingComponent = renderingComponentBefore;
        ObserveSingleton.instance.renderingComponentRef = renderingComponentRefBefore;
        return dirty;
    }

    public unbindAllInternalValues(): void {
        this.values_.forEach((value: MonitorValueInternal): void => {
            ObserveSingleton.instance.finalizeComputedAndMonitorPath(value.weakThis);
        });
    }

    get path(): string[] {
        return this.values_.map(
            (value: MonitorValueInternal): string => value.path
        );
    }

    resetOnReuse(): void {
        ObserveSingleton.instance.clearDelayedMonitorWhenReuse();
        this.values_.forEach((monitorValue: MonitorValueInternal) => {
            this.recordDependenciesForMonitorValue(false, monitorValue, undefined, true);
        });
    }

    public registerToOwningView(): void {
        this.owningComponent_?.__registerStateVariables__Internal(this);
    }
}

export class MonitorValueInternal implements IMonitorValue<Any>, ITrackedDecoratorRef {
    public id: RenderIdType;
    public weakThis: WeakRef<ITrackedDecoratorRef>;
    public reverseBindings: Set<WeakRef<IBindingSource>> = new Set<WeakRef<IBindingSource>>();
    public before: Any;
    public now: Any;
    public path: string;
    public monitor: MonitorFunctionDecorator;
    public enableWildcard: boolean;

    private dirty_: boolean = false;
    private readonly lambda: () => Any;

    constructor(path: string, lambda: () => Any, monitor: MonitorFunctionDecorator,
        isSync: boolean, enableWildcard?: boolean) {
        this.id = isSync ? MonitorFunctionDecorator.nextSyncWatchId_++ : MonitorFunctionDecorator.nextWatchId_++;
        this.path = path;
        this.lambda = lambda;
        this.weakThis = new WeakRef<ITrackedDecoratorRef>(this);
        this.monitor = monitor;
        this.enableWildcard = enableWildcard === undefined? false : enableWildcard; // isWildcard ?? false
        ObserveSingleton.instance.addToTrackedRegistry(this, this.reverseBindings);
    }

    public clearReverseBindings(): void {
        Array.from(this.reverseBindings).forEach((dep: WeakRef<IBindingSource>) => {
            let ref = dep.deref();
            if (ref) {
                ref.clearBindingRefs(this.weakThis);
            } else {
                this.reverseBindings.delete(dep);
            }
        });
    }
    /**
     * Executes lambda and check if value is dirty
     * @param isFirstRun not dirty, now = before
     * @return true if before !== now
     */
    public readValue(isFirstRun: boolean, sources: Array<MonitorTarget> | undefined): boolean {
        try {
            this.now = this.lambda();
            if (isFirstRun) {
                this.before = this.now;
                return false;
            }

            // No wildcard in the path, compare values now and before
            if (this.enableWildcard === false) {
                this.dirty_ = this.before !== this.now;
                return this.dirty_;
            }

            // Wildcard path. If any of the sources that triggered this drain
            // matches our last-seen value, the change was a transit-dep on the
            // LSV itself and we must fire even when before === now (e.g. a
            // wildcard `comp.a.*` whose lambda returns comp.a sees comp.a's
            // own properties change without the comp.a reference moving).
            if (sources && sources.includes(this.before as MonitorTarget)) {
                this.dirty_ = true;
            } else {
                this.dirty_ = this.before !== this.now;
            }
            return this.dirty_;
        } catch (e) {
            StateMgmtConsole.log(`Caught exception while reading monitor path ${this.path} value: ${e}.`);
            return false;
        }
    }

    public readValueWhenReuse(): boolean {
        try {
            this.now = this.lambda();
            this.before = this.now;
        } catch (e) {
            StateMgmtConsole.log(`Caught exception while reading monitor path ${this.path} value: ${e}.`);
        }
        return true;
    }

    public get dirty(): boolean {
        return this.dirty_;
    }

    public reset(): void {
        this.before = this.now;
        this.dirty_ = false;
    }

    public getDFXInfo(): ElementInfo {
        const functionName = this.monitor.functionName_;
        const elementName = functionName ?
            `@Monitor function: ${functionName}, path: ${this.path}` : `@Monitor function path: ${this.path}`;
        return {
            elementName: elementName,
            elementId: this.id
        };
    }
}

export class MonitorValuePublic<T> implements IMonitorValue<T> {
    public before: T;
    public now: T;
    public path: string;
    constructor(value: MonitorValueInternal) {
        this.before = value.before as T;
        this.now = value.now as T;
        this.path = value.path;
    }
}
