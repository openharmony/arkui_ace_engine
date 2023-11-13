//@ts-nocheck
class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    color(value: ResourceColor): LoadingProgressAttribute {
        throw new Error("Method not implemented.");
    }
    enableLoading(value: boolean): LoadingProgressAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.LoadingProgress.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkLoadingProgressComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
