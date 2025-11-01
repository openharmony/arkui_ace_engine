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
    IPropRefDecoratedVariable
} from '../../decorator';
import { NullableObject } from '../../base/types';
import { InterfaceProxyHandler } from './observeInterfaceProxy';
import { ISubscribedWatches, IWatchSubscriberRegister } from '../../decorator';
import { DecoratedV1VariableBase } from '../../decoratorImpl/decoratorBase';
import { StateManager, GlobalStateManager } from '@koalaui/runtime';
import { UIContextUtil } from '../../../base/UIContextUtil';
import { UIContextImpl } from '../../../base/UIContextImpl';
import { StateMgmtConsole } from '../stateMgmtDFX';
import { int32 } from '@koalaui/common';
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
    static isPropRefDecoratedVariable(value: NullableObject): boolean {
        return value instanceof IPropRefDecoratedVariable;
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
    static isIWatchSubscriberRegister<T>(value: T): boolean {
        return value instanceof IWatchSubscriberRegister;
    }
    static isInterfaceProxyHandler(value: NullableObject): boolean {
        return value instanceof InterfaceProxyHandler;
    }
    static tryGetHandler(value: Object): NullableObject {
        const objType = Type.of(value);
        return objType instanceof ClassType && (objType as ClassType).getName().startsWith('$Proxy')
            ? ((value as reflect.Proxy).getHandler() as NullableObject) // a very slow call so need to judge proxy first
            : undefined;
    }
    static tryGetTarget(value: Object): NullableObject {
        const handler = StateMgmtTool.tryGetHandler(value);
        if (handler && handler instanceof InterfaceProxyHandler) {
            return (handler as InterfaceProxyHandler).target;
        }
        return undefined;
    }
    static createProxy<T extends Object>(value: T, allowDeep: boolean = false, isAPI: boolean = false): T {
        const ifaces: FixedArray<Class> = Class.of(value).getInterfaces();
        const linker = Class.current().getLinker();
        return reflect.Proxy.create(linker, ifaces, new InterfaceProxyHandler(value, allowDeep, isAPI)) as T;
    }
    static isObjectLiteral<T extends Object>(value: T): boolean {
        return Reflect.isLiteralInitializedInterface(value);
    }
    static getGlobalStateManager(): StateManager {
        return GlobalStateManager.instance;
    }
    static tryGetCurrentGlobalStateManager(): StateManager {
        let context: UIContextImpl | undefined = undefined;
        try {
            context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        } catch (e) {
            // for scenario where UIContext is not ready.
            StateMgmtConsole.log('Get current UIContext fail, will directly use GlobalStateManager');
        }
        return context && context.stateMgr ? context.stateMgr! : GlobalStateManager.instance;
    }
}
