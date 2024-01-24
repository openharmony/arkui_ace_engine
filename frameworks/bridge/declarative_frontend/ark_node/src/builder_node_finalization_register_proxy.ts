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
      if (heldValue.name === "BuilderNode") {
        const builderNode = BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.get(heldValue.idOfNode);
        BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.delete(heldValue.idOfNode);
        builderNode.dispose();
      }
    });
  }
  public static register(target: BuilderNode, heldValue: RegisterParams) {
    BuilderNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue)
  }

  public static instance_: BuilderNodeFinalizationRegisterProxy = new BuilderNodeFinalizationRegisterProxy();
  public static ElementIdToOwningBuilderNode_ = new Map<Symbol, BaseNode>();
  private finalizationRegistry_: FinalizationRegistry;
}