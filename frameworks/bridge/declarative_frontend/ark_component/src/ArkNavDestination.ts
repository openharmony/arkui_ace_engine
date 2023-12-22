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

class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  title(value: any): this {
    throw new Error('Method not implemented.');
  }
  hideTitleBar(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, value);
    return this;
  }
  onShown(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onHidden(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBackPressed(callback: () => boolean): this {
    throw new Error('Method not implemented.');
  }
}

class HideTitleBarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navDestination.resetHideTitleBar(node);
    } else {
      GetUINativeModule().navDestination.setHideTitleBar(node, this.value!);
    }
  }
}
//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavDestinationComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
