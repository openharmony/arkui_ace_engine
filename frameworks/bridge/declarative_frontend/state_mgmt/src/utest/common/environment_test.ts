/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

const testEnvironment = tsuite("Environment", () => {
  var mockEnv = new MockEnvironmentBackend();
  var envProps : { key: string, defaultValue: boolean | number | string  }[] = [
    { key: "accessibilityEnabled", defaultValue: (mockEnv.getAccessibilityEnabled() == "true") }, // backend returns string, spec has boolean for frontend
    { key: "colorMode", defaultValue: mockEnv.getColorMode() },
    { key: "fontScale", defaultValue: mockEnv.getFontScale() },
    { key: "fontWeightScale", defaultValue: mockEnv.getFontWeightScale() },
    { key: "layoutDirection", defaultValue: mockEnv.getLayoutDirection() },
    { key: "languageCode", defaultValue: mockEnv.getLanguageCode() }
  ];

  tcase("Initialization", () => {
    Environment.configureBackend(mockEnv);
    test("Environment initialized", true);
  });

  tcase("Injecting values", () => {
    Environment.envProps(envProps);
  });

  tcase("Get all value keys", () => {
    const keys = Environment.keys();
    console.debug("Environment variables:");
    for (let i in keys) {
      console.debug(`${keys[i]} - strigified value: ${JSON.stringify(AppStorage.get(keys[i]))}`);
    }

    test("Environment number of keys returned corresponds with number of values registered", keys.length == envProps.length);
  });

  tcase("Value retrieval", () => {
    // the native backend treats bool as string
    test("Environment value 'accessibilityEnabled' correct", AppStorage.get<string>("accessibilityEnabled") == "false");
    test("Environment value 'languageCode' correct", AppStorage.get<string>("languageCode") == "cn");
  });

  tcase("Value changes from backend", () => {
    mockEnv.simulateChange("accessibilityEnabled", true);
    mockEnv.simulateChange("languageCode", "en");
    test("Environment value 'languageCode' after backend change", AppStorage.get<string>("languageCode") == "en");
    test("Environment value 'accessibilityEnabled' after backend change", AppStorage.get<boolean>("accessibilityEnabled") === true);
    test("Environment value change simulation ", true);
  });


  tcase("Teardown", () => {
    Environment.aboutToBeDeleted();
    test("Environment instance destroyed", true);
  });
});
