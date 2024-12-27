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

@Component
export struct ContainerSpanBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableTextBackgroundStyleColor: boolean = false;
  @State textBackgroundStyleColor: Color = Color.Transparent;
  @State enableTextBackgroundStyleRadius: boolean = false;
  @State textBackgroundStyleRadius: number = 0;


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
    Row() {
      Text(){
        ContainerSpan(){
          ImageSpan($r('app.media.app_icon'))
            .width('40vp')
            .height('40vp')
            .verticalAlign(ImageSpanAlignment.CENTER)
          Span('  Hello World !  ')
            .fontSize('16fp')
            .fontColor(Color.White)
        }
          .textBackgroundStyle({
            color: useEnabled(this.enableTextBackgroundStyleColor, this.textBackgroundStyleColor),
            radius: useEnabled(this.enableTextBackgroundStyleRadius, this.textBackgroundStyleRadius)
          })

      }

    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        ColorBlock({
          title: 'textBackgroundStyle.color',
          isEnabled: this.enableTextBackgroundStyleColor,
          color: this.textBackgroundStyleColor
        })

        SliderBlock({
          title: 'textBackgroundStyle.radius',
          isEnabled: this.enableTextBackgroundStyleRadius,
          value: this.textBackgroundStyleRadius,
          min: 0,
          max: 200
        })

      }
    }
  }
}

@Preview
@Component
struct ContainerSpanBootcampPreviewer {
  build() {
    ContainerSpanBootcamp({
      title: 'ContainerSpan'
    })
  }
}

