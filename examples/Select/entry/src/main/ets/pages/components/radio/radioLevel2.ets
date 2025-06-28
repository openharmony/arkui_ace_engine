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

@Builder
export function RadioLevel2Builder(name: string, param: Object) {
  RadioLevel2Example()
}

ThemeControl.setDefaultTheme(undefined);

interface obj {
  title?: string | undefined,
  visit?: Visibility | undefined
}

@Entry
@Component
struct RadioLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  @State visible: Visibility | undefined = undefined
  @State clip1: boolean = false
  @State offsetX: number | undefined = undefined
  @State width1: number = 50
  @State offsetX1: number = 0 //交互归一 手势相关
  @State offsetY: number = 0
  @State positionX: number = 0
  @State positionY: number = 0
  private panOption: PanGestureOptions = new PanGestureOptions({ direction: PanDirection.All })
  @State angle: number = 0
  @State rotateValue: number = 0
  @State scaleValue: number = 1
  @State pinchValue: number = 1
  @State pinchX: number = 0
  @State pinchY: number = 0
  private caseVisits: Array<obj> = [
    { title: 'Hidden', visit: Visibility.Hidden },
    { title: 'None', visit: Visibility.None },
    { title: 'Visible', visit: Visibility.Visible }
  ]
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomDialogExample({}),
    autoCancel: true,
    alignment: DialogAlignment.Default,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    customStyle: false
  })

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('Radio 通用属性组合测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 5 }) {
            Radio({ value: 'Radio1', group: 'radioGroup' })//不设置宽高
              .borderWidth(1)
              .padding({ top: 10, right: 10 })
              .backgroundColor(Color.Pink)
            Row() {
              Radio({ value: 'Radio2', group: 'radioGroup' })//设置单边宽高
                .width(70)
                .margin({ bottom: '10%', left: '10' })
                .borderWidth(1)
                .foregroundColor(Color.Pink)
            }
            .borderWidth(1)

            Row() {
              Radio({ value: 'Radio3', group: 'radioGroup' })
                .size({ width: 70, height: 70 })
                .borderWidth(1)
                .key('Radio01_Radio0')
            }
            .width(50)
            .borderWidth(1)
            .clip(this.clip1)

            Radio({ value: 'Radio4', group: 'radioGroup' })//宽度大于根容器
              .width(100)
              .height(100)
              .offset({ x: 50 })
              .borderWidth(1)
              .key('Radio01_Radio1')
              .onClick(() => {
                console.log('lhl:---Radio4 is onclick')
              })
          }

          Row({ space: 5 }) {
            Radio({ value: 'Radio7', group: 'radioGroup' })
              .width(-1)
              .height(-1)
              .borderWidth(-1)
              .borderColor('hello')
              .borderStyle(undefined)
              .borderRadius(-10)
              .size({ width: -100, height: undefined })
              .padding(-1)
              .margin(-1)
              .border(undefined)
              .borderImage(undefined)
            Radio({ value: 'Radio4', group: 'radioGroup' })
              .borderWidth(1)
              .height(30)
              .aspectRatio(2)
              .align(Alignment.BottomStart)
            Radio({ value: 'Radio5', group: 'radioGroup' })
              .borderWidth(1)
              .layoutWeight(2)
              .aspectRatio(0.8)
              .enabled(false)
              .key('Radio01_Radio2')
            Stack() {
              Radio({ value: 'Radio6', group: 'radioGroup' })
                .borderWidth(1)
                .responseRegion({
                  x: '-300%',
                  y: 0,
                  width: '300%',
                  height: '100%'
                })
                .key('Radio01_Radio3') //0522: 增加热区设置
            }
            .layoutWeight(3)
            .height(50)
            .margin({ top: 5 })
            .backgroundColor(0xFFE4C4)
            .align(Alignment.TopEnd)
          }
          .borderWidth(1)
          .width('100%')

          Text('是否裁剪：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            MyComponent({
              title: 'clip', func: () => {
                this.clip1 = !this.clip1
              }
            })
          }

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5, bottom: 5 })
          Text('自适应布局：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Flex({ direction: FlexDirection.Row }) {
            Radio({ value: 'Radio1', group: 'radioGroup1' })
              .width('20%')
              .borderWidth(1)
            Radio({ value: 'Radio2', group: 'radioGroup1' })
              .width('30%')
              .borderWidth(1)
            Radio({ value: 'Radio3', group: 'radioGroup1' })
              .width('50%')
              .borderWidth(1)
              .visibility(this.visible)
              .key('Radio01_Radio4')
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio3 status is ' + isChecked)
              })
          }.borderWidth(1)

          Text('控制组件显隐：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseVisits, (item: obj) => {
              MyComponent({
                title: item.title, func: () => {
                  this.visible = item.visit
                }
              })
            }, (item: obj) => item.title)
          }

          //交互归一
          Divider()
          Text('手工用例：交互归一：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            Radio({ value: '', group: 'group3' })
              .width(100)
              .onClick(() => {
                this.getUIContext().getPromptAction().showToast({
                  message: 'Radio is clicked',
                  duration: 1000
                })
              })
              .gesture(
                LongPressGesture({ repeat: true })// 由于repeat设置为true，长按动作存在时会连续触发，触发间隔为duration（默认值500ms）
                  .onAction((event: GestureEvent) => {
                    this.getUIContext().getPromptAction().showToast({
                      message: 'Radio LongPressGesture',
                      duration: 1000
                    })
                  })// 长按动作一结束触发
                  .onActionEnd(() => {
                    this.getUIContext().getPromptAction().showToast({
                      message: 'Radio LongPressGesture end',
                      duration: 1000
                    })
                  })
              )

            Radio({ value: '', group: 'group3' })
              .translate({ x: this.offsetX1, y: this.offsetY, z: 0 })
              .width(100)
              .gesture(
                PanGesture(this.panOption)
                  .onActionStart((event: GestureEvent) => {
                    this.getUIContext().getPromptAction().showToast({
                      message: 'Radio PanGesture start',
                      duration: 1000
                    })
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    this.offsetX1 = this.positionX + event.offsetX
                    this.offsetY = this.positionY + event.offsetY
                  })
                  .onActionEnd(() => {
                    this.positionX = this.offsetX1
                    this.positionY = this.offsetY
                    this.getUIContext().getPromptAction().showToast({
                      message: 'Radio PanGesture end',
                      duration: 1000
                    })
                  })
              )
          }

          Row({ space: 2 }) {
            Radio({ value: '', group: 'group3' })
              .width(100)
              .rotate({ angle: this.angle })// 双指旋转触发该手势事件
              .gesture(
                RotationGesture()
                  .onActionStart((event: GestureEvent) => {
                    console.info('Rotation start')
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    this.angle = this.rotateValue + event.angle
                  })
                  .onActionEnd(() => {
                    this.rotateValue = this.angle
                    console.info('Rotation end')
                  })
              )

            Radio({ value: '', group: 'group3' })
              .width(100)
              .scale({ x: this.scaleValue, y: this.scaleValue, z: 1 })// 双指捏合触发该手势事件
              .gesture(
                PinchGesture({ fingers: 2 })
                  .onActionStart((event: GestureEvent) => {
                    console.info('Pinch start')
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    this.scaleValue = this.pinchValue * event.scale
                    this.pinchX = event.pinchCenterX
                    this.pinchY = event.pinchCenterY
                  })
                  .onActionEnd(() => {
                    this.pinchValue = this.scaleValue
                    console.info('Pinch end')
                  })
              )
          }

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5, bottom: 5 })
          //radio位置和大小改变，热区变化情况
          Text('radio位置和大小改变，热区变化情况：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            Radio({ value: '1', group: 'radioGroup2' })
              .width(this.width1)
              .offset({ x: this.offsetX })
              .key('Radio01_Radio5')
              .borderWidth(1)
            Radio({ value: '2', group: 'radioGroup2' })
              .borderWidth(1)
              .key('Radio01_Radio6')
          }

          //复杂场景，弹窗和radio组合
          Text('复杂场景，和弹窗组合使用：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            Button('改变位置和大小')
              .width(100)
              .onClick(() => {
                this.width1 = 20
                this.offsetX = -50
              })
              .backgroundColor(0x317aff)
            Button('自定义弹窗')
              .onClick(() => {
                if (this.dialogController != undefined) {
                  this.dialogController.open()
                }
              })
              .backgroundColor(0x317aff)
              .key('Radio01_Dialog')
          }
        }
        .width('80%')
        .borderWidth(2)
        .padding(5)
        .margin(5)
      }
      .height('100%')
      .width('100%')
      .align(Alignment.Top)
    }
    .title('RadioLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

//和自定义弹窗组合
@CustomDialog
struct CustomDialogExample {
  controller: CustomDialogController = new CustomDialogController({ builder: CustomDialogExample() })

  @Styles
  focusedStyles() {
    .backgroundColor(Color.Orange)
  }

  @Styles
  normalStyles() {
    .backgroundColor(Color.White)
  }

  build() {
    Column() {
      Text('Radio和Dialog组合')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
      List({ space: 3 }) {
        ListItem() {
          Row() {
            Text('第一项').fontWeight(FontWeight.Bolder)
              .fontSize(20)
            Radio({ value: 'Radio1', group: 'radioGroup' })
              .checked(true)
              .height(20)
              .width(20)
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio1 status is ' + isChecked)
                this.controller.close()
              })
          }
          .justifyContent(FlexAlign.SpaceBetween)
          .width('100%')
        }
        .height(53)

        ListItem() {
          Row() {
            Text('第二项')
              .fontWeight(FontWeight.Bolder)
              .fontSize(20)
            Radio({ value: 'Radio2', group: 'radioGroup' })
              .checked(false)
              .height(20)
              .width(20)
              .key('Radio01_Radio7')
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio2 status is ' + isChecked)
                this.controller.close()
              })
          }
          .justifyContent(FlexAlign.SpaceBetween)
          .width('100%')
        }
        .height(53)

        ListItem() {
          Row() {
            Text('第三项')
              .fontWeight(FontWeight.Bolder)
              .fontSize(20)
            Radio({ value: 'Radio3', group: 'radioGroup' })
              .checked(false)
              .height(20)
              .width(20)
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio3 status is ' + isChecked)
                this.controller.close()
              })
          }
          .justifyContent(FlexAlign.SpaceBetween)
          .width('100%')
        }
        .height(53)
      }
      .width('100%')
      .divider({
        strokeWidth: 1,
        startMargin: 3,
        endMargin: 3
      })

      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            this.controller.close()
          })
          .backgroundColor(0xffffff)
          .fontColor(Color.Black)
        Button('confirm')
          .onClick(() => {
            this.controller.close()
          })
          .backgroundColor(0xffffff)
          .fontColor(Color.Red)
      }
      .margin({ bottom: 10 })
    }
  }
}