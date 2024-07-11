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

import { Block } from './Block';
import { IconPalette } from './IconPalette';

@Component
export struct IconBlock {
  @Prop title: string;
  @Link isEnabled: boolean;
  @Link icon: ResourceStr;

  build() {
    Block({
      title: this.title,
      isEnabled: $isEnabled
    }) {
      IconPalette({
        icon: this.icon,
        onChange: (icon) => {
          this.icon = icon
        },
        isEnabled: this.isEnabled
      })
    }
  }
}

@Preview
@Component
struct IconBlockPreview {
  @State isEnabled: boolean = true
  @State icon: ResourceStr = '#fd5d77'

  build() {
    IconBlock({
      title: '标题',
      isEnabled: $isEnabled,
      icon: $icon
    })
  }
}