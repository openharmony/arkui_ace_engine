/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


// HANDWRITTEN, DO NOT REGENERATE

import { __context, __id } from '@koalaui/runtime';
import { RepeatImpl } from '../handwritten/RepeatImpl';

export interface RepeatItem<T> {
    readonly item: T;
    readonly index: number;
}

export type RepeatArray<T> = Array<T> | ReadonlyArray<T> | Readonly<Array<T>>;
export type RepeatItemBuilder<T> =
    /** @memo */
    (repeatItem: RepeatItem<T>) => void;
export type TemplateTypedFunc<T> = (item: T, index: number) => string;

export interface VirtualScrollOptions {
    totalCount?: number;
    reusable?: boolean;
}

export interface TemplateOptions {
    cachedCount?: number;
}

export interface UIRepeatAttribute<T> {
    /** @memo */
    each(itemGenerator: RepeatItemBuilder<T>): UIRepeatAttribute<T>;
    /** @memo */
    key(keyGenerator: (item: T, index: number) => string): UIRepeatAttribute<T>;
    /** @memo */
    virtualScroll(options?: VirtualScrollOptions): UIRepeatAttribute<T>;
    /** @memo */
    template(
        type: string, itemBuilder: RepeatItemBuilder<T>, templateOptions?: TemplateOptions): UIRepeatAttribute<T>;
    /** @memo */
    templateId(typedFunc: TemplateTypedFunc<T>): UIRepeatAttribute<T>;
    /** @memo */
    render(arr: RepeatArray<T>): void;
}

/** @memo */
export function Repeat<T>(
    /** @memo */
    style: ((attributes: UIRepeatAttribute<T>) => void) | undefined,
    arr: RepeatArray<T>
): void {
    RepeatImpl<T>(style, arr);
}