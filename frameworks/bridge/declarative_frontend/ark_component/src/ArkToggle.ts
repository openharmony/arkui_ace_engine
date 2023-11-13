//@ts-nocheck
class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    onChange(callback: (isOn: boolean) => void): ToggleAttribute {
        throw new Error("Method not implemented.");
    }
    selectedColor(value: ResourceColor): ToggleAttribute {
        throw new Error("Method not implemented.");
    }
    switchPointColor(color: ResourceColor): ToggleAttribute {
        throw new Error("Method not implemented.");
    }
}

globalThis.Toggle.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkToggleComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
