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

import { FrameNode, NodeController, RadioModifier, ThemeControl, typeNode } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioLevel3Builder(name: string, param: Object) {
  RadioLevel3Example()
}

class MyModifier extends RadioModifier {
  public radioStyle1: Array<obj> = [
    {
      checked: true
    },
    {
      checked: false
    },
    {
      radioStyle1: {
        checkedBackgroundColor: 'rgb(0,0,255)'
      }
    },
    {
      radioStyle1: {
        checkedBackgroundColor: Color.Pink
      }
    },
    {
      radioStyle1: {
        uncheckedBorderColor: 'rgb(0,0,255)'
      }
    },
    {
      radioStyle1: {
        uncheckedBorderColor: Color.Pink
      }
    },
    {
      radioStyle1: {
        indicatorColor: 'rgb(0,0,255)'
      }
    },
    {
      radioStyle1: {
        indicatorColor: Color.Pink
      }
    },
  ]
  public num: number = 0

  applyNormalAttribute(instance: RadioModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.checked(this.radioStyle1[this.num].checked)
    this.radioStyle(this.radioStyle1[this.num].radioStyle1)
  }
}

interface radioStyle1 {
  checkedBackgroundColor?: ResourceColor,
  uncheckedBorderColor?: ResourceColor,
  indicatorColor?: ResourceColor
}

interface obj {
  checked?: boolean,
  radioStyle1?: radioStyle1
}

class MyNodeController extends NodeController {
  makeNode(uiContext: UIContext): FrameNode | null {
    let node = new FrameNode(uiContext);
    node.commonAttribute
      .borderColor(Color.Gray)
      .borderWidth(1)
    let col = typeNode.createNode(uiContext, 'Row');
    col.initialize({ space: 5 })
    node.appendChild(col);
    let radio = typeNode.createNode(uiContext, 'Radio');
    radio
      .initialize({ value: 'Radio1', group: 'radioGroup', indicatorType: RadioIndicatorType.DOT })
      .radioStyle({
        checkedBackgroundColor: Color.Pink,
        uncheckedBorderColor: $r('app.color.Color_blue'),
        indicatorColor: '#98FB98'
      })
      .key('Radio3')
      .height(30)
      .width(30)
      .padding(2)
      .direction(Direction.Rtl)
    ;
    let radio1 = typeNode.createNode(uiContext, 'Radio');
    radio1
      .initialize({ value: 'Radio2', group: 'radioGroup', indicatorType: RadioIndicatorType.TICK })
      .height(30)
      .width(30)
      .checked(true)
      .padding('5vp')
      .margin(12)
      .enabled(false)
      .key('Radio4')
    let radio2 = typeNode.createNode(uiContext, 'Radio');
    radio2
      .initialize({ value: 'Radio3', group: 'radioGroup', indicatorType: RadioIndicatorType.TICK })
      .height(30)
      .width(30)
      .padding('5vp')
      .margin(12)
      .key('Radio5')

    col.appendChild(radio);
    col.appendChild(radio1);
    col.appendChild(radio2);
    return node;
  }
}

@Entry
@Component
struct RadioLevel3Example {
  pathStack: NavPathStack = new NavPathStack()
  @State mod1: RadioModifier = new MyModifier()
    .checked(true)
    .radioStyle(undefined)
  private myNodeController: MyNodeController = new MyNodeController();
  @State mod2: RadioModifier = new RadioModifier()
    .height(30)
    .width(30)
    .padding($r('sys.float.arc_button_chamfer_radius'))
  @State isChecked: boolean | undefined = undefined
  @State hover: HoverEffect | undefined = undefined

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('Radio属性测试')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 10 }) {
          Radio({ value: 'Radio1', group: 'radioGroup' })
            .key('Radio1')
            .width('45%')
            .height(100)
            .attributeModifier((this.mod1 as MyModifier))
          Radio({ value: 'Radio2', group: 'radioGroup1' })
            .key('Radio2')
            .width('45%')
            .height(100)
            .checked((this.mod1 as MyModifier).radioStyle1[(this.mod1 as MyModifier).num].checked)
            .radioStyle((this.mod1 as MyModifier).radioStyle1[(this.mod1 as MyModifier).num].radioStyle1)
        }
        .height(100)

        Row({ space: 2 }) {
          Text(`${(this.mod1 as MyModifier).num + 1}/`)
          Text(`${(this.mod1 as MyModifier).radioStyle1.length}`)
            .key('RadioLevel12')
          Button() {
            Text('Index++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod1 as MyModifier).num++
            if ((this.mod1 as MyModifier).num > (this.mod1 as MyModifier).radioStyle1.length - 1) {
              (this.mod1 as MyModifier).num = 0
            }
            (this.mod1 as MyModifier).setGroup1()
          })

          Button() {
            Text('Index--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod1 as MyModifier).num--
            if ((this.mod1 as MyModifier).num < 0) {
              (this.mod1 as MyModifier).num = (this.mod1 as MyModifier).radioStyle1.length - 1
            }
            (this.mod1 as MyModifier).setGroup1()
          })
        }

        Column({ space: 5 }) {
          Divider()
          Text('FrameNode')
            .fontSize(15)
            .width('100%')
          NodeContainer(this.myNodeController);
          Divider()
          Text('Modifier')
            .fontSize(15)
            .width('100%')
          Radio({ value: 'Radio6', group: 'radioGroup3', indicatorType: RadioIndicatorType.TICK })
            .key('Radio6')
            .attributeModifier((this.mod2 as RadioModifier))
          Divider()
          Text('原生')
            .fontSize(15)
            .width('100%')
          Radio({ value: 'Radio3', group: 'radioGroup1', indicatorType: RadioIndicatorType.DOT })
            .key('Radio7')
            .radioStyle({
              checkedBackgroundColor: Color.Pink,
              uncheckedBorderColor: $r('app.color.Color_blue'),
              indicatorColor: '#98FB98'
            })
            .checked(true)
            .height(30)
            .width(30)
            .padding(2)
            .direction(Direction.Rtl)
          Radio({ value: 'Radio4', group: 'radioGroup1', indicatorType: RadioIndicatorType.TICK })
            .key('Radio8')
            .height(50)
            .width(50)
            .padding($r('sys.float.arc_button_chamfer_radius'))
            .margin(12)
            .checked(this.isChecked!!)
            .responseRegion({
              x: 0,
              y: 0,
              width: '60%',
              height: '100%'
            })
            .hoverEffect(this.hover)
          Text('' + this.isChecked).fontSize(15)
          Divider()
          Text('HoverEffect验证')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
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
        }
      }
      .width('100%')
    }
    .title('RadioLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}