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

import { ComponentContent, OverlayManager } from '@kit.ArkUI'

class Params {
  public context: UIContext
  public offset: Position
  public message: string
  constructor(context: UIContext, offset: Position, message: string) {
    this.context = context
    this.offset = offset
    this.message = message
  }
}
@Builder
function builderOverlay(params: Params) {
  Column() {
    Stack(){
    }.width(50).height(50).backgroundColor(Color.Yellow).position(params.offset).borderRadius(50)
    .onClick(() => {})
  }.focusable(false).width('100%').height('100%').hitTestBehavior(HitTestMode.Transparent)
}

@Builder
export function OverlayManagerHitBuilder(name: string, param: Object) {
  OverlayManageraHitTest()
}

@Component
export struct OverlayManageraHitTest {
  @State message: string = 'ComponentContent';
  private uiContext: UIContext = this.getUIContext()
  private overlayNode: OverlayManager = this.uiContext.getOverlayManager()
  private overlayContent:ComponentContent<Params>[] = []
  controller: TextInputController = new TextInputController()
  @State btnColor: Color = Color.Red;
  private  changeColor: boolean = false;


  aboutToDisappear(): void {
    if (this.overlayContent.length) {
      let componentContent = this.overlayContent.pop()
      this.overlayNode.removeComponentContent(componentContent)
    }
  }

  build() {
    NavDestination() {
      Column() {
        Button('show overlay').onClick(() => {
          let uiContext = this.getUIContext();
          let componentContent = new ComponentContent(
            this.uiContext, wrapBuilder<[Params]>(builderOverlay),
            new Params(uiContext, { x: 180, y: 100 }, 'component1')
          )
          this.overlayNode.addComponentContent(componentContent, 0)
          this.overlayContent.push(componentContent)
        })
        Button('click change').onClick(() => {
          this.btnColor = this.changeColor ? Color.Red : Color.Blue;
          this.changeColor = !this.changeColor;
        }).backgroundColor(this.btnColor)
      }
      .width('100%')
      .height('100%')
    }
  }
}