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

import { NodeAttach, remember  } from "@koalaui/runtime"
import { ArkCommonMethodComponent } from "./generated/ArkCommon"
import { ArkTestComponentPeer } from "./peers/ArkTestComponentPeer"
import { CommonMethod } from "./generated/ArkCommonInterfaces"
import { InteropNativeModule } from "@koalaui/interop"

/** @memo:stable */
export class ArkTestComponentComponent extends ArkCommonMethodComponent {
    getPeer(): ArkTestComponentPeer {
        return (this.peer as ArkTestComponentPeer)
    }
    /** @memo */
    setTestComponentOptions(options?: TestComponentOptions): this {
        if (this.checkPriority("setColumnOptions")) {
            const options_casted = options as (TestComponentOptions | undefined)
            this.getPeer()?.setTestComponentOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    onChange(value: Function0<void>): this {
        if (this.checkPriority("onChange")) {
            this.getPeer()?.onChangeAttribute(value)
            return this
        }
        return this
    }
    /** @memo */
    log(message: string): this {
        if (this.checkPriority("log")) {
            this.getPeer()?.logAttribute(message)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkTestComponent(
  /** @memo */
  style: ((attributes: ArkTestComponentComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: TestComponentOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkTestComponentComponent()
    })
    NodeAttach<ArkTestComponentPeer>((): ArkTestComponentPeer => ArkTestComponentPeer.create(receiver), (_: ArkTestComponentPeer) => {
            receiver.setTestComponentOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export interface TestComponentOptions {
    id?: number;
}
export type TestComponentInterface = (options?: TestComponentOptions) => TestComponentAttribute;
export interface TestComponentAttribute extends CommonMethod<TestComponentAttribute> {
    onChange?: Function0<void>;
    log?: string
}
