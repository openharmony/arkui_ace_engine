/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
import { IObservedObject } from '../../decorator';
import {
    IStateDecoratedVariable,
    IPropDecoratedVariable,
    ILinkDecoratedVariable,
    IObjectLinkDecoratedVariable,
    IProvideDecoratedVariable,
    IConsumeDecoratedVariable,
    IStorageLinkDecoratedVariable,
    ILocalStorageLinkDecoratedVariable,
    IStoragePropRefDecoratedVariable,
} from '../../decorator';
import { NullableObject } from '../../base/types';
import { InterfaceProxyHandler } from './observeInterfaceProxy';
import { ISubscribedWatches } from '../../decorator';
import { DecoratedV1VariableBase } from '../../decoratorImpl/decoratorBase';
import { StateManager, GlobalStateManager } from '@koalaui/runtime';
import { StateMgmtConsole } from '../stateMgmtDFX';
export class StateMgmtTool {
    static isIObservedObject(value: NullableObject): boolean {
        return value instanceof IObservedObject;
    }
    static isIStateDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IStateDecoratedVariable;
    }
    static isIPropDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IPropDecoratedVariable;
    }
    static isILinkDecoratedVariable(value: NullableObject): boolean {
        return value instanceof ILinkDecoratedVariable;
    }
    static isIObjectLinkDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IObjectLinkDecoratedVariable;
    }
    static isIProvideDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IProvideDecoratedVariable;
    }
    static isIConsumeDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IConsumeDecoratedVariable;
    }
    static isILocalStorageLinkDecoratedVariable(value: NullableObject): boolean {
        return value instanceof ILocalStorageLinkDecoratedVariable;
    }
    static isIStorageLinkDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IStorageLinkDecoratedVariable;
    }
    static isIStoragePropRefDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IStoragePropRefDecoratedVariable;
    }
    static isDecoratedV1VariableBase(value: NullableObject): boolean {
        return value instanceof DecoratedV1VariableBase;
    }
    static isISubscribedWatches(value: NullableObject): boolean {
        return value instanceof ISubscribedWatches;
    }
    static isInterfaceProxyHandler(value: NullableObject): boolean {
        return value instanceof InterfaceProxyHandler;
    }
    static tryGetHandler(value: Object): NullableObject {
        return proxy.Proxy.tryGetHandler(value) as NullableObject;
    }
    static createProxy<T extends Object>(value: T): T {
        return proxy.Proxy.create(value, new InterfaceProxyHandler<T>()) as T;
    }
    static isObjectLiteral<T extends Object>(value: T): boolean {
        return Reflect.isLiteralInitializedInterface(value);
    }
    static getGlobalStateManager(): StateManager {
        return GlobalStateManager.instance;
    }
}
