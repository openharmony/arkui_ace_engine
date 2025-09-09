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

import { ExtendableComponent } from '../../component/extendableComponent';
import { DecoratedV1VariableBase } from './decoratorBase';
import { IProvideDecoratedVariable } from '../decorator';
import { WatchFuncType } from '../decorator';
import { IConsumeDecoratedVariable } from '../decorator';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
export class ConsumeDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IConsumeDecoratedVariable<T> {
    provideAliasName: string;
    sourceProvide_: IProvideDecoratedVariable<T> | null;
    constructor(owningView: ExtendableComponent, varName: string, provideAliasName: string, watchFunc?: WatchFuncType) {
        super('@Consume', owningView, varName, watchFunc);
        this.provideAliasName = provideAliasName;
        this.sourceProvide_ = null// TODO:SAM
//        this.sourceProvide_ = owningView.findProvide<T>(provideAliasName);
//        if (this.sourceProvide_ === null) {
//            throw new Error('no Provide found for Consume');
//        }
//        if (this.sourceProvide_) {
            // check type
//        }
//        const initValue = this.sourceProvide_!.get();
//        this.registerWatchForObservedObjectChanges(initValue);
//        this.sourceProvide_!.registerWatchToSource(this);
    }
    public get(): T {
        const value = this.sourceProvide_!.get();
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }

    public set(newValue: T): void {
        const oldValue = this.sourceProvide_!.get();
        if (oldValue !== newValue) {
            const value = UIUtils.makeObserved(newValue);
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);
            this.sourceProvide_!.set(value);
        }
    }

    public getSource(): IProvideDecoratedVariable<T> {
        return this.sourceProvide_!;
    }
}
