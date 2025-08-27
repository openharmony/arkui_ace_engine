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
import { LengthMetrics, ThemeControl } from '@kit.ArkUI';

@Builder
export function RadioLevel1Builder(name: string, param: Object) {
  RadioLevel1Example()
}

ThemeControl.setDefaultTheme(undefined);

interface forSample {
  title?: string
  visit?: Visibility
}

@CustomDialog
struct MyDialog {
  controller: CustomDialogController = new CustomDialogController({ builder: MyDialog() })

  build() {
    Column({ space: 8 }) {
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Column() {
          Text('Radio1')
          Radio({ value: 'Radio1', group: 'radioGroup' })
            .checked(true)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .key('Radio001')
            .onChange((isChecked: boolean) => {
              console.log('RadioCustomDialog1 status is ' + isChecked)
            })
        }

        Column() {
          Text('Radio2')
          Radio({ value: 'Radio2', group: 'radioGroup' })
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .key('Radio002')
            .onChange((isChecked: boolean) => {
              console.log('RadioCustomDialog2 status is ' + isChecked)
            })
        }

        Column() {
          Text('Radio3')
          Radio({ value: 'Radio3', group: 'radioGroup' })
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .key('Radio003')
            .onChange((isChecked: boolean) => {
              console.log('RadioCustomDialog3 status is ' + isChecked)
            })
        }
      }

      Button('关闭弹窗')
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
  }
}

@Entry
@Component
struct RadioLevel1Example {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  indicatorBuilder() {
    Image($r('app.media.app_icon'))
  }

  @State checked1: boolean | undefined = undefined //checked属性
  @State checked2: boolean | undefined = undefined
  @State checked3: boolean | undefined = undefined
  @State checkedTest1: boolean | undefined = undefined //为了直观看到分组情况，自动化不用再重复点击
  @State checkedTest2: boolean | undefined = undefined
  @State value: string | undefined = undefined //接口
  @State group: string | undefined | null = undefined
  @State visible: Visibility | undefined = undefined //走焦相关属性
  @State focusable1: boolean = true
  @State enabled1: boolean = true
  @State show: boolean = true
  @State Color1: Color | undefined = undefined //radioStyle属性
  @State Color2: number | undefined = undefined
  @State Color3: string | undefined = undefined
  @State Color4: Resource | undefined = undefined
  @State index: number = 0
  @State num: number = 0
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
  testCases1: Array<RadioIndicatorType | undefined> = [
    RadioIndicatorType.TICK,
    RadioIndicatorType.DOT,
    RadioIndicatorType.CUSTOM,
    undefined,
    -1,
    0,
    1,
    2,
    3
  ]

  @Styles
  focusedStyles() {
    .backgroundColor(Color.Orange)
  }

  @Styles
  normalStyles() {
    .backgroundColor(Color.White)
  }

  //单选
  private case0 = () => {
    this.checked1 = true
    this.checked2 = false
    this.checked3 = false
    this.Color1 = Color.Pink //Radio1开启状态底板颜色
    this.Color2 = 0xffff00 //Radio1关闭状态描边颜色
    this.Color3 = 'rgb(255,255,0)' //Radio2开启状态底板颜色
    this.Color4 = $r('sys.color.ohos_id_color_warning') //Radio2开启状态内部圆饼颜色
  }
  //多选
  private case1 = () => {
    this.checked1 = true
    this.checked2 = true
    this.checked3 = false
    this.Color1 = Color.Blue
    this.Color2 = 10
    this.Color3 = '#ffff00'
    this.Color4 = $r('sys.color.ohos_id_color_toolbar_text')
  }
  //异常值
  private case2 = () => {
    this.checked1 = true
    this.checked2 = true
    this.checked3 = true
    this.Color1 = Color.Pink
    this.Color2 = -10
    this.Color3 = 'zzz'
    this.Color4 = $r('app.string.module_desc')
  }
  private case3 = () => {
    this.checked1 = undefined
    this.checked2 = undefined
    this.checked3 = undefined
    this.Color1 = undefined
    this.Color2 = undefined
    this.Color3 = undefined
    this.Color4 = undefined
  }
  //1、4、5三个为一组 传空值，看是否能作为一个group
  //预期结果：选中态为2、4
  private case4 = () => {
    this.value = ''
    this.group = null
    this.checkedTest1 = false
    this.checkedTest2 = true
  }
  //1为1组，2、3为一组，4、5为一组 正常值
  //预期结果：选中态为1、2、4
  private case5 = () => {
    this.value = 'Radio5'
    this.group = 'test'
    this.checkedTest1 = true
    this.checkedTest2 = true
  }
  //动态改变group，2、3、4、5为一组 动态切换两个radiogroup为一个
  //预期结果：选中态为1、4
  private case6 = () => {
    this.value = 'Radio5'
    this.group = 'groupTest'
    this.checkedTest1 = true
    this.checkedTest2 = true
  }
  //正常值变为undefined
  private case7 = () => {
    this.value = undefined
    this.group = undefined
    this.checkedTest1 = undefined
    this.checkedTest2 = undefined
  }
  private caseVisits: Array<forSample> = [
    { title: 'Hidden', visit: Visibility.Hidden },
    { title: 'None', visit: Visibility.None },
    { title: 'Visible', visit: Visibility.Visible }
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 8 }) {
          Text('Radio接口测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row({ space: 2 }) {
            Text(`${this.index + 1}/`)
              .width(25)
            Text(`${this.testCases1.length}`)
              .key(`totalTest1`)
            Text('Test++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.index++
                if (this.index >= this.testCases1.length) {
                  this.index = 0
                }
              })
            Text('Test--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.index--
                if (this.index < 0) {
                  this.index = this.testCases1.length - 1
                }
              })
          }

          Row({ space: 2 }) {
            Radio({ value: '', group: '' })
              .checked($$this.checkedTest1)
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
            Radio({ value: 'Radio2', group: 'group1' })
              .checked($$this.checkedTest2)
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
            Radio({ value: 'Radio3', group: 'group1' })
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
            Radio({ value: 'Radio4', group: this.group })
              .checked($$this.checkedTest2)
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
            Radio({
              value: this.value!,
              group: this.group!,
              indicatorType: this.testCases1[this.index],
              indicatorBuilder: () => {
                this.indicatorBuilder()
              }
            }).direction(this.dir[this.num]).margin({ start: LengthMetrics.vp(10) })
              .size({ width: 20, height: 20 }).key('RadioTest4')
          }.margin(5).padding(5)

          //测试点：主要看分组情况是否正确，预期写在case上了
          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            MyComponent({ title: '', func: this.case4 })
            MyComponent({ title: 'test', func: this.case5 })
            MyComponent({ title: 'group1', func: this.case6 })
            MyComponent({ title: 'undefined', func: this.case7 })
          }

          Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })

          Text('Radio 属性及事件测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row({ space: 2 }) {
            Radio({ value: 'Radio1', group: 'radioGroup2' })
              .key('Radio00_Radio1')
              .checked($$this.checked1)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio1 status is ' + isChecked)
              })

            Radio({ value: 'Radio2', group: 'radioGroup2' })
              .key('Radio00_Radio2')
              .checked($$this.checked2)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio2 status is ' + isChecked)
              })
            Radio({ value: 'Radio3', group: 'radioGroup2' })
              .key('Radio00_Radio3')
              .checked($$this.checked3)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Radio3 status is ' + isChecked)
              })
          }.margin(5).padding(5)

          Row({ space: 2 }) {
            Radio({ value: 'Radio1', group: 'radioGroup3' })
              .checked(true)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .radioStyle({ checkedBackgroundColor: this.Color1 })
            Radio({ value: 'Radio2', group: 'radioGroup4' })
              .checked(false)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .radioStyle({ uncheckedBorderColor: this.Color2 })
            Radio({ value: 'Radio3', group: 'radioGroup5' })
              .checked(true)
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
              .radioStyle({ checkedBackgroundColor: this.Color3, indicatorColor: this.Color4 })
          }.margin(5).padding(5).backgroundColor('#EEE9E9')

          /*测试点：1、看checked属性，满足同一个group只有一个被选中
                  2、radioStyle属性，包括正常值和异常值
                  3、onChange事件，包括点击时触发以及动态改变时触发*/
          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            MyComponent({ title: '颜色正常值1', func: this.case0 })
            MyComponent({ title: '颜色正常值2', func: this.case1 })
            MyComponent({ title: '颜色异常值', func: this.case2 })
            MyComponent({ title: 'all undefined', func: this.case3 })
          }

          Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })

          Text('手工用例：走焦测试：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            Radio({ value: '', group: 'group2' }).direction(this.dir[this.num]).margin({ start: LengthMetrics.vp(10) })
            Radio({ value: '', group: 'group2' }).direction(this.dir[this.num]).margin({ start: LengthMetrics.vp(10) })
              .stateStyles({
                focused: this.focusedStyles,
                normal: this.normalStyles,
              }) //设置获焦样式
            Radio({ value: '', group: 'group2' })
              .tabIndex(-1)
              .defaultFocus(true)
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
            Radio({ value: '', group: 'group2' })
              .focusable(this.focusable1)
              .direction(this.dir[this.num])
              .margin({ start: LengthMetrics.vp(10) })
              .visibility(this.visible)
              .enabled(this.enabled1)
              .key('RadioTest5')
            if (this.show) {
              Radio({ value: '', group: 'group2' })
                .direction(this.dir[this.num])
                .margin({ start: LengthMetrics.vp(10) })
            }
          }

          /*测试点：1、左右及tab键走焦及获焦样式正常
                  2、disable、visibility.None、focus(false)、if(false)时不获焦*/
          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseVisits, (item: forSample) => {
              MyComponent({
                title: item.title, func: () => {
                  this.visible = item.visit
                }
              })
            }, (item: forSample) => item.title)
          }

          Row({ space: 2 }) {
            MyComponent({
              title: 'focusable', func: () => {
                this.focusable1 = !this.focusable1
              }
            })
            MyComponent({
              title: 'enabled', func: () => {
                this.enabled1 = !this.enabled1
              }
            })
            MyComponent({
              title: 'show', func: () => {
                this.show = !this.show
              }
            })
          }

          Text('子窗口弹窗Radio组件onChange事件触发').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row() {
            Button('弹出弹窗，内置Radio组件')
              .key('Button001')
              .onClick(() => {
                this.dialog.open()
              }).backgroundColor(0x317aff)
          }

          Text('切换direction属性Radio组件镜像效果').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row() {
            Button('direction属性切换')
              .onClick(() => {
                this.num++
                if (this.num >= this.dir.length) {
                  this.num = 0
                }
              })
              .width('40%')
              .height(32)
              .margin(3)
              .backgroundColor('orange')
          }
        }.borderWidth(2)
      }.height('100%').width('100%').align(Alignment.Top)
    }
    .title('RadioLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}