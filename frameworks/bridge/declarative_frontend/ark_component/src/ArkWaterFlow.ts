/// <reference path='./import.ts' />
class ArkWaterFlowComponent extends ArkComponent implements WaterFlowAttribute {
  columnsTemplate(value: string): this {
    throw new Error('Method not implemented.');
  }
  itemConstraintSize(value: ConstraintSizeOptions): this {
    throw new Error('Method not implemented.');
  }
  rowsTemplate(value: string): this {
    throw new Error('Method not implemented.');
  }
  columnsGap(value: any): this {
    throw new Error('Method not implemented.');
  }
  rowsGap(value: any): this {
    throw new Error('Method not implemented.');
  }
  layoutDirection(value: FlexDirection): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: NestedScrollOptions): this {
    throw new Error('Method not implemented.');
  }
  enableScrollInteraction(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  friction(value: any): this {
    throw new Error('Method not implemented.');
  }
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  onReachStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWaterFlowComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
