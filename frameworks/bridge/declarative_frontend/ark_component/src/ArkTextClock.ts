/// <reference path='./import.ts' />
class ArkTextClockComponent extends ArkComponent implements TextClockAttribute {
  format(value: string): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFormatModifier.identity, TextClockFormatModifier, value);
    return this;
  }
  onDateChange(event: (value: number) => void): this {
    throw new Error('Method not implemented.');
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontColorModifier.identity, TextClockFontColorModifier, value);
    return this;
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontSizeModifier.identity, TextClockFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontStyleModifier.identity, TextClockFontStyleModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontWeightModifier.identity, TextClockFontWeightModifier, value);
    return this;
  }
  fontFamily(value: ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFamilyModifier.identity, TextClockFontFamilyModifier, value);
    return this;
  }
  textShadow(value: ShadowOptions): this {
    throw new Error('Method not implemented.');
  }
  fontFeature(value: string): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class TextClockFormatModifier extends ModifierWithKey<string> {
  static identity: Symbol = Symbol('textClockFormat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFormat(node);
    } else {
      GetUINativeModule().textClock.setFormat(node, this.value);
    }
  }
}

class TextClockFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('textClockFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontColor(node);
    } else {
      GetUINativeModule().textClock.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockFontSizeModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('textClockFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontSize(node);
    } else {
      GetUINativeModule().textClock.setFontSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockFontStyleModifier extends ModifierWithKey<FontStyle> {
  static identity: Symbol = Symbol('textClockFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontStyle(node);
    } else {
      GetUINativeModule().textClock.setFontStyle(node, this.value!);
    }
  }
}

class TextClockFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  static identity: Symbol = Symbol('textClockFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontWeight(node);
    } else {
      GetUINativeModule().textClock.setFontWeight(node, this.value!);
    }
  }
}

class TextClockFontFamilyModifier extends ModifierWithKey<ResourceStr> {
  static identity: Symbol = Symbol('textClockFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontFamily(node);
    } else {
      GetUINativeModule().textClock.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextClockComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
