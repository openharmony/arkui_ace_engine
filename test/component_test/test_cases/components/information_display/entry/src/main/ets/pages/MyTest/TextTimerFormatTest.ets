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

export default async function textTimerFormatTest() {
  /*
* TextTimer组件 Format属性
* 找到画面id为textTimerFormat的TextTimer组件
* 找到画面文本为TextTimerFormat的Button组件
* 获取textTimer的Format属性与期待值'mm:ss.SS'比对
* 点击button，变更textTimer的Format属性值为'HH:mm:ss.SS'
* 获取textTimer的Format属性与期待值'HH:mm:ss.SS'比对
*/
  defineTest('textTimerFormatTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerFormatTestDemo running')
    let driver: Tester = Tester.create()
    let textTimer: Component = await driver.findComponent(Matcher.create().id('textTimerFormat').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTimerFormat').enabled(true))
    let format1: string = await textTimer.getInspectorInfo()
    assertEqual(JSON.parse(format1).$attrs.format, 'mm:ss.SS')
    await button.tap()
    let format2: string = await textTimer.getInspectorInfo()
    assertEqual(JSON.parse(format2).$attrs.format, 'HH:mm:ss.SS')
  }, 0)
}