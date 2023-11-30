/// <reference path="./import.ts" />
class ArkTabsComponent extends ArkComponent implements TabsAttribute {
  vertical(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  barPosition(value: BarPosition): this {
    throw new Error("Method not implemented.");
  }
  scrollable(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  barMode(value: BarMode.Fixed): this;
  barMode(value: BarMode.Scrollable, options: ScrollableBarModeOptions): this;
  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): this;
  barMode(value: unknown, options?: unknown): this {
    throw new Error("Method not implemented.");
  }
  barWidth(value: any): this {
    throw new Error("Method not implemented.");
  }
  barHeight(value: any): this {
    throw new Error("Method not implemented.");
  }
  animationDuration(value: number): this {
    throw new Error("Method not implemented.");
  }
  onChange(event: (index: number) => void): this {
    throw new Error("Method not implemented.");
  }
  onTabBarClick(event: (index: number) => void): this {
    throw new Error("Method not implemented.");
  }
  onAnimationStart(handler: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): this {
    throw new Error("Method not implemented.");
  }
  onAnimationEnd(handler: (index: number, event: TabsAnimationEvent) => void): this {
    throw new Error("Method not implemented.");
  }
  onGestureSwipe(handler: (index: number, event: TabsAnimationEvent) => void): this {
    throw new Error("Method not implemented.");
  }
  fadingEdge(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  divider(value: DividerStyle | null): this {
    throw new Error("Method not implemented.");
  }
  barOverlap(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  barBackgroundColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  barGridAlign(value: BarGridColumnOptions): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkTabsComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
