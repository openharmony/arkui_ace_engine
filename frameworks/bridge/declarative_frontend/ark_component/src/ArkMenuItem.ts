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

class LabelFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol("labelfontColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetLabelFontColor(node);
    } else {
      GetUINativeModule().menuitem.setLabelFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class ContentFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol("contentfontColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFontColor(node);
    } else {
      GetUINativeModule().menuitem.setContentFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class LabelFontModifier extends ModifierWithKey<Font> {
  static identity: Symbol = Symbol("labelFont");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      const valueType: string = typeof this.value;
      if (valueType === "number" || valueType === "string" || isResource(this.value)) {
        GetUINativeModule().menuitem.setLabelFont(node, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().menuitem.setLabelFont(node, (this.value as Font).size,
          (this.value as Font).weight, (this.value as Font).family,
          (this.value as Font).style);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as Font).size === (this.value as Font).size &&
        (this.stageValue as Font).weight === (this.value as Font).weight &&
        (this.stageValue as Font).family === (this.value as Font).family &&
        (this.stageValue as Font).style === (this.value as Font).style);
    } else {
      return true;
    }
  }
}

class ContentFontModifier extends ModifierWithKey<Font> {
  static identity: Symbol = Symbol("contentFont");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      const valueType: string = typeof this.value;
      if (valueType === "number" || valueType === "string" || isResource(this.value)) {
        GetUINativeModule().menuitem.setContentFont(node, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().menuitem.setContentFont(node, (this.value as Font).size,
          (this.value as Font).weight, (this.value as Font).family,
          (this.value as Font).style);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as Font).size === (this.value as Font).size &&
        (this.stageValue as Font).weight === (this.value as Font).weight &&
        (this.stageValue as Font).family === (this.value as Font).family &&
        (this.stageValue as Font).style === (this.value as Font).style);
    } else {
      return true;
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
  contentFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, ContentFontModifier.identity, ContentFontModifier, value);
    return this;
  }
  contentFontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ContentFontColorModifier.identity, ContentFontColorModifier, value);
    return this;
  }
  labelFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, LabelFontModifier.identity, LabelFontModifier, value);
    return this;
  }
  labelFontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, LabelFontColorModifier.identity, LabelFontColorModifier, value);
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
