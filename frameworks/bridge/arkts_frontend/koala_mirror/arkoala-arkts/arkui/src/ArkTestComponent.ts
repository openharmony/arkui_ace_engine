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

import { NodeAttach, remember, rememberMutableState  } from "@koalaui/runtime"
import { ArkTestComponentPeer } from "./peers/ArkTestComponentPeer"
import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./generated/common"
import { AttributeModifier, AttributeUpdater } from "./handwritten"
import { nLog } from "./NativeLog"

export interface TestComponentOptions {
    id?: number;
    log?: string;
    onChange?: () => void;
}
export type TestComponentInterface = (options?: TestComponentOptions) => UITestComponentAttribute;
export interface TestComponentAttribute extends CommonMethod {
    onChange(callback: () => void): this
    log(message: string): this
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITestComponentAttribute extends UICommonMethod {
    /** @memo */
    onChange(callback: () => void): this
    /** @memo */
    log(message: string): this
    /** @memo */
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTestComponentStyle extends ArkCommonMethodStyle implements TestComponentAttribute {
    log_value?: string | undefined = undefined
    onChange_value?: () => void = undefined
    onChange(callback: () => void): this {
        this.onChange_value = callback
        return this
    }
    log(message: string): this {
        this.log_value = message
        return this
    }
    public attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("ArkTestComponentsStyle.attributeModifier not implemented")
    }
    /** @memo */
    apply(target: UITestComponentAttribute): void {
        super.apply(target)
        if (this.backgroundColor_value !== undefined)
            target.backgroundColor(this.backgroundColor_value!)
        if (this.log_value !== undefined)
            target.log(this.log_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
    }
}

/** @memo:stable */
export class ArkTestComponentComponent extends ArkCommonMethodComponent implements UITestComponentAttribute {
    getPeer(): ArkTestComponentPeer {
        return (this.peer as ArkTestComponentPeer)
    }
    /** @memo */
    setTestComponentOptions(options?: TestComponentOptions): this {
        const options_casted = options as (TestComponentOptions | undefined)
        this.getPeer()?.setTestComponentOptionsAttribute(options_casted)
        return this
    }
    /** @memo */
    onChange(callback: () => void): this {
        this.getPeer()?.onChangeAttribute(callback)
        return this
    }
    /** @memo */
    log(message: string): this {
        this.getPeer()?.logAttribute(message)
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
function withTestComponentStyle(receiver: UITestComponentAttribute, modifier: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTestComponentStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}

/** @memo */
export function ArkTestComponent(
  /** @memo */
  style: ((attributes: UITestComponentAttribute) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: TestComponentOptions | undefined
) {
    const receiver = remember<ArkTestComponentComponent>((): ArkTestComponentComponent => {
        return new ArkTestComponentComponent()
    })
    NodeAttach<ArkTestComponentPeer>((): ArkTestComponentPeer => ArkTestComponentPeer.create(receiver), (_: ArkTestComponentPeer): void => {
        receiver.setTestComponentOptions(options)
        style?.(receiver)
        withTestComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
