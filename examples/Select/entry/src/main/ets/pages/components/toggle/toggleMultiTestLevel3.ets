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

import { MyComponent } from '../base/MyComponent';
import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ToggleMultiTestLevel3Builder(name: string, param: Object) {
  toggleMultiTestLevel3()
}

@Entry
@Component
struct toggleMultiTestLevel3 {
  pathStack: NavPathStack = new NavPathStack()
  private scrollerForList: Scroller = new Scroller()
  @State index: number = 0
  @State sets: Array<ToggleType | undefined> =
    [ToggleType.Button, ToggleType.Checkbox, ToggleType.Switch, ToggleType.Button, undefined]
  @State hover: HoverEffect | undefined = undefined

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('type: Button验证与其他组件的兄弟节点关系').fontSize(12).fontColor(0xcccccc).width('90%')
          Row({ space: 2 }) {
            Text('${this.index + 1}' + '/')
              .fontSize(15)
              .fontColor(0xCCCCCC)
            Text('${this.sets.length}')
              .key('ToggleLevel1_3')
              .fontSize(15)
              .fontColor(0xCCCCCC)

            MyComponent({
              title: 'Test++', func: () => {
                this.index++
                if (this.index == this.sets.length) {
                  this.index = 0
                }
              }
            })

            MyComponent({
              title: 'Test--', func: () => {
                this.index--
                if (this.index <= -1) {
                  this.index = this.sets.length - 1
                }
              }
            })
          }

          Text('HoverEffect验证').fontSize(9).fontColor(0xCCCCCC).width('100%').width('90%')
          Row({ space: 5 }) {
            MyComponent({
              title: 'None', func: () => {
                this.hover = HoverEffect.None
              }
            })
            MyComponent({
              title: 'Scale', func: () => {
                this.hover = HoverEffect.Scale
              }
            })
            MyComponent({
              title: 'Auto', func: () => {
                this.hover = HoverEffect.Auto
              }
            })
          }
          Divider()
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Toggle({ type: this.sets[this.index], isOn: false }) {
              Text('status button').fontSize(12)
            }.width(106)
            .selectedColor('rgba(0,125,255,0.20)')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
            .hoverEffect(this.hover)
            .responseRegion({ x: 0, y: 0, width: '60%', height: '100%' })
            .key('Toggle0001')

            Text('ToggleType.Button时验证 Text组件').fontSize(14).lineHeight(20).fontWeight(500)


          }.margin({ bottom: 30 })

          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Toggle({ type: this.sets[this.index], isOn: true }) {
              Text('status button').fontSize(12)
            }.width(106)
            .selectedColor('rgba(0,125,255,0.20)')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
            .border({width: 2, color: Color.Red, radius: 3})
            .key('Toggle0002')

            Image($r('app.media.app_icon')).width(20).height(20)
          }.margin({ bottom: 30 })

          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Toggle({ type: this.sets[this.index], isOn: false }) {
              Text('status button').fontSize(12)
            }.width(106)
            .selectedColor('rgba(0,125,255,0.20)')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
            .borderRadius(3)
            .borderWidth(1)
            .key('Toggle0003')

            List({ space: 20, initialIndex: 3, scroller: this.scrollerForList })
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
              .width('30%')
              .height('5%')
              .backgroundColor(Color.Red)

          }.margin({ bottom: 30 })

          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Toggle({ type: this.sets[this.index], isOn: true }) {
              Text('status button').fontSize(12)
            }.width(106)
            .selectedColor('rgba(0,125,255,0.20)')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
            .key('Toggle0004')

            Grid()
              .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
              .rowsTemplate('1fr 1fr 1fr 1fr 1fr')
              .columnsGap(10)
              .rowsGap(10)
              .width('40%')
              .backgroundColor(0xFAEEE0)
              .height(20)
          }
        }.width('100%')
      }
    }
    .title('ToggleMultiTestLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}