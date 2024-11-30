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
import { RadioBlock,  useEnabled } from 'common';

@Component
export struct ImageSpanBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableVerticalAlign: boolean = false;
  @State verticalAlign: ImageSpanAlignment = ImageSpanAlignment.BOTTOM
  @State enableObjectFit: boolean = false;
  @State objectFit: ImageFit = ImageFit.Cover
  @State imageColor: ArrayBuffer = new ArrayBuffer(96);

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
        ImageSpan($r('app.media.startIcon'))
          .width(25)
          .height(25)
          .verticalAlign(useEnabled(this.enableVerticalAlign,this.verticalAlign))
          .objectFit(useEnabled(this.enableObjectFit,this.objectFit))

      }

    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'verticalAlign',
          isEnabled: this.enableVerticalAlign,
          value: this.verticalAlign,
          dataSource: [
            { label: 'BASELINE', value: ImageSpanAlignment.BASELINE },
            { label: 'BOTTOM', value: ImageSpanAlignment.BOTTOM },
            { label: 'CENTER', value: ImageSpanAlignment.CENTER },
            { label: 'TOP', value: ImageSpanAlignment.TOP },
          ]
        })

        RadioBlock({
          title: 'objectFit',
          isEnabled: this.enableObjectFit,
          value: this.objectFit,
          dataSource: [
            { label: 'Contain', value: ImageFit.Contain },
            { label: 'Cover', value: ImageFit.Cover },
            { label: 'Auto', value: ImageFit.Auto },
            { label: 'Fill', value: ImageFit.Fill },
            { label: 'ScaleDown', value: ImageFit.ScaleDown },
            { label: 'None', value: ImageFit.None },
            { label: 'TOP_START', value: ImageFit.TOP_START },
            { label: 'TOP', value: ImageFit.TOP },
            { label: 'TOP_END', value: ImageFit.TOP_END },
            { label: 'START', value: ImageFit.START },
            { label: 'CENTER', value: ImageFit.CENTER },
            { label: 'Regular', value: ImageFit.END },
            { label: 'Medium', value: ImageFit.BOTTOM_START },
            { label: 'Bold', value: ImageFit.BOTTOM },
            { label: 'Bolder', value: ImageFit.BOTTOM_END },
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct ImageSpanBootcampPreviewer {
  build() {
    ImageSpanBootcamp({
      title: 'ImageSpan'
    })
  }
}

