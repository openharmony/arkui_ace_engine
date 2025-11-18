/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import router from "@ohos.router"
import { Constants } from './Constants'

@Entry
@Component
export struct Skip {
  @State pushUrl: string = ""
  @State butName: string = ""

  build() {
    Column() {
      Button(this.butName)
        .fontSize(Constants.TEXT_FONT_SIZE)
        .fontWeight(FontWeight.Bold)
        .type(ButtonType.Capsule)
        .margin({
          top: Constants.MARGIN_TOP
        })
        .backgroundColor('#0D9FFB')
        .width(Constants.WIDTH_SIZE)
        .height(Constants.HEIGHT_SIZE)
        .onClick(() => {
          router.pushUrl({ url: this.pushUrl })
        })
    }
  }
}