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
    enableDataDetector(enable: boolean): this {
        throw new Error("Method not implemented.");
    }
    dataDetectorConfig(config: any): this {
        throw new Error("Method not implemented.");
    }
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    font(value: Font): this {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): this {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, FontColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, FontColorModifier, undefined);
        }
        return this;
    }
    fontSize(value: any): this {
        if (!isNumber(value) && !isString(value)) {
            modifier(this._modifiers, FontSizeModifier, undefined);
        }
        else {
            modifier(this._modifiers, FontSizeModifier, value);
        }
        return this;
    }
    minFontSize(value: any): this {
        throw new Error("Method not implemented.");
    }
    maxFontSize(value: any): this {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): this {      
        if(isNumber(value)){
            modifier(this._modifiers, FontStyleModifier, value);
        }
        return this;
    }
    fontWeight(value: any): this {
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
    textAlign(value: TextAlign): this {
        let textAlignNum = 0
        if(isNumber(value)){
            textAlignNum = value
        }
        modifier(this._modifiers, TextAlignModifier, textAlignNum);
        return this 
    }
    lineHeight(value: any): this {
        throw new Error("Method not implemented.");
    }
    textOverflow(value: { overflow: TextOverflow; }): this {
        throw new Error("Method not implemented.");
    }
    fontFamily(value: any): this {
        throw new Error("Method not implemented.");
    }
    maxLines(value: number): this {
        throw new Error("Method not implemented.");
    }
    decoration(value: { type: TextDecorationType; color?: any; }): this {
        throw new Error("Method not implemented.");
    }
    letterSpacing(value: string | number): this {
        throw new Error("Method not implemented.");
    }
    textCase(value: TextCase): this {
        throw new Error("Method not implemented.");
    }
    baselineOffset(value: string | number): this {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): this {
        throw new Error("Method not implemented.");
    }
    textShadow(value: ShadowOptions): this {
        throw new Error("Method not implemented.");
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        throw new Error("Method not implemented.");
    }
    textIndent(value: Length): this {
        throw new Error("Method not implemented.");
    }
    wordBreak(value: WordBreak): this {
        throw new Error("Method not implemented.");
    }
    onCopy(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    selection(selectionStart: number, selectionEnd: number): this {
        throw new Error("Method not implemented.");
    }
    ellipsisMode(value: EllipsisMode): this {
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
