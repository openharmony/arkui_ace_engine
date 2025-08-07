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

import { SymbolGlyphModifier } from '@kit.ArkUI';
import { MyComponent } from '../base/MyComponent'

@Builder
export function MenuTestLevel010Builder(name: string, param: Object) {
  MenuTestLevel010Example()
}

class MenuItemPrivateAttrOptions {
  public selected?: boolean | undefined
  public selectIcon?: boolean | ResourceStr | undefined
  public contentFont?: Font | undefined
  public contentFontColor?: ResourceColor | undefined
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Extend(MenuItem)
function menuItemStyle() {
  .borderWidth(1.0)
  .margin({ top: 1, bottom: 1 })
}

@Entry
@Component
struct MenuTestLevel010Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State selected: boolean = true
  @State selectedIcon: boolean | ResourceStr | SymbolGlyphModifier = true
  @State widthColumn: number = 200
  @State heightColumn: number = 40
  private MenuItemOptionsList: MenuItemOptions[] = [
  //1
    {},
    //2
    {
      startIcon: undefined,
      content: undefined,
      endIcon: undefined,
      labelInfo: undefined,
    },
    //3
    {
      startIcon: $r('app.media.app_icon'),
      content: '',
      endIcon: $r('app.media.app_icon'),
      labelInfo: '',
    },
    //4
    {
      startIcon: $r('app.string.EntryAbility_label'),
      content: 'content',
      endIcon: $r('app.string.EntryAbility_label'),
      labelInfo: 'label',
    },
    //5
    {
      startIcon: '/resource/media/svg_money.svg',
      content: 'content \n',
      endIcon: '/resource/media/png_arrow.png',
      labelInfo: 'label \n',

    },
    //6
    {
      startIcon: 'svg_number',
      content: 'content .'.repeat(3),
      endIcon: 'png_arrow.png',
      labelInfo: 'label .'.repeat(3),

    },
    //7
    {
      startIcon: $r('app.media.app_icon'),
      content: 'content .'.repeat(10),
      endIcon: $r('app.media.app_icon'),
      labelInfo: 'label .'.repeat(10),

    },
    //8
    {
      startIcon: $r('app.media.app_icon'),
      content: $r('app.string.EntryAbility_label'),
      endIcon: $r('app.media.app_icon'),
      labelInfo: $r('app.string.EntryAbility_desc'),
    },
    //9
    {
      startIcon: $r('app.media.app_icon'),
      content: $r('app.media.app_icon'),
      endIcon: $r('app.media.app_icon'),
      labelInfo: $r('app.media.app_icon'),
    },
    //10
    {
      startIcon: $r('app.media.app_icon'),
      endIcon: $r('app.media.app_icon'),
    },
    //11
    {
      startIcon: $r('app.media.app_icon'),
      endIcon: $r('app.media.app_icon'),
    },
    //12
    {
      startIcon: $r('app.media.app_icon'),
      endIcon: $r('app.media.app_icon'),
    },
    //13
    {
      startIcon: $r('app.media.app_icon'),
      content: '二级菜单',
      endIcon: $r('app.media.app_icon'),
      builder: (): void => this.SubMenuBuilder()
    },

    //HMSymbol设置startIcon和endIcon
    //14
    {
      symbolStartIcon: new SymbolGlyphModifier($r('sys.symbol.list_bullet_square_fill'))
        .fontSize('24vp')
        .fontColor([Color.Blue, Color.Red, Color.Green])
        .fontWeight(800)
        .effectStrategy(SymbolEffectStrategy.SCALE)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
        .symbolEffect(SymbolEffect.prototype, true),
      symbolEndIcon: new SymbolGlyphModifier($r('sys.symbol.arrowshape_up_fill'))
        .fontSize('30vp')
        .fontColor([Color.Red, Color.Green, Color.Blue])
        .fontWeight(300)
        .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_OPACITY)
        .symbolEffect(SymbolEffect.prototype, 2),


      content: 'Content',
      labelInfo: 'Ctrl',
      builder: (): void => this.SubMenuBuilder()
    },
  ]
  private MenuItemAttrList: MenuItemPrivateAttrOptions[] = [
  //1
    {},
    //2
    {
      selected: true,
      selectIcon: true,

      contentFont: undefined,
      contentFontColor: undefined,
    },
    //3
    {
      selected: false,
      selectIcon: true,
      contentFont: {
        size: -16,
        weight: 0, //预计字重走默认值
        style: FontStyle.Normal
      },
      contentFontColor: Color.Blue,

    },
    //4
    {
      selected: true,
      selectIcon: false,

      contentFont: {
        size: '0', //预计字体大小为0:
        weight: 300,
        family: '注册自定义字体',
        style: FontStyle.Italic
      },
      contentFontColor: '#ff0000ff',

    },
    //5
    {
      selected: true,
      selectIcon: $r('app.media.app_icon'),
      contentFont: {
        size: $r('app.float.float_40'),
        weight: 800,
        style: 3  //字体样式枚举异常值，预期走默认值
      },
      contentFontColor: 0x00ff00,
    },
    //6
    {
      selected: true,
      selectIcon: 'svg_album.svg',
      contentFont: {
        size: 20,
        weight: 1200, //超出范围的异常值，预计走默认值400
      },
      contentFontColor: $r('app.string.EntryAbility_label'),
    },
    //7
    {
      selected: true,
      // selectIcon: '/resource/media/svg_money.svg',
      contentFont: {
        size: 24,
        weight: '850', //预计走默认值400
        style: FontStyle.Italic
      },
      contentFontColor: $r('app.color.Color_red'),
    },
    //8
    {
      selected: true,
      selectIcon: $r('app.string.EntryAbility_label'),

      contentFont: {
        size: '100%', //预计字体大小为默认值
        weight: FontWeight.Lighter,
        style: undefined
      },
      contentFontColor: 'rgba(123.7,12.37,1.237, 1237)',
    },
    //9
    {
      selected: true,
      selectIcon: $r('app.media.app_icon'),

      contentFont: {
        size: 10,
        weight: FontWeight.Normal,
      },
      contentFontColor: 'color-blue',
    },
    //10
    {
      selected: true,
      selectIcon: undefined,

      contentFont: {
        size: $r('app.string.EntryAbility_label'), //预计字体大小为默认值,
        weight: FontWeight.Regular,
      },
    },
    //11
    {
      selected: true,
      // selectIcon: '/resource/media/gif.gif',

      contentFont: {
        size: 30,
        weight: FontWeight.Medium,
        family: undefined,
      },
    },
    //12
    {
      selected: true,
      // selectIcon: '/resource/media/mp4_video1.mp4',

      contentFont: {
        size: '30aa', //预计字体大小为默认值
        weight: FontWeight.Bold,
      },
    },
    //13
    {
      contentFont: {
        size: 20,
        weight: FontWeight.Bolder,
      },
    },
  ]
  private MenuItemGroupOptionsList: MenuItemGroupOptions[] = [
  //1
    {},
    //2
    {
      header: undefined,
      footer: undefined
    },
    //3
    {
      header: '标题',
      footer: '脚标'
    },
    //4
    {
      header: '标题 .'.repeat(10),
      footer: '脚标 .'.repeat(10)
    },
    //5
    {
      header: '标题 \n',
      footer: '脚标 \n'
    },
    //6
    {
      header: '标题 .'.repeat(0),
      footer: '脚标 .'.repeat(0)
    },
    //7
    {
      header: $r('app.string.EntryAbility_label'),
      footer: $r('app.string.EntryAbility_label'),
    },
    //8
    {
      header: $r('app.media.app_icon'), //预期空白占位：实际不占位
      footer: $r('app.media.app_icon'), //预期空白占位：实际不占位
    },
  ]

  //MenuItem的Builder
  @Builder
  MenuItemOptionsBuilder() {
    Menu() {
      MenuItem({
        startIcon: this.MenuItemOptionsList[this.index[0]].startIcon,
        content: this.MenuItemOptionsList[this.index[0]].content,
        endIcon: this.MenuItemOptionsList[this.index[0]].endIcon,
        labelInfo: this.MenuItemOptionsList[this.index[0]].labelInfo,
        builder: this.MenuItemOptionsList[this.index[0]].builder,
        symbolStartIcon: this.MenuItemOptionsList[this.index[0]].symbolStartIcon,
        symbolEndIcon: this.MenuItemOptionsList[this.index[0]].symbolEndIcon
      })
    }
  }

  //次级菜单
  @Builder
  SubMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  // MenuItem入参opt属性组合测试的绘制
  @Builder
  MenuItemParamBuilder() {
    Menu() {
      //设置不同MenuItem入参的组合
      MenuItem({ startIcon: $r('app.media.app_icon') })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), endIcon: $r('app.media.app_icon') })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), endIcon: $r('app.media.app_icon'), labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单', labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单', endIcon: $r('app.media.app_icon') })
        .menuItemStyle()
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单',
        endIcon: $r('app.media.app_icon'),
        labelInfo: 'label'
      })
        .menuItemStyle()

      MenuItem({})
        .menuItemStyle()
      MenuItem({ labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ endIcon: $r('app.media.app_icon') })
        .menuItemStyle()
      MenuItem({ endIcon: $r('app.media.app_icon'), labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ content: '菜单' })
        .menuItemStyle()
      MenuItem({ content: '菜单', labelInfo: 'label' })
        .menuItemStyle()
      MenuItem({ content: '菜单', endIcon: $r('app.media.app_icon') })
        .menuItemStyle()
      MenuItem({ content: '菜单', endIcon: $r('app.media.app_icon'), labelInfo: 'label' })
        .menuItemStyle()
    }
    .width(200)
  }

  //MenuItem设置CustomBuilder
  @Builder
  MenuItemCustomBuilder() {
    Menu() {
      MenuItem(this.ItemCustomBuilder())
        .borderWidth(1.0)
        .borderColor(Color.Green)
        .margin(2)
    }
    .borderWidth(1.0)
    .borderColor(Color.Red)
  }

  //MenuItem_CustomBuilder的Builder
  @Builder
  ItemCustomBuilder() {
    Row({ space: 5 }) {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
        .borderRadius(3)

      Text(`菜单选项`)
        .fontSize(16)
    }
    .margin(4)
    .width('240')
    .padding(3)
    .borderWidth(1.0)
    .borderColor(Color.Blue)
    .borderRadius(20)
    .backgroundColor(`#A6C2BE`)
  }

  //MenuItem的自有属性验证的builder
  @Builder
  MenuItemAttrBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .selected(this.MenuItemAttrList[this.index[1]].selected)
        .selectIcon(this.MenuItemAttrList[this.index[1]].selectIcon)

        .contentFont(this.MenuItemAttrList[this.index[1]].contentFont)
        .contentFontColor(this.MenuItemAttrList[this.index[1]].contentFontColor)
        .labelFont(this.MenuItemAttrList[this.index[1]].contentFont)
        .labelFontColor(this.MenuItemAttrList[this.index[1]].contentFontColor)
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  //MenuItem设置字体自有属性和Menu设置字体属性优先级的builder
  @Builder
  MenuItemFontPriorityBuilder() {
    Menu() {
      MenuItem({ content: `菜单选项`, labelInfo: 'Ctrl C' })
        .contentFont({ size: 10, weight: 300, style: FontStyle.Normal })
        .contentFontColor(Color.Blue)
        .labelFont({ size: 10, weight: 300, style: FontStyle.Normal })
        .labelFontColor(Color.Blue)
      MenuItem({ content: 'MenuItem', labelInfo: 'Ctrl V' })
    }
    .font({ size: 20, weight: 800, style: FontStyle.Italic })
    .fontColor(Color.Red)
  }

  //验证MenuItem的自有事件的builder
  @Builder
  MenuItemEventBuilder() {
    Menu() {
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        .selected(this.selected)
        .selectIcon(this.selectedIcon)
        .onChange((selected) => {
          console.info('---LCG---  menuItem select' + selected);
          this.selected = !this.selected
        })
    }
  }

  //验证MenuItemGroupOptions的builder
  @Builder
  MenuItemGroupOptionsBuilder() {
    Menu() {
      MenuItemGroup(this.MenuItemGroupOptionsList[this.index[2]]) {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItemGroup() {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }
  }

  //MenuItemGroup的入参设置builder
  @Builder
  MenuItemGroupCustomBuilder() {
    Menu() {
      MenuItemGroup({ header: this.MenuItemGroupHeaderBuilder(), footer: this.MenuItemGroupHeaderBuilder() }) {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }
  }

  //MenuItemGroup的header的builder
  @Builder
  MenuItemGroupHeaderBuilder() {
    Column() {
      Text('标题')
        .backgroundColor(Color.Orange)
    }
    .padding(10)
    .borderWidth(1.0)
    .borderRadius(20)
    .backgroundColor(Color.Green)
    .width(this.widthColumn)
    .height(this.heightColumn)
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text(`验证MenuItem入参: `)
            .paramTextStyle()
          Column({ space: 3 }) {
            Text(`MenuItem入参Options属性的组合测试: `)
              .paramTextStyle()
            Text('MenuItemParam')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemParamBuilder(), {
                placement: Placement.Bottom
              })

            Text(`MenuItem入参设置MenuItemOptions:`)
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[0] + 1}` + '/')
                .fontSize(9)
              Text(`${this.MenuItemOptionsList.length}`)
                .key('paramSets_key_0')
                .fontSize(9)
              MyComponent({
                title: 'Test0+', func: () => {
                  this.index[0]++
                  if (this.index[0] == this.MenuItemOptionsList.length) {
                    this.index[0] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test0-', func: () => {
                  this.index[0]--
                  if (this.index[0] <= -1) {
                    this.index[0] = this.MenuItemOptionsList.length - 1
                  }
                }
              })
            }

            Text('MenuItem: Options')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemOptionsBuilder(), {
                placement: Placement.Bottom
              })
          }
          .columnStyle()

          Column({ space: 3 }) {
            Text(`MenuItem设置CustomBuilder:`)
              .paramTextStyle()
            Text('MenuItem: CustomBuilder')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemCustomBuilder(), {
                placement: Placement.Bottom
              })
          }
          .columnStyle()

          Text(`验证MenuItem的自有属性: `)
            .paramTextStyle()
          Column({ space: 3 }) {
            Text(`切换MenuItem的自有属性参数：`)
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[1] + 1}` + ' / ')
                .fontSize(9)
              Text(`${this.MenuItemAttrList.length}`)
                .key('paramSets_key_1')
                .fontSize(9)
              MyComponent({
                title: 'Test1+', func: () => {
                  this.index[1]++
                  if (this.index[1] == this.MenuItemAttrList.length) {
                    this.index[1] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test1-', func: () => {
                  this.index[1]--
                  if (this.index[1] <= -1) {
                    this.index[1] = this.MenuItemAttrList.length - 1
                  }
                }
              })
            }

            Text('MenuItem: Attribute')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemAttrBuilder(), {
                placement: Placement.Bottom
              })

            Text(`验证MenuItem的字体属性和Menu字体属性优先级：私有高`)
              .paramTextStyle()
            Text(`MenuItem: fontAttr_menuFontAttr`)
              .key(`MenuItem: fontAttr_menuFontAttr`)
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemFontPriorityBuilder())
          }
          .columnStyle()

          Text(`验证MenuItem的自有事件: `)
            .paramTextStyle()
          Column({ space: 3 }) {
            Row({ space: 3 }) {
              MyComponent({
                title: `boolean`, func: () => {
                  this.selectedIcon = true
                }
              })
              MyComponent({
                title: `ResStr`, func: () => {
                  this.selectedIcon = $r('app.media.app_icon')
                }
              })
              MyComponent({
                title: `Symbol`, func: () => {
                  this.selectedIcon = new SymbolGlyphModifier($r('sys.symbol.checkmark_square_on_square_fill'))
                    .fontSize('30')
                    .fontColor([Color.Blue, Color.Orange])
                    .fontWeight(300)
                    .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
                    .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
                    .symbolEffect(SymbolEffect.prototype, 2)
                }
              })
            }

            Text('MenuItem: Event')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemEventBuilder(), {
                placement: Placement.Bottom
              })
          }
          .columnStyle()

          Text(`验证MenuItemGroup入参: `)
            .paramTextStyle()
          Column({ space: 3 }) {
            Text(`切换MenuItemGroupOptions参数: `)
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[2] + 1}` + ' / ')
                .fontSize(9)
              Text(`${this.MenuItemGroupOptionsList.length}`)
                .key('paramSets_key_2')
                .fontSize(9)
              MyComponent({
                title: 'Test2+', func: () => {
                  this.index[2]++
                  if (this.index[2] == this.MenuItemGroupOptionsList.length) {
                    this.index[2] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test2-', func: () => {
                  this.index[2]--
                  if (this.index[2] <= -1) {
                    this.index[2] = this.MenuItemGroupOptionsList.length - 1
                  }
                }
              })
            }

            Text('MenuItemGroup: Options')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemGroupOptionsBuilder(), {
                placement: Placement.Bottom
              })

            Text(`MenuItemGroup入参设置builder: width: ${this.widthColumn}, height: ${this.heightColumn}`)
              .paramTextStyle()
            Row({ space: 2 }) {
              MyComponent({
                title: 'width++', func: () => {
                  if (this.widthColumn >= 400) {
                    this.widthColumn = 400
                  } else {
                    this.widthColumn += 20
                  }
                }
              })
              MyComponent({
                title: 'width--', func: () => {
                  if (this.widthColumn <= 60) {
                    this.widthColumn = 60
                  } else {
                    this.widthColumn -= 20
                  }
                }
              })
              MyComponent({
                title: 'height++', func: () => {
                  if (this.heightColumn >= 800) {
                    this.heightColumn = 800
                  } else {
                    this.heightColumn += 40
                  }
                }
              })
              MyComponent({
                title: 'height--', func: () => {
                  if (this.heightColumn <= 40) {
                    this.heightColumn = 40
                  } else {
                    this.heightColumn -= 40
                  }
                }
              })
            }

            Text('MenuItemGroup: Builder')
              .backgroundColor(Color.Orange)
              .bindMenu(this.MenuItemGroupCustomBuilder(), {
                placement: Placement.Bottom
              })
          }
          .columnStyle()

        }
        .width('100%')
      }
      .padding(12)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .title('MenuTestLevel010')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}