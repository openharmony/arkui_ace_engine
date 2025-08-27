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
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ToggleMultiTestLevel1Builder(name: string, param: Object) {
  toggleMultiTestLevel1()
}

interface obj {
  title?: string | undefined,
  type?: ToggleType | undefined
}

interface obj1 {
  title?: string | undefined,
  visit?: Visibility | undefined
}

interface obj2 {
  title?: string | undefined,
  direction?: Direction | undefined
}

@Entry
@Component
struct toggleMultiTestLevel1 {
  pathStack: NavPathStack = new NavPathStack()
  @State visible: Visibility | undefined = undefined
  @State type: ToggleType | undefined = ToggleType.Checkbox
  @State clip1: boolean = false
  @State offsetX: number | undefined = undefined
  @State width1: number = 50
  @State num: number = 0
  private caseTypes: Array<obj> = [
    { title: 'Checkbox', type: ToggleType.Checkbox },
    { title: 'Button', type: ToggleType.Button },
    { title: 'Switch', type: ToggleType.Switch },
    { title: 'undefined', type: undefined }
  ]
  private caseVisits: Array<obj1> = [
    { title: 'Hidden', visit: Visibility.Hidden },
    { title: 'None', visit: Visibility.None },
    { title: 'Visible', visit: Visibility.Visible }
  ]
  @State dir: Array<Direction | undefined> = [undefined, Direction.Ltr, Direction.Rtl, Direction.Auto]

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('Toggle 通用属性组合测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 5 }) {
            //测试点：默认宽高、padding、backgroundColor、direction属性
            Toggle({ type: this.type })//不设置宽高
              .borderWidth(1)
              .padding({ top: 10, right: 10 })
              .backgroundColor(Color.Pink)
              .direction(this.dir[this.num])
            //测试点：单边宽高、margin、foregroundColor、direction属性
            Column() { //设置单边宽高
              Toggle({ type: this.type })
                .borderWidth(1)
                .width(50)
                .margin({ bottom: '10%', left: '10' })
                .foregroundColor(Color.Pink)//设置前景色
                .direction(this.dir[this.num])
            }.borderWidth(1)

            //测试点：size、clip属性、孩子节点超出父容器
            Row() {
              Toggle({ type: this.type })//看默认margin是否正确
                .size({ width: 70, height: 70 })
                .borderWidth(1)
                .direction(this.dir[this.num])
                .key('Toggle01_Toggle0')
            }.width(50).borderWidth(1).clip(this.clip1)

            //测试点：组件在根容器范围外绘制，范围外点击响应（clik事件和选中态）
            Toggle({ type: this.type })//宽度大于根容器
              .width(120)
              .height(100)
              .offset({ x: 50 })
              .direction(this.dir[this.num])
              .key('Toggle01_Toggle1')
              .onClick(() => {
                console.log('lhl:---toggle is onclick')
              })
              .borderWidth(1)
          }

          Row({ space: 5 }) {
            //测试点：aspectRatio属性
            Column({ space: 2 }) {
              Toggle({ type: this.type })
                .height(30)
                .aspectRatio(2)
                .align(Alignment.BottomStart)
                .borderWidth(1)
                .direction(this.dir[this.num])
              // 测试点：Toggle组件与通用属性结合考虑异常值
              Toggle({ type: this.type })//看默认margin是否正确
                .width(-1)
                .height(-1)
                .borderWidth(-1)
                .borderColor('fhujsfkjfjwsfjwj')
                .borderStyle(undefined)
                .borderRadius(-10)
                .size({ width: -100, height: undefined })
                .padding(-1)
                .margin(-1)
                .border(undefined)
                .borderImage(undefined)
                .direction(this.dir[this.num])
            }

            //测试点：layoutWeight属性测试
            Toggle({ type: this.type })
              .borderWidth(1)
              .layoutWeight(2)
              .aspectRatio(0.8)
              .enabled(false)
              .key('Toggle01_Toggle2')
              .direction(this.dir[this.num])
            //测试点：align属性测试
            Stack() {
              Toggle({ type: this.type })
                .borderWidth(1)
                .width(30)
                .direction(this.dir[this.num])
                .responseRegion({
                  x: '-300%',
                  y: 0,
                  width: '300%',
                  height: '100%'
                })//0522: 增加热区设置
                .key('Toggle01_Toggle3')
            }
            .layoutWeight(3)
            .height(50)
            .margin({ top: 5 })
            .backgroundColor(0xFFE4C4)
            .align(Alignment.TopEnd)
          }.borderWidth(1).width('100%')

          //测试点：1、动态切换type属性 2、看上面的通用属性表现情况
          Text('切换类型：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseTypes, (item: obj) => {
              MyComponent({
                title: item.title, func: () => {
                  this.type = item.type
                }
              })
            }, (item: obj) => item.title)
          }

          Text('direction设置与是否裁剪：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            MyComponent({
              title: 'direction', func: () => {
                this.num++
                if (this.num >= this.dir.length) {
                  this.num = 0
                }
              }
            })
            MyComponent({
              title: 'clip', func: () => {
                this.clip1 = !this.clip1
              }
            })
          }

          Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })
          //测试点：自适应父亲，不显示设置父容器宽高，孩子组件设置百分比宽高(此处测一种type即可，不需要测试所有type组合)
          Text('自适应布局：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Flex({ direction: FlexDirection.Row }) {
            Toggle({ type: this.type }).width('20%').borderWidth(1).direction(this.dir[this.num])
            Toggle({ type: this.type }).width('30%').borderWidth(1).direction(this.dir[this.num])
            Toggle({ type: this.type })
              .direction(this.dir[this.num])
              .width('40%')
              .borderWidth(1)
              .visibility(this.visible)
              .key('Toggle01_Toggle4')
              .onChange((isChecked: boolean) => { //测试点：visibility为hidden和None时点击不响应
                console.log('lhl:---toggle status is ' + isChecked)
              })
          }.borderWidth(1)

          //测试点：通用属性visibility组合，设为None时布局自适应
          Text('控制组件显隐：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseVisits, (item: obj1) => {
              MyComponent({
                title: item.title, func: () => {
                  this.visible = item.visit
                }
              })
            }, (item: obj1) => item.title)
          }

          Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })
          //toggle位置和大小改变，热区变化情况
          Text('toggle位置和大小改变，热区变化情况：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Toggle({ type: this.type })
            .direction(this.dir[this.num])
            .width(this.width1)
            .offset({ x: this.offsetX })
            .key('Toggle01_Toggle5')
            .borderWidth(1)
          Button('改变位置和大小').width(100)
            .onClick(() => {
              this.width1 = 30
              this.offsetX = -50
            }).backgroundColor(0x317aff)
        }.width('80%').borderWidth(2).padding(5).margin(5)
      }.height('100%').width('100%').align(Alignment.Top)
    }
    .title('ToggleMultiTestLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}