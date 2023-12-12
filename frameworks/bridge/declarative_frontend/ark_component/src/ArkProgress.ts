/// <reference path='./import.ts' />
class ArkProgressComponent extends ArkComponent implements ProgressAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  value(value: number): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    throw new Error('Method not implemented.');
  }
  color(value: any): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    throw new Error('Method not implemented.');
  }
  style(value: LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkProgressComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
