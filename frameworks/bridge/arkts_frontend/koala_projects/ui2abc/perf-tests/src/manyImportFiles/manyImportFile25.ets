
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent50 } from "./manyImportFile50"
import { ManyImportComponent51 } from "./manyImportFile51"


@Component
export struct ManyImportComponent25 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent50()
            ManyImportComponent51()

        }
    }
}
