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

/**
  skeleton of a class to support
  versioning of backing store values
*/

import { IMutableStateMeta } from '../decorator';
import { IBackingValue } from './iBackingValue';
import { TypeChecker } from '#components';
import { StateMgmtTool } from '#stateMgmtTool';
import { STATE_MGMT_FACTORY } from '../decorator';
import { ObserveSingleton } from './observeSingleton';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
export class DecoratorBackingValue<T> implements IBackingValue<T> {
    protected readonly propertyName_: string;
    private value_: T;
    protected readonly metaDependency_: IMutableStateMeta;

    constructor(propertyName: string, initValue: T) {
        if (!this.isValueValid(initValue)) {
            throw new TypeError(`${propertyName} init with non-Observed object. Type error.`);
        }
        this.propertyName_ = propertyName;
        this.value_ = initValue;
        this.metaDependency_ = STATE_MGMT_FACTORY.makeMutableStateMeta();
    }

    public get(shouldAddRef: boolean): T {
        if (shouldAddRef) {
            this.addRef();
        }
        return this.value_;
    }

    public set(newValue: T): boolean {
        if (newValue !== this.value_) {
            if (this.isValueValid(newValue)) {
                this.value_ = newValue;
                this.fireChange();
                return true;
            }
        }
        return false;
    }
    public setSilently(newValue: T): void {
        if (this.isValueValid(newValue)) {
            this.value_ = newValue;
        }
    }
    // create dependency if currently rendering anything
    // FIXME: make protected once compiler allows
    // super.addRef on protected
    public addRef(): void {
        this.metaDependency_.addRef();
    }

    // notify change to any dependencies
    // FIXME: make protected once compiler allows
    // super.addRef on protected
    public fireChange(): void {
        this.metaDependency_.fireChange();
    }

    protected isValueValid(newValue: T): boolean {
        // need add check
        return true;
    }
}
