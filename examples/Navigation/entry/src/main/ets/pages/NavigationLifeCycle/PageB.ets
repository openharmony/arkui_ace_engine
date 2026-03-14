/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
@Entry
@Component
struct PageB {

  onPageShow() {
    console.info('testTag MainWindow-pageB onPageShow');
  }

  onPageHide() {
    console.info('testTag MainWindow-pageB onPageHide');
  }

  onBackPress() {
    console.info('testTag MainWindow-pageB onBackPress');
    return false
  }

  aboutToAppear() {
    console.info('testTag MainWindow-pageB aboutToAppear');
  }

  aboutToDisappear() {
    console.info('testTag MainWindow-pageB aboutToDisappear');
  }

  build() {
    Column({space:10}){
      Text('pageB页面').fontSize(18).fontWeight(FontWeight.Bold)
      Button('router back')
        .onClick(()=>{
          router.back()
        })
    }.width('100%')
  }
}