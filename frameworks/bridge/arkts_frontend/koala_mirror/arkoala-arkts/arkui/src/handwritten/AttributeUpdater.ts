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

import { InteropNativeModule } from "@koalaui/interop";
import { AttributeModifier } from "./base";

export type Initializer<T> = () => T;
/** @memo:stable */
export class AttributeUpdater<T, C = Initializer<T>> implements AttributeModifier<T> {
    isUpdater: boolean = true
    /**@memo*/
    applyPressedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyPressedAttribute")
    }
    /**@memo*/
    applyFocusedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyFocusedAttribute")
    }
    /**@memo*/
    applyDisabledAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyDisabledAttribute")
    }
    /**@memo*/
    applySelectedAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applySelectedAttribute")
    }
    /**@memo*/
    applyNormalAttribute(instance: T): void {
        InteropNativeModule._NativeLog("AttributeUpdater.applyNormalAttribute")
    }
    /** @memo */
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
