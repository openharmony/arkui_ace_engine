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

class ComponentContent extends Content {
  // the name of "builderNode_" is used in ace_engine/interfaces/native/node/native_node_napi.cpp.
  private builderNode_: BuilderNode;
  constructor(uiContext: UIContext, builder: WrappedBuilder<[]> | WrappedBuilder<[Object]>, params?: Object) {
    super();
    let builderNode = new BuilderNode(uiContext, {});
    this.builderNode_ = builderNode;
    this.builderNode_.build(builder, params ?? undefined, false);
  }

  public update(params: Object) {
    this.builderNode_.update(params);
  }

  public getFrameNode(): FrameNode {
    return this.builderNode_.getFrameNode();
  }
  public getNodePtr(): NodePtr {
    return this.builderNode_.getNodePtr();
  }
}