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
class ArkXComponentComponent implements CommonMethod<XComponentAttribute> {
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
  width(value: Length): this {
    throw new Error('Method not implemented.');
  }
  height(value: Length): this {
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
    throw new Error('Method not implemented.');
  }
  backgroundImageSize(value: SizeOptions | ImageSize): this {
    throw new Error('Method not implemented.');
  }
  backgroundImagePosition(value: Alignment | Position): this {
    throw new Error('Method not implemented.');
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
  colorBlend(value: string | Resource | Color): this {
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
  hueRotate(value: string | number): this {
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
  onDragStart(event: (event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this {
    throw new Error('Method not implemented.');
  }
  onDragEnter(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }
  onDragMove(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }
  onDragLeave(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }
  onDrop(event: (event: DragEvent, extraParams?: string) => void): this {
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
    throw new Error('Method not implemented.');
  }
  lightUpEffect(value: number): this {
    throw new Error('Method not implemented.');
  }
  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }
  attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
    return this;
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  onLoad(callback: (event?: object) => void): this {
    throw new Error('Method not implemented.');
  }

  onDestroy(event: () => void): this {
    throw new Error('Method not implemented.');
  }

}

// @ts-ignore
globalThis.XComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkXComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

class XComponentOpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('xComponentOpacity');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().xComponent.resetOpacity(node);
    }
    else {
      GetUINativeModule().xComponent.setOpacity(node, this.value);
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
      GetUINativeModule().xComponent.resetBackgroundColor(node);
    } else {
      GetUINativeModule().xComponent.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
