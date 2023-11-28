
/// <reference path="./import.ts" />
class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    scrollable(value: ScrollDirection): this {
        throw new Error("Method not implemented.");
    }
    onScroll(event: (xOffset: number, yOffset: number) => void): this {
        throw new Error("Method not implemented.");
    }
    onScrollEdge(event: (side: Edge) => void): this {
        throw new Error("Method not implemented.");
    }
    onScrollStart(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    onScrollEnd(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    onScrollStop(event: () => void): this {
        throw new Error("Method not implemented.");
    }
    scrollBar(barState: BarState): this {
        throw new Error("Method not implemented.");
    }
    scrollBarColor(color: any): this {
        throw new Error("Method not implemented.");
    }
    scrollBarWidth(value: string | number): this {
        throw new Error("Method not implemented.");
    }
    edgeEffect(edgeEffect: EdgeEffect): this {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value: NestedScrollOptions): this {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    friction(value: any): this {
        throw new Error("Method not implemented.");
    }
    scrollSnap(value: ScrollSnapOptions): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Scroll.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkScrollComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
