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
  @State enableStrokeWidth: boolean  = false;
  @State strokeWidth: string | number  = 1;
  @State enableColor: boolean  = false;
  @State color: ResourceColor  = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableStartMargin: boolean  = false;
  @State startMargin: string | number  = 20;
  @State enableEndMargin: boolean  = false;
  @State endMargin: string | number  = 20;
  @State enableScrollBar: boolean  = false;
  @State scrollBar: BarState = BarState.Auto;
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
            style: ListItemGroupStyle.CARD,
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
          }.padding(4).divider({ strokeWidth: 0.5 })
        })
      }
      .layoutWeight(1)
      .width('100%')
      .edgeEffect(useEnabled(this.enableEdgeEffect, this.edgeEffect))
      .divider({
        strokeWidth:useEnabled(this.enableStrokeWidth, this.strokeWidth),
        color: useEnabled(this.enableColor, this.color),
        startMargin: useEnabled(this.enableStartMargin, this.startMargin),
        endMargin: useEnabled(this.enableEndMargin, this.endMargin)
      })
      .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
    }
  }
  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '滚动条状态',
          isEnabled: $enableScrollBar,
          value: $scrollBar,
          dataSource: [
            { label: '按需显示', value: BarState.Auto },
            { label: '不显示', value: BarState.Off },
            { label: '常驻显示', value: BarState.On }
          ]
        })
        RadioBlock({
          title: '边缘效果',
          isEnabled: $enableEdgeEffect,
          value: $edgeEffect,
          dataSource: [
            { label: '弹性效果', value: EdgeEffect.Spring },
            { label: '阴影效果', value: EdgeEffect.Fade },
            { label: '无动态效果', value: EdgeEffect.None }
          ]
        })
        ColorBlock({
          title: '分割线颜色',
          isEnabled: this.enableColor,
          color: this.color,
        })
        SliderBlock({
          title: '分割线线宽(vp)',
          isEnabled: $enableStrokeWidth,
          value: $strokeWidth,
          min: 0,
          max: 30
        })
        SliderBlock({
          title: '分割线与列表侧边起始端的距离(vp)',
          isEnabled: $enableStartMargin,
          value: $startMargin,
          min: 0,
          max: 30
        })
        SliderBlock({
          title: '分割线与列表侧边结束端的距离(vp)',
          isEnabled: $enableEndMargin,
          value: $endMargin,
          min: 0,
          max: 30
        })
      }
    }.width('100%')
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