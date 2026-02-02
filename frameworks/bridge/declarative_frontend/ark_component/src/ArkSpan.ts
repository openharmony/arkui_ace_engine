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
class SpanFontSizeModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('spanFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFontSize(node);
    } else {
      getUINativeModule().span.setFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanFontFamilyModifier extends ModifierWithKey<string | Resource> {
  static identity: Symbol = Symbol('spanFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFontFamily(node);
    } else {
      getUINativeModule().span.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanLineHeightModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('spanLineHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetLineHeight(node);
    } else {
      getUINativeModule().span.setLineHeight(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanFontStyleModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('spanFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFontStyle(node);
    } else {
      getUINativeModule().span.setFontStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanTextCaseModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('spanTextCase');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetTextCase(node);
    } else {
      getUINativeModule().span.setTextCase(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanTextBackgroundStyleModifier extends ModifierWithKey<TextBackgroundStyle> {
  constructor(value: TextBackgroundStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('spanTextBackgroundStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetTextBackgroundStyle(node);
    }
    else {
      let textBackgroundStyle = new ArkTextBackGroundStyle();
      if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
        getUINativeModule().span.resetTextBackgroundStyle(node);
      }
      else {
        getUINativeModule().span.setTextBackgroundStyle(node, textBackgroundStyle.color, textBackgroundStyle.radius.topLeft,
          textBackgroundStyle.radius.topRight, textBackgroundStyle.radius.bottomLeft, textBackgroundStyle.radius.bottomRight);
      }
    }
  }
  checkObjectDiff(): boolean {
    let textBackgroundStyle = new ArkTextBackGroundStyle();
    let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
    if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) || !stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
      return false;
    }
    else {
      return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
    }
  }
}
class SpanTextShadowModifier extends ModifierWithKey<ShadowOptions | Array<ShadowOptions>> {
  constructor(value: ShadowOptions | Array<ShadowOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('spanTextShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetTextShadow(node);
    } else {
      let shadow: ArkShadowInfoToArray = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        getUINativeModule().span.resetTextShadow(node);
      } else {
        getUINativeModule().span.setTextShadow(node, shadow.radius,
          shadow.type, shadow.color, shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
      }
    }
  }

  checkObjectDiff(): boolean {
    let checkDiff = true;
    let arkShadow = new ArkShadowInfoToArray();
    if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
      Object.getPrototypeOf(this.value).constructor === Object) {
      checkDiff = arkShadow.checkDiff(<ShadowOptions> this.stageValue, <ShadowOptions> this.value);
    } else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
      Object.getPrototypeOf(this.value).constructor === Array &&
      (<Array<ShadowOptions>> this.stageValue).length === (<Array<ShadowOptions>> this.value).length) {
      let isDiffItem = false;
      for (let i: number = 0; i < (<Array<ShadowOptions>> this.value).length; i++) {
        if (arkShadow.checkDiff(this.stageValue[i], this.value[1])) {
          isDiffItem = true;
          break;
        }
      }
      if (!isDiffItem) {
        checkDiff = false;
      }
    }
    return checkDiff;
  }
}
class SpanFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity = Symbol('spanFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFontColor(node);
    } else {
      getUINativeModule().span.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SpanLetterSpacingModifier extends ModifierWithKey<string | Resource> {
  constructor(value: string | Resource) {
    super(value);
  }
  static identity = Symbol('spanLetterSpacing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetLetterSpacing(node);
    } else {
      getUINativeModule().span.setLetterSpacing(node, this.value!);
    }
  }
}
class SpanBaselineOffsetModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity = Symbol('spanBaselineOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetBaselineOffset(node);
    } else {
      getUINativeModule().span.setBaselineOffset(node, this.value!);
    }
  }
}
class SpanFontModifier extends ModifierWithKey<Font> {
  static identity = Symbol('spanFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFont(node);
    } else {
      getUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
    if ((!isResource(this.stageValue.size) && !isResource(this.value.size) &&
        this.stageValue.size === this.value.size) &&
      ((!isResource(this.stageValue.family) && !isResource(this.value.family) &&
          this.stageValue.family === this.value.family))) {
      return false;
    } else {
      return true;
    }
  }
}
class SpanDecorationModifier extends ModifierWithKey<{ type: TextDecorationType, color?: ResourceColor; style?: TextDecorationStyle }> {
  constructor(value: { type: TextDecorationType, color?: ResourceColor; style?: TextDecorationStyle }) {
    super(value);
  }
  static identity = Symbol('spanDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetDecoration(node);
    } else {
      getUINativeModule().span.setDecoration(node, this.value.type, this.value.color, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    } else {
      return true;
    }
  }
}
class SpanFontWeightModifier extends ModifierWithKey<string | Resource> {
  constructor(value: string | Resource) {
    super(value);
  }
  static identity = Symbol('spanfontweight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetFontWeight(node);
    } else {
      getUINativeModule().span.setFontWeight(node, this.value!);
    }
  }
}

class SpanInputModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('spanInput');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.setSpanSrc(node, '');
    }
    else {
      getUINativeModule().span.setSpanSrc(node, this.value);
    }
  }
}

class SpanAccessibilityTextModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity = Symbol('spanAccessibilityText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetAccessibilityText(node);
    } else {
      getUINativeModule().span.setAccessibilityText(node, this.value);
    }
  }
}

class SpanAccessibilityDescriptionModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity = Symbol('spanAccessibilityDescription');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetAccessibilityDescription(node);
    } else {
      getUINativeModule().span.setAccessibilityDescription(node, this.value);
    }
  }
}

class SpanAccessibilityLevelModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity = Symbol('spanAccessibilityLevel');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetAccessibilityLevel(node);
    } else {
      getUINativeModule().span.setAccessibilityLevel(node, this.value);
    }
  }
}

class SpanOnHoverModifier extends ModifierWithKey<(isHover?: boolean, event?: HoverEvent) => void> {
  constructor(value) {
    super(value);
  }
  static identity = Symbol('spanOnHover');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetOnHover(node);
    } else {
      getUINativeModule().span.setOnHover(node, this.value);
    }
  }
}

class ArkSpanComponent implements CommonMethod<SpanAttribute> {
  _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
  _changed: boolean;
  nativePtr: KNode;
  _weakPtr: JsPointerClass;
  _classType: ModifierType | undefined;
  _nativePtrChanged: boolean;
  _needDiff: boolean;

  constructor(nativePtr: KNode, classType?: ModifierType) {
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
    this._changed = false;
    this._classType = classType;
    this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(nativePtr);
    this._nativePtrChanged = false;
    this._needDiff = true;
  }
  initialize(value: Object[]): this {
    modifierWithKey(this._modifiersWithKeys, SpanInputModifier.identity, SpanInputModifier, value[0]);
    return this;
  }
  cleanStageValue(): void {
    if (!this._modifiersWithKeys) {
      return;
    }
    this._modifiersWithKeys.forEach((value, key) => {
        value.stageValue = undefined;
    });
  }

  applyStateUpdatePtr(instance: ArkComponent): void {
    if (this.nativePtr !== instance.nativePtr) {
      this.nativePtr = instance.nativePtr;
      this._nativePtrChanged = true;
      if (instance._weakPtr) {
        this._weakPtr = instance._weakPtr;
      } else {
        this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(this.nativePtr);
      }
    }
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
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new BusinessError(100201, 'onGestureJudgeBegin function not supported in attributeModifier scenario.');
  }
  outline(value: OutlineOptions): this {
    throw new BusinessError(100201, 'outline function not supported in attributeModifier scenario.');
  }
  outlineColor(value: ResourceColor | EdgeColors): this {
    throw new BusinessError(100201, 'outlineColor function not supported in attributeModifier scenario.');
  }
  outlineRadius(value: Dimension | OutlineRadiuses): this {
    throw new BusinessError(100201, 'outlineRadius function not supported in attributeModifier scenario.');
  }
  outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
    throw new BusinessError(100201, 'outlineStyle function not supported in attributeModifier scenario.');
  }
  outlineWidth(value: Dimension | EdgeOutlineWidths): this {
    throw new BusinessError(100201, 'outlineWidth function not supported in attributeModifier scenario.');
  }
  width(value: Length): this {
    throw new BusinessError(100201, 'width function not supported in attributeModifier scenario.');
  }

  height(value: Length): this {
    throw new BusinessError(100201, 'height function not supported in attributeModifier scenario.');
  }

  expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
    throw new BusinessError(100201, 'expandSafeArea function not supported in attributeModifier scenario.');
  }

  responseRegion(value: Array<Rectangle> | Rectangle): this {
    throw new BusinessError(100201, 'responseRegion function not supported in attributeModifier scenario.');
  }

  mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
    throw new BusinessError(100201, 'mouseResponseRegion function not supported in attributeModifier scenario.');
  }

  size(value: SizeOptions): this {
    throw new BusinessError(100201, 'size function not supported in attributeModifier scenario.');
  }

  constraintSize(value: ConstraintSizeOptions): this {
    throw new BusinessError(100201, 'constraintSize function not supported in attributeModifier scenario.');
  }

  touchable(value: boolean): this {
    throw new BusinessError(100201, 'touchable function not supported in attributeModifier scenario.');
  }

  hitTestBehavior(value: HitTestMode): this {
    throw new BusinessError(100201, 'hitTestBehavior function not supported in attributeModifier scenario.');
  }

  layoutWeight(value: number | string): this {
    throw new BusinessError(100201, 'layoutWeight function not supported in attributeModifier scenario.');
  }

  padding(value: Padding | Length): this {
    throw new BusinessError(100201, 'padding function not supported in attributeModifier scenario.');
  }

  margin(value: Margin | Length): this {
    throw new BusinessError(100201, 'margin function not supported in attributeModifier scenario.');
  }

  background(builder: CustomBuilder, options?: { align?: Alignment }): this {
    throw new BusinessError(100201, 'background function not supported in attributeModifier scenario.');
  }

  backgroundColor(value: ResourceColor): this {
    throw new BusinessError(100201, 'backgroundColor function not supported in attributeModifier scenario.');
  }

  backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
    throw new BusinessError(100201, 'backgroundImage function not supported in attributeModifier scenario.');
  }

  backgroundImageSize(value: SizeOptions | ImageSize): this {
    throw new BusinessError(100201, 'backgroundImageSize function not supported in attributeModifier scenario.');
  }

  backgroundImagePosition(value: Position | Alignment): this {
    throw new BusinessError(100201, 'backgroundImagePosition function not supported in attributeModifier scenario.');
  }

  backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
    throw new BusinessError(100201, 'backgroundBlurStyle function not supported in attributeModifier scenario.');
  }

  foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
    throw new BusinessError(100201, 'foregroundBlurStyle function not supported in attributeModifier scenario.');
  }

  opacity(value: number | Resource): this {
    throw new BusinessError(100201, 'opacity function not supported in attributeModifier scenario.');
  }

  border(value: BorderOptions): this {
    throw new BusinessError(100201, 'border function not supported in attributeModifier scenario.');
  }

  borderStyle(value: BorderStyle | EdgeStyles): this {
    throw new BusinessError(100201, 'borderStyle function not supported in attributeModifier scenario.');
  }

  borderWidth(value: Length | EdgeWidths): this {
    throw new BusinessError(100201, 'borderWidth function not supported in attributeModifier scenario.');
  }

  borderColor(value: ResourceColor | EdgeColors): this {
    throw new BusinessError(100201, 'borderColor function not supported in attributeModifier scenario.');
  }

  borderRadius(value: Length | BorderRadiuses): this {
    throw new BusinessError(100201, 'borderRadius function not supported in attributeModifier scenario.');
  }


  borderImage(value: BorderImageOption): this {
    throw new BusinessError(100201, 'borderImage function not supported in attributeModifier scenario.');
  }

  foregroundColor(value: ResourceColor | ColoringStrategy): this {
    throw new BusinessError(100201, 'foregroundColor function not supported in attributeModifier scenario.');
  }

  onClick(event: (event?: ClickEvent) => void): this {
    throw new BusinessError(100201, 'onClick function not supported in attributeModifier scenario.');
  }

  onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, SpanOnHoverModifier.identity, SpanOnHoverModifier, event);
    return this;
  }

  hoverEffect(value: HoverEffect): this {
    throw new BusinessError(100201, 'hoverEffect function not supported in attributeModifier scenario.');
  }

  onMouse(event: (event?: MouseEvent) => void): this {
    throw new BusinessError(100201, 'onMouse function not supported in attributeModifier scenario.');
  }

  onTouch(event: (event?: TouchEvent) => void): this {
    throw new BusinessError(100201, 'onTouch function not supported in attributeModifier scenario.');
  }

  onKeyEvent(event: (event?: KeyEvent) => void): this {
    throw new BusinessError(100201, 'onKeyEvent function not supported in attributeModifier scenario.');
  }

  focusable(value: boolean): this {
    throw new BusinessError(100201, 'focusable function not supported in attributeModifier scenario.');
  }

  onFocus(event: () => void): this {
    throw new BusinessError(100201, 'onFocus function not supported in attributeModifier scenario.');
  }

  onBlur(event: () => void): this {
    throw new BusinessError(100201, 'onBlur function not supported in attributeModifier scenario.');
  }

  tabIndex(index: number): this {
    throw new BusinessError(100201, 'tabIndex function not supported in attributeModifier scenario.');
  }

  defaultFocus(value: boolean): this {
    throw new BusinessError(100201, 'defaultFocus function not supported in attributeModifier scenario.');
  }

  groupDefaultFocus(value: boolean): this {
    throw new BusinessError(100201, 'groupDefaultFocus function not supported in attributeModifier scenario.');
  }

  focusOnTouch(value: boolean): this {
    throw new BusinessError(100201, 'focusOnTouch function not supported in attributeModifier scenario.');
  }

  animation(value: AnimateParam): this {
    throw new BusinessError(100201, 'animation function not supported in attributeModifier scenario.');
  }

  transition(value: TransitionOptions | TransitionEffect): this {
    throw new BusinessError(100201, 'transition function not supported in attributeModifier scenario.');
  }

  gesture(gesture: GestureType, mask?: GestureMask): this {
    throw new BusinessError(100201, 'gesture function not supported in attributeModifier scenario.');
  }

  priorityGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new BusinessError(100201, 'priorityGesture function not supported in attributeModifier scenario.');
  }

  parallelGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new BusinessError(100201, 'parallelGesture function not supported in attributeModifier scenario.');
  }

  blur(value: number): this {
    throw new BusinessError(100201, 'blur function not supported in attributeModifier scenario.');
  }

  linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
    throw new BusinessError(100201, 'linearGradientBlur function not supported in attributeModifier scenario.');
  }

  brightness(value: number): this {
    throw new BusinessError(100201, 'brightness function not supported in attributeModifier scenario.');
  }

  contrast(value: number): this {
    throw new BusinessError(100201, 'contrast function not supported in attributeModifier scenario.');
  }

  grayscale(value: number): this {
    throw new BusinessError(100201, 'grayscale function not supported in attributeModifier scenario.');
  }

  colorBlend(value: Color | string | Resource): this {
    throw new BusinessError(100201, 'colorBlend function not supported in attributeModifier scenario.');
  }

  saturate(value: number): this {
    throw new BusinessError(100201, 'saturate function not supported in attributeModifier scenario.');
  }

  sepia(value: number): this {
    throw new BusinessError(100201, 'sepia function not supported in attributeModifier scenario.');
  }

  invert(value: number): this {
    throw new BusinessError(100201, 'invert function not supported in attributeModifier scenario.');
  }

  hueRotate(value: number | string): this {
    throw new BusinessError(100201, 'hueRotate function not supported in attributeModifier scenario.');
  }

  useEffect(value: boolean): this {
    throw new BusinessError(100201, 'useEffect function not supported in attributeModifier scenario.');
  }

  backdropBlur(value: number): this {
    throw new BusinessError(100201, 'backdropBlur function not supported in attributeModifier scenario.');
  }

  renderGroup(value: boolean): this {
    throw new BusinessError(100201, 'renderGroup function not supported in attributeModifier scenario.');
  }

  translate(value: TranslateOptions): this {
    throw new BusinessError(100201, 'translate function not supported in attributeModifier scenario.');
  }

  scale(value: ScaleOptions): this {
    throw new BusinessError(100201, 'scale function not supported in attributeModifier scenario.');
  }
  gridSpan(value: number): this {
    throw new BusinessError(100201, 'gridSpan function not supported in attributeModifier scenario.');
  }

  gridOffset(value: number): this {
    throw new BusinessError(100201, 'gridOffset function not supported in attributeModifier scenario.');
  }

  rotate(value: RotateOptions | RotateAngleOptions): this {
    throw new BusinessError(100201, 'rotate function not supported in attributeModifier scenario.');
  }

  transform(value: object): this {
    throw new BusinessError(100201, 'transform function not supported in attributeModifier scenario.');
  }

  transform3D(value: object): this {
    throw new BusinessError(100201, 'transform3D function not supported in attributeModifier scenario.');
  }

  onAppear(event: () => void): this {
    throw new BusinessError(100201, 'onAppear function not supported in attributeModifier scenario.');
  }

  onDisAppear(event: () => void): this {
    throw new BusinessError(100201, 'onDisAppear function not supported in attributeModifier scenario.');
  }

  onAttach(event: () => void): this {
    throw new BusinessError(100201, 'onAttach function not supported in attributeModifier scenario.');
  }

  onDetach(event: () => void): this {
    throw new BusinessError(100201, 'onDetach function not supported in attributeModifier scenario.');
  }

  onAreaChange(event: (oldValue: Area, newValue: Area) => void): this {
    throw new BusinessError(100201, 'onAreaChange function not supported in attributeModifier scenario.');
  }

  visibility(value: Visibility): this {
    throw new BusinessError(100201, 'visibility function not supported in attributeModifier scenario.');
  }

  flexGrow(value: number): this {
    throw new BusinessError(100201, 'flexGrow function not supported in attributeModifier scenario.');
  }

  flexShrink(value: number): this {
    throw new BusinessError(100201, 'flexShrink function not supported in attributeModifier scenario.');
  }

  flexBasis(value: number | string): this {
    throw new BusinessError(100201, 'flexBasis function not supported in attributeModifier scenario.');
  }

  alignSelf(value: ItemAlign): this {
    throw new BusinessError(100201, 'alignSelf function not supported in attributeModifier scenario.');
  }

  displayPriority(value: number): this {
    throw new BusinessError(100201, 'displayPriority function not supported in attributeModifier scenario.');
  }

  zIndex(value: number): this {
    throw new BusinessError(100201, 'zIndex function not supported in attributeModifier scenario.');
  }

  sharedTransition(id: string, options?: sharedTransitionOptions): this {
    throw new BusinessError(100201, 'sharedTransition function not supported in attributeModifier scenario.');
  }

  direction(value: Direction): this {
    throw new BusinessError(100201, 'direction function not supported in attributeModifier scenario.');
  }

  align(value: Alignment): this {
    throw new BusinessError(100201, 'align function not supported in attributeModifier scenario.');
  }

  position(value: Position): this {
    throw new BusinessError(100201, 'position function not supported in attributeModifier scenario.');
  }

  markAnchor(value: Position): this {
    throw new BusinessError(100201, 'markAnchor function not supported in attributeModifier scenario.');
  }

  offset(value: Position): this {
    throw new BusinessError(100201, 'offset function not supported in attributeModifier scenario.');
  }

  enabled(value: boolean): this {
    throw new BusinessError(100201, 'enabled function not supported in attributeModifier scenario.');
  }

  useSizeType(value: {
    xs?: number | { span: number; offset: number };
    sm?: number | { span: number; offset: number };
    md?: number | { span: number; offset: number };
    lg?: number | { span: number; offset: number };
  }): this {
    throw new BusinessError(100201, 'useSizeType function not supported in attributeModifier scenario.');
  }

  alignRules(value: AlignRuleOption): this {
    throw new BusinessError(100201, 'alignRules function not supported in attributeModifier scenario.');
  }

  aspectRatio(value: number): this {
    throw new BusinessError(100201, 'aspectRatio function not supported in attributeModifier scenario.');
  }

  clickEffect(value: ClickEffect | null): this {
    throw new BusinessError(100201, 'clickEffect function not supported in attributeModifier scenario.');
  }

  enableClickSoundEffect(enabled: boolean | undefined): this {
    throw new BusinessError(100201, 'enableClickSoundEffect function not supported in attributeModifier scenario.');
  }

  onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this {
    throw new BusinessError(100201, 'onDragStart function not supported in attributeModifier scenario.');
  }

  onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new BusinessError(100201, 'onDragEnter function not supported in attributeModifier scenario.');
  }

  onDragSpringLoading(callback: Callback<SpringLoadingContext> | null, configuration?: DragSpringLoadingConfiguration): this {
    throw new BusinessError(100201, 'onDragSpringLoading function not supported in attributeModifier scenario.');
  }

  onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new BusinessError(100201, 'onDragMove function not supported in attributeModifier scenario.');
  }

  onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new BusinessError(100201, 'onDragLeave function not supported in attributeModifier scenario.');
  }

  onDrop(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new BusinessError(100201, 'onDrop function not supported in attributeModifier scenario.');
  }

  onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new BusinessError(100201, 'onDragEnd function not supported in attributeModifier scenario.');
  }

  allowDrop(value: Array<UniformDataType> | Array<string>): this {
    throw new BusinessError(100201, 'allowDrop function not supported in attributeModifier scenario.');
  }

  draggable(value: boolean): this {
    throw new BusinessError(100201, 'draggable function not supported in attributeModifier scenario.');
  }

  overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number } }): this {
    throw new BusinessError(100201, 'overlay function not supported in attributeModifier scenario.');
  }

  linearGradient(value: {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    throw new BusinessError(100201, 'linearGradient function not supported in attributeModifier scenario.');
  }

  sweepGradient(value: {
    center: Array<any>;
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    throw new BusinessError(100201, 'sweepGradient function not supported in attributeModifier scenario.');
  }

  radialGradient(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }): this {
    throw new BusinessError(100201, 'radialGradient function not supported in attributeModifier scenario.');
  }

  motionPath(value: MotionPathOptions): this {
    throw new BusinessError(100201, 'motionPath function not supported in attributeModifier scenario.');
  }

  shadow(value: ShadowOptions | ShadowStyle): this {
    throw new BusinessError(100201, 'shadow function not supported in attributeModifier scenario.');
  }

  mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this {
    throw new BusinessError(100201, 'mask function not supported in attributeModifier scenario.');
  }

  key(value: string): this {
    throw new BusinessError(100201, 'key function not supported in attributeModifier scenario.');
  }

  id(value: string): this {
    throw new BusinessError(100201, 'id function not supported in attributeModifier scenario.');
  }

  geometryTransition(id: string): this {
    throw new BusinessError(100201, 'geometryTransition function not supported in attributeModifier scenario.');
  }

  bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
    throw new BusinessError(100201, 'bindPopup function not supported in attributeModifier scenario.');
  }

  bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
    throw new BusinessError(100201, 'bindMenu function not supported in attributeModifier scenario.');
  }

  bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
    throw new BusinessError(100201, 'bindContextMenu function not supported in attributeModifier scenario.');
  }

  bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
    throw new BusinessError(100201, 'bindContentCover function not supported in attributeModifier scenario.');
  }

  blendMode(value: BlendMode): this {
    throw new BusinessError(100201, 'blendMode function not supported in attributeModifier scenario.');
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    throw new BusinessError(100201, 'clip function not supported in attributeModifier scenario.');
  }

  bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this {
    throw new BusinessError(100201, 'bindSheet function not supported in attributeModifier scenario.');
  }

  stateStyles(value: StateStyles): this {
    throw new BusinessError(100201, 'stateStyles function not supported in attributeModifier scenario.');
  }

  restoreId(value: number): this {
    throw new BusinessError(100201, 'restoreId function not supported in attributeModifier scenario.');
  }

  onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this {
    throw new BusinessError(100201, 'onVisibleAreaChange function not supported in attributeModifier scenario.');
  }

  sphericalEffect(value: number): this {
    throw new BusinessError(100201, 'sphericalEffect function not supported in attributeModifier scenario.');
  }

  lightUpEffect(value: number): this {
    throw new BusinessError(100201, 'lightUpEffect function not supported in attributeModifier scenario.');
  }

  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    throw new BusinessError(100201, 'pixelStretchEffect function not supported in attributeModifier scenario.');
  }

  keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this {
    throw new BusinessError(100201, 'keyboardShortcut function not supported in attributeModifier scenario.');
  }

  accessibilityGroup(value: boolean): this {
    throw new BusinessError(100201, 'accessibilityGroup function not supported in attributeModifier scenario.');
  }

  accessibilityText(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityTextModifier.identity, SpanAccessibilityTextModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityTextModifier.identity, SpanAccessibilityTextModifier, undefined);
    }
    return this;
  }

  accessibilityDescription(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityDescriptionModifier.identity, SpanAccessibilityDescriptionModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityDescriptionModifier.identity, SpanAccessibilityDescriptionModifier, undefined);
    }
    return this;
  }

  accessibilityLevel(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityLevelModifier.identity, SpanAccessibilityLevelModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityLevelModifier.identity, SpanAccessibilityLevelModifier, undefined);
    }
    return this;
  }

  obscured(reasons: Array<ObscuredReasons>): this {
    throw new BusinessError(100201, 'obscured function not supported in attributeModifier scenario.');
  }

  reuseId(id: string): this {
    throw new BusinessError(100201, 'reuseId function not supported in attributeModifier scenario.');
  }

  renderFit(fitMode: RenderFit): this {
    throw new BusinessError(100201, 'renderFit function not supported in attributeModifier scenario.');
  }

  systemMaterial(material: SystemUiMaterial | undefined) {
    throw new BusinessError(100201, 'systemMaterial function not supported in attributeModifier scenario.');
  }

  materialFilter(filter: Filter) {
    throw new BusinessError(100201, 'materialFilter function not supported in attributeModifier scenario.');
  }

  attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
    return this;
  }
  decoration(value: { type: TextDecorationType, color?: ResourceColor; style?: TextDecorationStyle }): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanDecorationModifier.identity, SpanDecorationModifier, value);
    return this;
  }
  font(value: Font): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontSizeModifier.identity, SpanFontSizeModifier, value?.size);
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier, value?.weight);
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier, value?.family);
    modifierWithKey(this._modifiersWithKeys, SpanFontStyleModifier.identity, SpanFontStyleModifier, value?.style);
    return this;
  }
  lineHeight(value: Length): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanLineHeightModifier.identity, SpanLineHeightModifier, value);
    return this;
  }
  fontSize(value: Length): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontSizeModifier.identity, SpanFontSizeModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontColorModifier.identity, SpanFontColorModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontStyleModifier.identity, SpanFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string | Resource): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier, value);
    return this;
  }
  fontFamily(value: string | Resource): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier, value);
    return this;
  }
  letterSpacing(value: number | string | Resource): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanLetterSpacingModifier.identity, SpanLetterSpacingModifier, value);
    return this;
  }
  baselineOffset(value: LengthMetrics): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanBaselineOffsetModifier.identity, SpanBaselineOffsetModifier, value);
    return this;
  }
  textCase(value: TextCase): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanTextCaseModifier.identity, SpanTextCaseModifier, value);
    return this;
  }
  textBackgroundStyle(value: TextBackgroundStyle): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanTextBackgroundStyleModifier.identity, SpanTextBackgroundStyleModifier, value);
    return this;
  }
  textShadow(value: ShadowOptions | Array<ShadowOptions>): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanTextShadowModifier.identity, SpanTextShadowModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Span.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFuncWithoutStateStyles.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSpanComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SpanModifier(nativePtr, classType);
  });
};
