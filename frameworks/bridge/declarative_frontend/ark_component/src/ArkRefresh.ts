
/// <reference path="./import.ts" />
class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    onStateChange(callback: (state: RefreshStatus) => void): this {
        throw new Error("Method not implemented.");
    }
    onRefreshing(callback: () => void): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkRefreshComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
