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
import nativeNode from 'libnativeNode.so';

@Entry
@Component
struct Xcomponent {

  @State value: number = 40;
  @State width1: string = '100%';
  @State linearValue: number = 40;
  @State underline: boolean = false;

  build() {
    Column() {
      Column() {
        XComponent({
          id: 'xcomponentId11',
          type: 'node',
          libraryname: 'nativeNode'
        })
        .onAppear(() => {
          nativeNode.createNativeNode('xcomponentId11');
        }).width(400).height(600).padding(10)
          .id('xcomponent')
          .backgroundColor('#FFFFFFFF')
      }
    }
    .width('100%')
    .height('100%')
  }
}