
/// <reference path="./import.ts" />
class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    color(value: ResourceColor): LoadingProgressAttribute {
        throw new Error("Method not implemented.");
    }
    enableLoading(value: boolean): LoadingProgressAttribute {
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
