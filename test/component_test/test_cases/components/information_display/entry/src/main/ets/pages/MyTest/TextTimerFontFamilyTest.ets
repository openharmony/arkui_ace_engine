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

export default async function textTimerFontFamilyTest() {
  /*
  * TextTimer组件 FontFamily属性
  * 找到画面id为textTimerFontFamily的TextTimer组件
  * 找到画面文本为TextTimerFontFamily的Button组件
  * 获取textTimer的FontFamily属性与期待值'iconFont'比对
  * 点击button，变更textTimer的FontFamily属性值为"Arial"
  * 获取textTimer的FontFamily属性与期待值"Arial"比对
  */
  defineTest('textTimerFontFamilyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerFontFamilyTestDemo running')
    let driver: Tester = Tester.create()
    let textTimer: Component = await driver.findComponent(Matcher.create().id('textTimerFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTimerFontFamily').enabled(true))
    let fontFamily1: string = await textTimer.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'iconFont')
    await button.tap()
    let fontFamily2: string = await textTimer.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, "Arial")
  }, 0)
}