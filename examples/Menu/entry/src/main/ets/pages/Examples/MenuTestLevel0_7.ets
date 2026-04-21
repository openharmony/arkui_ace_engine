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
* 验证bindContextMenu：previewAnimationOptions (手工用例测试)
* 验证bindMenu和bindContextMenu: backgroundColor | backgroundBlurStyle
 */
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions, CustomMenuBuilder } from '../../customBuilder/MenuBuilder'

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
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_7 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  //Menu组件的属性
  @State menuAttrOption: MenuAttrOptions = {
  }
  //菜单和次级菜单
  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }
  // 自定义菜单组件
  @Builder
  CustomMenuBuilder() {
    CustomMenuBuilder()
  }

  // 菜单背景色和背景模糊材质
  private menuBlurStyleList: ContextMenuOptions[] = [
  //1
    {},
    //2
    {
      backgroundColor: undefined,
      backgroundBlurStyle: undefined,
    },
    //3
    {
      backgroundColor: Color.Orange,
      backgroundBlurStyle: BlurStyle.Thin,
    },
    //4
    {
      backgroundColor: 'rgba(1237,123.7,12.37,1.237)', //str异常值，预期走默认值
      backgroundBlurStyle: BlurStyle.Regular,
    },
    //5
    {
      backgroundColor: 0xffa500,
      backgroundBlurStyle: BlurStyle.Thick,
    },
    //6
    {
      backgroundColor: $r('app.string.EntryAbility_label'), //res异常值，预期走默认值
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
    },
    //7
    {
      backgroundColor: '#ffffa500',
      backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR,
    },
    //8
    {
      backgroundColor: $r('app.color.Color_orange'),
      backgroundBlurStyle: BlurStyle.BACKGROUND_THICK,
    },
    //9
    {
      backgroundColor: Color.Transparent,
      backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK,
    },
    //10
    {
      backgroundColor: '#8981F7',
      backgroundBlurStyle: BlurStyle.NONE,
    },
    //11
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN,
    },
    //12
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: BlurStyle.COMPONENT_THIN,
    },
    //13
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR,
    },
    //14
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
    },
    //15
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
    },
    //16
    {
      backgroundColor: Color.Blue,
      backgroundBlurStyle: 13, //枚举异常值，预期走默认值
    },
  ]

  // 菜单opt
  @State contextMenuOption: ContextMenuOptions = {
  }

  // 菜单模糊效果组合测试opt
  @State contextMenuBlurOption: ContextMenuOptions = {
  }

  // 菜单动效
  @State contextMenuTransition: ContextMenuOptions = {}

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证菜单控制的backgroundColor/backgroundBlurStyle属性`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换backgroundColor参数`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuBlurStyleList.slice(0, 10).length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({
              title: 'Test1+', func: () => {
                this.index[1]++
                if (this.index[1] == this.menuBlurStyleList.slice(0, 10).length) {
                  this.index[1] = 0
                }
              }
            })
            MyComponent({
              title: 'Test1-', func: () => {
                this.index[1]--
                if (this.index[1] <= -1) {
                  this.index[1] = this.menuBlurStyleList.slice(0, 10).length - 1
                }
              }
            })
          }
          Button('bindMenu: bgColor')
            .backgroundColor(Color.Orange)
            .bindMenu(this.MenuBuilder(), {
              placement: Placement.Bottom,
              backgroundColor: this.menuBlurStyleList.slice(0, 10)[this.index[1]].backgroundColor,
              backgroundBlurStyle: BlurStyle.NONE,
            })

          Text(`切换backgroundBlurStyle参数`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[2] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuBlurStyleList.length}`)
              .key('paramSets_key_2')
              .fontSize(9)
            MyComponent({
              title: 'Test2+', func: () => {
                this.index[2]++
                if (this.index[2] == this.menuBlurStyleList.length) {
                  this.index[2] = 0
                }
              }
            })
            MyComponent({
              title: 'Test2-', func: () => {
                this.index[2]--
                if (this.index[2] <= -1) {
                  this.index[2] = this.menuBlurStyleList.length - 1
                }
              }
            })
          }
          Button('bindContextMenu: bgBlurStyle')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.CustomMenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Bottom,
              backgroundColor: Color.Pink,
              backgroundBlurStyle: this.menuBlurStyleList[this.index[2]].backgroundBlurStyle,
            })
        }
        .columnStyle()

        // 商分注释api14
        Text(`验证菜单options的模糊材质属性`)
          .paramTextStyle()
        Column({space:5}){
          Text(`切换次级菜单类型: ${this.menuAttrOption.submenuMode}`)
            .paramTextStyle()
          Select([
            { value:'SIDE' },
            { value:'EMBEDDED' },
            { value:'STACK' },
          ])
            .selectStyle()
            .value('默认值')
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

          Text(`切换菜单动效duration`)
            .paramTextStyle()
          Select([
            { value:'默认动效' },
            { value:'较长动效' },
          ])
            .selectStyle()
            .value('默认值')
            .onSelect((idx, value: string) => {
              switch (value) {
                case '默认动效':
                  this.contextMenuTransition.transition = undefined
                  break;
                case '较长动效':
                  this.contextMenuTransition.transition =
                    TransitionEffect.SLIDE.animation({ duration: 2000, curve: Curve.Ease })
                  break;
              }
            })
            .key('select_menuTransition')
        }
        .columnStyle()
        Column({space: 5}){
          Text(`切换bgBlurStyleOptions属性`)
            .paramTextStyle()
          Select([
            { value:'不设置bgBlurOptions' },
            // 设置inactiveColor为orange
            { value:'不设置bgBlurOpt.policy' },
            { value:'设置bgBlurOpt.policy为follows' },
            { value:'设置bgBlurOpt.policy为active' },
            { value:'设置bgBlurOpt.policy为UN' },
            { value:'设置bgBlurOpt.policy为inactive' },
            { value:'设置bgBlurOpt.policy为7' },
            // policy设置follow类型
            { value:'不设置bgBlurOpt.inActColor' },
            { value:'colorMode为SYSTEM/inActColor为UN' },
            { value:'scale为0.5/inActColor为str正常' },
            { value:'设置bgBlurOpt.inActColor为num正常' },
            { value:'设置bgBlurOpt.inActColor为res正常' },
            { value:'adaColor为DEFAULT/inActColor为str异常' },
            { value:'adaColor为AVERAGE/inActColor为res异常' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置bgBlurOptions':
                  this.contextMenuOption = {}
                  break;
                case '不设置bgBlurOpt.policy':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    inactiveColor: Color.Orange
                  }
                  break;
                case '设置bgBlurOpt.policy为follows':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Orange
                  }
                  break;
                case '设置bgBlurOpt.policy为active':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: Color.Orange
                  }
                  break;
                case '设置bgBlurOpt.policy为inactive':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: Color.Orange
                  }
                  break;
                case '设置bgBlurOpt.policy为UN':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: undefined,
                    inactiveColor: Color.Orange
                  }
                  break;
                case '设置bgBlurOpt.policy为7':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: 7,
                    inactiveColor: Color.Orange
                  }
                  break;
                case '不设置bgBlurOpt.inActColor':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                  }
                  break;
                case 'scale为0.5/inActColor为str正常':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    scale: 0.5,
                    inactiveColor: '#ff4cbfb7'
                  }
                  break;
                case '设置bgBlurOpt.inActColor为num正常':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: 0xff494fc6
                  }
                  break;
                case '设置bgBlurOpt.inActColor为res正常':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: $r('app.color.Color_yellow')
                  }
                  break;
                case 'adaColor为DEFAULT/inActColor为str异常':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    inactiveColor: 'Color.Red'
                  }
                  break;
                case 'adaColor为AVERAGE/inActColor为res异常':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    inactiveColor: $r('app.media.app_icon')
                  }
                  break;
                case 'colorMode为SYSTEM/inActColor为UN':
                  this.contextMenuOption.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    colorMode: ThemeColorMode.SYSTEM,
                    inactiveColor: undefined
                  }
                  break;
              }
            })
            .key('select_bgBlurStyleOptions')

          Button('菜单: bgBlurStyleOptions')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Bottom,
              enableArrow: true,
              transition: this.contextMenuTransition.transition,
              backgroundBlurStyleOptions: this.contextMenuOption.backgroundBlurStyleOptions
            })

          Text(`切换bgEffect属性`)
            .paramTextStyle()
          Select([
            { value:'不设置bgEffect' },
            { value:'设置bgEffect为UN' },
            { value:'bgEffect设置R角为8' },
            { value:'bgEffect只设置R角为0' },
            { value:'bgEffect设置饱和度为3' },
            { value:'bgEffect设置饱和度0.5' },
            { value:'bgEffect设置亮度2' },
            { value:'bgEffect设置亮度0.5' },
            { value:'bgEffect设置AVERAGE颜色' },
            { value:'bgEffect设置DEFAULT颜色' },
            { value:'bgEffect设置灰阶0/127' },
            { value:'bgEffect设置灰阶127/0' },
            { value:'bgEffect设置激活策略' },
            { value:'bgEffect设置参数组合' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置bgEffect':
                  this.contextMenuOption = {}
                  break;
                case '设置bgEffect为UN':
                  this.contextMenuOption = {
                    backgroundEffect: undefined
                  }
                  break;

                case 'bgEffect设置R角为8':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8
                    }
                  }
                  break;
                case 'bgEffect只设置R角为0':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 0
                    }
                  }
                  break;
                case 'bgEffect设置饱和度为3':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      saturation: 3
                    }
                  }
                  break;
                case 'bgEffect设置饱和度0.5':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      saturation: 0.5
                    }
                  }
                  break;
                case 'bgEffect设置亮度2':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      brightness: 2
                    }
                  }
                  break;
                case 'bgEffect设置亮度0.5':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      brightness: 0.5
                    }
                  }
                  break;
                case 'bgEffect设置AVERAGE颜色':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      color: '#739dff00',
                      adaptiveColor: AdaptiveColor.AVERAGE
                    }
                  }
                  break;
                case 'bgEffect设置DEFAULT颜色':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      color: '#739dff00',
                      adaptiveColor: AdaptiveColor.DEFAULT
                    }
                  }
                  break;
                case 'bgEffect设置灰阶0/127':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      blurOptions: {grayscale: [0, 127]}
                    }
                  }
                  break;
                case 'bgEffect设置灰阶127/0':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      blurOptions: {grayscale: [127, 0]}
                    }
                  }
                  break;
                case 'bgEffect设置激活策略':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    }
                  }
                  break;

                case 'bgEffect设置参数组合':
                  this.contextMenuOption = {
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: '#7300ffc4',
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    }
                  }
                  break;
              }
            })
            .key('select_bgEffectOptions')

          Button('菜单: backgroundEffect')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Bottom,
              enableArrow: true,
              transition: this.contextMenuTransition.transition,
              backgroundEffect: this.contextMenuOption.backgroundEffect
            })
        }
        .columnStyle()

        Text(`菜单模糊效果设置绘制效果`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`组合设置bgBlurStyle/bgBlurStyleOpt/bgEffectOpt`)
            .paramTextStyle()
          Select([
            { value:'不设置模糊效果属性' },
            { value:'设置bgBlurStyle' },
            { value:'设置bgBlurStyle/bgBlurStyleOpt' },
            { value:'模糊效果全部设置' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置bgBlurOptions':
                  this.contextMenuBlurOption = {}
                  break;
                case '设置bgBlurStyle':
                  this.contextMenuBlurOption = {
                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: ''
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: '#7300ffc4',
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    }
                  }
                  break;
                case '设置bgBlurStyle/bgBlurStyleOpt':
                  this.contextMenuBlurOption = {
                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: '#7300ffc4',
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    }
                  }
                  break;
                case '模糊效果全部设置':
                  this.contextMenuBlurOption = {
                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: Color.Green,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange,
                    }
                  }
                  break;
              }
            })
            .key('select_bgBlur')

          Button('菜单: 模糊效果')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Top,
              preview: MenuPreviewMode.IMAGE,
              transition: this.contextMenuTransition.transition,
              backgroundColor: '#CC0A59F7',
              backgroundBlurStyle: this.contextMenuBlurOption.backgroundBlurStyle,
              backgroundBlurStyleOptions: this.contextMenuBlurOption.backgroundBlurStyleOptions,
              backgroundEffect: this.contextMenuBlurOption.backgroundEffect,
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

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}