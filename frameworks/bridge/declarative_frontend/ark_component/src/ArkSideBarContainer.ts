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
class SideBarContainerPositionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetSideBarPosition(node);
    } else {
      getUINativeModule().sideBarContainer.setSideBarPosition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerAutoHideModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerautoHide');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetAutoHide(node);
    } else {
      getUINativeModule().sideBarContainer.setAutoHide(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerShowSideBarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerShowSideBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetShowSideBar(node);
    } else {
      getUINativeModule().sideBarContainer.setShowSideBar(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMaxSideBarWidthModifier extends ModifierWithKey<number | Length> {
  constructor(value: number | Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerMaxSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
    } else {
      getUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerWidthModifier extends ModifierWithKey<number | Length> {
  constructor(value: number | Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetSideBarWidth(node);
    } else {
      getUINativeModule().sideBarContainer.setSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMinContentWidthModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerMinContentWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMinContentWidth(node);
    } else {
      getUINativeModule().sideBarContainer.setMinContentWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerShowControlButtonModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerShowControlButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetShowControlButton(node);
    } else {
      getUINativeModule().sideBarContainer.setShowControlButton(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMinSideBarWidthModifier extends ModifierWithKey<number | Length> {
  constructor(value: number | Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerMinSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
    } else {
      getUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerControlButtonModifier extends ModifierWithKey<ButtonStyle> {
  constructor(value: ButtonStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainercontrolButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetControlButton(node);
    } else {
      getUINativeModule().sideBarContainer.setControlButton(node, this.value.left,
        this.value.top, this.value.width, this.value.height, this.value.icons?.shown,
        this.value.icons?.hidden, this.value.icons?.switching);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.left === this.value.left &&
      this.stageValue.top === this.value.top &&
      this.stageValue.width === this.value.width &&
      this.stageValue.height === this.value.height)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue.icons?.shown, this.value.icons?.shown) ||
        !isBaseOrResourceEqual(this.stageValue.icons?.hidden, this.value.icons?.hidden) ||
        !isBaseOrResourceEqual(this.stageValue.icons?.switching, this.value.icons?.switching);
    }
  }
}

class SideBarContainerDividerModifier extends ModifierWithKey<DividerStyle> {
  constructor(value: DividerStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('sideBarContainerdivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().sideBarContainer.resetDivider(node);
    } else {
      if (!this.value || !isObject(this.value) || !this.value.strokeWidth) {
        getUINativeModule().sideBarContainer.resetDivider(node);
      } else {
        getUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth,
          this.value.color, this.value.startMargin, this.value.endMargin);
      }
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin);
  }
}

class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onChange(callback: (value: boolean) => void): SideBarContainerAttribute {
    throw new Error('Method not implemented.');
  }
  autoHide(value: boolean): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerAutoHideModifier.identity, SideBarContainerAutoHideModifier, value);
    return this;
  }
  showSideBar(value: boolean): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerShowSideBarModifier.identity, SideBarContainerShowSideBarModifier, value);
    return this;
  }

  maxSideBarWidth(value: number | Length): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMaxSideBarWidthModifier.identity, SideBarContainerMaxSideBarWidthModifier, value);
    return this;
  }

  minSideBarWidth(value: number | Length): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMinSideBarWidthModifier.identity, SideBarContainerMinSideBarWidthModifier, value);
    return this;
  }
  minContentWidth(value: Dimension): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMinContentWidthModifier.identity, SideBarContainerMinContentWidthModifier, value);
    return this;
  }
  controlButton(value: ButtonStyle): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerControlButtonModifier.identity, SideBarContainerControlButtonModifier, value);
    return this;
  }

  divider(value: DividerStyle | null): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerDividerModifier.identity, SideBarContainerDividerModifier, value);
    return this;
  }

  sideBarPosition(value: SideBarPosition): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerPositionModifier.identity, SideBarContainerPositionModifier, value);
    return this;
  }

  sideBarWidth(value: number | Length): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerWidthModifier.identity, SideBarContainerWidthModifier, value);
    return this;
  }

  showControlButton(value: boolean): SideBarContainerAttribute {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerShowControlButtonModifier.identity, SideBarContainerShowControlButtonModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.SideBarContainer.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSideBarContainerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SideBarContainerModifier(nativePtr, classType);
  });
};