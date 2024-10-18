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
import {
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function videoMutedTest() {
  /*
* Video组件 Muted属性
* 找到画面id为videoMuted的video组件
* 找到画面文本为VideoMuted的Button组件
* 获取video的Muted属性与期待值false比对
* 点击button，变更video的Muted属性值为true
* 获取video的Muted属性与期待值true比对
*/
  defineTest('videoMutedTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('videoMutedTestDemo running')
    let driver: Tester = Tester.create()
    let video: Component = await driver.findComponent(Matcher.create().id('videoMuted').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('VideoMuted').enabled(true))

    let muted1: string = await video.getInspectorInfo()
    assertFalse(JSON.parse(muted1).$attrs.muted == undefined)
    assertFalse(JSON.parse(muted1).$attrs.muted)
    await button.tap()
    let muted2: string = await video.getInspectorInfo()
    assertTrue(JSON.parse(muted2).$attrs.muted)
  })
}