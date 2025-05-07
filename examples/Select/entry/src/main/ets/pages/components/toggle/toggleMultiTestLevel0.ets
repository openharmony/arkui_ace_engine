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
export function ToggleMultiTestLevel0Builder(name: string, param: Object) {
  toggleMultiTestLevel0()
}

interface objectSample {
  title?: string | undefined,
  type?: ToggleType | undefined,
  visit?: Visibility | undefined
}

interface SwitchStyle1 {
  pointRadius?: number | Resource | undefined,
  unselectedColor?: ResourceColor | undefined,
  pointColor?: ResourceColor | undefined,
  trackBorderRadius?: number | Resource | undefined
}

@CustomDialog
struct MyDialog {
  controller: CustomDialogController = new CustomDialogController({ builder: MyDialog() })

  build() {
    Column({ space: 10 }) {
      Toggle({
        isOn: false,
        type: ToggleType.Checkbox,
      })
        .key('Toggle001')
        .onChange((value: boolean) => {
          console.info('ToggleCustomDialog Checkbox change is' + value)
        })
      Toggle({
        isOn: false,
        type: ToggleType.Switch,
      })
        .key('Toggle002')
        .onChange((value: boolean) => {
          console.info('ToggleCustomDialog Switch change is' + value)
        })
      Toggle({ type: ToggleType.Button, isOn: false }) {
        Text('status button').fontColor('#182431').fontSize(12)
      }
      .key('Toggle003')
      .width(106)
      .onChange((value: boolean) => {
        console.info('ToggleCustomDialog Button change is' + value)
      })

      Button('关闭弹窗')
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
  }
}

@Entry
@Component
struct toggleMultiTestLevel0 {
  pathStack: NavPathStack = new NavPathStack()

  @State checked1: boolean | undefined = undefined //checked属性
  @State checked2: boolean | undefined = undefined
  @State checked3: boolean | undefined = undefined
  @State Color1: Color | undefined = undefined //selectedColor switchPointColor属性
  @State Color2: number | undefined = undefined
  @State Color3: string | undefined = undefined
  @State Color4: Resource | undefined = undefined
  @State text: string | undefined = undefined //容器相关
  @State fontSize1: number | undefined = undefined
  @State clip1: boolean = false
  @State type: ToggleType | undefined = ToggleType.Checkbox //走焦相关属性
  @State visible: Visibility | undefined = undefined
  @State focusable1: boolean = true
  @State enabled1: boolean = true
  @State show: boolean = true
  @State index: number = 0
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
  testCases1: SwitchStyle1[] = [
    {
      pointRadius: -1,
      unselectedColor: Color.Red,
      pointColor: Color.Green,
      trackBorderRadius: -1
    },
    {
      pointRadius: 0,
      unselectedColor: $r('app.color.toggle_unselected_color'),
      pointColor: $r('app.string.module_desc'),
      trackBorderRadius: 0
    },
    {
      pointRadius: 4,
      unselectedColor: '#FF1493',
      pointColor: 'hdjsdjjkdjuwjd',
      trackBorderRadius: 4
    },
    {
      pointRadius: undefined,
      unselectedColor: undefined,
      pointColor: undefined,
      trackBorderRadius: undefined
    },
    {
      pointRadius: 8,
      unselectedColor: 'rgb( 255,105,180)',
      pointColor: 'rgba(255,105,180,111)',
      trackBorderRadius: 6
    },
    {
      pointRadius: 16,
      unselectedColor: 'rgb( 255,105,180)',
      pointColor: 'rgba(255,105,180,111)',
      trackBorderRadius: 3
    },
  ]

  @Styles
  focusedStyles() {
    .backgroundColor(Color.Orange)
  }

  @Styles
  normalStyles() {
    .backgroundColor(Color.White)
  }

  private case1 = () => {
    this.checked1 = true
    this.checked2 = false
    this.checked3 = false
    this.Color1 = Color.Pink
    this.Color2 = 0xffff00
    this.Color3 = 'rgb(255,255,0)'
    this.Color4 = $r('sys.color.ohos_id_color_warning')
  }
  private case2 = () => {
    this.checked1 = false
    this.checked2 = true
    this.checked3 = true
    this.Color1 = Color.Blue
    this.Color2 = 1
    this.Color3 = '#ffff00'
    this.Color4 =
      $r('sys.color.ohos_id_color_toolbar_text')
  }
  //异常值
  private case3 = () => {
    this.checked1 = true
    this.checked2 = true
    this.checked3 = true
    this.Color1 = Color.Pink
    this.Color2 = -1
    this.Color3 = 'zzz'
    this.Color4 = $r('app.string.module_desc')
  }
  private case4 = () => {
    this.checked1 = undefined
    this.checked2 = undefined
    this.checked3 = undefined
    this.Color1 = undefined
    this.Color2 = undefined
    this.Color3 = undefined
    this.Color4 = undefined
  }
  private case5 = () => {
    this.text = '按钮文字是一二三四五六七八九十十一十二十三十四' //只有中文
    this.fontSize1 = 16
  }
  private case6 = () => {
    this.text = '按钮文字是jhalfjkfsdfssfdakjkhfjshfefsjdshkggfdjdtdshhfsdrfgfhhsfd' //中文英文参杂
    this.fontSize1 = 32
  }
  private case7 = () => {
    this.text = 'jhalfjkfsdfssfdakjkh'
    this.fontSize1 = 40
  }

  @Builder
  myBuilder(value: string) { //局部自定义组件
    Column({ space: 2 }) {
      Text('自定义组件').backgroundColor(Color.White)
      TextInput({ placeholder: 'input' }).width(100).caretColor(Color.White)
    }
    .borderWidth(1)
  }

  private caseTypes: Array<objectSample> = [
    { title: 'Checkbox', type: ToggleType.Checkbox },
    { title: 'Button', type: ToggleType.Button },
    { title: 'Switch', type: ToggleType.Switch }
  ]
  private caseVisits: Array<objectSample> = [
    { title: 'Hidden', visit: Visibility.Hidden },
    { title: 'None', visit: Visibility.None },
    { title: 'Visible', visit: Visibility.Visible }
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          //测试点：type正确,ison不传走默认值
          Text('Toggle接口测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row({ space: 2 }) {
            // Toggle() //不传参
            // Toggle({ isOn: true}) //不传必选参数
            Toggle({ type: undefined }).borderWidth(1)
            Toggle({ type: ToggleType.Checkbox }).borderWidth(1)
            Toggle({ type: ToggleType.Button, isOn: true }).borderWidth(1).width(50).height(30)
            Toggle({ type: ToggleType.Switch }).borderWidth(1)
          }

          Divider().strokeWidth('1px')
          Text('checked属性及事件测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row({ space: 2 }) {
            Toggle({ type: ToggleType.Checkbox, isOn: $$this.checked1 }).selectedColor(this.Color1)
              .key('Toggle00_Checkbox')
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Checkbox status is ' + isChecked)
              })
            Toggle({ type: ToggleType.Button, isOn: $$this.checked2 })
              .width(50)
              .height(30)
              .selectedColor(this.Color2)
              .key('Toggle00_Button')
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Button status is ' + isChecked)
              })
            Toggle({ type: ToggleType.Switch, isOn: $$this.checked3 })
              .selectedColor(this.Color3)
              .switchPointColor(this.Color4)
              .key('Toggle00_Switch')
              .onChange((isChecked: boolean) => {
                console.log('lhl:---Switch status is ' + isChecked)
              })
          }.backgroundColor('#EEE9E9')

          /*测试点：1、看checked属性动态修改表现正确
                  2、selectedColor、switchPointColor属性，包括正常值和异常值
                  3、onChange事件，包括点击时触发以及动态改变时触发*/
          Text('SwitchStyle属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
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
            Toggle({ type: ToggleType.Checkbox, isOn: $$this.checked1 }).selectedColor(this.Color1)
              .key('Toggle01_Checkbox')
              .switchStyle(this.testCases1[this.index])
            Toggle({ type: ToggleType.Button, isOn: $$this.checked2 })
              .width(50)
              .height(30)
              .selectedColor(this.Color2)
              .key('Toggle01_Button')
              .switchStyle(this.testCases1[this.index])

            Toggle({ type: ToggleType.Switch, isOn: $$this.checked3 })
              .selectedColor(this.Color3)
              .switchPointColor(this.Color4)
              .key('Toggle01_Switch')
              .switchStyle(this.testCases1[this.index])
          }.backgroundColor('#EEE9E9')

          /*测试点：1、看switchStyle属性动态修改表现正确
                  2、switchStyle对象里面的属性值，包括正常值和异常值
                  3、ToggleType.Button和ToggleType.Checkbox两种类型使用switchStyle单纯不生效，不会引起应用崩溃*/

          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            MyComponent({ title: '颜色正常值1', func: this.case1 })
            MyComponent({ title: '颜色正常值2', func: this.case2 })
            MyComponent({ title: '颜色异常值', func: this.case3 })
            MyComponent({ title: 'all undefined', func: this.case4 })
          }

          Divider().strokeWidth('1px')
          Text('Toggle 作为容器').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Toggle({ type: ToggleType.Button }) { //动态改变文字，看自适应情况
            Text(this.text).fontColor('#182431').fontSize(this.fontSize1)
          }.backgroundColor(Color.Pink).borderWidth(2)

          Toggle({ type: ToggleType.Button }) { //设置容器宽高，文字超出父组件
            Text('1234435jfsjkdfkngd是的一二三五i五ghjgaukdhasfjksfgsrsfsdfsdfgrsgfddsfdsfdgfsfdsfdgsdsd')
              .fontColor('#182431')
              .fontSize(20)
              .width(250) //0522修改：文字加长，看圆角处的裁剪情况
          }
          .backgroundColor(Color.Pink)
          .borderWidth(2)
          .width(200)
          .height(100)
          .clip(this.clip1) //配合clip属性

          Toggle({ type: ToggleType.Button }) { //放自定义组件
            this.myBuilder('1')
          }.backgroundColor(Color.Pink).borderWidth(2).width(200).height(100)

          Toggle({ type: ToggleType.Button }) { //放自定义组件
            MyComponent({ title: 'MyComponent' }).borderWidth(1)
          }.backgroundColor(Color.Pink).borderWidth(2).width(200).height(50)

          /*测试点：1、动态改变文字，看自适应情况
                  2、clip属性、孩子节点超出父容器
                  3、放自定义组件*/
          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            MyComponent({ title: '只有中文', func: this.case5 })
            MyComponent({ title: '中英文参杂', func: this.case6 })
            MyComponent({ title: '只有英文', func: this.case7 })
            MyComponent({
              title: 'clip', func: () => {
                this.clip1 = !this.clip1
              }
            })
          }

          Divider().strokeWidth('1px')
          Text('手工用例：走焦测试：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            Toggle({ type: this.type }).width('50').borderWidth(1)
            Toggle({ type: this.type }).width('50').borderWidth(1)
              .stateStyles({
                focused: this.focusedStyles,
                normal: this.normalStyles
              }) //设置获焦样式
            Toggle({ type: this.type }).tabIndex(-1).width('50').borderWidth(1).defaultFocus(true)
            Toggle({ type: this.type })
              .focusable(this.focusable1)
              .visibility(this.visible)
              .enabled(this.enabled1)
              .width('50')
              .borderWidth(1)
              .key('ToggleTest5')
            if (this.show) {
              Toggle({ type: this.type }).width('50').borderWidth(2)
            }
          }

          /*测试点：1、左右及tab键走焦及获焦样式正常
                  2、disable、visibility.None、focus(false)、if(false)时不获焦
                  3、针对不同类型进行测试*/
          Text('切换测试参数：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseVisits, (item: objectSample) => {
              MyComponent({
                title: item.title, func: () => {
                  this.visible = item.visit
                }
              })
            }, (item: objectSample) => item.title)
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

          Text('切换类型：').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseTypes, (item: objectSample) => {
              MyComponent({
                title: item.title, func: () => {
                  this.type = item.type
                }
              })
            }, (item: objectSample) => item.title)
          }

          Text('子窗口弹窗Toggle组件onChange事件触发').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row() {
            Button('弹出弹窗，内置Toggle组件')
              .key('Button001')
              .onClick(() => {
                this.dialog.open()
              }).backgroundColor(0x317aff)
          }
        }.margin(5).borderWidth(2)
      }.height('100%').width('100%').align(Alignment.Top).scrollBar(BarState.Off)
    }
    .title('ToggleMultiTestLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}