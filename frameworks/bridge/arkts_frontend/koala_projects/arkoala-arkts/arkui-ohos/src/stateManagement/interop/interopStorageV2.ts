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

import { StorageHelper, StorageDefaultCreator } from '../storage/persistenceV2'
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { AppStorageV2Impl} from '../storage/appStorageV2';
import { transferTypeName } from '../storage/persistenceV2';

export class InteropAppStorageV2 {
    private static instance_: InteropAppStorageV2 | undefined = undefined;

    constructor() {
        this.BindDynamicStorageV2();
    }

    public static instance(): InteropAppStorageV2 {
        if (InteropAppStorageV2.instance_) {
            return InteropAppStorageV2.instance_!;
        }
        InteropAppStorageV2.instance_ = new InteropAppStorageV2();
        return InteropAppStorageV2.instance_!;
    }

    // get value from Storage in ArkTS1.1
    protected getDynamicValue_: (value: string) => object | undefined = (value: string) => {
        throw new Error('not implement');
    };
    protected removeDynamicValue_: (value: string | undefined) => boolean = (value: string | undefined) => {
        throw new Error('not implement');
    };
    protected getDynamicKeys_: () => Array<string> = () => {
        throw new Error('not implement');
    };

    public BindDynamicStorageV2(): void {
        // call ArkTS1.1 Storage to bind static Storage.
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('bindStaticAppStorageV2');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            StateMgmtConsole.log('fail to find bindStaticAppStorageV2');
            return;
        }

        // 1.1 part call 1.2 functions
        const getValue = (key: string): object | undefined => {
            const obj = AppStorageV2Impl.instance().getValue(key);
            if (obj === undefined) {
                return undefined
            }
            return obj;
        };
        const removeKey = (key: string): void => {
            AppStorageV2Impl.instance().remove(key);
        };
        const getKeys = (): Array<string> => {
            return AppStorageV2Impl.instance().keys();
        };
        
        // used by ArkTS1.2 to interop with dynamic storage map.
        const setGetValueFunc = (event: (value: string) => object | undefined): void => {
            this.getDynamicValue_ = event;
        };
        const setRemoveValueFunc = (event: (value: string | undefined) => boolean): void => {
            this.removeDynamicValue_ = event;
        };
        const setGetKeysFunc = (event: () => Array<string>): void => {
            this.getDynamicKeys_ = event;
        };

        // execute bindStaticAppStorageV2 and bind callback functions
        bindFunc.invoke(
            ESValue.wrap(getValue),
            ESValue.wrap(removeKey),
            ESValue.wrap(getKeys),
            ESValue.wrap(setGetValueFunc),
            ESValue.wrap(setRemoveValueFunc),
            ESValue.wrap(setGetKeysFunc),
        );
    }

    public connect<T extends object>(ttype: Type, key: string, defaultCreator?: StorageDefaultCreator<T>): T | undefined {
        if (ttype.isPrimitive()) {
            throw new Error(StorageHelper.INVALID_DEFAULT_VALUE_PRIMITIVE);
        }
        if (!StorageHelper.isKeyValid(key)) {
            return undefined;
        }
        if (!AppStorageV2Impl.instance().hasKey(key)) {
            // nonexistence then search in 1.1
            const interopValue = this.getDynamicValue_(key!);
            if (interopValue) {
                return interopValue! as T;
            }
        }
        // existence or not in 1.2
        return AppStorageV2Impl.instance().connect(ttype, key, defaultCreator);
    }

    public connect<T extends object>(ttype: Type, defaultCreator?: StorageDefaultCreator<T>): T | undefined {
        return InteropAppStorageV2.instance().connect(ttype, transferTypeName(ttype.getName()), defaultCreator);
    }

    public remove(keyOrType: string | Type): void {
        // delete 1.2
        const isDeleted = AppStorageV2Impl.instance().removeByInterop(keyOrType);
        if (!isDeleted) {
            // keyOrType is verified in remove function
            const key = StorageHelper.getKeyOrTypeNameWithChecks(keyOrType);
            // delete 1.1
            this.removeDynamicValue_(key);
        }
    }

    public keys(): Array<string> {
        const totalKeys = new Set<string>();
        AppStorageV2Impl.instance().keys().forEach((key: string) => {
            totalKeys.add(key);
        });
        this.getDynamicKeys_().forEach((key: string) => {
            totalKeys.add(key);
        });
        return Array.from(totalKeys.keys());
    }
}