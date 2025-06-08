
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent176 } from "./manyImportFile176"
import { ManyImportComponent177 } from "./manyImportFile177"


@Component
export struct ManyImportComponent88 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent176()
            ManyImportComponent177()

        }
    }
}
