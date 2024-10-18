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

export default async function marqueeFontFamilyTest() {
  /*
* Marquee组件 FontFamily属性
* 找到画面id为marqueeFontFamily的Marquee组件
* 找到画面文本为MarqueeFontFamily的Button组件
* 获取marquee的FontFamily属性与期待值'iconFont'比对
* 点击button，变更marquee的FontFamily属性值为"Arial"
* 获取marquee的FontFamily属性与期待值"Arial"比对
*/
  defineTest('marqueeFontFamilyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeFontFamilyTestDemo running')
    let driver: Tester = Tester.create()
    let marquee: Component = await driver.findComponent(Matcher.create().id('marqueeFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MarqueeFontFamily').enabled(true))
    let fontFamily1: string = await marquee.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'iconFont')
    await button.tap()
    let fontFamily2: string = await marquee.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, 'Arial')
  }, 0)
}