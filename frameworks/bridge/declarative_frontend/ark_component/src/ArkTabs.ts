/// <reference path="./import.ts" />
class ArkTabsComponent extends ArkComponent implements TabsAttribute {
    vertical(value: boolean): TabsAttribute {
        modifier(this._modifiers, VerticalModifier, value);
        return this;
    }
    barPosition(value: BarPosition): TabsAttribute {
        if (isNumber(value) && value >= BarPosition.Start && value < BarPosition.End) {
            modifier(this._modifiers, BarPositionModifier, value);
        } else {
            modifier(this._modifiers, BarPositionModifier, BarPosition.Start);
        }
        return this;
    }
    scrollable(value: boolean): TabsAttribute {
        modifier(this._modifiers, ScrollableModifier, isBoolean(value) ? value : true);
        return this;
    }
    barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute {
        let barMode: number;
        let arkBarMode: ArkBarMode = new ArkBarMode();
        let arkScrollableBarModeOptions: ArkScrollableBarModeOptions = new ArkScrollableBarModeOptions();
        arkScrollableBarModeOptions.value = options;
        arkBarMode.barMode = barMode;
        arkBarMode.options = arkScrollableBarModeOptions;

        modifier(this._modifiers, ScrollableBarModeOptionsModifier, arkBarMode.options);

        modifier(this._modifiers, TabBarModeModifier, arkBarMode);

        return this;
    }
    barWidth(value: Length): TabsAttribute {
        if (isUndefined(value) || isNull(value)) {
            return;
        }

        modifier(this._modifiers, BarWidthModifier, value.toString());

        return this;
    }
    barHeight(value: Length): TabsAttribute {
        if (isUndefined(value) || isNull(value)) {
            return;
        }

        let adaptiveHeight: boolean = false;

        modifier(this._modifiers, BarAdaptiveHeightModifier, adaptiveHeight);
        modifier(this._modifiers, BarHeightModifier, value.toString());

        return this;
    }
    animationDuration(value: number): TabsAttribute {
        let time: number = (isNumber(value) && value > 0) ? value : 300;
        modifier(this._modifiers, AnimationDurationModifier, time);
        return this;
    }
    onChange(event: (index: number) => void): TabsAttribute {
        throw new Error("Method not implemented.");
    }
    onTabBarClick(event: (index: number) => void): TabsAttribute {
        throw new Error("Method not implemented.");
    }
    fadingEdge(value: boolean): TabsAttribute {
        modifier(this._modifiers, FadingEdgeModifier, value);
        return this;
    }
    divider(value: DividerStyle | null): TabsAttribute {
        let arkDrivider = new ArkDivider();
        if (!value) {
            arkDrivider.value.strokeWidth = undefined;
            arkDrivider.value.color = undefined;
            arkDrivider.value.startMargin = undefined;
            arkDrivider.value.endMargin = undefined;
        }

        modifier(this._modifiers, DividerModifier, arkDrivider);

        return this;
    }
    barOverlap(value: boolean): TabsAttribute {
        modifier(this._modifiers, BarOverlapModifier, value);
        return this;
    }
    barBackgroundColor(value: ResourceColor): TabsAttribute {
        let arkBarBackgroundColor = new ArkBarBackgroundColor();
        arkBarBackgroundColor.value = value;
        modifier(this._modifiers, BarBackgroundColorModifier, arkBarBackgroundColor);

        return this;
    }
    barGridAlign(value: BarGridColumnOptions): TabsAttribute {
        let arkBarGridAlign = new ArkBarGridAlign();
        if (isObject(value)) {

            modifier(this._modifiers, BarGridAlignModifier, arkBarGridAlign);
        }

        return this;
    }
}

class BarGridAlignModifier extends Modifier<ArkBarGridAlign> {
    static identity: Symbol = Symbol("barGridAlign");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarGridAlign(node);
        } else {
            GetUINativeModule().tabs.setBarGridAlign(node, this.value);
        }
    }
}

class DividerModifier extends Modifier<ArkDivider> {
    static identity: Symbol = Symbol("Divider");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetDivider(node);
        } else {
            GetUINativeModule().tabs.setDivider(node, this.value);
        }
    }
}

class BarWidthModifier extends Modifier<string> {
    static identity: Symbol = Symbol("barWidth");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarWidth(node);
        } else {
            GetUINativeModule().tabs.setBarWidth(node, this.value);
        }
    }
}

class BarAdaptiveHeightModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("barAdaptiveHeight");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarAdaptiveHeight(node);
        } else {
            GetUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
        }
    }
}

class BarHeightModifier extends Modifier<string> {
    static identity: Symbol = Symbol("barHeight");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarHeight(node);
        } else {
            GetUINativeModule().tabs.setBarHeight(node, this.value);
        }
    }
}

class BarOverlapModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("barOverlap");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarOverlap(node);
        } else {
            GetUINativeModule().tabs.setBarOverlap(node, this.value);
        }
    }
}

class VerticalModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("vertical");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetVertical(node);
        } else {
            GetUINativeModule().tabs.setVertical(node, this.value);
        }
    }
}

class AnimationDurationModifier extends Modifier<number> {
    static identity: Symbol = Symbol("animationduration");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetAnimationDuration(node);
        } else {
            GetUINativeModule().tabs.setAnimationDuration(node, this.value);
        }
    }
}

class ScrollableModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("scrollable");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetScrollable(node);
        } else {
            GetUINativeModule().tabs.setScrollable(node, this.value);
        }
    }
}

class TabBarModeModifier extends Modifier<ArkBarMode> {
    static identity: Symbol = Symbol("tabsbarMode");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetTabBarMode(node);
        } else {
            GetUINativeModule().tabs.setTabBarMode(node, this.value);
        }
    }
}

class BarPositionModifier extends Modifier<number> {
    static identity: Symbol = Symbol("barPosition");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarPosition(node);
        } else {
            GetUINativeModule().tabs.setBarPosition(node, this.value);
        }
    }
}

class TabsHideTitleBarModifier extends Modifier<string> {
    static identity: Symbol = Symbol("hideTitleBar");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetHideTitleBar(node);
        } else {
            GetUINativeModule().tabs.setHideTitleBar(node, this.value);
        }
    }
}

class BarBackgroundColorModifier extends Modifier<ArkBarBackgroundColor> {
    static identity: Symbol = Symbol("barbackgroundcolor");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetBarBackgroundColor(node);
        } else {
            GetUINativeModule().tabs.setBarBackgroundColor(node, this.value);
        }
    }
}

class FadingEdgeModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("fadingedge");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetFadingEdge(node);
        } else {
            GetUINativeModule().tabs.setFadingEdge(node, this.value);
        }
    }
}

class ScrollableBarModeOptionsModifier extends Modifier<ArkScrollableBarModeOptions> {
    static identity: Symbol = Symbol("tabsscrollableBarModeOptions");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().tabs.resetScrollableBarModeOptions(node);
        } else {
            GetUINativeModule().tabs.setScrollableBarModeOptions(node, this.value["margin"], this.value["nonScrollableLayoutStyle"]);
        }
    }
}

// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTabsComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
