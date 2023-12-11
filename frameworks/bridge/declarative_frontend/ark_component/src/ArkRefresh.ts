
/// <reference path='./import.ts' />
class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  onStateChange(callback: (state: RefreshStatus) => void): this {
    throw new Error('Method not implemented.');
  }
  onRefreshing(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRefreshComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
