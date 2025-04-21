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

import { Drawer } from 'common/src/main/ets/components/Drawer';

@Component
export struct SearchCancelBootcamp {
  @Provide('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State text: string = ''
  @State changeValue: string = ''
  @State cancelStyle: CancelButtonStyle | null = CancelButtonStyle.CONSTANT;
  @State enableSearch: boolean = false;
  @State isSearch: boolean = false;
  @State enableCancel: boolean = false;
  @State isCancel: boolean = true;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Search({ value: this.changeValue, placeholder: 'Music' })
        .searchIcon({})
        .cancelButton({
          style: this.cancelStyle,
        })
        .searchButton('搜索')
    }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
  }
}

@Preview
@Component
struct SearchCancelBootcampPreviewer {
  build() {
    SearchCancelBootcamp({
      title: '搜索框关闭/SearchCancel'
    })
  }
}