/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { DecoratedV1VariableBase } from './decoratorBase';
import { WatchFuncType, IStoragePropDecoratedVariable } from '../decorator';
import { ExtendableComponent } from '../../component/extendableComponent';

export class StoragePropDecoratedVariable<T>
    extends DecoratedV1VariableBase<T>
    implements IStoragePropDecoratedVariable<T>
{
    private readonly propertyNameInAppStorage_: string;

    // localInitValue is the rhs of @state variable : type = localInitialValue;
    // caller ensure it is IObseredObject, eg. by wrapping
    constructor(
        owningComponent: ExtendableComponent | null,
        propertyNameInAppStorage: string,
        varName: string,
        watchFunc?: WatchFuncType
    ) {
        super('@StorageProp', owningComponent, varName, watchFunc);
        this.propertyNameInAppStorage_ = propertyNameInAppStorage;
    }
}
