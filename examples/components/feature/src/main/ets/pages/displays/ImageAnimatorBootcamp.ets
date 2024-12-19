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
import { RadioBlock, useEnabled, SliderBlock, ColorBlock } from 'common';
import { image } from '@kit.ImageKit'

@Component
export struct ImageAnimatorBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State reverse: boolean = false
  @State iterations: number = 1
  imagePixelMap: Array<PixelMap> = []
  @State images: Array<ImageFrameInfo> = []
  @State enableState: boolean = false;
  @State state: AnimationStatus = AnimationStatus.Initial
  @State enableDuration: boolean = false;
  @State duration: number = 1000
  @State enableReverse: boolean = false;
  @State eReverse: boolean = false;
  @State enableFixedSize: boolean = false;
  @State fixedSize: boolean = false;
  @State enableFillMode: boolean = false;
  @State fillMode: FillMode = FillMode.Forwards
  @State enableIterations: boolean = false;
  @State eIterations: number = 1;

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
    Column({space:10}) {
      ImageAnimator()
        .images([
          {
            src: $r('app.media.background')
          },
          {
            src: $r('app.media.indent_plus')
          },
          {
            src: $r('app.media.layered_image')
          },
          {
            src: $r('app.media.indent_minus')
          }
        ])
        .state(useEnabled(this.enableState, this.state))
        .duration(useEnabled(this.enableDuration, this.duration))
        .reverse(useEnabled(this.enableReverse, this.reverse))
        .fixedSize(useEnabled(this.enableFixedSize, this.fixedSize))
        .fillMode(useEnabled(this.enableFillMode, this.fillMode))
        .iterations(useEnabled(this.enableIterations, this.eIterations))
        .onStart(() => {
          console.info('Start')
        })
        .onPause(() => {
          console.info('Pause')
        })
        .onRepeat(() => {
          console.info('Repeat')
        })
        .onCancel(() => {
          console.info('Cancel')
        })
        .onFinish(() => {
          console.info('Finish')
          this.state = AnimationStatus.Stopped
        })


      Row() {
        Button('start').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Running
        }).margin(5)
        Button('pause').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Paused     // 显示当前帧图片
        }).margin(5)
        Button('stop').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Stopped    // 显示动画的起始帧图片
        }).margin(5)
      }

      Row() {
        Button('reverse').width(100).padding(5).onClick(() => {
          this.reverse = !this.reverse
        }).margin(5)
        Button('once').width(100).padding(5).onClick(() => {
          this.iterations = 1
        }).margin(5)
        Button('infinite').width(100).padding(5).onClick(() => {
          this.iterations = -1 // 无限循环播放
        }).margin(5)
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'state',
          isEnabled: this.enableState,
          value: this.state,
          dataSource: [
            { label: 'Initial', value: AnimationStatus.Initial },
            { label: 'Running', value: AnimationStatus.Running },
            { label: 'Paused', value: AnimationStatus.Paused },
            { label: 'Stopped', value: AnimationStatus.Stopped },

          ]
        })

        SliderBlock({
          title: 'duration',
          isEnabled: this.enableDuration,
          value: this.duration,
          min: 0,
          max: 2000
        })

        RadioBlock({
          title: 'reverse',
          isEnabled: this.enableReverse,
          value: this.reverse,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'fixedSize',
          isEnabled: this.enableFixedSize,
          value: this.fixedSize,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'fillMode',
          isEnabled: this.enableFillMode,
          value: this.fillMode,
          dataSource: [
            { label: 'None', value: FillMode.None },
            { label: 'Forwards', value: FillMode.Forwards },
            { label: 'Backwards', value: FillMode.Backwards },
            { label: 'Both', value: FillMode.Both },
          ]
        })

        SliderBlock({
          title: 'iterations',
          isEnabled: this.enableIterations,
          value: this.iterations,
          min: -1,
          max: 10
        })

      }
    }
  }
}

@Preview
@Component
struct ImageAnimatorBootcampPreviewer {
  build() {
    ImageAnimatorBootcamp({
      title: '帧动画/ImageAnimator'
    })
  }
}