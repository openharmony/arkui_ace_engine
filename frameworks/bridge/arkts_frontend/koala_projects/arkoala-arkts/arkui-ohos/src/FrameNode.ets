import { UIContext } from "@ohos/arkui/UIContext";
import {
  SerializerBase,
  DeserializerBase,
  Finalizable,
  runtimeType,
  RuntimeType,
  registerCallback,
  wrapCallback,
  toPeerPtr,
  KPointer,
  MaterializedBase,
  NativeBuffer,
  KInt,
  KBoolean,
  KStringPtr,
  CallbackResource,
  InteropNativeModule,
  Tags,
  nullptr,
  KSerializerBuffer,
  KUint8ArrayPtr,
} from "@koalaui/interop";
import { JSBuilderNode } from "./BuilderNode";
import { UIContextImpl } from "arkui/base/UIContextImpl";
import { RenderNode } from "./RenderNode";
import { CommonAttribute, UIGestureEvent } from "./component/common";
import { Size } from "arkui.Graphics";
import { ComponentContent } from './ComponentContent';

export class FrameNode implements MaterializedBase {
  peer?: Finalizable | undefined = undefined;
  uiContext: UIContextImpl | undefined = undefined;
  renderNode_: RenderNode | undefined = undefined;
  instanceId_?: number;
  // the name of "nodePtr_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
  nodePtr_: KPointer | undefined;
  public _nodeId: number = -1;
  protected _commonAttribute: CommonAttribute | undefined = undefined;
  protected _gestureEvent: UIGestureEvent | undefined = undefined;
  public nodeType_?: string | undefined = undefined;

  getType(): string {
    return "CustomFrameNode";
  }

  checkValid(node: FrameNode): boolean {
    return true;
  }
  public getPeer(): Finalizable | undefined {
    return this.peer;
  }
  public removeComponentContent<T = undefined>(content: ComponentContent<T>) {
  }
}

class ImmutableFrameNode extends FrameNode {}

export class BuilderRootFrameNode<T> extends ImmutableFrameNode {
  private __BuilderNodeOpt: JSBuilderNode<T> | undefined = undefined;
  getType(): string {
    return "BuilderRootFrameNode";
  }
  setJsBuilderNode(weak?: JSBuilderNode<T>) {
    this.__BuilderNodeOpt = weak;
  }
  public disposeNode(): void {}
  public dispose(): void {}
}

export class FrameNodeUtils {
  static searchNodeInRegisterProxy(ptr: KPointer): FrameNode | null {
    return null;
  }
  static createFrameNode(
    uiContext: UIContext,
    ptr: KPointer
  ): FrameNode | null {
    return null;
  }
  static createBuilderRootFrameNode<T = undefined>(
    uiContext: UIContext,
    ptr: KPointer
  ): BuilderRootFrameNode<T> | null {
    return null;
  }
}
export enum ExpandMode {
  NOT_EXPAND = 0,
  EXPAND = 1,
  LAZY_EXPAND = 2
}
export interface LayoutConstraint {
  maxSize: Size;
  minSize: Size;
  percentReference: Size;
}
export interface CrossLanguageOptions {
    attributeSetting?: boolean
}
export class NodeAdapter {
}
export namespace typeNode {
}