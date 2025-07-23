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

import { int32 } from "@koalaui/common"
import { ArkUIGeneratedNativeModule } from "#components"
import { NodeAttach, remember, rememberMutableState } from "@koalaui/runtime"
import { InteropNativeModule } from "@koalaui/interop"
import { ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodPeer, CommonMethod, ResourceColor } from "../generated"
import { BuilderLambda } from "@koalaui/builderLambda"
import { AttributeModifier } from "./component/base"
import { AttributeUpdater } from "./AttributeUpdater"
import { TEST_LOG_NUMBER } from "../Application"
import { ComponentBase } from "../ComponentBase"
import { PeerNode } from "../PeerNode"

export class TestComponentPeer extends ArkCommonMethodPeer {
    protected constructor(id: int32) {
        super(ArkUIGeneratedNativeModule._Stack_construct(0, 0), id)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): TestComponentPeer {
        const id = PeerNode.nextId()
        const peer  = new TestComponentPeer(id)
        component?.setPeer(peer)
        return peer
    }
    setTestComponentOptionsAttribute(option?: TestComponentOptions): void {
        if (option != undefined) {
            if (option.id != undefined) {
                this.setId(option.id!.toInt())
            }
            if (option.log != undefined) {
                this.logAttribute(option.log as string)
            }
            if (option.onChange != undefined) {
                this.onChangeAttribute(option.onChange as () => void)
            }
        }
    }
    onChangeCallback: (() => void) | undefined = undefined
    onChangeAttribute(callback: () => void): void {
        this.onChangeCallback = callback
    }
    logAttribute(message: string): void {
        if (true)
            InteropNativeModule._AppendGroupedLog(TEST_LOG_NUMBER, message + "\n")
        else
            console.log(message)
    }
}

export interface TestComponentOptions {
    id?: number;
    log?: string;
    onChange?: () => void;
}
export type TestComponentInterface = (options?: TestComponentOptions) => TestComponentAttribute;
export interface TestComponentAttribute extends CommonMethod {
    onChange(callback: () => void): this
    log(message: string): this
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
    apply(target: TestComponentAttribute): void {
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
export class TestComponentComponent extends ArkCommonMethodComponent implements TestComponentAttribute {
    getPeer(): TestComponentPeer {
        return (this.peer as TestComponentPeer)
    }
    @memo
    public setTestComponentOptions(options?: TestComponentOptions): this {
        this.getPeer()?.setTestComponentOptionsAttribute(options)
        return this
    }
    public onChange(callback: () => void): this {
        this.getPeer()?.onChangeAttribute(callback)
        return this
    }
    public log(message: string): this {
        this.getPeer()?.logAttribute(message)
        return this
    }
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
@BuilderLambda("TestComponentImpl")
export function TestComponent(
  options?: TestComponentOptions | undefined,
  @memo
  content_?: (() => void) | undefined
): TestComponentAttribute {
    throw new Error('stub')
}

@memo
function withTestComponentStyle(receiver: TestComponentAttribute, modifier: AttributeModifier<TestComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTestComponentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}

@memo
export function TestComponentImpl(
  @memo
  style: ((attributes: TestComponentAttribute) => void) | undefined,
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
