
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent168 } from "./manyImportFile168"
import { ManyImportComponent169 } from "./manyImportFile169"


@Component
export struct ManyImportComponent84 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent168()
            ManyImportComponent169()

        }
    }
}
