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

import { ArkStructBase } from "../ArkStructBase"
import { ArkCommonMethodComponent } from "../generated/ArkCommon"
import { UIContext } from "@ohos.arkui.UIContext"

class CustomDelegate<T extends CustomComponent<T, T_Options>, T_Options> extends
    ArkStructBase<CustomDelegate<T, T_Options>, T_Options> {
    private instance: CustomComponent<T, T_Options>;

    constructor(instance: CustomComponent<T, T_Options>) {
        super();
        this.instance = instance;
    }

    aboutToAppear(): void {
        this.instance.aboutToAppear();
    }
    aboutToDisappear(): void {
        this.instance.aboutToDisappear();
    }

    onDidBuild(): void {
        this.instance.onDidBuild();
    }
    onPageShow(): void {
        this.instance.onPageShow();
    }

    onPageHide(): void {
        this.instance.onPageHide();
    }

    onBackPress(): boolean {
        return this.instance.onBackPress();
    }

    aboutToRecycle(): void {
        return this.instance.aboutToRecycle()
    }

    aboutToReuse(params: Record<string, Object>): void {
        this.instance.aboutToReuse(params)
    }
    __toRecord(param: Object): Record<string, Object> {
        return this.instance.__toRecord(param)
    }

    /** @memo */
    __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        this.instance._build(undefined, content, initializers);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        this.instance.__initializeStruct(initializers, content);
    }

    /** @memo */
    protected __updateStruct(
        initializers?: T_Options
    ): void {
        this.instance.__updateStruct(initializers);
    }
}

export abstract class CustomComponent<T extends CustomComponent<T, T_Options>, T_Options> {
    /** @memo */
    static _instantiateImpl<S extends CustomComponent<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: S_Options,
        /** @memo */
        content?: () => void,
        reuseKey?: string
    ): void {
        CustomDelegate._instantiate(undefined, () => new CustomDelegate<S, S_Options>(factory()), undefined, initializers, reuseKey);
    }

    __initializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {}

    __updateStruct(
        initializers?: T_Options
    ): void {}

    // Life cycle for custom component
    aboutToAppear(): void {}
    aboutToDisappear(): void {}
    onDidBuild(): void {}

    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false; }
    getUIContext(): UIContext { return new UIContext(100000); }

    aboutToReuse(param: Record<string, Object>): void {}
    aboutToRecycle(): void {}
    __toRecord(param: Object): Record<string, Object> { return {} }

    build(): void {};

    /** @memo */
    _build(
        /** @memo */
        style: ((instance: T) => T) | undefined,
        /** @memo */
        content: (()=> void) | undefined,
        initializers: T_Options | undefined
    ): void {}
}