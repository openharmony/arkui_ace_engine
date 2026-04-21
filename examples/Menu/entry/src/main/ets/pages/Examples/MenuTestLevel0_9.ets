/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// xxx.ets
/*
* 验证Menu: font | fontColor | radius
 */
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'


@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .borderWidth(1.0)
  .backgroundColor(Color.Orange)
  .textAlign(TextAlign.Center)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_8 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  private menuFontStyleList: Font[] = [
    //1
    {},
    //2
    {
      size: undefined,
      weight: undefined,
      family: undefined,
      style: undefined
    },
    //3
    {
      size: -16,
      weight: 0, //预计字重走默认值
      family: 'HarmonyOS Sans',
      style: FontStyle.Normal
    },
    //4
    {
      size: '0', //预计字体大小为0:
      weight: 300,
      family: '注册自定义字体',
      style: FontStyle.Italic
    },
    //5
    {
      size: $r('app.float.float_40'),
      weight: 800,
      style: 3  //字体样式枚举异常值，预期走默认值
    },
    //6
    {
      size: 20,
      weight: 1200, //超出范围的异常值，预计走默认值400
    },
    //7
    {
      size: 24,
      weight: '850', //预计走默认值400
      style: FontStyle.Italic
    },
    //8
    {
      size: '100%', //预计字体大小为默认值
      weight: FontWeight.Lighter,
      style: undefined
    },
    //9
    {
      size: 10,
      weight: FontWeight.Normal,
    },
    //10
    {
      size: $r('app.string.EntryAbility_label'), //预计字体大小为默认值,
      weight: FontWeight.Regular,
    },
    //11
    {
      size: 30,
      weight: FontWeight.Medium,
      family: undefined,
    },
    //12
    {
      size: '30aa', //预计字体大小为默认值
      weight: FontWeight.Bold,
    },
    //13
    {
      size: 20,
      weight: FontWeight.Bolder,
    },

  ]
  private menuFontColorList: (ResourceColor | undefined)[] = [
  //1
    ,
    //2
    Color.Blue,
    //3
    '#ff0000ff',
    //4
    undefined,
    //5
    0x00ff00,
    //6
    $r('app.string.EntryAbility_label'),
    //7
    $r('app.color.Color_red'),
    //8
    'rgba(123.7,12.37,1.237, 1237)',
    //9
    'color-blue',
  ]
  private menuRadiusList: (Dimension | BorderRadiuses | undefined)[] = [
  //1
    ,
    //2
    5,
    //3
    undefined,
    //4
    '20vp',
    //5
    '20px',
    //6
    '20%', //预计走半径默认值：实际按照百分比绘制？
    //7
    $r('app.float.float_5'),
    //8
    $r('app.string.EntryAbility_label'),
    //9
    60, //设置比短边一半大的圆角，预计走默认值
    //10
    {},
    //11
    {
      topLeft: 10,
      topRight: 25,
      bottomLeft: 25,
      bottomRight: 10
    },
    //12
    { topLeft: undefined, bottomLeft: '', bottomRight: 60 }
  ]

  //Menu验证Item字体样式的Builder
  @Builder
  MenuItemFontBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C', builder: (): void => this.SubMenu() })
        .contentFont({ size: 10, weight: 600 })
        .contentFontColor(Color.Red)
        .labelFont({ size: 10, weight: 600 })
        .labelFontColor(Color.Red)
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })

      MenuItemGroup({ header: 'title' }) {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
          .contentFont({ size: 10, weight: 600 })
          .contentFontColor(Color.Red)
          .labelFont({ size: 10, weight: 600 })
          .labelFontColor(Color.Red)
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }
    .backgroundColor(Color.Orange)
    .borderWidth(1.0)
    .font({ size: 20, weight: 300 })
    .fontColor(Color.Green)
  }

  //MenuItem的子菜单
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C', })
        .contentFont({ size: 15, weight: 500 })
        .contentFontColor(Color.Blue)
        .labelFont({ size: 15, weight: 500 })
        .labelFontColor(Color.Blue)
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  //Menu验证通用属性圆角和自有属性圆角优先级的builder
  @Builder
  MenuRadiusBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
    }
    .backgroundColor(Color.Orange)
    .radius(20)
    .borderRadius(0)
  }

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  // 验证Menu组件的font属性
  @Builder
  MenuBuilder_font() {
    MenuBuilder({
      menuAttrOptions: {
        submenuMode: this.menuAttrOption.submenuMode,
        font: this.menuFontStyleList[this.index[0]],
        fontColor: Color.Black
      }})
  }
  // 验证Menu组件的fontColor属性
  @Builder
  MenuBuilder_fontColor() {
    MenuBuilder({
      menuAttrOptions: {
        submenuMode: this.menuAttrOption.submenuMode,
        font: { size: 20, weight: FontWeight.Bolder },
        fontColor: this.menuFontColorList[this.index[1]]
      }})
  }
  // 验证Menu组件的radius属性
  @Builder
  MenuBuilder_radius() {
    MenuBuilder({
      menuAttrOptions: {
        submenuMode: this.menuAttrOption.submenuMode,
        border: {width: 1.0, color: Color.Black},
        radius: this.menuRadiusList[this.index[2]]
      }})
  }
  // 验证Menu组件和子组件的文本样式设置优先级
  @Builder
  MenuBuilder_fontPriority() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .contentFont({ size: 10, weight: 600 })
        .contentFontColor(Color.Red)
        .labelFont({ size: 10, weight: 600 })
        .labelFontColor(Color.Red)
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup({ header: 'title' }) {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
          .contentFont({ size: 10, weight: 600 })
          .contentFontColor(Color.Red)
          .labelFont({ size: 10, weight: 600 })
          .labelFontColor(Color.Red)
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }
    .font({ size: 20, weight: 300 })
    .fontColor(Color.Orange)
  }
  // 验证Menu组件的radius和borderRadius设置优先级
  @Builder
  MenuBuilder_radiusPriority() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .enabled(false)
    }
    .borderRadius(5)
    .radius(20)
    .borderRadius(5)
    .borderWidth(1.0)  //设置边框宽度验证边框圆角
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证Menu组件属性: font/ fontColor/ radius`).paramTextStyle()
        Column({space: 5}){
          Text(`切换次级菜单类型`).paramTextStyle()
          Select([
            { value:'SIDE' },
            { value:'EMBEDDED' },
            { value:'STACK' },
          ])
            .value('SIDE')
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'SIDE':
                  this.menuAttrOption.submenuMode = 0
                  break;
                case 'EMBEDDED':
                  this.menuAttrOption.submenuMode = 1
                  break;
                case 'STACK':
                  this.menuAttrOption.submenuMode = 2
                  break;
              }
            })
            .key('select_subMenuMode')
        }
        .columnStyle()

        Column({ space: 5}) {
          Text(`切换font参数`).paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ').fontSize(9)
            Text(`${this.menuFontStyleList.length}`).key('paramSets_key_0').fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.menuFontStyleList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.menuFontStyleList.length - 1
                }
              }
            })
          }
          Text(`Menu: font`).componentTextStyle()
            .bindMenu(this.MenuBuilder_font())

          Text(`切换fontColor参数`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuFontColorList.length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({
              title: 'Test1+', func: () => {
                this.index[1]++
                if (this.index[1] == this.menuFontColorList.length) {
                  this.index[1] = 0
                }
              }
            })
            MyComponent({
              title: 'Test1-', func: () => {
                this.index[1]--
                if (this.index[1] <= -1) {
                  this.index[1] = this.menuFontColorList.length - 1
                }
              }
            })
          }
          Text(`Menu: fontColor`).componentTextStyle()
            .bindMenu(this.MenuBuilder_fontColor())

          Text(`切换radius参数`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[2] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuRadiusList.length}`)
              .key('paramSets_key_2')
              .fontSize(9)
            MyComponent({
              title: 'Test2+', func: () => {
                this.index[2]++
                if (this.index[2] == this.menuRadiusList.length) {
                  this.index[2] = 0
                }
              }
            })
            MyComponent({
              title: 'Test2-', func: () => {
                this.index[2]--
                if (this.index[2] <= -1) {
                  this.index[2] = this.menuRadiusList.length - 1
                }
              }
            })
          }
          Text(`Menu: radius`).componentTextStyle()
            .bindMenu(this.MenuBuilder_radius())
        }
        .columnStyle()

        Text(`验证Menu和MenuItem设置文本样式的绘制优先级: MenuItem优先级高`)
          .paramTextStyle()
        Column() {
          Text(`Menu和menuItem的文本样式优先级`)
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder_fontPriority(), ResponseType.LongPress)
        }
        .columnStyle()

        Text(`验证Menu:通用属性radius和自有属性radius的优先级`)
          .paramTextStyle()
        Column() {
          Text(`Menu: radius设置优先级`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_radiusPriority())
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}
