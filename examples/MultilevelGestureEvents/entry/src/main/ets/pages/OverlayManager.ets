/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { ComponentContent, OverlayManager, UIContext } from '@kit.ArkUI';
interface Position {
  x: number;
  y: number;
}
class Params {
  private  context: UIContext;
  private  position: Position;
  constructor(context: UIContext, position: Position) {
    this.context = context;
    this.position = position;
  }
}
let uiContext: UIContext;

// [Start overlay_manager]
@Builder
function builderOverlay(params: Params) {
  Component1().hitTestBehavior(HitTestMode.Transparent)
}

// [StartExclude overlay_manager]
@Entry
@Component
struct CustomEvent {
  private overlayManager?: OverlayManager;
  @State context: UIContext = this.getUIContext();
  // [EndExclude overlay_manager]

  aboutToAppear(): void {
    // [StartExclude overlay_manager]
    this.overlayManager = this.context.getOverlayManager();
    // [EndExclude overlay_manager]
    let componentContent = new ComponentContent(
      this.context, wrapBuilder<[Params]>(builderOverlay),
      new Params(uiContext, {x:0, y: 100})
    );
    this.overlayManager.addComponentContent(componentContent, 0);
  }
  // [End overlay_manager]
  build() {}
}
@Component
struct Component1 {
  build() {}
}