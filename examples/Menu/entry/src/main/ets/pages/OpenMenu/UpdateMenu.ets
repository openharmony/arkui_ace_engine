/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import common from '@ohos.app.ability.common';
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import { BusinessError } from '@kit.BasicServicesKit';
import { ComponentContent, LengthMetrics, PromptAction, SymbolGlyphModifier } from '@kit.ArkUI';
import { TargetInfo } from '@ohos.arkui.UIContext'
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from  './MenuBuilder'

// 菜单的wrapBuilder
@Builder
export function  MenuDemo(params: MenuAttrOptions) {
  MenuBuilder({
    menuAttrOptions: {
      submenuMode: params.submenuMode,
      enabled:params.enabled,
      subMenuExpandSymbol:params.subMenuExpandSymbol,
      menuItemDivider: params.menuItemDivider,
      menuItemGroupDivider: params.menuItemGroupDivider,
      font: params.font,
      fontColor:params.fontColor,
      radius:params.radius,
      selected:params.selected,
      selectIcon:params.selectIcon,
      contentFont:params.contentFont,
      contentFontColor:params.contentFontColor,
      labelFont:params.labelFont,
      labelFontColor:params.labelFontColor,
    }
  })
}

// 菜单预览图
@Builder
export function PreviewBuilder() {
  Image($r('app.media.app_icon'))
    .width(200)
    .height(120)
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(16)
  .width("100%")
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(20)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width("100%")
  .backgroundColor(Color.Pink)
}
@Entry
@Preview
@Component
export struct UpdateMenuIndex {
  private ctx: UIContext = this.getUIContext()
  private promptAction1: PromptAction = this.ctx.getPromptAction()
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, ]
  @State isShow: boolean = false
  @State isShow1: boolean = false

  // setTimeOut duration
  @State duration: number = 2000

  // Menu指向的绑定节点
  @State targetInfo: TargetInfo = {
    id: 'targetComponent',
  }
  // partialUpdate
  @State partialUpdate: boolean = false

  // MenuBuilder的入参
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 0,
    enabled:undefined,
    subMenuExpandSymbol:undefined,
  }
  @State menuOptions: MenuOptions = {
    title: '菜单Title',
    onAppear: () => {
      console.info('---1130---Menu---onAppear')
    },
    onDisappear: () => {
      console.info('---1130---Menu---onDisappear')
    },
    aboutToAppear: () => {
      console.info('---1130---Menu---aboutToAppear')
    },
    aboutToDisappear: () => {
      console.info('---1130---Menu---aboutToDisappear')
    }
  }

  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State isDark: boolean = false;

  @State subMenuExpandSymbol0: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_down'))
    .fontColor(['#ff0000']).fontSize('24vp')
  @State subMenuExpandSymbol1: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_down'))
    .fontColor(['rgb(255,105,180)']).fontSize('24vp')
  @State subMenuExpandSymbol2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_down'))
    .fontColor([Color.Blue]).fontSize('24vp')
  @State subMenuExpandSymbol3: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_down'))
    .fontColor(undefined).fontSize('24vp')
  @State subMenuExpandSymbol4: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_down')).fontSize('24vp')
  @State subMenuExpandSymbol5: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_forward'))
    .fontColor(['#ff0000']).fontSize('20vp').padding('2vp')
  @State subMenuExpandSymbol6: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_forward'))
    .fontColor(['rgb(255,105,180)']).fontSize('20vp').padding('2vp')
  @State subMenuExpandSymbol7: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_forward'))
    .fontColor([Color.Blue]).fontSize('20vp').padding('2vp')
  @State subMenuExpandSymbol8: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_forward'))
    .fontColor(undefined).fontSize('20vp').padding('2vp')
  @State subMenuExpandSymbol9: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.chevron_forward')).fontSize('20vp').padding('2vp')

  build() {
    NavDestination() {
      Column() {
        Column({ space: 10 }) {
          Text(`targetComponent`)
            .componentTextStyle()
            .id('targetComponent')

          MyComponent({
            title: 'openMenu菜单不设置,3s后更新菜单', func: () => {
              let uiContext = this.getUIContext();
              let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
              try {
                this.promptAction1.openMenu(contentNode, this.targetInfo)
                  .then(() => {
                    console.info('---1130---   openMenu success');
                  })
                  .catch((err: BusinessError) => {
                    console.info('---1130---   openMenu error: ' + err.code + ' ' + err.message);
                  })

              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---   openMenu error code is ${code}, message is ${message}`);
              }
              ;
              setTimeout(() => {
                this.promptAction1.updateMenu(contentNode, this.menuOptions);
              }, 3000)
            }
          })
          MyComponent({
            title: 'openMenu菜单设置,3s后增量更新菜单', func: () => {
              let uiContext = this.getUIContext();
              let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
              try {
                this.promptAction1.openMenu(contentNode, this.targetInfo, {
                  enableArrow: true,
                  backgroundColor: Color.Orange,
                  preview:MenuPreviewMode.IMAGE
                })
                  .then(() => {
                    console.info('---1130---   openMenu success');
                  })
                  .catch((err: BusinessError) => {
                    console.info('---1130---   openMenu error: ' + err.code + ' ' + err.message);
                  })

              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---   openMenu error code is ${code}, message is ${message}`);
              }
              ;
              setTimeout(() => {
                this.promptAction1.updateMenu(contentNode, this.menuOptions, true);
              }, 3000)
            }
          })

          MyComponent({
            title: 'openMenu菜单设置,3s后全量更新菜单', func: () => {
              let uiContext = this.getUIContext();
              let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
              try {
                this.promptAction1.openMenu(contentNode, this.targetInfo, {
                  enableArrow: true,
                  backgroundColor: Color.Yellow
                })
                  .then(() => {
                    console.info('---1130---   openMenu success');
                  })
                  .catch((err: BusinessError) => {
                    console.info('---1130---   openMenu error: ' + err.code + ' ' + err.message);
                  })

              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---   openMenu error code is ${code}, message is ${message}`);
              }
              ;
              setTimeout(() => {
                this.promptAction1.updateMenu(contentNode, this.menuOptions, false);
              }, 3000)
            }
          })
        }
        .columnStyle()
      }
      Column(){
        Scroll(this.scroller){
          Column({space: 10}) {
            Column(){
              Text('不支持更新showInSubWindow、preview、previewAnimationOptions、transition、onAppear、aboutToAppear、onDisappear、aboutToDisappear')
              Text(`preview: ${this.menuOptions.preview}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'preview: NONE', func: () => {
                    this.menuOptions.preview = MenuPreviewMode.NONE
                  }
                })
                MyComponent({
                  title: 'preview: IMAGE', func: () => {
                    this.menuOptions.preview = MenuPreviewMode.IMAGE
                  }
                })
                MyComponent({
                  title: 'preview: UN', func: () => {
                    this.menuOptions.preview = undefined
                  }
                })
              }

              Text(`showInSubWindow: ${this.menuOptions.showInSubWindow}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'true', func: () => {
                    this.menuOptions.showInSubWindow = true
                  }
                })
                MyComponent({
                  title: 'false', func: () => {
                    this.menuOptions.showInSubWindow = false
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.showInSubWindow = undefined
                  }
                })
              }

              Text(`offset: ${this.menuOptions.offset}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'x:10,y:100', func: () => {
                    this.menuOptions.offset = {x:10,y:100}
                  }
                })
                MyComponent({
                  title: 'x:-10,y:-10', func: () => {
                    this.menuOptions.offset = { x: -10, y: -10 }
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.offset = undefined
                  }
                })
              }

              Text(`placement: ${this.menuOptions.placement}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'Right', func: () => {
                    this.menuOptions.placement = Placement.Right
                  }
                })
                MyComponent({
                  title: 'RightBottom', func: () => {
                    this.menuOptions.placement = Placement.RightBottom
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.placement = undefined
                  }
                })
              }

              Text(`enableArrow: ${this.menuOptions.enableArrow}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'true', func: () => {
                    this.menuOptions.enableArrow = true
                  }
                })
                MyComponent({
                  title: 'false', func: () => {
                    this.menuOptions.enableArrow = false
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.enableArrow = undefined
                  }
                })
              }

              Text(`enableHoverMode: ${this.menuOptions.enableHoverMode}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'true', func: () => {
                    this.menuOptions.enableHoverMode = true
                  }
                })
                MyComponent({
                  title: 'false', func: () => {
                    this.menuOptions.enableHoverMode = false
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.enableHoverMode = undefined
                  }
                })
              }
              Text(`arrowOffset: ${this.menuOptions.arrowOffset}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '20', func: () => {
                    this.menuOptions.arrowOffset = 20
                  }
                })
                MyComponent({
                  title: '10', func: () => {
                    this.menuOptions.arrowOffset = 10
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.arrowOffset = undefined
                  }
                })
              }

              Text(`previewAnimationOptions: ${this.menuOptions.previewAnimationOptions}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'scale: [0.8, 1.0]', func: () => {
                    this.menuOptions.previewAnimationOptions = {scale: [0.8, 1.0]}
                  }
                })
                MyComponent({
                  title: 'animation&rotate', func: () => {
                    this.menuOptions.previewAnimationOptions = {
                      scale: [0.8, 1.0],
                      transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                        TransitionEffect.rotate({ z: 1, angle: 180 }))
                    }
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.previewAnimationOptions = undefined
                  }
                })
              }

              Text(`backgroundColor: ${this.menuOptions.backgroundColor}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '#ff0000', func: () => {
                    this.menuOptions.backgroundColor = '#ff0000'
                  }
                })
                MyComponent({
                  title: 'rgb(255,105,180)', func: () => {
                    this.menuOptions.backgroundColor = 'rgb(255,105,180)'
                  }
                })
                MyComponent({
                  title: 'Color.Blue', func: () => {
                    this.menuOptions.backgroundColor = Color.Blue
                  }
                })
                MyComponent({
                  title: 'un', func: () => {
                    this.menuOptions.backgroundColor = undefined
                  }
                })
              }

              Text(`backgroundBlurStyle: ${this.menuOptions.backgroundBlurStyle}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'Thin', func: () => {
                    this.menuOptions.backgroundBlurStyle = BlurStyle.Thin
                  }
                })
                MyComponent({
                  title: 'NONE', func: () => {
                    this.menuOptions.backgroundBlurStyle = BlurStyle.NONE
                  }
                })
                MyComponent({
                  title: 'COMPONENT_REGULAR', func: () => {
                    this.menuOptions.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                  }
                })
                MyComponent({
                  title: 'un', func: () => {
                    this.menuOptions.backgroundBlurStyle = undefined
                  }
                })
              }

              Text(`backgroundBlurStyleOptions: ${this.menuOptions.backgroundBlurStyleOptions}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '设置', func: () => {
                    this.menuOptions.backgroundBlurStyleOptions = {policy:BlurStyleActivePolicy.ALWAYS_ACTIVE,scale:1,
                      inactiveColor:'#ff0000',colorMode:ThemeColorMode.SYSTEM,adaptiveColor:AdaptiveColor.AVERAGE,blurOptions:{grayscale:[0,0]}}
                  }
                })
                MyComponent({
                  title: 'un', func: () => {
                    this.menuOptions.backgroundBlurStyleOptions = undefined
                  }
                })
              }

              Text(`backgroundEffect: ${this.menuOptions.backgroundEffect}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '设置', func: () => {
                    this.menuOptions.backgroundEffect = {policy:BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      inactiveColor:'#ff0000',radius:40,saturation:2,brightness:1,color:'rgb(255,105,180)',
                      adaptiveColor:AdaptiveColor.AVERAGE,blurOptions:{grayscale:[0,0]}}
                  }
                })
                MyComponent({
                  title: 'un', func: () => {
                    this.menuOptions.backgroundEffect = undefined
                  }
                })
              }

              Text(`transition: ${this.menuOptions.transition}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '设置', func: () => {
                    this.menuOptions.transition = TransitionEffect.asymmetric(TransitionEffect.OPACITY
                      .animation({ duration: 3000, curve: Curve.Sharp })
                      .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 }).animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                  }
                })
                MyComponent({
                  title: 'un', func: () => {
                    this.menuOptions.transition = undefined
                  }
                })
              }

              Text(`borderRadius: ${this.menuOptions.borderRadius}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '0vp', func: () => {
                    this.menuOptions.borderRadius = '0vp'
                  }
                })
                MyComponent({
                  title: '10vp', func: () => {
                    this.menuOptions.borderRadius = '10vp'
                  }
                })
                MyComponent({
                  title: '1000vp', func: () => {
                    this.menuOptions.borderRadius = '1000vp'
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.borderRadius = undefined
                  }
                })
              }

              Text(`layoutRegionMargin: ${this.menuOptions.layoutRegionMargin}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'top:200', func: () => {
                    this.menuOptions.layoutRegionMargin = { top:200 }
                  }
                })
                MyComponent({
                  title: 'bottom:100', func: () => {
                    this.menuOptions.layoutRegionMargin = { bottom:100 }
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.layoutRegionMargin = undefined
                  }
                })
              }
            }
            .columnStyle()

            Column().height(300)
          }
          .width('100%')
        }
      }
    }
  }
}
