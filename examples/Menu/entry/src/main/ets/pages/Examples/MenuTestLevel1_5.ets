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
* Menu组件主题场景测试用例
* 测试设计：
* 1、应用整体通过theme主题设置
* 2、withTheme内设置设置Menu
* 3、Menu
 */

import { CustomTheme, CustomColors, ThemeControl } from '@kit.ArkUI';
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions, symbolStartIcon } from '../../customBuilder/MenuBuilder'

class SpecialColors implements CustomColors {
  fontPrimary = '#ff9353c1'
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
struct MenuTestLevel1_5 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State show_1: boolean = false

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

  // 图文菜单
  // bindMenu菜单
  @Builder
  MenuBuilder() {
    MenuBuilder({
      menuAttrOptions: this.menuAttrOpt
    })
  }
  @Builder
  MenuBuilder_WithTheme() {
    WithTheme({theme: this.themeArray[this.themeIndex]}){
      MenuBuilder({
        menuAttrOptions: this.menuAttrOpt
      })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`Menu组件主题场景的功能实现`).paramTextStyle()
        Column({space: 5}){
          Text(`切换WithTheme主题配色: ${this.themeNames[this.themeIndex]}`).paramTextStyle()
          MyComponent({title: '切换withTheme配色', func: () => {
            this.themeIndex = (this.themeIndex + 1) % MenuTestLevel1_5.themeCount;
          }})

          Text(`切换Menu组件字体颜色`).paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'UN', func: ()=> {
              this.menuAttrOpt.fontColor = undefined
            }})
            MyComponent({title: '蓝色字体', func: ()=> {
              this.menuAttrOpt.fontColor = Color.Blue
            }})
          }

          Text(`切换次级菜单类型: ${this.menuAttrOpt.submenuMode}`).paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'SIDE', func: () => {
              this.menuAttrOpt.submenuMode = 0
            }})
            MyComponent({title: 'EMBEDDED', func: () => {
              this.menuAttrOpt.submenuMode = 1
            }})
            MyComponent({title: 'STACK', func: () => {
              this.menuAttrOpt.submenuMode = 2
            }})
          }
        }
        .columnStyle()
        Column({space: 5}){
          Text(`WithTheme下的Menu组件`).paramTextStyle()
          Text('图文菜单')
            .componentTextStyle()
            .bindMenu([
              //1 action验证
              {
                value: 'Menu ',
                action: () => {
                  console.info('---LCG---  Menu1 Action On')
                }
              },
              //2
              {
                value: 'Menu ',
                action: () => {
                },
                enabled: false
              },
              //3 value和icon组合验证: 不同字符串
              {
                value: 'Menu '.repeat(1),
                icon: $r('app.media.app_icon'),
                action: () => {
                }
              },
              //4
              {
                value: 'Menu '.repeat(1),
                symbolIcon: symbolStartIcon,
                action: () => {
                }
              },
            ])

          Text('bindMenu菜单-主题')
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_WithTheme())

          Text('预览图菜单-主题')
            .componentTextStyle()
            .bindContextMenu(this.show!!, this.MenuBuilder_WithTheme(), {
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
          Text(`非WithTheme下的Menu组件`).paramTextStyle()
          Text('图文菜单-非主题')
            .componentTextStyle()
            .bindMenu([
              //1 action验证
              {
                value: 'Menu ',
                action: () => {
                  console.info('---LCG---  Menu1 Action On')
                }
              },
              //2
              {
                value: 'Menu ',
                action: () => {
                },
                enabled: false
              },
              //3 value和icon组合验证: 不同字符串
              {
                value: 'Menu '.repeat(1),
                icon: $r('app.media.app_icon'),
                action: () => {
                }
              },
              //4
              {
                value: 'Menu '.repeat(1),
                symbolIcon: symbolStartIcon,
                action: () => {
                }
              },
            ])

          Text('bindMenu菜单-非主题')
            .componentTextStyle()
            .bindMenu(this.MenuBuilder())

          Text('预览图菜单-非主题')
            .componentTextStyle()
            .bindContextMenu(this.show_1!!, this.MenuBuilder(), {
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