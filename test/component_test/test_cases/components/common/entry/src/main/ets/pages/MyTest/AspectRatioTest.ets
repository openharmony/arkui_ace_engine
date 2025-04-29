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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function aspectRatioTest() {
  /*
  * row、menu组件 aspectRatio属性
  * 找到画面id为menuAspectRatio1的menu组件
  * 获取menuAspectRatio1的aspectRatio属性与期待值5比对
  */
  defineTest('aspectRatioTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("aspectRatioTestDemo running")
    let driver: Tester = Tester.create()
    let menuAspectRatio1: Component = await driver.findComponent(Matcher.create().id('menuAspectRatio1').enabled(true))
    let aspectRatio2: string = await menuAspectRatio1.getInspectorInfo()
    assertEqual(JSON.parse(aspectRatio2).$attrs.aspectRatio, 5)
  }, 0)
}