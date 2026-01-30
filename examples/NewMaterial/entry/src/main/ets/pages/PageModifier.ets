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

import { hdsMaterial }  from '@hms.hds.hdsMaterial';
import { AttributeUpdater } from '@kit.ArkUI';

class MyColumnUpdater extends AttributeUpdater<ColumnAttribute> {
  initializeModifier(instance: ColumnAttribute): void {
    instance.useUnionEffect(true);
  }
}
class MyUnionContainerModifier implements AttributeModifier<UnionEffectContainerAttribute> {
  pointLightParam: PointLightStyle | undefined = undefined;

  constructor(light: PointLightStyle | undefined) {
    this.pointLightParam = light;
  }

  applyNormalAttribute(instance: UnionEffectContainerAttribute): void {
    console.info("applyNormal attribute");
    instance.pointLight(this.pointLightParam);
  }
}
@Entry
@Component
struct PageModifier {
  @State y1: number = 0;
  @State spacing: number = 30;
  @State modifierUnion: AttributeUpdater<UnionEffectContainerAttribute> =
    new AttributeUpdater<UnionEffectContainerAttribute>();
  @State modifierUnion2: MyUnionContainerModifier = new MyUnionContainerModifier({ bloom: 0 })
  @State modifierColumn1: MyColumnUpdater = new MyColumnUpdater();
  @State modifierColumn2: MyColumnUpdater = new MyColumnUpdater();

  build() {
    Column() {
      UnionEffectContainer({ spacing: this.spacing }) {
        Column({ space: 20 }) {
          Text("no union") // 不使用新材质效果

          Flex()
            .pointLight({ illuminated: IlluminatedType.BORDER_CONTENT })
            .backgroundColor(0x307af7)
            .size({ width: 50, height: 50 })

          Column()
            .width(100)
            .height(100)
            .borderRadius(50) // 圆
            .translate({ x: 0, y: this.y1 }) //或offset、position之类的改变其位置
            .attributeModifier(this.modifierColumn1)
            .useUnionEffect(true)

          Column()
            .width(100)
            .height(30)
            .attributeModifier(this.modifierColumn2)
            .useUnionEffect(true)
        }
      }
      .width("80%")
      .height("50%")
      .systemMaterial(new hdsMaterial.Material({
        backgroundMaterial: {
          type: hdsMaterial.MaterialType.IMMERSIVE,
          scenario: hdsMaterial.ScenarioType.ULTRA_THIN,
          level: hdsMaterial.MaterialLevel.EXQUISITE,
          darkMode: hdsMaterial.DarkMode.ADAPTIVE
        }
      })) // 设置新材质
      .attributeModifier(this.modifierUnion)


      Row() {
        Text("inner button:")
        Button("down")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.y1 = this.y1 + 10;
            })
          })
        Button("up")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.y1 = this.y1 - 10;
            })
          })
      }.width('100%')

      Row() {
        Text("spacing:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 0;
            })
          })
        Button("50")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 50;
            })
          })
        Button("100")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 100;
            })
          })
      }.width('100%')

      Row() {
        Text("light:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.modifierUnion.attribute?.pointLight({
              lightSource: {
                intensity: 0,
                positionX: "50%",
                positionY: "50%",
                positionZ: 80
              },
              bloom: 0
            })
            // this.modifierUnion.pointLightParam = {
            //   lightSource: {
            //     intensity: 0,
            //     positionX: "50%",
            //     positionY: "50%",
            //     positionZ: 80
            //   },
            //   bloom: 0
            // };
          })
        Button("2")
          .width(100)
          .onClick(() => {
            this.modifierUnion.attribute?.pointLight({
              lightSource: {
                intensity: 2,
                positionX: "50%",
                positionY: "50%",
                positionZ: 80
              },
              bloom: 1
            })
            // this.modifierUnion.pointLightParam = {
            //   lightSource: {
            //     intensity: 2,
            //     positionX: "50%",
            //     positionY: "50%",
            //     positionZ: 80
            //   },
            //   bloom: 1
            // };
          })
        Button("10")
          .width(100)
          .onClick(() => {
            this.modifierUnion.attribute?.pointLight({
              lightSource: {
                intensity: 10,
                positionX: "50%",
                positionY: "50%",
                positionZ: 80
              },
              bloom: 1
            })
            // this.modifierUnion.pointLightParam = {
            //     lightSource: {
            //       intensity: 10,
            //       positionX: "50%",
            //       positionY: "50%",
            //       positionZ: 80
            //     },
            //     bloom: 1
            // };
          })
      }.width('100%')

      Row() {
        Text("useUnion1:")
        Button("false")
          .width(100)
          .onClick(() => {
            this.modifierColumn1.attribute?.useUnionEffect(false)
          })
        Button("true")
          .width(100)
          .onClick(() => {
            this.modifierColumn1.attribute?.useUnionEffect(true)
          })
      }.width('100%')

      Row() {
        Text("useUnion2:")
        Button("false")
          .width(100)
          .onClick(() => {
            this.modifierColumn2.attribute?.useUnionEffect(false)
          })
        Button("true")
          .width(100)
          .onClick(() => {
            this.modifierColumn2.attribute?.useUnionEffect(true)
          })
      }.width('100%')
    }.width('100%')
    .height('100%')
  }
}
