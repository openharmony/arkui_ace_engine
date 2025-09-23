
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent4 } from "./manyImportFile4"
import { ManyImportComponent5 } from "./manyImportFile5"


@Component
export struct ManyImportComponent2 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent4()
            ManyImportComponent5()

        }
    }
}
