
/// <reference path="./import.ts" />
class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
    scrollable(value: ScrollDirection): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScroll(event: (xOffset: number, yOffset: number) => void): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScrollEdge(event: (side: Edge) => void): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScrollStart(event: () => void): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScrollEnd(event: () => void): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScrollStop(event: () => void): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    scrollBar(barState: BarState): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    scrollBarColor(color: any): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    scrollBarWidth(value: string | number): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    edgeEffect(edgeEffect: EdgeEffect): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value: NestedScrollOptions): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value: boolean): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    friction(value: any): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
    scrollSnap(value: ScrollSnapOptions): ScrollAttribute {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Scroll.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkScrollComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
