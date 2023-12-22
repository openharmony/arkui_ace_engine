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
class ArkQRCodeComponent extends ArkComponent implements QRCodeAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, QRColorModifier.identity, QRColorModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, QRBackgroundColorModifier.identity, QRBackgroundColorModifier, value);
    return this;
  }
  contentOpacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, QRContentOpacityModifier.identity, QRContentOpacityModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class QRColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('color');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().qrcode.resetQRColor(node);
      } else {
          GetUINativeModule().qrcode.setQRColor(node, this.value);
      }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class QRBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('qrBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().qrcode.resetQRBackgroundColor(node);
      } else {
          GetUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
      }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class QRContentOpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('qrContentOpacity');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().qrcode.resetContentOpacity(node);
      } else {
          GetUINativeModule().qrcode.setContentOpacity(node, this.value);
      }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.QRCode.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkQRCodeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
