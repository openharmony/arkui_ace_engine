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

import { LocalStorage } from '../storage/localStorage';
import { IProvideDecoratedVariable, IProviderDecoratedVariable, IVariableOwner } from '../decorator';

export class ExtendableComponent implements IVariableOwner { // implements IExtendableComponent {
    protected parent_: ExtendableComponent | null;
    public localStorage_: LocalStorage;
    public isActive_: int = 1;
    private static uniqueId_ = 1;

    constructor(parent: ExtendableComponent | null = null, storage?: LocalStorage | undefined) {
        this.parent_ = parent;
        this.localStorage_ = (storage !== undefined)? storage : new LocalStorage();
    }

    isViewActive(): boolean {
        return true;
    }

    getUniqueId(): int
    {
        return ExtendableComponent.uniqueId_++;
    }

    getLocalStorage(): LocalStorage {
        return new LocalStorage();
    }

    addProvide<T>(alias: String, v: IProvideDecoratedVariable<T>, allowOverride: Boolean|undefined): void {
        console.log("addProvide not implemented");
    }
    addProvider<T>(alias: String, v: IProviderDecoratedVariable<T>): void {
        console.log("addProvider not implemented");
    }
    findProvide<T>(alias: String): IProvideDecoratedVariable<T>|undefined {
        console.log("findProvide not implemented");
        return undefined;
    }
    findProvider<T>(alias: String): IProviderDecoratedVariable<T>|undefined {
        console.log("findProvider not implemented");
        return undefined;
    }
 }