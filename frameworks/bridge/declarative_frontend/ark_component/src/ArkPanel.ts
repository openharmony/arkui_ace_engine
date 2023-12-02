/// <reference path='./import.ts' />
class ArkPanelComponent extends ArkComponent implements PanelAttribute {
  mode(value: PanelMode): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, PanelModeModifier, value);
    } else {
      modifier(this._modifiers, PanelModeModifier, undefined);
    }
    return this;
  }
  type(value: PanelType): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, PanelTypeModifier, value);
    } else {
      modifier(this._modifiers, PanelTypeModifier, undefined);
    }
    return this;
  }
  dragBar(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, DragBarModifier, value);
    } else {
      modifier(this._modifiers, DragBarModifier, undefined);
    }
    return this;
  }
  customHeight(value: any): this {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelCustomHeightModifier, undefined);
    } else {
      modifier(this._modifiers, PanelCustomHeightModifier, value);
    }
    return this;
  }
  fullHeight(value: string | number): this {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelFullHeightModifier, undefined);
    } else {
      modifier(this._modifiers, PanelFullHeightModifier, value);
    }
    return this;
  }
  halfHeight(value: string | number): this {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelHalfHeightModifier, undefined);
    } else {
      modifier(this._modifiers, PanelHalfHeightModifier, value);
    }
    return this;
  }
  miniHeight(value: string | number): this {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelMiniHeightModifier, undefined);
    } else {
      modifier(this._modifiers, PanelMiniHeightModifier, value);
    }
    return this;
  }
  show(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, ShowModifier, value);
    } else {
      modifier(this._modifiers, ShowModifier, undefined);
    }
    return this;
  }
  backgroundMask(color: ResourceColor): this {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(color)) {
      modifier(this._modifiers, PanelBackgroundMaskModifier, arkColor.color);
    } else {
      modifier(this._modifiers, PanelBackgroundMaskModifier, undefined);
    }
    return this;
  }
  showCloseIcon(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, ShowCloseIconModifier, value);
    } else {
      modifier(this._modifiers, ShowCloseIconModifier, undefined);
    }
    return this;
  }
  onChange(event: (width: number, height: number, mode: PanelMode) => void): this {
    throw new Error('Method not implemented.');
  }
  onHeightChange(callback: (value: number) => void): this {
    throw new Error('Method not implemented.');
  }
}

class PanelBackgroundMaskModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol('panelBackgroundMask');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.resetBackgroundMask(node);
    } else {
      GetUINativeModule().panel.setBackgroundMask(node, this.value);
    }
  }
}

class PanelModeModifier extends Modifier<PanelMode> {
  static identity: Symbol = Symbol('panelMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.ResetPanelMode(node);
    } else {
      GetUINativeModule().panel.SetPanelMode(node, this.value);
    }
  }
}

class PanelTypeModifier extends Modifier<PanelType> {
  static identity: Symbol = Symbol('panelType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.ResetPanelType(node);
    } else {
      GetUINativeModule().panel.SetPanelType(node, this.value);
    }
  }
}

class PanelCustomHeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol('panelCustomHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.resetPanelCustomHeight(node);
    } else {
      GetUINativeModule().panel.setPanelCustomHeight(node, this.value);
    }
  }
}

class PanelFullHeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol('panelFullHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.resetPanelFullHeight(node);
    } else {
      GetUINativeModule().panel.setPanelFullHeight(node, this.value);
    }
  }
}

class PanelHalfHeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol('panelHalfHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.resetPanelHalfHeight(node);
    } else {
      GetUINativeModule().panel.setPanelHalfHeight(node, this.value);
    }
  }
}

class PanelMiniHeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol('panelMiniHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().panel.resetPanelMiniHeight(node);
    } else {
      GetUINativeModule().panel.setPanelMiniHeight(node, this.value);
    }
  }
}

class ShowCloseIconModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('showCloseIcon');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().panel.resetShowCloseIconModifier(node);
    } else {
      GetUINativeModule().panel.setShowCloseIconModifier(node, this.value);
    }
  }
}

class DragBarModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('dragBar');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().panel.resetDragBar(node);
    } else {
      GetUINativeModule().panel.setDragBar(node, this.value);
    }
  }
}

class ShowModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('show');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().panel.resetDragBar(node);
    } else {
      GetUINativeModule().panel.setDragBar(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Panel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPanelComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
