/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import entry from 'libentry.so';
import { StatusClickComponent } from './PublishStatusClick';

@Entry
@Component
struct Index {
  build() {
    Column() {
      Column() {
        XComponent({
          id: 'xComponentId',
          type: XComponentType.NODE,
          libraryname: 'nativerender'
        }).onDestroy(() => {
          console.log('onDestroy');
        }).onAppear(() => {
          render.gridTest('xComponentId');
        }).width('100%')
          .height('100%')
      }.margin({
        top: 27,
        left: 12,
        right: 12
      })
      .height('100%')
      .width('100%')
    }
    .width('100%')
    .height('100%')
  }
}