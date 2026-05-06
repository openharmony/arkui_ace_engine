/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

declare interface TouchEvent {
}

declare interface MouseEvent {
}

declare interface AxisEvent {
}

declare interface Position { x?: number; y?: number; }

declare type InputEventType = TouchEvent | MouseEvent | AxisEvent;

interface UpdateFuncRecord {
  updateFunc: UpdateFunc;
  componentName: string;
  node?: object;
  getUpdateFunc(): UpdateFunc | undefined;
}

declare function wrapBuilder<Args extends Object[]>(
  builder: (...args: Args) => void
): WrappedBuilder<Args>;

declare class WrappedBuilder<Args extends Object[]> {
  builder: (...args: Args) => void;
  constructor(builder: (...args: Args) => void);
}

declare class __JSScopeUtil__ {
  static syncInstanceId(instanceId: number): void;
  static restoreInstanceId(): void;
}

declare interface Size {
  width: number;
  height: number;
}

declare enum XComponentType {
  SURFACE = 0,
  COMPONENT,
  TEXTURE
}

declare interface XComponentController { }
declare interface BuildOptions {
  nestingBuilderSupported?: boolean;
  lazyBuildSupported?: boolean;
  bindedViewOfBuilderNode?:ViewPU;
  localStorage?:LocalStorage;
  enableProvideConsumeCrossing?:boolean;
}

declare interface RegisterParams {
  name: string;
  idOfNode: Symbol
}

declare class FinalizationRegistry {
  constructor(fun: (arg0: RegisterParams | number) => void);
  register(target: BuilderNodeCommonBase | FrameNode, heldValue: RegisterParams | number): undefined;
}

declare function getUINativeModule(): ArkUINativeModule;

declare function applyUIAttributes(modifier: AttributeModifier<CommonAttribute>, nativeNode: NodePtr, component: ArkComponent): void;

declare interface CommonAttribute { }

declare interface AttributeModifier<T> { }

declare enum ModifierType {
  ORIGIN = 0,
  STATE = 1,
  FRAME_NODE = 2,
}

declare class ArkComponent {
  nativePtr: NodePtr;
  constructor(nativePtr: NodePtr, classType?: ModifierType);
  setNodePtr(noed: NodePtr);
  setInstanceId(instanceId: number): void;
  initialize(...args: Object[]);
  allowChildCount?(): number;
  allowChildTypes?(): string[];
}
declare class ArkTextInputComponent extends ArkComponent {}

declare class ArkTextComponent extends ArkComponent {}

declare class ArkColumnComponent extends ArkComponent {}

declare class ArkRowComponent extends ArkComponent {}

declare class ArkStackComponent extends ArkComponent {}

declare class ArkGridRowComponent extends ArkComponent {}

declare class ArkGridColComponent extends ArkComponent {}

declare class ArkBlankComponent extends ArkComponent {}

declare class ArkImageComponent extends ArkComponent {}

declare class ArkFlexComponent extends ArkComponent {}

declare class ArkSwiperComponent extends ArkComponent {}

declare class ArkProgressComponent extends ArkComponent {}

declare class ArkScrollComponent extends ArkComponent {}

declare class ArkRelativeContainerComponent extends ArkComponent {}

declare class ArkListComponent extends ArkComponent {}

declare class ArkListItemComponent extends ArkComponent {}

declare class ArkDividerComponent extends ArkComponent {}

declare class ArkLoadingProgressComponent extends ArkComponent {}

declare class ArkSearchComponent extends ArkComponent {}

declare class ArkButtonComponent extends ArkComponent {}

declare class ArkXComponentComponent extends ArkComponent {}

declare class ArkListItemGroupComponent extends ArkComponent {}

declare class ArkWaterFlowComponent extends ArkComponent {}

declare class ArkFlowItemComponent extends ArkComponent {}

declare class ArkSymbolGlyphComponent extends ArkComponent {}

declare class ArkMarqueeComponent extends ArkComponent {}

declare class ArkTextAreaComponent extends ArkComponent {}

declare class ArkQRCodeComponent extends ArkComponent {}

declare class ArkBadgeComponent extends ArkComponent {}

declare class ArkGridComponent extends ArkComponent {}

declare class ArkGridItemComponent extends ArkComponent {}

declare class ArkTextClockComponent extends ArkComponent {}

declare class ArkTextTimerComponent extends ArkComponent {}

declare class ArkCheckboxComponent extends ArkComponent {}

declare class ArkCheckboxGroupComponent extends ArkComponent {}

declare class ArkRadioComponent extends ArkComponent {}

declare class ArkRatingComponent extends ArkComponent {}

declare class ArkSliderComponent extends ArkComponent {}

declare class ArkSelectComponent extends ArkComponent {}

declare class ArkToggleComponent extends ArkComponent {}

declare class ArkLazyVGridLayoutComponent extends ArkComponent {}

declare class ArkContainerPickerComponent extends ArkComponent {}

declare class SwiperController {}

declare class Scroller {}

declare class TextController {}

declare class TextInputController {}

declare class TextAreaController {}

declare class UICommonEvent {
  private _nodePtr: NodePtr;
  private _instanceId: number;
  constructor(nodePtr: NodePtr);
  setInstanceId(instanceId: number): void;
  setNodePtr(nodePtr: NodePtr): void;
}

declare class UIScrollableCommonEvent extends UICommonEvent {}

declare class UIListEvent extends UIScrollableCommonEvent {}

declare class UIScrollEvent extends UIScrollableCommonEvent {}

declare class UIGridEvent extends UIScrollableCommonEvent {}

declare class UIWaterFlowEvent extends UIScrollableCommonEvent {}

declare class UIGestureEvent {
  private _nodePtr: NodePtr;
  private _weakPtr: WeakRef<FrameNode>;
  constructor();
  setNodePtr(nodePtr: NodePtr): void;
  setWeakNodePtr(weakPtr: WeakRef<FrameNode>): void;
  registerFrameNodeDeletedCallback(nodePtr): void;
}

declare class ModifierWithKey<T extends number | string | boolean | object> {
  stageValue?: T;
  value?: T;
  constructor(value: T);
  applyStage(node: NodePtr): boolean;
  applyPeer(node: NodePtr, reset: boolean): void;
  checkObjectDiff(): boolean;
}

declare class NativeStrongRef {
  getNativeHandle(): NodePtr;
  dispose(): void;
}

declare class NativeWeakRef {
  invalid(): boolean;
  upgrade(): NativeStrongRef;
  getNativeHandle(): NodePtr;
  dispose?(): void;
}

declare class NativeUtils {
  createNativeStrongRef(nodePtr: NodePtr): NativeStrongRef;
  createNativeWeakRef(nodePtr: NodePtr): NativeWeakRef;
}

declare function __getCustomProperty__(nodeId: number, key: string): Object | undefined;
declare function __getCustomPropertyString__(nodeId: number, key: string): string | undefined;

declare enum AnimationPropertyType {
  ROTATION = 0,
  TRANSLATION = 1,
  SCALE = 2,
  OPACITY = 3,
}

declare interface AnimateParam {
}

declare interface ArkUINativeModule {
  frameNode: FrameNodeNativeModule;
  nativeUtils: NativeUtilsNativeModule;
  renderNode: RenderNodeNativeModule;
  common: CommonNativeModule;
  nodeAdapter: NodeAdapterNativeModule;
  nodeContainer: NodeContainerNativeModule;

  // No validation
  swiper: any;
  scroll: any;
  list: any;
  waterFlow: any;
  grid: any;
  text: any;
  textInput: any;
  textArea: any;
  loadNativeModule(...args: any[]): any;
  xcomponentNode: any;
}

declare interface CommonNativeModule {
  getApiTargetVersion(): number;
  setOpacity(nodePtr: NodePtr, opacity: any): void;
  setTransform(nodePtr: NodePtr, transform: any): void;
}

declare interface NodeContainerNativeModule {
  clean(nodePtr: NodePtr): void;
  rebuild(containerId: number): void;
}

declare interface FrameNodeNativeModule {
  getFrameNodeRawPtr(nodePtr: NodePtr): number;
  invalidate(nodePtr: NodePtr): void;
  getIdByNodePtr(nodePtr: NodePtr): number;
  fireArkUIObjectLifecycleCallback(weakRef: WeakRef<any>, nodeType: string, type: string, nodePtr: NodePtr): void;
  createNativeStrongRefWithPtrVal(nodePtr: NodePtr): NativeStrongRef;
  isModifiable(nodePtr: NodePtr): boolean;
  checkIfCanCrossLanguageTreeOperating(nodePtr: NodePtr): boolean;
  addBuilderNode(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  removeBuilderNode(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  removeChild(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  clearBuilderNode(nodePtr: NodePtr): void;
  clearChildren(nodePtr: NodePtr): void;
  getFirstChildIndexWithoutExpand(nodePtr: NodePtr): number;
  getLastChildIndexWithoutExpand(nodePtr: NodePtr): number;
  getChildrenCount(nodePtr: NodePtr, isExpanded: boolean): number;
  getPositionToParent(nodePtr: NodePtr): Position;
  getPositionToScreen(nodePtr: NodePtr): Position;
  getPositionToWindow(nodePtr: NodePtr): Position;
  getGlobalPositionOnDisplay(nodePtr: NodePtr): Position;
  getPositionToParentWithTransform(nodePtr: NodePtr): Position;
  getPositionToScreenWithTransform(nodePtr: NodePtr): Position;
  getPositionToWindowWithTransform(nodePtr: NodePtr): Position;
  getMeasuredSize(nodePtr: NodePtr): Size;
  getLayoutPosition(nodePtr: NodePtr): Position;
  getConfigBorderWidth(nodePtr: NodePtr): EdgeWidths;
  getConfigPadding(nodePtr: NodePtr): EdgeWidths;
  getConfigMargin(nodePtr: NodePtr): EdgeWidths;
  getConfigSize(nodePtr: NodePtr): Size;
  getId(nodePtr: NodePtr): string;
  getNodeType(nodePtr: NodePtr): string;
  getOpacity(nodePtr: NodePtr): number;
  isVisible(nodePtr: NodePtr): boolean;
  isClipToFrame(nodePtr: NodePtr): boolean;
  isAttached(nodePtr: NodePtr): boolean;
  isOnMainTree(nodePtr: NodePtr): boolean;
  isOnRenderTree(nodePtr: NodePtr): boolean;
  getInspectorInfo(nodePtr: NodePtr): string;
  getCommonViewParentId(nodePtr: NodePtr): number;
  getCustomPropertyCapiByKey(nodePtr: NodePtr, key: string): string;
  setMeasuredSize(nodePtr: NodePtr, width: number, height: number): void;
  setLayoutPosition(nodePtr: NodePtr, x: number, y: number): void;
  measureNode(nodePtr: NodePtr, minWidth: number, minHeight: number, maxWidth: number, maxHeight: number, percentReferenceWidth: number, percentReferenceHeight: number): void;
  layoutNode(nodePtr: NodePtr, x: number, y: number): void;
  setNeedsLayout(nodePtr: NodePtr): void;
  getCrossLanguageOptions(nodePtr: NodePtr): boolean;
  getCrossLanguageTreeOperating(nodePtr: NodePtr): boolean;
  checkIfCanCrossLanguageAttributeSetting(nodePtr: NodePtr): boolean;
  triggerOnReuse(nodePtr: NodePtr): void;
  triggerOnRecycle(nodePtr: NodePtr): void;
  applyAttributesFinish(nodePtr: NodePtr): void;
  convertPoint(nodePtr: NodePtr, x: number | undefined | null, y: number | undefined | null, targteNodePtr: NodePtr): Position;
  convertPositionToWindow(nodePtr: NodePtr, x: number | undefined | null, y: number | undefined | null): Position;
  convertPositionFromWindow(nodePtr: NodePtr, x: number | undefined | null, y: number | undefined | null): Position;
  adoptChild(nodePtr: NodePtr, childNodePtr: NodePtr): number;
  removeAdoptedChild(nodePtr: NodePtr, childNodePtr: NodePtr): number;
  updateConfiguration(nodePtr: NodePtr): void;
  createNodeContent(): NativeStrongRef;

  // No validation for return values
  createFrameNode(self: FrameNode): any;
  createTransFrameNode(self: FrameNode, nativePointer: number): any;
  createTypedFrameNode(self: FrameNode, type: string, options?: object): any;
  createTransTypedFrameNode(self: FrameNode, type: string, options: object, nativePointer: number): any;
  createFrameNodes(count: number): any[];
  getFrameNodeById(nodePtr: NodePtr, id: string): any;
  getFrameNodeByUniqueId(nodePtr: NodePtr, id: number): any;
  appendChild(parentNodePtr: NodePtr, childNodePtr: NodePtr): any;
  insertChildAfter(parentNodePtr: NodePtr, childNodePtr: NodePtr, siblingNodePtr: NodePtr | null): any;
  moveTo(nodePtr: NodePtr, targetParentNodePtr: NodePtr, index: number): any;
  getChild(nodePtr: NodePtr, index: number, expandMode: number): any;
  getFirst(nodePtr: NodePtr, isExpanded: boolean): any;
  getFirstUINode(nodePtr: NodePtr): any;
  getNextSibling(nodePtr: NodePtr, isExpanded: boolean): any;
  getPreviousSibling(nodePtr: NodePtr, isExpanded: boolean): any;
  getParent(nodePtr: NodePtr): any;
  setCrossLanguageOptions(nodePtr: NodePtr, attributeSetting: boolean, treeOperating: boolean | undefined | null): any;
  addFrameNodeToNodeContent(nodePtr: NodePtr, nativePtr: NodePtr): any;
  removeFrameNodeFromNodeContent(nodePtr: NodePtr, nativePtr: NodePtr): any;

  // No validation
  getInteractionEventBindingInfo(...args: any[]): any;
  createAnimation(...args: any[]): any;
  cancelAnimations(...args: any[]): any;
  getNodePropertyValue(...args: any[]): any;
  addSupportedStates(...args: any[]): any;
  removeSupportedStates(...args: any[]): any;
}

declare interface RenderNodeNativeModule {
  createRenderNode(self: RenderNode): NativeStrongRef;
  createRenderNodeWithPtrVal(self: RenderNode, cptrVal: number): NativeStrongRef;
  setBackgroundColor(nodePtr: NodePtr, color: number): void;
  setClipToFrame(nodePtr: NodePtr, clipToFrame: boolean): void;
  setPivot(nodePtr: NodePtr, x: number, y: number): void;
  setPosition(nodePtr: NodePtr, x: number, y: number, unit: number): void;
  setRotation(nodePtr: NodePtr, x: number, y: number, z: number): void;
  setScale(nodePtr: NodePtr, x: number, y: number): void;
  setShadowColor(nodePtr: NodePtr, color: number): void;
  setShadowOffset(nodePtr: NodePtr, x: number, y: number, unit: number): void;
  setLabel(nodePtr: NodePtr, label: string): void;
  setShadowAlpha(nodePtr: NodePtr, alpha: number): void;
  setShadowElevation(nodePtr: NodePtr, elevation: number): void;
  setShadowRadius(nodePtr: NodePtr, radius: number): void;
  setSize(nodePtr: NodePtr, width: number, height: number, unit: number): void;
  setTranslate(nodePtr: NodePtr, x: number, y: number, z: number): void;
  setMarkNodeGroup(nodePtr: NodePtr, markNodeGroup: boolean): void;
  addBuilderNode(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  removeBuilderNode(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  removeChild(parentNodePtr: NodePtr, childNodePtr: NodePtr): void;
  clearBuilderNode(nodePtr: NodePtr): void;
  clearChildren(nodePtr: NodePtr): void;
  getNodeType(nodePtr: NodePtr): string;
  fireArkUIObjectLifecycleCallback(weakRef: WeakRef<RenderNode>, nodeType: string, type: string, nodePtr: NodePtr): void;
  invalidate(nodePtr: NodePtr): void;
  setBorderStyle(nodePtr: NodePtr, left: BorderStyle | undefined | null, top: BorderStyle | undefined | null,
    right: BorderStyle | undefined | null, bottom: BorderStyle | undefined | null): void;
  setBorderWidth(nodePtr: NodePtr, left: Number, top: Number, right: Number, bottom: Number, unit: LengthMetricsUnit): void;
  setBorderColor(nodePtr: NodePtr, left: Number, top: Number, right: Number, bottom: Number): void;
  setBorderRadius(nodePtr: NodePtr, topLeft: number, topRight: number,
    bottomLeft: number, bottomRight: number, uint: LengthMetricsUnit): void;
  setRectMask(nodePtr: NodePtr, left: number, top: number, right: number, bottom: number,
    fillColor: number, strokeColor: number, strokeWidth: number): void;
  setCircleMask(nodePtr: NodePtr, centerX: number, centerY: number, radius: number,
    fillColor: number, strokeColor: number, strokeWidth: number): void;
  setRoundRectMask(nodePtr: NodePtr,
    cornersTopLeftX: number,
    cornersTopLeftY: number,
    cornersTopRightX: number,
    cornersTopRightY: number,
    cornersBottomLeftX: number,
    cornersBottomLeftY: number,
    cornersBottomRightX: number,
    cornersBottomRightY: number,
    rectLeft: number,
    rectTop: number,
    rectRight: number,
    rectBottom: number,
    fillColor: number,
    strokeColor: number,
    strokeWidth: number): void;
  setOvalMask(nodePtr: NodePtr, left: number, top: number, right: number, bottom: number,
    fillColor: number, strokeColor: number, strokeWidth: number): void;
  setPath(nodePtr: NodePtr, commands: string, fillColor: number, strokeColor: number, strokeWidth: number): void;
  setRectClip(nodePtr: NodePtr, left: number, top: number, right: number, bottom: number): void;
  setCircleClip(nodePtr: NodePtr, centerX: number, centerY: number, radius: number): void;
  setRoundRectClip(nodePtr: NodePtr,
    cornersTopLeftX: number,
    cornersTopLeftY: number,
    cornersTopRightX: number,
    cornersTopRightY: number,
    cornersBottomLeftX: number,
    cornersBottomLeftY: number,
    cornersBottomRightX: number,
    cornersBottomRightY: number,
    rectLeft: number,
    rectTop: number,
    rectRight: number,
    rectBottom: number): void;
  setOvalClip(nodePtr: NodePtr, left: number, top: number, right: number, bottom: number): void;
  setPathClip(nodePtr: NodePtr, path: string): void;
  setBackgroundBlur(nodePtr: NodePtr, radius: number, grayscale1: number, grayscale2: number): void;
  setContentBlur(nodePtr: NodePtr, radius: number, grayscale1: number, grayscale2: number): void;
  setForegroundBlur(nodePtr: NodePtr, radius: number): void;

  // No validation for return values
  appendChild(parentNodePtr: NodePtr, childNodePtr: NodePtr): any;
  insertChildAfter(parentNodePtr: NodePtr, childNodePtr: NodePtr, siblingNodePtr: NodePtr | null): any;
}

declare interface NodeAdapterNativeModule {
  createAdapter(): NativeStrongRef;
  setCallbacks(nodePtr: NodePtr, thisObj: NodeAdapter, ...args: any[]): void;
  getNodeType(nodePtr: NodePtr): string;
  fireArkUIObjectLifecycleCallback(weakRef: WeakRef<NodeAdapter>, nodeType: string, type: string, nodePtr: NodePtr): void;
  setTotalNodeCount(nodePtr: NodePtr, count: number): void;
  notifyItemChanged(nodePtr: NodePtr, start: number, count: number): void;
  notifyItemReloaded(nodePtr: NodePtr): void;
  notifyItemRemoved(nodePtr: NodePtr, start: number, count: number): void;
  notifyItemInserted(nodePtr: NodePtr, start: number, count: number): void;
  notifyItemMoved(nodePtr: NodePtr, from: number, to: number): void;
  getAllItems(nodePtr: NodePtr): Array<NodeInfo>;
  attachNodeAdapter(adapterPtr: NodePtr, frameNodePtr: NodePtr): boolean;
  detachNodeAdapter(nodePtr: NodePtr): void;
}

declare interface NativeUtilsNativeModule {
  // No validation for return values;
  createNativeStrongRef(nodePtr: NodePtr): any;
  createNativeWeakRef(nodePtr: NodePtr): any;

  // No validation
  resoureToLengthMetrics(...args: any[]): any;
  parseResourceColor(...args: any[]): any;
  blendColor(...args: any[]): any;
}
