
/// <reference path="./import.ts" />
class ArkTextInputComponent extends ArkComponent implements TextInputAttribute {
    cancelButton(value: { style?: CancelButtonStyle; icon?: IconOptions; }): this {
        throw new Error("Method not implemented.");
    }
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    selectAll(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    enableAutoFill(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    passwordRules(value: string): this {
        throw new Error("Method not implemented.");
    }
    showCounter(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    type(value: InputType): this {
        throw new Error("Method not implemented.");
    }
    placeholderColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value?: any): this {
        throw new Error("Method not implemented.");
    }
    enterKeyType(value: EnterKeyType): this {
        throw new Error("Method not implemented.");
    }
    caretColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    onEditChanged(callback: (isEditing: boolean) => void): this {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback: (isEditing: boolean) => void): this {
        throw new Error("Method not implemented.");
    }
    onSubmit(callback: (enterKey: EnterKeyType) => void): this {
        throw new Error("Method not implemented.");
    }
    onChange(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): this {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): this {
        throw new Error("Method not implemented.");
    }
    maxLength(value: number): this {
        throw new Error("Method not implemented.");
    }
    fontColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    fontSize(value: Length): this {
        throw new Error("Method not implemented.");
    }
    fontStyle(value: FontStyle): this {
        throw new Error("Method not implemented.");
    }
    fontWeight(value: any): this {
        throw new Error("Method not implemented.");
    }
    fontFamily(value: ResourceStr): this {
        throw new Error("Method not implemented.");
    }
    inputFilter(value: ResourceStr, error?: ((value: string) => void) | undefined): this {
        throw new Error("Method not implemented.");
    }
    onCopy(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    onCut(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    onPaste(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): this {
        throw new Error("Method not implemented.");
    }
    showPasswordIcon(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    textAlign(value: TextAlign): this {
        throw new Error("Method not implemented.");
    }
    style(value: any): this {
        throw new Error("Method not implemented.");
    }
    caretStyle(value: CaretStyle): this {
        throw new Error("Method not implemented.");
    }
    selectedBackgroundColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    caretPosition(value: number): this {
        throw new Error("Method not implemented.");
    }
    enableKeyboardOnFocus(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    passwordIcon(value: PasswordIcon): this {
        throw new Error("Method not implemented.");
    }
    showError(value?: string | undefined): this {
        throw new Error("Method not implemented.");
    }
    showUnit(value: CustomBuilder): this {
        throw new Error("Method not implemented.");
    }
    showUnderline(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    barState(value: BarState): this {
        throw new Error("Method not implemented.");
    }
    maxLines(value: number): this {
        throw new Error("Method not implemented.");
    }
    customKeyboard(value: CustomBuilder): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkTextInputComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
