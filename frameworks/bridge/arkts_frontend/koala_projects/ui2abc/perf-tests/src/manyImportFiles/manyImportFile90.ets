
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent180 } from "./manyImportFile180"
import { ManyImportComponent181 } from "./manyImportFile181"


@Component
export struct ManyImportComponent90 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent180()
            ManyImportComponent181()

        }
    }
}
