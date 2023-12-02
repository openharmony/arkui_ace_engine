/// <reference path='./import.ts' />
class MenuFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetMenuFontColor(node);
    } else {
      GetUINativeModule().common.setMenuFontColor(node, this.value);
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

class MenuFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('font');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menu.resetFont(node);
    }
    else {
      GetUINativeModule().menu.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class RadiusModifier extends Modifier<ArkBorderRadius> {
  static identity: Symbol = Symbol('radius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menu.resetRadius(node);
    }
    else {
      GetUINativeModule().menu.setRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
    }
  }
}

class ArkMenuComponent extends ArkComponent implements MenuAttribute {
  fontSize(value: any): this {
    throw new Error('Method not implemented.');
  }
  font(value: Font): MenuAttribute {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
    }
    modifier(this._modifiers, MenuFontModifier, font);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, MenuFontColorModifier.identity, MenuFontColorModifier, value);
    return this;
  }
  radius(value: any): MenuAttribute {
    let radius = new ArkBorderRadius();
    if (typeof value === 'number' || typeof value === 'string') {
      radius.topLeft = value;
      radius.topRight = value;
      radius.bottomLeft = value;
      radius.bottomRight = value;
    }
    else {
      radius.topLeft = value?.topRight;
      radius.topRight = value?.topRight;
      radius.bottomLeft = value?.bottomLeft;
      radius.bottomRight = value?.bottomRight;
    }
    modifier(this._modifiers, RadiusModifier, radius);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Menu.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMenuComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
