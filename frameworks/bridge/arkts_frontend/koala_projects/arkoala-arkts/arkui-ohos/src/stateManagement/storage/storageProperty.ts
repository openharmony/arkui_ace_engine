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
import { IStorageProperty, StorageProperty } from './storageBase';
import { DecoratedV1VariableBase } from '../decoratorImpl/decoratorBase';
import { WatchFunc } from '../decoratorImpl/decoratorWatch';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { WatchIdType } from '../decorator';

type GetType<T> = () => T;
type SetType<T> = (newVal: T) => void;
export type OnChangeType<T> = (propName: string, newValue: T) => void;

export enum ColorMode {
    LIGHT = 0,
    DARK = 1
}

export enum LayoutDirection {
    RTL = 0,
    LTR = 1,
    Auto = 2
}

export class AbstractProperty<T> extends DecoratedV1VariableBase<T> implements IStorageProperty {
    private readonly key_: string;
    private readonly get_: GetType<T>;
    private readonly set_: SetType<T>;
    private readonly storageProperty_: StorageProperty<T> | undefined;
    private tempWatchId: WatchIdType | undefined = undefined;

    constructor(key: string, get: GetType<T>, set: SetType<T>, storageProperty?: StorageProperty<T>) {
        super('AbstractProperty', undefined, key);

        this.key_ = key;
        this.get_ = get;
        this.set_ = set;
        this.storageProperty_ = storageProperty;
        // as it register watch to source, no need to register watch itself.
    }

    // FIXME change to info()
    // this needs renaming of info property (not function) in base classes!
    public info_(): string {
        return this.key_;
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
            if (this.tempWatchId !== undefined) {
                this.storageProperty_!.__unregister(this.tempWatchId!);
                this.tempWatchId = undefined;
            }
            return;
        }
        if (typeof onChangeCbFunc === 'function') {
            if (this._watchFuncs.size > 0) {
                this._watchFuncs.clear();
            } 
            const watchFunc = (propName: string): void => {
                (onChangeCbFunc as OnChangeType<T>)(propName, this.get());
            };
            const watchFuncObj = new WatchFunc(watchFunc);
            this._watchFuncs.set(watchFuncObj.id(), watchFuncObj);
            if (this.tempWatchId === undefined) {
                this.tempWatchId = this.storageProperty_!.registerWatchToStorageSource(this);
            }
        }
    }
}

/**
 * for backward compatibility only
 *
 */
export class SubscribedAbstractProperty<T> extends AbstractProperty<T> {
    constructor(key: string, get: GetType<T>, set: SetType<T>) {
        super(key, get, set);
    }

    public onChange(onChangeCbFunc: OnChangeType<T> | undefined): void {
        if (onChangeCbFunc === undefined) {
            // clear all register callbacks
            this._watchFuncs.clear();
            return;
        }
        if (typeof onChangeCbFunc === 'function') {
            if (this._watchFuncs.size > 0) {
                this._watchFuncs.clear();
            } 
            const watchFunc = (propName: string): void => {
                (onChangeCbFunc as OnChangeType<T>)(propName, this.get());
            };
            const watchFuncObj = new WatchFunc(watchFunc);
            this._watchFuncs.set(watchFuncObj.id(), watchFuncObj);
        }
    }

    public aboutToBeDeleted(): void {}
}
