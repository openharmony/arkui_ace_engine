
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent16 } from "./manyImportFile16"
import { ManyImportComponent17 } from "./manyImportFile17"


@Component
export struct ManyImportComponent8 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent16()
            ManyImportComponent17()

        }
    }
}
