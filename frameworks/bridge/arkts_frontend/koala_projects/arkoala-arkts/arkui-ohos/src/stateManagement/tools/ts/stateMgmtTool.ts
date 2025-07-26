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
export class StateMgmtTool {
    static isIObservedObject(value: Object): boolean {
        return true;
    }
    static isIStateDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIPropDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isILinkDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIObjectLinkDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIProvideDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIConsumeDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isILocalStorageLinkDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIStorageLinkDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isIStoragePropRefDecoratedVariable(value: NullableObject): boolean {
        return true;
    }
    static isDecoratedV1VariableBase(value: NullableObject): boolean {
        return true;
    }
    static isISubscribedWatches<T>(value: T): boolean {
        return true;
    }
    static isIWatchSubscriberRegister(value: NullableObject): boolean {
        return true;
    }
    static isInterfaceProxyHandler(value: NullableObject): boolean {
        return true;
    }
    static tryGetHandler(value: NullableObject): NullableObject {
        return value;
    }
    static createProxy<T extends Object>(value: T): T {
        return value;
    }
    static isObjectLiteral<T extends Object>(value: T): boolean {
        return true;
    }
}
