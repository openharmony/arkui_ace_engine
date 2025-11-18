/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { MutableState, GlobalStateManager } from '@koalaui/runtime'
import { CommonAttribute, AttributeModifier } from  './component/common'
import { CommonMethodModifier } from './CommonMethodModifier'

export class CommonModifier extends CommonMethodModifier implements CommonAttribute,AttributeModifier<CommonAttribute> {
    applyNormalAttribute(instance: CommonAttribute): void {}
    applyPressedAttribute(instance: CommonAttribute): void {}
    applyFocusedAttribute(instance: CommonAttribute): void {}
    applyDisabledAttribute(instance: CommonAttribute): void {}
    applySelectedAttribute(instance: CommonAttribute): void {}
}

export class ModifierStateManager {
    static INSTANCE: ModifierStateManager = new ModifierStateManager();
    private constructor() { }
    private _flag: boolean = false;
    get isEnable(): boolean {
        return this._flag;
    }
    scope(f: () => void): void {
        this.disable();
        try {
            f();
        } finally {
            this.enable();
        }
    }
    private enable(): void {
        this._flag = true;
    }
    private disable(): void {
        this._flag = false;
    }
}

export interface IModifierState {
    addRef(): void;
    fireChange(): void;
}

export class ModifierState implements IModifierState {
    public _state: MutableState<int> | undefined = undefined;
    constructor() {
        this._state = GlobalStateManager.instance.mutableState<int>(0, true);
    }
    get state(): MutableState<int> {
        return this._state!;
    }
    addRef(): void {
        this._state!.value;
    }
    fireChange(): void {
        if (!ModifierStateManager.INSTANCE.isEnable) {
            this._state!.value;
            return;
        }
        this._state!.value = this._state!.value % 100 + 1;
    }
}
