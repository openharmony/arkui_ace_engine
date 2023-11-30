/// <reference path="./import.ts" />
class SpanFontSizeModifier extends Modifier<string | number> {
  static identity: Symbol = Symbol('spanFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontSize(node);
    } else {
      GetUINativeModule().span.setFontSize(node, this.value!);
    }
  }
}
class SpanFontFamilyModifier extends Modifier<string> {
  static identity: Symbol = Symbol('spanFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontFamily(node);
    } else {
      GetUINativeModule().span.setFontFamily(node, this.value);
    }
  }
}
class SpanLineHeightModifier extends Modifier<string | number> {
  static identity: Symbol = Symbol('spanLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetLineHeight(node);
    } else {
      GetUINativeModule().span.setLineHeight(node, this.value!);
    }
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
class SpanFontColorModifier extends Modifier<string | number> {
  static identity = Symbol('spanFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFontColor(node);
    } else {
      GetUINativeModule().span.setFontColor(node, this.value!);
    }
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
class SpanFontModifier extends Modifier<ArkFont> {
  static identity = Symbol('spanFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetFont(node);
    } else {
      GetUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}
class SpanDecorationModifier extends Modifier<ArkDecoration> {
  static identity = Symbol('spanDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().span.resetDecoration(node);
    } else {
      GetUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
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
    if (!isNumber(value.type) && !(value.type in TextDecorationType)) {
      arkValue.type = undefined;
    }
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value.color)) {
      arkValue.color = arkColor.color;
    } else {
      arkValue.color = undefined;
    }
    modifier(this._modifiers, SpanDecorationModifier, arkValue);
    return this;
  }
  font(value: Font): SpanAttribute {
    let arkValue: ArkFont = new ArkFont();
    if (isLengthType(value.size)) {
      arkValue.size = <string | number>value.size;
    }
    if (isLengthType(value.weight)) {
      arkValue.weight = value.weight;
    }
    if (isString(value.family)) {
      arkValue.family = <string>value.family;
    }
    if (value.style in FontStyle) {
      arkValue.style = value.style;
    }
    modifier(this._modifiers, SpanFontModifier, arkValue);
    return this;
  }
  lineHeight(value: Length): SpanAttribute {
    if (isString(value) || isNumber(value)) {
      modifier(this._modifiers, SpanLineHeightModifier, <string | number>value);
    } else {
      modifier(this._modifiers, SpanLineHeightModifier, undefined);
    }
    return this;
  }
  fontSize(value: number | string | Resource): SpanAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, SpanFontSizeModifier, <string | number>value);
    } else {
      modifier(this._modifiers, SpanFontSizeModifier, undefined);
    }
    return this;
  }
  fontColor(value: ResourceColor): SpanAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, SpanFontColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, SpanFontColorModifier, undefined);
    }
    return this;
  }
  fontStyle(value: FontStyle): SpanAttribute {
    if (!(value in FontStyle)) {
      value = FontStyle.Normal;
    }
    modifier(this._modifiers, SpanFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): SpanAttribute {
    if (!isLengthType(value)) {
      modifier(this._modifiers, SpanFontWeightModifier, undefined);
    } else {
      modifier(this._modifiers, SpanFontWeightModifier, value);
    }
    return this;
  }
  fontFamily(value: string | Resource): SpanAttribute {
    if (isString(value)) {
      modifier(this._modifiers, SpanFontFamilyModifier, <string>value);
    } else {
      modifier(this._modifiers, SpanFontFamilyModifier, undefined);
    }
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
