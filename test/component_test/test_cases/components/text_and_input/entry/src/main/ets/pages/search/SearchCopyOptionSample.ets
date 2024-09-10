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
import searchCopyOptionTest from '../MyTest/SearchCopyOptionTest'

@Entry
@Component
struct SearchCopyOptionSample {
  @State copyOptionValue: CopyOptions = CopyOptions.InApp
  controller: SearchController = new SearchController()

  aboutToAppear(): void {
    loadComponentTestEntry(searchCopyOptionTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .copyOption(CopyOptions.None)
        .id('searchCopyOption1')
      Search({ controller: this.controller })
        .copyOption(this.copyOptionValue)
        .id('searchCopyOption2')
      Button('SearchCopyOption1')
        .onClick(() => {
          this.copyOptionValue = CopyOptions.LocalDevice
        })
      Button('SearchCopyOption2')
        .onClick(() => {
          this.copyOptionValue = CopyOptions.CROSS_DEVICE
        })
    }
  }
}