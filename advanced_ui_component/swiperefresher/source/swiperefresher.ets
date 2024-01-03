/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

const LOADINGPROGRESS_SIZE = 24
const DEFAULT_MARGIN = 16
const ITEM_SPACE = 4

@Component
export struct SwipeRefresher {
  @Prop
  content: string = null
  @Prop
  isLoading: boolean = false;

  build() {
    Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      if (this.isLoading) {
        LoadingProgress()
          .height(LOADINGPROGRESS_SIZE)
          .width(LOADINGPROGRESS_SIZE)
          .margin({
            right: ITEM_SPACE
          })
      }
      Text(this.content)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .fontSize($r('sys.float.ohos_id_text_size_body2'))
        .padding({
          top: DEFAULT_MARGIN,
          bottom: DEFAULT_MARGIN
        })
    }
  }
}