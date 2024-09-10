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
import displayPriorityTest from '../MyTest/DisplayPriorityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

class ContainerInfo {
  label: string = '';
  size: string = '';
}

class ChildInfo {
  text: string = '';
  priority: number = 0;
}

@Entry
@Component
struct DisplayPrioritySample {
  private container: ContainerInfo[] = [
    { label: 'Big container', size: '40%' },
    { label: 'Small container', size: '15%' }
  ]
  private children: ChildInfo[] = [
    { text: '1\n(priority:2)', priority: 2 },
    { text: '2\n(priority:1)', priority: 1 },
  ]
  @State currentIndex: number = 0;

  aboutToAppear(): void {
    loadComponentTestEntry(displayPriorityTest)
  }

  build() {
    Column({ space: 10 }) {
      Flex({ justifyContent: FlexAlign.SpaceBetween }) {
        Text('item.text')
          .textAlign(TextAlign.Center)
          .backgroundColor(0xbbb2cb)
          .id('textDisplayPriority1')
          .displayPriority(1)
      }
    }
  }
}