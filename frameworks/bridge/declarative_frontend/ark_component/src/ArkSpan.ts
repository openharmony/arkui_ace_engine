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
  constructor(value: Length) {
    super(value);
  }
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
  constructor(value: string | Resource) {
    super(value);
  }
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
  constructor(value: Length) {
    super(value);
  }
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
  constructor(value: number) {
    super(value);
  }
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
  constructor(value: number) {
    super(value);
  }
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
class SpanFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
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
class SpanLetterSpacingModifier extends ModifierWithKey<string> {
  constructor(value: string) {
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
class SpanFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
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
    if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
      isResourceEqual(this.stageValue.size, this.value.size)) ||
      (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
        this.stageValue.size === this.value.size)) &&
      ((isResource(this.stageValue.family) && isResource(this.value.family) &&
        isResourceEqual(this.stageValue.family, this.value.family)) ||
        (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
          this.stageValue.family === this.value.family))) {
      return false;
    } else {
      return true;
    }
  }
}
class SpanDecorationModifier extends ModifierWithKey<{ type: TextDecorationType, color?: ResourceColor }> {
  constructor(value: { type: TextDecorationType, color?: ResourceColor }) {
    super(value);
  }
  static identity = Symbol('spanDecoration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().span.resetDecoration(node);
    } else {
      getUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
    }
  }

  checkObjectDiff(): boolean {
    if (this.stageValue.type !== this.value.type) {
      return true;
    }
    if (isResource(this.stageValue.color) && isResource(this.value.color)) {
      return !isResourceEqual(this.stageValue.color, this.value.color);
    } else if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    } else {
      return true;
    }
  }
}
class SpanFontWeightModifier extends ModifierWithKey<string> {
  constructor(value: string) {
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

class ArkSpanComponent implements CommonMethod<SpanAttribute> {
  _modifiersWithKeys: Map<Symbol, ModifierWithKey<number | string | boolean | object>>;
  nativePtr: KNode;

  constructor(nativePtr: KNode) {
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
  }
  applyModifierPatch(): void {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
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
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }

  accessibilityDescription(value: string): this {
    throw new Error('Method not implemented.');
  }

  accessibilityLevel(value: string): this {
    throw new Error('Method not implemented.');
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
  decoration(value: { type: TextDecorationType, color?: ResourceColor }): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanDecorationModifier.identity, SpanDecorationModifier, value);
    return this;
  }
  font(value: Font): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontModifier.identity, SpanFontModifier, value);
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
  fontWeight(value: number | FontWeight | string): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier, value);
    return this;
  }
  fontFamily(value: string | Resource): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier, value);
    return this;
  }
  letterSpacing(value: number | string): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanLetterSpacingModifier.identity, SpanLetterSpacingModifier, value);
    return this;
  }
  textCase(value: TextCase): SpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SpanTextCaseModifier.identity, SpanTextCaseModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Span.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSpanComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};