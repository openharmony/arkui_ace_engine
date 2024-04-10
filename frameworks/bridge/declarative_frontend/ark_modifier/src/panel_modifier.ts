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

/// <reference path='./import.ts' />
class PanelModifier extends ArkPanelComponent implements AttributeModifier<PanelAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }

  applyNormalAttribute(instance: PanelAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<PanelAttribute, ArkPanelComponent, ArkComponent>(instance, this);
  }
}
