
/// <reference path="./import.ts" />
class ArkTextAreaComponent extends ArkComponent implements TextAreaAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    type(value: TextAreaType): this{
        throw new Error("Method not implemented.");
    }
    placeholderColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value: Font): this {
        throw new Error("Method not implemented.");
    }
    textAlign(value: TextAlign): this {
        throw new Error("Method not implemented.");
    }
    caretColor(value: ResourceColor): this {
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
    onChange(callback: (value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): this {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): this {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback: (isEditing: boolean) => void): this {
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
    enableKeyboardOnFocus(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    maxLength(value: number): this {
        throw new Error("Method not implemented.");
    }
    showCounter(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    style(value: TextContentStyle): this {
        throw new Error("Method not implemented.");
    }
    barState(value: BarState): this {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value: boolean): this {
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
globalThis.TextArea.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkTextAreaComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
