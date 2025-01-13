/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { Route, RouteGroup } from 'common/src/main/ets/common/route';
import { RadioBlock, SliderBlock,ColorBlock,useEnabled } from 'common';
import curves from '@ohos.curves';


@Component
export struct ListItemGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State rating: number = 3.5;
  @State enableEdgeEffect: boolean = false;
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State enableDividerStrokeWidth: boolean  = false;
  @State dividerStrokeWidth: string | number  = 0;
  @State enableDividerColor: boolean  = false;
  @State dividerColor: ResourceColor  = 0x08000000;
  @State enableDividerStartMargin: boolean  = false;
  @State dividerStartMargin: string | number  = 0;
  @State enableDividerEndMargin: boolean  = false;
  @State dividerEndMargin: string | number  = 0;
  @State enableScrollBar: boolean  = false;
  @State scrollBar: BarState = BarState.Auto;
  @State enableSpace: boolean  = false;
  @State space: number | string  = 0;
  @State enableStyle: boolean  = false;
  @State style: ListItemGroupStyle  = ListItemGroupStyle.NONE;
  @State enableCompWidth: boolean = false;
  @State compWidth: Length = 'auto';
  @State enableCompHeight: boolean = false;
  @State compHeight: Length = 'auto';
  @State enableCompPadding: boolean = false;
  @State compPadding: number = 0;
  @State enableCompMargin: boolean = false;
  @State compMargin: number = 0;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = '#ff000000';
  @State enableCompBorderWidth: boolean = false;
  @State compBorderWidth: number = 0;
  @State enableCompBorderColor: boolean = false;
  @State compBorderColor: ResourceColor = Color.Black;
  @State enableCompBorderRadius: boolean = false;
  @State compBorderRadius: number = 0;
  @State enableCompBorderStyle: boolean = false;
  @State compBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableCompFlexBasis: boolean = false;
  @State compFlexBasis: number | string = 'auto';
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableCompClip: boolean = false;
  @State compClip: boolean = false;

  @State selection: string | null = null;
  @State routesChildren: Route[] =  [
    { name: 'Chinese', label: '语文'},
    { name: 'Math', label: '数学'},
    { name: 'English', label: '英语'},
    { name: 'Politics',label:'政治'},
    { name: 'History',label:'历史'},
    { name: 'Geography',label:'地理'}
  ];
  @State names: string[] = ['Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday'];
  @State labels: string[] = ['星期一','星期二','星期三','星期四','星期五','星期六','星期日'];
  @State routes: RouteGroup[] = [];

  aboutToAppear() {
    for (let i = 0; i < this.names.length; i++) {
      this.routes.push({name:this.names[i],label:this.labels[i],children:this.routesChildren})
    }
  }

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
  ListItemGroupHeader(route: RouteGroup) {
    Row() {
      Text(route.label)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontWeight(FontWeight.Medium)

      Blank()

      Text(`${route.children.length}`)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .opacity(this.selection === route.name ? 0 : 1)

      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(24)
        .width(24)
        .rotate({ angle: this.selection === route.name ? 90 : 0 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 30) })
    }
    .borderRadius(20)
    .width('100%')
    .padding({ left: 8, right: 8, top: 18, bottom: 18 })
    .enabled(!!route.children.length)
    .onTouch((event) => {
      if (event.type === TouchType.Down) {
      } else if (event.type === TouchType.Up) {
        animateTo({ curve: curves.interpolatingSpring(0, 1, 228, 25) }, () => {
          if (this.selection === route.name) {
            this.selection = null
          } else {
            this.selection = route.name
          }
        });
      }
    })
  }

  @Builder
  Content() {
    Column() {
      List({ space: 12 }) {
        ForEach(this.routes, (routeGroup: RouteGroup) => {
          ListItemGroup({
            header: this.ListItemGroupHeader(routeGroup),
            space: useEnabled(this.enableSpace, this.space),
            style: useEnabled(this.enableStyle, this.style)
          }) {
            if (routeGroup.name === this.selection) {
              ForEach(routeGroup.children, (route: Route) => {
                ListItem() {
                  Row() {
                    Text(route.label)
                      .fontSize(16)
                    Blank()
                    Image($r('sys.media.ohos_ic_public_arrow_right'))
                      .fillColor($r('sys.color.ohos_id_color_fourth'))
                      .height(24)
                      .width(24)
                  }
                  .borderRadius(20)
                  .padding({ left: 8, right: 8, top: 13, bottom: 13 })
                  .transition(TransitionEffect.OPACITY.animation({
                    curve: curves.interpolatingSpring(0, 1, 228, 30)
                  }))
                  .width('100%')
                  .onClick(() => {

                  })
                }
                .width('100%')
              })
            }
          }
          .divider({
            strokeWidth:useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth),
            color: useEnabled(this.enableDividerColor, this.dividerColor),
            startMargin: useEnabled(this.enableDividerStartMargin, this.dividerStartMargin),
            endMargin: useEnabled(this.enableDividerEndMargin, this.dividerEndMargin)
          })
          .width(useEnabled(this.enableCompWidth, this.compWidth))
          .height(useEnabled(this.enableCompHeight, this.compHeight))
          .padding(useEnabled(this.enableCompPadding, this.compPadding))
          .margin(useEnabled(this.enableCompMargin, this.compMargin))
          .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
          .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
          .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
          .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
          .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
          .flexBasis(useEnabled(this.enableCompFlexBasis, this.compFlexBasis))
          .opacity(useEnabled(this.enableCompOpacity, this.compOpacity))
          .visibility(useEnabled(this.enableCompVisibility, this.compVisibility))
          .direction(useEnabled(this.enableCompDirection, this.compDirection))
          .clip(useEnabled(this.enableCompClip, this.compClip))
        })
      }
      .layoutWeight(1)
      .width('100%')
      .edgeEffect(useEnabled(this.enableEdgeEffect, this.edgeEffect))
      .divider({
        strokeWidth:useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth),
        color: useEnabled(this.enableDividerColor, this.dividerColor),
        startMargin: useEnabled(this.enableDividerStartMargin, this.dividerStartMargin),
        endMargin: useEnabled(this.enableDividerEndMargin, this.dividerEndMargin)
      })
      .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'space',
          isEnabled: $enableSpace,
          value: $space,
          min: 0,
          max: 10
        })

        RadioBlock({
          title: 'style',
          isEnabled: $enableStyle,
          value: $style,
          dataSource: [
            { label: 'NONE', value: ListItemGroupStyle.NONE },
            { label: 'CARD', value: ListItemGroupStyle.CARD }
          ]
        })

        RadioBlock({
          title: 'scrollBar',
          isEnabled: $enableScrollBar,
          value: $scrollBar,
          dataSource: [
            { label: 'Auto', value: BarState.Auto },
            { label: 'Off', value: BarState.Off },
            { label: 'On', value: BarState.On }
          ]
        })

        RadioBlock({
          title: 'edgeEffect',
          isEnabled: $enableEdgeEffect,
          value: $edgeEffect,
          dataSource: [
            { label: 'Spring', value: EdgeEffect.Spring },
            { label: 'Fade', value: EdgeEffect.Fade },
            { label: 'None', value: EdgeEffect.None }
          ]
        })

        ColorBlock({
          title: 'divider.color',
          isEnabled: $enableDividerColor,
          color: $dividerColor,
        })

        SliderBlock({
          title: 'divider.strokeWidth',
          isEnabled: $enableDividerStrokeWidth,
          value: $dividerStrokeWidth,
          min: 0,
          max: 30
        })

        SliderBlock({
          title: 'divider.startMargin',
          isEnabled: $enableDividerStartMargin,
          value: $dividerStartMargin,
          min: 0,
          max: 30
        })

        SliderBlock({
          title: 'divider.endMargin',
          isEnabled: $enableDividerEndMargin,
          value: $dividerEndMargin,
          min: 0,
          max: 30
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 50,
          max: 400
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableCompPadding,
          value: $compPadding,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableCompMargin,
          value: $compMargin,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableCompBorderWidth,
          value: $compBorderWidth,
          min: 0,
          max: 20
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableCompBorderColor,
          color: $compBorderColor
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableCompBorderRadius,
          value: $compBorderRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableCompBorderStyle,
          value: $compBorderStyle,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'flexBasis',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 10,
          max: 200
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableCompOpacity,
          value: $compOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableCompVisibility,
          value: $compVisibility,
          dataSource: [
            { label: 'None', value: Visibility.None },
            { label: 'Hidden', value: Visibility.Hidden },
            { label: 'Visible', value: Visibility.Visible }
          ]
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl }
          ]
        })

        RadioBlock({
          title: 'clip',
          isEnabled: $enableCompClip,
          value: $compClip,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct ListItemGroupBootcampPreviewer{
  build(){
    ListItemGroupBootcamp({
      title: '分组列表/ListItemGroup'
    })
  }
}