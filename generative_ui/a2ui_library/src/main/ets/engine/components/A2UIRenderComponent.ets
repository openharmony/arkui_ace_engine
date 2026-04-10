/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { SurfaceController } from './../core/SurfaceController'
import { FunctionBridge } from './../functions/FunctionBridge'
import { NodeContent } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';

@Component
export struct A2UIRenderComponent {
  surfaceControllerBound: SurfaceController | null = null;
  private rootSlot: NodeContent = new NodeContent();

  aboutToAppear() {
    FunctionBridge.setHostContext(this.getUIContext().getHostContext() as common.UIAbilityContext)
    this.surfaceControllerBound?.bindToRender(this.rootSlot);
  }

  build() {
      Column() {
        ContentSlot(this.rootSlot)
      }
      .width('100%')
      .height('100%')
    }

}
