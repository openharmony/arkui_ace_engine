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

import { IBackingValue } from './iBackingValue';
import { IMutableStateMeta, IMutableKeyedStateMeta } from '../decorator';
import { ISubscribedWatches } from '../decorator';
import { FactoryInternalImpl } from './factoryInternal';
/**
 * iFactoryInternal is the state mgmt factory for classes, which are not exposed
 * by the SDK and not used by UIPlugin generated code. So 'internal' use classes.
 * Using a factory still has benefit, in the case of mkDecoratorValue and
 * mkMutableKeyedStateMeta the benefit is unit tests creating special
 * derived classes to support the testing.
 */
export interface IFactoryInternal {
    // IBackingValue for Decorator implementations
    mkDecoratorValue<T>(info: string, initValue: T): IBackingValue<T>;

    mkMutableStateMeta(info: string): IMutableStateMeta;

    // IMutableKeyedStateMeta used by wrapper classes for Array, Map, Set, Date
    mkMutableKeyedStateMeta(info: string): IMutableKeyedStateMeta;

    // create a Proxy for observed interface / intrinsic object T
    // see also InterfaceProxyHandler
    mkObservedInterfaceProxy<T extends Object>(x: T): T;
}

export const FactoryInternal: IFactoryInternal = new FactoryInternalImpl();
