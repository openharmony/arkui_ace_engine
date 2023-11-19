
/// <reference path="./import.ts" />

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

// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, ()=> {
      return new ArkButtonComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
