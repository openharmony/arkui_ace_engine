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

import { IFactoryInternal } from '../base/iFactoryInternal';
import { TrackedMutableStateMeta } from '../base/mutableStateMeta';
import { IMutableKeyedStateMeta, IMutableStateMeta } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { StateMgmtTool } from '#stateMgmtTool';
import { DecoratorBackingValue } from '../base/backingValue';
import { MutableKeyedStateMeta, MutableStateMeta } from '../base/mutableStateMeta';

// FactoryInternalImpl contains implementation needed by unit test framework tracking
export class FactoryInternalImpl implements IFactoryInternal {
    public mkDecoratorValue<T>(info: string, initValue: T): IBackingValue<T> {
        return new DecoratorBackingValue<T>(info, initValue);
    }
    public mkMutableStateMeta(info: string): IMutableStateMeta {
        return new TrackedMutableStateMeta(info);
    }
    public mkMutableKeyedStateMeta(info: string): IMutableKeyedStateMeta {
        return new MutableKeyedStateMeta(info);
    }
    public mkObservedInterfaceProxy<T extends Object>(x: T): T {
        return StateMgmtTool.createProxy<T>(x);
    }
}
