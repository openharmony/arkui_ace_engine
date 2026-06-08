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
import { IProvideDecoratedVariable, IVariableOwner, ConsumeOptions } from '../decorator';
import { WatchFuncType } from '../decorator';
import { IConsumeDecoratedVariable } from '../decorator';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX, ObservedObjectRegistry } from '../tools/stateMgmtDFX';
import { ProvideDecoratedVariable } from './decoratorProvide';
export class ConsumeDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IConsumeDecoratedVariable<T> {
    provideAliasName: string;
    sourceProvide_: ProvideDecoratedVariable<T> | undefined;
    checkFake: boolean = false;
    constructor(owningView: IVariableOwner, varName: string, provideAliasName: string, watchFunc?: WatchFuncType, consumeOptions?: ConsumeOptions<T>) {
        super('@Consume', owningView, varName, watchFunc);
        this.provideAliasName = provideAliasName;
        this.sourceProvide_ = owningView.__findProvide__Internal<T>(provideAliasName) as ProvideDecoratedVariable<T> | undefined;
        if (!this.sourceProvide_) {
            if (consumeOptions) {
                this.checkFake = true;
                // use fake Provide source
                this.sourceProvide_ = new ProvideDecoratedVariable<T>(varName, uiUtils.makeV1Observed(consumeOptions!.defaultValue) as T);
                this.registerWatchForObservedObjectChanges(this.sourceProvide_!.get(false));
            } else {
                throw new Error(`Can not initialize @Consume. @Consume ${varName} has no default value or @Provide source!`);
            }
        } else {
            const wid = this.sourceProvide_!.registerWatchToSource(this);
            this.setMyTriggerFromSourceWatchId(wid);
        }
        const initValue = this.sourceProvide_!.get();
        this.registerToObservedObject(initValue);
    }

    public get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consume ${this.getTraceInfo()}`);
        this.selfTrack();
        return this.sourceProvide_!.get();
    }

    public set(newValue: T): void {
        const oldValue = this.sourceProvide_!.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consume ${oldValue === newValue} ${this.setTraceInfo()}`);
        if (oldValue === newValue) {
            return;
        }
        this.checkValueIsNotFunction(newValue);
        if (!this.checkFake) {
            this.sourceProvide_!.set(newValue);
            this.updateObservedObjectRegistration(oldValue, this.sourceProvide_!.get(false));
            return;
        }

        // Update ObservedObjectRegistry registration before setting the new value
        // Only update when using fake Provide source
        const processedNewValue = uiUtils.makeV1Observed(newValue);
        this.updateObservedObjectRegistration(oldValue, processedNewValue);

        this.unregisterWatchFromObservedObjectChanges(oldValue);
        this.sourceProvide_!.set(newValue, false);
        this.registerWatchForObservedObjectChanges(this.sourceProvide_!.get(false));
        this.execWatchFuncs();
    }

    public getSource(): IProvideDecoratedVariable<T> {
        return this.sourceProvide_! as IProvideDecoratedVariable<T>;
    }

    public resetOnReuse(provideAliasName: string, watchFunc?: WatchFuncType, consumeOptions?: ConsumeOptions<T>): void {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consume resetOnReuse alias=${provideAliasName}`);
        
        const oldSource = this.sourceProvide_;
        
        // detach watches and observed-object registrations from current source
        if (this.sourceProvide_) {
            const currentValue = this.sourceProvide_!.get(false);
            this.unregisterWatchFromObservedObjectChanges(currentValue);
            if (this.checkFake) {
                this.unregisterFromObservedObject(currentValue);
            }
        }

        // Remove watch the old provide registered on us, if we tracked it.
        const oldWatchId = this.getMyTriggerFromSourceWatchId();
        if (oldSource && oldWatchId !== -1) {
            (oldSource as DecoratedV1VariableBase<T>).removeWatch(oldWatchId);
            this.setMyTriggerFromSourceWatchId(-1);
        }

        this.provideAliasName = provideAliasName;
        const owner = this.owningComponent;
        this.sourceProvide_ = owner ? owner.__findProvide__Internal<T>(provideAliasName) as ProvideDecoratedVariable<T> | undefined : undefined;
        this.checkFake = false;
        
        if (!this.sourceProvide_) {
            if (consumeOptions) {
                this.checkFake = true;
                this.sourceProvide_ = new ProvideDecoratedVariable<T>(this.varName, uiUtils.makeV1Observed(consumeOptions!.defaultValue) as T);
                this.registerWatchForObservedObjectChanges(this.sourceProvide_!.get(false));
            } else {
                throw new Error(`Can not resetOnReuse @Consume ${this.varName}: no default value or @Provide source.`);
            }
        } else {
            const newWatchId = this.sourceProvide_!.registerWatchToSource(this);
            this.setMyTriggerFromSourceWatchId(newWatchId);
        }
        
        const newValue = this.sourceProvide_!.get();
        this.registerToObservedObject(newValue);

        // === KEY FIX (mirrors Link.resetOnReuse) ===
        // Memo scopes that read `this.consumeVal` during the previous parent's
        // tenure recorded dependency edges against `oldSource`'s backing meta
        // (because Consume.get pass-throughs to sourceProvide_.get, which addRefs
        // on the Provide's own backing). After this swap, those scopes still
        // point at oldSource. Fire oldSource's meta so they invalidate next frame
        // and re-record edges against the new source.
        if (oldSource) {
            oldSource.fireChange();
            console.log(`GlobalReuse: Consume.resetOnReuse FIRED oldSource meta to invalidate memo scopes`);
        }
    }

    public aboutToBeDeletedInternal(): void {
        if (this.checkFake && this.sourceProvide_) {
            const currentValue = this.sourceProvide_!.get(false);
            this.unregisterFromObservedObject(currentValue);
        }

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}
