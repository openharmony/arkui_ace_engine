
/// <reference path="./import.ts" />
class ArkStackComponent extends ArkComponent implements StackAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    alignContent(value: Alignment): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Stack.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkStackComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
