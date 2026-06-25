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
import { DecoratedV1VariableBase } from './decoratorBase';
import { IDecoratedV1Variable, IDecoratedMutableVariable, IVariableOwner, WatchFuncType } from '../decorator';
import { ILinkDecoratedVariable } from '../decorator';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX, ObservedObjectRegistry } from '../tools/stateMgmtDFX';
import { StateDecoratedVariable } from './decoratorState';

/**
 * implementation of V1 @Link
 *
 * must no have local init
 * must have source of same type
 * source most be a Decorated variable
 * source is allowed to be immutable (@ObjectLink),
 *   when the unsolved issues arises that a set on @Link has no effect
 * @Link reads-through from source, and if source mutable also writes-through
 * to source. Therefore, source meta.addRef and meta.fireChange is enough to
 * manage dependencies of the @link: LinkDecoratedVariable does not use its meta
 */
export class LinkDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements ILinkDecoratedVariable<T> {
    private sourceGet_: () => T;
    private sourceSet_?: (newValue: T) => void;

    // localInitValue is the rhs of @state variable : type = localInitialValue;
    // caller ensure it is IObseredObject, eg. by wrapping
    constructor(
        owningView: IVariableOwner | undefined,
        varName: string,
        source: IDecoratedV1Variable<T>,
        sourceGet: () => T,
        sourceSet: (newValue: T) => void,
        watchFunc?: WatchFuncType
    ) {
        super('@Link', owningView, varName, watchFunc);
        const initValue = sourceGet();
        this.sourceGet_ = sourceGet;
        this.sourceSet_ = sourceSet;

        if (source instanceof LinkDecoratedVariable) {
            this.source_ = source.getSource();
        } else {
            this.source_ = source;
        }
        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        // registerWatchtoSource is done in factory

        // Register the relationship between this Link variable and the observed object it uses
        this.registerToObservedObject(initValue);
    }

    public getInfo(): string {
        return `@Link ${this.varName} (LinkDecoratedVariable)`;
    }

    public get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`${this.decorator} ${this.getTraceInfo()}`);
        this.selfTrack();
        return this.sourceGet_();
    }

    public set(newValue: T): void {
        const oldValue = this.sourceGet_();
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`${this.decorator} ${oldValue === newValue} ${this.setTraceInfo()}`);
        if (oldValue !== newValue) {
            if (this.sourceSet_ === undefined) {
                throw new Error(`${this.getInfo()}: Can not set @Link value. @Link source is immutable error.`);
            }
            this.checkValueIsNotFunction(newValue);
            const value = uiUtils.makeV1Observed(newValue);
            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);

            // Update ObservedObjectRegistry registration
            this.updateObservedObjectRegistration(oldValue, value);

            // a @Link set  truggers a meta.fireChange on the source XXXDecoratedVariable
            // set also get above.
            this.sourceSet_!(value);
        }
    }

    // Add a private setter for closures, then:
 public resetOnReuse(newSource: IDecoratedV1Variable<T>): void {
    const oldValue = this.sourceGet_();
    const oldSource = this.source_;

    const oldWatchId = this.getMyTriggerFromSourceWatchId();
    if (oldSource && oldWatchId !== -1) {
        (oldSource as DecoratedV1VariableBase<T>).removeWatch(oldWatchId);
    }

    const realSource = (newSource instanceof LinkDecoratedVariable)
        ? (newSource as LinkDecoratedVariable<T>).getSource()
        : newSource;

    this.source_ = realSource;
    const readable = realSource as Object as IDecoratedMutableVariable<T>;
    this.sourceGet_ = (): T => { return readable.get(); };
    this.sourceSet_ = (v: T): void => { readable.set(v); };

    const newWatchId = realSource.registerWatchToSource(this);
    this.setMyTriggerFromSourceWatchId(newWatchId);

    const newValue = this.sourceGet_();
    this.unregisterWatchFromObservedObjectChanges(oldValue);
    this.registerWatchForObservedObjectChanges(newValue);
    this.updateObservedObjectRegistration(oldValue, newValue);

    // === KEY FIX ===
    // The koalaui memo scopes that read this @Link during the previous parent's
    // tenure recorded dependency edges against `oldSource`'s meta. After this
    // closure swap, those scopes still subscribe to oldSource. We need to
    // invalidate them so they re-run, at which point Link.get() will pass
    // through to the new source and addRef against newSource's meta — migrating
    // the edges naturally.
    //
    // Fire oldSource's backing meta to mark all existing subscribers dirty.
    if (oldSource && (oldSource as Object) instanceof StateDecoratedVariable) {
        const oldStateSource = oldSource as StateDecoratedVariable<T>;
        // fireChange triggers all dependent memo scopes to invalidate
        oldStateSource.fireChange();
        console.log(`GlobalReuse: Link.resetOnReuse FIRED oldSource meta to invalidate memo scopes`);
    }

    console.log(`GlobalReuse: Link.resetOnReuse EXIT varName=${this.varName} oldVal=${oldValue} newVal=${newValue}`);
}
    private source_: IDecoratedV1Variable<T>;

    public getSource(): IDecoratedV1Variable<T> {
        return this.source_;
    }

    public aboutToBeDeletedInternal(): void {
        // Unregister from the observed object before deletion
        const currentValue = this.sourceGet_();
        this.unregisterFromObservedObject(currentValue);

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}
