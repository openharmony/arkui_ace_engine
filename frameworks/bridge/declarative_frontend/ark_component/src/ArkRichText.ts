/// <reference path="./import.ts" />
class ArkRichTextComponent extends ArkComponent implements CommonMethod<RichTextAttribute> {
  onStart(callback: () => void): RichTextAttribute {
    throw new Error('Method not implemented.');
  }
  onComplete(callback: () => void): RichTextAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): RichTextAttribute {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.RichText.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRichTextComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();

}