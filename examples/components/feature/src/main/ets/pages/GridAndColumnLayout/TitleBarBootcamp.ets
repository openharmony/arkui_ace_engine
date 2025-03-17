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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock } from 'common';

@Component
export struct TitleBarBootcamp {
  @Provide('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @State hideItemValue: boolean = false;
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'menuItem',
      icon: 'resources/base/media/text_title.svg' // 图标资源路径
    },
  ]
  @Require @Prop title: ResourceStr;
  @State navigationMode: NavigationMode = NavigationMode.Stack;
  @State enableToolBarAdaptation: boolean = false;
  @State showParameters: boolean = false;
  @State enableNavigationMode: boolean = false;
  @State enableAdaptation: boolean = false;
  @State enableHideItem: boolean = false;
  @State isBackGroundEffect: boolean = false;
  @State enableEffect: boolean = false;
  @State blurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THIN;
  @State enableBlurStyle: boolean = false;
  @State enableRadius: boolean = false;
  @State isRadiusIndex: number = 20;
  @State isRadius: number = 20;
  @State enableSaturation: boolean = false;
  @State isSaturation: number = 10;
  @State enableBrightness: boolean = false;
  @State isBrightness: number = 0;
  @State enableColorEffect: boolean = false;
  @State isColorEffect: string = '#66FFFFFF';
  @State enableAdaptiveColor: boolean = false;
  @State isAdaptiveColor: AdaptiveColor = AdaptiveColor.DEFAULT;
  @State enableBlurOptions: boolean = false;
  @State isBlurOptions: BlurOptions = { grayscale: [0, 0] };
  @State enableColorMode: boolean = false;
  @State isColorMode: ThemeColorMode = ThemeColorMode.DARK;
  @State enableAdaptiveColorBlurStyle: boolean = false;
  @State isAdaptiveColorBlurStyle: AdaptiveColor = AdaptiveColor.DEFAULT;
  @State enableBlurOptionsBlurStyle: boolean = false;
  @State isBlurOptionsBlurStyle: BlurOptions = { grayscale: [20, 20] };
  @State enableScale: boolean = false;
  @State isScale: number = 1;
  @State enableNavigation: boolean = false;
  @State isNavigation: boolean = false;
  private scrollerForScroll: Scroller = new Scroller();

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Scroll(this.scrollerForScroll) {
      Column() {
        if (this.isNavigation) {
          Navigation(this.navPathStack) {
            Column() {
            }
          }
          .titleMode(NavigationTitleMode.Mini)
          .title('titleBar', this.isBackGroundEffect ? {
            backgroundEffect:
            {
              radius: this.isRadius,
              saturation: this.isSaturation,
              brightness: this.isBrightness,
              color: this.isColorEffect,
              adaptiveColor: this.isAdaptiveColor,
              blurOptions: this.isBlurOptions,
            }
          } : {
            backgroundBlurStyle: this.blurStyle,
            backgroundBlurStyleOptions:
            {
              colorMode: this.isColorMode,
              adaptiveColor:
              this.isAdaptiveColor,
              scale:
              this.isScale,
              blurOptions:
              this.isBlurOptions
            }
          }
          )
          .mode(this.navigationMode)
          .menus(this.menuItems, this.isBackGroundEffect ?
            {
              moreButtonOptions: {
                backgroundEffect: {
                  radius: this.isRadius,
                  saturation: this.isSaturation,
                  brightness: this.isBrightness,
                  color: this.isColorEffect,
                  adaptiveColor: this.isAdaptiveColor,
                  blurOptions: this.isBlurOptions,
                },
              }
            } : {
              moreButtonOptions: {
                backgroundBlurStyle: this.blurStyle,
                backgroundBlurStyleOptions:
                {
                  colorMode: this.isColorMode,
                  adaptiveColor:
                  this.isAdaptiveColor,
                  scale:
                  this.isScale,
                  blurOptions:
                  this.isBlurOptions
                }
              }
            }
          )
        } else {
          NavDestination() {
            Column() {
            }
          }
          .title('titleBar', this.isBackGroundEffect ? {
            backgroundEffect:
            {
              radius: this.isRadius,
              saturation: this.isSaturation,
              brightness: this.isBrightness,
              color: this.isColorEffect,
              adaptiveColor: this.isAdaptiveColor,
              blurOptions: this.isBlurOptions,
            }
          } : {
            backgroundBlurStyle: this.blurStyle,
            backgroundBlurStyleOptions:
            {
              colorMode: this.isColorMode,
              adaptiveColor:
              this.isAdaptiveColor,
              scale:
              this.isScale,
              blurOptions:
              this.isBlurOptions
            }
          }
          )
          .menus(this.menuItems, this.isBackGroundEffect ?
            {
              moreButtonOptions: {
                backgroundEffect: {
                  radius: this.isRadius,
                  saturation: this.isSaturation,
                  brightness: this.isBrightness,
                  color: this.isColorEffect,
                  adaptiveColor: this.isAdaptiveColor,
                  blurOptions: this.isBlurOptions,
                },
              }
            } : {
              moreButtonOptions: {
                backgroundBlurStyle: this.blurStyle,
                backgroundBlurStyleOptions:
                {
                  colorMode: this.isColorMode,
                  adaptiveColor:
                  this.isAdaptiveColor,
                  scale:
                  this.isScale,
                  blurOptions:
                  this.isBlurOptions
                }
              }
            }
          )
        }
      }.width('100%').height('100%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '是否设置backgroundEffectOptions',
          isEnabled: this.enableEffect,
          value: this.isBackGroundEffect,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false },
          ]
        })

        RadioBlock({
          title: '标题栏背景模糊样式',
          isEnabled: this.enableBlurStyle,
          value: this.blurStyle,
          dataSource: [
            { label: '组件超轻薄材质模糊', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: '组件轻薄材质模糊', value: BlurStyle.COMPONENT_THIN },
            { label: '组件普通材质模糊', value: BlurStyle.COMPONENT_REGULAR },
            { label: '组件厚材质模糊', value: BlurStyle.COMPONENT_THICK },
            { label: '组件超厚材质模糊', value: BlurStyle.COMPONENT_ULTRA_THICK }]
        })

        RadioBlock({
          title: 'navigation/navDestination',
          isEnabled: this.enableNavigation,
          value: this.isNavigation,
          dataSource: [
            { label: 'navigation', value: true },
            { label: 'navDestination', value: false }
          ]
        })

        RadioBlock({
          title: '背景属性选项（模糊半径）',
          isEnabled: this.enableRadius,
          value: this.isRadius,
          dataSource: [{ label: '20', value: 20 }, { label: '60', value: 60 }]

        })

        RadioBlock({
          title: '背景属性选项（饱和度）',
          isEnabled: this.enableSaturation,
          value: this.isSaturation,
          dataSource: [
            { label: '10', value: 10 },
            { label: '40', value: 40 },
          ]
        })

        RadioBlock({
          title: '背景属性选项（亮度）',
          isEnabled: this.enableBrightness,
          value: this.isBrightness,
          dataSource: [
            { label: '0', value: 0 },
            { label: '1', value: 1 },
          ]
        })

        RadioBlock({
          title: '背景属性选项（颜色）',
          isEnabled: this.enableColorEffect,
          value: this.isColorEffect,
          dataSource: [
            { label: '#66FFFFFF', value: '#66FFFFFF' },
            { label: '#661A1A1A', value: '#661A1A1A' },
          ]
        })

        RadioBlock({
          title: '背景属性选项（自适应颜色）',
          isEnabled: this.enableAdaptiveColor,
          value: this.isAdaptiveColor,
          dataSource: [
            { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
            { label: 'AVERAGE', value: AdaptiveColor.AVERAGE },
          ]
        })

        RadioBlock({
          title: '背景属性选项（模糊选项）',
          isEnabled: this.enableBlurOptions,
          value: this.isBlurOptions,
          dataSource: [
            { label: '(0,0)', value: { grayscale: [0, 0] } as BlurOptions },
            { label: '(1,1)', value: { grayscale: [1, 1] } as BlurOptions },
          ]
        })
        //backgroundblurstyleoptions
        RadioBlock({
          title: '背景模糊样式（深浅色模式）',
          isEnabled: this.enableColorMode,
          value: this.isColorMode,
          dataSource: [
            { label: 'Dark', value: ThemeColorMode.DARK },
            { label: 'Light', value: ThemeColorMode.LIGHT },
          ]
        })

        RadioBlock({
          title: '背景模糊样式（自适应颜色）',
          isEnabled: this.enableAdaptiveColorBlurStyle,
          value: this.isAdaptiveColorBlurStyle,
          dataSource: [
            { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
            { label: 'AVERAGE', value: AdaptiveColor.AVERAGE },
          ]
        })

        RadioBlock({
          title: '背景模糊样式（模糊选项）',
          isEnabled: this.enableBlurOptionsBlurStyle,
          value: this.isBlurOptionsBlurStyle,
          dataSource: [
            { label: '(20,20)', value: { grayscale: [20, 20] } as BlurOptions },
          ]
        })

        RadioBlock({
          title: '背景模糊样式（比例）',
          isEnabled: this.enableScale,
          value: this.isScale,
          dataSource: [
            { label: '1', value: 1 },
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TitleBarBootcampPreviewer {
  build() {
    TitleBarBootcamp({ title: '标题栏/TitleBar' })
  }
}