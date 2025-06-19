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

ThemeControl.setDefaultTheme(undefined);

@Builder
export function SelectLevel11Builder(name: string, param: Object) {
  SelectLevel1_1()
}

@CustomDialog
struct MyDialog {
  controller: CustomDialogController = new CustomDialogController({
    builder: MyDialog()
  })
  @State text: string = 'TTTTT'
  @State index: number = 2
  @State space: number = 8
  @State arrowPosition: ArrowPosition = ArrowPosition.END

  build() {
    Column() {
      Select([{ value: 'aaa', icon: $r('app.media.app_icon') },
        { value: 'bbb', icon: $r('app.media.app_icon') },
        { value: 'ccc', icon: $r('app.media.app_icon') },
        { value: 'ddd', icon: $r('app.media.app_icon') }])
        .selected(this.index)
        .value(this.text)
        .font({ size: 16, weight: 500 })
        .fontColor('#182431')
        .selectedOptionFont({ size: 16, weight: 400 })
        .optionFont({ size: 16, weight: 400 })
        .space(this.space)
        .arrowPosition(this.arrowPosition)
        .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
        .optionWidth(200)
        .optionHeight(300)
        .key('Select001')
        .onSelect((index: number, text?: string | undefined) => {
          console.info('SelectCustomDialog: ' + index + ' value: ' + text)
          this.index = index;
          if (text) {
            this.text = text;
          }
        })
        .margin(10)
      Button('关闭弹窗')
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
    .height('80%')
    .width('100%')
  }
}

@Entry
@Component
struct SelectLevel1_1 {
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
  scroller: Scroller = new Scroller()
  pathStack: NavPathStack = new NavPathStack()
  @State num: number = 0
  @State select: number = 0
  @State select1: number = 1
  @State value: string = '不设宽高自适应显示vegbb'
  @State value1: string = '通用属性的一些异常值'
  @State dir: Array<Direction | undefined> = [undefined, Direction.Ltr, Direction.Rtl, Direction.Auto]

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column() {
          Text('子窗口弹窗Select组件onChange事件触发')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row() {
            Button('弹出弹窗，内置Select组件')
              .key('Button001')
              .onClick(() => {
                this.dialog.open()
              })
              .backgroundColor(0x317aff)
          }

          Button('direction属性切换')
            .onClick(() => {
              this.num++
              if (this.num >= this.dir.length) {
                this.num = 0
              }
            })
            .width('40%')
            .height(32)
            .backgroundColor('orange')
          Text('不设宽高,自适应显示 渐变色边框')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, {
            value: '选项5'
          }])//.selected(-1)  无菜单项选中
            .value($$this.value)
            .key('2Select1')
            .direction(this.dir[this.num])
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
          Text('Select组件与通用属性结合考虑异常值')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '苹果' }, { value: '香蕉' }, { value: '西瓜' }, { value: '柠檬' }, {
            value: '葡萄'
          }])
            .key('2Select0+')
            .selected(this.select1)
            .value($$this.value1)
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
            .divider({
              strokeWidth: 5,
              startMargin: 5,
              endMargin: 25,
              color: Color.Red
            })
            .direction(this.dir[this.num])
            .onSelect((index: number, text?: string | undefined) => {
              this.select1 = index
            })

          Text('固定宽 .width(200) 边框')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
            .selected(1)
            .value('固定宽TTTTbqfarnbj;tqnbtqb')
            .width(200)
            .borderWidth(2)
            .borderColor(Color.Red)
            .borderStyle(BorderStyle.Dashed)
            .borderRadius(10)
            .key('2Select2')
            .direction(this.dir[this.num])

          Text('固定高.height(100) 图片边框')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
            .selected($$this.select)
            .height(100)
            .key('2Select3')
            .direction(this.dir[this.num])
            .borderImage({
              source: $r('app.media.app_icon'),
              slice: 40,
              width: 40,
              outset: '5px',
              repeat: RepeatMode.Repeat,
              fill: false
            })

          Text('百分比设置宽高 背景颜色')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
            .selected(1)
            .value('百分比设置宽高')
            .width('50%')
            .height(50)
            .backgroundColor(Color.Blue)
            .key('2Select4')
            .direction(this.dir[this.num])

          Text('固定宽高.width(300).height(100) 背景颜色')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
            .selected(1)
            .value('TTTTbqfarnbj;tqnbtqb')
            .font({
              size: 30,
              weight: 400,
              family: 'serif',
              style: FontStyle.Normal
            })
            .width(300)
            .height(100)
            .backgroundColor(Color.Blue)
            .key('2Select5')
            .direction(this.dir[this.num])

          Text('size .padding(40) 背景颜色')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }, {
            value: '选项6'
          }])
            .selected(1)
            .value('TTTTbqfarnbj;tqnbtqb')
            .font({
              size: 30,
              weight: 400,
              family: 'serif',
              style: FontStyle.Normal
            })
            .size({ width: 300, height: 100 })
            .padding(40)//设置内边距属性
            .backgroundColor(Color.Blue)
            .key('2Select6')
            .direction(this.dir[this.num])

          Text('constraintSize .margin(20) 背景图片')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }, {
            value: '选项6'
          }, { value: '选项7' }])
            .selected(1)
            .value('TTTTbqfarnbj;tqnbtqb')
            .size({ width: 400, height: 40 })
            .constraintSize({ maxWidth: 300 })
            .margin(15)//设置外边距属性
            .backgroundImage('/pages/picture/landscape.jpg', ImageRepeat.X)
            .key('2Select7')
            .direction(this.dir[this.num])

          Text('位置设置')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Text('布局约束 offset({x: 50, y: 10}) 点击控制 颜色渐变--角度渐变')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
            .selected(1)
            .value('TTTTbqfarnbj;tqnbtqb')
            .aspectRatio(2.5)
            .height(60)
            .key('2Select8')
            .offset({ x: 50, y: 10 })
            .hitTestBehavior(HitTestMode.None)
            .direction(this.dir[this.num])
            .sweepGradient({
              center: [50, 50],
              start: 0,
              end: 359,
              rotation: 45, // 旋转角度
              repeating: true, // 渐变颜色是否重复
              colors: [[0xff0000, 0.0], [0x0000ff, 0.3], [0xffff00, 0.5]] // 数组末尾元素占比小于1时满足重复着色效果
            })

          Text('Column .position({x: 10, y: 10}) 禁用控制 颜色渐变--径向渐变')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Column() {
            Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
              .selected(1)
              .value('position')
              .size({ width: 300, height: 50 })
              .align(Alignment.Start)
              .position({ x: 10, y: 10 })
              .enabled(false)
              .key('2Select9')
              .direction(this.dir[this.num])
              .radialGradient({
                center: [50, 50],
                radius: 60,
                repeating: true,
                colors: [[0xff0000, 0.0], [0x0000ff, 0.3], [0xffff00, 0.5]] // 数组末尾元素占比小于1时满足重复着色效果
              })
          }.height(100).width('100%')
        }
      }.scrollBar(BarState.Off)
    }
    .title('SelectLevel11')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}