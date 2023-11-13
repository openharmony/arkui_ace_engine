//@ts-nocheck
class ArkTextInputComponent extends ArkComponent implements TextInputAttribute {
    type(value: InputType): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    placeholderColor(value: ResourceColor): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value?: any): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    enterKeyType(value: EnterKeyType): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    caretColor(value: ResourceColor): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onEditChanged(callback: (isEditing: boolean) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback: (isEditing: boolean) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onSubmit(callback: (enterKey: EnterKeyType) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onChange(callback: (value: string) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    maxLength(value: number): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    fontSize(value: Length): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    fontWeight(value: any): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    fontFamily(value: ResourceStr): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    inputFilter(value: ResourceStr, error?: ((value: string) => void) | undefined): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onCopy(callback: (value: string) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onCut(callback: (value: string) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    onPaste(callback: (value: string) => void): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    showPasswordIcon(value: boolean): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    textAlign(value: TextAlign): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    style(value: any): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    caretStyle(value: CaretStyle): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    selectedBackgroundColor(value: ResourceColor): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    caretPosition(value: number): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    enableKeyboardOnFocus(value: boolean): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    passwordIcon(value: PasswordIcon): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    showError(value?: string | undefined): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    showUnit(value: CustomBuilder): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    showUnderline(value: boolean): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value: boolean): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    barState(value: BarState): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    maxLines(value: number): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
    customKeyboard(value: CustomBuilder): TextInputAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.TextInput.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkTextInputComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
