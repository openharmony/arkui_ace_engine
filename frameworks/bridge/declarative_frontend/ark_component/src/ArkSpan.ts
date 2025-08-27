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
    throw new Error('Method not implemented.');
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
  width(value: Length): this {
    throw new Error('Method not implemented.');
  }

  height(value: Length): this {
    throw new Error('Method not implemented.');
  }

  expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
    throw new Error('Method not implemented.');
  }

  responseRegion(value: Array<Rectangle> | Rectangle): this {
    throw new Error('Method not implemented.');
  }

  mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
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

  layoutWeight(value: number | string): this {
    throw new Error('Method not implemented.');
  }

  padding(value: Padding | Length): this {
    throw new Error('Method not implemented.');
  }

  margin(value: Margin | Length): this {
    throw new Error('Method not implemented.');
  }

  background(builder: CustomBuilder, options?: { align?: Alignment }): this {
    throw new Error('Method not implemented.');
  }

  backgroundColor(value: ResourceColor): this {
    throw new Error('Method not implemented.');
  }

  backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
    throw new Error('Method not implemented.');
  }

  backgroundImageSize(value: SizeOptions | ImageSize): this {
    throw new Error('Method not implemented.');
  }

  backgroundImagePosition(value: Position | Alignment): this {
    throw new Error('Method not implemented.');
  }

  backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
    throw new Error('Method not implemented.');
  }

  foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
    throw new Error('Method not implemented.');
  }

  opacity(value: number | Resource): this {
    throw new Error('Method not implemented.');
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

  foregroundColor(value: ResourceColor | ColoringStrategy): this {
    throw new Error('Method not implemented.');
  }

  onClick(event: (event?: ClickEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, SpanOnHoverModifier.identity, SpanOnHoverModifier, event);
    return this;
  }

  hoverEffect(value: HoverEffect): this {
    throw new Error('Method not implemented.');
  }

  onMouse(event: (event?: MouseEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onTouch(event: (event?: TouchEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onKeyEvent(event: (event?: KeyEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  focusable(value: boolean): this {
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

  defaultFocus(value: boolean): this {
    throw new Error('Method not implemented.');
  }

  groupDefaultFocus(value: boolean): this {
    throw new Error('Method not implemented.');
  }

  focusOnTouch(value: boolean): this {
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
    throw new Error('Method not implemented.');
  }

  linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
    throw new Error('Method not implemented.');
  }

  brightness(value: number): this {
    throw new Error('Method not implemented.');
  }

  contrast(value: number): this {
    throw new Error('Method not implemented.');
  }

  grayscale(value: number): this {
    throw new Error('Method not implemented.');
  }

  colorBlend(value: Color | string | Resource): this {
    throw new Error('Method not implemented.');
  }

  saturate(value: number): this {
    throw new Error('Method not implemented.');
  }

  sepia(value: number): this {
    throw new Error('Method not implemented.');
  }

  invert(value: number): this {
    throw new Error('Method not implemented.');
  }

  hueRotate(value: number | string): this {
    throw new Error('Method not implemented.');
  }

  useEffect(value: boolean): this {
    throw new Error('Method not implemented.');
  }

  backdropBlur(value: number): this {
    throw new Error('Method not implemented.');
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

  rotate(value: RotateOptions | RotateAngleOptions): this {
    throw new Error('Method not implemented.');
  }

  transform(value: object): this {
    throw new Error('Method not implemented.');
  }

  transform3D(value: object): this {
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

  flexBasis(value: number | string): this {
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

  clickEffect(value: ClickEffect | null): this {
    throw new Error('Method not implemented.');
  }

  onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this {
    throw new Error('Method not implemented.');
  }

  onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragSpringLoading(callback: Callback<SpringLoadingContext> | null, configuration?: DragSpringLoadingConfiguration): this {
    throw new Error('Method not implemented.');
  }

  onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDrop(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  allowDrop(value: Array<UniformDataType>): this {
    throw new Error('Method not implemented.');
  }

  draggable(value: boolean): this {
    throw new Error('Method not implemented.');
  }

  overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number } }): this {
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

  bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
    throw new Error('Method not implemented.');
  }

  bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
    throw new Error('Method not implemented.');
  }

  bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
    throw new Error('Method not implemented.');
  }

  blendMode(value: BlendMode): this {
    throw new Error('Method not implemented.');
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
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

  onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this {
    throw new Error('Method not implemented.');
  }

  sphericalEffect(value: number): this {
    throw new Error('Method not implemented.');
  }

  lightUpEffect(value: number): this {
    throw new Error('Method not implemented.');
  }

  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    throw new Error('Method not implemented.');
  }

  keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this {
    throw new Error('Method not implemented.');
  }

  accessibilityGroup(value: boolean): this {
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }

  reuseId(id: string): this {
    throw new Error('Method not implemented.');
  }

  renderFit(fitMode: RenderFit): this {
    throw new Error('Method not implemented.');
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
