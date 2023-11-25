/// <reference path="./import.ts" />
class ArkPanelComponent extends ArkComponent implements PanelAttribute {
    mode(value: PanelMode): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    type(value: PanelType): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    dragBar(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, DragBarModifier, value);
        } else {
            modifier(this._modifiers, DragBarModifier, undefined);
        }
        return this;
    }
    customHeight(value: any): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    fullHeight(value: string | number): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    halfHeight(value: string | number): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    miniHeight(value: string | number): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    show(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowModifier, value);
        } else {
            modifier(this._modifiers, ShowModifier, undefined);
        }
        return this;
    }
    backgroundMask(color: ResourceColor): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    showCloseIcon(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowCloseIconModifier, value);
        } else {
            modifier(this._modifiers, ShowCloseIconModifier, undefined);
        }
        return this;
    }
    onChange(event: (width: number, height: number, mode: PanelMode) => void): PanelAttribute {
        throw new Error("Method not implemented.");
    }
    onHeightChange(callback: (value: number) => void): PanelAttribute {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkPanelComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
class ShowCloseIconModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("showCloseIcon");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().panel.resetShowCloseIconModifier(node);
        }
        else {
            GetUINativeModule().panel.setShowCloseIconModifier(node, this.value);
        }
    }
}
class DragBarModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("dragBar");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().panel.resetDragBar(node);
        }
        else {
            GetUINativeModule().panel.setDragBar(node, this.value);
        }
    }
}
class ShowModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("show");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().panel.resetDragBar(node);
        }
        else {
            GetUINativeModule().panel.setDragBar(node, this.value);
        }
    }
}
