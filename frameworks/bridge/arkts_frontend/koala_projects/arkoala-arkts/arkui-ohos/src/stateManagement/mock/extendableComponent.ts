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
import {
    IDecoratorBaseRegistry,
    IProvideDecoratedVariable,
    IProviderDecoratedVariable,
    IVariableOwner,
} from '../decorator';
import { CustomComponentLifecycle } from '@component/customComponent';
import { IEnvVariable } from '@decoratorEnv';
import { ActiveAndInactiveCallbackType, CustomComponentContext } from '../utils';

export class ExtendableComponent implements IVariableOwner {
    protected parent_: ExtendableComponent | null;
    public localStorage_: LocalStorage;
    public isActive_: int = 1;
    private static uniqueId_ = 1;

    constructor(parent: ExtendableComponent | null = null, storage?: LocalStorage | undefined) {
        this.parent_ = parent;
        this.localStorage_ = (storage !== undefined)? storage : new LocalStorage();
    }

    static current: Object | undefined = undefined;

    getUniqueId(): int {
        return ExtendableComponent.uniqueId_++;
    }

    getownedStateVariables(): Array<Object> {
        return new Array<Object>();
    }

    __getLifecycle__Internal(): CustomComponentLifecycle {
        return {} as CustomComponentLifecycle;
    }

    __isViewActive__Internal(): boolean {
        return true;
    }

    __getLocalStorage__Internal(): LocalStorage {
        return this.localStorage_;
    }

    __addProvide__Internal<T>(alias: string, v: IProvideDecoratedVariable<T>, allowOverride?: boolean): void {
    }

    __findProvide__Internal<T>(alias: string): IProvideDecoratedVariable<T> | undefined {
        return undefined;
    }

    __addProvider__Internal<T>(alias: string, v: IProviderDecoratedVariable<T>): void {
    }

    __findProvider__Internal<T>(alias: string): IProviderDecoratedVariable<T> | undefined {
        return undefined;
    }

    __registerStateVariables__Internal(stateVariable: IDecoratorBaseRegistry): void {
    }

    __addEnvInstance__Internal(envProperty: IEnvVariable): void {
    }

    __getCustomComponentContext__Internal(): CustomComponentContext {
        return {
            registerActiveAndInactiveCallback: (
                active?: ActiveAndInactiveCallbackType,
                inactive?: ActiveAndInactiveCallbackType
            ): void => {}
        } as CustomComponentContext;
    }

    __registerActiveAndInactiveCallback__Internal(
        active?: ActiveAndInactiveCallbackType,
        inactive?: ActiveAndInactiveCallbackType
    ): void {
    }
}