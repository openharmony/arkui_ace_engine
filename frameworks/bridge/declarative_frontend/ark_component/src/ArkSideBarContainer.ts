/// <reference path="./import.ts" />
class SideBarContainerPositionModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('sideBarContainerPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetSideBarPosition(node);
    } else {
      GetUINativeModule().sideBarContainer.setSideBarPosition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerAutoHideModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('sideBarContainerautoHide');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetAutoHide(node);
    } else {
      GetUINativeModule().sideBarContainer.setAutoHide(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerShowSideBarModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('sideBarContainerShowSideBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetShowSideBar(node);
    } else {
      GetUINativeModule().sideBarContainer.setShowSideBar(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMaxSideBarWidthModifier extends ModifierWithKey<number | Length> {
  static identity: Symbol = Symbol('sideBarContainerMaxSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerWidthModifier extends ModifierWithKey<number | Length> {
  static identity: Symbol = Symbol('sideBarContainerWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMinContentWidthModifier extends ModifierWithKey<Dimension> {
  static identity: Symbol = Symbol('sideBarContainerMinContentWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMinContentWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMinContentWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerShowControlButtonModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('sideBarContainerShowControlButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetShowControlButton(node);
    } else {
      GetUINativeModule().sideBarContainer.setShowControlButton(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerMinSideBarWidthModifier extends ModifierWithKey<number | Length> {
  static identity: Symbol = Symbol('sideBarContainerMinSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SideBarContainerControlButtonModifier extends ModifierWithKey<ButtonStyle> {
  static identity: Symbol = Symbol('sideBarContainercontrolButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetControlButton(node);
    } else {
      GetUINativeModule().sideBarContainer.setControlButton(node, this.value.left,
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
    }
    else {
      return !isBaseOrResourceEqual(this.stageValue.icons?.shown, this.value.icons?.shown) ||
        !isBaseOrResourceEqual(this.stageValue.icons?.hidden, this.value.icons?.hidden) ||
        !isBaseOrResourceEqual(this.stageValue.icons?.switching, this.value.icons?.switching)
    }
  }
}

class SideBarContainerDividerModifier extends ModifierWithKey<DividerStyle> {
  static identity: Symbol = Symbol('sideBarContainerdivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetDivider(node);
    } else {
      if (!this.value || !isObject(this.value) || !this.value.strokeWidth) {
        GetUINativeModule().sideBarContainer.resetDivider(node);
      } else {
        GetUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth,
          this.value.color, this.value.startMargin, this.value.endMargin);
      }
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin)
  }
}

class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
  onChange(callback: (value: boolean) => void): SideBarContainerAttribute {
    throw new Error("Method not implemented.");
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
globalThis.SideBarContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSideBarContainerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
