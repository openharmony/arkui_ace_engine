/// <reference path="./import.ts" />
class SpanFontSizeModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('spanFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontSize(node);
    } else if (!isString(this.value) && !isNumber(this.value) && !isResource(this.value)) {
      GetUINativeModule().span.resetFontSize(node);
    } else {
      GetUINativeModule().span.setFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanFontFamilyModifier extends ModifierWithKey<string | Resource> {
  static identity: Symbol = Symbol('spanFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontFamily(node);
    } else if (!isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().span.resetFontFamily(node);
    } else {
      GetUINativeModule().span.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanLineHeightModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('spanLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetLineHeight(node);
    } else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().span.resetLineHeight(node);
    } else {
      GetUINativeModule().span.setLineHeight(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanFontStyleModifier extends Modifier<FontStyle> {
  static identity: Symbol = Symbol('spanFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontStyle(node);
    } else {
      GetUINativeModule().span.setFontStyle(node, this.value!);
    }
  }
}
class SpanTextCaseModifier extends Modifier<TextCase> {
  static identity: Symbol = Symbol('spanTextCase');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetTextCase(node);
    } else {
      GetUINativeModule().span.setTextCase(node, this.value!);
    }
  }
}
class SpanFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity = Symbol('spanFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontColor(node);
    } else if (!isString(this.value) && !isNumber(this.value) && !isResource(this.value)) {
      GetUINativeModule().span.resetFontColor(node);
    } else {
      GetUINativeModule().span.setFontColor(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanLetterSpacingModifier extends Modifier<string> {
  static identity = Symbol('spanLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetLetterSpacing(node);
    } else {
      GetUINativeModule().span.setLetterSpacing(node, this.value!);
    }
  }
}
class SpanFontModifier extends ModifierWithKey<Font> {
  static identity = Symbol('spanFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFont(node);
    } else {
      if (!(isNumber(this.value.size)) && !(isString(this.value.size)) && !(isResource(this.value.size))) {
        this.value.size = undefined;
      }
      if (!(isString(this.value.family)) && !(isResource(this.value.family))) {
        this.value.family = undefined;
      }
      GetUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
      isResourceEqual(this.stageValue.size, this.value.size)) ||
      (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
        this.stageValue.size === this.value.size)) &&
      ((isResource(this.stageValue.family) && isResource(this.value.family) &&
        isResourceEqual(this.stageValue.family, this.value.family)) ||
        (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
          this.stageValue.family === this.value.family))) {
      return false;
    } else {
      return true;
    }
  }
}
class SpanDecorationModifier extends ModifierWithKey<ArkDecoration> {
  static identity = Symbol('spanDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetDecoration(node);
    } else {
      if (!(isNumber(this.value.color)) && !(isString(this.value.color)) && !(isResource(this.value.color))) {
        this.value.color = undefined;
      }
      GetUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.type !== this.value.type) {
      return true;
    }
    if (isResource(this.stageValue.color) && isResource(this.value.color)) {
      return !isResourceEqual(this.stageValue.color, this.value.color);
    } else if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    } else {
      return true;
    }
  }
}
class SpanFontWeightModifier extends Modifier<string> {
  static identity = Symbol('spanfontweight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontWeight(node);
    } else {
      GetUINativeModule().span.setFontWeight(node, this.value!);
    }
  }
}

class ArkSpanComponent extends ArkComponent implements CommonMethod<SpanAttribute> {
  decoration(value: { type: TextDecorationType, color?: ResourceColor }): SpanAttribute {
    let arkValue: ArkDecoration = new ArkDecoration();
    if (isNumber(value.type) || (value.type in TextDecorationType)) {
      arkValue.type = value.type;
    }
    if (value.color) {
      arkValue.color = value.color;
    }
    modifierWithKey(this._modifiersWithKeys, SpanDecorationModifier.identity, SpanDecorationModifier, arkValue);
    return this;
  }
  font(value: Font): SpanAttribute {
    if (!isLengthType(value.weight)) {
      value.weight = undefined;
    }
    if (!(value.style in FontStyle)) {
      value.style = undefined;
    }
    modifierWithKey(this._modifiersWithKeys, SpanFontModifier.identity, SpanFontModifier, value);
    return this;
  }
  lineHeight(value: Length): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanLineHeightModifier.identity, SpanLineHeightModifier, value);
    return this;
  }
  fontSize(value: Length): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontSizeModifier.identity, SpanFontSizeModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontColorModifier.identity, SpanFontColorModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): SpanAttribute {
    if (value in FontStyle) {
      modifier(this._modifiers, SpanFontStyleModifier, value);
    } else {
      modifier(this._modifiers, SpanFontStyleModifier, undefined);
    }
    return this;
  }
  fontWeight(value: number | FontWeight | string): SpanAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, SpanFontWeightModifier, value);
    } else {
      modifier(this._modifiers, SpanFontWeightModifier, undefined);
    }
    return this;
  }
  fontFamily(value: string | Resource): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier, value);
    return this;
  }
  letterSpacing(value: number | string): SpanAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, SpanLetterSpacingModifier, value);
    } else {
      modifier(this._modifiers, SpanLetterSpacingModifier, undefined);
    }
    return this;
  }
  textCase(value: TextCase): SpanAttribute {
    if (value in TextCase) {
      modifier(this._modifiers, SpanTextCaseModifier, value);
    } else {
      modifier(this._modifiers, SpanTextCaseModifier, undefined);
    }
    return this;
  }
}
// @ts-ignore
globalThis.Span.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSpanComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();

}
