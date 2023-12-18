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

/// <reference path='./import.ts' />
class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  prevLabel(value: string): this {
    throw new Error('Method not implemented.');
  }
  nextLabel(value: string): this {
    modifier(this._modifiers, NextLabelModifier, value);
    return this;
  }
  status(value?: ItemState | undefined): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class NextLabelModifier extends Modifier<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('NextLabel');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().stepperItem.resetNextLabel(node);
    } else {
      GetUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStepperItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
