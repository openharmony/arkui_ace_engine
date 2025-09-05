
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent30 } from "./manyImportFile30"
import { ManyImportComponent31 } from "./manyImportFile31"


@Component
export struct ManyImportComponent15 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent30()
            ManyImportComponent31()

        }
    }
}
