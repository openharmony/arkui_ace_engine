
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent102 } from "./manyImportFile102"
import { ManyImportComponent103 } from "./manyImportFile103"


@Component
export struct ManyImportComponent51 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent102()
            ManyImportComponent103()

        }
    }
}
