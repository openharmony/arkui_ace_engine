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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function outlineColorTest_one() {
  /*
   * outlineColor 通用属性
   * 找到画面id为 menuItemOutlineColor1 的 menu 组件
   * 获取 menuItemOutlineColor1 的 outlineColor.left 属性与期待值 '#FFBFAAFA' 比对
   * 获取 menuItemOutlineColor1 的 outlineColor.right 属性与期待值 Color.Blue 比对
   * 获取 menuItemOutlineColor1 的 outlineColor.top 属性与期待值 '#FFFFC900' 比对
   * 获取 menuItemOutlineColor1 的 outlineColor.bottom 属性与期待值 $r("app.string.common_color") 比对
   * */
  defineTest('outlineColorTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineColorTest_oneDemo running')
    let driver: Tester = Tester.create()
    let menuItemOutlineColor1: Component =
      await driver.findComponent(Matcher.create().id('menuItemOutlineColor1').enabled(true))
    let outlineColor1: string = await menuItemOutlineColor1.getInspectorInfo()
    assertEqual(JSON.parse(outlineColor1)
      .$attrs
      .outlineColor
      .left, '#FFBFAAFA')
    assertEqual(JSON.parse(outlineColor1)
      .$attrs
      .outlineColor
      .right
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(outlineColor1)
      .$attrs
      .outlineColor
      .top, '#FFFFC900')
    assertEqual(JSON.parse(outlineColor1)
      .$attrs
      .outlineColor
      .bottom, $r("app.string.common_color"))
  }, 0)
}