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


import { FrameNode, NodeController, ThemeControl, ToggleModifier, typeNode } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ToggleMultiTestLevel2Builder(name: string, param: Object) {
  toggleMultiTestLevel2()
}


class MyModifier extends ToggleModifier {
  public toggleStyle: Array<obj> = [
    {
      selectedColor: Color.Green
    },
    {
      selectedColor: 'rgb(0,0,255)'
    },
    {
      selectedColor: $r('app.color.selectedColor')
    },
    {
      switchPointColor: 'blue'
    },
    {
      switchPointColor: 'rgb(0,0,255)'
    },
    {
      switchPointColor:
      $r('app.color.switchPointColor')
    },
    {
      switchStyle: {
        pointRadius: -1,
        unselectedColor: Color.Red,
        pointColor: Color.Green,
        trackBorderRadius: -1
      }
    },
    {
      switchStyle: {
        pointRadius: 0,
        unselectedColor: $r('app.color.yellow'),
        pointColor:
        $r('app.string.module_desc'),
        trackBorderRadius: 0
      }
    },
    {
      switchStyle: {
        pointRadius: 4,
        unselectedColor: '#FF1493',
        pointColor: 'hdjsdjjkdjuwjd',
        trackBorderRadius: 4
      }
    },
    {
      switchStyle: {
        pointRadius: undefined,
        unselectedColor: undefined,
        pointColor: undefined,
        trackBorderRadius: undefined
      }
    },
    {
      switchStyle: {
        pointRadius: 8,
        unselectedColor: 'rgb( 255,105,180)',
        pointColor: 'rgba(255,105,180,111)',
        trackBorderRadius: 6
      }
    },
    {
      switchStyle: {
        pointRadius: 16,
        unselectedColor: 'rgb( 255,105,180)',
        pointColor: 'rgba(255,105,180,111)',
        trackBorderRadius: 3
      }
    }
  ]
  public num: number = 0

  applyNormalAttribute(instance: ToggleModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.selectedColor(this.toggleStyle[this.num].selectedColor)
    this.switchPointColor(this.toggleStyle[this.num].switchPointColor)
    this.switchStyle(this.toggleStyle[this.num].switchStyle)
  }
}

interface obj {
  selectedColor?: ResourceColor,
  switchPointColor?: ResourceColor,
  switchStyle?: SwitchStyle,
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
    let toggle = typeNode.createNode(uiContext, 'Toggle', {
      type: ToggleType.Switch,
      isOn: true
    });
    toggle
      .attribute
      .key('Toggle3')
      .padding(2)
      .margin(5)
      .width(50)
      .height(25)
      .direction(Direction.Rtl)
      .borderWidth(1)
      .selectedColor(Color.Blue)
      .switchPointColor('#FFA500')
      .switchStyle({
        pointRadius: 5,
        trackBorderRadius: 10,
        pointColor: '#D2B48C',
        unselectedColor: Color.Pink
      })
    let toggle1 = typeNode.createNode(uiContext, 'Toggle', {
      type: ToggleType.Button,
    });
    toggle1
      .attribute
      .key('Toggle4')
      .padding(2)
      .margin(5)
      .width(50)
      .height(25)
      .borderWidth(1)
      .selectedColor(Color.Blue)
    let toggle2 = typeNode.createNode(uiContext, 'Toggle', {
      type: ToggleType.Checkbox,
    });
    toggle2
      .attribute
      .key('Toggle5')
      .padding(2)
      .margin(5)
      .width(50)
      .height(25)
      .borderWidth(1)
      .selectedColor(Color.Blue)

    col.appendChild(toggle);
    col.appendChild(toggle1);
    col.appendChild(toggle2);

    return node;
  }
}

@Entry
@Component
struct toggleMultiTestLevel2 {
  pathStack: NavPathStack = new NavPathStack()
  @State mod0: ToggleModifier = new MyModifier()
    .selectedColor(Color.Green)
    .switchPointColor(undefined)
    .switchStyle(undefined)
  private myNodeController: MyNodeController = new MyNodeController();
  @State mod1: ToggleModifier = new ToggleModifier()
    .padding(2)
    .margin(5)
    .width(50)
    .height(25)
    .direction(Direction.Rtl)
    .borderWidth(1)
    .selectedColor(Color.Blue)
    .switchPointColor('#FFA500')
    .switchStyle({
      pointRadius: 5,
      trackBorderRadius: 10,
      pointColor: '#D2B48C',
      unselectedColor: Color.Pink
    })
  @State mod2: ToggleModifier = new ToggleModifier()
    .padding(2)
    .margin(5)
    .width(50)
    .height(25)
    .direction(Direction.Rtl)
    .borderWidth(1)
    .selectedColor(Color.Blue)
  @State mod3: ToggleModifier = new ToggleModifier()
    .padding(2)
    .margin(5)
    .width(50)
    .height(25)
    .direction(Direction.Rtl)
    .borderWidth(1)
    .selectedColor(Color.Blue)
  @State ison1: boolean | undefined = undefined
  @State ison2: boolean | undefined = undefined
  @State ison3: boolean | undefined = undefined

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('ToggleStyle属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 10 }) {
          Toggle({ type: ToggleType.Switch, isOn: true })
            .key('Toggle1')
            .width('45%')
            .height(100)
            .attributeModifier((this.mod0 as MyModifier))
          Toggle({ type: ToggleType.Switch, isOn: true })
            .key('Toggle2')
            .width('45%')
            .height(100)
            .selectedColor((this.mod0 as MyModifier).toggleStyle[(this.mod0 as MyModifier).num].selectedColor)
            .switchPointColor((this.mod0 as MyModifier).toggleStyle[(this.mod0 as MyModifier).num].switchPointColor)
            .switchStyle((this.mod0 as MyModifier).toggleStyle[(this.mod0 as MyModifier).num].switchStyle)
        }.height(100)

        Row({ space: 2 }) {
          Text(`${(this.mod0 as MyModifier).num + 1}/`)
          Text(`${(this.mod0 as MyModifier).toggleStyle.length}`)
            .key('ToggleLevel12')
          Button() {
            Text('Index++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod0 as MyModifier).num++
            if ((this.mod0 as MyModifier).num > (this.mod0 as MyModifier).toggleStyle.length - 1) {
              (this.mod0 as MyModifier).num = 0
            }
            (this.mod0 as MyModifier).setGroup1()
          })

          Button() {
            Text('Index--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod0 as MyModifier).num--
            if ((this.mod0 as MyModifier).num < 0) {
              (this.mod0 as MyModifier).num = (this.mod0 as MyModifier).toggleStyle.length - 1
            }
            (this.mod0 as MyModifier).setGroup1()
          })
        }

        Column({ space: 5 }) {
          Divider()
          Text('FrameNode').fontSize(15).width('100%')
          NodeContainer(this.myNodeController);
          Divider()
          Text('Modifier').fontSize(15).width('100%')
          Row({ space: 5 }) {
            Toggle({
              type: ToggleType.Switch,
              isOn: true
            })
              .key('Toggle6')
              .attributeModifier((this.mod1 as ToggleModifier))
            Toggle({
              type: ToggleType.Button,
            })
              .key('Toggle7')
              .attributeModifier((this.mod2 as ToggleModifier))
            Toggle({
              type: ToggleType.Checkbox,
            })
              .key('Toggle8')
              .attributeModifier((this.mod3 as ToggleModifier))
          }

          Divider()
          Text('原生').fontSize(15).width('100%')
          Row({ space: 5 }) {
            Column({ space: 3 }) {
              Toggle({
                type: ToggleType.Switch,
                isOn: this.ison1!!
              })
                .key('Toggle9')
                .padding(2)
                .margin(5)
                .width(50)
                .height(25)
                .direction(Direction.Rtl)
                .borderWidth(1)
                .selectedColor(Color.Blue)
                .switchPointColor('#FFA500')
                .switchStyle({
                  pointRadius: 5,
                  trackBorderRadius: 10,
                  pointColor: '#D2B48C',
                  unselectedColor: Color.Pink
                })
              Text('' + this.ison1).fontSize(15)
            }

            Column({ space: 3 }) {
              Toggle({
                type: ToggleType.Button,
                isOn: this.ison2!!
              })
                .key('Toggle10')
                .padding(2)
                .margin(5)
                .width(50)
                .height(25)
                .direction(Direction.Rtl)
                .borderWidth(1)
                .selectedColor(Color.Blue)
              Text('' + this.ison2).fontSize(15)
            }

            Column({ space: 3 }) {
              Toggle({
                type: ToggleType.Checkbox,
                isOn: this.ison3!!
              })
                .key('Toggle11')
                .padding(2)
                .margin(5)
                .width(50)
                .height(25)
                .direction(Direction.Rtl)
                .borderWidth(1)
                .selectedColor(Color.Blue)
              Text('' + this.ison3).fontSize(15)
            }
          }

          Divider()
        }.width('100%')
      }.width('100%')
    }
    .title('ToggleMultiTestLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}