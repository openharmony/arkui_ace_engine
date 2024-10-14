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

import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import { Drawer } from '../../components/Drawer';
import { RadioBlock, SliderBlock, useEnabled } from 'common';


@Component
export struct WaterFlowBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = false;
  @State enableFadingEdgeLengthValue: boolean = false;
  @State fadingEdgeLengthValue: number = 32;
  @State enableFadingEdgeLengthUnit: boolean = false;
  @State fadingEdgeLengthUnit: LengthUnit = LengthUnit.VP;
  @State enableAxis: boolean = false;
  @State axis: FlexDirection = FlexDirection.Column;
  @State enableDirection: boolean = false;
  @State directionMode: Direction = Direction.Ltr;
  @State totalCount: number = 20;
  scroller: Scroller = new Scroller();

  getElements() {
    return Array.from({ length: this.totalCount }, (_: ESObject, index: number) => `${index}`);
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
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      WaterFlow({ scroller: this.scroller }) {
        ForEach(this.getElements(), (item: number) => {
          FlowItem() {
          }
          .width('100%')
          .height(80)
          .margin({ bottom: 20 })
          .backgroundColor('#510A59F7')
          .borderRadius(12)
        }, (item: string) => item)
      }
      .layoutDirection(useEnabled(this.enableAxis, this.axis))
      .direction(useEnabled(this.enableDirection, this.directionMode))
      .fadingEdge(
        useEnabled(this.enableFadingEdge, this.fadingEdge),
        useEnabled<FadingEdgeOptions>(this.fadingEdge, {
          fadingEdgeLength: new LengthMetrics(this.fadingEdgeLengthValue, this.fadingEdgeLengthUnit)
        })
      )
    }
    .height('80%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
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
            { label: '竖直', value: FlexDirection.Column },
            { label: '水平', value: FlexDirection.Row }
          ]
        })
        RadioBlock({
          title: '镜像模式',
          isEnabled: this.enableDirection,
          value: this.directionMode,
          dataSource: [
            { label: '正常', value: Direction.Ltr },
            { label: '镜像', value: Direction.Rtl }
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
struct WaterFlowBootcampPreviewer {
  build() {
    WaterFlowBootcamp({
      title: '瀑布流容器/WaterFlow'
    })
  }
}