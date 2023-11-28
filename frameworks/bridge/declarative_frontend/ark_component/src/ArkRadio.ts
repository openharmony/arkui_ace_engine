/// <reference path="./import.ts" />

class ArkRadioComponent extends ArkComponent implements RadioAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    checked(value: boolean): this {
        if(!!value){
            modifier(this._modifiers, RadioCheckedModifier, value);
        } else {
            modifier(this._modifiers, RadioCheckedModifier, undefined);
        }
        return this;
    }
    onChange(callback: (isChecked: boolean) => void): this {
        throw new Error("Method not implemented.");
    }
    radioStyle(value: RadioStyle): this {
        let arkRadioStyle = new ArkRadioStyle();
        let getColor = new ArkColor();

        if (typeof value === "object") {      
            if (getColor.parseColorValue(value?.checkedBackgroundColor)){
                arkRadioStyle.checkedBackgroundColor = getColor.getColor();
            }

            if (getColor.parseColorValue(value?.uncheckedBorderColor)){
                arkRadioStyle.uncheckedBorderColor = getColor.getColor();
            }

            if (getColor.parseColorValue(value?.indicatorColor)){
                arkRadioStyle.indicatorColor = getColor.getColor();
            }

            modifier(this._modifiers, RadioStyleModifier, arkRadioStyle);
        } else {
            modifier(this._modifiers, RadioStyleModifier, undefined);
        }
        return this;
    }
}

class RadioCheckedModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("radioChecked");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().radio.resetRadioChecked(node);
        } else {
            GetUINativeModule().radio.setRadioChecked(node, this.value!);
        }
    }
}

class RadioStyleModifier extends Modifier<ArkRadioStyle> {
    static identity: Symbol = Symbol("radioStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().radio.resetRadioStyle(node);
        } else {
            GetUINativeModule().radio.setRadioStyle(node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor );
        }
    }
}
// @ts-ignore
globalThis.Radio.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkRadioComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
