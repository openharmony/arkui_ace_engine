/// <reference path='./import.ts' />
class MenuItemSelectedModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('selected');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().menuitem.resetSelected(node);
    }
    else {
      GetUINativeModule().menuitem.setSelected(node, this.value);
    }
  }
}
class LabelFontColorModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol('labelfontColor');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().menuitem.resetLabelFontColor(node);
    }
    else {
      GetUINativeModule().menuitem.setLabelFontColor(node, this.value);
    }
  }
}
class ContentFontColorModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol('contentfontColor');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFontColor(node);
    }
    else {
      GetUINativeModule().menuitem.setContentFontColor(node, this.value);
    }
  }
}

class LabelFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('labelFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      GetUINativeModule().menuitem.setLabelFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class ContentFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('contentFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      GetUINativeModule().menuitem.setContentFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
  selected(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, MenuItemSelectedModifier, value);
    } else {
      modifier(this._modifiers, MenuItemSelectedModifier, false);
    }
    return this;
  }
  selectIcon(value: any): MenuItemAttribute {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (selected: boolean) => void): MenuItemAttribute {
    throw new Error('Method not implemented.');
  }
  contentFont(value: Font): MenuItemAttribute {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
    }
    modifier(this._modifiers, ContentFontModifier, font);
    return this;
  }
  contentFontColor(value: ResourceColor): this {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, ContentFontColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, ContentFontColorModifier, undefined);
    }
    return this;
  }
  labelFont(value: Font): MenuItemAttribute {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
    }
    modifier(this._modifiers, LabelFontModifier, font);
    return this;
  }
  labelFontColor(value: ResourceColor): this {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, LabelFontColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, LabelFontColorModifier, undefined);
    }
    return this;
  }
}
// @ts-ignore
globalThis.MenuItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
