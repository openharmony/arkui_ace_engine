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

import { PersistentStorageMocked } from './ani_storage_mock'

export class IncrementalNode {}

/** This interface represents an object that may depend on some other dependencies. */
export interface Dependent {
    /** @return `true` if this object has at least one dependency */
    hasDependencies(): boolean
    /** @return a string representation of this object, useful for debugging */
    toString(): string
}

export class MutableState<T> {
    static nextId: int = 1;
    public backing_value_: T;
    public dependencies: DepsMocked = new DepsMocked();
    public id: int;

    constructor(value: T) {
        this.backing_value_ = value;
        this.id = MutableState.nextId++;
    }

    get value(): T {
        this.dependencies.empty = false;
        return this.backing_value_;
    }

    set value(value: T) {
        this.backing_value_ = value;
    }

    getDependentInfo(): Set<IncrementalNode> | undefined {
        return undefined;
    }

    dispose(): void {}
}


export class MockScope {
    public unchanged: boolean = false;
    public cached: Object = new Object();
    recache(value: Object): Object {
        this.cached = value;
        return value;
    }
}

export class StateManager {
    public currentScope: MockedElement | undefined = undefined;
    public scopeEx<T>(id: int, flags: int, a?: Object, b?: Object, c?: Object, d?: boolean): MockScope {
        return new MockScope();
    }
    public mutableState<T>(value: T, flag?: boolean): MutableState<T> {
        return new StateImpl<T>(value);
    }
}

export class StateManagerImpl extends StateManager {
    public current: MockedElement = new MockedElement();
    constructor() {
    }
}

export class GlobalStateManager {
    public static instance = new StateManagerImpl();
}

class DepsMocked {
    public empty: boolean = true;
}

class MockedElement {
    public id: int;
}

export class StateImpl<T> extends MutableState<T> implements Dependent {
    constructor(value: T) {
        super(value);
    }

    // Dependent methods
    hasDependencies(): boolean {
        return false;
    }

    toString(): string {
        return '';
    }
}

export let MockGlobalStateManagerInstance = new StateManager();

export class ArkUIAniModule {
    private static backend_ = new PersistentStorageMocked();

    public static _CustomNode_RequestFrame(): void {}

    public static _Env_GetAccessibilityEnabled(): boolean { return false; }
    public static _Env_GetColorMode(): int { return 0; }
    public static _Env_GetFontScale(): number { return 1.0; }
    public static _Env_GetFontWeightScale(): number { return 1.0; }
    public static _Env_GetLayoutDirection(): int { return 0; }
    public static _Env_GetLanguageCode(): string { return 'en'; }

    public static _PersistentStorage_Get(key: string, areaMode?: Int): string | undefined {
      return ArkUIAniModule.backend_.get(key, areaMode);
    };

    public static _PersistentStorage_Set(key: string, val: string, areaMode?: Int) : void {
      ArkUIAniModule.backend_.set(key, val, areaMode);
    };
    public static _PersistentStorage_Has(key: string, areaMode?: Int): boolean {
      return ArkUIAniModule.backend_.has(key, areaMode);

    };
    public static _PersistentStorage_Clear(): void {
      ArkUIAniModule.backend_.clear();
    };
    public static _PersistentStorage_Delete(key: string, areaMode?: Int): void {
      ArkUIAniModule.backend_.delete(key, areaMode);
    };
}

export let StateMgmtConsole = console

export function __context(): StateManager {
    return GlobalStateManager.instance;
}

export function __id(): int {
    return 0;
}
