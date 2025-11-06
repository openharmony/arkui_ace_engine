/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/*
 * Description: List支持展开指定ListItem的swipeAction
 * Writer: renxiaowen
 */

import entry from 'libentry.so';

@Entry
@Component
struct NativePage {
  @State text: string = 'Hello, Native';
  @State tag: string = 'NativePage';

  build() {
    Column({ space: 10 }) {
      XComponent({
        id: this.tag,
        type: 'node',
        libraryname: 'entry'
      }).onDestroy(() => {
        console.log('onDestroy');
      }).backgroundColor('#FFEEEEEE')
        .width('100%')
        .height('100%')
    }
    .height('100%')
    .width('100%')
    .onAppear(() => {
      entry.SwipeActionTest(this.tag);
    })
  }
}