/// <reference path="./import.ts" />
class FontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFontColor(node);
    } else {
      GetUINativeModule().text.setFontColor(node, this.value);
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

class FontSizeModifier extends ModifierWithKey<number | string | Resource> {
  static identity: Symbol = Symbol('fontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFontSize(node);
    } else {
      GetUINativeModule().text.setFontSize(node, this.value);
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

class FontWeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol('fontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFontWeight(node);
    } else {
      GetUINativeModule().text.setFontWeight(node, this.value);
    }
  }
}

class FontStyleModifier extends Modifier<number> {
  static identity: Symbol = Symbol('fontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFontStyle(node);
    } else {
      GetUINativeModule().text.setFontStyle(node, this.value);
    }
  }
}

class TextAlignModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetTextAlign(node);
    } else {
      GetUINativeModule().text.setTextAlign(node, this.value);
    }
  }
}

class TextHeightAdaptivePolicyModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textHeightAdaptivePolicy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetHeightAdaptivePolicy(node);
    } else {
      GetUINativeModule().text.setHeightAdaptivePolicy(node, this.value!);
    }
  }
}

class TextDraggableModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textDraggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetDraggable(node);
    } else {
      GetUINativeModule().text.setDraggable(node, this.value!);
    }
  }
}

class TextMinFontSizeModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textMinFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetMinFontSize(node);
    } else {
      GetUINativeModule().text.setMinFontSize(node, this.value!);
    }
  }
}

class TextMaxFontSizeModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textMaxFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetMaxFontSize(node);
    } else {
      GetUINativeModule().text.setMaxFontSize(node, this.value!);
    }
  }
}

class TextLineHeightModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetLineHeight(node);
    } else {
      GetUINativeModule().text.setLineHeight(node, this.value!);
    }
  }
}

class TextCopyOptionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetCopyOption(node);
    } else {
      GetUINativeModule().text.setCopyOption(node, this.value!);
    }
  }
}

class TextFontFamilyModifier extends Modifier<string> {
  static identity: Symbol = Symbol('textFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFontFamily(node);
    } else {
      GetUINativeModule().text.setFontFamily(node, this.value!);
    }
  }
}

class TextMaxLinesModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetMaxLines(node);
    } else {
      GetUINativeModule().text.setMaxLines(node, this.value!);
    }
  }
}

class TextLetterSpacingModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetLetterSpacing(node);
    } else {
      GetUINativeModule().text.setLetterSpacing(node, this.value!);
    }
  }
}

class TextTextOverflowModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textTextOverflow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetTextOverflow(node);
    } else {
      GetUINativeModule().text.setTextOverflow(node, this.value!);
    }
  }
}

class TextBaselineOffsetModifier extends Modifier<number | string> {
  static identity: symbol = Symbol('textBaselineOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetBaselineOffset(node);
    } else {
      GetUINativeModule().text.setBaselineOffset(node, this.value!);
    }
  }
}

class TextTextCaseModifier extends Modifier<number> {
  static identity: symbol = Symbol('textTextCase');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetTextCase(node);
    } else {
      GetUINativeModule().text.setTextCase(node, this.value!);
    }
  }
}

class TextTextIndentModifier extends Modifier<number | string> {
  static identity: symbol = Symbol('textTextIndent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetTextIndent(node);
    } else {
      GetUINativeModule().text.setTextIndent(node, this.value!);
    }
  }
}

class TextTextShadowModifier extends Modifier<ArkShadowInfoToArray> {
  static identity: Symbol = Symbol('textTextShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetTextShadow(node);
    } else {
      GetUINativeModule().text.setTextShadow(
        node,
        this.value.radius,
        this.value.color,
        this.value.offsetX,
        this.value.offsetY,
        this.value.fill,
        this.value.radius.length
      );
    }
  }
}

class TextDecorationModifier extends Modifier<ArkDecoration> {
  static identity: Symbol = Symbol('textDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetDecoration(node);
    } else {
      GetUINativeModule().text.setDecoration(node, this.value!.type, this.value!.color);
    }
  }
}

class TextFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('textFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().text.resetFont(node);
    } else {
      GetUINativeModule().text.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}
class ArkTextComponent extends ArkComponent implements TextAttribute {
  enableDataDetector(enable: boolean): this {
    throw new Error('Method not implemented.');
  }
  dataDetectorConfig(config: any): this {
    throw new Error('Method not implemented.');
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  font(value: Font): TextAttribute {
    let arkValue: ArkFont = new ArkFont();
    if (isLengthType(value.size)) {
      arkValue.size = <number | string>value.size;
    }
    if (isLengthType(value.weight)) {
      arkValue.weight = <number | string>value.weight;
    }
    if (isString(value.family)) {
      arkValue.family = <string>value.family;
    }
    if (isNumber(value.style)) {
      if (value.style in FontStyle) {
        arkValue.style = value.style;
      } else {
        arkValue.style = FontStyle.Normal;
      }
    }
    modifier(this._modifiers, TextFontModifier, arkValue);
    return this;
  }
  fontColor(value: ResourceColor): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, FontColorModifier.identity, FontColorModifier, value);
    return this;
  }
  fontSize(value: any): TextAttribute {
    modifierWithKey(this._modifiersWithKeys, FontSizeModifier.identity, FontSizeModifier, value);
    return this;
  }
  minFontSize(value: number | string | Resource): TextAttribute {
    if (isLengthType(value)) {
      let arkValue: number | string = <number | string>value;
      modifier(this._modifiers, TextMinFontSizeModifier, arkValue);
    } else {
      modifier(this._modifiers, TextMinFontSizeModifier, undefined);
    }
    return this;
  }
  maxFontSize(value: number | string | Resource): TextAttribute {
    if (isLengthType(value)) {
      let arkValue: number | string = <number | string>value;
      modifier(this._modifiers, TextMaxFontSizeModifier, arkValue);
    } else {
      modifier(this._modifiers, TextMaxFontSizeModifier, undefined);
    }
    return this;
  }
  fontStyle(value: FontStyle): TextAttribute {
    if (isNumber(value)) {
      modifier(this._modifiers, FontStyleModifier, value);
    }
    return this;
  }
  fontWeight(value: any): TextAttribute {
    let fontWeightStr: string = '400';
    if (isNumber(value)) {
      if (value === 0) {
        fontWeightStr = 'Lighter';
      } else if (value === 1) {
        fontWeightStr = 'Normal';
      } else if (value === 2) {
        fontWeightStr = 'Regular';
      } else if (value === 3) {
        fontWeightStr = 'Medium';
      } else if (value === 4) {
        fontWeightStr = 'Bold';
      } else if (value === 5) {
        fontWeightStr = 'Bolder';
      } else {
        fontWeightStr = value.toString();
      }
    } else if (isString(value)) {
      fontWeightStr = value;
    }
    modifier(this._modifiers, FontWeightModifier, fontWeightStr);
    return this;
  }
  textAlign(value: TextAlign): TextAttribute {
    let textAlignNum = 0;
    if (isNumber(value)) {
      textAlignNum = value;
    }
    modifier(this._modifiers, TextAlignModifier, textAlignNum);
    return this;
  }
  lineHeight(value: number | string | Resource): TextAttribute {
    if (isLengthType(value)) {
      let arkValue: number | string = <number | string>value;
      modifier(this._modifiers, TextLineHeightModifier, arkValue);
    } else {
      modifier(this._modifiers, TextLineHeightModifier, undefined);
    }
    return this;
  }
  textOverflow(value: { overflow: TextOverflow }): TextAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, TextTextOverflowModifier, undefined);
    } else if (isObject(value)) {
      let overflowValue = value.overflow;
      if (isNumber(overflowValue)) {
        if (!(overflowValue in CopyOptions)) {
          overflowValue = TextOverflow.Clip;
        }
        modifier(this._modifiers, TextTextOverflowModifier, overflowValue);
      } else {
        modifier(this._modifiers, TextTextOverflowModifier, undefined);
      }
    }
    return this;
  }
  fontFamily(value: string | Resource): TextAttribute {
    if (isLengthType(value)) {
      let arkValue: number | string = <number | string>value;
      modifier(this._modifiers, TextFontFamilyModifier, arkValue);
    } else {
      modifier(this._modifiers, TextFontFamilyModifier, undefined);
    }
    return this;
  }
  maxLines(value: number): TextAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, TextMaxLinesModifier, undefined);
    } else {
      modifier(this._modifiers, TextMaxLinesModifier, value);
    }
    return this;
  }
  decoration(value: { type: TextDecorationType; color?: ResourceColor }): TextAttribute {
    let arkDecoration: ArkDecoration = new ArkDecoration();
    if (value === null || value === undefined) {
      modifier(this._modifiers, TextDecorationModifier, arkDecoration);
    } else if (isObject(value)) {
      let typeValue = value.type;
      if (!(typeValue in TextDecorationType)) {
        arkDecoration.type = TextDecorationType.None;
      } else {
        arkDecoration.type = typeValue;
      }
      let arkColor: ArkColor = new ArkColor();
      if (arkColor.parseColorValue(value.color)) {
        arkDecoration.color = arkColor.color;
      }
      modifier(this._modifiers, TextDecorationModifier, arkDecoration);
    }
    return this;
  }
  letterSpacing(value: number | string): TextAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, TextLetterSpacingModifier, value);
    } else {
      modifier(this._modifiers, TextLetterSpacingModifier, undefined);
    }
    return this;
  }
  textCase(value: TextCase): TextAttribute {
    if (!(value in TextCase)) {
      modifier(this._modifiers, TextTextCaseModifier, undefined);
    } else {
      modifier(this._modifiers, TextTextCaseModifier, value);
    }
    return this;
  }
  baselineOffset(value: number | string): TextAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, TextBaselineOffsetModifier, value);
    } else {
      modifier(this._modifiers, TextBaselineOffsetModifier, undefined);
    }
    return this;
  }
  copyOption(value: CopyOptions): TextAttribute {
    if (isNumber(value)) {
      modifier(this._modifiers, TextCopyOptionModifier, value);
    } else {
      modifier(this._modifiers, TextCopyOptionModifier, undefined);
    }
    return this;
  }
  draggable(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, TextDraggableModifier, value);
    } else {
      modifier(this._modifiers, TextDraggableModifier, undefined);
    }
    return this;
  }
  textShadow(value: ShadowOptions | Array<ShadowOptions>): TextAttribute {
    let array: ArkShadowInfoToArray = new ArkShadowInfoToArray();
    if (value === null || value === undefined) {
      modifier(this._modifiers, TextTextShadowModifier, undefined);
    } else if (Object.getPrototypeOf(value).constructor === Object) {
      let objValue: ShadowOptions = <ShadowOptions>value;
      if (objValue.radius === null || objValue.radius === undefined) {
        modifier(this._modifiers, TextTextShadowModifier, undefined);
      } else {
        array.radius.push(<number | string>objValue.radius);
        array.color.push(objValue.color);
        array.offsetX.push(
          objValue.offsetX === undefined || objValue.offsetX === null ? 0 : <number | string>objValue.offsetX
        );
        array.offsetY.push(
          objValue.offsetY === undefined || objValue.offsetY === null ? 0 : <number | string>objValue.offsetY
        );
        array.fill.push(objValue.fill === undefined || objValue.fill === null ? false : objValue.fill);
        modifier(this._modifiers, TextTextShadowModifier, array);
      }
    } else if (Object.getPrototypeOf(value).constructor === Array) {
      let arrayValue: Array<ShadowOptions> = <Array<ShadowOptions>>value;
      let isFlag: boolean = true;
      for (let item of arrayValue) {
        if (item.radius === undefined || item.radius === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        for (let objValue of arrayValue) {
          array.radius.push(<number | string>objValue.radius);
          array.color.push(objValue.color);
          array.offsetX.push(
            objValue.offsetX === undefined || objValue.offsetX === null ? 0 : <number | string>objValue.offsetX
          );
          array.offsetY.push(
            objValue.offsetY === undefined || objValue.offsetY === null ? 0 : <number | string>objValue.offsetY
          );
          array.fill.push(objValue.fill === undefined || objValue.fill === null ? false : objValue.fill);
        }
        modifier(this._modifiers, TextTextShadowModifier, array);
      } else {
        modifier(this._modifiers, TextTextShadowModifier, undefined);
      }
    }
    return this;
  }
  heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute {
    if (!(value in TextHeightAdaptivePolicy)) {
      modifier(this._modifiers, TextHeightAdaptivePolicyModifier, undefined);
    } else {
      modifier(this._modifiers, TextHeightAdaptivePolicyModifier, value);
    }
    return this;
  }
  textIndent(value: Length): TextAttribute {
    if (isLengthType(value)) {
      let arkValue: number | string = <number | string>value;
      modifier(this._modifiers, TextTextIndentModifier, arkValue);
    } else {
      modifier(this._modifiers, TextTextIndentModifier, undefined);
    }
    return this;
  }
  wordBreak(value: WordBreak): TextAttribute {
    throw new Error('Method not implemented.');
  }
  onCopy(callback: (value: string) => void): TextAttribute {
    throw new Error('Method not implemented.');
  }
  selection(selectionStart: number, selectionEnd: number): TextAttribute {
    throw new Error('Method not implemented.');
  }
  ellipsisMode(value: EllipsisMode): TextAttribute {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Text.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
