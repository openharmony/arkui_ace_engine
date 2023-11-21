
/// <reference path="./import.ts" />
class ArkStackComponent extends ArkComponent implements StackAttribute {
    alignContent(value: Alignment): StackAttribute {
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
