/// <reference path="./import.ts" />
class ArkWindowSceneComponent extends ArkComponent implements WindowSceneAttribute {

}
// @ts-ignore
globalThis.WindowScene.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkWindowSceneComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
