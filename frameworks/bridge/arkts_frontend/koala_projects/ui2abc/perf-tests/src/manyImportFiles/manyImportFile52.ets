
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent104 } from "./manyImportFile104"
import { ManyImportComponent105 } from "./manyImportFile105"


@Component
export struct ManyImportComponent52 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent104()
            ManyImportComponent105()

        }
    }
}
