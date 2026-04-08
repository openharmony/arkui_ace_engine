/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CustomComponentAttribute } from './CustomComponent';
import { CustomComponentDefinition } from './CustomComponentFactory';

interface BlankOptions {
  min: number;
  color: string;
}

@Component
export struct CustomBlank {
  @Prop attribute: CustomComponentAttribute | undefined = undefined;

  aboutToAppear(): void {
    console.log("ArkTS CustomBlank start build");
  }

  build() {
    Column() {
      Blank(this.resolveMin())
        .width('100%')
        .color(this.resolveColor())
    }
    .width('100%')
  }

  private resolveMin(): number {
    return this.resolveOptions().min;
  }

  private resolveColor(): string {
    return this.resolveOptions().color;
  }

  private resolveOptions(): BlankOptions {
    let customProps = this.attribute?.customProps;
    if (customProps === undefined || customProps.length === 0) {
      return { min: 0, color: '#00000000' };
    }

    try {
      let parsed = JSON.parse(customProps) as Record<string, Object>;
      let options: BlankOptions = { min: 0, color: '#00000000' };
      let minValue = Number(parsed['min']);
      if (!Number.isNaN(minValue)) {
        options.min = minValue;
      }
      let colorValue = parsed['color'];
      if (typeof colorValue === 'string' && colorValue.length > 0) {
        options.color = colorValue;
      }
      return options;
    } catch (error) {
      console.error(`CustomBlank resolveOptions parse failed: ${JSON.stringify(error)}`);
      return { min: 0, color: '#00000000' };
    }
  }
}

@Builder
export function customBlankBuilder(attribute: CustomComponentAttribute): void {
  CustomBlank({ attribute: attribute });
}

export function createBlankDefinition(): CustomComponentDefinition {
  return {
    type: 'Blank',
    builder: wrapBuilder(customBlankBuilder)
  };
}
