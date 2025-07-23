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

import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
import { InteropNativeModule } from "@koalaui/interop";
import { AttributeModifier } from "./component/base";

export type Initializer<T> = () => T;
export class AttributeUpdater<T, C = Initializer<T>> implements AttributeModifier<T> {
    isUpdater(): boolean { return true }
    applyPressedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyPressedAttribute")
    }
    applyFocusedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyFocusedAttribute")
    }
    applyDisabledAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyDisabledAttribute")
    }
    applySelectedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applySelectedAttribute")
    }
    applyNormalAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyNormalAttribute")
    }
    initializeModifier(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.initializeModifier")
    }
    get attribute(): T | undefined {
        InteropNativeModule._NativeLog("AttributeUpdater.attribute")
        return undefined
    }
    updateConstructorParams?: C
    onComponentChanged(component: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.onComponentChanged")
    }
}
