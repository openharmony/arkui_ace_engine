import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
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

import { NodeAttach, remember, rememberMutableState } from "@koalaui/runtime"
import { TestComponentPeer } from "./TestComponentPeer"
import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, ResourceColor, UICommonMethod } from "../generated"
import { BuilderLambda } from "@koalaui/builderLambda"
import { AttributeModifier } from "./base"
import { AttributeUpdater } from "./AttributeUpdater"

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
    @memo
    onChange(callback: () => void): this
    log(message: string): this
    @memo
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}

export class ArkTestComponentStyle extends ArkCommonMethodStyle implements TestComponentAttribute {
    log_value?: string | undefined = undefined
    onChange_value?: () => void = undefined
    public backgroundColor(value: ResourceColor): this {
        this.backgroundColor_value = value
        return this
    }
    onChange(callback: () => void): this {
        this.onChange_value = callback
        return this
    }
    log(message: string): this {
        this.log_value = message
        return this
    }
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    @memo
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

@memo_stable
export class TestComponentComponent extends ArkCommonMethodComponent implements UITestComponentAttribute {
    getPeer(): TestComponentPeer {
        return (this.peer as TestComponentPeer)
    }
    @memo
    public setTestComponentOptions(options?: TestComponentOptions): this {
        this.getPeer()?.setTestComponentOptionsAttribute(options)
        return this
    }
    @memo
    public onChange(callback: () => void): this {
        this.getPeer()?.onChangeAttribute(callback)
        return this
    }
    public log(message: string): this {
        this.getPeer()?.logAttribute(message)
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
@BuilderLambda("TestComponent")
export function TestComponent(
  options?: TestComponentOptions | undefined,
  @memo
  content_?: (() => void) | undefined
): TestComponentAttribute {
    throw new Error('stub')
}

@memo
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

@memo
export function TestComponent(
  @memo
  style: ((attributes: UITestComponentAttribute) => void) | undefined,
  options?: TestComponentOptions | undefined,
  @memo
  content_?: (() => void) | undefined
): void {
    const receiver = remember<TestComponentComponent>((): TestComponentComponent => {
        return new TestComponentComponent()
    })
    NodeAttach<TestComponentPeer>((): TestComponentPeer => TestComponentPeer.create(receiver), (_: TestComponentPeer): void => {
        receiver.setTestComponentOptions(options)
        style?.(receiver)
        withTestComponentStyle(receiver, receiver._modifier)
        content_?.()
    })
}
