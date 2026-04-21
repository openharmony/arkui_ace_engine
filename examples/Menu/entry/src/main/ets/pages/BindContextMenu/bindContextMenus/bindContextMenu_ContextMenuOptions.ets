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
import { ComponentContent, LengthMetrics, PromptAction, SymbolGlyphModifier } from '@kit.ArkUI';
import { TargetInfo } from '@ohos.arkui.UIContext'
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../MenuBuilder'
import { inputMethod } from '@kit.IMEKit';
// 菜单的wrapBuilder
@Builder
export function MenuDemo(params: MenuAttrOptions) {
  MenuBuilder({
    menuAttrOptions: {
      submenuMode: params.submenuMode,
      enabled: params.enabled,
      subMenuExpandSymbol: params.subMenuExpandSymbol,
      menuItemDivider: params.menuItemDivider,
      menuItemGroupDivider: params.menuItemGroupDivider,
      font: params.font,
      fontColor: params.fontColor,
      radius: params.radius,
      selected: params.selected,
      selectIcon: params.selectIcon,
      contentFont: params.contentFont,
      contentFontColor: params.contentFontColor,
      labelFont: params.labelFont,
      labelFontColor: params.labelFontColor,
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

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width("100%")
  .backgroundColor(Color.Pink)
}

@Entry
@Preview
@Component
export struct bindContextMenu_ContextMenuOptions {
  private inputController: inputMethod.InputMethodController = inputMethod.getController();
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State isShow: boolean = false
  @State isShow1: boolean = false
  @State AVisible: Visibility = Visibility.Visible;
  // Menu指向的绑定节点
  @State targetInfo: TargetInfo = {
    id: 'targetComponent',
  }
  // MenuBuilder的入参
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 0,
    enabled: undefined,
    subMenuExpandSymbol: undefined,
  }
  @State menuOptions: MenuOptions = {
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
    },
    onWillAppear: () => {
      console.info('---1130---Menu---onWillAppear')
    },
    onDidAppear: () => {
      console.info('---1130---Menu---onDidAppear')
    },
    onWillDisappear: () => {
      console.info('---1130---Menu---onWillDisappear')
    },
    onDidDisappear: () => {
      console.info('---1130---Menu---onDidDisappear')
    },
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
  async attachAndListener() {
    focusControl.requestFocus('Index')
    try {
      await this.inputController.attach(true, {
        inputAttribute: {
          textInputType: inputMethod.TextInputType.TEXT,
          enterKeyType: inputMethod.EnterKeyType.SEARCH
        }
      })
    } catch (err) {
      console.error('Fail to attach')
    }
  }
  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(200)
        .height(200)
    }
  }
  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Column({ space: 10 }) {
          Text(`targetComponent`)
            .componentTextStyle()
            .id('targetComponent')
            .bindContextMenu(this.isShow1!!, MenuDemo(this.menuAttrOptions), this.menuOptions)

          MyComponent({
            title: 'bindContextMenu菜单', func: () => {
              this.isShow1 = !this.isShow1
            }
          })
        }
        .columnStyle()
      }
      Column(){
        Scroll(this.scroller) {
          Column({ space: 10 }) {
            Column() {
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

              Text(`offset: ${this.menuOptions.offset}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'x:10,y:10', func: () => {
                    this.menuOptions.offset = { x: 10, y: 10 }
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
                    this.menuOptions.previewAnimationOptions = { scale: [0.8, 1.0] }
                  }
                })
                MyComponent({
                  title: 'hoverScale: [1.0, 0.95]', func: () => {
                    this.menuOptions.previewAnimationOptions = { hoverScale: [1.0, 0.95] }
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
                    this.menuOptions.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      scale: 0,
                      inactiveColor: '#ff0000',
                      colorMode: ThemeColorMode.SYSTEM,
                      adaptiveColor: AdaptiveColor.AVERAGE,
                      blurOptions: { grayscale: [0, 0] }
                    }
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
                    this.menuOptions.backgroundEffect = {
                      policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      inactiveColor: '#ff0000',
                      radius: 40,
                      saturation: 2,
                      brightness: 1,
                      color: 'rgb(255,105,180)',
                      adaptiveColor: AdaptiveColor.AVERAGE,
                      blurOptions: { grayscale: [0, 0] }
                    }
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
                      .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                        .animation({ duration: 3000, curve: Curve.Sharp })),
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

              Text(`previewBorderRadius: ${this.menuOptions.previewBorderRadius}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '0vp', func: () => {
                    this.menuOptions.previewBorderRadius = '0vp'
                  }
                })
                MyComponent({
                  title: '10vp', func: () => {
                    this.menuOptions.previewBorderRadius = '10vp'
                  }
                })
                MyComponent({
                  title: '1000vp', func: () => {
                    this.menuOptions.previewBorderRadius = '1000vp'
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.previewBorderRadius = undefined
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

              Text(`hapticFeedbackMode: ${this.menuOptions.hapticFeedbackMode}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'ENABLED', func: () => {
                    this.menuOptions.hapticFeedbackMode = HapticFeedbackMode.ENABLED
                  }
                })
                MyComponent({
                  title: 'AUTO', func: () => {
                    this.menuOptions.hapticFeedbackMode = HapticFeedbackMode.AUTO
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.hapticFeedbackMode = undefined
                  }
                })
              }

              Text(`outlineWidth: ${this.menuOptions.outlineWidth}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: '10vp', func: () => {
                    this.menuOptions.outlineWidth = '10vp'
                  }
                })
                MyComponent({
                  title: '20vp', func: () => {
                    this.menuOptions.outlineWidth = '20vp'
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.outlineWidth = undefined
                  }
                })
              }

              Text(`outlineColor: ${this.menuOptions.outlineColor}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'rgb(255,105,180)', func: () => {
                    this.menuOptions.outlineColor = 'rgb(255,105,180)'
                  }
                })
                MyComponent({
                  title: 'Color.Blue', func: () => {
                    this.menuOptions.outlineColor = Color.Blue
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.outlineColor = undefined
                  }
                })
              }
              Text(`mask: ${this.menuOptions.mask}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'true', func: () => {
                    this.menuOptions.mask = true
                  }
                })
                MyComponent({
                  title: 'false', func: () => {
                    this.menuOptions.mask = false
                  }
                })
                MyComponent({
                  title: 'Type', func: () => {
                    this.menuOptions.mask = { color: Color.Green, backgroundBlurStyle: BlurStyle.Thin}
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.mask = undefined
                  }
                })
              }
              Text(`modalMode: ${this.menuOptions.modalMode}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'AUTO', func: () => {
                    this.menuOptions.modalMode = ModalMode.AUTO
                  }
                })
                MyComponent({
                  title: 'NONE', func: () => {
                    this.menuOptions.modalMode = ModalMode.NONE
                  }
                })
                MyComponent({
                  title: 'TARGET_WINDOW', func: () => {
                    this.menuOptions.modalMode = ModalMode.TARGET_WINDOW
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.modalMode = undefined
                  }
                })
              }
              Text(`anchorPosition: ${this.menuOptions.anchorPosition}`)
                .paramTextStyle()
              Row({ space: 5 }) {
                MyComponent({
                  title: 'x:-20,y:-20', func: () => {
                    this.menuOptions.anchorPosition = { x: -20, y: -20 }
                  }
                })
                MyComponent({
                  title: 'x:20,y:20', func: () => {
                    this.menuOptions.anchorPosition = { x: 20, y: 20 }
                  }
                })
                MyComponent({
                  title: 'UN', func: () => {
                    this.menuOptions.anchorPosition = undefined
                  }
                })
              }
              Text('透传')
                .fontSize(80)
                .onClick(()=>{
                  console.log('sssssssssssssss')
                })
            }
            .columnStyle()
            Column().height(300)
          }
        }
      }
    }
  }
}