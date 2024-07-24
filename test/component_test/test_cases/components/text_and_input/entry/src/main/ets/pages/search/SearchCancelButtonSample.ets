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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import searchCancelButtonTest from '../MyTest/SearchCancelButtonTest'

@Entry
@Component
struct SearchCancelButtonSample {
  controller: SearchController = new SearchController()
  @State constantValue: CancelButtonStyle = CancelButtonStyle.CONSTANT
  @State iconValue: IconOptions = { size: '50px', src: "../../../resources/base/media/icon.png", color: 0xffff0000 }
  @State colorValue: ResourceColor = '#ffffff'

  aboutToAppear(): void {
    loadComponentTestEntry(searchCancelButtonTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .cancelButton({ style: this.constantValue, icon: this.iconValue })
        .height(50)
        .id('searchCancelButton1')
      Button('SearchCancelButton1')
        .onClick(() => {
          this.constantValue = CancelButtonStyle.INPUT
          this.iconValue = { size: 100, src: $r('app.media.startIcon'), color: Color.Blue }
        })
      Button('SearchCancelButton2')
        .onClick(() => {
          this.constantValue = CancelButtonStyle.INVISIBLE
          this.iconValue = { size: $r('app.string.length'), color: '#ffffff' }
        })
      Search({ controller: this.controller })
        .cancelButton({
          style: CancelButtonStyle.CONSTANT,
          icon: { color: $r('sys.color.ohos_id_color_text_hyperlink') }
        })
        .id('searchCancelButton2')
    }
  }
}