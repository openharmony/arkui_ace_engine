/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class BuilderNodeFinalizationRegisterProxy {
  constructor() {
    this.finalizationRegistry_ = new FinalizationRegistry((heldValue: RegisterParams) => {
      if (heldValue.name === 'BuilderRootFrameNode') {
        const builderNode = BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.get(heldValue.idOfNode);
        BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.delete(heldValue.idOfNode);
        builderNode.dispose();
      }
    });
  }
  public static register(target: BuilderNode, heldValue: RegisterParams) {
    BuilderNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue);
  }

  public static instance_: BuilderNodeFinalizationRegisterProxy = new BuilderNodeFinalizationRegisterProxy();
  public static ElementIdToOwningBuilderNode_ = new Map<Symbol, JSBuilderNode>();
  private finalizationRegistry_: FinalizationRegistry;
}

class FrameNodeFinalizationRegisterProxy {
  constructor() {
    this.finalizationRegistry_ = new FinalizationRegistry((heldValue: number) => {
      FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(heldValue);
    });
  }
  public static register(target: FrameNode, heldValue: number) {
    FrameNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue);
  }

  public static instance_: FrameNodeFinalizationRegisterProxy = new FrameNodeFinalizationRegisterProxy();
  public static ElementIdToOwningFrameNode_ = new Map<number, WeakRef<FrameNode>>();
  public static FrameNodeInMainTree_ = new Map<number, FrameNode>();
  private finalizationRegistry_: FinalizationRegistry;
}

class NodeControllerRegisterProxy {
  public static instance_: NodeControllerRegisterProxy = new NodeControllerRegisterProxy();
  public static __NodeControllerMap__ = new Map<number, NodeController>();
}

globalThis.__AddToNodeControllerMap__ = function __AddToNodeControllerMap__(containerId: number,nodeController:NodeController ) {
  NodeControllerRegisterProxy.__NodeControllerMap__.set(containerId, nodeController);
}

globalThis.__RemoveFromNodeControllerMap__ = function __RemoveFromNodeControllerMap__(containerId: number) {
  let nodeController: NodeController = NodeControllerRegisterProxy.__NodeControllerMap__.get(containerId);
  nodeController._nodeContainerId.__rootNodeOfNodeController__ = undefined;
  NodeControllerRegisterProxy.__NodeControllerMap__.delete(containerId);
}

globalThis.__viewPuStack__ = new Array<ViewPU>();

globalThis.__CheckIsInBuilderNode__ = function __CheckIsInBuilderNode__(parent: ViewPU): boolean {
  if (globalThis.__viewPuStack__ === undefined || globalThis.__viewPuStack__.length === 0) {
    return false;
  }
  const _BuilderNodeView = globalThis.__viewPuStack__?.pop();
  if (_BuilderNodeView) {
    globalThis.__viewPuStack__?.push(_BuilderNodeView);
  }
  return (_BuilderNodeView !== undefined && _BuilderNodeView === parent) ? true : false;
}
