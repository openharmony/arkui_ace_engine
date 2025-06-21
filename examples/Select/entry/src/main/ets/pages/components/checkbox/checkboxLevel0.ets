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

import { MyComponent } from '../base/MyComponent'
import { LengthMetrics, ThemeControl } from '@kit.ArkUI'

@Builder
export function CheckboxLevel0Builder(name: string, param: Object) {
  CheckboxLevel0Example()
}

ThemeControl.setDefaultTheme(undefined);

interface objectSample {
  width: number,
  height: number
}

interface objectSample1 {
  toastInfo?: string,
  groupName_1?: string,
  groupName_2?: string,
  boxName_G1?: string,
  boxName_G2?: string,
  boxName_G3?: string,
  boxName_G4?: string,
  boxName_N1?: string,
  boxName_N2?: string,
  boxName_N3?: string,
  boxName_N4?: string,
  select?: boolean
}

@CustomDialog
struct MyDialog {
  controller: CustomDialogController = new CustomDialogController({ builder: MyDialog() })

  build() {
    Column({ space: 10 }) {
      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        CheckboxGroup({ group: 'checkboxGroup' })
          .selectedColor(0x39a2db)
          .key('CheckboxGroup001')
          .onChange((event: CheckboxGroupResult) => {
            console.info('CheckboxCustomDialog change is' + JSON.stringify(event))
          })
          .width(30)
          .height(30)
        Text('checkboxGroup1').fontSize(20)
      }

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
          .selectedColor(0x39a2db)
          .key('Checkbox001')
          .shape(CheckBoxShape.ROUNDED_SQUARE)
          .onChange((value: boolean) => {
            console.info('CheckboxCustomDialog change001 is' + value)
          })
          .width(30)
          .height(30)
        Text('Checkbox1').fontSize(20)
      }

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Checkbox({ name: 'checkbox3', group: 'checkboxGroup' })
          .selectedColor(0x39a2db)
          .key('Checkbox002')
          .shape(CheckBoxShape.ROUNDED_SQUARE)
          .onChange((value: boolean) => {
            console.info('CheckboxCustomDialog change002 is' + value)
          })
          .width(30)
          .height(30)
        Text('Checkbox2').fontSize(20)
      }

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Button('关闭弹窗')
          .onClick(() => {
            this.controller.close()
          }).backgroundColor(0x317aff)
      }
    }
    .width('100%')
  }
}

@Entry
@Component
struct CheckboxLevel0Example {
  pathStack: NavPathStack = new NavPathStack()
  @State toastInfo: string | undefined = ''
  @State calcIndex: number = -1
  @State index: number = -1
  private groupSize: objectSample = { width: 45, height: 45 }
  @State groupName_1: string | undefined = 'group1'
  @State groupName_2: string | undefined = 'group2'
  @State boxName_N1: string | undefined = 'box1'
  @State boxName_N2: string | undefined = 'box2'
  @State boxName_N3: string | undefined = 'box3'
  @State boxName_N4: string | undefined = 'box4'
  @State boxName_G1: string | undefined = 'group1'
  @State boxName_G2: string | undefined = 'group2'
  @State boxName_G3: string | undefined = 'group1'
  @State boxName_G4: string | undefined = 'group2'
  @State selectB1: boolean | undefined = false
  @State selectB3: boolean | undefined = false
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
  private sets: Array<objectSample1> = [
    {
      toastInfo: '1.两个group的名字一样：group1，四个box的group名字一样：group1（验证两个group是否可以控制四个多选框）',
      groupName_1: 'group1',
      groupName_2: 'group1',

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group1',
      boxName_G4: 'group1',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',

      select: true
    },
    {
      toastInfo: '本组参数单纯验证动态增删子节点，与第1组对比结果',
      groupName_1: 'group1',
      groupName_2: 'group1',

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group1',
      boxName_G4: 'group1',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',

      select: false
    },
    {
      toastInfo: '2.两个group的名字一样：group1，两个box的group名字：group1，两个box的group名字：group2',
      groupName_1: 'group1',
      groupName_2: 'group1',

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group2',
      boxName_G4: 'group2',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '3.两个group的名字一样：group1，四个box的group的名字都不是group1',
      groupName_1: 'group1',
      groupName_2: 'group1',

      boxName_G1: 'group11',
      boxName_G2: 'group11',
      boxName_G3: 'group21',
      boxName_G4: 'group21',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '4.两个group的名字不一样：group1,group2，四个box的group的名字都是group1',
      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group1',
      boxName_G4: 'group1',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '5.两个group的名字不一样：group1,group2，两个box的group的名字都是group1，两个box的group的名字都是group2', //问题：group2控制两个box不生效
      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group2',
      boxName_G4: 'group2',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '6.两个group的名字不一样：group1,group2，四个box的名字都不是group1,group2',
      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: 'group11',
      boxName_G2: 'group11',
      boxName_G3: 'group21',
      boxName_G4: 'group21',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '7.两个group的名字：undefined，两个box是group1, 两个box是group2 (验证group动态切换undefined走哪种设置)',
      groupName_1: undefined,
      groupName_2: undefined,

      boxName_G1: 'group1',
      boxName_G2: 'group1',
      boxName_G3: 'group2',
      boxName_G4: 'group2',

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },
    {
      toastInfo: '8.两个group的名字不一样：group1,group2，四个box的group是undefined(验证box动态切换undefined走哪种设置)',
      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: undefined,
      boxName_G2: undefined,
      boxName_G3: undefined,
      boxName_G4: undefined,

      boxName_N1: 'box1',
      boxName_N2: 'box2',
      boxName_N3: 'box3',
      boxName_N4: 'box4',
    },

  ]

  private setParam(): void {

    this.toastInfo = this.sets[this.index].toastInfo
    this.groupName_1 = this.sets[this.index].groupName_1
    this.groupName_2 = this.sets[this.index].groupName_2

    this.boxName_G1 = this.sets[this.index].boxName_G1
    this.boxName_G2 = this.sets[this.index].boxName_G2
    this.boxName_G3 = this.sets[this.index].boxName_G3
    this.boxName_G4 = this.sets[this.index].boxName_G4

    this.boxName_N1 = this.sets[this.index].boxName_N1
    this.boxName_N2 = this.sets[this.index].boxName_N2
    this.boxName_N3 = this.sets[this.index].boxName_N3
    this.boxName_N4 = this.sets[this.index].boxName_N4

    this.selectB1 = this.sets[this.index].select
    this.selectB3 = this.sets[this.index].select
  }

  build() {
    NavDestination() {
      Column() {

        Text('切换测试参数')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, top: 10 })

        Row({ space: 2 }) {

          Text(`${this.sets.length}` + '')
            .key('paramSets_key')
            .fontSize(9)
            .fontColor(0xCCCCCC)

          MyComponent({
            title: 'Test ++', func: () => {

              this.index++
              if (this.index == this.sets.length) {
                this.index = 0
              }
              this.setParam()
              this.calcIndex = this.index
            }
          })

          MyComponent({
            title: 'Test --', func: () => {

              this.index--
              if (this.index <= -1) {
                this.index = this.sets.length - 1
              }
              this.setParam()
              this.calcIndex = this.index
            }
          })
        }
        .margin(10)

        Text('子窗口弹窗Checkbox组件onChange事件触发').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row() {
          Button('弹出弹窗，内置Checkbox组件')
            .key('Button001')
            .onClick(() => {
              this.dialog.open()
            }).backgroundColor(0x317aff)
        }

        Text('切换direction属性Checkbox组件镜像效果').fontSize(9).fontColor(0xCCCCCC).width('100%')
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

        // 全选按钮
        Row({ space: 10 }) {
          //CheckboxGroup组件与通用属性结合考虑异常值
          CheckboxGroup({ group: this.groupName_1 })
            .key('CheckboxGroup1')
            .width(-1)
            .height(-1)
            .borderWidth(-1)
            .borderColor('fhujsfkjfjwsfjwj')
            .borderStyle(undefined)
            .borderRadius(-10)
            .size({ width: -100, height: undefined })
            .padding(-1)
            .border(undefined)
            .borderImage(undefined)
            .selectedColor('#007DFF')
            .margin({ start: LengthMetrics.vp(10) })
            .direction(this.dir[this.num])
          Text('1st: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)

          CheckboxGroup({ group: this.groupName_2 })
            .key('CheckboxGroup2')
            .size(this.groupSize)
            .selectedColor('#007DFF')
            .margin({ start: LengthMetrics.vp(10) })
            .direction(this.dir[this.num])
          Text('2nd: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项1
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          //Checkbox组件与通用属性结合考虑异常值
          Checkbox({ name: this.boxName_N1, group: this.boxName_G1 })
            .width(-1)
            .height(-1)
            .borderWidth(-1)
            .borderColor('fhujsfkjfjwsfjwj')
            .borderStyle(undefined)
            .borderRadius(-10)
            .size({ width: -100, height: undefined })
            .padding(-1)
            .border(undefined)
            .borderImage(undefined)
            .key('Checkbox1')
            .selectedColor('#007DFF')
            .select($$this.selectB1)
            .margin({ start: LengthMetrics.vp(10) })
            .direction(this.dir[this.num])
          Text('Checkbox1').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项2
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({ name: this.boxName_N2, group: this.boxName_G2 })
            .key('Checkbox2')
            .selectedColor('#007DFF')
            .margin({ start: LengthMetrics.vp(10) })
            .direction(this.dir[this.num])
          Text('Checkbox2').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项3
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({ name: this.boxName_N3, group: this.boxName_G3 })
            .key('Checkbox3')
            .selectedColor('#007DFF')
            .select($$this.selectB3)
            .margin({ start: LengthMetrics.vp(10) })
            .direction(this.dir[this.num])
          Text('Checkbox3').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项4
        if (this.index === 1) {
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: this.boxName_N4, group: this.boxName_G4 })
              .select(true)
              .key('Checkbox4')
              .selectedColor('#007DFF')
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
            Text('Checkbox4').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }
        } else {
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: this.boxName_N4, group: this.boxName_G4 })
              .key('Checkbox5')
              .selectedColor('#007DFF')
              .margin({ start: LengthMetrics.vp(10) })
              .direction(this.dir[this.num])
            Text('Checkbox5').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }
        }

        Text('配置信息显示: ' + '\n' + '' + this.toastInfo)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, top: 10, bottom: 5 })

      }.width('100%').height('100%')

    }
    .title('CheckboxLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}