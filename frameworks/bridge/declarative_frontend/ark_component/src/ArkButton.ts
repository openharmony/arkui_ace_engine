//@ts-nocheck
class ArkButtonComponent extends ArkComponent implements  ButtonAttribute {
  type (value: ButtonType): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  stateEffect(value: boolean): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  fontColor(value: ResourceColor): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  fontSize(value: Length): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  fontWeight(value: string | number | FontWeight): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  fontStyle(value: FontStyle): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  fontFamily(value: string | Resource): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
  labelStyle(value: LabelStyle): ButtonAttribute {
    throw new Error("Method not implemented.");
  }
}
globalThis.Button.attributeModifier = (modifier) => {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);

    if (thisViewPu.length !== 0) {
        var viewPu = thisViewPu[thisViewPu.length - 1];
        var component = viewPu.getOrCreateArkComponent(elmtId, (nativePtr)=>new ArkButtonComponent(nativePtr), nativeNode);
        modifier.applyNormalAttribute(component);
        component.applyModifierPatch();
    }
}