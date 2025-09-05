/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
import { IStorageProperty } from './storageBase';
import { DecoratedV1VariableBase } from '../decoratorImpl/decoratorBase';
import { WatchFunc } from '../decoratorImpl/decoratorWatch';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

type GetType<T> = () => T;
type SetType<T> = (newVal: T) => void;
export type OnChangeType<T> = (propName: string, newValue: T) => void;

export interface IStorageProperties {
    value: NullishType;
    ttype: Type;
}

export class AbstractProperty<T> extends DecoratedV1VariableBase<T> implements IStorageProperty {
    private readonly key_: string;
    private readonly ttype_: Type;
    private readonly get_: GetType<T>;
    private readonly set_: SetType<T>;

    constructor(key: string, ttype: Type, get: GetType<T>, set: SetType<T>) {
        super('AbstractProperty', null, key);
        StateMgmtConsole.log(`create new AbstractProperty for key '${key}' `);

        this.key_ = key;
        this.ttype_ = ttype;
        this.get_ = get;
        this.set_ = set;

        const initValue: T = this.get_();

        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        this.registerWatchForObservedObjectChanges(initValue);
        // registerWatch  to source is done in the factory function
    }

    // FIXME change to info()
    // this needs renaming of info property (not function) in base classes!
    public info_(): string {
        return this.key_;
    }

    public ttype(): Type {
        return this.ttype_;
    }

    public get(): T {
        return this.get_();
    }

    public set(newValue: T): void {
        this.set_(newValue);
    }

    public onChange(onChangeCbFunc: OnChangeType<T> | undefined): void {
        if (onChangeCbFunc === undefined) {
            // clear all register callbacks
            this._watchFuncs.clear();
        }
        if (typeof onChangeCbFunc === 'function') {
            const watchFunc = (propName: string): void => {
                (onChangeCbFunc as OnChangeType<T>)(propName, this.get());
            };
            const watchFuncObj = new WatchFunc(watchFunc);
            this._watchFuncs.set(watchFuncObj.id(), watchFuncObj);
        }
    }
}

/**
 * for backward compatibility only
 *
 */
export class SubscribedAbstractProperty<T> extends AbstractProperty<T> {
    constructor(key: string, ttype: Type, get: GetType<T>, set: SetType<T>) {
        super(key, ttype, get, set);
    }

    public aboutToBeDeleted(): void {}
}
