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
/*
* MenuItem组件主题场景测试用例
* 测试设计：
* 1、应用整体通过theme主题设置
* 2、withTheme内设置设置Menu
* 3、Menu
 */

import { CustomTheme, CustomColors, ThemeControl } from '@kit.ArkUI';
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions, symbolStartIcon, startIcon, endIcon, symbolEndIcon, SubMenuBuilder} from '../../customBuilder/MenuBuilder'

// theme换肤主题色
class SpecialColors implements CustomColors {
  fontPrimary = '#ff9353c1';
  backgroundPrimary = '#D2CAB3';
  brand = '#b34a4333'; //品牌色
}

// WithTheme
class GreenColors implements CustomColors {
  fontPrimary = '#ff049404';
  fontEmphasize = '#FF00541F';
  fontOnPrimary = '#FFFFFFFF';
  compBackgroundTertiary = '#1111FF11';
  backgroundEmphasize = '#FF00541F';
  compEmphasizeSecondary = '#3322FF22';
}

class RedColors implements CustomColors {
  fontPrimary = '#fff32b3c';
  fontEmphasize = '#FFD53032';
  fontOnPrimary = '#FFFFFFFF';
  compBackgroundTertiary = '#44FF2222';
  backgroundEmphasize = '#FFD00000';
  compEmphasizeSecondary = '#33FF1111';
}

class PageCustomTheme implements CustomTheme {
  colors?: CustomColors;
  constructor(colors: CustomColors) {
    this.colors = colors;
  }
}

// menuItem的字体颜色
class MenuItemAttrOpt {
  contentFontColor?: ResourceColor
  labelFontColor?: ResourceColor
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuTestLevel1_6 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State show_1: boolean = false

  // withTheme参数
  static readonly themeCount = 3;
  themeNames: string[] = ['System', 'Custom (green)', 'Custom (red)'];
  themeArray: (CustomTheme | undefined)[] = [
    undefined, // System
    new PageCustomTheme(new GreenColors()),
    new PageCustomTheme(new RedColors())
  ]
  @State themeIndex: number = 0;

  // 菜单builder的opt
  @State menuAttrOpt: MenuAttrOptions = {
    submenuMode: 0,
  }
  // 菜单选项的字体颜色
  @State menuItemAttrOpt: MenuItemAttrOpt = {

  }
  // 菜单的builder
  @Builder
  MenuItemBuilder() {
    Column({space: 5}){
      MenuItem({ startIcon: startIcon, content: '菜单选项' })
        .enabled(false)
        .contentFontColor(this.menuItemAttrOpt.contentFontColor)
        .labelFontColor(this.menuItemAttrOpt.labelFontColor)
      MenuItem({
        symbolStartIcon: symbolStartIcon,
        labelInfo: 'label',
        symbolEndIcon: symbolEndIcon
      })
        .contentFontColor(this.menuItemAttrOpt.contentFontColor)
        .labelFontColor(this.menuItemAttrOpt.labelFontColor)

      MenuItemGroup({header: '标题', footer: '脚标' }) {
        MenuItem({
          content: '菜单选项1',
          endIcon: endIcon,
        })
          .enabled(false)
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          labelInfo: 'label',
        })
      }

      MenuItem({
        content: '菜单选项2',
        labelInfo: 'label',
        symbolStartIcon: symbolStartIcon,
        symbolEndIcon: symbolEndIcon
      })
        .contentFontColor(this.menuItemAttrOpt.contentFontColor)
        .labelFontColor(this.menuItemAttrOpt.labelFontColor)
    }
  }

  @Builder
  MenuItemBuilder_WithTheme() {
    Column({space: 5}){
      WithTheme({theme: this.themeArray[this.themeIndex]}) {
        MenuItem({ startIcon: startIcon, content: '菜单选项' })
          .enabled(false)
          .contentFontColor(this.menuItemAttrOpt.contentFontColor)
          .labelFontColor(this.menuItemAttrOpt.labelFontColor)
      }
      WithTheme({theme: this.themeArray[this.themeIndex]}) {
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          labelInfo: 'label',
          symbolEndIcon: symbolEndIcon
        })
          .contentFontColor(this.menuItemAttrOpt.contentFontColor)
          .labelFontColor(this.menuItemAttrOpt.labelFontColor)
      }
      WithTheme({theme: this.themeArray[this.themeIndex]}) {
        MenuItemGroup({header: '标题', footer: '脚标' }) {
          MenuItem({
            content: '菜单选项1',
            endIcon: endIcon,
          })
            .enabled(false)
          MenuItem({
            symbolStartIcon: symbolStartIcon,
            labelInfo: 'label',
          })
        }
      }
      WithTheme({theme: this.themeArray[this.themeIndex]}) {
        MenuItem({
          content: '菜单选项2',
          labelInfo: 'label',
          symbolStartIcon: symbolStartIcon,
          symbolEndIcon: symbolEndIcon
        })
          .contentFontColor(this.menuItemAttrOpt.contentFontColor)
          .labelFontColor(this.menuItemAttrOpt.labelFontColor)
      }
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`MenuItem组件主题场景的功能实现`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换WithTheme主题配色: ${this.themeNames[this.themeIndex]}`)
            .paramTextStyle()
          MyComponent({title: '切换withTheme配色', func: () => {
            this.themeIndex = (this.themeIndex + 1) % MenuTestLevel1_6.themeCount;
          }})

          Text(`切换MenuItem组件字体颜色`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'UN', func: ()=> {
              this.menuItemAttrOpt.labelFontColor = undefined
              this.menuItemAttrOpt.contentFontColor = undefined

            }})
            MyComponent({title: '蓝色字体', func: ()=> {
              this.menuItemAttrOpt.labelFontColor =Color.Blue
              this.menuItemAttrOpt.contentFontColor = '#ff5252ff'
            }})
          }
        }
        .columnStyle()

        Column({space: 5}){
          Text(`WithTheme下的MenuItem组件`)
            .paramTextStyle()
          Text('bindMenu菜单-主题')
            .componentTextStyle()
            .bindMenu(this.MenuItemBuilder_WithTheme())
          Text('预览图菜单-主题')
            .componentTextStyle()
            .bindContextMenu(this.show!!, this.MenuItemBuilder_WithTheme(), {
              preview: MenuPreviewMode.IMAGE
            })
            .onClick( () => {
              if(!this.show) {
                this.show = true
              }
            })
        }
        .columnStyle()

        Column({space: 5}){
          Text(`非WithTheme下的Menu组件`)
            .paramTextStyle()
          Text('bindMenu菜单-非主题')
            .componentTextStyle()
            .bindMenu(this.MenuItemBuilder())
          Text('预览图菜单-非主题')
            .componentTextStyle()
            .bindContextMenu(this.show_1!!, this.MenuItemBuilder(), {
              preview: MenuPreviewMode.IMAGE
            })
            .onClick( () => {
              if(!this.show_1) {
                this.show_1 = true
              }
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

  onPageShow(): void {
    // theme换肤, 创建实例
    const SpecialColorsTheme = new PageCustomTheme(new SpecialColors());
    ThemeControl.setDefaultTheme(SpecialColorsTheme);
  }

  onPageHide(): void {
    ThemeControl.setDefaultTheme(undefined);
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}