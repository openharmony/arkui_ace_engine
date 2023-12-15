/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

/// <reference path="./import.ts" />
class ArkCounterComponent extends ArkComponent implements CounterAttribute {
    constructor(nativePtr: KNode) {
      super(nativePtr);
    }
    onInc(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    onDec(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    enableDec(value: boolean): this {
        if (isBoolean(value)) {
            modifier(this._modifiers, EnableDecModifier, value);
        } else {
            modifier(this._modifiers, EnableDecModifier, undefined);
        }
        return this;
    }
    enableInc(value: boolean): this {
        if (isBoolean(value)) {
            modifier(this._modifiers, EnableIncModifier, value);
        } else {
            modifier(this._modifiers, EnableIncModifier, undefined);
        }
        return this;
    }
}
class EnableIncModifier extends Modifier<boolean> {
    constructor(value: boolean) {
      super(value);
    }
    static identity = Symbol("enableInc");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().counter.resetEnableInc(node);
        }
        else {
            GetUINativeModule().counter.setEnableInc(node, this.value);
        }
    }
}
class EnableDecModifier extends Modifier<boolean> {
    constructor(value: boolean) {
      super(value);
    }
    static identity = Symbol("enableDec");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().counter.resetEnableDec(node);
        }
        else {
            GetUINativeModule().counter.setEnableDec(node, this.value);
        }
    }
}

// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCounterComponent(nativeNode);
    });
    applyUIAttributes(modifier, nativeNode, component);
    component.applyModifierPatch();
}
