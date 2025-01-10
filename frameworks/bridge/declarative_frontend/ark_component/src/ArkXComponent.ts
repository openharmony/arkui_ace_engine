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
  xComponentType: XComponentType = XComponentType.SURFACE;
  libraryname?: string = undefined;

  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    if (this.xComponentType === XComponentType.COMPONENT) {
      return undefined;
    }
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
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      this.xComponentType = (value[0] as XComponentParam).type;
      this.libraryname = (value[0] as XComponentParam).libraryname;
      modifierWithKey(this._modifiersWithKeys, XComponentInitializeModifier.identity,
        XComponentInitializeModifier, value[0] as XComponentParam);
    }
    return this;
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
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let arkBackgroundImage = new ArkBackgroundImage();
    arkBackgroundImage.src = src;
    arkBackgroundImage.repeat = repeat;
    modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier, arkBackgroundImage);
    return this;
  }
  backgroundImageSize(value: SizeOptions | ImageSize): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier, value);
    return this;
  }
  backgroundImagePosition(value: Alignment | Position): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier, value);
    return this;
  }
  opacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, XComponentOpacityModifier.identity, XComponentOpacityModifier, value);
    return this;
  }
  foregroundColor(value: string | number | Resource | Color): this {
    throw new Error('Method not implemented.');
  }
  onClick(event: (event: ClickEvent) => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnClickModifier.identity, OnClickModifier, event);
    }
    return this;
  }
  onHover(event: (isHover: boolean, event: HoverEvent) => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnHoverModifier.identity, OnHoverModifier, event);
    }
    return this;
  }
  onMouse(event: (event: MouseEvent) => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnMouseModifier.identity, OnMouseModifier, event);
    }
    return this;
  }
  onTouch(event: (event: TouchEvent) => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnTouchModifier.identity, OnTouchModifier, event);
    }
    return this;
  }
  onKeyEvent(event: (event: KeyEvent) => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity, OnKeyEventModifier, event);
    }
    return this;
  }
  onFocus(event: () => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnFocusModifier.identity, OnFocusModifier, event);
    }
    return this;
  }
  onBlur(event: () => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnBlurModifier.identity, OnBlurModifier, event);
    }
    return this;
  }
  animation(value: AnimateParam): this {
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
  blur(value: number, options?: BlurOptions): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let blur = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, blur);
    return this;
  }
  linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (isUndefined(value) || isNull(value) || isUndefined(options) || isNull(options)) {
      modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier,
        undefined);
      return this;
    }
    let arkLinearGradientBlur = new ArkLinearGradientBlur();
    arkLinearGradientBlur.blurRadius = value;
    arkLinearGradientBlur.fractionStops = options.fractionStops;
    arkLinearGradientBlur.direction = options.direction;
    modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier,
      arkLinearGradientBlur);
    return this;
  }
  brightness(value: number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, value);
    }
    return this;
  }
  contrast(value: number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, value);
    }
    return this;
  }
  grayscale(value: number): this {
    modifierWithKey(this._modifiersWithKeys, XComponentGrayscaleModifier.identity, XComponentGrayscaleModifier, value);
    return this;
  }
  colorBlend(value: string | Resource | Color): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
    return this;
  }
  saturate(value: number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, value);
    }
    return this;
  }
  sepia(value: number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, value);
    }
    return this;
  }
  invert(value: number | InvertOptions): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, undefined);
    }
    return this;
  }
  hueRotate(value: string | number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value) && !isString(value)) {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, value);
    }
    return this;
  }
  useEffect(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  backdropBlur(value: number, options?: BlurOptions): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let blur = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, blur);
    return this;
  }
  renderGroup(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  onAppear(event: () => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnAppearModifier.identity, OnAppearModifier, event);
    }
    return this;
  }
  onDisAppear(event: () => void): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnDisappearModifier.identity, OnDisappearModifier, event);
    }
    return this;
  }
  onAttach(callback: Callback<void>): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnAttachModifier.identity, OnAttachModifier, callback);
    }
    return this;
  }
  onDetach(callback: Callback<void>): this {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnDetachModifier.identity, OnDetachModifier, callback);
    }
    return this;
  }
  flexGrow(value: number): this {
    throw new Error('Method not implemented.');
  }
  direction(value: Direction): this {
    throw new Error('Method not implemented.');
  }
  align(value: Alignment): this {
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
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
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
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, SphericalEffectModifier.identity, SphericalEffectModifier, value);
    return this;
  }
  lightUpEffect(value: number): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, LightUpEffectModifier.identity, LightUpEffectModifier, value);
    return this;
  }
  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, PixelStretchEffectModifier.identity, PixelStretchEffectModifier, options);
    return this;
  }
  accessibilityGroup(value: boolean): this {
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
