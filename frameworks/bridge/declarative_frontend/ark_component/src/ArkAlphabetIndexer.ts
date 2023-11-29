/// <reference path="./import.ts" />
class ArkAlphabetIndexerComponent extends ArkComponent implements AlphabetIndexerAttribute {
  onSelected(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  color(value: any): this {
    throw new Error('Method not implemented.');
  }
  selectedColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  popupColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  selectedBackgroundColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  popupBackground(value: any): this {
    throw new Error('Method not implemented.');
  }
  popupSelectedColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  popupUnselectedColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  popupItemBackgroundColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  usingPopup(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  selectedFont(value: Font): this {
    throw new Error('Method not implemented.');
  }
  popupFont(value: Font): this {
    throw new Error('Method not implemented.');
  }
  popupItemFont(value: Font): this {
    throw new Error('Method not implemented.');
  }
  itemSize(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  font(value: Font): this {
    throw new Error('Method not implemented.');
  }
  alignStyle(value: IndexerAlign, offset?: any): this {
    throw new Error('Method not implemented.');
  }
  onSelect(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onRequestPopupData(callback: (index: number) => string[]): AlphabetIndexerAttribute {
    throw new Error('Method not implemented.');
  }
  onPopupSelect(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  selected(index: number): this {
    throw new Error('Method not implemented.');
  }
  popupPosition(value: Position): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.AlphabetIndexer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkAlphabetIndexerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
