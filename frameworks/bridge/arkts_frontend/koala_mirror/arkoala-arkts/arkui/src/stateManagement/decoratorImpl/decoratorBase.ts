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
import { WatchFunc } from './decoratorWatch';
import { IDecoratedV1Variable } from '../decorator';
import { WatchFuncType, ISubscribedWatches, WatchIdType } from '../decorator';
import { ExtendableComponent } from '../../component/extendableComponent';
import { OBSERVE } from '../decorator';
import { StateMgmtTool } from '#stateMgmtTool';

/**
It is useful to have separate class implement each variable decoratore,  e.g. for DFX, not use `MutableState` as currently done.
V1 decorator implementations can limit permissableAddRef (the reading depth for recording dependencies when starting to read from a V1 variable)

V1:
* @State implements IDecoratedMutableVariable
* @ObjectLink implements IDecoratedImmutableVariable, IDecoratedUpdatableVariable
* @Prop implements IDecoratedMutableVariable, IDecoratedUpdatableVariable
* @Link implements IDecoratedMutableVariable  (updates work a bit special)
* @Provide implements IDecoratedMutableVariable, IDecoratedUpdatableVariable
* @Consume implements IDecoratedMutableVariable  (updates work a bit special)
* @Local/StorageLink/Prop IDecoratedMutableVariable
V2:
* @Local implements IDecoratedMutableVariable
* @Param implements IDecoratedImmutableVariable, IDecoratedUpdatableVariable
* @Param @Once implements IDecoratedMutableVariable
*/

/**
 * Base class of all decorated variable classes
 */
export class DecoratedVariableBase {
    protected readonly owningComponent_: ExtendableComponent | null;
    // can be read publically
    public _varName: string;
    public readonly decorator: string;
    // public readonly info: string;  Remaining to be added
    get varName(): string {
        return this._varName;
    }
    set varName(value: string) {
        this._varName = value;
    }
    constructor(decorator: string, owningComponent: ExtendableComponent | null, varName: string) {
        this.decorator = decorator;
        this.owningComponent_ = owningComponent;
        this._varName = varName;
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }
}

/**
base class for all V1 decorated DecoratedVariableBase implements DecoratedVariableBase
*/

export abstract class DecoratedV1VariableBase<T> extends DecoratedVariableBase implements IDecoratedV1Variable<T> {
    // V1 decorators can optionally have one @Watch function
    // to manage Local/AppStorge dependencies additional WatchFunc are required
    // therefore _watchFuncs is an Map<WatchIdType, WatchFunc>
    /* compiler BUG: change to protcted */
    public readonly _watchFuncs: Map<WatchIdType, WatchFunc> = new Map<WatchIdType, WatchFunc>();
    protected myTriggerFromSourceWatchId_: WatchIdType = -1;

    constructor(
        decorator: string,
        owningComponent: ExtendableComponent | null,
        varName: string,
        watchFunc?: WatchFuncType
    ) {
        super(decorator, owningComponent, varName);
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
    }

    public info(): string {
        return this.varName;
    }

    get(): T {
        return undefined as T;
    }

    set(newValue: T): void {
        return;
    }

    public setMyTriggerFromSourceWatchId(id: WatchIdType): void {
        this.myTriggerFromSourceWatchId_ = id;
    }

    public getMyTriggerFromSourceWatchId(): WatchIdType {
        return this.myTriggerFromSourceWatchId_;
    }

    public addWatch(watchFunc?: WatchFuncType): void {
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
    }

    /**
     * remove WatchFunc with given id
     * @param watchId
     * @returns
     */
    public removeWatch(watchId: WatchIdType): boolean {
        return this._watchFuncs.delete(watchId);
    }

    /* compiler BUG: change to protcted */
    public registerWatchForObservedObjectChanges(value: T): void {
        if (!(value && typeof value === 'object')) {
            return;
        }
        if (StateMgmtTool.isISubscribedWatches(value as Object)) {
            const iSubscribedWatches = value as Object as ISubscribedWatches;
            this._watchFuncs.forEach((watchFunc) => {
                watchFunc.registerMeTo(iSubscribedWatches);
            });
        } else {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isISubscribedWatches(handler as Object)) {
                const iSubscribedWatches = handler as Object as ISubscribedWatches;
                this._watchFuncs.forEach((watchFunc) => {
                    watchFunc.registerMeTo(iSubscribedWatches);
                });
            }
        }
    }

    /* compiler BUG: change to protcted */
    public unregisterWatchFromObservedObjectChanges(value: T): void {
        if (!(value && typeof value === 'object')) {
            return;
        }
        if (StateMgmtTool.isISubscribedWatches(value as Object)) {
            const iSubscribedWatches = value as Object as ISubscribedWatches;
            this._watchFuncs.forEach((watchFunc) => {
                watchFunc.unregisterMeFrom(iSubscribedWatches);
            });
        } else {
            // check if value is observed / proxied interface
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isISubscribedWatches(handler as Object)) {
                const iSubscribedWatches = handler as ISubscribedWatches;
                this._watchFuncs.forEach((watchFunc) => {
                    watchFunc.unregisterMeFrom(iSubscribedWatches);
                });
            }
        }
    }

    /* compiler BUG: change to protcted */
    public execWatchFuncs(): void {
        this._watchFuncs.forEach((watchFunc, id) => {
            watchFunc.execute(this.varName);
        });
    }

    public registerWatchToSource(me: IDecoratedV1Variable<T>): void {
        if (!StateMgmtTool.isDecoratedV1VariableBase(me)) {
            throw new SyntaxError('syntax error');
        }
        const meBase = me as DecoratedV1VariableBase<T>;
        const weakMe = new WeakRef<DecoratedV1VariableBase<T>>(meBase);
        const watchThis = new WatchFunc((_: string) => {});
        const watchFunc: WatchFuncType = (_: string) => {
            const me = weakMe.deref();
            if (me) {
                me.execWatchFuncs();
            } else {
                this._watchFuncs.delete(watchThis.id());
            }
        };
        watchThis.setFunc(watchFunc);
        this._watchFuncs.set(watchThis.id(), watchThis);
    }
}
