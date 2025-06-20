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

import { CheckboxGroupModifier, CheckboxModifier } from '@ohos.arkui.modifier';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function CheckboxLevel3Builder(name: string, param: Object) {
  CheckboxLevel3Example()
}

ThemeControl.setDefaultTheme(undefined);

class MyModifier extends CheckboxModifier {
  public num: number = 0
  public checkboxStyle: Array<obj> = [
    {
      select: true
    },
    {
      select: false
    },
    {
      unselectedColor: Color.Red
    },
    {
      unselectedColor: '#ff182431'
    },
    {
      selectedColor: Color.Red,
      checkboxShape: CheckBoxShape.CIRCLE
    },
    {
      selectedColor: '#ff182431',
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      },
      checkboxShape: 0
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 10,
        strokeWidth: 50
      },
      checkboxShape: 1
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 100,
        strokeWidth: 5
      },
      checkboxShape: 2
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: '80vp',
        strokeWidth: 60
      },
      checkboxShape: -1
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: '120vp',
        strokeWidth: '5vp'
      },
      checkboxShape: CheckBoxShape.CIRCLE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 60,
        strokeWidth: '15vp'
      },
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 120,
        strokeWidth: '100vp'
      },
      checkboxShape: CheckBoxShape.CIRCLE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 16,
        strokeWidth: 100
      },
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
  ]

  applyNormalAttribute(instance: CheckboxModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.selectedColor(this.checkboxStyle[this.num].selectedColor)
    this.select(this.checkboxStyle[this.num].select)
    this.unselectedColor(this.checkboxStyle[this.num].unselectedColor)
    this.mark(this.checkboxStyle[this.num].mark)
  }
}

class MyModifier1 extends CheckboxGroupModifier {
  public index: number = 0
  public checkboxGroupStyle: Array<obj1> = [
    {
      selectAll: true
    },
    {
      selectAll: false
    },
    {
      unselectedColor: Color.Red
    },
    {
      unselectedColor: '#ff182431'
    },
    {
      selectedColor: Color.Red,
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
    {
      selectedColor: '#ff182431',
      checkboxShape: CheckBoxShape.CIRCLE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      },
      checkboxShape: 0
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 10,
        strokeWidth: 50
      },
      checkboxShape: 1
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 100,
        strokeWidth: 5
      },
      checkboxShape: 2
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: '80vp',
        strokeWidth: 60
      },
      checkboxShape: -1
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: '120vp',
        strokeWidth: '5vp'
      },
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 60,
        strokeWidth: '15vp'
      },
      checkboxShape: CheckBoxShape.CIRCLE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 120,
        strokeWidth: '100vp'
      },
      checkboxShape: CheckBoxShape.ROUNDED_SQUARE
    },
    {
      mark: {
        strokeColor: Color.Black,
        size: 16,
        strokeWidth: 100
      },
      checkboxShape: CheckBoxShape.CIRCLE
    }
  ]

  applyNormalAttribute(instance: CheckboxGroupModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup2(): void {
    this.selectedColor(this.checkboxGroupStyle[this.index].selectedColor)
    this.selectAll(this.checkboxGroupStyle[this.index].selectAll)
    this.unselectedColor(this.checkboxGroupStyle[this.index].unselectedColor)
    this.mark(this.checkboxGroupStyle[this.index].mark)
    this.checkboxShape(this.checkboxGroupStyle[this.index].checkboxShape)
  }
}

interface mark {
  strokeColor?: ResourceColor
  size?: number | string
  strokeWidth?: number | string
}

interface obj {
  selectedColor?: ResourceColor,
  select?: boolean,
  unselectedColor?: ResourceColor,
  mark?: mark,
  checkboxShape?: CheckBoxShape
}

interface obj1 {
  selectedColor?: ResourceColor,
  selectAll?: boolean,
  unselectedColor?: ResourceColor,
  mark?: mark,
  checkboxShape?: CheckBoxShape
}

@Entry
@Component
struct CheckboxLevel3Example {
  pathStack: NavPathStack = new NavPathStack()
  @State mod1: CheckboxModifier = new MyModifier()
    .select(true)
    .mark(undefined)
    .selectedColor(undefined)
    .unselectedColor(undefined)
  @State mod2: CheckboxGroupModifier = new MyModifier1()
    .selectAll(true)
    .mark(undefined)
    .selectedColor(undefined)
    .unselectedColor(undefined)
    .checkboxShape(undefined)

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('Checkbox与CheckboxGroup属性联动测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Text('CheckboxGroup组件原生接口与Checkbox联动测试，左边红色背景为CheckboxGroup')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 5 }) {
          CheckboxGroup({ group: 'checkboxGroup' })
            .key('checkboxGroup0')
            .width('30%')
            .height(100)
            .attributeModifier((this.mod2 as MyModifier1))
            .backgroundColor(Color.Red)
          Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
            .key('Checkbox1')
            .width('30%')
            .height(100)
            .attributeModifier((this.mod1 as MyModifier))
          Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
            .key('Checkbox2')
            .width('30%')
            .height(100)
            .selectedColor((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].selectedColor)
            .mark((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].mark)
            .select((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].select)
            .unselectedColor((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].unselectedColor)
        }.height(100)

        Text('CheckboxGroup组件modifier接口与Checkbox联动测试，左边红色背景为CheckboxGroup')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 5 }) {
          CheckboxGroup({ group: 'checkboxGroup1' })
            .key('checkboxGroup1')
            .width('30%')
            .height(100)
            .backgroundColor(Color.Red)
            .selectedColor((this.mod2 as MyModifier1)
              .checkboxGroupStyle[(this.mod2 as MyModifier1).index].selectedColor)
            .mark((this.mod2 as MyModifier1)
              .checkboxGroupStyle[(this.mod2 as MyModifier1).index].mark)
            .selectAll((this.mod2 as MyModifier1)
              .checkboxGroupStyle[(this.mod2 as MyModifier1).index].selectAll)
            .unselectedColor((this.mod2 as MyModifier1)
              .checkboxGroupStyle[(this.mod2 as MyModifier1).index].unselectedColor)
            .checkboxShape((this.mod2 as MyModifier1)
              .checkboxGroupStyle[(this.mod2 as MyModifier1).index].checkboxShape)
          Checkbox({ name: 'checkbox3', group: 'checkboxGroup1' })
            .key('Checkbox3')
            .width('30%')
            .height(100)
            .attributeModifier((this.mod1 as MyModifier))
          Checkbox({ name: 'checkbox4', group: 'checkboxGroup1' })
            .key('Checkbox4')
            .width('30%')
            .height(100)
            .selectedColor((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].selectedColor)
            .mark((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].mark)
            .select((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].select)
            .unselectedColor((this.mod1 as MyModifier)
              .checkboxStyle[(this.mod1 as MyModifier).num].unselectedColor)
        }.height(100)

        Text('切换Checkbox参数测试，对比左右Checkbox组件效果').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Text(`${(this.mod1 as MyModifier).num + 1}/`)
          Text(`${(this.mod1 as MyModifier).checkboxStyle.length}`)
            .key('CheckboxTestLevel11')
          Button() {
            Text('Num++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod2 as MyModifier1).index++
            if ((this.mod2 as MyModifier1).index > (this.mod2 as MyModifier1)
              .checkboxGroupStyle.length - 1) {
              (this.mod2 as MyModifier1).index = 0
            }
            (this.mod2 as MyModifier1).setGroup2()
          })

          Button() {
            Text('Index--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod2 as MyModifier1).index--
            if ((this.mod2 as MyModifier1).index < 0) {
              (this.mod2 as MyModifier1).index = (this.mod2 as MyModifier1)
                .checkboxGroupStyle.length - 1
            }
            (this.mod2 as MyModifier1).setGroup2()
          })
        }
      }.width('100%')
    }
    .title('CheckboxLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}