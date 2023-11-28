/// <reference path="./import.ts" />
class ArkSearchComponent extends ArkComponent implements SearchAttribute {
  searchButton(value: string, option?: SearchButtonOptions | undefined): this {
    throw new Error("Method not implemented.");
  }
  fontColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  searchIcon(value: IconOptions): this {
    throw new Error("Method not implemented.");
  }
  cancelButton(value: { style?: CancelButtonStyle | undefined; icon?: IconOptions | undefined; }): this {
    throw new Error("Method not implemented.");
  }
  caretStyle(value: CaretStyle): this {
    throw new Error("Method not implemented.");
  }
  placeholderColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  placeholderFont(value?: Font | undefined): this {
    throw new Error("Method not implemented.");
  }
  textFont(value?: Font | undefined): this {
    throw new Error("Method not implemented.");
  }
  onSubmit(callback: (value: string) => void): this {
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
  maxLength(value: number): this {
    throw new Error("Method not implemented.");
  }
  textAlign(value: TextAlign): this {
    throw new Error("Method not implemented.");
  }
  enableKeyboardOnFocus(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  selectionMenuHidden(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  customKeyboard(value: CustomBuilder): this {
    throw new Error("Method not implemented.");
  }
  type(value: SearchType): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Search.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkSearchComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
