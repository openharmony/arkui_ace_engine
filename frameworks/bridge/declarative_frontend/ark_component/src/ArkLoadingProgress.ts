
/// <reference path="./import.ts" />
class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    color(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    enableLoading(value: boolean): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkLoadingProgressComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
