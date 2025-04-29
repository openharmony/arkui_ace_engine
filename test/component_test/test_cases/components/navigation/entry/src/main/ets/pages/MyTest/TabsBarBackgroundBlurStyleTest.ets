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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function tabsBarBackgroundBlurStyleTest() {
  /*
* Tabs组件 BarBackgroundBlurStyle属性
* 找到画面id为tabsBarBackgroundBlurStyle的Tabs组件
* 找到画面文本为TabsBarBackgroundBlurStyle的Button组件
* 获取tabs的BarBackgroundBlurStyle属性与期待值BlurStyle.NONE比对
* 点击button，变更tabs的BarBackgroundBlurStyle属性值为BlurStyle.BACKGROUND_THIN
* 获取tabs的BarBackgroundBlurStyle属性与期待值BlurStyle.BACKGROUND_THIN比对
*/
  defineTest('tabsBarBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarBackgroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsBarBackgroundBlurStyle').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('TabsBarBackgroundBlurStyle').enabled(true))

    let barBackgroundBlurStyle1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundBlurStyle1).$attrs.barBackgroundBlurStyle, 'BlurStyle.NONE')
    await button.tap()
    let barBackgroundBlurStyle2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundBlurStyle2).$attrs.barBackgroundBlurStyle, 'BlurStyle.BACKGROUND_THIN')
  }, 0)
}