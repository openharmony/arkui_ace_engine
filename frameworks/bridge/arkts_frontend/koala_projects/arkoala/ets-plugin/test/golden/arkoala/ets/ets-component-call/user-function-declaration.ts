import { ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, LocalStorage } from "@koalaui/arkoala-arkui";
/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
export function Foo() {
    return "string";
}
export function Text() {
    return "string";
}
/** @memo:stable */
export class ArkStructComponent extends ArkStructBase<ArkStructComponent, StructOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StructOptions): void {
        this.__backing_param = initializers?.param ?? (0);
    }
    private __backing_param?: number;
    private get param(): number {
        return this.__backing_param as number;
    }
    private set param(value: number) {
        this.__backing_param = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StructOptions) { }
}
/** @memo:stable */
export class ArkStructWithContentComponent extends ArkStructBase<ArkStructWithContentComponent, StructWithContentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StructWithContentOptions): void {
        this.__backing_param = initializers?.param ?? (0);
        if (initializers?.content) {
            this.__backing_content = initializers?.content;
        }
        if (this.__backing_content === undefined && content !== undefined)
            this.__backing_content = content;
    }
    private __backing_param?: number;
    private get param(): number {
        return this.__backing_param as number;
    }
    private set param(value: number) {
        this.__backing_param = value;
    }
    /** @memo */
    private __backing_content?: () => void;
    /** @memo */
    private get content(): () => void {
        return this.__backing_content!;
    }
    private set content(/**/
    /** @memo */
    value: () => void) {
        this.__backing_content = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StructWithContentOptions) {
        this.content();
    }
}
/** @memo */
export function Struct(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StructOptions): void {
    const updatedInitializers: StructOptions = {
        param: initializers?.param
    };
    ArkStructComponent._instantiate(style, () => new ArkStructComponent, content, updatedInitializers);
}
/** @memo */
export function StructWithContent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StructWithContentOptions): void {
    const updatedInitializers: StructWithContentOptions = {
        param: initializers?.param,
        content: initializers?.content
    };
    ArkStructWithContentComponent._instantiate(style, () => new ArkStructWithContentComponent, content, updatedInitializers);
}
export interface StructOptions {
    param?: number;
}
export interface StructWithContentOptions {
    param?: number;
    /** @memo */
    content?: () => void;
}
