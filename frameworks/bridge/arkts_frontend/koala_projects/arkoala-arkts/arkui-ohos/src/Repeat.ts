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

import { int32, hashCodeFromString, KoalaCallsiteKey } from "@koalaui/common"
import { __context, __id, contextNode, DataNode, memoEntry2, remember, rememberMutableState, scheduleCallback, RepeatByArray } from "@koalaui/runtime"
import { RepeatItem, UIRepeatAttribute, RepeatArray, RepeatItemBuilder, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions } from "./component"
import { InteropNativeModule } from "@koalaui/interop"
import { PeerNode, PeerNodeType } from "./PeerNode"

export class RepeatDataNode<T> extends DataNode<T> {}

class RepeatItemImpl<T> implements RepeatItem<T> {
    item: T;
    index?: number;
    constructor(initialItem: T, initialIndex: number) {
        this.item = initialItem;
        this.index = initialIndex;
    }
    public updateItem(newItem: T): void {
        this.item = newItem;
    }
    public updateIndex(newIndex: number): void {
        this.index = newIndex;
    }
}

export class UIRepeatAttributeImpl<T> implements UIRepeatAttribute<T> {
    // /** @memo */
    // private config_: RepeatConfig<T> = {};
    private impl_?: RepeatImpl<T> | RepeatVirtualScrollImpl<T>;
    private isVirtualScroll_: boolean = false;

    constructor(arr: RepeatArray<T>) {
    }

    /** @memo */
    setRepeatOptions(): void {
        // InteropNativeModule._NativeLog('setRepeatOptions called.')
    }
    /** @memo */
    each(
        /** @memo */
        itemGenerator: (repeatItem: RepeatItem<T>) => void
    ): UIRepeatAttributeImpl<T> {
        // InteropNativeModule._NativeLog('each called.')
        if (itemGenerator === undefined || typeof itemGenerator !== 'function') {
            throw new Error('item generator function missing. Application error!');
        }
        return this;
    }
    /** @memo */
    key(keyGenerator: (item: T, index?: number) => string): UIRepeatAttributeImpl<T> {
        // InteropNativeModule._NativeLog('key called.')
        if (keyGenerator === undefined || typeof keyGenerator !== 'function') {
            throw new Error('key generator function missing. Application error!');
        }
        return this;
    }
    /** @memo */
    virtualScroll(virtualScrollOptions?: VirtualScrollOptions): UIRepeatAttributeImpl<T> {
        // InteropNativeModule._NativeLog('virtualScroll called.')
        this.isVirtualScroll_ = true;
        return this;
    }
    /** @memo */
    template(type: string,
        /** @memo */
        itemBuilder: (repeatItem: RepeatItem<T>) => void,
        templateOptions?: TemplateOptions
    ): UIRepeatAttributeImpl<T> {
        // InteropNativeModule._NativeLog('template called.')
        if (itemBuilder === undefined || typeof itemBuilder !== 'function') {
            throw new Error('template generator function missing. Application error!');
        }
        return this;
    }
    /** @memo */
    templateId(typedFunc: TemplateTypedFunc<T>): UIRepeatAttributeImpl<T> {
        // InteropNativeModule._NativeLog('templateId called.')
        if (typedFunc === undefined || typeof typedFunc !== 'function') {
            throw new Error('templateId generator function missing. Application error!');
        }
        return this;
    }
    /** @memo */
    render(): void {
        // InteropNativeModule._NativeLog('render called.')
        this.impl_ = this.isVirtualScroll_ ? new RepeatVirtualScrollImpl<T>() : new RepeatImpl<T>();
        // this.impl_.render(this.config_);
    }
}

class RepeatImpl<T> {}

class RepeatVirtualScrollImpl<T> {}