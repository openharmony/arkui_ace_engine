/// <reference path="./import.ts" />

class FontColorModifier extends Modifier< number | undefined> {
    static identity: Symbol = Symbol("fontColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().text.resetFontColor(node);
        } else {
            GetUINativeModule().text.setFontColor(node, this.value);
        }
    }
}

class FontSizeModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("fontSize");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().text.resetFontSize(node);
        }
        else {
            GetUINativeModule().text.setFontSize(node, this.value);
        }
    }
}

class FontWeightModifier extends Modifier<string> {
    static identity: Symbol = Symbol("fontWeight");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().text.resetFontWeight(node);
        }
        else {
            GetUINativeModule().text.setFontWeight(node, this.value);
        }
    }
}

class FontStyleModifier extends Modifier<number> {
    static identity: Symbol = Symbol("fontStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().text.resetFontStyle(node);
        }
        else {
            GetUINativeModule().text.setFontStyle(node, this.value);
        }
    }
}

class TextAlignModifier extends Modifier<number> {
    static identity: Symbol = Symbol("textAlign");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().text.resetTextAlign(node);
        }
        else {
            GetUINativeModule().text.setTextAlign(node, this.value);
        }
    }
}

class ArkTextComponent extends ArkComponent implements TextAttribute {
    font(value: Font): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): TextAttribute {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, FontColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, FontColorModifier, undefined);
        }
        return this;
    }
    fontSize(value: any): TextAttribute {
        if (!isNumber(value) && !isString(value)) {
            modifier(this._modifiers, FontSizeModifier, undefined);
        }
        else {
            modifier(this._modifiers, FontSizeModifier, value);
        }
        return this;
    }
    minFontSize(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    maxFontSize(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): TextAttribute {      
        if(isNumber(value)){
            modifier(this._modifiers, FontStyleModifier, value);
        }
        return this;
    }
    fontWeight(value: any): TextAttribute {
        let fontWeightStr: string = "400";
        if(isNumber(value)){
            if(value === 0){
                fontWeightStr = "Lighter"
            }
            else if(value === 1){
                fontWeightStr = "Normal"
            }
            else if(value === 2){
                fontWeightStr = "Regular"
            }
            else if(value === 3){
                fontWeightStr = "Medium"
            }
            else if(value === 4){
                fontWeightStr = "Bold"
            }
            else if(value === 5){
                fontWeightStr = "Bolder"
            }
            else{
                fontWeightStr = value.toString()            
            }
        }       
        else if (isString(value)) {
            fontWeightStr = value
        }
        modifier(this._modifiers, FontWeightModifier, fontWeightStr);
        return this;
    }
    textAlign(value: TextAlign): TextAttribute {
        let textAlignNum = 0
        if(isNumber(value)){
            textAlignNum = value
        }
        modifier(this._modifiers, TextAlignModifier, textAlignNum);
        return this 
    }
    lineHeight(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    textOverflow(value: { overflow: TextOverflow; }): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontFamily(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    maxLines(value: number): TextAttribute {
        throw new Error("Method not implemented.");
    }
    decoration(value: { type: TextDecorationType; color?: any; }): TextAttribute {
        throw new Error("Method not implemented.");
    }
    letterSpacing(value: string | number): TextAttribute {
        throw new Error("Method not implemented.");
    }
    textCase(value: TextCase): TextAttribute {
        throw new Error("Method not implemented.");
    }
    baselineOffset(value: string | number): TextAttribute {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): TextAttribute {
        throw new Error("Method not implemented.");
    }
    textShadow(value: ShadowOptions): TextAttribute {
        throw new Error("Method not implemented.");
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute {
        throw new Error("Method not implemented.");
    }
    textIndent(value: Length): TextAttribute {
        throw new Error("Method not implemented.");
    }
    wordBreak(value: WordBreak): TextAttribute {
        throw new Error("Method not implemented.");
    }
    onCopy(callback: (value: string) => void): TextAttribute {
        throw new Error("Method not implemented.");
    }
    selection(selectionStart: number, selectionEnd: number): TextAttribute {
        throw new Error("Method not implemented.");
    }
    ellipsisMode(value: EllipsisMode): TextAttribute {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Text.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkTextComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
