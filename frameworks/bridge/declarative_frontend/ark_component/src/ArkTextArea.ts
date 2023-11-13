//@ts-nocheck
class ArkTextAreaComponent extends ArkComponent implements TextAreaAttribute {
    placeholderColor(value: ResourceColor): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value: Font): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    textAlign(value: TextAlign): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    caretColor(value: ResourceColor): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    fontSize(value: Length): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    fontWeight(value: any): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    fontFamily(value: ResourceStr): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    inputFilter(value: ResourceStr, error?: ((value: string) => void) | undefined): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onChange(callback: (value: string) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback: (isEditing: boolean) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onCopy(callback: (value: string) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onCut(callback: (value: string) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    onPaste(callback: (value: string) => void): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    enableKeyboardOnFocus(value: boolean): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    maxLength(value: number): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    showCounter(value: boolean): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    style(value: TextContentStyle): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    barState(value: BarState): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value: boolean): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    maxLines(value: number): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
    customKeyboard(value: CustomBuilder): TextAreaAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.TextArea.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkTextAreaComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
