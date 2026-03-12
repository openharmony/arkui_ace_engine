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

@Builder
export function Page12WithToolBarBuilder(name: string, param: Object) {
  Page12WithToolBar()
}

@Component
export struct  Page12WithToolBar {

  @Builder ToolBarBuilder() {
    Row() {
      Button('tool1').fontSize(14)
      Button('tool2').fontSize(14)
      Button('tool3').fontSize(14)
    }
  }

  @State toolbar1: CustomBuilder= this.ToolBarBuilder()

  build() {
    NavDestination(                                                                                                  ){
      Column({ space: '5vp' }) {
      }
    }
    .width('100%')
    .height('100%')
    .title('This is navDestination')
    .toolbarConfiguration(this.ToolBarBuilder(), {
      backgroundColor: '#80004AAF',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
    })
  }
}