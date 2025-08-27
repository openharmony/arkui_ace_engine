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
export function CheckboxLevel2Builder(name: string, param: Object) {
  CheckboxLevel2Example()
}

ThemeControl.setDefaultTheme(undefined);

interface objectSample {
  width: number,
  height: number
}

class IsChecked {
  public checkedName: string = ''
  public isChecked: boolean = false

  constructor(checkedName: string, isChecked: boolean) {
    this.isChecked = isChecked
    this.checkedName = checkedName
  }
}

interface objectSample1 {
  toastInfo: string,
  groupName_1: string,
  groupName_2: string,
  boxName_G1: string,
  boxName_G2: string,
  boxName_N1: string,
  boxName_N2: string,

}

@Entry
@Component
struct CheckboxLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  @State toastInfo: string = ''
  @State calcIndex: number = -1
  private index: number = -1
  private groupSize: objectSample = { width: 45, height: 45 }
  @State groupName_1: string = 'group1'
  @State groupName_2: string = 'group1'
  @State boxName_N1: string = 'box1'
  @State boxName_N2: string = 'box2'
  @State boxName_G1: string = 'group1'
  @State boxName_G2: string = 'group2'
  private sets: Array<objectSample1> = [
    {
      toastInfo: '1. 全部',

      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: 'group1',
      boxName_G2: 'group1',

      boxName_N1: 'box1',
      boxName_N2: 'box2',

    },
    {
      toastInfo: '2. 部分',

      groupName_1: 'group1',
      groupName_2: 'group2',

      boxName_G1: 'group1',
      boxName_G2: 'group2',

      boxName_N1: 'box1',
      boxName_N2: 'box2',

    },
    {
      toastInfo: '3. 没有',

      groupName_1: 'group1.0',
      groupName_2: 'group2',

      boxName_G1: 'group2',
      boxName_G2: 'group2',

      boxName_N1: 'box1',
      boxName_N2: 'box2',

    },
  ]
  @State isSelectAll: boolean = false
  @State isSelectAll1: boolean | undefined = undefined
  @State isSelect1: boolean | undefined = undefined
  @State selectArray: Array<IsChecked> = []
  @State checkboxArray: Array<string> = ['checkbox1', 'checkbox2', 'checkbox3', 'checkbox4', 'checkbox5']
  @State checkedBoxArray: Array<string> = []
  @State arrayIndex: number = 5
  private scrollerForList: Scroller = new Scroller()

  private setParam(): void {

    this.toastInfo = this.sets[this.index].toastInfo

    this.groupName_1 = this.sets[this.index].groupName_1
    this.groupName_2 = this.sets[this.index].groupName_2

    this.boxName_G1 = this.sets[this.index].boxName_G1
    this.boxName_G2 = this.sets[this.index].boxName_G2

    this.boxName_N1 = this.sets[this.index].boxName_N1
    this.boxName_N2 = this.sets[this.index].boxName_N2

  }

  @State hover: HoverEffect | undefined = undefined

  build() {
    NavDestination() {
      Scroll(this.scrollerForList) {
        Column({ space: 10 }) {
          Text('切换测试参数')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')

          Row({ space: 10 }) {

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

          // 全选按钮
          Row({ space: 10 }) {

            CheckboxGroup({ group: this.groupName_1 })
              .key('CheckboxGroup1')
              .size(this.groupSize)
              .selectedColor('#007DFF')
              .selectAll(this.isSelectAll1!!)
              .onChange((itemName: CheckboxGroupResult) => {
                console.info('---Lcg---   Checkbox group 1 content： ' + JSON.stringify(itemName))
              })
            Column({ space: 3 }) {
              Text('1st: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
              Text('' + this.isSelectAll1).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
            }

            CheckboxGroup({ group: this.groupName_2 })
              .key('CheckboxGroup2')
              .size(this.groupSize)
              .selectedColor('#007DFF')
              .onChange((itemName: CheckboxGroupResult) => {
                console.info('---Lcg---   Checkbox group 2 content： ' + JSON.stringify(itemName))
              })
            Text('2nd: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)

          }

          // 选项1
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: this.boxName_N1, group: this.boxName_G1 })
              .key('Checkbox1')
              .selectedColor('#007DFF')
              .onChange((value: boolean) => {
                console.info('---Lcg---   Checkbox1 change is: ' + value)
              })
              .select(this.isSelect1!!)
            Column({ space: 3 }) {
              Text('Checkbox1').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
              Text('' + this.isSelect1).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
            }
          }

          // 选项2
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: this.boxName_N2, group: this.boxName_G2 })
              .key('Checkbox2')
              .selectedColor('#007DFF')
              .onChange((value: boolean) => {
                console.info('---Lcg---   Checkbox2 change is:' + value)
              })
              .hoverEffect(this.hover)
            Text('Checkbox2').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }

          Text('配置信息显示: ' + '\n' + '' + this.toastInfo)
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')

          Divider()
          Text('Array Checkbox增删联动CheckboxGroup状态')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')

          Row({ space: 10 }) {
            MyComponent({
              title: 'splice', func: () => {
                this.checkedBoxArray.forEach((item: string) => {
                  if (this.checkboxArray.indexOf(item) != -1) {
                    this.checkboxArray.splice(this.checkboxArray.indexOf(item), 1)
                  }
                })
              }
            })
            MyComponent({
              title: 'push', func: () => {
                this.arrayIndex++
                this.checkboxArray.push('checkbox' + this.arrayIndex)
              }
            })
          }

          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            CheckboxGroup({ group: 'checkboxGroup' })
              .key('checkboxGroup01')
              .selectAll($$this.isSelectAll)
              .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
              .selectedColor('#007DFF')
              .onChange((itemName: CheckboxGroupResult) => {
                this.checkedBoxArray = itemName.name
                console.info('---Lcg--- CheckboxGroup content' + JSON.stringify(itemName))
              })
            Text('Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }

          ForEach(this.checkboxArray, (item: string) => {
            Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
              Checkbox({ name: item, group: 'checkboxGroup' })
                .key(item)
                .selectedColor('#007DFF')
                .shape(CheckBoxShape.ROUNDED_SQUARE)
                .onChange((value: boolean) => {
                  const index = this.selectArray.findIndex(obj => obj.checkedName === item);
                  if (index !== -1) {
                    this.selectArray[index].isChecked = value
                  } else {
                    this.selectArray.push(new IsChecked(item, value))
                  }
                })
              Text(item).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
            }
          }, (item: string, index: number) => item + index)
          CheckboxGroup({ group: 'checkboxGroup4' })
            .responseRegion({
              x: 0,
              y: 0,
              width: '60%',
              height: '100%'
            })
            .size({ width: 60, height: 60 })
            .padding(10)
            .key('CheckboxGroup0001')
            .hoverEffect(this.hover)

          Text('HoverEffect验证').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 5 }) {
            Text('None')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.hover = HoverEffect.None
              })

            Text('Scale')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.hover = HoverEffect.Scale
              })
            Text('auto')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.hover = HoverEffect.Auto
              })
          }
        }.width('100%').height('100%')
      }.scrollBar(BarState.Off)
    }
    .title('CheckboxLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}