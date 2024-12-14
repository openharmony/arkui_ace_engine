import { RadioBlock } from "common";
import { pointer } from "@kit.InputKit";

@Component
export struct CompObscuringBlocks {
  @Link enableCompObscured: boolean;
  @Link compObscured: Array<ObscuredReasons>;

  build() {
    Column() {
      RadioBlock({
        title: 'obscured',
        isEnabled: $enableCompObscured,
        value: $compObscured,
        dataSource: [
          { label: 'null', value: [] },
          { label: 'PLACEHOLDER', value: [ObscuredReasons.PLACEHOLDER] },
        ]
      })
    }
  }
}