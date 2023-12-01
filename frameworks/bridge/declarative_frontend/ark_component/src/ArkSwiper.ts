/// <reference path='./import.ts' />
class ArkSwiperComponent extends ArkComponent implements SwiperAttribute {
  index(value: number): this {
    throw new Error('Method not implemented.');
  }
  autoPlay(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  interval(value: number): this {
    throw new Error('Method not implemented.');
  }
  indicator(value: boolean | DotIndicator | DigitIndicator): this {
    throw new Error('Method not implemented.');
  }
  displayArrow(value: boolean | ArrowStyle, isHoverShow?: boolean | undefined): this {
    throw new Error('Method not implemented.');
  }
  loop(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  duration(value: number): this {
    throw new Error('Method not implemented.');
  }
  vertical(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  itemSpace(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  displayMode(value: SwiperDisplayMode): this {
    throw new Error('Method not implemented.');
  }
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  displayCount(value: string | number | SwiperAutoFill): this {
    throw new Error('Method not implemented.');
  }
  effectMode(value: EdgeEffect): this {
    throw new Error('Method not implemented.');
  }
  disableSwipe(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  curve(value: string | Curve | ICurve): this {
    throw new Error('Method not implemented.');
  }
  onChange(event: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  indicatorStyle(value?: IndicatorStyle | undefined): this {
    throw new Error('Method not implemented.');
  }
  prevMargin(value: any): this {
    throw new Error('Method not implemented.');
  }
  nextMargin(value: any): this {
    throw new Error('Method not implemented.');
  }
  onAnimationStart(event: (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onAnimationEnd(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onGestureSwipe(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: SwiperNestedScrollMode): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSwiperComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
