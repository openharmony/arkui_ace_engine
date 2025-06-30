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

import { Model1, Model6 } from '../base/DataModel';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function RatingLevel1Builder(name: string, param: Object) {
  RatingLevel1Example()
}

ThemeControl.setDefaultTheme(undefined);

interface exampleObject {
  backgroundUri?: string,
  foregroundUri?: string,
  secondaryUri?: string,
  direction?: Direction | undefined
}

@CustomDialog
struct MyDialog {
  @State rating: number = 3.5
  controller: CustomDialogController = new CustomDialogController({ builder: MyDialog() })

  build() {
    Column() {
      Rating({ rating: this.rating, indicator: false })
        .stars(5)
        .stepSize(0.5)
        .margin({ top: 24 })
        .onChange((value: number) => {
          this.rating = value
          console.info('CustomDialogRating value is: ' + value.toString())
        })
        .key('Rating001')
        .margin({ bottom: 10 })
      Button('关闭弹窗')
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
  }
}

@Entry
@Component
struct RatingLevel1Example {
  pathStack: NavPathStack = new NavPathStack()
  @State borderColorVal: Color = Color.Yellow
  @State model1: Model1 = new Model1()
  @State model6: Model6 = new Model6()
  @State info?: string = undefined
  @State show: boolean = false
  @State index: number = 0
  @State num: number = 0
  scroller: Scroller = new Scroller()
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
    maskColor: Color.Green,
    isModal: true,
  })

  private testCase: Array<exampleObject> = [
    {
      backgroundUri: 'hhh',
      foregroundUri: 'hhh',
      secondaryUri: 'hhh'
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Rtl
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: undefined
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Rtl
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Ltr
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Rtl
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Auto
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Rtl
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      direction: Direction.Auto
    },
    //undefined
    {
      backgroundUri: undefined, //预期走默认图源
      foregroundUri: undefined,
      secondaryUri: undefined
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      //验证图片比例1:2的情况
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
  ]
  private setParam(): void {
    // 1. 参数赋值
    this.model1.backgroundUri = this.testCase[this.index].backgroundUri
    this.model1.foregroundUri = this.testCase[this.index].foregroundUri
    this.model1.secondaryUri = this.testCase[this.index].secondaryUri
    this.model6.direction = this.testCase[this.index].direction
    // 2. 参数打印
    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\nbackgroundUri: ' + this.model1.backgroundUri + ', foregroundUri: ' + this.model1.foregroundUri +
      ', secondaryUri: ' + this.model1.secondaryUri + '\ndirection: ' + this.model6.direction
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Column({ space: 2 }) {
            Text('Rating组件 布局与剪裁规则测试')
              .fontSize(12)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Text('Rating组件设置宽高且按照图片为正方形设置')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Rating()
              .width(160)
              .height(40)
              .borderWidth(2)
              .margin(10)
              .padding(5)
              .backgroundColor(Color.Green)
              .key('rating1')
              .direction(this.model6.direction)
              .starStyle({
                backgroundUri: this.model1.backgroundUri,
                foregroundUri: this.model1.foregroundUri
              })
            Text('Rating组件设置宽高且按照图片为非正方形设置')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Rating()
              .height(50)
              .aspectRatio(4)
              .padding(10)
              .borderWidth(2)
              .borderColor(Color.Orange)
              .margin(10)
              .key('rating2')
              .direction(this.model6.direction)
              .foregroundColor(Color.Red)
              .starStyle({
                backgroundUri: this.model1.backgroundUri,
                foregroundUri: this.model1.foregroundUri,
                secondaryUri: this.model1.secondaryUri
              })
            Text('Rating组件设置高且设置圆角属性')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Rating()
              .borderWidth(2)
              .borderColor(Color.Yellow)
              .margin(10)
              .borderRadius(80)
              .key('rating3')
              .direction(this.model6.direction)
              .size({ height: 60 })
              .starStyle({
                backgroundUri: this.model1.backgroundUri,
                foregroundUri: this.model1.foregroundUri,
                secondaryUri: this.model1.secondaryUri
              })
            Text('Rating组件设置宽且设置enabled属性')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Rating()
              .width(300)
              .borderWidth(2)
              .borderColor(Color.Blue)
              .margin(10)
              .key('rating4')
              .direction(this.model6.direction)
              .starStyle({ backgroundUri: this.model1.backgroundUri, foregroundUri: this.model1.foregroundUri })
              .enabled(false)
            Text('Rating组件设置indicator为true')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10 })
            Rating({ rating: 1, indicator: true })
              .borderWidth(2)
              .borderColor(this.borderColorVal)
              .margin(10)
              .backgroundImage('../../../../../../../AppScope/resources/base/media/app_icon.png')
              .key('rating5')
              .direction(this.model6.direction)
              .onClick(() => {
                this.borderColorVal = Color.Pink
              })
          }
          .width('100%')

          Text('Rating组件与通用属性结合考虑异常值')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Rating({ rating: 1, indicator: false })
            .width(-1)
            .height(-1)
            .borderWidth(-1)
            .borderColor('fhujsfkjfjwsfjwj')
            .borderStyle(undefined)
            .borderRadius(-10)
            .size({ width: -100, height: undefined })
            .padding(-1)
            .margin(-1)
            .backgroundColor('hdshddjwjkjkwbjkwkj')
            .border(undefined)
            .borderImage(undefined)
            .clip(undefined)
            .direction(this.model6.direction)

          Text('子窗口弹窗Rating组件onChange事件触发')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row() {
            Button('弹出弹窗，内置Rating组件')
              .onClick(() => {
                this.dialog.open()
              }).backgroundColor(0x317aff)
              .key('Button001')
          }

          Divider()
            .strokeWidth('1px')
          Text('切换参数，显示参数=' + this.show)
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .onClick(() => {
            this.show = !this.show
          })
          Row({ space: 2 }) {
            Text(`${this.index + 1}/`)
              .width(25)
            Text(`${this.testCase.length}`)
              .key('rating10_cycles')
            Text('Test++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.setParam()
                // 控制循环
                this.index++
                if (this.index == this.testCase.length) {
                  this.index = 0
                }
              })

            Text('Test--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                // 控制循环
                this.index--
                if (this.index == -1) {
                  this.index = this.testCase.length - 1
                }
                this.setParam()
              })
          }

          if (this.show) {
            Text(this.info)
          }
        }
        .borderWidth(2)
      }
      .scrollBar(BarState.Off)
    }
    .title('RatingLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}