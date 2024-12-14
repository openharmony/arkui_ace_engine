import { RadioBlock } from "common";
import { pointer } from "@kit.InputKit";

@Component
export struct CompEventMonopolizationBlocks {
  @Link enableCompMonopolizeEvents: boolean;
  @Link compMonopolizeEvents: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'monopolizeEvents',
        isEnabled: $enableCompMonopolizeEvents,
        value: $compMonopolizeEvents,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
    }
  }
}