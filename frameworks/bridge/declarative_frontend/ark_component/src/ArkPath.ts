/// <reference path='./import.ts' />
class ArkPathComponent extends ArkComponent implements PathAttribute {
  commands(value: string): this {
    throw new Error('Method not implemented.');
  }
  stroke(value: any): this {
    throw new Error('Method not implemented.');
  }
  fill(value: any): this {
    throw new Error('Method not implemented.');
  }
  strokeDashOffset(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  strokeLineCap(value: LineCapStyle): this {
    throw new Error('Method not implemented.');
  }
  strokeLineJoin(value: LineJoinStyle): this {
    throw new Error('Method not implemented.');
  }
  strokeMiterLimit(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  strokeOpacity(value: any): this {
    throw new Error('Method not implemented.');
  }
  fillOpacity(value: any): this {
    throw new Error('Method not implemented.');
  }
  strokeWidth(value: any): this {
    throw new Error('Method not implemented.');
  }
  antiAlias(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  strokeDashArray(value: any[]): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Path.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPathComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
