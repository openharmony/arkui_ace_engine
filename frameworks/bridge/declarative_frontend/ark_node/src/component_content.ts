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
/// <reference path="../../state_mgmt/src/lib/common/ifelse_native.d.ts" />
/// <reference path="../../state_mgmt/src/lib/partial_update/pu_viewstack_processor.d.ts" />

class ComponentContent {
  private builderNode_: BuilderNode;
  constructor(uiContext: UIContext, builder: WrappedBuilder<[]> | WrappedBuilder<[Object]>, params?: Object) {
    let builderNode = new BuilderNode(uiContext, {});
    this.builderNode_ = builderNode;
    this.builderNode_.build(builder, params ?? {});
  }

  public update(params: Object) {
    this.builderNode_.update(params);
  }

  public getFrameNode(): FrameNode {
    return this.builderNode_.getFrameNode();
  }
}