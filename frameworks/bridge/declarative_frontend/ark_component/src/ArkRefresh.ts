//@ts-nocheck
class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
    onStateChange(callback: (state: RefreshStatus) => void): RefreshAttribute {
        throw new Error("Method not implemented.");
    }
    onRefreshing(callback: () => void): RefreshAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.Refresh.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkRefreshComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
