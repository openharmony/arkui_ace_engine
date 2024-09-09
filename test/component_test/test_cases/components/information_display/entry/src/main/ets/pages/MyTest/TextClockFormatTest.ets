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

export default async function textClockFormatTest() {
  /*
  * TextClock组件 Format属性
  * 找到画面id为textClockFormat的TextClock组件
  * 获取textClock的Format属性与期待值"HH:mm:ss"比对
  */
  defineTest('textClockFormatTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFormatTest running')
    let driver: Tester = Tester.create()
    let textClock: Component = await driver.findComponent(Matcher.create().id('textClockFormat').enabled(true))
    let formatState1: string = await textClock.getInspectorInfo()
    assertEqual(JSON.parse(formatState1).$attrs.format, "HH:mm:ss")
  }, 0)
}