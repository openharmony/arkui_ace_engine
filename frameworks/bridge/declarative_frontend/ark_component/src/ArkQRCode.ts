/// <reference path='./import.ts' />
class ArkQRCodeComponent extends ArkComponent implements QRCodeAttribute {
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
  static identity: Symbol = Symbol('color');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().qrcode.resetQRColor(node);
      } else {
          GetUINativeModule().qrcode.setQRColor(node, this.value);
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

class QRBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('qrBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().qrcode.resetQRBackgroundColor(node);
      } else {
          GetUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
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

class QRContentOpacityModifier extends ModifierWithKey<number | Resource> {
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
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
