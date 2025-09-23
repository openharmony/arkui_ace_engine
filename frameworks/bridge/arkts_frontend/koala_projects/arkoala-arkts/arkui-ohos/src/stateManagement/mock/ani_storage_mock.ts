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

import { StateMgmtConsole } from '../tools/stateMgmtDFX';
type stateMgmtConsole=StateMgmtConsole;

export interface IAniStorage {
    get(key: string, areaMode?: Int | undefined): string | undefined;
    set(key: string, val: string, areaMode?: Int | undefined): void;
    has(key: string, areaMode?: Int | undefined): boolean;
    clear(): void;
    delete(key: string, areaMode?: Int | undefined): void;
}

export class AniStorage implements IAniStorage {
    get(key: string, areaMode: Int | undefined): string | undefined {
        console.log(`AniStorage.get key ${key}`)
        return undefined;
    }
    set(key: string, val: string, areaMode: Int | undefined): void {
        console.log(`AniStorage.set key ${key} jsonValue ${val}`)
    }
    has(key: string, areaMode: Int | undefined): boolean {
        console.log(`AniStorage.has key ${key}`)
        return false;
    }
    clear(): void {
        console.log(`AniStorage.clear`)
    }
    delete(key: string, areaMode: Int | undefined): void {
        console.log(`AniStorage.delete key ${key}`)
    }
}

export class PersistentStorageMocked implements IAniStorage {
    private storage_ = new Map<string, string>()
    private globalStorages_ = new Map<Int, Map<string, string>>();

    getStorage(areaMode: Int | undefined): Map<string, string> {
        if (areaMode === undefined) {
            stateMgmtConsole.log(`PersistentStorageMocked.get use storage_`);
            return this.storage_;
        }

        if (this.globalStorages_.has(areaMode)) {
            return this.globalStorages_.get(areaMode)!;
        }

        let ret = new Map<string, string>();
        this.globalStorages_.set(areaMode, ret);
        return ret;
    }

    get(key: string, areaMode: Int | undefined): string | undefined {
        stateMgmtConsole.log(`PersistentStorageMocked.get key ${key}`)
        return this.getStorage(areaMode).get(key);
    }
    set(key: string, val: string, areaMode: Int | undefined): void {
        stateMgmtConsole.log(`PersistentStorageMocked.set key ${key} jsonValue ${val}`)
        this.getStorage(areaMode).set(key, val);
    }
    has(key: string, areaMode: Int | undefined): boolean {
        let flag = this.getStorage(areaMode).has(key);
        stateMgmtConsole.log(`PersistentStorageMocked.has key ${key + ' ' + flag} `)
        return flag;
    }
    clear(): void {
        stateMgmtConsole.log(`PersistentStorageMocked.clear`)
        this.storage_.clear();
        this.globalStorages_.clear()
    }
    delete(key: string, areaMode: Int | undefined): void {
        stateMgmtConsole.log(`PersistentStorageMocked.delete key ${key}`)
        this.getStorage(areaMode).delete(key);
    }
}