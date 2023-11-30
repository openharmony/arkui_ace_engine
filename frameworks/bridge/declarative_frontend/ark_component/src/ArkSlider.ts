/// <reference path="./import.ts" />

class ArkSliderComponent extends ArkComponent implements SliderAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    blockColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BlockColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, BlockColorModifier, undefined);
        }
        return this;
    }
    trackColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TrackColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, TrackColorModifier, undefined);
        }
        return this;
    }
    selectedColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, SelectColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, SelectColorModifier, undefined);
        }
        return this;
    }
    minLabel(value: string): this {
        throw new Error("Method not implemented.");
    }
    maxLabel(value: string): this {
        throw new Error("Method not implemented.");
    }
    showSteps(value: boolean): this {
        let showSteps = false;
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowStepsModifier, value);
        } else {
            modifier(this._modifiers, ShowStepsModifier, showSteps);
        }
        return this;;
    }
    showTips(value: boolean, content?: any): this {
        let showTips = new ArkSliderTips();
        if(typeof value === "boolean") {
            showTips.showTip = value;
        }
        if(typeof content === "string") {
            showTips.tipText = content;
        }
        modifier(this._modifiers, ShowTipsModifier, showTips);
        return this;
    }
    trackThickness(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TrackThicknessModifier, undefined);
        } else {
            modifier(this._modifiers, TrackThicknessModifier, value);
        }
        return this;
    }
    onChange(callback: (value: number, mode: SliderChangeMode) => void): this {
        throw new Error("Method not implemented.");
    }
    blockBorderColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BlockBorderColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, BlockBorderColorModifier, undefined);
        }
        return this;
    }
    blockBorderWidth(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, BlockBorderWidthModifier, undefined);
        } else {
            modifier(this._modifiers, BlockBorderWidthModifier, value);
        }
        return this;
    }
    stepColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, StepColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, StepColorModifier, undefined);
        }
        return this;
    }
    trackBorderRadius(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TrackBorderRadiusModifier, undefined);
        } else {
            modifier(this._modifiers, TrackBorderRadiusModifier, value);
        }
        return this;
    }
    blockSize(value: SizeOptions): this {
        if (!value || (!!value?.width && typeof value?.width != "number" && typeof value?.width != "string") ||
            (!!value?.height && typeof value?.height != "number" && typeof value?.height != "string")) {
            modifier(this._modifiers, BlockSizeModifier, undefined);
        } else {
            let blockSize = new ArkBlockSize()
            blockSize.width = value?.width
            blockSize.height = value?.height
            modifier(this._modifiers, BlockSizeModifier, blockSize);
        }
        return this;
    }
    blockStyle(value: SliderBlockStyle): this {
        modifierWithKey(this._modifiersWithKeys, BlockStyleModifier.identity, BlockStyleModifier, value);
        return this
    }
    stepSize(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, StepSizeModifier, undefined);
        } else {
            modifier(this._modifiers, StepSizeModifier, value);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, ()=> {
      return new ArkSliderComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

class BlockStyleModifier extends ModifierWithKey<boolean | object> {
    static identity: Symbol = Symbol("sliderBlockStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().slider.resetBlockStyle(node);
        }
        else {
            GetUINativeModule().slider.setBlockStyle(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        return false;
    }
}

class ShowTipsModifier extends Modifier<ArkSliderTips> {
    static identity: Symbol = Symbol("sliderShowTips");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetShowTips(node);
        }
        else {
            GetUINativeModule().slider.setShowTips(node, this.value.showTip, this.value?.tipText);
        }
    }
}

class StepSizeModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("sliderStepSize");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetStepSize(node);
        }
        else {
            GetUINativeModule().slider.setStepSize(node, this.value);
        }
    }
}

class BlockSizeModifier extends Modifier<ArkBlockSize> {
    static identity: Symbol = Symbol("sliderBlockSize");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetBlockSize(node);
        }
        else {
            GetUINativeModule().slider.setBlockSize(node, this.value.width, this.value.height);
        }
    }
}

class TrackBorderRadiusModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("sliderTrackBorderRadius");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetTrackBorderRadius(node);
        }
        else {
            GetUINativeModule().slider.setTrackBorderRadius(node, this.value);
        }
    }
}

class StepColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("sliderStepColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetStepColor(node);
        }
        else {
            GetUINativeModule().slider.setStepColor(node, this.value);
        }
    }
}

class BlockBorderColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("sliderBlockBorderColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetBlockBorderColor(node);
        }
        else {
            GetUINativeModule().slider.setBlockBorderColor(node, this.value);
        }
    }
}

class BlockBorderWidthModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("sliderBlockBorderWidth");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetBlockBorderWidth(node);
        }
        else {
            GetUINativeModule().slider.setBlockBorderWidth(node, this.value);
        }
    }
}

class BlockColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("sliderBlockColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetBlockColor(node);
        }
        else {
            GetUINativeModule().slider.setBlockColor(node, this.value);
        }
    }
}

class TrackColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("sliderTrackColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetTrackBackgroundColor(node);
        }
        else {
            GetUINativeModule().slider.setTrackBackgroundColor(node, this.value);
        }
    }
}

class SelectColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("sliderSelectColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetSelectColor(node);
        }
        else {
            GetUINativeModule().slider.setSelectColor(node, this.value);
        }
    }
}

class ShowStepsModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("sliderShowSteps");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetShowSteps(node);
        }
        else {
            GetUINativeModule().slider.setShowSteps(node, this.value);
        }
    }
}

class TrackThicknessModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("sliderTrackThickness");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().slider.resetThickness(node);
        }
        else {
            GetUINativeModule().slider.setThickness(node, this.value);
        }
    }
}