/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function dividerColorTest() {
  /*
   * Divider组件 Color 属性
   * 找到画面id为dividerColor1,dividerColor2,dividerColor3的Divider组件
   * 找到画面文本为DividerColor的Button组件
   * 获取dividerColor1的Color属性与期待值Color.Yellow比对
   * 获取dividerColor2的Color属性与期待值'#FFFF0000'比对
   * 获取dividerColor3的Color属性与期待值'#FFFF64FF'比对
   * 点击button，变更dividerColor3的Color属性值为$r('sys.color.ohos_fa_connected')
   * 获取dividerColor3的Color属性与期待值$r('sys.color.ohos_fa_connected')比对
   */
  defineTest('dividerColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dividerColorTestDemo running')
    let driver: Tester = Tester.create()
    let dividerColor1: Component = await driver.findComponent(Matcher.create().id('dividerColor1').enabled(true))
    let dividerColor2: Component = await driver.findComponent(Matcher.create().id('dividerColor2').enabled(true))
    let dividerColor3: Component = await driver.findComponent(Matcher.create().id('dividerColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('DividerColor').enabled(true))

    let color1: string = await dividerColor1.getInspectorInfo()
    assertEqual(JSON.parse(color1).$attrs.color.toLowerCase(), Color.Yellow)

    let color2: string = await dividerColor2.getInspectorInfo()
    assertEqual(JSON.parse(color2).$attrs.color, '#FFFF0000')

    let color3: string = await dividerColor3.getInspectorInfo()
    assertEqual(JSON.parse(color3).$attrs.color, '#FFFF64FF')

    await button.tap()
    let color4: string = await dividerColor3.getInspectorInfo()
    assertEqual(JSON.parse(color4).$attrs.color, $r('sys.color.ohos_fa_connected'))
  }, 0)
}