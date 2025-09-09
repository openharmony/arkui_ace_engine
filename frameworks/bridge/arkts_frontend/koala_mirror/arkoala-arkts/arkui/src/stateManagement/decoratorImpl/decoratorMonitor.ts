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
import { ObserveSingleton } from "../base/observeSingleton";
import { IBindingSource } from "../base/mutableStateMeta";
import { StateMgmtConsole } from "../tools/stateMgmtDFX";
import { ITrackedDecoratorRef } from "../base/mutableStateMeta";
import { RenderIdType, IMonitorValue, IMonitorDecoratedVariable, IMonitor, IMonitorPathInfo } from "../decorator";

export class MonitorFunctionDecorator implements IMonitorDecoratedVariable, IMonitor {
    public static readonly MIN_MONITOR_ID: RenderIdType = 0x20000000;
    public static nextWatchId_ = MonitorFunctionDecorator.MIN_MONITOR_ID;

    private readonly monitorFunction_: (m: IMonitor) => void;
    private readonly values_: MonitorValueInternal[] = new Array<MonitorValueInternal>();

    constructor(pathLambda: IMonitorPathInfo[], monitorFunction: (m: IMonitor) => void) {
        this.monitorFunction_ = monitorFunction;
        pathLambda.forEach((info: IMonitorPathInfo) => {
            this.values_.push(new MonitorValueInternal(info.path, info.lambda, this));
        })
        this.readInitialMonitorValues();
    }

    public value<T>(path?: string): IMonitorValue<T> | undefined {
        if (path) {
            for (let monitorValue of this.values_) {
                if (monitorValue.dirty && monitorValue.path === path) {
                    return new MonitorValuePublic<T>(monitorValue);
                }
            }
        } else {
            for (let monitorValue of this.values_) {
                if (monitorValue.dirty) {
                    return new MonitorValuePublic<T>(monitorValue);
                }
            }
        }
        return undefined;
    }

    public notifyChangesForPath(monitorPath: ITrackedDecoratorRef): boolean {
        return this.recordDependenciesForMonitorValue(false, monitorPath as MonitorValueInternal);
    }
    
    public runMonitorFunction(): void {
        if (this.dirty.length == 0) {
            return;
        }
        try {
            this.monitorFunction_(this);
        } catch (e: Exception) {
            StateMgmtConsole.log(`Error caught while executing @Monitor function: '${e}'`);
        } finally {
            this.values_.forEach((monitorValue: MonitorValueInternal) => { monitorValue.reset(); });
        }
    }

    public get dirty(): string[] {
        let ret = new Array<string>();
        this.values_.forEach((monitorValue: MonitorValueInternal) => {
            if (monitorValue.dirty) {
                ret.push(monitorValue.path);
            }
        })
        return ret;
    }

    private readInitialMonitorValues(): void {
        this.values_.forEach((monitorValue: MonitorValueInternal) => {
            this.recordDependenciesForMonitorValue(true, monitorValue);
        })
    }

    /**
     * Reads monitor value
     * @param isFirstRun true to clear previous bindings, and read value for first time
     * @param monitorValue 
     * @returns true if value is dirty
     */
    private recordDependenciesForMonitorValue(isFirstRun: boolean, monitorValue: MonitorValueInternal): boolean {
        if (!isFirstRun) {
            monitorValue.clearReverseBindings();
        }
        let renderingComponentBefore = ObserveSingleton.instance.renderingComponent;
        let renderingComponentRefBefore = ObserveSingleton.instance.renderingComponentRef;
        ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingMonitor;
        ObserveSingleton.instance.renderingComponentRef = monitorValue;
        let dirty = monitorValue.readValue(isFirstRun);
        ObserveSingleton.instance.renderingComponent = renderingComponentBefore;
        ObserveSingleton.instance.renderingComponentRef = renderingComponentRefBefore;
        return dirty;
    }
}

export class MonitorValueInternal implements IMonitorValue<NullishType>, ITrackedDecoratorRef {
    public id: RenderIdType;
    public weakThis: WeakRef<ITrackedDecoratorRef>;
    public reverseBindings: Set<WeakRef<IBindingSource>> = new Set<WeakRef<IBindingSource>>();
    public before: NullishType;
    public now: NullishType;
    public path: string;
    public monitor: MonitorFunctionDecorator;

    private dirty_: boolean = false;
    private readonly lambda: () => NullishType;

    constructor(path: string, lambda: () => NullishType, monitor: MonitorFunctionDecorator) {
        this.id = MonitorFunctionDecorator.nextWatchId_++;
        this.path = path;
        this.lambda = lambda;
        this.weakThis = new WeakRef<ITrackedDecoratorRef>(this);
        this.monitor = monitor;
        ObserveSingleton.instance.addToTrackedRegistry(this, this.reverseBindings);
    }

    public clearReverseBindings(): void {
        this.reverseBindings.forEach((dep: WeakRef<IBindingSource>) => {
            let ref = dep.deref();
            if (ref) {
                ref.clearBindingRefs(this.weakThis);
            } else {
                this.reverseBindings.delete(dep);
            }
        })
    }
    /**
     * Executes lambda and check if value is dirty
     * @param isFirstRun not dirty, now = before
     * @return true if before !== now
     */
    public readValue(isFirstRun: boolean = false): boolean {
        try {
            this.now = this.lambda();
            if (isFirstRun) {
                this.before = this.now;
                return false;
            }
            this.dirty_ = this.before !== this.now
            return this.dirty;
        } catch(e) {
            StateMgmtConsole.log(`Caught exception while reading monitor path ${this.path} value: ${e}.`);
            return false;
        }
    }

    public get dirty(): boolean {
        return this.dirty_;
    }

    public reset(): void {
        this.before = this.now;
        this.dirty_ = false;
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