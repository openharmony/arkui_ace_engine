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

import { RadioBlock, useEnabled, SliderBlock } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';

@Component
export struct SliderBootcamp {
  @State showParameters: boolean = false;
  @Require @Prop title: ResourceStr;
  @State enableSliderStyle: boolean = false;
  @State sliderStyle: SliderStyle = SliderStyle.OutSet;
  @State enableShowSteps: boolean = false;
  @State showSteps: boolean = false;
  @State enableStep: boolean = false;
  @State step: number = 1;
  @State enableShowTips: boolean = false;
  @State showTips: boolean = false;
  @State enableDirection: boolean = false;
  @State currentDirection: Direction = Direction.Auto;

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
    Column({ space: 8 }) {
      Slider({ style: useEnabled(this.enableSliderStyle, this.sliderStyle), step: this.step })
        .showTips(useEnabled(this.enableShowTips, this.showTips))
        .showSteps(useEnabled(this.enableShowSteps, this.showSteps))
        .direction(useEnabled(this.enableDirection, this.currentDirection))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '滑块的位置',
          isEnabled: this.enableSliderStyle,
          value: this.sliderStyle,
          dataSource: [
            { label: '滑块在滑轨上', value: SliderStyle.OutSet },
            { label: '滑块在滑轨内', value: SliderStyle.InSet },
          ]
        })

        RadioBlock({
          title: '是否显示步长刻度值',
          isEnabled: this.enableShowSteps,
          value: this.showSteps,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false },
          ]
        })

        SliderBlock({
          title: '间续滑动步长',
          isEnabled: this.enableStep,
          value: this.step,
          min: 1,
          max: 20
        })

        RadioBlock({
          title: '是否显示气泡',
          isEnabled: this.enableShowTips,
          value: this.showTips,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false },
          ]
        })

        RadioBlock({
          title: '布局方式',
          isEnabled: this.enableDirection,
          value: this.currentDirection,
          dataSource: [
            { label: '默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
          ]
        })
      }
      .height('52%')
    }
  }
}

@Preview
@Component
struct SliderBootcampPreviewer {
  build() {
    SliderBootcamp({ title: '滑动条/Slider' })
  }
}