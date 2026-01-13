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

import {
    IDecoratedV1Variable,
    IDecoratedV2Variable,
    IVariableOwner,
    IWatchSubscriberRegister,
    OBSERVE,
    WatchFuncType,
    WatchIdType,
} from '../decorator';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { StateMgmtTool } from '#stateMgmtTool';
import { WatchFunc } from './decoratorWatch';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { ObserveSingleton } from '../base/observeSingleton';

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
    protected readonly owningComponent_: IVariableOwner | undefined;
    // can be read publically
    public _varName: string;
    public decorator: string;
    // public readonly info: string;  Remaining to be added
    get varName(): string {
        return this._varName;
    }
    set varName(value: string) {
        this._varName = value;
    }
    constructor(decorator: string, owningComponent: IVariableOwner | undefined, varName: string) {
        this.decorator = decorator;
        this.owningComponent_ = owningComponent;
        this._varName = varName;
    }

    public getTraceInfo(): string {
            return `get: ${this.varName} ${Type.of(this.owningComponent_)} ${this.shouldAddRef()} ${ObserveSingleton.instance.renderingComponent}`
        }
    
    public setTraceInfo(): string {
        return `set: ${this.varName} ${Type.of(this.owningComponent_)}`;
    } 

    public updateTraceInfo(): string {
        return `update: ${this.varName} ${Type.of(this.owningComponent_)}`;
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
    protected onObservedObjectChangeExecWatchFuncs_: WatchFunc;

    constructor(
        decorator: string,
        owningComponent: IVariableOwner | undefined,
        varName: string,
        watchFunc?: WatchFuncType
    ) {
        super(decorator, owningComponent, varName);
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
        this.onObservedObjectChangeExecWatchFuncs_ = new WatchFunc(this.execWatchFuncs);
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
        if (StateMgmtTool.isIWatchSubscriberRegister(value)) {
            this.onObservedObjectChangeExecWatchFuncs_.registerMeTo(value as IWatchSubscriberRegister);
        } else {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isIWatchSubscriberRegister(handler)) {
                this.onObservedObjectChangeExecWatchFuncs_.registerMeTo(handler as IWatchSubscriberRegister);
            }
        }
    }

    /* compiler BUG: change to protcted */
    public unregisterWatchFromObservedObjectChanges(value: T): void {
        if (!(value && typeof value === 'object')) {
            return;
        }
        if (StateMgmtTool.isIWatchSubscriberRegister(value)) {
            this.onObservedObjectChangeExecWatchFuncs_.unregisterMeFrom(value as IWatchSubscriberRegister);
        } else {
            // check if value is observed / proxied interface
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isIWatchSubscriberRegister(handler)) {
                this.onObservedObjectChangeExecWatchFuncs_.unregisterMeFrom(handler as IWatchSubscriberRegister);
            }
        }
    }
    
    public isViewActive(): boolean {
        return this.owningComponent_!.__isViewActive__Internal();
    }

    /* compiler BUG: change to protcted */
    public execWatchFuncs(_: string = ''): void {
        if (this.owningComponent_ && !this.isViewActive()) {
            StateUpdateLoop.addFreezeTask(this.owningComponent_!.getUniqueId(), this.onObservedObjectChangeExecWatchFuncs_.id());
        }
        else {
            if (this._watchFuncs.size > 0) {
                this._watchFuncs.forEach((watchFunc, id) => {
                    watchFunc.execute(this.varName);
                });
            }
        }
        
    }

    public registerWatchToSource(watchOwner: IDecoratedV1Variable<T>): WatchIdType {
        if (!StateMgmtTool.isDecoratedV1VariableBase(watchOwner)) {
            throw new SyntaxError('syntax error');
        }
        const watchOwnerBase = watchOwner as DecoratedV1VariableBase<T>;
        const weakWatchOwner = new WeakRef<DecoratedV1VariableBase<T>>(watchOwnerBase);
        const watchFuncObj = new WatchFunc((_: string) => {});
        const watchFunc: WatchFuncType = (_: string) => {
            const watchOwner1 = weakWatchOwner.deref();
            if (watchOwner1) {
                watchOwner1.execWatchFuncs();
            } else {
                this._watchFuncs.delete(watchFuncObj.id());
            }
        };
        watchFuncObj.setFunc(watchFunc);
        this._watchFuncs.set(watchFuncObj.id(), watchFuncObj);
        return watchFuncObj.id();
    }

    public checkValueIsNotFunction(value: Any): void {
        if (typeof value === 'function') {
            let componentName: string = this.owningComponent_ ? Class.of(this.owningComponent_!).getName() : 'undefined';
            if (componentName.indexOf('.') >= 0) {
                componentName = componentName.substring(componentName.lastIndexOf('.') + 1);
            }
            let msg: string = `@Component '${componentName}': Illegal variable value error `;
            msg += `with decorated variable ${this.decorator} '${this._varName}': `;
            msg += `failed validation: 'not function'`;
            try {
                msg += `, attempt to assign value type: '${typeof value}'`;
                msg += `, value: '${JSON.stringify(value, null, 4)}'`;
            } catch(e) { }
            msg += '!';
            console.error(msg);
            throw new TypeError(msg);
        }
    }
}

export abstract class DecoratedV2VariableBase<T> extends DecoratedVariableBase implements IDecoratedV2Variable<T> {
    constructor(decorator: string, owningComponent: IVariableOwner | undefined, varName: string) {
        super(decorator, owningComponent, varName);
    }
    abstract resetOnReuse(newValue: T): void;
    public info(): string {
        return this.varName;
    }

    get(): Any {
        return undefined as Any;
    }

    set(newValue: Any): void {
        return;
    }
}
