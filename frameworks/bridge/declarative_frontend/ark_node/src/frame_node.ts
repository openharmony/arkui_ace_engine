/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
/// <reference path="./disposable.ts" />
interface LayoutConstraint {
  maxSize: Size;
  minSize: Size;
  percentReference: Size;
}

interface CrossLanguageOptions {
  attributeSetting?: boolean;
}

interface InteractionEventBindingInfo  {
  baseEventRegistered?: boolean;
  nodeEventRegistered?: boolean;
  nativeEventRegistered?: boolean;
  builtInEventRegistered?: boolean;
}

enum ExpandMode {
  NOT_EXPAND = 0,
  EXPAND = 1,
  LAZY_EXPAND = 2,
}

enum UIState {
  NORMAL = 0 ,
  PRESSED = 1 << 0 ,
  FOCUSED = 1 << 1 ,
  DISABLED = 1 << 2 ,
  SELECTED = 1 << 3 ,
}

declare enum EventQueryType {
  ON_CLICK = 0,
}

declare type UIStatesChangeHandler = (node: FrameNode, currentUIStates: number) => void;

class FrameNode extends Disposable {
  public _nodeId: number;
  protected _commonAttribute: ArkComponent;
  protected _commonEvent: UICommonEvent;
  public _componentAttribute: ArkComponent;
  public _scrollableEvent: UIScrollableCommonEvent;
  protected _gestureEvent: UIGestureEvent;
  protected _childList: Map<number, FrameNode>;
  protected _nativeRef: NativeStrongRef | NativeWeakRef;
  protected renderNode_: RenderNode;
  protected baseNode_: BaseNode;
  protected builderNode_: JSBuilderNode;
  protected uiContext_: UIContext | undefined | null;
  protected nodePtr_: NodePtr;
  protected instanceId_?: number;
  private nodeAdapterRef_?: NodeAdapter;
  constructor(uiContext: UIContext, type: string, options?: object) {
    super();
    if (uiContext === undefined) {
      throw Error('Node constructor error, param uiContext error');
    } else {
      if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
        throw Error(
          'Node constructor error, param uiContext is invalid'
        );
      }
    }
    this.instanceId_ = uiContext.instanceId_;
    this.uiContext_ = uiContext;
    this._nodeId = -1;
    this._childList = new Map();
    if (type === 'BuilderRootFrameNode') {
      this.renderNode_ = new RenderNode(type);
      this.renderNode_.setFrameNode(new WeakRef(this));
      return;
    }
    if (type === 'ProxyFrameNode') {
      return;
    }
    let result;
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    if (type === undefined || type === "CustomFrameNode") {
      this.renderNode_ = new RenderNode('CustomFrameNode');
      result = getUINativeModule().frameNode.createFrameNode(this);
    } else {
      result = getUINativeModule().frameNode.createTypedFrameNode(this, type, options);
    }
    __JSScopeUtil__.restoreInstanceId();
    this._nativeRef = result?.nativeStrongRef;
    this._nodeId = result?.nodeId;
    this.nodePtr_ = this._nativeRef?.getNativeHandle();
    this.renderNode_?.setNodePtr(result?.nativeStrongRef);
    this.renderNode_?.setFrameNode(new WeakRef(this));
    if (result === undefined || this._nodeId === -1) {
      return;
    }
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, new WeakRef(this));
    FrameNodeFinalizationRegisterProxy.register(this, this._nodeId);

  }
  invalidate() {
    if (this.nodePtr_ === undefined || this.nodePtr_ === null) {
      return;
    }
    getUINativeModule().frameNode.invalidate(this.nodePtr_);
  }
  getType(): string {
    return 'CustomFrameNode';
  }
  setRenderNode(nativeRef: NativeStrongRef): void {
    this.renderNode_?.setNodePtr(nativeRef);
  }
  getRenderNode(): RenderNode | null {
    if (
      this.renderNode_ !== undefined &&
      this.renderNode_ !== null &&
      this.renderNode_.getNodePtr() !== null
    ) {
      return this.renderNode_;
    }
    return null;
  }
  setNodePtr(nativeRef: NativeStrongRef | NativeWeakRef, nodePtr: NodePtr): void {
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nativeRef = nativeRef;
    this.nodePtr_ = nodePtr ? nodePtr : this._nativeRef?.getNativeHandle();
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this._nodeId = getUINativeModule().frameNode.getIdByNodePtr(this.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    if (this._nodeId === -1) {
      return;
    }
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, new WeakRef(this));
    FrameNodeFinalizationRegisterProxy.register(this, this._nodeId);
  }
  resetNodePtr(): void {
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = null;
    this.nodePtr_ = null;
    this.renderNode_?.resetNodePtr();
  }
  setBaseNode(baseNode: BaseNode | null): void {
    this.baseNode_ = baseNode;
    this.renderNode_?.setBaseNode(baseNode);
  }
  setBuilderNode(builderNode: JSBuilderNode | null): void {
    this.builderNode_ = builderNode;
  }
  getBuilderNode(): JSBuilderNode | null {
    return this.builderNode_ || null;
  }
  setAdapterRef(adapter: NodeAdapter | undefined): void {
    this.nodeAdapterRef_ = adapter;
  }
  getNodePtr(): NodePtr | null {
    return this.nodePtr_;
  }
  getValidNodePtr(): NodePtr {
    const node = this.getNodePtr();
    if (node === null) {
      throw Error('The FrameNode has been disposed!');
    } else {
      return node;
    }
  }
  dispose(): void {
    super.dispose();
    if (this.nodePtr_) {
      getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback(new WeakRef(this), 'FrameNode', this.getNodeType() || 'FrameNode', this.nodePtr_);
    }
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = null;
    this.nodePtr_ = null;
  }
  
  isDisposed(): boolean {
    return super.isDisposed() && (this._nativeRef === undefined ||
     this._nativeRef === null || this._nativeRef instanceof NativeWeakRef && this._nativeRef.invalid());
  }

  static disposeTreeRecursively(node: FrameNode | null): void {
    if (node === null) {
      return;
    }
    let child = node.getFirstChildWithoutExpand();
    FrameNode.disposeTreeRecursively(child);
    let sibling = node.getNextSiblingWithoutExpand();
    FrameNode.disposeTreeRecursively(sibling);
    node.dispose();
  }

  disposeTree(): void {
    let parent = this.getParent();
    if (parent?.getNodeType() === "NodeContainer") {
      getUINativeModule().nodeContainer.clean(parent?.getNodePtr());
    } else {
      parent?.removeChild(this);
    }
    FrameNode.disposeTreeRecursively(this);
  }

  checkType(): void {
    if (!this.isModifiable()) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
  }
  isModifiable(): boolean {
    return this._nativeRef !== undefined && this._nativeRef !== null;
  }

  convertToFrameNode(nodePtr: NodePtr, nodeId: number = -1): FrameNode | null {
    if (nodeId === -1) {
      __JSScopeUtil__.syncInstanceId(this.instanceId_);
      nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
      __JSScopeUtil__.restoreInstanceId();
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      if (frameNode) {
        return frameNode;
      }
    }
    if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
      __JSScopeUtil__.syncInstanceId(this.instanceId_);
      let frameNode = new ProxyFrameNode(this.uiContext_);
      let node = getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr);
      __JSScopeUtil__.restoreInstanceId();
      frameNode.setNodePtr(node);
      frameNode._nodeId = nodeId;
      FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(frameNode._nodeId, new WeakRef(frameNode));
      FrameNodeFinalizationRegisterProxy.register(frameNode, frameNode._nodeId);
      return frameNode;
    }
    return null;
  }

  checkValid(node?: FrameNode): boolean {
    return true;
  }

  appendChild(node: FrameNode): void {
    if (node === undefined || node === null) {
      return;
    }
    if (node.getType() === 'ProxyFrameNode' || !this.checkValid(node)) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, node.nodePtr_);
    getUINativeModule().frameNode.addBuilderNode(this.nodePtr_, node.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    if (!flag) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    this._childList.set(node._nodeId, node);
  }

  addComponentContent(content: ComponentContent): void {
    if (content === undefined || content === null || content.getNodePtr() === null || content.getNodePtr() == undefined) {
      return;
    }
    if (!this.checkValid() || !this.isModifiable()) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, content.getNodeWithoutProxy());
    getUINativeModule().frameNode.addBuilderNode(this.nodePtr_, content.getNodePtr());
    __JSScopeUtil__.restoreInstanceId();
    if (!flag) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    } else {
      content.setAttachedParent(new WeakRef<FrameNode>(this));
    }
  }

  removeComponentContent(content: ComponentContent): void {
    if (content === undefined || content === null || content.getNodePtr() === null || content.getNodePtr() === undefined) {
      return;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.removeBuilderNode(this.nodePtr_, content.getNodePtr());
    getUINativeModule().frameNode.removeChild(this.nodePtr_, content.getNodePtr());
    content.setAttachedParent(undefined);
    __JSScopeUtil__.restoreInstanceId();
  }

  insertChildAfter(child: FrameNode, sibling: FrameNode): void {
    if (child === undefined || child === null) {
      return;
    }
    if (child.getType() === 'ProxyFrameNode' || !this.checkValid(child)) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    let flag = true;
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    if (sibling === undefined || sibling === null) {
      flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, null);
    } else {
      flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, sibling.getNodePtr());
    }
    getUINativeModule().frameNode.addBuilderNode(this.nodePtr_, child.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    if (!flag) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    this._childList.set(child._nodeId, child);
  }

  removeChild(node: FrameNode): void {
    if (node === undefined || node === null) {
      return;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.removeBuilderNode(this.nodePtr_, node.nodePtr_);
    getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.delete(node._nodeId);
  }

  clearChildren(): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.clearBuilderNode(this.nodePtr_);
    getUINativeModule().frameNode.clearChildren(this.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.clear();
  }

  moveTo(targetParent: FrameNode, index?: number): void {
    if (targetParent === undefined || targetParent === null) {
      return;
    }
    if (index === undefined || index === null) {
      index = -1;
    }
    const oldParent = this.getParent();
    if (oldParent && !oldParent.isModifiable() || !targetParent.isModifiable() || !targetParent.checkValid(this)) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.moveTo(this.nodePtr_, targetParent.nodePtr_, index);
    __JSScopeUtil__.restoreInstanceId();
    if (oldParent) {
      oldParent._childList.delete(this._nodeId);
    }
    targetParent._childList.set(this._nodeId, this);
  }

  getChild(index: number, expandMode?: ExpandMode): FrameNode | null {
    const result = getUINativeModule().frameNode.getChild(this.getNodePtr(), index, expandMode);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getFirstChildIndexWithoutExpand(): number {
    return getUINativeModule().frameNode.getFirstChildIndexWithoutExpand(this.getNodePtr());
  }

  getLastChildIndexWithoutExpand(): number {
    return getUINativeModule().frameNode.getLastChildIndexWithoutExpand(this.getNodePtr());
  }

  getFirstChild(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getFirstChildWithoutExpand(): FrameNode | null {
    const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), false);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getNextSibling(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getNextSiblingWithoutExpand(): FrameNode | null {
    const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), false);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getPreviousSibling(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getPreviousSibling(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getParent(): FrameNode | null {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const result = getUINativeModule().frameNode.getParent(this.getNodePtr());
    const nodeId = result?.nodeId;
    __JSScopeUtil__.restoreInstanceId();
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getChildrenCount(isExpanded?: boolean): number {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const childrenCount = getUINativeModule().frameNode.getChildrenCount(this.nodePtr_, isExpanded);
    __JSScopeUtil__.restoreInstanceId();
    return childrenCount;
  }

  getPositionToParent(): Position {
    const position = getUINativeModule().frameNode.getPositionToParent(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToScreen(): Position {
    const position = getUINativeModule().frameNode.getPositionToScreen(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToWindow(): Position {
    const position = getUINativeModule().frameNode.getPositionToWindow(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getGlobalPositionOnDisplay(): Position {
    const position = getUINativeModule().frameNode.getGlobalPositionOnDisplay(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToParentWithTransform(): Position {
    const position = getUINativeModule().frameNode.getPositionToParentWithTransform(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToScreenWithTransform(): Position {
    const position = getUINativeModule().frameNode.getPositionToScreenWithTransform(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToWindowWithTransform(): Position {
    const position = getUINativeModule().frameNode.getPositionToWindowWithTransform(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getMeasuredSize(): Size {
    const size = getUINativeModule().frameNode.getMeasuredSize(this.getValidNodePtr());
    return { width: size[0], height: size[1] };
  }

  getLayoutPosition(): Position {
    const position = getUINativeModule().frameNode.getLayoutPosition(this.getValidNodePtr());
    return { x: position[0], y: position[1] };
  }

  getUserConfigBorderWidth(): EdgesT<LengthMetrics> {
    const borderWidth = getUINativeModule().frameNode.getConfigBorderWidth(this.getNodePtr());
    return {
      top: new LengthMetrics(borderWidth[0], borderWidth[1]),
      right: new LengthMetrics(borderWidth[2], borderWidth[3]),
      bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
      left: new LengthMetrics(borderWidth[6], borderWidth[7])
    };
  }

  getUserConfigPadding(): EdgesT<LengthMetrics> {
    const borderWidth = getUINativeModule().frameNode.getConfigPadding(this.getNodePtr());
    return {
      top: new LengthMetrics(borderWidth[0], borderWidth[1]),
      right: new LengthMetrics(borderWidth[2], borderWidth[3]),
      bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
      left: new LengthMetrics(borderWidth[6], borderWidth[7])
    };
  }

  getUserConfigMargin(): EdgesT<LengthMetrics> {
    const margin = getUINativeModule().frameNode.getConfigMargin(this.getNodePtr());
    return {
      top: new LengthMetrics(margin[0], margin[1]),
      right: new LengthMetrics(margin[2], margin[3]),
      bottom: new LengthMetrics(margin[4], margin[5]),
      left: new LengthMetrics(margin[6], margin[7])
    };
  }

  getUserConfigSize(): SizeT<LengthMetrics> {
    const size = getUINativeModule().frameNode.getConfigSize(this.getNodePtr());
    return {
      width: new LengthMetrics(size[0], size[1]),
      height: new LengthMetrics(size[2], size[3])
    };
  }

  getId(): string {
    return getUINativeModule().frameNode.getId(this.getNodePtr());
  }

  getUniqueId(): number {
    return getUINativeModule().frameNode.getIdByNodePtr(this.getNodePtr());
  }

  getNodeType(): string {
    return getUINativeModule().frameNode.getNodeType(this.getNodePtr());
  }

  getOpacity(): number {
    return getUINativeModule().frameNode.getOpacity(this.getNodePtr());
  }

  isVisible(): boolean {
    return getUINativeModule().frameNode.isVisible(this.getNodePtr());
  }

  isClipToFrame(): boolean {
    return getUINativeModule().frameNode.isClipToFrame(this.getNodePtr());
  }

  isAttached(): boolean {
    return getUINativeModule().frameNode.isAttached(this.getNodePtr());
  }

  getInspectorInfo(): Object {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const inspectorInfoStr = getUINativeModule().frameNode.getInspectorInfo(this.getNodePtr());
    __JSScopeUtil__.restoreInstanceId();
    const inspectorInfo = JSON.parse(inspectorInfoStr);
    return inspectorInfo;
  }

  getCustomProperty(key: string): Object | undefined {
    if (key === undefined) {
      return undefined;
    }
    let value = __getCustomProperty__(this._nodeId, key);
    if (value === undefined) {
      const valueStr = getUINativeModule().frameNode.getCustomPropertyCapiByKey(this.getNodePtr(), key);
      value = valueStr === undefined ? undefined : valueStr;
    }
    return value;
  }

  setMeasuredSize(size: Size): void {
    getUINativeModule().frameNode.setMeasuredSize(this.getNodePtr(), Math.max(size.width, 0),
      Math.max(size.height, 0));
  }

  setLayoutPosition(position: Position): void {
    getUINativeModule().frameNode.setLayoutPosition(this.getNodePtr(), position.x, position.y);
  }

  measure(constraint: LayoutConstraint): void {
    const minSize: Size = constraint.minSize;
    const maxSize: Size = constraint.maxSize;
    const percentReference: Size = constraint.percentReference;
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.measureNode(this.getNodePtr(), minSize.width, minSize.height, maxSize.width,
      maxSize.height, percentReference.width, percentReference.height);
    __JSScopeUtil__.restoreInstanceId();
  }

  layout(position: Position): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.layoutNode(this.getNodePtr(), position.x, position.y);
    __JSScopeUtil__.restoreInstanceId();
  }

  setNeedsLayout(): void {
    getUINativeModule().frameNode.setNeedsLayout(this.getNodePtr());
  }

  setCrossLanguageOptions(options: CrossLanguageOptions): void {
    if (!this.isModifiable()) {
      throw { message: 'The FrameNode cannot be set whether to support cross-language common attribute setting.', code: 100022 };
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const result = getUINativeModule().frameNode.setCrossLanguageOptions(this.getNodePtr(), options.attributeSetting ?? false);
    __JSScopeUtil__.restoreInstanceId();
    if (result !== 0) {
      throw { message: 'The FrameNode cannot be set whether to support cross-language common attribute setting.', code: 100022 };
    }
  }

  getCrossLanguageOptions(): CrossLanguageOptions {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const attributeSetting = getUINativeModule().frameNode.getCrossLanguageOptions(this.getNodePtr());
    __JSScopeUtil__.restoreInstanceId();
    return { attributeSetting: attributeSetting ?? false };
  }

  checkIfCanCrossLanguageAttributeSetting(): boolean {
    return this.isModifiable() || getUINativeModule().frameNode.checkIfCanCrossLanguageAttributeSetting(this.getNodePtr());
  }

  getInteractionEventBindingInfo(eventType: EventQueryType): InteractionEventBindingInfo {
    if (eventType === undefined || eventType === null) {
      return undefined;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    const eventBindingInfo = getUINativeModule().frameNode.getInteractionEventBindingInfo(this.getNodePtr(), eventType);
    __JSScopeUtil__.restoreInstanceId();
    if (!eventBindingInfo || (!eventBindingInfo.baseEventRegistered && !eventBindingInfo.nodeEventRegistered &&
      !eventBindingInfo.nativeEventRegistered && !eventBindingInfo.builtInEventRegistered)) {
      return undefined;
    }
    return {
      baseEventRegistered: eventBindingInfo.baseEventRegistered,
      nodeEventRegistered: eventBindingInfo.nodeEventRegistered,
      nativeEventRegistered: eventBindingInfo.nativeEventRegistered,
      builtInEventRegistered: eventBindingInfo.builtInEventRegistered,
    };
  }

  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new ArkComponent(this.nodePtr_, ModifierType.FRAME_NODE);
    }
    this._commonAttribute.setNodePtr(this.nodePtr_);
    this._commonAttribute.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    return this._commonAttribute;
  }

  get commonEvent(): UICommonEvent {
    let node = this.getNodePtr();
    if (this._commonEvent === undefined) {
      this._commonEvent = new UICommonEvent(node);
    }
    this._commonEvent.setNodePtr(node);
    this._commonEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    return this._commonEvent;
  }

  get gestureEvent(): UIGestureEvent {
    if (this._gestureEvent === undefined) {
        this._gestureEvent = new UIGestureEvent();
        this._gestureEvent.setNodePtr(this.nodePtr_);
        let weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(this.nodePtr_);
        this._gestureEvent.setWeakNodePtr(weakPtr);
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this._gestureEvent.registerFrameNodeDeletedCallback(this.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
    }
    return this._gestureEvent;
  }
  updateInstance(uiContext: UIContext): void {
    this.uiContext_ = uiContext;
    this.instanceId_ = uiContext.instanceId_;
  }
  createAnimation(property: AnimationPropertyType, startValue: number[] | undefined, endValue: number[], param: AnimateParam): boolean {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    let result = getUINativeModule().frameNode.createAnimation(this.getNodePtr(), property, startValue, endValue, param);
    __JSScopeUtil__.restoreInstanceId();
    return result;
  }
  cancelAnimations(properties: AnimationPropertyType[]): boolean {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    let result = getUINativeModule().frameNode.cancelAnimations(this.getNodePtr(), properties);
    __JSScopeUtil__.restoreInstanceId();
    return result;
  }
  getNodePropertyValue(property: AnimationPropertyType): number[] {
    return getUINativeModule().frameNode.getNodePropertyValue(this.getNodePtr(), property);
  }
  triggerOnReuse(): void {
    getUINativeModule().frameNode.triggerOnReuse(this.getNodePtr());
  }
  triggerOnRecycle(): void {
    getUINativeModule().frameNode.triggerOnRecycle(this.getNodePtr());
  }
  reuse(): void {
    this.triggerOnReuse();
  }
  recycle(): void {
    this.triggerOnRecycle();
  }
  addSupportedUIStates(uistates: number, statesChangeHandler: UIStatesChangeHandler, excludeInner?: boolean): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.addSupportedStates(this.getNodePtr(), uistates, (currentUIStates: number)=>{
      statesChangeHandler(this, currentUIStates);
    }, excludeInner);
    __JSScopeUtil__.restoreInstanceId();
  }
  removeSupportedUIStates(uiStates: number): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.removeSupportedStates(this.getNodePtr(), uiStates);
    __JSScopeUtil__.restoreInstanceId();
  }
}

class ImmutableFrameNode extends FrameNode {
  isModifiable(): boolean {
    return false;
  }
  invalidate() {
    return;
  }
  appendChild(node: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  insertChildAfter(child: FrameNode, sibling: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  removeChild(node: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  clearChildren(): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new ArkComponent(undefined, ModifierType.FRAME_NODE);
    }
    this._commonAttribute.setNodePtr(undefined);
    return this._commonAttribute;
  }
  createAnimation(property: AnimationPropertyType, startValue: number[] | undefined, endValue: number[], param: AnimateParam): boolean {
    JSXNodeLogConsole.warn("can't create animation on unmodifiable frameNode");
    return false;
  }
  cancelAnimations(properties: AnimationPropertyType[]): boolean {
    JSXNodeLogConsole.warn("can't cancel animation on unmodifiable frameNode");
    return false;
  }
}

class BuilderRootFrameNode extends ImmutableFrameNode {
  constructor(uiContext: UIContext, type: string = 'BuilderRootFrameNode') {
    super(uiContext, type);
  }
  getType(): string {
    return 'BuilderRootFrameNode';
  }
}

class ProxyFrameNode extends ImmutableFrameNode {
  _nativeRef: NativeWeakRef;

  constructor(uiContext: UIContext, type: string = 'ProxyFrameNode') {
    super(uiContext, type);
  }

  setNodePtr(nativeRef: NativeWeakRef) {
    this._nativeRef = nativeRef;
    this.nodePtr_ = this._nativeRef.getNativeHandle();
  }
  getType(): string {
    return 'ProxyFrameNode';
  }
  getRenderNode(): RenderNode | null {
    return null;
  }
  getNodePtr(): NodePtr | null {
    if (this._nativeRef === undefined || this._nativeRef === null || this._nativeRef.invalid()) {
      return null;
    }
    return this.nodePtr_;
  }
  dispose(): void {
    this.isDisposed_ = true;
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = undefined;
    this.nodePtr_ = undefined;
  }
  moveTo(targetParent: FrameNode, index?: number): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
}

class FrameNodeUtils {
  static searchNodeInRegisterProxy(nodePtr: NodePtr): FrameNode | null {
    let nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
    if (nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return null;
  }

  static createFrameNode(uiContext: UIContext, nodePtr: NodePtr): FrameNode | null {
    let nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
    if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
      let frameNode = new ProxyFrameNode(uiContext);
      let node = getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr);
      frameNode.setNodePtr(node);
      frameNode._nodeId = nodeId;
      FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(nodeId, new WeakRef(frameNode));
      FrameNodeFinalizationRegisterProxy.register(frameNode, nodeId);
      return frameNode;
    }
    return null;
  }
}

class TypedFrameNode<T extends ArkComponent> extends FrameNode {
  attribute_: T;
  attrCreator_: (node: NodePtr, type: ModifierType) => T

  constructor(uiContext: UIContext, type: string, attrCreator: (node: NodePtr, type: ModifierType) => T, options?: object) {
    super(uiContext, type, options);
    this.attrCreator_ = attrCreator;
  }

  dispose() {
    this.isDisposed_ = true;
    if (this.nodePtr_) {
      getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback(new WeakRef(this), 'FrameNode', this.getNodeType() || 'FrameNode', this.nodePtr_);
    }
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef?.dispose();
    this._nativeRef = null;
    this.nodePtr_ = null;
  }

  initialize(...args: Object[]): T {
    return this.attribute.initialize(args);
  }

  get attribute(): T {
    if (this.attribute_ === undefined) {
      this.attribute_ = this.attrCreator_(this.nodePtr_, ModifierType.FRAME_NODE);
    }
    this.attribute_.setNodePtr(this.nodePtr_);
    this.attribute_.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    return this.attribute_;
  }

  checkValid(node?: FrameNode): boolean {
    if (this.attribute_ === undefined) {
      this.attribute_ = this.attrCreator_(this.nodePtr_, ModifierType.FRAME_NODE);
    }

    if (this.attribute_.allowChildCount !== undefined) {
      const allowCount = this.attribute_.allowChildCount();
      if (this.getChildrenCount() >= allowCount) {
        return false;
      }
    }

    if (this.attribute_.allowChildTypes !== undefined && node !== undefined) {
      const childType = node.getNodeType();
      const allowTypes = this.attribute_.allowChildTypes();
      let isValid = false;
      allowTypes.forEach((nodeType: string) => {
        if (nodeType === childType) {
          isValid = true;
        }
      });
      return isValid;
    }
    return true;
  }
}

const __creatorMap__ = new Map<string, (context: UIContext, options?: object) => FrameNode>(
  [
    ['Text', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Text', (node: NodePtr, type: ModifierType): ArkTextComponent => {
        return new ArkTextComponent(node, type);
      })
    }],
    ['Column', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Column', (node: NodePtr, type: ModifierType): ArkColumnComponent => {
        return new ArkColumnComponent(node, type);
      })
    }],
    ['Row', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Row', (node: NodePtr, type: ModifierType): ArkRowComponent => {
        return new ArkRowComponent(node, type);
      })
    }],
    ['Stack', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Stack', (node: NodePtr, type: ModifierType): ArkStackComponent => {
        return new ArkStackComponent(node, type);
      })
    }],
    ['GridRow', (context: UIContext): FrameNode=> {
      let node = new TypedFrameNode(context, 'GridRow', (node: NodePtr, type: ModifierType): ArkGridRowComponent => {
        return new ArkGridRowComponent(node, type);
      });
      node.initialize();
      return node;
    }],
    ['TextInput', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'TextInput', (node: NodePtr, type: ModifierType): ArkTextInputComponent => {
        return new ArkTextInputComponent(node, type);
      })
    }],
    ['GridCol', (context: UIContext): FrameNode=> {
      let node = new TypedFrameNode(context, 'GridCol', (node: NodePtr, type: ModifierType): ArkGridColComponent => {
        return new ArkGridColComponent(node, type);
      });
      node.initialize();
      return node;
    }],
    ['Blank', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Blank', (node: NodePtr, type: ModifierType): ArkBlankComponent => {
        return new ArkBlankComponent(node, type);
      })
    }],
    ['Image', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Image', (node: NodePtr, type: ModifierType): ArkImageComponent => {
        return new ArkImageComponent(node, type);
      })
    }],
    ['Flex', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Flex', (node: NodePtr, type: ModifierType): ArkFlexComponent => {
        return new ArkFlexComponent(node, type);
      })
    }],
    ['Swiper', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Swiper', (node: NodePtr, type: ModifierType): ArkSwiperComponent => {
        return new ArkSwiperComponent(node, type);
      })
    }],
    ['Progress', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Progress', (node: NodePtr, type: ModifierType): ArkProgressComponent => {
        return new ArkProgressComponent(node, type);
      })
    }],
    ['Scroll', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Scroll', (node: NodePtr, type: ModifierType): ArkScrollComponent => {
        return new ArkScrollComponent(node, type);
      })
    }],
    ['RelativeContainer', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'RelativeContainer', (node: NodePtr, type: ModifierType): ArkRelativeContainerComponent => {
        return new ArkRelativeContainerComponent(node, type);
      })
    }],
    ['List', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'List', (node: NodePtr, type: ModifierType): ArkListComponent => {
        return new ArkListComponent(node, type);
      })
    }],
    ['ListItem', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'ListItem', (node: NodePtr, type: ModifierType): ArkListItemComponent => {
        return new ArkListItemComponent(node, type);
      })
    }],
    ['Divider', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Divider', (node: NodePtr, type: ModifierType): ArkDividerComponent => {
        return new ArkDividerComponent(node, type);
      })
    }],
    ['LoadingProgress', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'LoadingProgress', (node: NodePtr, type: ModifierType): ArkLoadingProgressComponent => {
        return new ArkLoadingProgressComponent(node, type);
      })
    }],
    ['Search', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Search', (node: NodePtr, type: ModifierType): ArkSearchComponent => {
        return new ArkSearchComponent(node, type);
      })
    }],
    ['Button', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Button', (node: NodePtr, type: ModifierType): ArkButtonComponent => {
        return new ArkButtonComponent(node, type);
      })
    }],
    ['XComponent', (context: UIContext, options?: object): FrameNode=> {
      return new TypedFrameNode(context, 'XComponent', (node: NodePtr, type: ModifierType): ArkXComponentComponent => {
        return new ArkXComponentComponent(node, type);
      }, options);
    }],
    ['ListItemGroup', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'ListItemGroup', (node: NodePtr, type: ModifierType): ArkListItemGroupComponent => {
        return new ArkListItemGroupComponent(node, type);
      })
    }],
    ['WaterFlow', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'WaterFlow', (node: NodePtr, type: ModifierType): ArkWaterFlowComponent => {
        return new ArkWaterFlowComponent(node, type);
      })
    }],
    ['SymbolGlyph', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'SymbolGlyph', (node: NodePtr, type: ModifierType): ArkSymbolGlyphComponent => {
        return new ArkSymbolGlyphComponent(node, type);
      })
    }],
    ['FlowItem', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'FlowItem', (node: NodePtr, type: ModifierType): ArkFlowItemComponent => {
        return new ArkFlowItemComponent(node, type);
      })
    }],
    ['QRCode', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'QRCode', (node: NodePtr, type: ModifierType): ArkQRCodeComponent => {
        return new ArkQRCodeComponent(node, type);
      })
    }],
    ['Badge', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Badge', (node: NodePtr, type: ModifierType): ArkBadgeComponent => {
        return new ArkBadgeComponent(node, type);
      })
    }],
    ['Grid', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Grid', (node: NodePtr, type: ModifierType): ArkGridComponent => {
        return new ArkGridComponent(node, type);
      })
    }],
    ['GridItem', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'GridItem', (node: NodePtr, type: ModifierType): ArkGridItemComponent => {
        return new ArkGridItemComponent(node, type);
      })
    }],
    ['TextClock', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'TextClock', (node: NodePtr, type: ModifierType): ArkTextClockComponent => {
        return new ArkTextClockComponent(node, type);
      })
    }],
    ['TextTimer', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'TextTimer', (node: NodePtr, type: ModifierType): ArkTextTimerComponent => {
        return new ArkTextTimerComponent(node, type);
      })
    }],
    ['Marquee', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Marquee', (node: NodePtr, type: ModifierType): ArkMarqueeComponent => {
        return new ArkMarqueeComponent(node, type);
      })
    }],
    ['TextArea', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'TextArea', (node: NodePtr, type: ModifierType): ArkTextAreaComponent => {
        return new ArkTextAreaComponent(node, type);
      })
    }],
    ['Checkbox', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Checkbox', (node: NodePtr, type: ModifierType): ArkCheckboxComponent => {
        return new ArkCheckboxComponent(node, type);
      });
    }],
    ['CheckboxGroup', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'CheckboxGroup', (node: NodePtr, type: ModifierType): ArkCheckboxGroupComponent => {
        return new ArkCheckboxGroupComponent(node, type);
      });
    }],
    ['Radio', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Radio', (node: NodePtr, type: ModifierType): ArkRadioComponent => {
        return new ArkRadioComponent(node, type);
      });
    }],
    ['Rating', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Rating', (node: NodePtr, type: ModifierType): ArkRatingComponent => {
        return new ArkRatingComponent(node, type);
      });
    }],
    ['Slider', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Slider', (node: NodePtr, type: ModifierType): ArkSliderComponent => {
        return new ArkSliderComponent(node, type);
      });
    }],
    ['Select', (context: UIContext): FrameNode=> {
      return new TypedFrameNode(context, 'Select', (node: NodePtr, type: ModifierType): ArkSelectComponent => {
        return new ArkSelectComponent(node, type);
      });
    }],
    ['Toggle', (context: UIContext, options?: object): FrameNode=> {
      return new TypedFrameNode(context, 'Toggle', (node: NodePtr, type: ModifierType): ArkToggleComponent => {
        return new ArkToggleComponent(node, type);
      }, options);
    }],
  ]
)

const __attributeMap__ = new Map<string, (node: FrameNode) => ArkComponent>(
  [
    ['Swiper', (node: FrameNode): ArkSwiperComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkSwiperComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Scroll', (node: FrameNode): ArkScrollComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkScrollComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['List', (node: FrameNode): ArkListComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkListComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['ListItem', (node: FrameNode): ArkListItemComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkListItemComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['ListItemGroup', (node: FrameNode): ArkListItemGroupComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkListItemGroupComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['WaterFlow', (node: FrameNode): ArkWaterFlowComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkWaterFlowComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['FlowItem', (node: FrameNode): ArkFlowItemComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkFlowItemComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Grid', (node: FrameNode): ArkGridComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkGridComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['GridItem', (node: FrameNode): ArkGridItemComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkGridItemComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Text', (node: FrameNode): ArkTextComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkTextComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['TextInput', (node: FrameNode): ArkTextInputComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkTextInputComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['TextArea', (node: FrameNode): ArkTextAreaComponent => {
        if (node._componentAttribute) {
          return node._componentAttribute;
        }
        if (!node.getNodePtr()) {
          return undefined;
        }
        node._componentAttribute = new ArkTextAreaComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
        return node._componentAttribute;
    }],
    ['Button', (node: FrameNode): ArkButtonComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkButtonComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Checkbox', (node: FrameNode): ArkCheckboxComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkCheckboxComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Radio', (node: FrameNode): ArkRadioComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkRadioComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Slider', (node: FrameNode): ArkSliderComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkSliderComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Toggle', (node: FrameNode): ArkToggleComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkToggleComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Column', (node: FrameNode): ArkColumnComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkColumnComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Row', (node: FrameNode): ArkRowComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkRowComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Stack', (node: FrameNode): ArkStackComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkStackComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Flex', (node: FrameNode): ArkFlexComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkFlexComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['RelativeContainer', (node: FrameNode): ArkRelativeContainerComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkRelativeContainerComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['XComponent', (node: FrameNode): ArkXComponentComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
        return undefined;
      }
      node._componentAttribute = new ArkXComponentComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Progress', (node: FrameNode): ArkProgressComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkProgressComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['LoadingProgress', (node: FrameNode): ArkLoadingProgressComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkLoadingProgressComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }],
    ['Image', (node: FrameNode): ArkImageComponent => {
      if (node._componentAttribute) {
        return node._componentAttribute;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._componentAttribute = new ArkImageComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
      return node._componentAttribute;
    }]
  ]
)

const __eventMap__ = new Map<string, (node: FrameNode) => UICommonEvent>(
  [
    ['List', (node: FrameNode): UIListEvent => {
      if (node._scrollableEvent) {
        return node._scrollableEvent;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._scrollableEvent = new UIListEvent(node.getNodePtr());
      node._scrollableEvent.setNodePtr(node);
      node._scrollableEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
      return node._scrollableEvent;
    }],
    ['Scroll', (node: FrameNode): UIScrollEvent => {
      if (node._scrollableEvent) {
        return node._scrollableEvent;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._scrollableEvent = new UIScrollEvent(node.getNodePtr());
      node._scrollableEvent.setNodePtr(node);
      node._scrollableEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
      return node._scrollableEvent;
    }],
    ['Grid', (node: FrameNode): UIGridEvent => {
      if (node._scrollableEvent) {
        return node._scrollableEvent;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._scrollableEvent = new UIGridEvent(node.getNodePtr());
      node._scrollableEvent.setNodePtr(node);
      node._scrollableEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
      return node._scrollableEvent;
    }],
    ['WaterFlow', (node: FrameNode): UIWaterFlowEvent => {
      if (node._scrollableEvent) {
        return node._scrollableEvent;
      }
      if (!node.getNodePtr()) {
         return undefined;
      }
      node._scrollableEvent = new UIWaterFlowEvent(node.getNodePtr());
      node._scrollableEvent.setNodePtr(node);
      node._scrollableEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
      return node._scrollableEvent;
    }]
  ]
)

type Controller = Scroller | SwiperController | TextController | TextInputController | TextAreaController

const __bindControllerCallbackMap__ = new Map<string, (node: FrameNode, controller: Controller) => void>(
  [
    ['Swiper', (node: FrameNode, controller: SwiperController) => {
      getUINativeModule().swiper.setSwiperInitialize(node.getNodePtr(), controller);
    }],
    ['Scroll', (node: FrameNode, controller: Scroller) => {
      getUINativeModule().scroll.setScrollInitialize(node.getNodePtr(), controller);
    }],
    ['List', (node: FrameNode, controller: Scroller) => {
      getUINativeModule().list.setInitialScroller(node.getNodePtr(), controller);
    }],
    ['WaterFlow', (node: FrameNode, controller: Scroller) => {
      getUINativeModule().waterFlow.setWaterFlowScroller(node.getNodePtr(), controller);
    }],
    ['Grid', (node: FrameNode, controller: Scroller) => {
      getUINativeModule().grid.setGridScroller(node.getNodePtr(), controller);
    }],
    ['Text', (node: FrameNode, controller: TextController) => {
        getUINativeModule().text.setTextController(node.getNodePtr(), { controller: controller });
    }],
    ['TextInput', (node: FrameNode, controller: TextInputController) => {
        getUINativeModule().textInput.setController(node.getNodePtr(), controller);
    }],
    ['TextArea', (node: FrameNode, controller: TextAreaController) => {
        getUINativeModule().textArea.setController(node.getNodePtr(), controller);
    }]
  ]
)

class typeNode {
  static createNode(context: UIContext, type: string, options?: object): FrameNode {
    let creator = __creatorMap__.get(type)
    if (creator === undefined) {
      return undefined
    }
    return creator(context, options);
  }
  
  static getAttribute(node: FrameNode, nodeType: string): ArkComponent {
    if (node === undefined || node === null || node.getNodeType() !== nodeType) {
      return undefined;
    }
    if (!node.checkIfCanCrossLanguageAttributeSetting()) {
      return undefined;
    }
    let attribute = __attributeMap__.get(nodeType);
    if (attribute === undefined || attribute === null) {
      return undefined;
    }
    return attribute(node);
  }

  static getEvent(node: FrameNode, nodeType: string): UICommonEvent {
    if (node === undefined || node === null || node.getNodeType() !== nodeType) {
      return undefined;
    }
    let event = __eventMap__.get(nodeType);
    if (event === undefined || event === null) {
      return undefined;
    }
    return event(node);
  } 

  static bindController(node: FrameNode, controller: Controller, nodeType: string): void {
    if (node === undefined || node === null || controller === undefined || controller === null ||
      node.getNodeType() !== nodeType || node.getNodePtr() === null || node.getNodePtr() === undefined) {
      if (nodeType === undefined || nodeType === null || nodeType === 'Scroll') {
        throw { message: 'Parameter error. Possible causes: 1. The type of the node is error; 2. The node is null or undefined.', code: 401 };
      } else {
        throw { message: 'Parameter error. Possible causes: 1. The component type of the node is incorrect. 2. The node is null or undefined. 3. The controller is null or undefined.', code: 100023 };
      }
    }
    if (!node.checkIfCanCrossLanguageAttributeSetting()) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    let callback = __bindControllerCallbackMap__.get(nodeType);
    if (callback === undefined || callback === null) {
      return;
    }
    callback(node, controller);
  }
}
