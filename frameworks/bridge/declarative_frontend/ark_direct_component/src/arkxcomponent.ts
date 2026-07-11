/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
interface XComponentParam {
  id: string;
  type: string | XComponentType;
  imageAIOptions: ImageAIOptions;
  libraryname?: string;
  controller?: XComponentController;
}

interface XComponentHdrBrightnessParam {
  brightness: number;
  hdrType?: HdrType;
}

type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkXComponentComponent extends globalThis.__ArkComponent__ implements XComponentAttribute {
      _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
      nativePtr: KNode;
      xComponentType: XComponentType = XComponentType.SURFACE;
      libraryname?: string = undefined;

      constructor(nativePtr: any, classType?: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        if (this.xComponentType === XComponentType.COMPONENT) {
          return undefined;
        }
        return 0;
      }
      initialize(value: any[]): this {
        if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
          this.xComponentType = (value[0] as XComponentParam).type;
          this.libraryname = (value[0] as XComponentParam).libraryname;
          modifierWithKey(this._modifiersWithKeys, XComponentInitializeModifier.identity,
            XComponentInitializeModifier, value[0] as XComponentParam);
        }
        return this;
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
      background(builder: CustomBuilder, options?: { align?: Alignment; }): this {
        throw new BusinessError(100201, 'background Method not supportted in ArkXComponentComponent class.');
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentBackgroundColorModifier.identity,
          XComponentBackgroundColorModifier, value);
        return this;
      }
      backgroundImage(src: any, repeat?: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        let arkBackgroundImage = new ArkBackgroundImage();
        arkBackgroundImage.src = src;
        arkBackgroundImage.repeat = repeat;
        modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier, arkBackgroundImage);
        return this;
      }
      backgroundImageSize(value: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier, value);
        return this;
      }
      backgroundImagePosition(value: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier, value);
        return this;
      }
      opacity(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentOpacityModifier.identity, XComponentOpacityModifier, value);
        return this;
      }
      foregroundColor(value: string | number | Resource | Color): this {
        throw new BusinessError(100201, 'foregroundColor Method not supportted in ArkXComponentComponent class.');
      }
      onClick(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, ClickModifier.identity, ClickModifier, event);
        }
        return this;
      }
      onHover(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnHoverModifier.identity, OnHoverModifier, event);
        }
        return this;
      }
      onHoverMove(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnHoverMoveModifier.identity, OnHoverMoveModifier, event);
        }
        return this;
      }
      onMouse(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnMouseModifier.identity, OnMouseModifier, event);
        }
        return this;
      }
      onTouch(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnTouchModifier.identity, OnTouchModifier, event);
        }
        return this;
      }
      onKeyEvent(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity, OnKeyEventModifier, event);
        }
        return this;
      }
      onFocus(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnFocusModifier.identity, OnFocusModifier, event);
        }
        return this;
      }
      onNeedSoftkeyboard(onNeedSoftkeyboardCallback: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnNeedSoftkeyboardModifier.identity, OnNeedSoftkeyboardModifier, onNeedSoftkeyboardCallback);
        }
        return this;
      }
      onBlur(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnBlurModifier.identity, OnBlurModifier, event);
        }
        return this;
      }
      animation(value: AnimateParam): this {
        throw new BusinessError(100201, 'animation Method not supportted in ArkXComponentComponent class.');
      }
      gesture(gesture: GestureType, mask?: GestureMask): this {
        throw new BusinessError(100201, 'gesture Method not supportted in ArkXComponentComponent class.');
      }
      priorityGesture(gesture: GestureType, mask?: GestureMask): this {
        throw new BusinessError(100201, 'priorityGesture Method not supportted in ArkXComponentComponent class.');
      }
      parallelGesture(gesture: GestureType, mask?: GestureMask): this {
        throw new BusinessError(100201, 'parallelGesture Method not supportted in ArkXComponentComponent class.');
      }
      blur(value: any, options?: any, sysOptions?: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        let blur = new ArkBlurOptions();
        blur.value = value;
        blur.options = options;
        if (typeof sysOptions === 'object') {
          blur.disableSystemAdaptation = sysOptions.disableSystemAdaptation;
        }
        modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, blur);
        return this;
      }
      linearGradientBlur(value: any, options: any): this {
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
      brightness(value: any): this {
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
      contrast(value: any): this {
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
      grayscale(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentGrayscaleModifier.identity, XComponentGrayscaleModifier, value);
        return this;
      }
      colorBlend(value: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
        return this;
      }
      saturate(value: any): this {
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
      sepia(value: any): this {
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
      invert(value: any): this {
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
      hueRotate(value: any): this {
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
        throw new BusinessError(100201, 'useEffect Method not supportted in ArkXComponentComponent class.');
      }
      backdropBlur(value: any, options?: any): this {
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
        throw new BusinessError(100201, 'renderGroup Method not supportted in ArkXComponentComponent class.');
      }
      onAppear(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnAppearModifier.identity, OnAppearModifier, event);
        }
        return this;
      }
      onDisAppear(event: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnDisappearModifier.identity, OnDisappearModifier, event);
        }
        return this;
      }
      onAttach(callback: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnAttachModifier.identity, OnAttachModifier, callback);
        }
        return this;
      }
      onDetach(callback: any): this {
        if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
          modifierWithKey(this._modifiersWithKeys, OnDetachModifier.identity, OnDetachModifier, callback);
        }
        return this;
      }
      flexGrow(value: number): this {
        throw new BusinessError(100201, 'flexGrow Method not supportted in ArkXComponentComponent class.');
      }
      direction(value: Direction): this {
        throw new BusinessError(100201, 'direction Method not supportted in ArkXComponentComponent class.');
      }
      align(value: Alignment): this {
        throw new BusinessError(100201, 'align Method not supportted in ArkXComponentComponent class.');
      }
      useSizeType(value: {
        xs?: number | { span: number; offset: number };
        sm?: number | { span: number; offset: number };
        md?: number | { span: number; offset: number };
        lg?: number | { span: number; offset: number };
      }): this {
        throw new BusinessError(100201, 'useSizeType Method not supportted in ArkXComponentComponent class.');
      }
      clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
        throw new BusinessError(100201, 'clip Method not supportted in ArkXComponentComponent class.');
      }
      geometryTransition(id: string): this {
        throw new BusinessError(100201, 'geometryTransition Method not supportted in ArkXComponentComponent class.');
      }
      bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        throw new BusinessError(100201, 'bindPopup Method not supportted in ArkXComponentComponent class.');
      }
      bindMenu(content: CustomBuilder | MenuElement[], options?: MenuOptions): this {
        throw new BusinessError(100201, 'bindMenu Method not supportted in ArkXComponentComponent class.');
      }
      bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
        throw new BusinessError(100201, 'bindContextMenu Method not supportted in ArkXComponentComponent class.');
      }
      bindContentCover(isShow: unknown, builder: unknown, options?: unknown): this {
        throw new BusinessError(100201, 'bindContentCover Method not supportted in ArkXComponentComponent class.');
      }
      bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this {
        throw new BusinessError(100201, 'bindSheet Method not supportted in ArkXComponentComponent class.');
      }
      stateStyles(value: StateStyles): this {
        throw new BusinessError(100201, 'stateStyles Method not supportted in ArkXComponentComponent class.');
      }
      restoreId(value: number): this {
        throw new BusinessError(100201, 'restoreId Method not supportted in ArkXComponentComponent class.');
      }
      onVisibleAreaChange(ratios: number[], event: (isVisible: boolean, currentRatio: number) => void): this {
        throw new BusinessError(100201, 'onVisibleAreaChange Method not supportted in ArkXComponentComponent class.');
      }
      sphericalEffect(value: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, SphericalEffectModifier.identity, SphericalEffectModifier, value);
        return this;
      }
      lightUpEffect(value: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, LightUpEffectModifier.identity, LightUpEffectModifier, value);
        return this;
      }
      pixelStretchEffect(options: any): this {
        if (this.xComponentType !== XComponentType.NODE) {
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, PixelStretchEffectModifier.identity, PixelStretchEffectModifier, options);
        return this;
      }
      accessibilityGroup(value: boolean): this {
        throw new BusinessError(100201, 'accessibilityGroup Method not supportted in ArkXComponentComponent class.');
      }
      obscured(reasons: ObscuredReasons[]): this {
        throw new BusinessError(100201, 'obscured Method not supportted in ArkXComponentComponent class.');
      }
      reuseId(id: string): this {
        throw new BusinessError(100201, 'reuseId Method not supportted in ArkXComponentComponent class.');
      }
      renderFit(fitMode: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentRenderFitModifier.identity, XComponentRenderFitModifier, fitMode);
        return this;
      }
      attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
        return this;
      }
      onLoad(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentOnLoadModifier.identity, XComponentOnLoadModifier, callback);
        return this;
      }
      onDestroy(event: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentOnDestroyModifier.identity, XComponentOnDestroyModifier, event);
        return this;
      }
      enableAnalyzer(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentEnableAnalyzerModifier.identity, XComponentEnableAnalyzerModifier, value);
        return this;
      }
      enableSecure(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentEnableSecureModifier.identity, XComponentEnableSecureModifier, value);
        return this;
      }
      hdrBrightness(value: any, hdrType?: any): this {
        if (isUndefined(value) || isNull(value)) {
          modifierWithKey(this._modifiersWithKeys, XComponentHdrBrightnessModifier.identity,
            XComponentHdrBrightnessModifier, undefined);
          return this;
        }
        modifierWithKey(this._modifiersWithKeys, XComponentHdrBrightnessModifier.identity,
          XComponentHdrBrightnessModifier, { brightness: value, hdrType: hdrType });
        return this;
      }
      enableTransparentLayer(value: any): this {
        modifierWithKey(this._modifiersWithKeys, XComponentEnableTransparentLayerModifier.identity, XComponentEnableTransparentLayerModifier, value);
        return this;
      }
    }

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

    class XComponentHdrBrightnessModifier extends ModifierWithKey<XComponentHdrBrightnessParam> {
      constructor(value: XComponentHdrBrightnessParam) {
        super(value);
      }
      static identity: Symbol = Symbol('xComponentHdrBrightness');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().xComponent.resetHdrBrightness(node);
        } else {
          getUINativeModule().xComponent.setHdrBrightness(node, this.value.brightness, this.value.hdrType);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.brightness, this.value.brightness) ||
          !isBaseOrResourceEqual(this.stageValue.hdrType, this.value.hdrType);
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
    loadComponent.componentObj = { 'component': ArkXComponentComponent };
  }
  return loadComponent.componentObj;
}

function getXComponentComponent(): any {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  const nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  return JSXComponent.createOrGetNode(elmtId, () => {
    return createComponent(nativeNode, 'xcomponent');
  });
}

// @ts-ignore
globalThis.XComponent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return createComponent(nativePtr, 'xcomponent');
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.XComponentModifier(nativePtr, classType);
  });
};
class JSXComponent extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().xComponent.create(params);
  }

  static backgroundColor(value: any): void {
    getUINativeModule().xComponent.setBackgroundColor(true, value);
  }

  static backgroundImage(src: any, repeat: any): void {
    getUINativeModule().xComponent.setBackgroundImage(true, src, repeat);
  }

  static backgroundImageSize(value: any): void {
    if (isNumber(value)) {
      getUINativeModule().xComponent.setBackgroundImageSize(true, value, undefined, undefined);
      return;
    }
    getUINativeModule().xComponent.setBackgroundImageSize(true, undefined, value?.width, value?.height);
  }

  static backgroundImagePosition(value: any): void {
    if (isNumber(value)) {
      getUINativeModule().xComponent.setBackgroundImagePosition(true, value, undefined, undefined);
      return;
    }
    getUINativeModule().xComponent.setBackgroundImagePosition(true, undefined, value?.x, value?.y);
  }

  static opacity(value: any): void {
    getUINativeModule().xComponent.setOpacity(true, value);
  }

  static blur(value: any, options: any, sysOptions: any): void {
    getUINativeModule().xComponent.setBlur(
      true, value, options?.grayscale, sysOptions?.disableSystemAdaptation);
  }

  static linearGradientBlur(value: any, options: any): void {
    getUINativeModule().xComponent.setLinearGradientBlur(
      true, value, options);
  }

  static brightness(value: any): void {
    getUINativeModule().xComponent.setBrightness(true, value);
  }

  static contrast(value: any): void {
    getUINativeModule().xComponent.setContrast(true, value);
  }

  static grayscale(value: any): void {
    getUINativeModule().xComponent.setGrayscale(true, value);
  }

  static colorBlend(value: any): void {
    getUINativeModule().xComponent.setColorBlend(true, value);
  }

  static saturate(value: any): void {
    getUINativeModule().xComponent.setSaturate(true, value);
  }

  static sepia(value: any): void {
    getUINativeModule().xComponent.setSepia(true, value);
  }

  static invert(value: any): void {
    getUINativeModule().xComponent.setInvert(true, value);
    return;
  }

  static hueRotate(value: any): void {
    getUINativeModule().xComponent.setHueRotate(true, value);
  }

  static backdropBlur(value: any, options: any, sysOptions: any): void {
    getUINativeModule().xComponent.setBackdropBlur(
      true, value, options?.grayscale, sysOptions?.disableSystemAdaptation);
  }

  static sphericalEffect(value: any): void {
    getUINativeModule().xComponent.setSphericalEffect(true, value);
  }

  static lightUpEffect(value: any): void {
    getUINativeModule().xComponent.setLightUpEffect(true, value);
  }

  static pixelStretchEffect(value: any): void {
    getUINativeModule().xComponent.setPixelStretchEffect(
      true, value);
  }

  static renderFit(value: any): void {
    getUINativeModule().xComponent.setRenderFit(true, value);
  }

  static onLoad(value: any): void {
    getUINativeModule().xComponent.setOnLoad(true, value);
  }

  static onDestroy(value: any): void {
    getUINativeModule().xComponent.setOnDestroy(true, value);
  }

  static enableAnalyzer(value: any): void {
    getUINativeModule().xComponent.setEnableAnalyzer(true, value);
  }

  static enableSecure(value: any): void {
    getUINativeModule().xComponent.setEnableSecure(true, value);
  }

  static hdrBrightness(hdrBrightness: any, hdrType: any): void {
    getUINativeModule().xComponent.setHdrBrightness(true, hdrBrightness, hdrType);
  }

  static enableTransparentLayer(value: any): void {
    getUINativeModule().xComponent.setEnableTransparentLayer(true, value);
  }
  
  static blendMode(blendMode: any, blendApplyType: any): void {
    getUINativeModule().xComponent.setBlendMode(true, blendMode, blendApplyType);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
      return createComponent(nativePtr, 'xcomponent');
    }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
      return new modifierJS.XComponentModifier(nativePtr, classType);
    });
  }

  static onClick(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onClick(value);
  }

  static onHover(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onHover(value);
  }

  static onMouse(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onMouse(value);
  }

  static onTouch(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onTouch(value);
  }

  static onKeyEvent(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onKeyEvent(value);
  }

  static onFocus(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onFocus(value);
  }

  static onBlur(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onBlur(value);
  }

  static onAppear(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onAppear(value);
  }

  static onDisAppear(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onDisAppear(value);
  }

  static onAttach(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onAttach(value);
  }

  static onDetach(value: any): void {
    if (!getUINativeModule().xComponent.isCommonEventAvailable(true)) {
        return;
    }
    __Common__.onDetach(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkXComponentComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.XComponent = JSXComponent;
}

export default { loadComponent, createComponent, exportComponent, exportView };
