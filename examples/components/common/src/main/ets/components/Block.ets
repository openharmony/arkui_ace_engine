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
import { BlockTag } from '../model/BlockTag';

@Component
export struct Block {
  @Prop title: string;
  @Link isEnabled: boolean;
  @BuilderParam content: () => void;
  @State listBlockTags: Array<BlockTag> = [];
  @State listBlockTagsTemp: Array<BlockTag> = [];

  build() {
    Column() {
      Row() {
        Text(this.title)
          .fontSize($r('sys.float.Body_M'))
          .fontColor($r('sys.color.font_secondary'))
          .fontWeight(FontWeight.Medium)
        Blank()
        Toggle({
          type: ToggleType.Switch,
          isOn: this.isEnabled
        }).onChange((enabled) => {
          this.isEnabled = enabled;
        })
      }
      .padding({ left: 8, right: 8 })
      .width('100%')

      this.content()
    }
    .margin({ top: 6 })
    .width('100%')
  }
}

@Preview
@Component
struct BlockPreview {
  @State isEnabled: boolean = false

  build() {
    Block({
      title: '标题',
      isEnabled: $isEnabled
    }) {
      Text('内容')
    }
  }
}