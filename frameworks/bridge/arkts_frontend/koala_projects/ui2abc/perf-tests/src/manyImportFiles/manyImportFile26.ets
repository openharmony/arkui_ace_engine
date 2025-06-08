
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent52 } from "./manyImportFile52"
import { ManyImportComponent53 } from "./manyImportFile53"


@Component
export struct ManyImportComponent26 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent52()
            ManyImportComponent53()

        }
    }
}
