/// <reference path="./import.ts" />
class ArkSelectComponent extends ArkComponent implements SelectAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    optionWidth(value: Dimension | OptionWidthMode ): this {
        throw new Error("Method not implemented.");
    }
    optionHeight(value: Dimension): this {
        throw new Error("Method not implemented.");
    }
    selected(value: number | Resource): this {
        if (typeof value === "number") {
            modifier(this._modifiers, SelectedModifier, value);
        } else {
            modifier(this._modifiers, SelectedModifier, undefined);
        }
        return this;
    }
    value(value: ResourceStr): this {
        if (typeof value === "string") {
            modifier(this._modifiers, ValueModifier, value);
        } else {
            modifier(this._modifiers, ValueModifier, undefined);
        }
        return this;
    }
    font(value: Font): this {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family)
            font.setStyle(value.style)
            modifier(this._modifiers, FontModifier, font);
        } else {
            modifier(this._modifiers, FontModifier, undefined);
        }
        return this;
    }
    fontColor(value: ResourceColor): this {
        if( isResource(value)  || isUndefined(value)) {
            modifier(this._modifiers, SelectFontColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#E6FFFFFF");
        }
        modifier(this._modifiers, SelectFontColorModifier, arkColor.color);
        return this;
    }
    selectedOptionBgColor(value: ResourceColor): this {
        if( isResource(value)  || isUndefined(value)) {
            modifier(this._modifiers, SelectedOptionBgColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#33007DFF");
        }
        modifier(this._modifiers, SelectedOptionBgColorModifier, arkColor.color);        
        return this;
    }
    selectedOptionFont(value: Font): this {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family)
            font.setStyle(value.style)
            modifier(this._modifiers, SelectedOptionFontModifier, font);
        } else {
            modifier(this._modifiers, SelectedOptionFontModifier, undefined);
        }
        return this;
    }
    selectedOptionFontColor(value: ResourceColor): this {  
        if( isResource(value)  || isUndefined(value)) {
            modifier(this._modifiers, SelectedOptionFontColorModifier, undefined);
            return this;
        }     
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {            
            arkColor.parseColorValue("#ff007dff")
        }
        modifier(this._modifiers, SelectedOptionFontColorModifier, arkColor.color);
        return this;
    }
    optionBgColor(value: ResourceColor): this {
        if( isResource(value)  || isUndefined(value)) {
            modifier(this._modifiers, OptionBgColorModifier, undefined);
            return this;
        }  
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#ffffffff");
        }
        modifier(this._modifiers, OptionBgColorModifier, arkColor.color);
        return this;
    }
    optionFont(value: Font): this {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family)
            font.setStyle(value.style)
            modifier(this._modifiers, OptionFontModifier, font);
        } else {
            modifier(this._modifiers, OptionFontModifier, undefined);
        }
        return this;
    }
    optionFontColor(value: ResourceColor): this {

        if( isResource(value)  || isUndefined(value)) {
            modifier(this._modifiers, OptionFontColorModifier, undefined);
            return this;
        }  
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#ffffffff");
        } 
        modifier(this._modifiers, OptionFontColorModifier, arkColor.color);
        return this;
    }
    onSelect(callback: (index: number, value: string) => void): this {
        throw new Error("Method not implemented.");
    }
    space(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, SpaceModifier, undefined);
        }
        else {
            modifier(this._modifiers, SpaceModifier, value);
        }
        return this;
    }
    arrowPosition(value: ArrowPosition): this {
        if (isNumber(value)) {
            modifier(this._modifiers, ArrowPositionModifier, value);
        } else {
            modifier(this._modifiers, ArrowPositionModifier, undefined);
        }
        return this;
    }
    menuAlign(alignType: MenuAlignType, offset?: any): this {
        let menuAlignType = new ArkMenuAlignType();
        if (isNumber(alignType)) {
            menuAlignType.alignType = alignType;
            if (typeof offset === "object") {
                menuAlignType.dx = offset.dx;
                menuAlignType.dy = offset.dy;
            }
            modifier(this._modifiers, MenuAlignModifier, menuAlignType);
        } else {
            modifier(this._modifiers, MenuAlignModifier, undefined);
        }
        return this;
    }
}

// @ts-ignore
globalThis.Select.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkSelectComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

class FontModifier extends Modifier<ArkFont> {
    static identity: Symbol = Symbol("selectFont");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetFont(node);
        }
        else {
            GetUINativeModule().select.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}

class OptionFontModifier extends Modifier<ArkFont> {
    static identity: Symbol = Symbol("selectOptionFont");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetOptionFont(node);
        }
        else {
            GetUINativeModule().select.setOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}

class SelectedOptionFontModifier extends Modifier<ArkFont> {
    static identity: Symbol = Symbol("selectSelectedOptionFont");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionFont(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}

class MenuAlignModifier extends Modifier<ArkMenuAlignType> {
    static identity: Symbol = Symbol("selectMenuAlign");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetMenuAlign(node);
        }
        else {
            GetUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
        }
    }
}

class ArrowPositionModifier extends Modifier<number> {
    static identity: Symbol = Symbol("selectArrowPosition");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetArrowPosition(node);
        }
        else {
            GetUINativeModule().select.setArrowPosition(node, this.value);
        }
    }
}
class SpaceModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("selectSpace");
    
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetSpace(node);
        }
        else {
            GetUINativeModule().select.setSpace(node, this.value);
        }
    }
}
class ValueModifier extends Modifier<string> {
    static identity: Symbol = Symbol("selectValue");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetValue(node);
        }
        else {
            GetUINativeModule().select.setValue(node, this.value);
        }
    }
}
class SelectedModifier extends Modifier<number> {
    static identity: Symbol = Symbol("selectSelected");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetSelected(node);
        }
        else {
            GetUINativeModule().select.setSelected(node, this.value);
        }
    }
}
class SelectFontColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("selectFontColor");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetFontColor(node);
        }
        else {
            GetUINativeModule().select.setFontColor(node, this.value);
        }
    }
}
class SelectedOptionBgColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("selectSelectedOptionBgColor");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionBgColor(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionBgColor(node, this.value);
        }
    }
}
class OptionBgColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("selectOptionBgColor");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetOptionBgColor(node);
        }
        else {
            GetUINativeModule().select.setOptionBgColor(node, this.value);
        }
    }
}
class OptionFontColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("selectOptionFontColor");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetOptionFontColor(node);
        }
        else {
            GetUINativeModule().select.setOptionFontColor(node, this.value);
        }
    }
}
class SelectedOptionFontColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("selectSelectedOptionFontColor");

    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionFontColor(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionFontColor(node, this.value);
        }
    }
}