/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

interface LayoutConstraint {
  maxSize: Size;
  minSize: Size;
  percentReference: Size;
}

class FrameNode {
  public _nodeId: number;
  protected _commonAttribute: ArkComponent;
  protected _commonEvent: UICommonEvent;
  protected _gestureEvent: UIGestureEvent;
  protected _childList: Map<number, FrameNode>;
  protected _nativeRef: NativeStrongRef | NativeWeakRef;
  protected renderNode_: RenderNode;
  protected baseNode_: BaseNode;
  protected uiContext_: UIContext | undefined | null;
  protected nodePtr_: NodePtr;
  protected instanceId_?: number;
  private nodeAdapterRef_?: NodeAdapter;
  constructor(uiContext: UIContext, type: string, options?: object) {
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
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = null;
    this.nodePtr_ = null;
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
    getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.delete(node._nodeId);
  }

  clearChildren(): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.clearChildren(this.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.clear();
  }
  getChild(index: number, isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getChild(this.getNodePtr(), index, isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getFirstChild(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getFirstChildWithoutExpand(): FrameNode | null {
    const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), false);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getNextSibling(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getNextSiblingWithoutExpand(): FrameNode | null {
    const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), false);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getPreviousSibling(isExpanded?: boolean): FrameNode | null {
    const result = getUINativeModule().frameNode.getPreviousSibling(this.getNodePtr(), isExpanded);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
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
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getChildrenCount(isExpanded?: boolean): number {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    return getUINativeModule().frameNode.getChildrenCount(this.nodePtr_, isExpanded);
    __JSScopeUtil__.restoreInstanceId();
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

  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new ArkComponent(this.nodePtr_, ModifierType.FRAME_NODE);
      this._commonAttribute.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    }
    this._commonAttribute.setNodePtr(this.nodePtr_);
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
    }
    return this._gestureEvent;
  }
  updateInstance(uiContext: UIContext): void {
    this.uiContext_ = uiContext;
    this.instanceId_ = uiContext.instanceId_;
  }
  triggerOnReuse(): void {
    getUINativeModule().frameNode.triggerOnReuse(this.getNodePtr());
  }
  triggerOnRecycle(): void {
    getUINativeModule().frameNode.triggerOnRecycle(this.getNodePtr());
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
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = undefined;
    this.nodePtr_ = undefined;
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

class typeNode {
  static createNode(context: UIContext, type: string, options?: object): FrameNode {
    let creator = __creatorMap__.get(type)
    if (creator === undefined) {
      return undefined
    }
    return creator(context, options);
  }
}
