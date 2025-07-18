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
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { IParamDecoratedVariable } from '../decorator';
import { UIUtils } from '../utils';
import { DecoratedV2VariableBase } from './decoratorBase';
export class ParamDecoratedVariable<T> extends DecoratedV2VariableBase implements IParamDecoratedVariable<T> {
    public readonly backing_: IBackingValue<T>;
    constructor(owningView: ExtendableComponent | null, varName: string, initValue: T) {
        super('@Param', owningView, varName);
        this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);
    }

    get(): T {
        const value = this.backing_.get(this.shouldAddRef());
        return value;
    }

    update(newValue: T): void {
        const value = this.backing_.get(false);
        if (value === newValue) {
            return;
        }
        StateUpdateLoop.add(() => {
            this.backing_.set(UIUtils.makeObserved(newValue) as T);
        });
    }
}
