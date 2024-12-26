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
import { ColorBlock, IconBlock, RadioBlock, SliderBlock, useEnabled } from 'common';


@Component
export struct GaugeBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableGaugeValue: boolean = false;
  @State gaugeValue: number = 0;
  @State enableGaugeChildComponent: boolean = false;
  @State gaugeChildComponent: boolean = false;
  @State enableGaugeMin: boolean = false;
  @State gaugeMin: number = 0;
  @State enableGaugeMax: boolean = false;
  @State gaugeMax: number = 100;
  @State enableStartAngle: boolean = false;
  @State startAngle: number = 0;
  @State enableEndAngle: boolean = false;
  @State endAngle: number = 360;
  @State enableColors: boolean = false;
  @State colors: ResourceStr = '#ff000000';
  @State enableStrokeWidth: boolean = false;
  @State strokeWidth: number = 4;
  @State enableDescription: boolean = false;
  @State description: boolean = false;
  @State enableTrackShadowRadius: boolean = false;
  @State trackShadowRadius: number = 20;
  @State enableTrackShadowOffsetX: boolean = false;
  @State trackShadowOffsetX: number = 5;
  @State enableTrackShadowOffsetY: boolean = false;
  @State trackShadowOffsetY: number = 5;
  @State enableIndicatorIcon: boolean = false;
  @State indicatorIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone')
  @State enableIndicatorSpace: boolean = false;
  @State indicatorSpace: number = 8

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
  descriptionBuilder() {
    Text('说明文本')
      .maxFontSize('30sp')
      .minFontSize('10.0vp')
      .fontColor('#fffa2a2d')
      .fontWeight(FontWeight.Medium)
      .width('100%')
      .height('100%')
      .textAlign(TextAlign.Center)
  }

  @Builder
  Content() {
    Column() {

      Gauge({
        value: useEnabled(this.enableGaugeValue, this.gaugeValue),
        min: useEnabled(this.enableGaugeMin, this.gaugeMin),
        max: useEnabled(this.enableGaugeMax, this.gaugeMax),
      }) {
        Column() {
          if (this.gaugeChildComponent) {

            Text(useEnabled(this.enableGaugeValue, this.gaugeValue)?.toString())
              .fontWeight(FontWeight.Medium)
              .width('62%')
              .fontColor('#ff182431')
              .maxFontSize('60.0vp')
              .minFontSize('30.0vp')
              .textAlign(TextAlign.Center)
              .margin({ top: '35%' })
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .maxLines(1)

            Text('辅助文本')
              .maxFontSize('16.0fp')
              .minFontSize('10.0vp')
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .fontWeight(FontWeight.Regular)
              .width('67.4%')
              .height('9.5%')
              .textAlign(TextAlign.Center)

          }

        }.width('100%').height('100%')

      }
      .value(useEnabled(this.enableGaugeValue, this.gaugeValue))
      .startAngle(useEnabled(this.enableStartAngle, this.startAngle))
      .endAngle(useEnabled(this.enableEndAngle, this.endAngle))
      .colors(useEnabled(this.enableColors, this.colors))
      .strokeWidth(useEnabled(this.enableStrokeWidth, this.strokeWidth))
      .description(useEnabled(this.enableDescription, this.description) ? this.descriptionBuilder() : null)
      .trackShadow({
        radius: useEnabled(this.enableTrackShadowRadius, this.trackShadowRadius),
        offsetX: useEnabled(this.enableTrackShadowOffsetX, this.trackShadowOffsetX),
        offsetY: useEnabled(this.enableTrackShadowOffsetY, this.trackShadowOffsetY),
      })
      .indicator({
        icon: useEnabled(this.enableIndicatorIcon, this.indicatorIcon),
        space: useEnabled(this.enableIndicatorSpace, this.indicatorSpace),
      })

    }

  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: '显示子组件',
          isEnabled: $enableGaugeChildComponent,
          value: $gaugeChildComponent,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'value',
          isEnabled: $enableGaugeValue,
          value: $gaugeValue,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'min',
          isEnabled: $enableGaugeMin,
          value: $gaugeMin,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'max',
          isEnabled: $enableGaugeMax,
          value: $gaugeMax,
          min: 100,
          max: 400
        })

        SliderBlock({
          title: 'startAngle',
          isEnabled: $enableStartAngle,
          value: $startAngle,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'endAngle',
          isEnabled: $enableEndAngle,
          value: $endAngle,
          min: 100,
          max: 360
        })

        ColorBlock({
          title: 'colors',
          isEnabled: $enableColors,
          color: $colors
        })

        SliderBlock({
          title: 'strokeWidth',
          isEnabled: $enableStrokeWidth,
          value: $strokeWidth,
          min: 4,
          max: 10
        })

        RadioBlock({
          title: 'description',
          isEnabled: $enableDescription,
          value: $description,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })


        SliderBlock({
          title: 'trackShadow.radius',
          isEnabled: $enableTrackShadowRadius,
          value: $trackShadowRadius,
          min: 20,
          max: 50
        })

        SliderBlock({
          title: 'trackShadow.OffsetX',
          isEnabled: $enableTrackShadowOffsetX,
          value: $trackShadowOffsetX,
          min: 5,
          max: 15
        })

        SliderBlock({
          title: 'trackShadow.OffsetY',
          isEnabled: $enableTrackShadowOffsetY,
          value: $trackShadowOffsetY,
          min: 5,
          max: 15
        })

        IconBlock({
          title: 'indicator.icon',
          isEnabled: $enableIndicatorIcon,
          icon: $indicatorIcon,
        })

        SliderBlock({
          title: 'indicator.space',
          isEnabled: $enableIndicatorSpace,
          value: $indicatorSpace,
          min: 8,
          max: 20
        })

      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct GaugeBootcampPreviewer {
  build() {
    GaugeBootcamp({
      title: '数据量规图/Gauge'
    })
  }
}
