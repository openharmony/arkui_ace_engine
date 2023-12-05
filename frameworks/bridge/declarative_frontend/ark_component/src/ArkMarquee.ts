/// <reference path='./import.ts' />
class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
  fontColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  fontSize(value: any): this {
    throw new Error('Method not implemented.');
  }
  allowScale(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  fontWeight(value: string | number | FontWeight): this {
    throw new Error('Method not implemented.');
  }
  fontFamily(value: any): this {
    throw new Error('Method not implemented.');
  }
  onStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBounce(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMarqueeComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
