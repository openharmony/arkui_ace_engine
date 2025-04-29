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

export default async function videoObjectFitTest_three() {
  /*
* Video组件 ObjectFit属性
* 找到画面id为videoObjectFit3的video组件
* 找到画面文本为VideoObjectFit的Button组件
* 获取video的ObjectFit属性与期待值ImageFit.ScaleDown比对
* 点击button，变更video的ObjectFit属性值为ImageFit.Fill
* 获取video的ObjectFit属性与期待值ImageFit.Fill比对
*/
  defineTest('videoObjectFitTestDemo_three', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('videoObjectFitTestDemo_three running')
    let driver: Tester = Tester.create()
    let video: Component = await driver.findComponent(Matcher.create().id('videoObjectFit3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('VideoObjectFit').enabled(true))

    let objectFit1: string = await video.getInspectorInfo()
    assertEqual(JSON.parse(objectFit1).$attrs.objectFit, 'ImageFit.ScaleDown')
    await button.tap()
    let objectFit2: string = await video.getInspectorInfo()
    assertEqual(JSON.parse(objectFit2).$attrs.objectFit, 'ImageFit.Fill')
  })
}