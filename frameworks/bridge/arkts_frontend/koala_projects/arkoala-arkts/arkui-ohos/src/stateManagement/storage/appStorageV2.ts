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

import { uiUtils } from '../base/uiUtilsImpl';
import { StorageHelper } from './persistenceV2'
import { StorageDefaultCreator } from './persistenceV2'
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

export class AppStorageV2 {
    public static connect<T extends object>(
        ttype: Type,
        key: string,
        defaultCreator?: StorageDefaultCreator<T>
    ): T | undefined {
        return AppStorageV2Impl.instance().connect(ttype, key, defaultCreator);
    }

    public static connect<T extends object>(ttype: Type, defaultCreator?: StorageDefaultCreator<T>): T | undefined {
        return AppStorageV2Impl.instance().connect(ttype, defaultCreator);
    }

    public static remove(keyOrType: string | Type): void {
        AppStorageV2Impl.instance().remove(keyOrType);
    }

    public static keys(): Array<string> {
        return AppStorageV2Impl.instance().keys();
    }
}

export class AppStorageV2Impl {
    private static instance_: AppStorageV2Impl | undefined = undefined;
    private memorizedValues_: Map<string, Object>; // IObservedObject?

    constructor() {
        super();
        this.memorizedValues_ = new Map<string, Object>();
    }

    public static instance(): AppStorageV2Impl {
        if (AppStorageV2Impl.instance_) {
            return AppStorageV2Impl.instance_!;
        }
        AppStorageV2Impl.instance_ = new AppStorageV2Impl();
        return AppStorageV2Impl.instance_!;
    }

    public connect<T extends object>(
        ttype: Type,
        key: string,
        defaultCreator?: StorageDefaultCreator<T>
    ): T | undefined {
        if (ttype.isPrimitive()) {
            throw new Error(StorageHelper.INVALID_DEFAULT_VALUE_PRIMITIVE);
        }
        if (!StorageHelper.isKeyValid(key)) {
            return undefined;
        }

        if (!this.memorizedValues_.has(key!)) {
            if (defaultCreator === undefined) {
                throw new Error(StorageHelper.INVALID_DEFAULT_VALUE_CREATOR);
            }
            let defaultValue = defaultCreator!();
            StorageHelper.checkTypeByInstanceOf(key!, ttype, defaultValue);
            let observedValue = uiUtils.makeObserved(defaultValue, true);

            this.memorizedValues_.set(key!, observedValue);
            return observedValue;
        }

        let obj = this.memorizedValues_.get(key!);
        StorageHelper.checkTypeByType(key!, ttype, Type.of(obj));
        return obj as T;
    }

    public connect<T extends object>(ttype: Type, defaultCreator?: StorageDefaultCreator<T>): T | undefined {
        return this.connect(ttype, ttype.getName(), defaultCreator);
    }

    public remove(keyOrType: string | Type): void {
        const key = StorageHelper.getKeyOrTypeNameWithChecks(keyOrType);
        if (!key) {
            return;
        }
        this.removeFromMemory(key!);
    }

    public keys(): Array<string> {
        return Array.from(this.memorizedValues_.keys());
    }

    private removeFromMemory(key: string): void {
        const isDeleted: boolean = this.memorizedValues_.delete(key);
        if (!isDeleted) {
            StateMgmtConsole.log(StorageHelper.DELETE_NOT_EXIST_KEY);
        }
    }
}
