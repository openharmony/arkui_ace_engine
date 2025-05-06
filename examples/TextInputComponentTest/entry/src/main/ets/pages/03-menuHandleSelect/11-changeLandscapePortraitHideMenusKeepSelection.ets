/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct ChangeLandscapePortraitHideMenusKeepSelection {
  build() {
    Column() {
      Text('==========操作==========\n0' +
        '1、点击选择高亮区，保持选中区，展示菜单\n' +
        '2、切换横屏，保持选中区，隐藏菜单\n' +
        '3、点击选择高亮区，保持选中区，展示菜单\n' +
        '4、切换竖屏，保持选中区，隐藏菜单\n' +
        '==========期望==========\n' +
        '1、切换横屏后，保持选中区，隐藏菜单\n' +
        '2、切换竖屏后，保持选中区，隐藏菜单')

      Text('选中文本后，切换横屏与竖屏，需要保持选中区域，隐藏菜单')
        .copyOption(CopyOptions.InApp)
        .selection(1, 5)
    }
  }
}