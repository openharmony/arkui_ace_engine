/// <reference path="./import.ts" />
class ArkCounterComponent extends ArkComponent implements CounterAttribute {
    constructor(nativePtr: KNode) {
      super(nativePtr);
    }
    onInc(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    onDec(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    enableDec(value: boolean): this {
        if (isBoolean(value)) {
            modifier(this._modifiers, EnableDecModifier, value);
        } else {
            modifier(this._modifiers, EnableDecModifier, undefined);
        }
        return this;
    }
    enableInc(value: boolean): this {
        if (isBoolean(value)) {
            modifier(this._modifiers, EnableIncModifier, value);
        } else {
            modifier(this._modifiers, EnableIncModifier, undefined);
        }
        return this;
    }
}
class EnableIncModifier extends Modifier<boolean> {
    constructor(value: boolean) {
      super(value);
    }
    static identity = Symbol("enableInc");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().counter.resetEnableInc(node);
        }
        else {
            GetUINativeModule().counter.setEnableInc(node, this.value);
        }
    }
}
class EnableDecModifier extends Modifier<boolean> {
    constructor(value: boolean) {
      super(value);
    }
    static identity = Symbol("enableDec");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().counter.resetEnableDec(node);
        }
        else {
            GetUINativeModule().counter.setEnableDec(node, this.value);
        }
    }
}

// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCounterComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
