/// <reference path="./import.ts" />
class ArkTextPickerComponent extends ArkComponent implements TextPickerAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    defaultPickerItemHeight(value: string | number): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, value);
        }
        return this;
    }
    canLoop(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, TextpickerCanLoopModifier, value);
        } else {
            modifier(this._modifiers, TextpickerCanLoopModifier, undefined);
        }
        return this;
    }
    disappearTextStyle(value: PickerTextStyle): this {
        let disappearTextStyle = new ArkTextStyle();
        if (isObject(value)) {
            disappearTextStyle.parseTextStyle(value, '#ff182431', '14fp', 'Regular');
            modifier(this._modifiers, TextpickerDisappearTextStyleModifier, disappearTextStyle);
        } else {
            modifier(this._modifiers, TextpickerDisappearTextStyleModifier, undefined);
        }
        return this;
    }
    textStyle(value: PickerTextStyle): this {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff182431', '16fp', 'Regular');
            modifier(this._modifiers, TextpickerTextStyleModifier, textStyle);
        } else {
            modifier(this._modifiers, TextpickerTextStyleModifier, undefined);
        }
        return this;
    }
    selectedTextStyle(value: PickerTextStyle): this {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff007dff', '20vp', 'Medium');
            modifier(this._modifiers, TextpickerSelectedTextStyleModifier, textStyle);
        } else {
            modifier(this._modifiers, TextpickerSelectedTextStyleModifier, undefined);
        }
        return this;
    }
    onAccept(callback: (value: string, index: number) => void): this {
        throw new Error("Method not implemented.");
    }
    onCancel(callback: () => void): this {
        throw new Error("Method not implemented.");
    }
    onChange(callback: (value: string | string[], index: number | number[]) => void): this {
        throw new Error("Method not implemented.");
    }
    selectedIndex(value: number | number[]): this {
        let input = new ArkSelectedIndices();

        if (!Array.isArray(value)) {
            if (!isNumber(value)) {
                modifier(this._modifiers, TextpickerSelectedIndexModifier, undefined);
                return this;
            }
            input.selectedValues[0] = value;
        } else {
            input.selectedValues = value;
        }

        modifier(this._modifiers, TextpickerSelectedIndexModifier, input);
        return this;
    }
}

// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, ()=> {
      return new ArkTextPickerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

class TextpickerCanLoopModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("textpickerCanLoop");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetCanLoop(node);
        }
        else {
            GetUINativeModule().textpicker.setCanLoop(node, this.value);
        }
    }
}

class TextpickerSelectedIndexModifier extends Modifier<ArkSelectedIndices> {
    static identity: Symbol = Symbol("textpickerSelectedIndex");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetSelectedIndex(node);
        }
        else {
            GetUINativeModule().textpicker.setSelectedIndex(node, this.value.selectedValues);
        }
    }
}

class TextpickerTextStyleModifier extends Modifier<ArkTextStyle> {
    static identity: Symbol = Symbol("textpickerTextStyle");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setTextStyle(node,
                this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
        }
    }
}

class TextpickerSelectedTextStyleModifier extends Modifier<ArkTextStyle> {
    static identity: Symbol = Symbol("textpickerSelectedTextStyle");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetSelectedTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setSelectedTextStyle(node,
                this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
        }
    }
}

class TextpickerDefaultPickerItemHeightModifier extends Modifier<number|string> {
    static identity: Symbol = Symbol("textpickerDefaultPickerItemHeight");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
        }
        else {
            GetUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
        }
    }
}

class TextpickerDisappearTextStyleModifier extends Modifier<ArkTextStyle> {
    static identity: Symbol = Symbol("textpickerDisappearTextStyle");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().textpicker.resetDisappearTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setDisappearTextStyle(node, 
                this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
        }
    }
}