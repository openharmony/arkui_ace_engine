/// <reference path="./import.ts" />
class ArkButtonComponent extends ArkComponent implements ButtonAttribute {
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error("Method not implemented.");
  }
  type (value: ButtonType): this {
    if (typeof value === "number") {
      modifier(this._modifiers, ButtonTypeModifier, value);
    }
    else {
      modifier(this._modifiers, ButtonTypeModifier, undefined);
    }
    return this;
  }
  stateEffect(value: boolean): this {
    if (typeof value === "boolean") {
      modifier(this._modifiers, ButtonStateEffectModifier, value);
    } else {
      modifier(this._modifiers, ButtonStateEffectModifier, undefined);
    }
    return this;
  }
  fontColor(value: ResourceColor): this {
    var arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, ButtonFontColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, ButtonFontColorModifier, undefined);
    }
    return this;
  }
  fontSize(value: Length): this {
    if (typeof value === "number" || typeof value === "string") {
      modifier(this._modifiers, ButtonFontSizeModifier, value);
    } else {
      modifier(this._modifiers, ButtonFontSizeModifier, undefined);
    }
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    if (typeof value === "string") {
      modifier(this._modifiers, ButtonFontWeightModifier, value);
    } else {
      modifier(this._modifiers, ButtonFontWeightModifier, undefined);
    }
    return this;
  }
  fontStyle(value: FontStyle): this {
    if (typeof value === "number" && value >= 0 && value < 2) {
      modifier(this._modifiers, ButtonFontStyleModifier, value);
    } else {
      modifier(this._modifiers, ButtonFontStyleModifier, undefined);
    }
    return this;
  }
  fontFamily(value: string | Resource): this {
    if (typeof value === "string") {
      modifier(this._modifiers, ButtonFontFamilyModifier, value);
    } else {
      modifier(this._modifiers, ButtonFontFamilyModifier, undefined);
    }
    return this;
  }
  labelStyle(value: LabelStyle): this {
    if (typeof value === "object") {
      let data = new ArkLabelStyle();
      data.heightAdaptivePolicy = value.heightAdaptivePolicy;
      data.maxFontSize = value.maxFontSize;
      data.maxLines = value.maxLines;
      data.minFontSize = value.minFontSize;
      data.overflow = value.overflow;
      if (typeof value.font === "object") {
        data.font.family = value.font.family;
        data.font.size = value.font.size;
        data.font.style = value.font.style;
        data.font.weight = value.font.weight;
      }
      modifier(this._modifiers, ButtonLabelStyleModifier, data);
    } else {
      modifier(this._modifiers, ButtonLabelStyleModifier, undefined);
    }
    return this;
  }
}
class ButtonStateEffectModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol("buttonStateEffect");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetStateEffect(node);
    }
    else {
      GetUINativeModule().button.setStateEffect(node, this.value);
    }
  }
}
class ButtonFontStyleModifier extends Modifier<number> {
  static identity: Symbol = Symbol("buttonFontStyle");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontStyle(node);
    }
    else {
      GetUINativeModule().button.setFontStyle(node, this.value);
    }
  }
}
class ButtonFontFamilyModifier extends Modifier<string> {
  static identity: Symbol = Symbol("buttonFontFamily");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        GetUINativeModule().button.resetFontFamily(node);
      }
      else {
        GetUINativeModule().button.setFontFamily(node, this.value);
      }
  }
}
class ButtonLabelStyleModifier extends Modifier<ArkLabelStyle> {
  static identity: Symbol = Symbol("buttonLabelStyle");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
        GetUINativeModule().button.resetLabelStyle(node);
    }
    else {
      if (typeof this.value === "object")
      {
        let textOverflow = this.value.overflow; // number -> Ace::TextOverflow
        let maxLines = this.value.maxLines; // number -> uint32_t
        let minFontSize = this.value.minFontSize; // number/string -> Dimension
        let maxFontSize = this.value.maxFontSize; // number/string -> Dimension
        let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number -> Ace::TextHeightAdaptivePolicy
        let fontSize = undefined; // number/string ->Dimension
        let fontWeight = undefined; // string -> Ace::FontWeight
        let fontStyle = undefined; // number -> Ace::FontStyle
        let fontFamily = undefined; // string ->std::vector<std::string>
        if (typeof this.value.font === "object")
        {
          fontSize = this.value.font.size;
          fontWeight = this.value.font.weight;
          fontStyle = this.value.font.style;
          fontFamily = this.value.font.family;
        }
        GetUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize, maxFontSize,
          heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
      }
    }
  }
}
class ButtonTypeModifier extends Modifier<number> {
  static identity: Symbol = Symbol("buttonType");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetType(node);
    }
    else {
      GetUINativeModule().button.setType(node, this.value);
    }
  }
}
class ButtonFontColorModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol("buttonFontColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontColor(node);
    }
    else {
      GetUINativeModule().button.setFontColor(node, this.value);
    }
  }
}
class ButtonFontSizeModifier extends Modifier<number> {
  static identity: Symbol = Symbol("buttonFontSize");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontSize(node);
    }
    else {
      GetUINativeModule().button.setFontSize(node, this.value);
    }
  }
}
class ButtonFontWeightModifier extends Modifier<string> {
  static identity: Symbol = Symbol("buttonFontWeight");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().button.resetFontWeight(node);
    }
    else {
      GetUINativeModule().button.setFontWeight(node, this.value);
    }
  }
}
// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  var component = this.createOrGetNode(elmtId, ()=> {
    return new ArkButtonComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
