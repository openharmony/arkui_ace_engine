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
class ArkPanelComponent extends ArkComponent implements PanelAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  mode(value: PanelMode): this {
    modifierWithKey(this._modifiersWithKeys, PanelModeModifier.identity, PanelModeModifier, value);
    return this;
  }
  type(value: PanelType): this {
    modifierWithKey(this._modifiersWithKeys, PanelTypeModifier.identity, PanelTypeModifier, value);
    return this;
  }
  dragBar(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, DragBarModifier.identity, DragBarModifier, value);
    return this;
  }
  customHeight(value: any): this {
    modifierWithKey(this._modifiersWithKeys, PanelCustomHeightModifier.identity, PanelCustomHeightModifier, value);
    return this;
  }
  fullHeight(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, PanelFullHeightModifier.identity, PanelFullHeightModifier, value);
    return this;
  }
  halfHeight(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, PanelHalfHeightModifier.identity, PanelHalfHeightModifier, value);
    return this;
  }
  miniHeight(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, PanelMiniHeightModifier.identity, PanelMiniHeightModifier, value);
    return this;
  }
  show(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ShowModifier.identity, ShowModifier, value);
    return this;
  }
  backgroundMask(color: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PanelBackgroundMaskModifier.identity, PanelBackgroundMaskModifier, color);
    return this;
  }
  showCloseIcon(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ShowCloseIconModifier.identity, ShowCloseIconModifier, value);
    return this;
  }
  onChange(event: (width: number, height: number, mode: PanelMode) => void): this {
    throw new Error('Method not implemented.');
  }
  onHeightChange(callback: (value: number) => void): this {
    throw new Error('Method not implemented.');
  }
}

class PanelBackgroundMaskModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('panelBackgroundMask');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelBackgroundMask(node);
    } else {
      getUINativeModule().panel.setPanelBackgroundMask(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelModeModifier extends ModifierWithKey<PanelMode> {
  constructor(value: PanelMode) {
    super(value);
  }
  static identity: Symbol = Symbol('panelMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelMode(node);
    } else {
      getUINativeModule().panel.setPanelMode(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelTypeModifier extends ModifierWithKey<PanelType> {
  constructor(value: PanelType) {
    super(value);
  }
  static identity: Symbol = Symbol('panelType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelType(node);
    } else {
      getUINativeModule().panel.setPanelType(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelCustomHeightModifier extends ModifierWithKey<Dimension | PanelHeight> {
  constructor(value: Dimension | PanelHeight) {
    super(value);
  }
  static identity: Symbol = Symbol('panelCustomHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelCustomHeight(node);
    } else {
      getUINativeModule().panel.setPanelCustomHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelFullHeightModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('panelFullHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelFullHeight(node);
    } else {
      getUINativeModule().panel.setPanelFullHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelHalfHeightModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('panelHalfHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelHalfHeight(node);
    } else {
      getUINativeModule().panel.setPanelHalfHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PanelMiniHeightModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('panelMiniHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().panel.resetPanelMiniHeight(node);
    } else {
      getUINativeModule().panel.setPanelMiniHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ShowCloseIconModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('showCloseIcon');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().panel.resetShowCloseIcon(node);
    } else {
      getUINativeModule().panel.setShowCloseIcon(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class DragBarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('dragBar');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().panel.resetDragBar(node);
    } else {
      getUINativeModule().panel.setDragBar(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ShowModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('show');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().panel.resetShow(node);
    } else {
      getUINativeModule().panel.setShow(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Panel.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkPanelComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.PanelModifier(nativePtr, classType);
  });
};
