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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';

@Component
export struct ListBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State dataSource: number[] = Array.from({ length: 100 }, (_: Object, index: number) => index);
  @State markOutDataSource: number[] = Array.from({ length: 3 }, (_: Object, index: number) => index);
  @State enableEdgeEffect: boolean = false;
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State enableDividerStrokeWidth: boolean = false;
  @State dividerStrokeWidth: string | number = 0;
  @State enableDividerColor: boolean = false;
  @State dividerColor: ResourceColor = '0x08000000';
  @State enableDividerStartMargin: boolean = false;
  @State dividerStartMargin: string | number = 0;
  @State enableDividerEndMargin: boolean = false;
  @State dividerEndMargin: string | number = 0;
  @State enableScrollBar: boolean = false;
  @State scrollBar: BarState = BarState.Auto;
  @State enableDividerValue: boolean = false;
  @State dividerValue: boolean = false;
  @State enableDirection: boolean = false;
  @State currentDirection: Direction = Direction.Auto;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = false;
  @State enableFadingEdgeLengthValue: boolean = false;
  @State fadingEdgeLengthValue: number = 32;
  @State enableFadingEdgeLengthUnit: boolean = false;
  @State fadingEdgeLengthUnit: LengthUnit = LengthUnit.VP;
  @State enableAxis: boolean = false;
  @State axis: Axis = Axis.Vertical;
  @State enableDragGray: boolean = false;
  @State dragGray: DragPreviewMode = DragPreviewMode.AUTO;

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
  itemEnd() {
    //设置ListItem的划出组件
    Row() {
      ForEach(this.markOutDataSource, () => {
        Button({ type: ButtonType.Circle, stateEffect: true }) {
          Image($r('app.media.app_icon'))
        }
        .width(40)
        .height(40)
      })
    }
  }

  @Builder
  Content() {
    Column() {
      List() {
        ForEach(this.dataSource, (item: number) => {
          ListItem() {
            Text(item + '')
              .width('100%')
              .padding(16)
              .textAlign(TextAlign.Center)
          }
          .direction(useEnabled(this.enableDirection, this.currentDirection))
          .swipeAction({
            end: {
              builder: () => {
                this.itemEnd()
              },
              onAction: () => {
                animateTo({ duration: 1000 }, () => {
                  let index = this.dataSource.indexOf(item)
                  this.dataSource.splice(index, 1)
                })
              },
              actionAreaDistance: 100,
            }
          })
        })
      }
      .direction(useEnabled(this.enableDirection, this.currentDirection))
      .edgeEffect(useEnabled(this.enableEdgeEffect, this.edgeEffect))
      .divider(this.dividerValue ?
        {
          strokeWidth: useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth),
          color: useEnabled(this.enableDividerColor, this.dividerColor),
          startMargin: useEnabled(this.enableDividerStartMargin, this.dividerStartMargin),
          endMargin: useEnabled(this.enableDividerEndMargin, this.dividerEndMargin)
        } : null)
      .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
      .listDirection(useEnabled(this.enableAxis, this.axis))
      .fadingEdge(
        useEnabled(this.enableFadingEdge, this.fadingEdge),
        useEnabled<FadingEdgeOptions>(this.fadingEdge, {
          fadingEdgeLength: new LengthMetrics(this.fadingEdgeLengthValue, this.fadingEdgeLengthUnit)
        })
      )
      .onDragStart(() => {})
      .dragPreviewOptions({ mode: useEnabled(this.enableDragGray, this.dragGray)})

    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '布局方式',
          isEnabled: $enableDirection,
          value: $currentDirection,
          dataSource: [
            { label: '默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
          ]
        })
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
        RadioBlock({
          title: '是否显示分割线',
          isEnabled: this.enableDividerValue,
          value: this.dividerValue,
          dataSource: [
            { label: '自定义', value: true },
            { label: '不显示', value: false }
          ]
        })
        RadioBlock({
          title: '开启渐隐效果',
          isEnabled: this.enableFadingEdge,
          value: this.fadingEdge,
          dataSource: [
            { label: '开启', value: true },
            { label: '关闭', value: false }
          ]
        })
        if (this.fadingEdge) {
          SliderBlock({
            title: '渐隐长度值',
            isEnabled: this.enableFadingEdgeLengthValue,
            value: this.fadingEdgeLengthValue,
            min: 0,
            max: 500
          })
          RadioBlock({
            title: '渐隐长度单位',
            isEnabled: this.enableFadingEdgeLengthUnit,
            value: this.fadingEdgeLengthUnit,
            dataSource: [
              { label: 'px', value: LengthUnit.PX },
              { label: 'vp', value: LengthUnit.VP },
              { label: 'fp', value: LengthUnit.FP },
              { label: 'percent', value: LengthUnit.PERCENT },
              { label: 'lpx', value: LengthUnit.LPX }
            ]
          })
        }
        RadioBlock({
          title: '布局方向',
          isEnabled: this.enableAxis,
          value: this.axis,
          dataSource: [
            { label: '竖直', value: Axis.Vertical },
            { label: '水平', value: Axis.Horizontal }
          ]
        })
        if (this.dividerValue) {
          SliderBlock({
            title: '分割线线宽(vp)',
            isEnabled: $enableDividerStrokeWidth,
            value: $dividerStrokeWidth,
            min: 0,
            max: 30
          })
          ColorBlock({
            title: '分割线颜色',
            isEnabled: $enableDividerColor,
            color: $dividerColor,
          })
          SliderBlock({
            title: '分割线与列表侧边起始端的距离(vp)',
            isEnabled: $enableDividerStartMargin,
            value: $dividerStartMargin,
            min: 0,
            max: 30
          })
          SliderBlock({
            title: '分割线与列表侧边结束端的距离(vp)',
            isEnabled: $enableDividerEndMargin,
            value: $dividerEndMargin,
            min: 0,
            max: 30
          })
        }
        RadioBlock({
          title: '拖拽背板图样式',
          isEnabled: $enableDragGray,
          value: $dragGray,
          dataSource: [
            { label: '默认', value: DragPreviewMode.AUTO },
            { label: '灰显', value: DragPreviewMode.ENABLE_DRAG_ITEM_GRAY_EFFECT }
          ]
        })
      }
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct ListBootcampPreviewer {
  build() {
    ListBootcamp({
      title: '列表/List'
    })
  }
}