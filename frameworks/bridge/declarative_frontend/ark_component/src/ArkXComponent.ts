/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
interface XComponentParam {
  id: string;
  type: string | XComponentType;
  imageAIOptions: ImageAIOptions;
  libraryname?: string;
  controller?: XComponentController;
}
class ArkXComponentComponent extends ArkComponent implements XComponentAttribute {
  _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
  nativePtr: KNode;

  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  applyModifierPatch(): void {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr, this)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  initialize(value: Object[]): this {
    if (value[0]) {
      modifierWithKey(this._modifiersWithKeys, XComponentInitializeModifier.identity,
        XComponentInitializeModifier, value[0] as XComponentParam);
    }
    return this;
  }
  outline(value: OutlineOptions): this {
    throw new Error('Method not implemented.');
  }
  outlineColor(value: ResourceColor | EdgeColors): this {
    throw new Error('Method not implemented.');
  }
  outlineRadius(value: Dimension | OutlineRadiuses): this {
    throw new Error('Method not implemented.');
  }
  outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
    throw new Error('Method not implemented.');
  }
  outlineWidth(value: Dimension | EdgeOutlineWidths): this {
    throw new Error('Method not implemented.');
  }
  expandSafeArea(types?: SafeAreaType[], edges?: SafeAreaEdge[]): this {
    throw new Error('Method not implemented.');
  }
  responseRegion(value: Rectangle | Rectangle[]): this {
    throw new Error('Method not implemented.');
  }
  mouseResponseRegion(value: Rectangle | Rectangle[]): this {
    throw new Error('Method not implemented.');
  }
  size(value: SizeOptions): this {
    throw new Error('Method not implemented.');
  }
  constraintSize(value: ConstraintSizeOptions): this {
    throw new Error('Method not implemented.');
  }
  touchable(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  hitTestBehavior(value: HitTestMode): this {
    throw new Error('Method not implemented.');
  }
  layoutWeight(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  padding(value: Length | Padding): this {
    throw new Error('Method not implemented.');
  }
  margin(value: Length | Padding): this {
    throw new Error('Method not implemented.');
  }
  background(builder: CustomBuilder, options?: { align?: Alignment; }): this {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundColorModifier.identity,
      XComponentBackgroundColorModifier, value);
    return this;
  }
  backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
    let arkBackgroundImage = new ArkBackgroundImage();
    arkBackgroundImage.src = src;
    arkBackgroundImage.repeat = repeat;
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundImageModifier.identity, XComponentBackgroundImageModifier, arkBackgroundImage);
    return this;
  }
  backgroundImageSize(value: SizeOptions | ImageSize): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundImageSizeModifier.identity, XComponentBackgroundImageSizeModifier, value);
    return this;
  }
  backgroundImagePosition(value: Alignment | Position): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundImagePositionModifier.identity, XComponentBackgroundImagePositionModifier, value);
    return this;
  }
  backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
    throw new Error('Method not implemented.');
  }
  foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
    throw new Error('Method not implemented.');
  }
  opacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, XComponentOpacityModifier.identity, XComponentOpacityModifier, value);
    return this;
  }
  border(value: BorderOptions): this {
    throw new Error('Method not implemented.');
  }
  borderStyle(value: BorderStyle | EdgeStyles): this {
    throw new Error('Method not implemented.');
  }
  borderWidth(value: Length | EdgeWidths): this {
    throw new Error('Method not implemented.');
  }
  borderColor(value: ResourceColor | EdgeColors): this {
    throw new Error('Method not implemented.');
  }
  borderRadius(value: Length | BorderRadiuses): this {
    throw new Error('Method not implemented.');
  }
  borderImage(value: BorderImageOption): this {
    throw new Error('Method not implemented.');
  }
  foregroundColor(value: string | number | Resource | Color): this {
    throw new Error('Method not implemented.');
  }
  onClick(event: (event: ClickEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onHover(event: (isHover: boolean, event: HoverEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  hoverEffect(value: HoverEffect): this {
    throw new Error('Method not implemented.');
  }
  onMouse(event: (event: MouseEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onTouch(event: (event: TouchEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onKeyEvent(event: (event: KeyEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onFocus(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBlur(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  tabIndex(index: number): this {
    throw new Error('Method not implemented.');
  }
  groupDefaultFocus(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  animation(value: AnimateParam): this {
    throw new Error('Method not implemented.');
  }
  transition(value: TransitionOptions | TransitionEffect): this {
    throw new Error('Method not implemented.');
  }
  gesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }
  priorityGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }
  parallelGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }
  blur(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBlurModifier.identity, XComponentBlurModifier, value);
    return this;
  }
  linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
    if (isUndefined(value) || isNull(value) || isUndefined(options) || isNull(options)) {
      modifierWithKey(this._modifiersWithKeys, XComponentLinearGradientBlurModifier.identity, XComponentLinearGradientBlurModifier,
        undefined);
      return this;
    }
    let arkLinearGradientBlur = new ArkLinearGradientBlur();
    arkLinearGradientBlur.blurRadius = value;
    arkLinearGradientBlur.fractionStops = options.fractionStops;
    arkLinearGradientBlur.direction = options.direction;
    modifierWithKey(this._modifiersWithKeys, XComponentLinearGradientBlurModifier.identity, XComponentLinearGradientBlurModifier,
      arkLinearGradientBlur);
    return this;
  }
  brightness(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBrightnessModifier.identity, XComponentBrightnessModifier, value);
    return this;
  }
  contrast(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentContrastModifier.identity, XComponentContrastModifier, value);
    return this;
  }
  grayscale(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentGrayscaleModifier.identity, XComponentGrayscaleModifier, value);
    return this;
  }
  colorBlend(value: string | Resource | Color): this {
    modifierWithKey(this._modifiersWithKeys, XComponentColorBlendModifier.identity, XComponentColorBlendModifier, value);
    return this;
  }
  saturate(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentSaturateModifier.identity, XComponentSaturateModifier, value);
    return this;
  }
  sepia(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentSepiaModifier.identity, XComponentSepiaModifier, value);
    return this;
  }
  invert(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentInvertModifier.identity, XComponentInvertModifier, value);
    return this;
  }
  hueRotate(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentHueRotateModifier.identity, XComponentHueRotateModifier, value);
    return this;
  }
  useEffect(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  backdropBlur(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentBackdropBlurModifier.identity, XComponentBackdropBlurModifier, value);
    return this;
  }
  renderGroup(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  translate(value: TranslateOptions): this {
    throw new Error('Method not implemented.');
  }
  scale(value: ScaleOptions): this {
    throw new Error('Method not implemented.');
  }
  gridSpan(value: number): this {
    throw new Error('Method not implemented.');
  }
  gridOffset(value: number): this {
    throw new Error('Method not implemented.');
  }
  rotate(value: RotateOptions): this {
    throw new Error('Method not implemented.');
  }
  transform(value: object): this {
    throw new Error('Method not implemented.');
  }
  onAppear(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onDisAppear(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onAttach(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onDetach(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onAreaChange(event: (oldValue: Area, newValue: Area) => void): this {
    throw new Error('Method not implemented.');
  }
  visibility(value: Visibility): this {
    throw new Error('Method not implemented.');
  }
  flexGrow(value: number): this {
    throw new Error('Method not implemented.');
  }
  flexShrink(value: number): this {
    throw new Error('Method not implemented.');
  }
  flexBasis(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  alignSelf(value: ItemAlign): this {
    throw new Error('Method not implemented.');
  }
  displayPriority(value: number): this {
    throw new Error('Method not implemented.');
  }
  zIndex(value: number): this {
    throw new Error('Method not implemented.');
  }
  sharedTransition(id: string, options?: sharedTransitionOptions): this {
    throw new Error('Method not implemented.');
  }
  direction(value: Direction): this {
    throw new Error('Method not implemented.');
  }
  align(value: Alignment): this {
    throw new Error('Method not implemented.');
  }
  position(value: Position): this {
    throw new Error('Method not implemented.');
  }
  markAnchor(value: Position): this {
    throw new Error('Method not implemented.');
  }
  offset(value: Position): this {
    throw new Error('Method not implemented.');
  }
  enabled(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  useSizeType(value: {
    xs?: number | { span: number; offset: number };
    sm?: number | { span: number; offset: number };
    md?: number | { span: number; offset: number };
    lg?: number | { span: number; offset: number };
  }): this {
    throw new Error('Method not implemented.');
  }
  alignRules(value: AlignRuleOption): this {
    throw new Error('Method not implemented.');
  }
  aspectRatio(value: number): this {
    throw new Error('Method not implemented.');
  }
  clickEffect(value: ClickEffect): this {
    throw new Error('Method not implemented.');
  }
  allowDrop(value: Array<UniformDataType>): this {
    throw new Error('Method not implemented.');
  }
  overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number; }; }): this {
    throw new Error('Method not implemented.');
  }
  linearGradient(value: {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    throw new Error('Method not implemented.');
  }
  sweepGradient(value: {
    center: Array<any>;
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    throw new Error('Method not implemented.');
  }
  radialGradient(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }): this {
    throw new Error('Method not implemented.');
  }
  motionPath(value: MotionPathOptions): this {
    throw new Error('Method not implemented.');
  }
  shadow(value: ShadowOptions | ShadowStyle): this {
    modifierWithKey(this._modifiersWithKeys, ShadowModifier.identity, ShadowModifier, value);
    return this;
  }
  blendMode(value: BlendMode): this {
    throw new Error('Method not implemented.');
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    throw new Error('Method not implemented.');
  }
  mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this {
    throw new Error('Method not implemented.');
  }
  key(value: string): this {
    throw new Error('Method not implemented.');
  }
  id(value: string): this {
    throw new Error('Method not implemented.');
  }
  geometryTransition(id: string): this {
    throw new Error('Method not implemented.');
  }
  bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
    throw new Error('Method not implemented.');
  }
  bindMenu(content: CustomBuilder | MenuElement[], options?: MenuOptions): this {
    throw new Error('Method not implemented.');
  }
  bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
    throw new Error('Method not implemented.');
  }
  bindContentCover(isShow: unknown, builder: unknown, options?: unknown): this {
    throw new Error('Method not implemented.');
  }
  bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this {
    throw new Error('Method not implemented.');
  }
  stateStyles(value: StateStyles): this {
    throw new Error('Method not implemented.');
  }
  restoreId(value: number): this {
    throw new Error('Method not implemented.');
  }
  onVisibleAreaChange(ratios: number[], event: (isVisible: boolean, currentRatio: number) => void): this {
    throw new Error('Method not implemented.');
  }
  sphericalEffect(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentSphericalEffectModifier.identity, XComponentSphericalEffectModifier, value);
    return this;
  }
  lightUpEffect(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentLightUpEffectModifier.identity, XComponentLightUpEffectModifier, value);
    return this;
  }
  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    modifierWithKey(this._modifiersWithKeys, XComponentPixelStretchEffectModifier.identity, XComponentPixelStretchEffectModifier, options);
    return this;
  }
  keyboardShortcut(value: string | FunctionKey, keys: ModifierKey[], action?: () => void): this {
    throw new Error('Method not implemented.');
  }
  accessibilityGroup(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  accessibilityText(value: string): this {
    throw new Error('Method not implemented.');
  }
  accessibilityDescription(value: string): this {
    throw new Error('Method not implemented.');
  }
  accessibilityLevel(value: string): this {
    throw new Error('Method not implemented.');
  }
  obscured(reasons: ObscuredReasons[]): this {
    throw new Error('Method not implemented.');
  }
  reuseId(id: string): this {
    throw new Error('Method not implemented.');
  }
  renderFit(fitMode: RenderFit): this {
    modifierWithKey(this._modifiersWithKeys, XComponentRenderFitModifier.identity, XComponentRenderFitModifier, fitMode);
    return this;
  }
  attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
    return this;
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  onLoad(callback: (event?: object) => void): this {
    modifierWithKey(this._modifiersWithKeys, XComponentOnLoadModifier.identity, XComponentOnLoadModifier, callback);
    return this;
  }
  onDestroy(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, XComponentOnDestroyModifier.identity, XComponentOnDestroyModifier, event);
    return this;
  }
  enableAnalyzer(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableAnalyzerModifier.identity, XComponentEnableAnalyzerModifier, value);
    return this;
  }
  enableSecure(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableSecureModifier.identity, XComponentEnableSecureModifier, value);
    return this;
  }
  hdrBrightness(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentHdrBrightnessModifier.identity, XComponentHdrBrightnessModifier, value);
    return this;
  }
  enableTransparentLayer(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableTransparentLayerModifier.identity, XComponentEnableTransparentLayerModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.XComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkXComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

class XComponentInitializeModifier extends ModifierWithKey<XComponentParam> {
  constructor(value: XComponentParam) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetXComponentInitialize(node);
    } else {
      getUINativeModule().xComponent.setXComponentInitialize(node, this.value?.id,
        this.value?.type, this.value?.imageAIOptions, this.value?.libraryname, this.value?.controller);
    }
  }
}

class XComponentOpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentOpacity');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetOpacity(node);
    } else {
      getUINativeModule().xComponent.setOpacity(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBackgroundColor(node);
    } else {
      getUINativeModule().xComponent.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentBackgroundImageModifier extends ModifierWithKey<ArkBackgroundImage> {
  constructor(value: ArkBackgroundImage) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBackgroundImage');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBackgroundImage(node);
    } else {
      getUINativeModule().xComponent.setBackgroundImage(node, this.value.src, this.value.repeat);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as ArkBackgroundImage).src === (this.value as ArkBackgroundImage).src &&
      (this.stageValue as ArkBackgroundImage).repeat === (this.value as ArkBackgroundImage).repeat);
  }
}

class XComponentBackgroundImageSizeModifier extends ModifierWithKey<SizeOptions | ImageSize> {
  constructor(value: SizeOptions | ImageSize) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBackgroundImageSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBackgroundImageSize(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().xComponent.setBackgroundImageSize(node, this.value, undefined, undefined);
      } else {
        getUINativeModule().xComponent.setBackgroundImageSize(node, undefined, (this.value as SizeOptions)?.width, (this.value as SizeOptions)?.height);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as SizeOptions).width === (this.stageValue as SizeOptions).width &&
      (this.value as SizeOptions).height === (this.stageValue as SizeOptions).height);
  }
}

class XComponentBackgroundImagePositionModifier extends ModifierWithKey<Position | Alignment> {
  constructor(value: Position | Alignment) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBackgroundImagePosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBackgroundImagePosition(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().xComponent.setBackgroundImagePosition(node, this.value, undefined, undefined);
      } else {
        getUINativeModule().xComponent.setBackgroundImagePosition(node, undefined, (this.value as Position)?.x, (this.value as Position)?.y);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as Position)?.x === (this.stageValue as Position)?.x &&
      (this.value as Position)?.y === (this.stageValue as Position)?.y);
  }
}

class XComponentBlurModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBlur(node);
    } else {
      getUINativeModule().xComponent.setBlur(node, this.value);
    }
  }
}

class XComponentBackdropBlurModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBackdropBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBackdropBlur(node);
    } else {
      getUINativeModule().xComponent.setBackdropBlur(node, this.value);
    }
  }
}

class XComponentGrayscaleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentGrayscale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetGrayscale(node);
    } else {
      getUINativeModule().xComponent.setGrayscale(node, this.value);
    }
  }
}

class XComponentBrightnessModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentBrightness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetBrightness(node);
    } else {
      getUINativeModule().xComponent.setBrightness(node, this.value);
    }
  }
}

class XComponentSaturateModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentSaturate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetSaturate(node);
    } else {
      getUINativeModule().xComponent.setSaturate(node, this.value);
    }
  }
}

class XComponentContrastModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentContrast');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetContrast(node);
    } else {
      getUINativeModule().xComponent.setContrast(node, this.value);
    }
  }
}

class XComponentInvertModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentInvert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetInvert(node);
    } else {
      getUINativeModule().xComponent.setInvert(node, this.value);
    }
  }
}

class XComponentSepiaModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentSepia');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetSepia(node);
    } else {
      getUINativeModule().xComponent.setSepia(node, this.value);
    }
  }
}

class XComponentHueRotateModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentHueRotate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetHueRotate(node);
    } else {
      getUINativeModule().xComponent.setHueRotate(node, this.value);
    }
  }
}

class XComponentColorBlendModifier extends ModifierWithKey<Color | string | Resource> {
  constructor(value: Color | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentColorBlend');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetColorBlend(node);
    } else {
      getUINativeModule().xComponent.setColorBlend(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentSphericalEffectModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentSphericalEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetSphericalEffect(node);
    } else {
      getUINativeModule().xComponent.setSphericalEffect(node, this.value);
    }
  }
}

class XComponentLightUpEffectModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentLightUpEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetLightUpEffect(node);
    } else {
      getUINativeModule().xComponent.setLightUpEffect(node, this.value);
    }
  }
}

class XComponentPixelStretchEffectModifier extends ModifierWithKey<PixelStretchEffectOptions> {
  constructor(value: PixelStretchEffectOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentPixelStretchEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetPixelStretchEffect(node);
    } else {
      getUINativeModule().xComponent.setPixelStretchEffect(node,
        this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as PixelStretchEffectOptions).left === (this.value as PixelStretchEffectOptions).left &&
      (this.stageValue as PixelStretchEffectOptions).right === (this.value as PixelStretchEffectOptions).right &&
      (this.stageValue as PixelStretchEffectOptions).top === (this.value as PixelStretchEffectOptions).top &&
      (this.stageValue as PixelStretchEffectOptions).bottom === (this.value as PixelStretchEffectOptions).bottom);
  }
}

class XComponentLinearGradientBlurModifier extends ModifierWithKey<ArkLinearGradientBlur> {
  constructor(value: ArkLinearGradientBlur) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentlinearGradientBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetLinearGradientBlur(node);
    } else {
      getUINativeModule().xComponent.setLinearGradientBlur(node,
        this.value.blurRadius, this.value.fractionStops, this.value.direction);
    }
  }
  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class XComponentOnLoadModifier extends ModifierWithKey<(event?: object) => void> {
  constructor(value: (event?: object) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentOnLoad');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetOnLoad(node);
    } else {
      getUINativeModule().xComponent.setOnLoad(node, this.value);
    }
  }
}

class XComponentOnDestroyModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentOnDestroy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetOnDestroy(node);
    } else {
      getUINativeModule().xComponent.setOnDestroy(node, this.value);
    }
  }
}

class XComponentEnableAnalyzerModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentEnableAnalyzer');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetEnableAnalyzer(node);
    } else {
      getUINativeModule().xComponent.setEnableAnalyzer(node, this.value);
    }
  }
  
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentEnableSecureModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentEnableSecure');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetEnableSecure(node);
    } else {
      getUINativeModule().xComponent.setEnableSecure(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentHdrBrightnessModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentHdrBrightness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetHdrBrightness(node);
    } else {
      getUINativeModule().xComponent.setHdrBrightness(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentEnableTransparentLayerModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentEnableTransparentLayer');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetEnableTransparentLayer(node);
    } else {
      getUINativeModule().xComponent.setEnableTransparentLayer(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class XComponentRenderFitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentRenderFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().xComponent.resetRenderFit(node);
    } else {
      getUINativeModule().xComponent.setRenderFit(node, this.value);
    }
  }
}