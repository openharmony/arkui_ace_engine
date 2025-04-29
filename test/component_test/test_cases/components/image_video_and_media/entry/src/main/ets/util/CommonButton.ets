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

import router from '@ohos.router';

@Component
export struct CommonButton {
  @State buttonName: string = '';
  @State buttonUrl: string = '';
  @State data: string = '';

  build() {
    Text(this.buttonName)
      .id(this.buttonName)
      .padding(px2vp(5))
      .fontSize(px2fp(16))
      .backgroundColor(Color.Blue)
      .fontColor(Color.White)
      .borderRadius(5)
      .margin(px2vp(5))
      .onClick(() => {
        router.pushUrl({
          url: this.buttonUrl,
          params: {
            text: this.data,
            buttonName: this.buttonName
          }
        })
      })
  }
}