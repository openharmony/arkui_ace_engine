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

export default async function marqueeFontSizeTest() {
  /*
* Marquee组件 FontSize属性
* 找到画面id为marqueeFontSize1，marqueeFontSize2的Marquee组件
* 找到画面文本为MarqueeFontSize的Button组件
* 获取marquee1的FontSize属性与期待值30比对
* 点击button，变更marquee1的FontSize属性值为"50px"
* 获取marquee1的FontSize属性与期待值"50px"比对
* 获取marquee2的FontSize属性与期待值$r('app.integer.marquee_fontSize')比对
*/
  defineTest('marqueeFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeFontSizeTestDemo running')
    let driver: Tester = Tester.create()
    let marquee1: Component = await driver.findComponent(Matcher.create().id('marqueeFontSize1').enabled(true))
    let marquee2: Component = await driver.findComponent(Matcher.create().id('marqueeFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MarqueeFontSize').enabled(true))
    let fontSize1: string = await marquee1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, '30.00fp')
    await button.tap()
    let fontSize2: string = await marquee1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, "50.00px")
    let fontSize3: string = await marquee2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, $r('app.string.marquee_fontSize'))
  }, 0)
}