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

import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderLevel01Builder(name: string, param: Object) {
  Slider_Level0_1()
}

@CustomDialog
struct MyDialog {
  @State outSetValueOne: number = 40
  controller: CustomDialogController = new CustomDialogController({ builder: MyDialog() })

  build() {
    Column({ space: 20 }) {
      Slider({
        value: this.outSetValueOne,
        min: 0,
        max: 100,
        style: SliderStyle.OutSet
      })
        .showTips(true, '小广nb')
        .key('Slider001')
        .onChange((value: number, mode: SliderChangeMode) => {
          this.outSetValueOne = value
          console.info('SliderCustomDialog value:' + value + 'mode:' + mode.toString())
        })
      Button('关闭弹窗')
        .borderRadius(0)
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
  }
}

@Entry
@Component
struct Slider_Level0_1 {
  pathStack: NavPathStack = new NavPathStack()
  @State num: number = 0
  @State outSetValue1: number = 40
  @State outSetValue2: number = 40
  @State outSetValue3: number = 40
  @State showPopup: boolean = false
  @State dir: Array<Direction | undefined | null> =
    [null, Direction.Rtl, undefined, Direction.Rtl, Direction.Ltr, Direction.Rtl, Direction.Auto]
  private dialog = new CustomDialogController({
    builder: MyDialog(),
    showInSubWindow: true,
    autoCancel: false,
    cancel: () => {

    },
    closeAnimation: {
      duration: 350,
      onFinish: () => {

      }
    },
    alignment: DialogAlignment.Center,
    customStyle: true,
    backgroundColor: '#22000000',
    maskColor: '#ff0',
    isModal: true,
  })

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('direction属性切换')
            .onClick(() => {
              this.num++
              if (this.num >= this.dir.length) {
                this.num = 0
              }
            })
            .margin(3)
            .focusable(false)
            .backgroundColor(0x317aff)

          Text('子窗口弹窗Slider组件onChange事件触发').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row() {
            Text('弹窗内置Slider')
              .focusable(false)
              .key('Button001')
              .onClick(() => {
                this.dialog.open()
              })
              .backgroundColor(0x317aff)
          }

          Text('Slider组件与通用属性结合考虑异常值 ' + this.outSetValue1?.toFixed(2))
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row() {
            Slider({
              value: $$this.outSetValue1,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .showTips(true, '四组牛逼')
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
              .onChange((value: number) => {
                this.outSetValue1 = value
              })
              .defaultFocus(true)
              .key('Slider002')
          }

          Text('Slider组件双向绑定测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row() {
            Slider({
              value: $$this.outSetValue1,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .showTips(true,
                '1436456345634343434\n34343434343434343434343434343434343434343434343434345235235346453634')
              .direction(this.dir[this.num])
              .onChange((value: number, mode: SliderChangeMode) => {
                if (value > 60) {
                  this.showPopup = true
                } else {
                  this.showPopup = false
                }
                console.info('value:' + value + 'mode:' + mode.toString())
              })
              .key('slider')
          }
          .width('80%')
          .borderWidth(2)
          .borderColor(Color.Red)
          .bindPopup(this.showPopup, {
            message: 'This is a popup with PopupOptions'
          })

          Text('测试父组件设置裁剪tips的显示情况').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row() {
            Slider({
              value: $$this.outSetValue1,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .direction(this.dir[this.num])
              .showTips(true,
                '1436456345634343434\n34343434343434343434343434343434343434343434343434345235235346453634')
              .onChange((value: number, mode: SliderChangeMode) => {
                console.info('value:' + value + 'mode:' + mode.toString())
              })
              .rotate({
                x: 0,
                y: 0,
                z: 1,
                centerX: '50%',
                centerY: '50%',
                angle: 10
              }) // 组件以矢量(0,0,1)为旋转轴，绕中心点顺时针旋转300度
          }
          .width('80%')
          .borderWidth(2)
          .borderColor(Color.Red)
          .clip(true)

          Text('测试父组件设置width/height/padding/border/margin的显示情况')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Row() {
            Slider({
              value: $$this.outSetValue2,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .direction(this.dir[this.num])
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                console.info('value:' + value + 'mode:' + mode.toString())
              })
              .position({ x: 10, y: 10 })
              .width('80%')
              .height(30)
              .padding(40)
              .borderWidth(2)
              .margin(10)
              .backgroundColor(Color.Pink)
          }
          .width('80%')
          .height(100)
          .borderWidth(2)
          .borderColor(Color.Red)

          Text('测试父组件设置constraintSize/enabled/opacity/borderImage的显示情况')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row() {
            Slider({
              value: $$this.outSetValue3,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .direction(this.dir[this.num])
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                console.info('value:' + value + 'mode:' + mode.toString())
              })
              .constraintSize({ maxWidth: 100, minHeight: 50 })
              .width('80%')
              .height(30)
              .borderImage({
                source: {
                  angle: 90,
                  direction: GradientDirection.Left,
                  colors: [[0xAEE1E1, 0.0], [0xD3E0DC, 0.3], [0xFCD1D1, 1.0]]
                },
                slice: {
                  top: 10,
                  bottom: 10,
                  left: 10,
                  right: 10
                },
                width: {
                  top: '10px',
                  bottom: '10px',
                  left: '10px',
                  right: '10px'
                },
                repeat: RepeatMode.Stretch,
                fill: false
              })
              .margin(10)
              .backgroundColor(Color.Pink)
              .enabled(false)
              .opacity(0.5)
              .key('Slider003')
          }
          .width('80%')
          .height(100)
          .borderWidth(2)
          .borderColor(Color.Red)
        }
        .width('100%')
        .borderWidth(2)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
    }
    .title('SliderLevel01')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}