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

import { CheckboxGroupModifier, CheckboxModifier, FrameNode, NodeController, ThemeControl, typeNode } from '@kit.ArkUI';
import { MyComponent } from '../base/MyComponent';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function CheckboxMultiTestLevel0Builder(name: string, param: Object) {
  checkboxMultiTestLevel0()
}


interface objectSample {
  width: number,
  height: number
}

interface objectSample1 {
  strokeColor: ResourceColor | undefined,
  size: number | string | undefined,
  strokeWidth: number | string | undefined
}

interface objectSample2 {
  toastInfo: string,
  selectColorG1: ResourceColor | undefined,
  unselectColorG1: ResourceColor | undefined,
  selectColorG2: ResourceColor | undefined,
  unselectColorG2: ResourceColor | undefined,
  selectColorB1: ResourceColor | undefined,
  selectColorB2: ResourceColor | undefined,
  unselectColorB1: ResourceColor | undefined,
  unselectColorB2: ResourceColor | undefined,
  group1_MarkStyle: objectSample1,
  group2_MarkStyle: objectSample1,
  box1_MarkStyle: objectSample1,
  box2_MarkStyle: objectSample1,
  shape?: CheckBoxShape | undefined | null,
  shape1?: CheckBoxShape | undefined | null
  // enableFocusEffect?:
}

class MyNodeController extends NodeController {
  makeNode(uiContext: UIContext): FrameNode | null {
    let node = new FrameNode(uiContext);
    node.commonAttribute
      .borderColor(Color.Gray)
      .borderWidth(1)
    let col = typeNode.createNode(uiContext, 'Column');
    col.initialize({ space: 5 })
    node.appendChild(col);

    let row1 = typeNode.createNode(uiContext, 'Row');
    row1.initialize({ space: 3 });
    col.appendChild(row1);
    let text1 = typeNode.createNode(uiContext, 'Text');
    text1.initialize('禁用Checkbox').fontSize(15);
    let checkbox = typeNode.createNode(uiContext, 'Checkbox');
    checkbox
      .initialize({ name: 'checkbox1', group: 'checkboxGroup2' })
      .key('checkbox000')
      .selectedColor(Color.Red)
      .unselectedColor($r('app.color.checkbox_unselected_color'))
      .mark({
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      })
      .shape(CheckBoxShape.ROUNDED_SQUARE)
      .height(40)
      .width(40)
      .padding(10)
      .enabled(false)
    ;
    row1.appendChild(text1);
    row1.appendChild(checkbox);

    let row2 = typeNode.createNode(uiContext, 'Row');
    row2.initialize({ space: 3 });
    col.appendChild(row2);
    let text2 = typeNode.createNode(uiContext, 'Text');
    text2.initialize('正常Checkbox').fontSize(15);
    let checkbox1 = typeNode.createNode(uiContext, 'Checkbox');
    checkbox1
      .initialize({ name: 'checkbox2', group: 'checkboxGroup2' })
      .key('checkbox001')
      .selectedColor(Color.Red)
      .unselectedColor($r('app.color.checkbox_unselected_color'))
      .mark({
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      })
      .shape(CheckBoxShape.CIRCLE)
      .height(40)
      .width(40)
      .padding(10);
    row2.appendChild(text2);
    row2.appendChild(checkbox1);

    let row3 = typeNode.createNode(uiContext, 'Row');
    row3.initialize({ space: 3 });
    col.appendChild(row3);
    let text3 = typeNode.createNode(uiContext, 'Text');
    text3.initialize('禁用CheckboxGroup').fontSize(15);
    let checkboxgroup = typeNode.createNode(uiContext, 'CheckboxGroup');
    checkboxgroup
      .initialize({ group: 'checkboxGroup1' })
      .key('checkbox002')
      .selectedColor(Color.Red)
      .unselectedColor($r('app.color.checkbox_unselected_color'))
      .mark({
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      })
      .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
      .height(40)
      .width(40)
      .padding(10)
      .enabled(false)
    row3.appendChild(text3);
    row3.appendChild(checkboxgroup);

    let row4 = typeNode.createNode(uiContext, 'Row');
    row4.initialize({ space: 3 });
    col.appendChild(row4);
    let text4 = typeNode.createNode(uiContext, 'Text');
    text4.initialize('正常CheckboxGroup').fontSize(15);
    let checkboxgroup1 = typeNode.createNode(uiContext, 'CheckboxGroup');
    checkboxgroup1
      .initialize({ group: 'checkboxGroup2' })
      .key('checkbox003')
      .selectedColor(Color.Red)
      .unselectedColor($r('app.color.checkbox_unselected_color'))
      .mark({
        strokeColor: Color.Black,
        size: 50,
        strokeWidth: 5
      })
      .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
      .height(40)
      .width(40)
      .padding(10)
    row4.appendChild(text4);
    row4.appendChild(checkboxgroup1);

    return node;
  }
}

@Entry
@Component
struct checkboxMultiTestLevel0 {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  indicatorBuilder(value: number) {
    Column() {
      Text(value > 99 ? '99+' : value.toString())
        .textAlign(TextAlign.Center)
        .fontSize(value > 99 ? '16vp' : '20vp')
        .fontWeight(FontWeight.Medium)
        .fontColor($r('sys.color.point_color_checked'))
    }
  }

  @State toastInfo: string = ' '
  @State test1: string = ' '
  @State test2: string = ' '
  @State test3: boolean | undefined = undefined
  @State test4: boolean | undefined = undefined
  @State test5: boolean | undefined = undefined
  @State test6: boolean | undefined = undefined
  @State calcIndex: number = -1
  private index: number = -1
  private lastIndex: number = 0
  private groupSize: objectSample = { width: 45, height: 45 }
  //group1控制box1,box2
  @State selectedColor_G1: ResourceColor | undefined = undefined
  @State unselectedColor_G1: ResourceColor | undefined = undefined
  @State selectedColor_B1: ResourceColor | undefined = undefined
  @State selectedColor_B2: ResourceColor | undefined = undefined
  @State unselectedColor_B1: ResourceColor | undefined = undefined
  @State unselectedColor_B2: ResourceColor | undefined = undefined
  //group2控制box3,box4
  @State selectedColor_G2: ResourceColor | undefined = undefined
  @State unselectedColor_G2: ResourceColor | undefined = undefined
  @State selectedColor_B3: ResourceColor | undefined = undefined
  @State selectedColor_B4: ResourceColor | undefined = undefined
  @State unselectedColor_B3: ResourceColor | undefined = undefined
  @State unselectedColor_B4: ResourceColor | undefined = undefined
  @State groupName_1: string = 'group1'
  @State groupName_2: string = 'group2'
  @State boxName_N1: string = 'box1'
  @State boxName_N2: string = 'box2'
  @State boxName_N3: string = 'box3'
  @State boxName_N4: string = 'box4'
  @State boxName_G1: string = 'group1'
  @State boxName_G2: string = 'group1'
  @State boxName_G3: string = 'group2'
  @State boxName_G4: string = 'group2'
  @State shape: CheckBoxShape | undefined | null = undefined
  @State shape1: CheckBoxShape | undefined | null = undefined
  //group的图标样式
  @State group1_MarkStyle: objectSample1 =
    { strokeColor: undefined, size: undefined, strokeWidth: undefined }
  @State group2_MarkStyle: objectSample1 =
    { strokeColor: undefined, size: undefined, strokeWidth: undefined }
  //box的图标样式
  @State box1_MarkStyle: objectSample1 =
    { strokeColor: undefined, size: undefined, strokeWidth: undefined }
  @State box3_MarkStyle: objectSample1 =
    { strokeColor: undefined, size: undefined, strokeWidth: undefined }
  @State selectB1: boolean = false
  @State selectB3: boolean = false
  private sets: Array<objectSample2> = [

    {
      toastInfo: '1.正常初始设置 ',
      //select: false,

      selectColorG1: '#ff0080ff',
      unselectColorG1: '#ff808080',

      selectColorG2: $r('app.color.checkbox_selected_color'),
      unselectColorG2: $r('app.color.checkbox_unselected_color'),

      selectColorB1: '#ff0080ff',
      selectColorB2: $r('app.color.checkbox_selected_color'),
      unselectColorB1: '#ff808080',
      unselectColorB2: $r('app.color.checkbox_unselected_color'),

      group1_MarkStyle: { strokeColor: 0xffffff, size: 30, strokeWidth: 4 },
      group2_MarkStyle: { strokeColor: $r('app.color.Color_white'), size: '30', strokeWidth: 2 },

      box1_MarkStyle: { strokeColor: 0xffffff, size: 20, strokeWidth: 4 },
      box2_MarkStyle: { strokeColor: $r('app.color.Color_white'), size: '20', strokeWidth: '2' },
      shape: undefined,
      shape1: CheckBoxShape.CIRCLE
    },
    {
      toastInfo: '2.group1(2): 粉色(橙色)选中态，灰（黑）色边框，黑色勾勾，负值大小、粗细走默认值；box1(3): 粉色（橙色）选中态，灰（黑）色边框，黑色勾勾，负值大小、粗细走默认值',
      //select: false,

      selectColorG1: 'rgb(255, 128, 255)',
      unselectColorG1: 'rgb(128, 128, 128)',

      selectColorG2: $r('app.color.Color_orange'),
      unselectColorG2: $r('app.color.Color_black'),

      selectColorB1: 'rgb(255, 128, 255)',
      selectColorB2: $r('app.color.Color_orange'),
      unselectColorB1: 'rgb(128, 128, 128)',
      unselectColorB2: $r('app.color.Color_black'),

      group1_MarkStyle: { strokeColor: 'rgb(0, 0, 0)', size: -45, strokeWidth: -4 },
      group2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '-45', strokeWidth: -2 },

      box1_MarkStyle: { strokeColor: 'rgb(0, 0, 0)', size: -30, strokeWidth: -4 },
      box2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '-30', strokeWidth: '-2' },
      shape: CheckBoxShape.CIRCLE,
      shape1: undefined
    },
    {
      toastInfo: '3.group1(2): 粉色选中态，灰（黑）色边框，黑色勾勾，大小为0不显示；box1(3): 粉色选中态，灰（黑）色边框，黑色勾勾，大小为0不显示',
      //select: false,

      selectColorG1: 'rgba(255, 128, 255, 0.70)',
      unselectColorG1: 'rgba(128, 128, 128, 0.70)',

      selectColorG2: $r('app.color.Color_pink'),
      unselectColorG2: $r('app.color.Color_black'),

      selectColorB1: 'rgba(255, 128, 255, 0.70)',
      selectColorB2: $r('app.color.Color_pink'),
      unselectColorB1: 'rgba(128, 128, 128, 0.70)',
      unselectColorB2: $r('app.color.Color_black'),

      group1_MarkStyle: { strokeColor: 'rgba(0, 0, 0, 1.0)', size: 0, strokeWidth: 2 },
      group2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '0', strokeWidth: 2 },

      box1_MarkStyle: { strokeColor: 'rgba(0, 0, 0, 1.0)', size: 0, strokeWidth: 2 },
      box2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '0', strokeWidth: 2 },
      shape: CheckBoxShape.ROUNDED_SQUARE,
      shape1: CheckBoxShape.CIRCLE
    },
    {
      toastInfo: '3.1 额外验证图标大小正常，粗细为0的显示',
      //select: false,

      selectColorG1: 'rgba(255, 128, 255, 0.70)',
      unselectColorG1: 'rgba(128, 128, 128, 0.70)',

      selectColorG2: $r('app.color.Color_pink'),
      unselectColorG2: $r('app.color.Color_black'),

      selectColorB1: 'rgba(255, 128, 255, 0.70)',
      selectColorB2: $r('app.color.Color_pink'),
      unselectColorB1: 'rgba(128, 128, 128, 0.70)',
      unselectColorB2: $r('app.color.Color_black'),

      group1_MarkStyle: { strokeColor: 'rgba(0, 0, 0, 1.0)', size: 30, strokeWidth: 0 },
      group2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '30', strokeWidth: '0' },

      box1_MarkStyle: { strokeColor: 'rgba(0, 0, 0, 1.0)', size: 20, strokeWidth: 0 },
      box2_MarkStyle: { strokeColor: $r('app.color.Color_black'), size: '20', strokeWidth: '0' },
      shape: 0,
      shape1: 1
    },
    {
      toastInfo: '4.group1(2): 粉（红）色选中态，灰（黑）色边框，黑色勾勾，大小4.5，宽度6（宽度>大小）；box1(3): 粉（红）色选中态，灰（黑）色边框，黑色勾勾，大小3.0，宽度4（宽度>大小） ',
      //select: false,

      selectColorG1: 0xFF80FF,
      unselectColorG1: 0x808080,

      selectColorG2: $r('app.color.Color_red'),
      unselectColorG2: $r('app.color.Color_black'),

      selectColorB1: 0xFF80FF,
      selectColorB2: $r('app.color.Color_red'),
      unselectColorB1: 0x808080,
      unselectColorB2: $r('app.color.Color_black'),

      group1_MarkStyle: { strokeColor: 0X000000, size: 4.5, strokeWidth: 6 },
      group2_MarkStyle: { strokeColor: $r('app.color.checkbox_mark_color'), size: '4.5', strokeWidth: '6' },

      box1_MarkStyle: { strokeColor: 0X000000, size: 3.0, strokeWidth: 4 },
      box2_MarkStyle: { strokeColor: $r('app.color.checkbox_mark_color'), size: '3.0', strokeWidth: '4' },

      shape: 1,
      shape1: 0
    },
    {
      toastInfo: '5.group1(2): 默认选中态，默认颜色边框，白色勾勾，对勾的大小、粗细大于选中框尺寸的设置；box1(3): 默认选中态，默认颜色边框，白色勾勾，对勾的大小、粗细大于选中框尺寸的设置',
      //select: false,

      selectColorG1: 'rgba(-126, 0.5, 51.2, 3.00)',
      unselectColorG1: 'rgba(-126, 0.5, 51.2, 3.00)',

      selectColorG2: undefined, //非法值走上一个颜色设置的值
      unselectColorG2: undefined,

      selectColorB1: 'rgba(-126, 0.5, 51.2, 3.00)',
      selectColorB2: undefined,
      unselectColorB1: 'rgba(-126, 0.5, 51.2, 3.00)',
      unselectColorB2: undefined,

      group1_MarkStyle: { strokeColor: '#ff000000', size: 450, strokeWidth: 50 },
      group2_MarkStyle: { strokeColor: $r('app.color.checkbox_mark_color'), size: '450', strokeWidth: '50' },
      box1_MarkStyle: { strokeColor: '#ff000000', size: 300, strokeWidth: 50 },
      box2_MarkStyle: { strokeColor: $r('app.color.checkbox_mark_color'), size: '300', strokeWidth: '50' },

      shape: 3,
      shape1: 0
    },
    {
      toastInfo: '6. 其他正常， group2和box3的对勾粗细设置“3px”的设置',
      //select: false,

      selectColorG1: undefined,
      unselectColorG1: undefined,

      selectColorG2: $r('app.color.Color_blue'),
      unselectColorG2: $r('app.color.Color_black'),

      selectColorB1: undefined,
      selectColorB2: $r('app.color.Color_blue'),
      unselectColorB1: undefined,
      unselectColorB2: $r('app.color.Color_black'),

      group1_MarkStyle: { strokeColor: undefined, size: undefined, strokeWidth: undefined },
      group2_MarkStyle: { strokeColor: undefined, size: '45px', strokeWidth: '2px' },
      box1_MarkStyle: { strokeColor: undefined, size: undefined, strokeWidth: undefined },
      box2_MarkStyle: { strokeColor: undefined, size: '30px', strokeWidth: '2px' },
      shape: null,
      shape1: CheckBoxShape.ROUNDED_SQUARE
    },
  ]

  private setParam(): void {

    this.toastInfo = this.sets[this.index].toastInfo
    this.selectedColor_G1 = this.sets[this.index].selectColorG1
    this.selectedColor_G2 = this.sets[this.index].selectColorG2

    this.unselectedColor_G1 = this.sets[this.index].unselectColorG1
    this.unselectedColor_G2 = this.sets[this.index].unselectColorG2


    this.selectedColor_B1 = this.sets[this.index].selectColorB1
    this.selectedColor_B2 = this.sets[this.index].selectColorB2
    this.selectedColor_B3 = this.sets[this.index].selectColorB1
    this.selectedColor_B4 = this.sets[this.index].selectColorB2

    this.unselectedColor_B1 = this.sets[this.index].unselectColorB1
    this.unselectedColor_B2 = this.sets[this.index].unselectColorB2
    this.unselectedColor_B3 = this.sets[this.index].unselectColorB1
    this.unselectedColor_B4 = this.sets[this.index].unselectColorB2

    this.group1_MarkStyle = this.sets[this.index].group1_MarkStyle
    this.group2_MarkStyle = this.sets[this.index].group2_MarkStyle

    this.box1_MarkStyle = this.sets[this.index].box1_MarkStyle
    this.box3_MarkStyle = this.sets[this.index].box2_MarkStyle
    this.shape = this.sets[this.index].shape
    this.shape1 = this.sets[this.index].shape1
  }

  private myNodeController: MyNodeController = new MyNodeController();
  @State mod1: CheckboxModifier = new CheckboxModifier()
    .selectedColor(Color.Red)
    .unselectedColor($r('app.color.checkbox_unselected_color'))
    .mark({ strokeColor: Color.Black, size: 50, strokeWidth: 5 })
    .shape(CheckBoxShape.CIRCLE)
    .height(40)
    .width(40)
    .padding(10)
  @State
  mod2: CheckboxGroupModifier = new CheckboxGroupModifier()
    .selectedColor(Color.Red)
    .unselectedColor($r('app.color.checkbox_unselected_color'))
    .mark({
      strokeColor: Color.Black,
      size: 50,
      strokeWidth: 5
    })
    .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
    .height(40)
    .width(40)
    .padding(10)

  build() {
    NavDestination() {
      Column({ space: 5 }) {

        Text('切换测试参数')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')

        Row({ space: 2 }) {

          Text(`${this.sets.length}` + '  ')
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
          Column() {
            Row({ space: 10 }) {
              CheckboxGroup({ group: this.groupName_1 })
                .checkboxShape(this.shape1)
                .key('CheckboxGroup1')
                .size(this.groupSize)
                .selectedColor(this.selectedColor_G1)
                .unselectedColor(this.unselectedColor_G1)
                .mark(this.group1_MarkStyle)
                .onChange((itemName2: CheckboxGroupResult) => {
                  this.test1 = itemName2.name[0] + ' ' + itemName2.name[1] + ' ' + itemName2.status
                })
              Text('1st: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
            }

            Text(this.test1).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }

          Column() {
            Row({ space: 10 }) {
              CheckboxGroup({ group: this.groupName_2 })
                .checkboxShape(this.shape1)
                .key('CheckboxGroup2')
                .size(this.groupSize)
                .selectedColor(this.selectedColor_G2)
                .unselectedColor(this.unselectedColor_G2)
                .mark(this.group2_MarkStyle)
                .onChange((itemName2: CheckboxGroupResult) => {
                  this.test2 = itemName2.name[0] + ' ' + itemName2.name[1] + ' ' + itemName2.status
                })
              Text('2nd: Select All').fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
            }

            Text(this.test2).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
          }
        }

        // 选项1
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({
            name: this.boxName_N1, group: this.boxName_G1, indicatorBuilder: () => {
              this.indicatorBuilder(9)
            }
          })
            .key('Checkbox1')
            .selectedColor(this.selectedColor_B1)
            .unselectedColor(this.unselectedColor_B1)
            .mark(this.box1_MarkStyle)
            .select($$this.selectB1)
            .shape(this.shape)
            .onChange((value1: boolean) => {
              this.test3 = value1
            })
          Text('Checkbox1 select: ' + this.test3).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项2
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({ name: this.boxName_N2, group: this.boxName_G2 })
            .key('Checkbox2')
            .shape(this.shape)
            .selectedColor(this.selectedColor_B2)
            .unselectedColor(this.unselectedColor_B2)
            .onChange((value2: boolean) => {
              this.test4 = value2
            })
          Text('Checkbox2 select: ' + this.test4).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项3
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({
            name: this.boxName_N3, group: this.boxName_G3, indicatorBuilder: () => {
              this.indicatorBuilder(100)
            }
          })
            .key('Checkbox3')
            .shape(this.shape)
            .selectedColor(this.selectedColor_B3)
            .unselectedColor(this.unselectedColor_B3)
            .mark(this.box3_MarkStyle)
            .select($$this.selectB3)
            .onChange((value3: boolean) => {
              this.test5 = value3
            })
          Text('Checkbox3 select: ' + this.test5).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        // 选项4
        Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
          Checkbox({ name: this.boxName_N4, group: this.boxName_G4 })
            .key('Checkbox4')
            .shape(this.shape)
            .selectedColor(this.selectedColor_B4)
            .unselectedColor(this.unselectedColor_B4)
            .onChange((value4: boolean) => {
              this.test6 = value4
            })
          Text('Checkbox4 select: ' + this.test6).fontSize(14).lineHeight(20).fontColor('#182431').fontWeight(500)
        }

        Text('配置信息显示: ' + ' \n ' +
          '    ' + this.toastInfo)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')

        Divider()
        Text('FrameNode').fontSize(15).width('100%')
        NodeContainer(this.myNodeController);

        Text('Modifier').fontSize(15).width('100%')
        Row({ space: 3 }) {
          Text('Checkbox').fontSize(15)
          Checkbox({ name: 'checkbox5', group: 'checkboxGroup3' })
            .key('checkbox004')
            .attributeModifier((this.mod1 as CheckboxModifier))
        }

        Row({ space: 3 }) {
          Text('CheckboxGroup').fontSize(15)
          CheckboxGroup({ group: 'checkboxGroup3' })
            .key('checkbox005')
            .attributeModifier((this.mod2 as CheckboxGroupModifier))
        }

        Divider()

      }.width('100%').height('100%')
    }
    .title('CheckboxMultiTestLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}