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
import { IBindingSource, ITrackedDecoratorRef } from "../base/mutableStateMeta";
import { StateMgmtConsole } from "../tools/stateMgmtDFX";
import { RenderIdType, IMutableStateMeta, IComputedDecoratedVariable } from '../decorator';
import { FactoryInternal } from "../base/iFactoryInternal";

export interface IComputedDecoratorRef extends ITrackedDecoratorRef {
    fireChange(): void;
}

export class ComputedDecoratedVariable<T> implements IComputedDecoratedVariable<T> {
    public static readonly MIN_COMPUTED_ID: RenderIdType = 0x10000000;
    public static nextComputedId_: RenderIdType = ComputedDecoratedVariable.MIN_COMPUTED_ID;

    public id: RenderIdType;
    public varName: string;
    public weakThis: WeakRef<ITrackedDecoratorRef>;
    public reverseBindings: Set<WeakRef<IBindingSource>> = new Set<WeakRef<IBindingSource>>();
    private cachedValue_?: T;
    private readonly computedLambda_: () => T;
    private meta_: IMutableStateMeta = FactoryInternal.mkMutableStateMeta('Computed');
    constructor(computedLambda: () => T, varName: string) {
        this.id = ++ComputedDecoratedVariable.nextComputedId_;
        this.weakThis = new WeakRef<ITrackedDecoratorRef>(this);
        this.computedLambda_ = computedLambda;
        this.varName = varName;
        ObserveSingleton.instance.addToTrackedRegistry(this, this.reverseBindings);
    }
    fireChange(): void {
        const newValue: T = this.runFunctionAndObserve();
        if (this.cachedValue_ !== newValue) {
            this.meta_.fireChange();
            this.cachedValue_ = newValue;
        }
    }
    clearReverseBindings(): void {
        this.reverseBindings.forEach((dep: WeakRef<IBindingSource>) => {
            let ref = dep.deref();
            if (ref) {
                ref.clearBindingRefs(this.weakThis);
            } else {
                this.reverseBindings.delete(dep);
            }
        }) 
    }
    get(): T {
        // first get triffered by constructor, used only for dependency gathering.
        if (this.cachedValue_ === undefined) {
            this.cachedValue_ = this.runFunctionAndObserve();
            return this.cachedValue_!;
        }
        if (ObserveSingleton.instance.shouldAddRef(ObserveSingleton.InvalidRenderId)) {
            this.meta_.addRef();
        }
        return this.cachedValue_!;
    }

    private runFunctionAndObserve(): T {
        let renderingComponentBefore = ObserveSingleton.instance.renderingComponent;
        let renderingComponentRefBefore = ObserveSingleton.instance.renderingComponentRef;

        ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComputed;
        ObserveSingleton.instance.renderingComponentRef = this;
        let newValue: T;
        try {
            newValue = this.computedLambda_();
        } catch (e: Exception) {
            StateMgmtConsole.log(`@Computed Exception caught for ${this.varName}: ${e.toString()}.`);
            throw e;
        } finally {
            ObserveSingleton.instance.renderingComponent = renderingComponentBefore;
            ObserveSingleton.instance.renderingComponentRef = renderingComponentRefBefore;
        }
        return newValue;
    }
}