//@ts-nocheck
class ArkStackComponent extends ArkComponent implements StackAttribute {
    alignContent(value: Alignment): StackAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.Stack.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkStackComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
