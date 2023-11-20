
/// <reference path="./import.ts" />
class ArkTextComponent extends ArkComponent implements TextAttribute {
    font(value: Font): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontSize(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    minFontSize(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    maxFontSize(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): TextAttribute {
        throw new Error("Method not implemented.");
    }
    fontWeight(value: any): TextAttribute {
        throw new Error("Method not implemented.");
    }
    textAlign(value: TextAlign): TextAttribute {
        throw new Error("Method not implemented.");
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
