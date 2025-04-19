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

import { ComponentContent, LevelOrder, OverlayManager } from '@kit.ArkUI'
import { ParamOption, SetParam } from '../base/ParamOption'

class Params {
  public text: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  constructor(text: string, overlayManager: OverlayManager, overlayIdx: number) {
    this.text = text
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
  }
}

let overlayArray: ComponentContent<Params>[] = []
let overlayIndex: number = 0

@Builder
function buildText(params: Params) {
  Column({ space: 5 }) {
    Text(params.text)
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    Button('点我关闭弹窗')
      .onClick(() => {
        let componentContent = overlayArray[params.overlayIdx]
        params.overlayManager.removeComponentContent(componentContent)
        overlayArray[params.overlayIdx] = null!
      })
  }
  .width(300)
  .height(200)
  .backgroundColor('#FFF0F0F0')
}

@Builder
export function OverlayLevelOrderBuilder(name: string, param: Object) {
  OverlayLevelOrder()
}

@Component
export struct OverlayLevelOrder {
  private message = '弹窗'
  private ctx: UIContext = this.getUIContext()
  private overlayManager: OverlayManager = this.ctx.getOverlayManager()

  @State levelOrder: LevelOrder = LevelOrder.clamp(undefined)
  private setLevelOrder: SetParam[] = [{
    title: '-100000',
    func: () => {
      this.levelOrder = LevelOrder.clamp(-100000)
    }
  }, {
    title: '-5',
    func: () => {
      this.levelOrder = LevelOrder.clamp(-5)
    }
  }, {
    title: 'undefined',
    func: () => {
      this.levelOrder = LevelOrder.clamp(undefined)
    }
  }, {
    title: '1.41',
    func: () => {
      this.levelOrder = LevelOrder.clamp(1.41)
    }
  }, {
    title: '100000',
    func: () => {
      this.levelOrder = LevelOrder.clamp(100000)
    }
  }]

  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('LevelOrder: ' + this.levelOrder.getOrder())
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setLevelOrder, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Button('弹出弹窗')
          .onClick(() => {
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[Params]>(buildText),
              new Params(this.message + ', 层级: ' + this.levelOrder.getOrder(), this.overlayManager, overlayIndex))
            overlayArray[overlayIndex] = componentContent
            overlayIndex++
            this.overlayManager.addComponentContentWithOrder(componentContent, this.levelOrder)
          })
      }
    }
    .title('OverlayLevelOrder')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}