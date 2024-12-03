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
import { ColorBlock, useEnabled } from 'common';

@Component
export struct HyperlinkBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableColor: boolean = false;
  @State color: ResourceColor | undefined = undefined;

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
      Row(){
        Hyperlink('https://example.com/') {
          Image($r('app.media.background'))
            .width(200)
            .height(100)
        }
      }

      Row(){
        Hyperlink('https://example.com/', 'Go to the developer website') {}
          .color(useEnabled(this.enableColor,this.color))
      }.width('100%').height('100%').justifyContent(FlexAlign.Center)

    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        ColorBlock({
          title: 'color',
          isEnabled: this.enableColor,
          color: this.color
        })
      }
    }
  }
}

@Preview
@Component
struct HyperlinkBootcampPreviewer {
  build() {
    HyperlinkBootcamp({
      title: 'Hyperlink'
    })
  }
}